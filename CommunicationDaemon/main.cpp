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


/*
* out size can be calculated easily...
* 2 * inSize + 1
*/
void toHex(char* in, char* outStr, int inSize){
    for(int i = 0; i < inSize; i++){
        //1 byte = 2 byte in hex -> offset is i * 2
        sprintf((outStr + 2 * i), "%02X", in[i]);
    }
}
/*
* input is a string, dont need sizes
* ret -1 if the hex string is invalid 0 everythings fine
*/
int fromHex(char* inStr, char* out){
    int counter = 1;

    while(*inStr){
        switch(*inStr){
            case '0': break;
            case '1': *(out) |= (counter % 2) ? 0x10 : 0x01; break;
            case '2': *(out) |= (counter % 2) ? 0x20 : 0x02; break;
            case '3': *(out) |= (counter % 2) ? 0x30 : 0x03; break;
            case '4': *(out) |= (counter % 2) ? 0x40 : 0x04; break;
            case '5': *(out) |= (counter % 2) ? 0x50 : 0x05; break;
            case '6': *(out) |= (counter % 2) ? 0x60 : 0x06; break;
            case '7': *(out) |= (counter % 2) ? 0x70 : 0x07; break;
            case '8': *(out) |= (counter % 2) ? 0x80 : 0x08; break;
            case '9': *(out) |= (counter % 2) ? 0x90 : 0x09; break;
            case 'A': *(out) |= (counter % 2) ? 0xA0 : 0x0A; break;
            case 'B': *(out) |= (counter % 2) ? 0xB0 : 0x0B; break;
            case 'C': *(out) |= (counter % 2) ? 0xC0 : 0x0C; break;
            case 'D': *(out) |= (counter % 2) ? 0xD0 : 0x0D; break;
            case 'E': *(out) |= (counter % 2) ? 0xE0 : 0x0E; break;
            case 'F': *(out) |= (counter % 2) ? 0xF0 : 0x0F; break;
            default: return -1;
        }
        if(!(++counter % 2))
            out++;
    }
    return 0;
}















