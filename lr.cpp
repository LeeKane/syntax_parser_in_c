/*
 likai
 2016/11/2
 */
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <cstring>
#include <stdlib.h>
#include <stack>
#include "lr.h"
using namespace std;

vector<string> productions;
stack<int> stateStack;
stack<char> operatorStack;
map<char, string>* actions[100];
map<char, int>* gotos[100];
int headIndex=0;
char InputStrip[100];
int inputLength=0;

void init()
{
    cout<<"Input a string:"<<endl;
    cin>>InputStrip;
    char* input=InputStrip;
    string sinput=string(input);
    inputLength=sinput.length();
    operator_stack.push('$');
    state_stack.push(0);
    startParser();
}

void inputcfg (char* cfg_path)
{
    ifstream cfgStream(cfg_path);
    while (!cfgStream.eof()) {
        char line[100];
        cfgStream>>line;
        if (line[0] != '\0') {
            productions.push_back(line);
        }
    }
}
//init ppt get action and goto for each state
void parsingTableInit(char* ppt_path)
{
    ifstream ppt(ppt_path);
    while (!ppt.eof())
    {
        char line[100];
        if (line[0] != '\0')
        {
            ppt>>line;
            char *outer_ptr=NULL;
            char *inner_ptr=NULL;
            char *delim = ":";
            char *p;
            char* state=strtok_r(line, delim,&outer_ptr);
//            printf("state=%s ", state);
            int stateNo=atoi(state);
            for(int i=0;p = strtok_r(NULL, delim,&outer_ptr);i++)
            {
                char* temp=p;
                if(i==1)//action
                {
                    map<char, string>* curAction = new map<char, string>();
                    actions[stateNo]=curAction;
                    char* symbol=strtok_r(temp,";",&inner_ptr);
                    char terminator=symbol[0];
                    string s=string(symbol);
                    s=s.substr(2,s.length()-1);
                    curAction->insert(pair<char, string>(terminator, s));
                    while(symbol= strtok_r(NULL,";",&inner_ptr))
                    {
                        terminator=symbol[0];
                        s=string(symbol);
                        s=s.substr(2,s.length()-1);
                        curAction->insert(pair<char, string>(terminator, s));
                    }

         
                }
                if(i==3)//goto
                {
                    map<char, int>* curGoto = new map<char, int>();
                    gotos[stateNo]=curGoto;
                    char* symbol=strtok_r(temp,";",&inner_ptr);
                    char nullTerminator=symbol[0];
                    string s=string(symbol);
                    s=s.substr(2,s.length()-1);
                    int nextState=atoi(s.c_str());
                    curGoto->insert(pair<char, int>(nullTerminator, nextState));
//                    printf("(%c,%d)",nullTerminator,nextState);
                    while(symbol= strtok_r(NULL,";",&inner_ptr))
                    {
                        nullTerminator=symbol[0];
                        s=string(symbol);
                        s=s.substr(2,s.length()-1);
                        nextState=atoi(s.c_str());
//                        printf("(%c,%d)",nullTerminator,nextState);
                        curGoto->insert(pair<char, int>(nullTerminator, nextState));
                    }
                }
            }
        }
    }
}

void startParser()
{

}
