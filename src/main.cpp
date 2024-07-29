#include <csignal>
#include <QtGui/QIcon>
#include <QtGui/QPalette>
#include <QtWidgets/QApplication>
#include <QtWidgets/QStyleFactory>

#include "mainwindow.h"

void handleSigterm(int)
{
    QApplication::quit();
}

int main(int argc, char *argv[])
{
    // Handle term quit
    signal(SIGTERM, handleSigterm);
    signal(SIGINT, handleSigterm);

    QApplication app(argc, argv);
    app.setStyle(QStyleFactory::create("Fusion"));
    app.setWindowIcon(QIcon(":/image/icon.ico"));

    QPalette lightPalette;

    lightPalette.setColor(QPalette::Window, Qt::white);
    lightPalette.setColor(QPalette::WindowText, Qt::black);
    lightPalette.setColor(QPalette::Base, Qt::white);
    lightPalette.setColor(QPalette::AlternateBase, Qt::lightGray);
    lightPalette.setColor(QPalette::ToolTipBase, Qt::black);
    lightPalette.setColor(QPalette::ToolTipText, Qt::white);
    lightPalette.setColor(QPalette::Text, Qt::black);
    lightPalette.setColor(QPalette::Button, Qt::white);
    lightPalette.setColor(QPalette::ButtonText, Qt::black);
    lightPalette.setColor(QPalette::BrightText, Qt::red);
    lightPalette.setColor(QPalette::Link, Qt::blue);
    lightPalette.setColor(QPalette::Highlight, Qt::blue);
    lightPalette.setColor(QPalette::HighlightedText, Qt::white);

    app.setPalette(lightPalette);

    MainWindow w;
    w.setWindowTitle("AIScaler");
    w.resize(QSize(1200, 600));
    w.setVersion("1.0.0");

    w.show();

    return app.exec();
}

#ifdef _WIN32
#include <Windows.h>
#include <shellapi.h>

int WINAPI CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd)
{
    int argc = 0;
    auto argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    std::vector<QByteArray> argv_utf8;

    for (int i = 0; i < argc; i++) {
        argv_utf8.push_back(QString::fromUtf16((const char16_t *) argv[i]).toUtf8());
    }

    LocalFree(argv);
    std::vector<char *> argv_main;

    for (auto &arg : argv_utf8) {
        argv_main.push_back(arg.data());
    }

    return main(argc, argv_main.data());
}
#endif // _WIN32