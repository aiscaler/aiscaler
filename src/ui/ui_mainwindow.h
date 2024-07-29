/********************************************************************************
** Form generated from reading UI file 'mainwindowDKgwvA.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWINDOWDKGWVA_H
#define MAINWINDOWDKGWVA_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QLabel *labelInput;
    QPushButton *pushButtonOptimize;
    QLabel *label_4;
    QLabel *labelOutput;
    QLabel *labelProgress;
    QLabel *label_9;
    QPushButton *pushButtonOutput;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButtonFile;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButtonFolder;
    QLabel *label_5;
    QProgressBar *progressBar;
    QLabel *label_7;
    QComboBox *comboBoxModel;
    QComboBox *comboBoxFormat;
    QLabel *label_3;
    QPushButton *pushButtonProcess;
    QFrame *frame_2;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QLabel *labelVersion;
    QSpacerItem *verticalSpacer;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QFrame *frameOriginal;
    QFrame *frameOutput;
    QFrame *frameStatusBar;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelStatusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(875, 598);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setMinimumSize(QSize(230, 0));
        frame->setMaximumSize(QSize(230, 16777215));
        QFont font;
        font.setPointSize(8);
        frame->setFont(font);
        frame->setStyleSheet(QString::fromUtf8("#frame {\n"
"   background-color: rgb(255, 255, 255);\n"
"}"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName("gridLayout_2");
        labelInput = new QLabel(frame);
        labelInput->setObjectName("labelInput");
        sizePolicy.setHeightForWidth(labelInput->sizePolicy().hasHeightForWidth());
        labelInput->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Segoe UI")});
        labelInput->setFont(font1);

        gridLayout_2->addWidget(labelInput, 1, 0, 1, 2);

        pushButtonOptimize = new QPushButton(frame);
        pushButtonOptimize->setObjectName("pushButtonOptimize");
        pushButtonOptimize->setEnabled(false);
        pushButtonOptimize->setFont(font1);

        gridLayout_2->addWidget(pushButtonOptimize, 16, 0, 1, 2);

        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setFont(font1);

        gridLayout_2->addWidget(label_4, 11, 0, 1, 2);

        labelOutput = new QLabel(frame);
        labelOutput->setObjectName("labelOutput");
        sizePolicy.setHeightForWidth(labelOutput->sizePolicy().hasHeightForWidth());
        labelOutput->setSizePolicy(sizePolicy);
        labelOutput->setFont(font1);

        gridLayout_2->addWidget(labelOutput, 5, 0, 1, 2);

        labelProgress = new QLabel(frame);
        labelProgress->setObjectName("labelProgress");
        labelProgress->setFont(font1);
        labelProgress->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(labelProgress, 17, 1, 1, 1);

        label_9 = new QLabel(frame);
        label_9->setObjectName("label_9");
        label_9->setFont(font1);

        gridLayout_2->addWidget(label_9, 9, 0, 1, 2);

        pushButtonOutput = new QPushButton(frame);
        pushButtonOutput->setObjectName("pushButtonOutput");
        pushButtonOutput->setMinimumSize(QSize(130, 0));
        pushButtonOutput->setFont(font1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/icons/folder_96px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonOutput->setIcon(icon1);

        gridLayout_2->addWidget(pushButtonOutput, 6, 0, 1, 2);

        tabWidget = new QTabWidget(frame);
        tabWidget->setObjectName("tabWidget");
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tab = new QWidget();
        tab->setObjectName("tab");
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setObjectName("verticalLayout");
        pushButtonFile = new QPushButton(tab);
        pushButtonFile->setObjectName("pushButtonFile");
        pushButtonFile->setFont(font1);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icon/icons/image_96px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonFile->setIcon(icon2);

        verticalLayout->addWidget(pushButtonFile);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        verticalLayout_2 = new QVBoxLayout(tab_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        pushButtonFolder = new QPushButton(tab_2);
        pushButtonFolder->setObjectName("pushButtonFolder");
        pushButtonFolder->setFont(font1);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icon/icons/pictures_folder_96px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonFolder->setIcon(icon3);

        verticalLayout_2->addWidget(pushButtonFolder);

        tabWidget->addTab(tab_2, QString());

        gridLayout_2->addWidget(tabWidget, 2, 0, 1, 2);

        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setFont(font1);

        gridLayout_2->addWidget(label_5, 15, 0, 1, 1);

        progressBar = new QProgressBar(frame);
        progressBar->setObjectName("progressBar");
        progressBar->setFont(font1);
        progressBar->setValue(0);
        progressBar->setAlignment(Qt::AlignCenter);
        progressBar->setTextVisible(true);

        gridLayout_2->addWidget(progressBar, 18, 0, 1, 2);

        label_7 = new QLabel(frame);
        label_7->setObjectName("label_7");
        label_7->setFont(font1);

        gridLayout_2->addWidget(label_7, 17, 0, 1, 1);

        comboBoxModel = new QComboBox(frame);
        comboBoxModel->setObjectName("comboBoxModel");
        comboBoxModel->setFont(font1);

        gridLayout_2->addWidget(comboBoxModel, 8, 0, 1, 2);

        comboBoxFormat = new QComboBox(frame);
        comboBoxFormat->setObjectName("comboBoxFormat");
        comboBoxFormat->setFont(font1);

        gridLayout_2->addWidget(comboBoxFormat, 10, 0, 1, 2);

        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setFont(font1);

        gridLayout_2->addWidget(label_3, 7, 0, 1, 2);

        pushButtonProcess = new QPushButton(frame);
        pushButtonProcess->setObjectName("pushButtonProcess");
        pushButtonProcess->setEnabled(false);
        pushButtonProcess->setFont(font1);
        pushButtonProcess->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(pushButtonProcess, 13, 0, 1, 2);

        frame_2 = new QFrame(frame);
        frame_2->setObjectName("frame_2");
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_2);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(-1, 0, -1, -1);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(-1, -1, -1, 0);
        label = new QLabel(frame_2);
        label->setObjectName("label");
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMaximumSize(QSize(40, 40));
        label->setStyleSheet(QString::fromUtf8(""));
        label->setPixmap(QPixmap(QString::fromUtf8(":/image/icons/icon.ico")));
        label->setScaledContents(true);

        horizontalLayout_3->addWidget(label);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_2 = new QLabel(frame_2);
        label_2->setObjectName("label_2");
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Segoe UI")});
        font2.setPointSize(19);
        font2.setBold(true);
        label_2->setFont(font2);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(201, 0, 0);\n"
"font-weight: bold;"));

        verticalLayout_3->addWidget(label_2);

        labelVersion = new QLabel(frame_2);
        labelVersion->setObjectName("labelVersion");
        sizePolicy1.setHeightForWidth(labelVersion->sizePolicy().hasHeightForWidth());
        labelVersion->setSizePolicy(sizePolicy1);
        labelVersion->setFont(font1);

        verticalLayout_3->addWidget(labelVersion);


        horizontalLayout_3->addLayout(verticalLayout_3);


        gridLayout_3->addLayout(horizontalLayout_3, 0, 0, 1, 1);


        gridLayout_2->addWidget(frame_2, 0, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 14, 0, 1, 2);


        gridLayout->addWidget(frame, 0, 0, 2, 1);

        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy2);
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        splitter = new QSplitter(widget);
        splitter->setObjectName("splitter");
        splitter->setLineWidth(0);
        splitter->setOrientation(Qt::Horizontal);
        splitter->setOpaqueResize(true);
        splitter->setHandleWidth(0);
        splitter->setChildrenCollapsible(true);
        frameOriginal = new QFrame(splitter);
        frameOriginal->setObjectName("frameOriginal");
        sizePolicy2.setHeightForWidth(frameOriginal->sizePolicy().hasHeightForWidth());
        frameOriginal->setSizePolicy(sizePolicy2);
        frameOriginal->setStyleSheet(QString::fromUtf8(""));
        frameOriginal->setFrameShape(QFrame::StyledPanel);
        frameOriginal->setFrameShadow(QFrame::Raised);
        frameOriginal->setLineWidth(1);
        splitter->addWidget(frameOriginal);
        frameOutput = new QFrame(splitter);
        frameOutput->setObjectName("frameOutput");
        sizePolicy2.setHeightForWidth(frameOutput->sizePolicy().hasHeightForWidth());
        frameOutput->setSizePolicy(sizePolicy2);
        frameOutput->setFrameShape(QFrame::StyledPanel);
        frameOutput->setFrameShadow(QFrame::Raised);
        splitter->addWidget(frameOutput);

        horizontalLayout->addWidget(splitter);


        gridLayout->addWidget(widget, 0, 1, 2, 1);

        frameStatusBar = new QFrame(centralwidget);
        frameStatusBar->setObjectName("frameStatusBar");
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(frameStatusBar->sizePolicy().hasHeightForWidth());
        frameStatusBar->setSizePolicy(sizePolicy3);
        frameStatusBar->setStyleSheet(QString::fromUtf8("#frameStatusBar {\n"
"   background-color: rgb(255, 255, 255);\n"
"}"));
        frameStatusBar->setFrameShape(QFrame::NoFrame);
        frameStatusBar->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frameStatusBar);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(-1, 6, -1, 6);
        labelStatusBar = new QLabel(frameStatusBar);
        labelStatusBar->setObjectName("labelStatusBar");

        horizontalLayout_2->addWidget(labelStatusBar);


        gridLayout->addWidget(frameStatusBar, 2, 0, 1, 2);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "AIScaler", nullptr));
        labelInput->setText(QCoreApplication::translate("MainWindow", "Input", nullptr));
        pushButtonOptimize->setText(QCoreApplication::translate("MainWindow", "Optimize Images", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Action", nullptr));
        labelOutput->setText(QCoreApplication::translate("MainWindow", "Output", nullptr));
        labelProgress->setText(QCoreApplication::translate("MainWindow", "0/1", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Format", nullptr));
        pushButtonOutput->setText(QCoreApplication::translate("MainWindow", "Output Folder", nullptr));
        pushButtonFile->setText(QCoreApplication::translate("MainWindow", "Input File", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "File Image", nullptr));
        pushButtonFolder->setText(QCoreApplication::translate("MainWindow", "Input Folder", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "File Batch", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Tools", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Progress", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Model", nullptr));
        pushButtonProcess->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        label->setText(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "AIScaler", nullptr));
        labelVersion->setText(QCoreApplication::translate("MainWindow", "Version: 1.0.0", nullptr));
        labelStatusBar->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOWDKGWVA_H
