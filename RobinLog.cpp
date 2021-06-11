#include "spdlog/spdlog.h"
#include <QObject>
#include <spdlog/fmt/ostr.h> // must be included
#include "spdlog/sinks/rotating_file_sink.h"
using namespace spdlog;
std::shared_ptr<spdlog::logger> g_logger;
bool g_logger_isinit = false;
#define LogName  "RobinLog"
Q_DECL_EXPORT std::shared_ptr<spdlog::logger> get_global_logger()
{
    if(g_logger_isinit){
        return g_logger;
    }else{
        return spdlog::default_logger();
    }
}

Q_DECL_EXPORT void set_rotating_log(const char * logFile,
int maxSize, int maxFiles)
{
    // Create a file rotating logger with 5mb size max and 3 rotated files
    g_logger = spdlog::rotating_logger_mt(LogName, logFile, maxSize, maxFiles);
    g_logger_isinit = true;
}