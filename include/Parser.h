#ifndef PARSER_H
#define PARSER_H
#include <string>
#include<vector>
using namespace std;

class Parser
{
    public:
        Parser();
        virtual ~Parser();
        bool isBackgroundProcess(string* input);
        bool isExit(string* input);
        vector<char*> splitInput(string* input);

    protected:

    private:
        string trim(string input);
};

#endif // PARSER_H
