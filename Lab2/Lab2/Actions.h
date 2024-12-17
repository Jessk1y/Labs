#ifndef ACTIONS_H
#define ACTIONS_H

#include <vector>
#include "Pipe.h"
#include "CompressorStation.h"

void addPipe(std::vector<Pipe>& pipes);
void addCompressorStation(std::vector<CompressorStation>& compressorStations);
void viewAllObjects(const std::vector<Pipe>& pipes, const std::vector<CompressorStation>& compressorStations);
void editPipe(std::vector<Pipe>& pipes);
void editCompressorStation(std::vector<CompressorStation>& compressorStations);
void saveDataToFile(const std::vector<Pipe>& pipes, const std::vector<CompressorStation>& compressorStations);
void loadDataFromFile(std::vector<Pipe>& pipes, std::vector<CompressorStation>& compressorStations);
void searchPipes(const std::vector<Pipe>& pipes);
void searchCompressorStations(const std::vector<CompressorStation>& compressorStations);
void batchEditPipes(std::vector<Pipe>& pipes);

#endif // ACTIONS_H