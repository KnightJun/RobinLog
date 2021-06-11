#pragma once
#include "spdlog/spdlog.h"
#include <QRect>
#include <QString>
#include <QImage>
#include <QUrl>
#ifdef QT_NETWORK_LIB
#include <QSslError>
#endif
#include <spdlog/fmt/ostr.h> // must be included
#include "spdlog/sinks/rotating_file_sink.h"
#include <QDebug>
#include <iostream>
#define LOG_DBG(fmt,    ...)      get_global_logger()->debug(fmt,  __VA_ARGS__)
#define LOG_INFO(fmt,   ...)      get_global_logger()->info(fmt,   __VA_ARGS__)
#define LOG_WARN(fmt,   ...)      get_global_logger()->warn(fmt,   __VA_ARGS__)
#define LOG_ERR(fmt,    ...)      get_global_logger()->error(fmt,  __VA_ARGS__)

#ifndef BUILD_STATIC
# if defined(ROBINLOG_LIB)
#  define ROBINLOG_EXPORT Q_DECL_EXPORT
# else
#  define ROBINLOG_EXPORT Q_DECL_IMPORT
# endif
#else
# define ROBINLOG_EXPORT
#endif

template<typename OStream>
OStream &operator<<(OStream &os, const QRect &c)
{
    return os << "QRect(" 
        << c.x() << "," << c.y()  
        << " " << c.width() << "x" << c.height() << ")";
}

template<typename OStream>
OStream &operator<<(OStream &os, const QString &c)
{   
    return os << c.toLocal8Bit().constData();
}

template<typename OStream>
OStream &operator<<(OStream &os, const QByteArray &c)
{   
    return os << (QString)c;
}

template<typename OStream>
OStream &operator<<(OStream &os, const QImage &c)
{
    return os << "QImage(" << c.width() << "x" << c.height() << ", " << c.bytesPerLine() / c.width() << " channels)";
}

template<typename OStream>
OStream &operator<<(OStream &os, const QUrl &c)
{
    return os << c.toString();
}

#ifdef QT_NETWORK_LIB
template<typename OStream>
OStream &operator<<(OStream &os, const QSslError &c)
{
    return os << c.errorString();
}
#endif
template<typename OStream, typename L>
OStream &operator<<(OStream &os, const QList<L> &c)
{
    for (const L &member : c)
    {
        os << member;
    }
    return os;
}

ROBINLOG_EXPORT std::shared_ptr<spdlog::logger> get_global_logger();
ROBINLOG_EXPORT void set_rotating_log(const char * logFile,
int maxSize = 1048576 * 1, int maxFiles = 2);

static void QtLogOutputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString text;
    switch(type)
    {
    case QtDebugMsg:
        LOG_DBG("Qt: {}", msg);
        break;
    case QtWarningMsg:
        LOG_WARN("Qt: {}", msg);
        break;
    case QtInfoMsg:
        LOG_INFO("Qt: {}", msg);
        break;
    case QtFatalMsg:
    case QtCriticalMsg:
        LOG_ERR("Qt: {}", msg);
        break;
    }
}

static void InstallQtLogToRobin(){
    qInstallMessageHandler(QtLogOutputMessage);
}
