#pragma once

#include <QLoggingCategory>

namespace rfmodel::logging {

Q_DECLARE_LOGGING_CATEGORY(uiCategory)
Q_DECLARE_LOGGING_CATEGORY(engineCategory)

void initializeLogging(int argc, char *argv[]);

#define LOG_UI_DEBUG() qCDebug(::rfmodel::logging::uiCategory())
#define LOG_UI_INFO() qCInfo(::rfmodel::logging::uiCategory())
#define LOG_UI_WARNING() qCWarning(::rfmodel::logging::uiCategory())
#define LOG_UI_ERROR() qCCritical(::rfmodel::logging::uiCategory())

#define LOG_ENGINE_DEBUG() qCDebug(::rfmodel::logging::engineCategory())
#define LOG_ENGINE_INFO() qCInfo(::rfmodel::logging::engineCategory())
#define LOG_ENGINE_WARNING() qCWarning(::rfmodel::logging::engineCategory())
#define LOG_ENGINE_ERROR() qCCritical(::rfmodel::logging::engineCategory())

} // namespace rfmodel::logging

