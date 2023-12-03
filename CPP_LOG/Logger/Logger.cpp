//
// Created by 72829 on 2023/12/17.
//

#include "Logger.h"
#include <time.h>
#include <string.h>
#include <stdexcept>
#include <iostream>
#include <stdarg.h>
using  namespace hanjr::utility;

const char * Logger::s_level[LEVEL_COUNT] = {
        "DEBUG",
        "INFO",
        "WARN",
        "ERROR",
        "FATAL"
};
Logger * Logger::m_instance = nullptr;

Logger::Logger():m_level(DEBUG)
,m_max(0)
,m_len(0)
{

}
Logger::~Logger(){

}

Logger * Logger::getLoggerInstance() {
    if(m_instance == nullptr){
        m_instance = new Logger();
    }
    return m_instance;
}
void Logger::open(const std::string &fileName) {
    m_filename = fileName;
    m_fout.open(fileName,std::ios::app);
    if(m_fout.fail()) {
        throw std::logic_error("open file failed " + m_filename);
    }
    m_fout.seekp(0,std::ios::end);
    m_len = m_fout.tellp();

}
void Logger::close() {
    m_fout.close();
}

void Logger::log(Level level, const char *file, int line, const char *format, ...) {
    if(m_level > level){
        return;// 根据日志等级打印日志
    }

    if(m_fout.fail()){
        throw std::logic_error("open file failed " + m_filename);
    }
    time_t m_ticks = time(NULL);
    struct tm * ptn = localtime(&m_ticks);
    char timestamp[32];
    memset(timestamp,0,sizeof(timestamp));
    strftime(timestamp,sizeof(timestamp),"%Y-%m-%d %H:%M:%S",ptn);

    const char * ftm = "%s %s %s:%d ";
    int size = snprintf(NULL,0,ftm, timestamp,s_level[level],file,line);
    if(size > 0){
        char * buffer = new char[size + 1];
        snprintf(buffer,size+1,ftm, timestamp,s_level[level],file,line);
        buffer[size] = 0;
        std::cout << buffer << std::endl;
        m_fout << buffer;// 写入文件
        m_len+=size; // 加入当前日志的长度
        delete buffer;
    }
    va_list arg_ptr;//存可变参数
    va_start(arg_ptr,format);
    size = vsnprintf(NULL,0,format,arg_ptr);
    va_end(arg_ptr);
    if(size > 0){
        char * content = new char[size+1];
        va_start(arg_ptr,format);
        vsnprintf(content,size+1,format,arg_ptr);
        va_end(arg_ptr);
        std::cout << content << std::endl;
        m_fout << content;
        m_len+=size;
        delete content;
    }
    m_fout << "\n";
    m_fout.flush();

    if(m_len >= m_max && m_max >= 0){
        // 日志翻滚
        rotate();
    }

}
void Logger::rotate() {
    close();
    time_t ticks = time(NULL);
    struct  tm* ptm = localtime(&ticks);
    char timestamp[32];
    memset(timestamp,0,sizeof(timestamp));
    strftime(timestamp,sizeof(timestamp),"%Y-%m-%d %H:%M:%S",ptm);
    std::string filename = m_filename + timestamp;
    if(rename(m_filename.c_str(),filename.c_str()) != 0){
        throw std::logic_error("rename log file failed: " + std::string(strerror(errno)));
    }
    open(m_filename);//打开新的 文件
}