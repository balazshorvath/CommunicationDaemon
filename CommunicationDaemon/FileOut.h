#ifndef FILE_OUT_H
#define FILE_OUT_H

class FileOut {
    public:
        FileOut();
        ~FileOut();
    private:
        bool _working;
        std::string _currentFile;
        std::ofstream _fileStream;
    public:
        /*
        * return: 0, if it exists. other, if there was an error.
        */
        int Start(std::string file);
        int PutBytes(char* str);

        /* Returns the file rename's result */
        int Finish();
};

#endif

