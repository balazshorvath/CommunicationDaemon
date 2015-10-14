#include <string>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include <ctime>
#include "Logger.h"


ServerBasics::Logger::Logger(std::string fileName) {
	_fileName = fileName;
}
ServerBasics::Logger::Logger(const Logger& asd) {}

ServerBasics::Logger::~Logger() {
}
int ServerBasics::Logger::Log(std::string msg, int level, std::string from = "") {

	std::unique_lock<std::mutex> lock(this->_mutex);
	std::ofstream logFile(this->_fileName, std::ios::app);

	if(!logFile.is_open()) return 1;

	std::string time = this->GetTimeString();
	std::string logLevel;
	std::string msgFrom;

	if(!from.empty()) {
		msgFrom = "[";
		msgFrom.append(from);
		msgFrom.append("]");
	}

	switch(level) {
	case LOG_ERROR:
		logLevel = "Error";
			break;
		case LOG_WARNING:
			logLevel = "Warning";
			break;
		case LOG_MESSAGE:
			logLevel = "Message";
			break;
	}
	logFile << "[" << time << "]" << "["<< logLevel << "] " << msgFrom << msg << std::endl;

	logFile.close();
	return 0;
}
void ServerBasics::Logger::Error(std::string text, std::string from = ""){
    Log(text, LOG_ERROR, from);
}
void ServerBasics::Logger::Warning(std::string text, std::string from = ""){
    Log(text, LOG_WARNING, from);
}
void ServerBasics::Logger::Message(std::string text, std::string from = ""){
    Log(text, LOG_MESSAGE, from);
}


std::string ServerBasics::Logger::GetTimeString() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

void ServerBasics::Logger::SetFileName(std::string file) {
	_fileName = file;
}

