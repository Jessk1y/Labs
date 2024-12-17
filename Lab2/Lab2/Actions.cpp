#include "Actions.h"
#include "Utils.h"
#include "Logger.h"
#include <iostream>

using namespace std;

void addPipe(vector<Pipe>& pipes) {
    Pipe pipe;
    pipe.read();
    pipes.push_back(pipe);
    Logger::log("Added pipe: " + pipe.getName());
    cout << "Pipe added!" << endl;
}

void addCompressorStation(vector<CompressorStation>& compressorStations) {
    CompressorStation cs;
    cs.read();
    compressorStations.push_back(cs);
    Logger::log("Added compressor station: " + cs.getName());
    cout << "Compressor station added!" << endl;
}

void viewAllObjects(const vector<Pipe>& pipes, const vector<CompressorStation>& compressorStations) {
    cout << "---- Pipes ----" << endl;
    for (const auto& pipe : pipes) {
        pipe.print();
    }
    cout << "---- Compressor Stations ----" << endl;
    for (const auto& cs : compressorStations) {
        cs.print();
    }
}

void editPipe(vector<Pipe>& pipes) {
    int id = safeIntInput("Enter pipe ID to edit: ");
    if (id >= 0 && id < pipes.size()) {
        pipes[id].setRepair(safeIntInput("In repair? (1 - yes, 0 - no): ") == 1);
        Logger::log("Pipe with ID " + to_string(id) + " edited");
        cout << "Pipe updated!" << endl;
    }
    else {
        cout << "Invalid ID!" << endl;
    }
}

void editCompressorStation(vector<CompressorStation>& compressorStations) {
    int id = safeIntInput("Enter compressor station ID to edit: ");
    if (id >= 0 && id < compressorStations.size()) {
        int action = safeIntInput("1. Start shop\n2. Stop shop\nEnter action: ");
        if (action == 1) {
            compressorStations[id].startShop();
            Logger::log("Shop started on compressor station with ID " + to_string(id));
        }
        else if (action == 2) {
            compressorStations[id].stopShop();
            Logger::log("Shop stopped on compressor station with ID " + to_string(id));
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    }
    else {
        cout << "Invalid ID!" << endl;
    }
}

void saveDataToFile(const vector<Pipe>& pipes, const vector<CompressorStation>& compressorStations) {
    string filename = safeStringInput("Enter filename to save: ");
    saveData(filename, pipes, compressorStations);
    Logger::log("Data saved to file " + filename);
}

void loadDataFromFile(vector<Pipe>& pipes, vector<CompressorStation>& compressorStations) {
    string filename = safeStringInput("Enter filename to load: ");
    loadData(filename, pipes, compressorStations);
    Logger::log("Data loaded from file " + filename);
}

void searchPipes(const vector<Pipe>& pipes) {
    int filter = safeIntInput("1. By name\n2. By repair status\nEnter filter: ");
    if (filter == 1) {
        string name = safeStringInput("Enter pipe name: ");
        bool found = false;
        for (const auto& pipe : pipes) {
            if (pipe.getName() == name) {
                pipe.print();
                found = true;
            }
        }
        if (!found) {
            cout << "No pipes with name " << name << " found." << endl;
            cout << "Available pipes:" << endl;
            for (const auto& pipe : pipes) {
                cout << pipe.getName() << endl;
            }
        }
    }
    else if (filter == 2) {
        bool inRepair = safeIntInput("In repair? (1 - yes, 0 - no): ") == 1;
        for (const auto& pipe : pipes) {
            if (pipe.isInRepair() == inRepair) {
                pipe.print();
            }
        }
    }
    else {
        cout << "Invalid choice!" << endl;
    }
}

void searchCompressorStations(const vector<CompressorStation>& compressorStations) {
    int filter = safeIntInput("1. By name\n2. By unused shop percentage\nEnter filter: ");
    if (filter == 1) {
        string name = safeStringInput("Enter compressor station name: ");
        bool found = false;
        for (const auto& cs : compressorStations) {
            if (cs.getName() == name) {
                cs.print();
                found = true;
            }
        }
        if (!found) {
            cout << "No compressor stations with name " << name << " found." << endl;
            cout << "Available compressor stations:" << endl;
            for (const auto& cs : compressorStations) {
                cout << cs.getName() << endl;
            }
        }
    }
    else if (filter == 2) {
        double percent = safeDoubleInput("Enter unused shop percentage: ");
        for (const auto& cs : compressorStations) {
            if (cs.getUnusedShopPercent() >= percent) {
                cs.print();
            }
        }
    }
    else {
        cout << "Invalid choice!" << endl;
    }
}

void batchEditPipes(vector<Pipe>& pipes) {
    int filter = safeIntInput("1. By name\n2. By repair status\nEnter filter: ");
    vector<int> selectedPipes;
    if (filter == 1) {
        string name = safeStringInput("Enter pipe name: ");
        for (int i = 0; i < pipes.size(); ++i) {
            if (pipes[i].getName() == name) {
                selectedPipes.push_back(i);
            }
        }
        if (selectedPipes.empty()) {
            cout << "No pipes with name " << name << " found." << endl;
            cout << "Available pipes:" << endl;
            for (const auto& pipe : pipes) {
                cout << pipe.getName() << endl;
            }
        }
    }
    else if (filter == 2) {
        bool inRepair = safeIntInput("In repair? (1 - yes, 0 - no): ") == 1;
        for (int i = 0; i < pipes.size(); ++i) {
            if (pipes[i].isInRepair() == inRepair) {
                selectedPipes.push_back(i);
            }
        }
        if (selectedPipes.empty()) {
            cout << "No pipes with the specified repair status found." << endl;
            cout << "Available pipes:" << endl;
            for (const auto& pipe : pipes) {
                cout << pipe.getName() << endl;
            }
        }
    }
    else {
        cout << "Invalid choice!" << endl;
        return;
    }

    if (selectedPipes.empty()) {
        cout << "No pipes found!" << endl;
        return;
    }

    int action = safeIntInput("1. Edit\n2. Delete\nEnter action: ");
    if (action == 1) {
        for (int id : selectedPipes) {
            pipes[id].setRepair(safeIntInput("In repair? (1 - yes, 0 - no): ") == 1);
            Logger::log("Pipe with ID " + to_string(id) + " edited");
        }
    }
    else if (action == 2) {
        for (auto it = selectedPipes.rbegin(); it != selectedPipes.rend(); ++it) {
            Logger::log("Pipe with ID " + to_string(*it) + " deleted");
            pipes.erase(pipes.begin() + *it);
        }
    }
    else {
        cout << "Invalid choice!" << endl;
    }
}