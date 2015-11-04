#ifndef INCLUDES_H
#define INCLUDES_H

/* External headers */
//make your life easier
#include <string>
#include <cstring>
#include <vector>
//system
#include <ctime>
//multithreading
#include <thread>
#include <mutex>
#include <condition_variable>
//IO
#include <unistd.h>
#include <termios.h>
#include <fstream>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <memory>

/* Project headers */
/* Carefully with the include order */
#include "Macros.h"
#include "Logger.h"
#include "Globals.h"
#include "Prototypes.h"
#include "Serial.h"
#include "FileIn.h"

#endif
