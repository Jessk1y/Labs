#include "Utils.h"
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

int safeIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter a positive integer." << endl;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

double safeDoubleInput(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter a positive number." << endl;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

string safeStringInput(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

void saveData(const string& filename, const vector<Pipe>& pipes, const vector<CompressorStation>& compressorStations) {
    ofstream outfile(filename);
    if (!outfile.is_open()) {
        ofstream createFile(filename);
        createFile.close();
        outfile.open(filename);
    }

    if (outfile.is_open()) {
        outfile << "Pipes:" << endl;
        for (const auto& pipe : pipes) {
            outfile << pipe.getName() << "," << pipe.getLength() << "," << pipe.getDiameter() << "," << (pipe.isInRepair() ? "1" : "0") << endl;
        }

        outfile << "CompressorStations:" << endl;
        for (const auto& cs : compressorStations) {
            outfile << cs.getName() << "," << cs.getNumShops() << "," << cs.getWorkingShops() << "," << cs.getEfficiency() << endl;
        }
        outfile.close();
        cout << "Data saved to file " << filename << endl;
    }
    else {
        cout << "Error opening file!" << endl;
    }
}

void loadData(const string& filename, vector<Pipe>& pipes, vector<CompressorStation>& compressorStations) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cout << "File does not exist!" << endl;
        return;
    }

    if (infile.is_open()) {
        string line;
        string type;
        while (getline(infile, line)) {
            if (line.find("Pipes:") != string::npos) {
                type = "Pipes";
                continue;
            }
            else if (line.find("CompressorStations:") != string::npos) {
                type = "CompressorStations";
                continue;
            }

            if (type == "Pipes") {
                string name, lengthStr, diameterStr, repairStr;
                int commaIndex = static_cast<int>(line.find(','));
                name = line.substr(0, commaIndex);
                line = line.substr(commaIndex + 1);
                commaIndex = static_cast<int>(line.find(','));
                lengthStr = line.substr(0, commaIndex);
                line = line.substr(commaIndex + 1);
                commaIndex = static_cast<int>(line.find(','));
                diameterStr = line.substr(0, commaIndex);
                repairStr = line.substr(commaIndex + 1);

                pipes.push_back(Pipe(name, stod(lengthStr), stod(diameterStr), repairStr == "1"));
            }
            else if (type == "CompressorStations") {
                string name, numShopsStr, workingShopsStr, efficiencyStr;
                int commaIndex = static_cast<int>(line.find(','));
                name = line.substr(0, commaIndex);
                line = line.substr(commaIndex + 1);
                commaIndex = static_cast<int>(line.find(','));
                numShopsStr = line.substr(0, commaIndex);
                line = line.substr(commaIndex + 1);
                commaIndex = static_cast<int>(line.find(','));
                workingShopsStr = line.substr(0, commaIndex);
                efficiencyStr = line.substr(commaIndex + 1);

                compressorStations.push_back(CompressorStation(name, stoi(numShopsStr), stoi(workingShopsStr), stod(efficiencyStr)));
            }
        }
        infile.close();
        cout << "Data loaded from file " << filename << endl;
    }
    else {
        cout << "Error opening file!" << endl;
    }
}