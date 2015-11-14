#ifndef GLOBALS_H
#define GLOBALS_H

/* ! The file requres Macros.h, Logger.h */
/* ! Be aware of include order */
ServerBasics::Logger logger(DEFAULT_LOG_FILE);
std::string device = "";
std::string communicationFolder = "";

//constants
const std::string TMP = "_tmp";
int running = 1;
int portCount = 0;
typedef enum _ioFlags {read_f = 1, write_f = 2, readwrite_f = 3 } ioFlags;

#endif
