/*
 likai
 2016/11/2
 */
#include <string>
#include <vector>
using namespace std;
/*---------------------------data structures----------------------------*/
typedef struct action_op{
    char op;
    int num;
}ACTION;

class InputStrip{
public:
    vector<char> inputs;
    string str;
    int index;
    static int reserved_bits;
    InputStrip(string s);
    string get_current_string();
    
    char get_current_char();
};
/*----------------------------------------------------------------------*/

/*------------------------function prototypes--------------------------*/
void inputcfg(char* cfg_path);
void build_parsing_table(char* ppt_path);
void add_action(char* input);
void add_goto(char* input);

string print_operator_stack();
string print_state_stack();

/*----------------------------------------------------------------------*/

