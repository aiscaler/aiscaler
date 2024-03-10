import os
import sys
import json
import re
from glob import glob
from PyQt6.QtWidgets import (
    QApplication,
    QMainWindow,
    QFileDialog,
    QScrollArea,
    QVBoxLayout,
    QLabel,
    QWidget,
    QSizePolicy,
    QScroller,
)
from PyQt6.QtCore import Qt, QProcess, QEvent
from PyQt6.QtGui import QPixmap, QImage, QIcon, QDropEvent

import ui.resource

from ui.ui_main import Ui_MainWindow
from ui.ui_image import Ui_Image

BASE_DIR = os.path.abspath(".")
USERPROFILE = os.path.join(os.environ["USERPROFILE"], "Pictures")
MODEL_PATH = os.path.join(BASE_DIR, "models")
INPUT_PATH = USERPROFILE  # os.path.join(BASE_DIR, 'inputs')
OUTPUT_PATH = USERPROFILE  # os.path.join(BASE_DIR, 'outputs')
APPDATA = os.path.join(os.environ["APPDATA"], "AIScaler")

VERSION = "1.0.0"


class ImageWidget(QWidget, Ui_Image):
    def __init__(self, parent=None):
        super(ImageWidget, self).__init__()
        self.setupUi(self)
        self.parent = parent

        self.zoom = 1
        self.image = None

        scroller = QScroller.scroller(self.scrollArea)
        scroller.grabGesture(
            self.scrollArea.viewport(),
            QScroller.ScrollerGestureType.LeftMouseButtonGesture,
        )

        self.horizontalSlider.valueChanged.connect(self.onZoom)

    def loadImage(self, image):
        self.image = QImage(image)
        self.updateImage()

    def onZoom(self, e):
        self.zoom = e
        self.updateImage()

    def updateImage(self):
        if self.image:
            w = round(self.width() / 1.1) + (self.zoom * 10)
            h = round(self.height() / 1.1) + (self.zoom * 10)
            imgInput = QPixmap(self.image).scaled(
                w, h, Qt.AspectRatioMode.KeepAspectRatio
            )

            self.labelImage.setPixmap(imgInput)
            self.labelImage.setAlignment(Qt.AlignmentFlag.AlignCenter)

    def dragEnterEvent(self, event: QDropEvent):
        if event.mimeData().hasUrls():
            formats = ["jpg", "png", "webp"]
            if event.mimeData().text().split(".")[-1] in formats:
                event.accept()
        else:
            event.ignore()

    def dropEvent(self, event: QDropEvent):
        file = event.mimeData().text().replace("file:///", "")
        print("Drop: ", file)
        self.parent.inputs = file
        self.parent.imageInput.loadImage(file)
        self.parent.updateLabel()
        self.parent.labelStatusBar.setText(f"Drop file: {file}")


class MainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()

        self.setupUi(self)
        self.setWindowTitle("AIScaler")
        self.showMaximized()

        self.running = False
        self.zoomInput = 0
        self.zoomOutput = 0

        self.inputs = INPUT_PATH
        self.outputs = OUTPUT_PATH
        self.models = []
        self.model = []
        self.format = "jpg"
        self.formats = ["jpg", "png", "webp"]
        self.task = None
        self.tasks = []
        self.temps = {
            "inputs": INPUT_PATH,
            "outputs": OUTPUT_PATH,
        }

        self.initUi()
        self.initDir()
        self.initModel()

        self.show()

    def initUi(self):
        self.updateTemps()
        self.updateLabel()
        self.updateTask()

        self.labelVersion.setText(f"Version: {VERSION}")

        self.pushButtonFile.clicked.connect(self.onFileClicked)
        self.pushButtonFolder.clicked.connect(self.onFolderClicked)
        self.pushButtonOutput.clicked.connect(self.onOutputClicked)
        self.pushButtonProcess.clicked.connect(self.process)

        self.pushButtonOptimize.setDisabled(True)

        self.comboBoxModel.addItems(self.models)
        self.comboBoxFormat.addItems(self.formats)

        self.progressBar.setRange(0, 100)

        self.comboBoxModel.currentTextChanged.connect(self.onModelChange)
        self.comboBoxFormat.currentTextChanged.connect(self.onFormatChange)

        self.imageInput = ImageWidget(self)
        self.imageInput.setAcceptDrops(True)  # set drop support
        self.imageInput.labelTitle.setText("INPUT")
        layoutInput = QVBoxLayout()
        layoutInput.addWidget(self.imageInput)
        layoutInput.setContentsMargins(0, 0, 0, 0)

        self.imageOutput = ImageWidget()
        self.imageOutput.labelTitle.setText("OUTPUT")
        layoutOutput = QVBoxLayout()
        layoutOutput.addWidget(self.imageOutput)
        layoutOutput.setContentsMargins(0, 0, 0, 0)

        self.frameOriginal.setLayout(layoutInput)
        self.frameOutput.setLayout(layoutOutput)

    def updateTemps(self, write=False):
        tmppath = os.path.join(APPDATA, "tmp.json")
        data = json.dumps(
            {
                "inputs": self.inputs,
                "outputs": self.outputs,
            }
        )
        if not os.path.isdir(APPDATA):
            os.makedirs(APPDATA)
        if not os.path.isfile(tmppath):
            with open(tmppath, "w") as f:
                f.write(data)
                f.close()
        if write:
            with open(tmppath, "w") as f:
                f.write(data)
                self.temps["inputs"] = self.inputs
                self.temps["outputs"] = self.outputs
                f.close()
        else:
            with open(tmppath, "r") as f:
                self.temps = json.loads(f.read())
                if self.temps:
                    self.inputs = self.temps["inputs"]
                    self.outputs = self.temps["outputs"]
                f.close()

    def updateLabel(self):
        self.labelInput.setText(f"Input: {self.inputs}")
        self.labelOutput.setText(f"Output: {self.outputs}")
        self.labelInput.setToolTip(self.inputs)
        self.labelOutput.setToolTip(self.outputs)

    def updateTask(self):
        if os.path.isdir(self.inputs):
            files = [
                f
                for ext in ["jpg", "png", "webp"]
                for f in glob(f"{self.inputs}\\*.{ext}")
            ]
            print(files)
            self.tasks = files
            self.labelProgress.setText(f"{len(files)}/0")
        else:
            self.tasks = []
            self.tasks.append(self.inputs)
            self.labelProgress.setText(f"1/0")

    def initDir(self):
        if not os.path.isdir("models"):
            os.mkdir("models")
        # if not os.path.isdir('inputs'):
        #     os.mkdir('inputs')
        # if not os.path.isdir('outputs'):
        #     os.mkdir('outputs')

    def initModel(self):
        if os.path.isdir("models"):
            models = glob("models\\*.bin")
            models = [x.replace("models\\", "").replace(".bin", "") for x in models]
            self.models = models
            self.comboBoxModel.addItems(self.models)
            self.comboBoxModel.setCurrentText("RealESRGAN_General_x4_v3")

    def onFileClicked(self):
        file, _ = QFileDialog.getOpenFileName(
            self,
            "Open File",
            os.path.abspath(self.temps["inputs"]),
            "Image (*.jpg *.png *.webp)",
        )

        if file:
            print("Input: ", file)
            self.labelStatusBar.setText(f"Open file: {file}")
            self.inputs = file

            self.imageInput.loadImage(file)
            self.updateLabel()
            self.updateTemps(True)

    def onFolderClicked(self):
        folder = QFileDialog.getExistingDirectory(
            self, "Input folder", os.path.abspath(self.temps["inputs"])
        )

        if folder:
            print("Input: ", folder)
            self.labelStatusBar.setText(f"Input folder: {folder}")
            self.inputs = folder
            self.updateLabel()
            self.updateTask()
            self.updateTemps(True)

    def onOutputClicked(self):
        output = QFileDialog.getExistingDirectory(
            self, "Output folder", os.path.abspath(self.temps["outputs"])
        )

        if output:
            print("Output: ", output)
            self.labelStatusBar.setText(f"Output folder: {output}")
            self.outputs = output
            self.updateLabel()
            self.updateTemps(True)

    def onModelChange(self, e):
        print("Model: ", e)
        self.labelStatusBar.setText(f"Change model : {e}")
        self.model = e
        self.loadModel()

    def onFormatChange(self, e):
        print(e)
        self.labelStatusBar.setText(f"Change format : {e}")
        self.format = e

    def loadModel(self):
        if not os.path.isfile(f"{MODEL_PATH}\\{self.model}.bin"):
            print("model not found")
            self.labelStatusBar.setText(f"Model not found")
        else:
            self.labelStatusBar.setText("Model loaded")

    def process(self):
        if os.path.isfile(self.inputs):
            self.startTask(self.inputs)
        else:
            self.task = 0
            self.startTask(self.tasks[0])

    def startTask(self, file, task=0):
        output = self.parseOutputFile(file)

        if os.path.isdir(self.inputs):
            self.imageInput.loadImage(file)

        if not self.running:
            self.labelProgress.setText(f"{len(self.tasks)}/{task+1}")
            self.running = True
            self.proc = QProcess()
            self.proc.setProcessChannelMode(QProcess.ProcessChannelMode.MergedChannels)
            self.proc.readyRead.connect(self.onFinished)
            self.proc.finished.connect(self.showOutput)
            self.proc.start(
                "bin\\realesrgan-ncnn-vulkan",
                [
                    "-i",
                    file,
                    "-o",
                    output,
                    "-n",
                    self.model,
                    "-f",
                    self.format,
                ],
            )
            self.pushButtonProcess.setText("Stop")
            self.pushButtonProcess.setStyleSheet("background-color: red; color: white;")
        else:
            self.running = False
            self.proc.deleteLater()
            self.proc.terminate()
            self.pushButtonProcess.setText("Start")
            self.pushButtonProcess.setStyleSheet("")
            self.labelStatusBar.setText("Stoped")

    def onFinished(self):
        text = bytearray(self.proc.readAll())
        res = text.decode("ascii")
        num = re.search(r"(\d+).(\d+)", res)
        if "%" in res and num:
            prog = round(float(num[0]))
            self.progressBar.setValue(prog)
            print("Progress: ", prog)

    def showOutput(self):
        if self.running:
            self.progressBar.setValue(100)
            self.pushButtonProcess.setText("Start")
            self.pushButtonProcess.setStyleSheet("")
            self.labelStatusBar.setText("Complete")
            self.running = False
            self.proc.deleteLater()
            self.proc.terminate()

            if os.path.isfile(self.inputs):
                image = self.parseOutputFile(self.inputs)
                self.imageOutput.loadImage(image)
            else:
                image = self.parseOutputFile(self.tasks[self.task])
                self.imageOutput.loadImage(image)
                if self.task is not None and len(self.tasks) != self.task + 1:
                    self.startTask(self.tasks[self.task + 1], self.task + 1)
                    self.task += 1
                else:
                    self.task = None

    def parseOutputFile(self, file):
        ff = file.split(".")[-1]
        if os.path.isdir(self.inputs):
            fname = file.split("\\")[-1]
        else:
            fname = file.split("/")[-1]
        # fname = fname.replace(f".{ff}", f".{self.format}")
        output = os.path.join(self.outputs, fname)
        print(output)
        return output

    def destroy(self):
        self.proc.deleteLater()
        self.proc.terminate()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    app.setWindowIcon(QIcon("icon.ico"))
    app.setStyle("fusion")
    win = MainWindow()
    sys.exit(app.exec())
