#pragma once
#include <string>

/*
erroro code table:
0 - ok
1 - resource in use
-1 - serial port error
-2 - file I/O error
2 resource not ready yet
*/


class CommHandler
{
    public:
        CommHandler() {}

        CommHandler(std::string file,std::string device, ioFlags flag)
        {
            _filename = file;
            _device = device;
            _flag = flag;

            _working = 0;
            if(isF2S())
            {
                fileIn = new FileIn();
            }
            if (isS2F())
            {
                fileOut = new FileOut();
            }
            serial = new Serial();
            serial->SetDevice(_device.c_str());
            if(serial->OpenPort() != 0)
            {
                err = true;
            }
            else
            {
                err = false;
            }
            //ctor
        }



        ~CommHandler()
        {
            //dtor
            if (serial != 0)
            {
                serial->ClosePort();
            }

        }
        bool isS2F()
        {
            return _flag & ioFlags::read_f;
        }
        bool isF2S()
        {
            return _flag & ioFlags::write_f;
        }

        int fromFileToSerial()
        {
            if (err)
            {
                return -1;
            }
            if(_working)
            {
                return 1;
            }

            _working = true;
            if(fileIn->Start(communicationFolder + _filename) != 0)
            {
                _working = false;
                return 2;
            }

            char data[20];

            if(fileIn->ReadBytes(data,4) != 0)
            {
                _working = false;
                return -2;
            }

            if(serial->SendBytes(data,4) < 0)
            {
                _working = false;
                return -1;
            }
            serial->FlushOut();

            if(fileIn->Finish()!=0)
            {
                _working = false;
                return -2;

            }

            _working = false;
            return 0;
        }

        int fromSerialToFile()
        {


            if(err)
            {
                return -1;
            }
            if(_working)
            {
                return 1;
            }
            _working = true;

            int bytes = serial->BytesToRead();
            if(bytes)
            {
                char buffer[20];
                int readBytes = serial->RecvNBytes(buffer, 20, bytes);
                if(readBytes <= 0)
                {
                    _working = false;
                    return readBytes;
                }

                if(fileOut->Start(_filename) != 0)
                {
                    _working = false;
                    return -2;
                }

                fileOut->PutBytes(buffer);

                if(fileOut->Finish() != 0)
                {
                    _working = false;
                    return -2;
                }

            }
            return 0;
        }


    private:
        ioFlags _flag;
        bool _working;
        bool err;
        FileIn* fileIn;
        FileOut* fileOut;
        Serial* serial;

        std::string _filename;
        std::string _device;

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

};
