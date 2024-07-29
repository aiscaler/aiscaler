#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QFileDevice>
#include <QtCore/QFileInfo>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QObject>
#include <QtCore/QSize>
#include <QtCore/QStandardPaths>
#include <QtCore/QThread>
#include <QtCore/QTimer>
#include <QtCore/QtContainerFwd>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

#include "image.h"
#include "mainwindow.h"
#include "ui/ui_mainwindow.h"
#include "worker.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , worker(new Worker(this))
{
    ui->setupUi(this);

    inputMode = FILE_MODE;

    ui->pushButtonOptimize->setDisabled(true);
    ui->pushButtonProcess->setDisabled(true);

    listFormat = {"jpg", "png", "webp"};
    ui->comboBoxFormat->addItems(listFormat);

    listModel = loadModel("models");
    if (listModel.length() >= 1)
        ui->comboBoxModel->addItems(listModel);
    else
        QMessageBox::warning(nullptr, "Warning", "Model not detected");

    imageInput = new Image();
    imageInput->setImageTitle("Input");
    imageInput->setAcceptDrops(true);
    QVBoxLayout *layoutInput = new QVBoxLayout;
    layoutInput->addWidget(imageInput);
    ui->frameOriginal->setLayout(layoutInput);

    imageResult = new Image();
    imageResult->setImageTitle("Output");
    QVBoxLayout *layoutResult = new QVBoxLayout;
    layoutResult->addWidget(imageResult);
    ui->frameOutput->setLayout(layoutResult);

    worker->setProgressBar(ui->progressBar);

    connect(worker, &Worker::finished, this, &MainWindow::processFinished);
    connect(imageInput, &Image::onDropped, this, [this](const QString &val) {
        inputMode = FILE_MODE;
        inputFile = val;
        ui->labelStatusBar->setText("File selected: " + val);
        ui->labelInput->setText("Input : " + val);
        ui->labelInput->setToolTip(val);
        ui->pushButtonProcess->setDisabled(false);
    });

    qDebug() << "Main thread: " << QThread::currentThread();

    QTimer::singleShot(0, [this] { readJsonConfig(); });
}

MainWindow::~MainWindow()
{
    qDebug() << "Quit main app";

    delete worker;
    delete ui;
}

void MainWindow::setVersion(QString version)
{
    ui->labelVersion->setText("Version: " + version);
}

void MainWindow::on_pushButtonFolder_clicked()
{
    qDebug() << "CLICKED: open folder";

    inputFolder = QFileDialog::getExistingDirectory(
        nullptr, "Open folder", "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!inputFolder.isEmpty()) {
        qDebug() << "FOLDER SELECTED:" << inputFolder.toStdString();

        ui->labelStatusBar->setText("Folder selected: " + inputFolder);
        ui->labelInput->setText(inputFolder);
        ui->labelInput->setToolTip(inputFolder);

        if (!loadImages(inputFolder))
            ui->pushButtonProcess->setDisabled(true);

        inputMode = FOLDER_MODE;

        if (!listModel.isEmpty())
            ui->pushButtonProcess->setDisabled(false);
    }
}

void MainWindow::on_pushButtonFile_clicked()
{
    qDebug() << "CLICKED: open file";

    inputFile
        = QFileDialog::getOpenFileName(nullptr, "Open file", "", "Images (*.png *.webp *.jpg)");

    if (!inputFile.isEmpty()) {
        qDebug() << "FILE SELECTED:" << inputFile.toStdString();

        ui->labelStatusBar->setText("File selected: " + inputFile);
        ui->labelInput->setText("Input : " + inputFile);
        ui->labelInput->setToolTip(inputFile);
        imageInput->setImage(inputFile);

        inputMode = FILE_MODE;

        if (!outputFolder.isEmpty())
            ui->pushButtonProcess->setDisabled(false);
    }
}

void MainWindow::on_pushButtonOutput_clicked()
{
    qDebug() << "CLICKED: output";

    outputFolder = QFileDialog::getExistingDirectory(
        nullptr, "Open folder", "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!outputFolder.isEmpty()) {
        qDebug() << "OUTPUT FOLDER SELECTED:" << outputFolder.toStdString();

        ui->labelStatusBar->setText("Output folder selected: " + outputFolder);
        ui->labelOutput->setText("Output : " + outputFolder);
        ui->labelOutput->setToolTip(outputFolder);

        if (!listModel.isEmpty())
            ui->pushButtonProcess->setDisabled(false);
    }
}

void MainWindow::on_pushButtonOptimize_clicked()
{
    qDebug() << "CLICKED: optimize";
}

void MainWindow::on_pushButtonProcess_clicked()
{
    writeJsonConfig();

    if (worker->isRunning()) {
        qDebug() << "CLICKED: canceled";

        ui->pushButtonProcess->setDisabled(true);
        worker->cancelProcess();
        return;
    }

    qDebug() << "CLICKED: process";

    processed = 1;

    if (inputMode == FOLDER_MODE) {
        process(inputFolder + "/" + listFile[processed - 1]);
        ui->labelProgress->setText("1/" + QString::number(listFile.length()));
        return;
    }

    process(inputFile);
}

void MainWindow::on_comboBoxModel_currentTextChanged(QString value)
{
    qDebug() << "MODEL CHANGED: " << value.toStdString();

    ui->labelStatusBar->setText("Model selected: " + value);
}

void MainWindow::on_comboBoxFormat_currentTextChanged(QString value)
{
    qDebug() << "FORMAT CHANGED: " << value.toStdString();

    ui->labelStatusBar->setText("Format selected: " + value);
}

