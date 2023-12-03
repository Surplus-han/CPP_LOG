#include <iostream>
#include "Logger/Logger.h"
using namespace hanjr::utility;
int main()
{
    Logger::getLoggerInstance()->open("D:\\Code\\CPP_LOG\\test.log");
    Logger::getLoggerInstance()->level(Logger::ERROR);
    Logger::getLoggerInstance()->set_max_size(1024);

    debug("hello word");
    debug("name is %s ,age is %d","hanjr",22);
    info("hello word");
    error("hello word");
    fatal("hello word");
    return 0;
}
