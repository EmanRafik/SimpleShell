#include "Logger.h"
#include "fstream"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

Logger *Logger::instance = 0;

Logger::Logger()
{
    //ctor
}

Logger::~Logger()
{
    //dtor
}

Logger *Logger::getInstance()
{
    if (instance == 0)
        instance = new Logger();
    return instance;
}
void Logger::openFile(string path)
{
    Logger::file.open(path);
}

void Logger::close()
{
    Logger::file.flush();
    Logger::file.close();
}

void Logger::write(string info)
{
    time_t current = time(0);
    char* t = ctime(&current);
    stringstream ss;
    ss << t;
    string str = ss.str();
    str = str.substr(0,str.length()-2);
    file << str << " :" << info << endl;
}
