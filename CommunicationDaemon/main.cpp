#include "Includes.h"


using namespace ServerBasics;


/*Parameters
* 1. required   path to the folder to make and modify in/out files
* 2. optional   path to the log file, default: /var/log/commdae/commdae.log
*/
int main(int argc, char* argv[]){
    if(validateInput(argc, argv) != 0)
        return 1;

    initializeProgram(argc, argv);
    return 0;
}

void initializeProgram(int argc, char** argv){


}
int validateInput(int argc, char** argv){
    if(argc < 2){
        logger.Error("Wrong arguments.", "INPVAL");
        return 1;
    }
    return 0;
}


