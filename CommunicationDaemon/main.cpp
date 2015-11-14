#include "Includes.h"

std::vector<CommHandler*> cHandlers;
std::vector<Serial> ports;
int currentHandler = 0;
int initData();
std::vector<std::string> split(std::string str, char delimiter);
void increment(int*);
/*Parameters
* 1. required   path to the folder to make and modify in/out files
* 2. required   serial device to read and write
* 3. optional   path to the log file, default: /var/log/commdae/commdae.log
*/
int main(int argc, char* argv[]){
    /*if(validateInput(argc, argv) != 0) //we keep this for later use, but curretnly we would need about 15 params or more which i refuse to do
        return 1;*/

    //initializeProgram(argc, argv); // same as above

    if(initData())
    {
        return 1;
    }



    //current init
    communicationFolder="/media/ramdisk/";
    //cHandlers.push_back(new CommHandler("asd", "/dev/ttyS1", ioFlags::readwrite_f));
    //ports.push(Serial("/dev/ttyS0",0,0));
    //cHandlers.push_back(new CommHandler("c", "/dev/ttyS1", ioFlags::read_f));
    //ports.push(Serial("/dev/ttyS1",0,0));


    running = 1;

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
    int i = 0;
    int timeout = 20;
    CommHandler* ch;
    while (running)
    {
        if(timeout != 20)
        timeout = 20;

        int result;
        ch = cHandlers[i];

        if (ch->isS2F())
        {
            result = ch->fromSerialToFile();
            switch (result)
            {
                case 0: increment(&i); break; //everything is ok
                case 1: timeout = 5; break; //other thread working, try again a bit later
                case 2: increment(&i); break; //file still there
                case -1: logger.Error("Unable to open serial port.","Serial I/O"); increment(&i); break;
                case -2: logger.Error("Unable to open file.","File I/O"); increment(&i); break;
            }

        }

        std::this_thread::sleep_for (std::chrono::milliseconds(timeout));
    }
}

void outputThread(){
    int i = 0;
    int timeout = 20;
    CommHandler* ch;
    while (running)
    {
        if(timeout != 20)
        timeout = 20;

        int result;
        ch = cHandlers[i];

        if (ch->isF2S())
        {
            result = ch->fromFileToSerial();
            switch (result)
            {
                case 0: increment(&i); break; //everything is ok
                case 1: timeout = 5; break; //other thread working, try again a bit later
                case 2: increment(&i); break; //file not existing yet
                case -1: logger.Error("Unable to open serial port.","Serial I/O"); increment(&i); break;
                case -2: logger.Error("Unable to open file.","File I/O"); increment(&i); break;
            }

        }
        std::this_thread::sleep_for (std::chrono::milliseconds(timeout));
    }
}

int initData(){
    std::ifstream ins;

    ins.open("/media/config", std::ifstream::in);
    if (ins.good() == 0)
    {
        return 1;
    }

    std::vector<std::string> values;
    std::string data;
    int flag;

    while(ins.peek() != EOF)
    {
        std::getline(ins, data);
        values = split(data,';');
        std::istringstream(values[2]) >> flag;
        cHandlers.push_back(new CommHandler(values[0],values[1],ioFlags(flag)));
        portCount++;
    }


    return 0;
}

std::vector<std::string> split(std::string str, char delimiter) {
  std::vector<std::string> internal;
  std::stringstream ss(str); // Turn the string into a stream.
  std::string tok;

  while(getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }

  return internal;
}

void increment(int* i)
{
    if(*i < portCount - 1)
    {
        *i++;
    }
    else
    {
        *i=0;
    }

}















