#include <cmath>
#include <QtCore/QMimeData>
#include <QtCore/QThread>
#include <QtCore/Qt>
#include <QtGui/QDragEnterEvent>
#include <QtGui/QDropEvent>
#include <QtGui/QImage>
#include <QtGui/QPixmap>
#include <QtWidgets/QScroller>
#include <QtWidgets/QWidget>

#include "image.h"
#include "ui/ui_image.h"

Image::Image(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Image)
    , zoom(1)
{
    ui->setupUi(this);

    scroller->scroller(ui->scrollArea);
    scroller->grabGesture(
        ui->scrollArea->viewport(), QScroller::ScrollerGestureType::LeftMouseButtonGesture);

    qDebug() << "Image thread: " << QThread::currentThread();
}

Image::~Image()
{
    qDebug() << "Quit image widget" << ui->labelTitle->text();

    delete ui;
}

void Image::on_horizontalSlider_valueChanged(int value)
{
    zoom = value;
    resizeImage();
}

void Image::setImageTitle(const QString &title)
{
    ui->labelTitle->setText(title);
}

void Image::setImage(const QString &file)
{
    QImage img;
    if (img.load(file)) {
        QImage thumb = img.scaled(
            img.width() / 1.2, img.height() / 1.2, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        image = thumb;
        ui->labelImage->setPixmap(QPixmap::fromImage(thumb));
        resizeImage();
    }
}

void Image::resizeImage()
{
    if (!image.isNull()) {
        int w = std::round(width() / 1.1) + (zoom * 10);
        int h = std::round(height() / 1.1) + (zoom * 10);
        QPixmap imgInput = QPixmap::fromImage(image);
        ui->labelImage->setPixmap(imgInput.scaled(w, h, Qt::AspectRatioMode::KeepAspectRatio));
        ui->labelImage->setAlignment(Qt::AlignmentFlag::AlignCenter);
    }
}

void Image::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        QString urls = event->mimeData()->text();
        QStringList formatSupports = {".jpg", ".png", ".webp"};
        for (QString formatSupport : formatSupports) {
            if (urls.endsWith(formatSupport)) {
                event->acceptProposedAction();
                return;
            }
        }
    }

    event->ignore();
}

void Image::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();
    if (mimeData->hasUrls()) {
        QList<QUrl> urlList = mimeData->urls();
        if (!urlList.isEmpty()) {
            QUrl url = urlList.first();
            if (image.load(url.toLocalFile())) {
                ui->labelImage->setPixmap(QPixmap::fromImage(image));
                emit onDropped(url.toLocalFile());
                resizeImage();
            }
            event->acceptProposedAction();
        }
    }

    event->ignore();
}