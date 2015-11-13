#include "CommHandler.h"
#include <string>
#include <iostream>

CommHandler::CommHandler(std::string file,std::string device, int flag)
{
    _filename = file;
    _flag = flag;
    _device = device;
    //ctor
}

CommHandler::~CommHandler()
{
    //dtor
}

void CommHandler::testmethod()
{
    std::cout << "asdf" << std::endl;
}
