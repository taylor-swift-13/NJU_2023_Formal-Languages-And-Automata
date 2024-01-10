#include "utils.h"
#include "transtionparser.h"
#ifndef TURING_MACHINE_H
#define TURING_MACHINE_H

using namespace std;


class TuringMachine{
 private: 
    vector<string> Q;        // 状态集 Q
    vector<char> S;          // 输入符号集 S
    vector<char> G;          // 纸带符号集 G
    string q0;               // 初始状态 q0
    char B;                  // 空格符号 B
    vector<string> F;        // 终结状态集 F
    int N;                   // 纸带数 N
    vector<transition> delta; // 转移函数 delta
    int step;                    // 步骤数
    string state;                // 当前状态
    string acc;                  
    vector<int> headIndex;
    vector<int> leftIndex;
    vector<int> rightIndex;
    vector<string> tape;
    TransitionParser * parser;


    void handle_Comment(string& line);
    void handle_Q(string line);
    void handle_S(string line);
    void handle_G(string line);
    void handle_F(string line);
    void handle_B(string line);
    void handle_q0(string line);
    void handle_N(string line);
    void handle_delta(string line);
    void handleError(const string& errorType, const string& errorMessage, const int exitCode);
    void printTapeInfo(int tapeIndex);
    void printSpaces(int n);
    void printInstantDescription();
    void moveHeadLeft(int tapeIndex);
    void moveHeadRight(int tapeIndex);
    void checkInputString(string input);
    void initializeTape(string input);
    int  symbolCompare(string a,string b);
    vector<string> splitString(const string input ,char delimiter);
    void run();


 public: 
    TuringMachine(string file,bool verbose);
    ~TuringMachine();   
    void runTuringMachine (string input);
     
};


#endif