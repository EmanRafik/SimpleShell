#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include <fstream>

using namespace std;

class Logger
{
    public:
        static Logger *getInstance();
        virtual ~Logger();
        void openFile(string path);
        void close();
        void write(string info);

    protected:

    private:
        static Logger *instance;
        Logger();
        ofstream file;
};

#endif // LOGGER_H
