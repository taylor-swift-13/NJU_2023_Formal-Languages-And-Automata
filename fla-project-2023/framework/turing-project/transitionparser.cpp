#include "transtionparser.h"
using namespace std;

void  TransitionParser:: parseDelta(const string& input) {
        // 解析输入字符串
        vector<string> result = splitString(input);
        // 验证并创建 Transition 对象
        validateAndCreateTransition(result);
    }
    // 分割字符串
    vector<string> TransitionParser::  splitString(const string& input) {
        vector<string> result;
        string strs = input + ' ';
        size_t pos = strs.find(' ');

        while (pos != strs.npos) {
            string temp = strs.substr(0, pos);
            result.push_back(temp);
            strs = strs.substr(pos + 1, strs.size());
            pos = strs.find(' ');
        }
        return result;

    }

    // 验证并创建 Transition 对象
    void  TransitionParser::  validateAndCreateTransition(const vector<string>& result) {
        transition new_transition;

        // 验证旧状态是否存在于 Q 中
        validateState(result[0], "Old state");

        // 设置旧状态
        new_transition.old_state = result[0];

        // 验证并设置旧符号集
        validateSymbolSet(result[1], "Old symbol");
        new_transition.old_symbol_set = result[1];

        // 验证并设置新符号集
        validateSymbolSet(result[2], "New symbol");
        new_transition.new_symbol_set = result[2];

        // 验证并设置方向集
        validateDirectionSet(result[3]);
        new_transition.direction_set = result[3];

        // 验证新状态是否存在于 Q 中
        validateState(result[4], "New state");
        new_transition.new_state = result[4];

        // 添加 Transition 对象到 delta 中
        delta.push_back(new_transition);
    }

    // 验证状态是否存在于 Q 中
    void   TransitionParser:: validateState(const string& state, const string& description) { 
        if (find(Q.begin(), Q.end(), state) == Q.end()) {
            handleError(syntax_error_tip, description + " " + state + " not exists in Q",CONSTRUCT_DELTA_ERROR);
        }
    }

    // 验证符号集
    void  TransitionParser:: validateSymbolSet(const string& symbolSet, const string& description) {
        if (symbolSet.size() != N) {
            handleError(syntax_error_tip, description + "'s length is not N",CONSTRUCT_DELTA_ERROR);
        }

        for (int i = 0; i < N; i++) {
            if (symbolSet[i] != '*' && std::find(G.begin(), G.end(), symbolSet[i]) == G.end()) {
                handleError(syntax_error_tip, description + " " + symbolSet[i] + " not exists in G",CONSTRUCT_DELTA_ERROR);
            }
        }
    }

    // 验证方向集
    void TransitionParser:: validateDirectionSet(const string& directionSet) {
        if (directionSet.size() != N ||
            count(directionSet.begin(), directionSet.end(), 'l') +
            count(directionSet.begin(), directionSet.end(), 'r') +
            count(directionSet.begin(), directionSet.end(), '*') != N) {
            handleError(syntax_error_tip, "Direction should be l or r or *'s string",CONSTRUCT_DELTA_ERROR);
        }
    }

    // 处理错误
    void TransitionParser:: handleError(const string& errorType, const string& errorMessage, const int exitCode) {
        cerr << errorType << endl;
        if (verbose) {
            cerr << errorMessage << endl;
        }
        //throw std::runtime_error("Error occurred");
        exit(exitCode);
    }