#ifndef LOGGER_H
#define LOGGER_H

#define LOG_ERROR 2
#define LOG_WARNING 1
#define LOG_MESSAGE 0

namespace ServerBasics {
	class Logger {
	public:
		Logger(std::string);
		Logger(const Logger&);
		~Logger();

		Logger& operator=(Logger&);
		int Log(std::string, int, std::string);
		void SetFileName(std::string);

		void Error(std::string, std::string);
		void Warning(std::string, std::string);
		void Message(std::string, std::string);

	private:
		std::string GetTimeString();

		std::string _fileName;

		bool _isAvailable;
		std::mutex _mutex;
		std::condition_variable _condition;
	};
}
#endif

