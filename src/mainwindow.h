#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QObject>
#include <QtWidgets/QMainWindow>

#include "image.h"
#include "worker.h"

namespace Ui {
class MainWindow;
}

#define FOLDER_MODE "FOLDER"
#define FILE_MODE "FILE"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setVersion(QString version);

private slots:
    void on_pushButtonFolder_clicked();
    void on_pushButtonFile_clicked();
    void on_pushButtonOutput_clicked();
    void on_pushButtonOptimize_clicked();
    void on_pushButtonProcess_clicked();

    void on_comboBoxModel_currentTextChanged(QString value);
    void on_comboBoxFormat_currentTextChanged(QString value);

private:
    Ui::MainWindow *ui;

    int processed;

    QStringList listFormat;
    QStringList listModel;
    QStringList listFile;

    QString inputMode;
    QString inputFile;
    QString inputFolder;
    QString currentFile;
    QString outputFolder;
    QString outputFile;

    Image *imageInput;
    Image *imageResult;
    Worker *worker;

    void process(const QString &filePath);
    void processFinished(bool status);
    void writeJsonConfig();
    void readJsonConfig();
    bool loadImages(QString path);

    QStringList loadModel(const QString &path);
    QString replaceSuffix(const QString &filePath, const QString &newSuffix);
};

#endif // MAINWINDOW_H