//
// Created by 72829 on 2023/12/17.
//
#pragma
#ifndef CODE_LOGGER_H
#define CODE_LOGGER_H
#include <string>
#include <fstream>

namespace hanjr{
namespace utility{
#define debug(format,...) \
    Logger::getLoggerInstance()->log(Logger::DEBUG,__FILE__,__LINE__,format,##__VA_ARGS__);

#define info(format,...) \
    Logger::getLoggerInstance()->log(Logger::INFO,__FILE__,__LINE__,format,##__VA_ARGS__);

#define error(format,...) \
    Logger::getLoggerInstance()->log(Logger::ERROR,__FILE__,__LINE__,format,##__VA_ARGS__);

#define warn(format,...) \
    Logger::getLoggerInstance()->log(Logger::WARN,__FILE__,__LINE__,format,##__VA_ARGS__);

#define fatal(format,...) \
    Logger::getLoggerInstance()->log(Logger::FATAL,__FILE__,__LINE__,format,##__VA_ARGS__);

class Logger{
public:
    enum Level{
        DEBUG = 0,
        INFO,
        WARN,
        ERROR,
        FATAL,
        LEVEL_COUNT
    };
    static Logger * getLoggerInstance();
    void log(Level level,const char * file,int line,const char * format,...);
    void open(const std::string & fileName);
    void close();
    void level(Level level){
        m_level = level;
    }
    void set_max_size(int bytes){
        m_max = bytes;
    }

private:
    std::string m_filename;
    std::ofstream m_fout;
    static const char * s_level[LEVEL_COUNT];
    static Logger * m_instance;
    Level m_level;
    int m_max;
    int m_len;
    void rotate();
private:
    Logger();
    ~Logger();
};
}
}
#endif //CODE_LOGGER_H
