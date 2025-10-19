#include "logging.h"

#include <QByteArray>
#include <QString>
#include <QStringList>
#include <QtGlobal>

#include <optional>

namespace rfmodel::logging {

Q_LOGGING_CATEGORY(uiCategory, "rfmodel.ui")
Q_LOGGING_CATEGORY(engineCategory, "rfmodel.engine")

namespace {

QtMsgType parseLevel(const QString &name)
{
    const QString normalized = name.trimmed().toLower();
    if (normalized == QLatin1String("debug")) {
        return QtDebugMsg;
    }
    if (normalized == QLatin1String("info")) {
        return QtInfoMsg;
    }
    if (normalized == QLatin1String("warning") || normalized == QLatin1String("warn")) {
        return QtWarningMsg;
    }
    if (normalized == QLatin1String("error") || normalized == QLatin1String("critical")) {
        return QtCriticalMsg;
    }
    return QtInfoMsg;
}

QStringList buildFilterRules(QtMsgType minimumLevel)
{
    const QStringList categories = {QStringLiteral("rfmodel.ui"), QStringLiteral("rfmodel.engine")};
    QStringList rules;
    const auto allow = [minimumLevel](QtMsgType level) {
        return minimumLevel <= level ? QStringLiteral("true") : QStringLiteral("false");
    };
    for (const auto &category : categories) {
        rules << QStringLiteral("%1.debug=%2").arg(category, allow(QtDebugMsg));
        rules << QStringLiteral("%1.info=%2").arg(category, allow(QtInfoMsg));
        rules << QStringLiteral("%1.warning=%2").arg(category, allow(QtWarningMsg));
        rules << QStringLiteral("%1.critical=%2").arg(category, allow(QtCriticalMsg));
    }
    return rules;
}

std::optional<QString> levelFromArguments(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i) {
        const QString arg = QString::fromLocal8Bit(argv[i]);
        const QString prefix = QStringLiteral("--log-level=");
        if (arg.startsWith(prefix)) {
            return arg.mid(prefix.size());
        }
        if (arg == QStringLiteral("--log-level")) {
            if (i + 1 < argc) {
                return QString::fromLocal8Bit(argv[i + 1]);
            }
            break;
        }
    }
    return std::nullopt;
}

std::optional<QString> levelFromEnvironment()
{
    const QByteArray value = qgetenv("RF_MODEL_LOG_LEVEL");
    if (!value.isEmpty()) {
        return QString::fromLocal8Bit(value);
    }
    return std::nullopt;
}

} // namespace

void initializeLogging(int argc, char *argv[])
{
    const auto envLevel = levelFromEnvironment();
    const auto cliLevel = levelFromArguments(argc, argv);
    const QString levelName = cliLevel.value_or(envLevel.value_or(QStringLiteral("info")));

    const QtMsgType level = parseLevel(levelName);
    QLoggingCategory::setFilterRules(buildFilterRules(level).join(QLatin1Char('\n')));
}

} // namespace rfmodel::logging

