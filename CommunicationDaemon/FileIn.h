#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

class FileIn {
    public:
        FileIn();
        ~FileIn();
    private:
        bool _working;
        std::string _currentFile;
    public:
        std::string GetFile();

        int Start(std::string file);

        int ReadBytes(char* data);

        int Finish();
};

#endif
