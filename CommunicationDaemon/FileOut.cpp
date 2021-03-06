#include <fstream>
#include <string>
#include <cstring>

#include "FileOut.h"

FileOut::FileOut() {
}
FileOut::~FileOut() {
}

/*
* return: 0, if it exists. other, if there was an error.
*/
int FileOut::Start(std::string file){
    _currentFile = file + "_tmp";

    _fileStream.open(_currentFile.c_str(), std::fstream::in);

    if(_fileStream.good())
    {
        _fileStream.close();
        return 1;
    }
    _fileStream.close();
    _fileStream.open(_currentFile.c_str(), std::fstream::out);

    _working = true;
    return 0;
}

int FileOut::PutBytes(char* str){
    _fileStream.write(str, strlen(str));
    return 0;
}

/* Returns the file rename's result */
int FileOut::Finish(){
    _working = false;
    _fileStream.close();

    return rename(
        _currentFile.c_str(),
        _currentFile.substr(0, _currentFile.size() - 4).c_str()
    );
}








