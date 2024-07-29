#ifndef IMAGE_H
#define IMAGE_H

#include <QtCore/QObject>
#include <QtGui/QDragEnterEvent>
#include <QtGui/QDropEvent>
#include <QtGui/QImage>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QScroller>
#include <QtWidgets/QWidget>

namespace Ui {
class Image;
}

class Image : public QWidget
{
    Q_OBJECT

public:
    explicit Image(QWidget *parent = nullptr);
    ~Image();

    void setImageTitle(const QString &title);
    void setImage(const QString &file);
    void resizeImage();

signals:
    void onDropped(const QString &title);

private slots:
    void on_horizontalSlider_valueChanged(int value);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    Ui::Image *ui;
    QScroller *scroller;
    QImage image;
    int zoom;
};

#endif // IMAGE_H