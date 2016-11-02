/*
 likai
 2016/11/2
 */
#include<iostream>
#include <string>
#include <fstream>

#include "lr.h"
using namespace std;

int main() {
    inputcfg("cfg.txt");
    parsingTableInit("ppt.txt");
    init();
    return 0;
}
