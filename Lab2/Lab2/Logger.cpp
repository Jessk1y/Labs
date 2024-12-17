#include "Logger.h"
#include <iostream>
#include <fstream>
#include <ctime>

void Logger::log(const std::string& message) {
    std::string logFileName = "log.txt";
    std::ofstream logFile(logFileName, std::ios::app);
    if (!logFile.is_open()) {
        std::ofstream createLogFile(logFileName);
        createLogFile.close();
        logFile.open(logFileName, std::ios::app);
    }

    if (logFile.is_open()) {
        time_t now = time(0);
        char dt[26];
        ctime_s(dt, sizeof dt, &now);
        logFile << dt << " - " << message << std::endl;
        logFile.close();
    }
    else {
        std::cerr << "Unable to open log file!" << std::endl;
    }
}