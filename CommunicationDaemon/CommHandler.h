#pragma once
#include <string>




class CommHandler
{
    public:
        CommHandler() {}

        CommHandler(std::string file,std::string device, ioFlags flag)
        {
            _filename = file;
            _flag = flag;
            _device = device;
            _working = 0;
            //ctor
        }



        ~CommHandler()
        {
            //dtor
        }
        bool isReader()
        {
            return _flag & ioFlags::read_f;
        }
        bool isWriter()
        {
            return _flag & ioFlags::write_f;
        }

        int fromFileToSerial(char* data)
        {
            if(_working)
            {
                return 1;
            }

            _working = true;
            FileIn fileIn;
            if(fileIn.Start(communicationFolder + _filename)!=0)
            {
                _working =false;
                return -1;
            }
            if(fileIn.ReadBytes(data,4)!=0)
            {
                _working =false;
                return -1;
            }
            if(fileIn.Finish()!=0)
            {
                _working =false;
                return -1;

            }

            _working = false;
            return 0;
        }


    private:
        ioFlags _flag;
        bool _working;

        std::string _filename;
        std::string _device;



};
