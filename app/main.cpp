#include "logging.h"
#include "mainwindow.h"

#include <QApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QString>
#include <QTextStream>

int main(int argc, char *argv[])
{
    rfmodel::logging::initializeLogging(argc, argv);

    QCoreApplication::setApplicationName(QStringLiteral("RF-Model"));
    QCoreApplication::setApplicationVersion(QStringLiteral(RFMODEL_VERSION));

    QApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription(QStringLiteral("RF-Model visualizes RF propagation scenarios."));
    parser.addHelpOption();

    const QCommandLineOption versionOption({QStringLiteral("v"), QStringLiteral("version")},
                                           QStringLiteral("Display version information and exit."));
    parser.addOption(versionOption);
    parser.process(app);

    if (parser.isSet(versionOption)) {
        QTextStream(stdout) << QCoreApplication::applicationName() << ' '
                            << QCoreApplication::applicationVersion() << Qt::endl;
        return 0;
    }

    LOG_UI_INFO() << "Starting RF-Model application";
    MainWindow w;
    w.show();
    return app.exec();
}