bool MainWindow::loadImages(QString filePath)
{
    ui->labelStatusBar->setText("Load images from: " + filePath);

    QDir dir(filePath);
    QStringList filters = {"*.jpg", "*.webp", "*.png"};
    listFile = dir.entryList(filters, QDir::Files);

    qDebug() << "TOTAL FILE:" << listFile.length();

    ui->labelProgress->setText("0/" + QString::number(listFile.length()));

    if (listFile.isEmpty()) {
        QMessageBox::warning(nullptr, "Info", "no image found");
        return false;
    }

    imageInput->setImage(filePath + "/" + listFile[0]);
    QMessageBox::information(nullptr, "Info", QString::number(listFile.length()) + " images found");
    return true;
}

QStringList MainWindow::loadModel(const QString &path)
{
    QDir dir(path);

    QStringList filters = {"*.bin"};
    QStringList binFiles = dir.entryList(filters, QDir::Files);
    QStringList models;

    for (QString file : binFiles)
        models << file.replace(".bin", "");

    return models;
}

void MainWindow::process(const QString &filePath)
{
    QDir dir = QDir::current();
    QString program = dir.absoluteFilePath("models/realesrgan-ncnn-vulkan");
    QString modelPath = dir.absoluteFilePath("models");
    QFileInfo fileInfo(filePath);
    outputFile
        = replaceSuffix(outputFolder + "/" + fileInfo.fileName(), ui->comboBoxFormat->currentText());
    QFileInfo outputFileInfo(outputFile);

    qDebug() << "Check output exist:" << outputFile;

    if (outputFileInfo.exists()) {
        QMessageBox msgBox;
        msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Warning");
        msgBox.setText("Output File Already Exist, Do You Want to Replace It?");
        if (msgBox.exec() == QMessageBox::Cancel)
            return;
    }

    ui->labelStatusBar->setText("Processing: " + filePath);
    ui->pushButtonProcess->setText("Stop");
    ui->pushButtonProcess->setStyleSheet("background-color: red; color: white;");

    worker->startProcess(
        program,
        {"-i", filePath, "-o", outputFile, "-m", modelPath, "-n", ui->comboBoxModel->currentText()});
}

void MainWindow::processFinished(bool status)
{
    ui->pushButtonProcess->setDisabled(false);

    if (status) {
        // Process next image if FOLDER_MODE
        if (inputMode == FOLDER_MODE && processed - 1 != listFile.length() - 1) {
            processed += 1;
            QString inputImg = inputFolder + "/" + listFile[processed - 1];
            imageInput->setImage(inputImg);
            imageResult->setImage(outputFile);

            process(inputImg);
            ui->labelProgress->setText(
                QString::number(processed) + "/" + QString::number(listFile.length()));
            return;
        }

        QMessageBox::information(nullptr, "Info", "Process Completed");

        imageResult->setImage(outputFile);
        ui->labelStatusBar->setText("Completed: " + outputFile);
        ui->labelProgress->setText(
            QString::number(processed) + "/" + QString::number(listFile.length()));

    } else {
        ui->labelStatusBar->setText("Canceled");
        QMessageBox::information(nullptr, "Info", "Process Canceled");
    }

    ui->pushButtonProcess->setText("Start");
    ui->pushButtonProcess->setStyleSheet("");
}

QString MainWindow::replaceSuffix(const QString &filePath, const QString &newSuffix)
{
    QFileInfo fileInfo(filePath);
    QString baseName = fileInfo.completeBaseName();

    if (fileInfo.suffix() != "png") {
        QString newFileName = baseName + "." + newSuffix;
        QDir dir = fileInfo.dir();
        QString newFilePath = dir.filePath(newFileName);

        return newFilePath;
    }

    return filePath;
}

void MainWindow::writeJsonConfig()
{
    QString appDataLoc = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    QDir dir(appDataLoc);
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            qWarning() << "Failed to create directory :" << appDataLoc;
            return;
        }
    }

    QJsonObject jsonObj;

    jsonObj["mode"] = inputMode;
    if (inputMode == FILE_MODE)
        jsonObj["input"] = inputFile;
    else
        jsonObj["input"] = inputFolder;
    jsonObj["output"] = outputFolder;

    QJsonDocument config(jsonObj);

    QString filePath = dir.filePath("config.json");
    QFile configFile(filePath);

    qDebug() << "Write JSON config : " << filePath;

    if (!configFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    configFile.write(config.toJson());
    configFile.close();
}

void MainWindow::readJsonConfig()
{
    QString appDataLoc = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    QDir dir(appDataLoc);
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            qWarning() << "Failed to create directory : " << appDataLoc;
            return;
        }
    }
    if (!dir.exists("config.json")) {
        qWarning() << "File config.json not found in : " << appDataLoc;
        return;
    }

    QString filePath = dir.filePath("config.json");

    qDebug() << "Read JSON config : " << filePath;

    QFile configFile(filePath);
    if (!configFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't read file.");
        return;
    }

    QByteArray dataArray = configFile.readAll();
    QJsonDocument config(QJsonDocument::fromJson(dataArray));

    outputFolder = config["output"].toString();
    ui->labelOutput->setText("Output : " + outputFolder);
    ui->labelOutput->setToolTip(outputFolder);

    if (!inputFile.isEmpty())
        ui->pushButtonProcess->setDisabled(false);

    inputMode = config["mode"].toString();
    if (inputMode == FOLDER_MODE) {
        inputFolder = config["input"].toString();
        ui->labelInput->setText("Input : " + inputFolder);
        ui->labelInput->setToolTip(inputFolder);
        ui->tabWidget->setCurrentIndex(1);

        if (loadImages(inputFolder))
            ui->pushButtonProcess->setDisabled(false);
    }

    configFile.close();
}
