/********************************************************************************
** Form generated from reading UI file 'ui_imageNfkuPN.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGENFKUPN_H
#define UI_IMAGENFKUPN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Image
{
public:
    QGridLayout *gridLayout;
    QSlider *horizontalSlider;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaContent;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelImage;
    QLabel *labelTitle;

    void setupUi(QWidget *Image)
    {
        if (Image->objectName().isEmpty())
            Image->setObjectName("Image");
        Image->resize(424, 323);
        Image->setStyleSheet(QString::fromUtf8("#frame {\n"
"	background-color: rgb(255, 255, 255);\n"
"}"));
        gridLayout = new QGridLayout(Image);
        gridLayout->setObjectName("gridLayout");
        horizontalSlider = new QSlider(Image);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider, 2, 0, 1, 1);

        frame = new QFrame(Image);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(frame);
        scrollArea->setObjectName("scrollArea");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        scrollArea->setWidgetResizable(true);
        scrollArea->setAlignment(Qt::AlignCenter);
        scrollAreaContent = new QWidget();
        scrollAreaContent->setObjectName("scrollAreaContent");
        scrollAreaContent->setGeometry(QRect(0, 0, 402, 246));
        sizePolicy.setHeightForWidth(scrollAreaContent->sizePolicy().hasHeightForWidth());
        scrollAreaContent->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(scrollAreaContent);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        labelImage = new QLabel(scrollAreaContent);
        labelImage->setObjectName("labelImage");
        sizePolicy.setHeightForWidth(labelImage->sizePolicy().hasHeightForWidth());
        labelImage->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setPointSize(10);
        labelImage->setFont(font);
        labelImage->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(labelImage);

        scrollArea->setWidget(scrollAreaContent);

        verticalLayout->addWidget(scrollArea);


        gridLayout->addWidget(frame, 1, 0, 1, 1);

        labelTitle = new QLabel(Image);
        labelTitle->setObjectName("labelTitle");
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelTitle->sizePolicy().hasHeightForWidth());
        labelTitle->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Segoe UI")});
        font1.setPointSize(12);
        font1.setBold(true);
        labelTitle->setFont(font1);
        labelTitle->setStyleSheet(QString::fromUtf8("font-weight: bold;"));
        labelTitle->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labelTitle, 0, 0, 1, 1);


        retranslateUi(Image);

        QMetaObject::connectSlotsByName(Image);
    } // setupUi

    void retranslateUi(QWidget *Image)
    {
        Image->setWindowTitle(QCoreApplication::translate("Image", "Image", nullptr));
        labelImage->setText(QString());
        labelTitle->setText(QCoreApplication::translate("Image", "Title", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Image: public Ui_Image {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGENFKUPN_H
