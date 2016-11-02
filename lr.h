/*
 likai
 2016/11/2
 */
#include <string>
#include <vector>
using namespace std;

void inputcfg(char* cfg_path);
void parsingTableInit(char* ppt_path);
void setAction(int stateNo,char*temp);
void setGoto(int stateNo,char*temp);
void init();
void startParser();
string print_operator_stack();
string print_state_stack();




