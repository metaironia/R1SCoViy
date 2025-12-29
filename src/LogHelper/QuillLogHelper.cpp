#include <cassert>

#include "QuillLogHelper.h"

#include "quill/Backend.h"
#include "quill/Frontend.h"
#include "quill/Logger.h"
#include "quill/sinks/FileSink.h"

quill::Logger* GlobalLogger = nullptr;

void SetupQuill(char const* LogFile) {

    assert(LogFile);

    quill::Backend::start();

    auto FileSink = quill::Frontend::create_or_get_sink<quill::FileSink>(
        LogFile,
        []() {

            quill::FileSinkConfig cfg;
            cfg.set_open_mode('w');
            cfg.set_filename_append_option(quill::FilenameAppendOption::StartDateTime);
            return cfg;
        }(),
        quill::FileEventNotifier{});

  GlobalLogger = quill::Frontend::create_or_get_logger(
        "Simulator.log", std::move(FileSink),
        quill::PatternFormatterOptions{"%(time) [%(thread_id)] %(short_source_location:<28) "
                                       "LOG_%(log_level:<9) %(logger:<12) %(message)",
                                       "%H:%M:%S.%Qns", quill::Timezone::GmtTime});
}