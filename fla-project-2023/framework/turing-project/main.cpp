#include "turingmachine.h"
using namespace std;

//verbose the mode of TM
bool verbose = false;

int main(int argc, char* argv[]){
    //tm
    string file;
    //input for tm
    string input;

    //legal input
    if(argc>=1 && argc<=5 ){
        bool getfile=false;
        bool getinput=false;

        if(argc==1){
            //turing 
            cout<<help_tip<<endl;
        }else{

        for(int index=1;index<argc;index++){
                string arg=argv[index];
                if(arg[0]=='-'){
                    if(arg=="-h"||arg=="--help"){
                       cout<<help_tip<<endl;
                       exit(PRINT_HELP);
                    }
                    else if(arg=="-v"||arg=="--verbose"){
                        verbose=true;
                    }else{
                        cerr<<syntax_error_tip<<endl;
                        exit(ARG_ERROR);
                    }
                } else{
                    if(!getfile) {
                        file=arg;
                        getfile=true;
                    }
                    else if(!getinput) {
                        input=arg;
                        getinput=true;
                    }
                    else{
                         cerr<<syntax_error_tip<<endl;
                         exit(ARG_ERROR);
                    }
                }           
         }
         if(!getfile||!getinput){
            cerr<<syntax_error_tip<<endl;
            exit(ARG_ERROR);
         }
        }
    }else {
        cerr<<syntax_error_tip<<endl;
        exit(ARG_ERROR);
    }

    TuringMachine *tm=new TuringMachine(file,verbose);
    tm->runTuringMachine(input);
    //delete tm;
    return 0;
}