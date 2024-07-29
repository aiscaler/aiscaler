#include <QtCore/QByteArray>
#include <QtCore/QDir>
#include <QtCore/QObject>
#include <QtCore/QProcess>
#include <QtCore/QRegularExpression>
#include <QtCore/QRegularExpressionMatch>
#include <QtCore/QThread>
#include <QtCore/Qt>

#include "worker.h"

Worker::Worker(QObject *parent)
    : QObject(parent)
    , process(new QProcess(this))
    , progressBar(nullptr)
{
    process->setProcessChannelMode(QProcess::ProcessChannelMode::MergedChannels);

    connect(process, &QProcess::readyReadStandardOutput, this, &Worker::readProcessOutput);
    connect(
        process,
        QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
        this,
        &Worker::onProcessFinished);
    connect(process, &QProcess::errorOccurred, this, &Worker::onProcessErrorOccurred);

    qDebug() << "Worker thread: " << QThread::currentThread();
}

Worker::~Worker()
{
    qDebug() << "Quit worker app";

    delete process;
}

void Worker::setProgressBar(QProgressBar *progressBar)
{
    this->progressBar = progressBar;
}

void Worker::startProcess(const QString &program, const QStringList &args)
{
    qDebug() << "Program Path" << program << args;

    progressBar->setValue(0);
    emit progress(0);
    process->start(program, args);
}

void Worker::readProcessOutput()
{
    while (process->canReadLine()) {
        QByteArray line = process->readLine();
        QString text(line);
        QRegularExpression regex(R"((\d{2}\.\d{2})%)");
        QRegularExpressionMatch match = regex.match(text);

        if (match.hasMatch()) {
            QString percentageStr = match.captured(1);
            bool ok;
            double percentage = percentageStr.toDouble(&ok);

            if (ok) {
                int value = static_cast<int>(percentage);
                progressBar->setValue(value);
                emit progress(value);
                qDebug() << "PROGRESS:" << percentageStr << "Value:" << value;
            }
        }
    }
}

bool Worker::isRunning()
{
    return process->state() == QProcess::Running;
}

void Worker::cancelProcess()
{
    if (process->state() == QProcess::Running) {
        process->terminate();

        if (!process->waitForFinished(1000)) {
            process->kill();
        }

        progressBar->setValue(0);
        emit progress(0);
    }
}

void Worker::onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    Q_UNUSED(exitCode)

    if (exitStatus == QProcess::CrashExit) {
        emit finished(false);
        emit progress(progressBar->minimum());
        progressBar->setValue(progressBar->minimum());
        return;
    }

    emit progress(progressBar->maximum());
    progressBar->setValue(progressBar->maximum());

    emit finished(true);
}

void Worker::onProcessErrorOccurred(QProcess::ProcessError error)
{
    Q_UNUSED(error);

    QString errorMsg = process->errorString();

    qWarning() << "PROCESS ERROR:" << errorMsg;

    emit errorOccurred(errorMsg);
}