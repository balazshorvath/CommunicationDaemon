#include <string>
#include <fstream>

#include "FileIn.h"

FileIn::FileIn(){
}

FileIn::~FileIn(){
}

/*
* return: 0, if it exists. other, if there was an error.
*/
int FileIn::Start(std::string file){
    _currentFile = file;

    _fileStream.open(_currentFile.c_str(), std::ifstream::in);

    if(!_fileStream.good())
        return 1;

    _working = true;
    return 0;
}

int FileIn::ReadBytes(char* data, int nBytes){
    if(!_fileStream.is_open())
        return -1;

    _fileStream.read(data, nBytes);

    return 0;
}
/* Returns the file removal's result*/
int FileIn::Finish(){
    _working = false;
    _fileStream.close();
    return remove(_currentFile.c_str());
}

