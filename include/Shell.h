#ifndef SHELL_H
#define SHELL_H
#include <string>
#include <vector>
#include <Logger.h>

using namespace std;

class Shell
{
    public:
        Shell();
        virtual ~Shell();
        void runShell();

    protected:

    private:
        void executeCommand(vector<char*> argv);
        void executeInBackground(vector<char*> argv);
        static void handler(int s);
        void interface();
        int handle_cd(char* path);
};

#endif // SHELL_H
