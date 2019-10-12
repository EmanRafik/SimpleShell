#include "Shell.h"
#include <iostream>
#include <string>
#include <Parser.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <bits/stdc++.h>
#include <signal.h>
#include <Logger.h>
#include <unistd.h>

using namespace std;

//string input;

Shell::Shell()
{
    //ctor
}

Shell::~Shell()
{
    //dtor
}

void Shell::runShell()
{
    Logger *logger = Logger::getInstance();
    logger->openFile("/home/eman/Documents/OS/SimpleShell/logger.txt");
    logger->write("Shell started running");
    interface();
    string input;
    cout << "Shell > ";
    getline(cin, input);
    cout << endl;
    while (1)
    {
        Parser p;
        if (p.isExit(&input))
        {
            logger->close();
            exit(1);
        }
        vector<char*> argv = p.splitInput(&input);
        signal(SIGCHLD, handler);
        if (p.isBackgroundProcess(&input))
        {
            executeInBackground(argv);
        }
        else
        {
            executeCommand(argv);
        }
        cout << "Shell > ";
        getline(cin, input);
        cout << endl;
    }
}

void Shell::executeCommand(vector<char*> a)
{
    if (strcmp(a[0], "cd") == 0)
    {
        char** argv = &a[1];
        int status = handle_cd(argv[0]);
        /**error changing directory**/
        if (status < 0)
        {
            Logger *logger = Logger::getInstance();
            logger->write("Error changing directory");
        }
        else
        {
            return;
        }
    }
    char** argv = &a[0];
    pid_t childPid = fork();

    /**Error creating child process**/
    if (childPid < 0)
    {
        Logger *logger = Logger::getInstance();
        logger->write("Error creating child process");
    }
    /**child process running**/
    else if (childPid == 0)
    {
        int status = execvp(argv[0],argv);
        /**Error executing child process**/
        if (status < 0)
        {
            Logger *logger = Logger::getInstance();
            logger->write("Error executing process");
        }
    }
    /**parent process running**/
    else
    {
        int status;
        wait(&status);
    }
}

void Shell::executeInBackground(vector<char*> a)
{
    char** argv = &a[0];
    pid_t childPid = fork();

    /**Error creating child process**/
    if (childPid < 0)
    {
        Logger *logger = Logger::getInstance();
        logger->write("Error creating child process");
    }
    /**child process running**/
    else if (childPid == 0)
    {
        int status = execvp(argv[0],argv);
        signal(SIGCHLD, handler);
        /**Error executing child process**/
        if (status < 0)
        {
            Logger *logger = Logger::getInstance();
            logger->write("Error executing process");
        }
        else
        {
            signal(SIGCHLD, handler);
        }
    }
}

void Shell::handler(int s)
{
    Logger *logger = Logger::getInstance();
    logger->write("Child process terminated");
}
void Shell::interface()
{
    //cout << getenv("HOME") << ":";
}

int Shell::handle_cd(char* path)
{
    return chdir(path);
}
