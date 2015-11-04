#ifndef FILE_IN_H
#define FILE_IN_H

class FileIn {
    public:
        FileIn();
        ~FileIn();
    private:
        bool _working;
        std::string _currentFile;
        std::ifstream _fileStream;
    public:
        /*
        * return: 0, if it exists. other, if there was an error.
        */
        int Start(std::string file);
        /* -1 if the file isn't open, 0 else */
        int ReadBytes(char* data, int nBytes);

        /* Returns the file removal's result*/
        int Finish();
};

#endif
