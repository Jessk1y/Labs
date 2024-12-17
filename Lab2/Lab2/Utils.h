#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include "Pipe.h"
#include "CompressorStation.h"

int safeIntInput(const std::string& prompt);
double safeDoubleInput(const std::string& prompt);
std::string safeStringInput(const std::string& prompt);

void saveData(const std::string& filename, const std::vector<Pipe>& pipes, const std::vector<CompressorStation>& compressorStations);
void loadData(const std::string& filename, std::vector<Pipe>& pipes, std::vector<CompressorStation>& compressorStations);

#endif // UTILS_H
