/*
 likai
 2016/11/2
 */
#include <fstream>
#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <cstring>
#include <stdlib.h>

#include "lr.h"
using namespace std;

vector<string> productions;
stack<int> stateStack;
stack<char> operatorStack;
map<char, string>* actions[100];
map<char, int>* gotos[100];
string operationOutput="";
int headIndex=0;
char inputstirng[100];
int inputLength=0;

void init()
{
    cout<<"Input a string:"<<endl;
    cin>>inputstirng;
    char* input=inputstirng;
    string sinput=string(input);
    inputLength=sinput.length();
    operatorStack.push('$');
    stateStack.push(0);
    printResult();//init state
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
    for(headIndex=0;headIndex<inputLength; headIndex++)
    {
        if (stateStack.empty() || operatorStack.empty())
        {
            cout << "error,the parse stack is empty" << endl;
            return;
        }
        int currentStateNo = stateStack.top();
        char currentHeadChar = inputstirng[headIndex];
//        cout<<currentHeadChar<<endl;
//        cout<<currentStateNo<<endl;
        map<char, string>* curAction = actions[currentStateNo];
        if(curAction->find(currentHeadChar)->first!=NULL)
        {
            string operation=curAction->find(currentHeadChar)->second;
//            cout<<operation<<endl;
            if(operation[0]=='s')
            {
                const char* currentState=(operation.substr(1,operation.length()-1)).c_str();
                currentStateNo=atoi(currentState);
                stateStack.push(currentStateNo);
                operatorStack.push(currentHeadChar);
                operationOutput="shfit";
            }
            else if(operation[0]=='r')
            {
                const char* currentProduction=(operation.substr(1,operation.length()-1)).c_str();
                int currentProductionNo=atoi(currentProduction);
                if(currentProductionNo==0)
                {
                    cout<<"finish"<<endl;
                    break;
                }
                operationOutput=operation;
                dealR(currentProductionNo);
            }
            else
            {
                cout<<"error,the ppt is not valid"<<endl;
            }
        }
        else
        {
             cout << "error,the input's headChar is not find in ppt" << endl;
        }
        printResult();
    }
    while (!operatorStack.empty()) {
        int currentStateNo = stateStack.top();
        char currentHeadChar = '$';
//        cout<<currentHeadChar<<endl;
//        cout<<currentStateNo<<endl;
        map<char, string>* curAction = actions[currentStateNo];
        string operation=curAction->find(currentHeadChar)->second;
//        cout<<operation<<endl;
        const char* currentProduction=(operation.substr(1,operation.length()-1)).c_str();
        int currentProductionNo=atoi(currentProduction);
        if(currentProductionNo==0)
        {
            cout<<"finish"<<endl;
            break;
        }
        dealR(currentProductionNo);
    }
}

void dealR(int currentProductionNo)
{
    string production=productions[currentProductionNo];
    string right=production.substr(1,production.length()-1);
    //from stack bottom to top
    for(int i=right.length()-1;i>=0;i--)
    {
        if(operatorStack.top()==right[i])
        {
            operatorStack.pop();
            stateStack.pop();
        }
    }
    operatorStack.push(production[0]);
    int currentStateNo=stateStack.top();
//    cout<<currentStateNo<<endl;
    map<char, int>* currentGoto = gotos[currentStateNo];
    if (currentGoto->find(production[0])->first != NULL) {
        int nextStateNo = currentGoto->find(production[0])->second;
//        cout<<nextStateNo<<endl;
        stateStack.push(nextStateNo);
    }
    else
    {
        cout<<"error, in dealR case the goto is wrong"<<endl;
    }
    headIndex--;
}

void printResult()
{
    string ss = "";
    stack<int> tempState = stateStack;
    while (!tempState.empty()) {
        int stateNo = tempState.top();
        tempState.pop();
        ss += ('0'+stateNo);
        ss += " ";
    }
    printf("stateStack:   %s\n",ss.c_str());
    
     string s = "";
    stack<char> tempOpeator=operatorStack;
    while (!tempOpeator.empty()) {
        char op=tempOpeator.top();
        tempOpeator.pop();
        s+=op;
        s+=" ";
    }
    
    printf("operatorStack:%s\n",s.c_str());
    
    char* inputs=inputstirng;
    string sinput=string(inputs);
    string input=sinput.substr(headIndex+1,inputLength-1);
    printf("input:        %s\n",input.c_str());
    
    printf("action:       %s\n",operationOutput.c_str());
    printf("\n");
}