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