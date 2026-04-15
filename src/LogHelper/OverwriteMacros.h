#ifndef SRC_LOGHELPER_OVERWRITE_MACROS_H
#define SRC_LOGHELPER_OVERWRITE_MACROS_H

#define QUILL_DISABLE_NON_PREFIXED_MACROS

#include "quill/LogMacros.h"
#include "quill/Logger.h"

extern quill::Logger* GlobalLogger;

#define LOG_TRACE_(Fmt, ...)    QUILL_LOG_TRACE(GlobalLogger, Fmt, ##__VA_ARGS__)
#define LOG_DEBUG_(Fmt, ...)    QUILL_LOG_DEBUG(GlobalLogger, Fmt, ##__VA_ARGS__)
#define LOG_INFO_(Fmt, ...)     QUILL_LOG_INFO(GlobalLogger, Fmt, ##__VA_ARGS__)
#define LOG_WARNING_(Fmt, ...)  QUILL_LOG_WARNING(GlobalLogger, Fmt, ##__VA_ARGS__)
#define LOG_ERROR_(Fmt, ...)    QUILL_LOG_ERROR(GlobalLogger, Fmt, ##__VA_ARGS__)
#define LOG_CRITICAL_(Fmt, ...) QUILL_LOG_CRITICAL(GlobalLogger, Fmt, ##__VA_ARGS__)

#endif