#include "Parser.h"
#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <stdlib.h>

using namespace std;

Parser::Parser()
{
    //ctor
}

Parser::~Parser()
{
    //dtor
}

bool Parser::isBackgroundProcess(string* input)
{
    string s = trim(*input);
    if (s.at(s.length()-1)=='#')
        return true;
    return false;
}

bool Parser::isExit(string*input)
{
    if(trim(*input)=="exit")
    {
        return true;
    }
    return false;
}

vector<char*> Parser::splitInput(string* input)
{
    vector<string> tokens;
    string token;
    istringstream str(*input);
    while (getline(str,token, ' '))
    {
        if (token != "#")
            tokens.push_back(token);
    }
    vector<char*> argVector(tokens.size()+1);
    size_t i = 0;
    for (i = 0; i < tokens.size(); i++)
    {
        argVector[i] = &tokens[i][0];
    }
    argVector[i] = NULL;
    //char** arg = &arg[0];
    return argVector;
}

string Parser::trim(string input)
{
    int counter = 0;
    int n = input.length();
    int i = n-1;
    while (input.at(i) == ' ')
    {
        counter++;
        i--;
    }
    input = input.substr(0, n-counter);
    counter = 0;
    i = 0;
    while (input.at(i) == ' ')
    {
        counter++;
        i++;
    }
    input = input.substr(0+counter);
    return input;
}
