/*
 likai
 2016/11/2
 */
#include<iostream>
#include <string>
#include <fstream>

#include "lr.h"
using namespace std;

/*--------------------------global variables----------------------------*/

/* paths definition */
char* cfg_path="cfg.txt";
char* ppt_path="ppt.txt";

/*----------------------------------------------------------------------*/
int main() {
    inputcfg(cfg_path);
    cout<<"Input expression:"<<endl;
    string input;
    cin>>input;
    cout<<input<<endl;
    return 0;
}
