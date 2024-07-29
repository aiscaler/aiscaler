#ifndef WORKER_H
#define WORKER_H

#include <QtCore/QObject>
#include <QtCore/QProcess>
#include <QtCore/QtContainerFwd>
#include <QtWidgets/QProgressBar>

class Worker : public QObject
{
    Q_OBJECT

public:
    explicit Worker(QObject *parent = nullptr);
    ~Worker();

    bool isRunning();
    void cancelProcess();
    void setProgressBar(QProgressBar *progressBar);
    void startProcess(const QString &program, const QStringList &args);

signals:
    void progress(int value);
    void finished(bool status);
    void errorOccurred(const QString &error);

private slots:
    void readProcessOutput();
    void onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onProcessErrorOccurred(QProcess::ProcessError error);

private:
    QProcess *process;
    QProgressBar *progressBar;
};

#endif // WORKER_H