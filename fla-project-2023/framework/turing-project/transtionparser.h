#include "utils.h"
#ifndef TRANSITION_PARSER_H
#define TRANSITION_PARSER_H


struct transition
{
    string old_state;
    string old_symbol_set;
    string new_symbol_set;
    string direction_set;
    string new_state;
}; // <旧状态> <旧符号组> <新符号组> <方向组> <新状态>

class TransitionParser {
private:
    vector<transition> delta;
    vector<string> Q;
    vector<char> G;
    int N;
    bool verbose;
    vector<string> splitString(const string& input);
    void validateAndCreateTransition(const vector<string>& result);
    void validateState(const string& state, const string& description);
    void validateSymbolSet(const string& symbolSet, const string& description);
    void validateDirectionSet(const string& directionSet);
    void handleError(const string& errorType, const string& errorMessage, const int exitCode);
    

public:
    TransitionParser(const vector<string>& Q, const vector<char>& G, int N, bool verbose)
        : Q(Q), G(G), N(N), verbose(verbose) {};
        
    void parseDelta(const string& input);

    vector<transition> getDelta(){
      return delta;
    };

};


#endif