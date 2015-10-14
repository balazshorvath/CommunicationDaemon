#include "Includes.h"


/*Parameters
* 1. required   path to the folder to make and modify in/out files
* 2. required   serial device to read and write
* 3. optional   path to the log file, default: /var/log/commdae/commdae.log
*/
int main(int argc, char* argv[]){
    if(validateInput(argc, argv) != 0)
        return 1;

    initializeProgram(argc, argv);

    std::thread fromSerial(inputThread);
    std::thread toSerial(outputThread);

    fromSerial.join();
    toSerial.join();

    return 0;
}

void initializeProgram(int argc, char** argv){
    /* setup globals */
    communicationFolder = std::string(argv[1]);
    device = std::string(argv[2]);

    if(argc > 3)
        logger.SetFileName(std::string(argv[3]));
}
int validateInput(int argc, char** argv){
    if(argc < 3){
        logger.Error("Wrong arguments.", "Validation");
        return 1;
    }
    return 0;
}


void inputThread(){

}

void outputThread(){

}

