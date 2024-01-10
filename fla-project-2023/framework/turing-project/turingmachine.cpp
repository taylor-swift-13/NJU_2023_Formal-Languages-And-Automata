#include "turingmachine.h"
#include "transtionparser.h"
using namespace std;

vector<string> TuringMachine:: splitString(const string input, char delimiter) {
    vector<string> tokens;
    istringstream tokenStream(input);
    string token;

    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

 // 处理错误
 void TuringMachine:: handleError(const string& errorType, const string& errorMessage,const int exitCode) {
        cerr << errorType << endl;
        if (verbose) {
            cerr << errorMessage << endl;
        }
        exit(exitCode);
        //throw runtime_error("Error occurred");
}

void TuringMachine:: handle_Comment(string& line){
        // 查找第一个分号的位置
    size_t semicolonPos = line.find(';');

    // 如果找到了分号，则截取字符串到分号之前，并删除行尾空格
    if (semicolonPos != std::string::npos) {
        line = line.substr(0, semicolonPos);
        while (!line.empty() && line.back() == ' ') {
            line.pop_back();
        }
    }
        
    }
    void TuringMachine:: handle_S(string line){
        regex pattern("\\{([\\w,]+)\\}");
        smatch matches;

    if (regex_search(line, matches, pattern)) {
        std::string sString = matches[1];

        // 使用stringstream分割字符串
        stringstream ss(sString);
        string token;
       

        // 逐个读取逗号分隔的字符并存储到数组中
        while (getline(ss, token, ',')) {
            if (token.length() == 1) {
                S.push_back(token[0]);
            } else {
                handleError(syntax_error_tip,"invalid character in tm file.",CONSTRUCT_TURING_ERROR);
            }
        }

    };
      
    };
    void TuringMachine:: handle_G(string line){
         regex pattern("\\{([\\w,]+)\\}");
         smatch matches;

    if (regex_search(line, matches, pattern)) {
        std::string gString = matches[1];

        // 使用stringstream分割字符串
        stringstream ss(gString);
        string token;
       

        // 逐个读取逗号分隔的字符并存储到数组中
        while (getline(ss, token, ',')) {
            if (token.length() == 1) {
                G.push_back(token[0]);
            } else {
                 handleError(syntax_error_tip,"invalid character in tm file.",CONSTRUCT_TURING_ERROR);
            }
        }

    };
}


    void TuringMachine:: handle_Q(string line){
    regex pattern("\\{([^\\}]*)\\}");
    smatch matches;

    if (regex_search(line, matches, pattern)) {
        // 提取匹配的部分
        string qString = matches[1];

        // 使用stringstream分割字符串
        stringstream ss(qString);
        string token;

        // 逐个读取逗号分隔的状态并存储到vector Q中
        while (getline(ss, token, ',')) {
            Q.push_back(token);

        }

    }
};



    void TuringMachine:: handle_N(string line){
    size_t equalPos = line.find('=');
    if (equalPos != string::npos) {
        string value = line.substr(equalPos + 2);
        N=(char)value[0]-'0';

    };
    };

    void TuringMachine:: handle_q0(string line){
        size_t equalPos = line.find('=');
    if (equalPos != string::npos) {
        string value = line.substr(equalPos + 2);

        if(find(Q.begin(), Q.end(), value)!=Q.end()){
        q0=value;
        }else{
            handleError(syntax_error_tip,"state q0 not in Q.",CONSTRUCT_TURING_ERROR);
        }
        
       }
    };
    

    void TuringMachine:: handle_B (string line){
         size_t equalPos = line.find('=');
    if (equalPos != string::npos) {
        string value = line.substr(equalPos + 2);
        B=(char)value[0];
       }
    };

    void TuringMachine:: handle_F(string line){
         regex pattern("\\{([^\\}]*)\\}");
         smatch matches;

    if (regex_search(line, matches, pattern)) {
        // 提取匹配的部分
        string fString = matches[1];

        // 使用stringstream分割字符串
        stringstream ss(fString);
        string token;

        // 逐个读取逗号分隔的状态并存储到vector Q中
        while (getline(ss, token, ',')) {

        if(find(Q.begin(), Q.end(), token)!=Q.end()){
             F.push_back(token);
        }else{
            handleError(syntax_error_tip,"state f not in Q.",CONSTRUCT_TURING_ERROR);
        }
            
        }

    }
    };
    void TuringMachine:: handle_delta(string line){
        if(parser==nullptr) parser=new TransitionParser(Q,G,N,verbose);
        parser->parseDelta(line);
    };


   void TuringMachine:: printSpaces(int n){
       for(int i=0;i<n;i++){
       cout<<" ";
       }
   };

   void TuringMachine:: checkInputString(const string input) {
        for (int i = 0; i < input.size(); i++) {
            if (find(S.begin(), S.end(), input[i]) == S.end()) {

                 
                if (verbose) {
                    cerr << "Input: " << input << endl;
                    cerr << ERR << endl;
                    cerr << "error: "<< "Symbol \""<<input[i]<<"\" in input is not defined in the set of input symbols" << endl;
                    cerr << "Input: " << input << endl;
                    printSpaces(i + 7);
                    cerr << "^" << endl;
                    cerr << END << endl;
                }else{
                    cerr<<"illegal input string"<<endl;
                }

                exit(INPUT_ERROR);
            }
        }
    }
 void TuringMachine:: moveHeadLeft(int tapeIndex) {
        headIndex[tapeIndex]--;
        if (headIndex[tapeIndex] < leftIndex[tapeIndex]) {
            tape[tapeIndex][headIndex[tapeIndex]] = '_';
            leftIndex[tapeIndex] = headIndex[tapeIndex];
        }

        for (int j = rightIndex[tapeIndex] - 1; j > headIndex[tapeIndex]; j--) {
            if (tape[tapeIndex][j] == '_') {
                rightIndex[tapeIndex]--;
            } else {
                break;
            }
        }
    }

    void TuringMachine:: moveHeadRight(int tapeIndex) {
        headIndex[tapeIndex]++;
        if (headIndex[tapeIndex] >= rightIndex[tapeIndex]) {
            tape[tapeIndex][headIndex[tapeIndex]] = '_';
            rightIndex[tapeIndex] = headIndex[tapeIndex] + 1;
        }

        for (int j = leftIndex[tapeIndex]; j < headIndex[tapeIndex]; j++) {
            if (tape[tapeIndex][j] == '_') {
                leftIndex[tapeIndex]++;
            } else {
                break;
            }
        }
    }

 void TuringMachine:: run() {
        while (true) {

            if (verbose) {
                printInstantDescription();
            }

            string symbol;
            for (int i = 0; i < N; i++) {
                symbol.push_back(tape[i][headIndex[i]]);
            }

            transition currentTransition;
            int index = 0;
            for (; index < delta.size(); index++) {
                if (state == delta[index].old_state && symbolCompare(symbol, delta[index].old_symbol_set) == 0) {
                    currentTransition = delta[index];
                    break;
                }
            }
        
            if (index == delta.size()) {
                break; 
            }
            state = currentTransition.new_state;
            
            if (state.find("accept") != string::npos) {
                    acc = "Yes";
            }
            for (int i = 0; i < N; i++) {
                if (currentTransition.new_symbol_set[i] != '*') {
                    tape[i][headIndex[i]] = currentTransition.new_symbol_set[i];
                }

                if (currentTransition.direction_set[i] == 'l') {
                    moveHeadLeft(i);
                } else if (currentTransition.direction_set[i] == 'r') {
                    moveHeadRight(i);
                }
            }

            step++;
        }
    }

    void TuringMachine::  printTapeInfo(int tapeIndex) {
    // Print Index
    cout << "Index" << tapeIndex << " :";
    for (int j = leftIndex[tapeIndex]; j < rightIndex[tapeIndex]; j++) {
        cout << " " << abs(j);
    }
    cout << endl;

    // Print Tape
    cout << "Tape" << tapeIndex << "  :";
    for (int j = leftIndex[tapeIndex]; j < rightIndex[tapeIndex]; j++) {
        int cnt = to_string(abs(j)).length();
        cout << " " << tape[tapeIndex][j];
        printSpaces(cnt-1);
    }
    cout << endl;

    // Print Head
    cout << "Head" << tapeIndex << "  :";
    for (int j = leftIndex[tapeIndex]; j < rightIndex[tapeIndex]; j++) {
        int cnt = to_string(abs(j)).length();
        if (j == headIndex[tapeIndex]) {
            cout << " ^";
            printSpaces(cnt-1);
            break;
        }
        printSpaces(cnt+1);
    }
    cout << endl;
    
    }

    int TuringMachine:: symbolCompare(const string a, const string b) {
        assert(a.size() == b.size());

        for (int i = 0; i < a.size(); i++) {
            if (b[i] == '*') {
                if (a[i] == '_') {
                    return -1;
                }
            } else {
                if (a[i] != b[i]) {
                    return -1;
                }
            }
        }

        return 0;
    }

 void TuringMachine:: initializeTape(const string input) {
    if (!input.empty()) {
            tape[0].resize(200);
            copy(input.begin(), input.end(), tape[0].begin());
    } else{
            tape[0][0]=B;
    }
    rightIndex[0] = input.size();
    // 初始化其他纸带
    for (int i = 1; i < N; i++) {
        tape[i].resize(200);
        tape[i][0] = '_';
        rightIndex[i] = 1;
    }
};


 void TuringMachine:: printInstantDescription() {
        cout << "Step   : " << step << endl;
        cout << "State  : " << state << endl;
        cout << "Acc    : " << acc <<endl;

        for (int i = 0; i < N; i++) {
            printTapeInfo(i);
        }

        cout << "---------------------------------------------" <<endl;
    };





TuringMachine::~TuringMachine() {
    delete parser;  
}

 
TuringMachine::TuringMachine(string file,bool verbose){
    if (file == "")
    {  
        cerr << syntax_error_tip << endl;
        if (verbose){
            //cout<< "file is empty"<<endl;
            cerr<< "Please enter the TM's name" << endl;
            exit(FILE_READING_ERROR);
        }
    }
    ifstream input;
    
    // 拼接文件路径
   
    file="../programs/"+file;
    // 打开文件
    input.open(file);
    if (input.fail())
    {  
        cerr << syntax_error_tip << endl;
        if (verbose){
            cerr << "TM file not exists" << endl;
           exit(FILE_READING_ERROR);
        }
    }
    string line;
    while (getline(input, line))
    {
        handle_Comment(line);
        if (line != "" && line[0] != ';')
        {   
            if (line.substr(0,2)=="#Q")
            {
                handle_Q(line);
            }
            else if (line.substr(0,2)=="#S")
            {
                handle_S(line);
            }
            else if (line.substr(0,2)=="#G")
            {
                handle_G(line);
            }
            else if (line.substr(0,3)=="#q0")
            {
                handle_q0(line);
                
            }
            else if (line.substr(0,2)=="#B")
            {
                handle_B(line);
            }
            else if (line.substr(0,2)=="#F")
            {
                handle_F(line);
            }
            else if (line.substr(0,2)=="#N")
            {
                handle_N(line);
            }
            else if (splitString(line,' ').size() == 5)
            {   
                handle_delta(line);
            }
            else
            {
                handleError(syntax_error_tip,"TM file incorrect format",CONSTRUCT_TURING_ERROR);
            
            }
        }
    }
    input.close();

    step = 0;
    state = q0;
    acc="No";
    headIndex.resize(N);
    leftIndex.resize(N);
    rightIndex.resize(N);
    tape.resize(N);
    delta=parser->getDelta();
}



void TuringMachine::runTuringMachine(string input){
    
        checkInputString(input);
       
        if (verbose) {
            cout << "Input: " << input << endl;
            cout << RUN << endl;
        }


        initializeTape(input);
        run();

        
        string ifAcc;

        if(acc=="Yes"&& verbose) ifAcc=accepted_tip_verbose;
        else if(acc=="Yes"&& !verbose) ifAcc=accepted_tip;
        else if(verbose) ifAcc=unaccepted_tip_verbose;
        else ifAcc=unaccepted_tip;

        string result;
        for (int i = leftIndex[0]; i < rightIndex[0]; i++) {
            result.push_back(tape[0][i]);
        }

        if (verbose) {
            cout<<  ifAcc <<endl;
            cout << "Result: " << result << endl;
            cout << END << endl;
        } else {

            cout <<ifAcc<<" "<<result << endl;
        }

}










