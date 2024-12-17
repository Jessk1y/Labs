#include <iostream>
#include "Actions.h"
#include "Utils.h"

using namespace std;

vector<Pipe> pipes;
vector<CompressorStation> compressorStations;

void showMenu() {
    cout << "Menu:" << endl;
    cout << "1. Add Pipe" << endl;
    cout << "2. Add Compressor Station" << endl;
    cout << "3. View All Objects" << endl;
    cout << "4. Edit Pipe" << endl;
    cout << "5. Edit Compressor Station" << endl;
    cout << "6. Save" << endl;
    cout << "7. Load" << endl;
    cout << "8. Search Pipes" << endl;
    cout << "9. Search Compressor Stations" << endl;
    cout << "10. Batch Edit Pipes" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
}

void handleChoice() {
    int choice = safeIntInput("");
    switch (choice) {
    case 1:
        addPipe(pipes);
        break;
    case 2:
        addCompressorStation(compressorStations);
        break;
    case 3:
        viewAllObjects(pipes, compressorStations);
        break;
    case 4:
        editPipe(pipes);
        break;
    case 5:
        editCompressorStation(compressorStations);
        break;
    case 6:
        saveDataToFile(pipes, compressorStations);
        break;
    case 7:
        loadDataFromFile(pipes, compressorStations);
        break;
    case 8:
        searchPipes(pipes);
        break;
    case 9:
        searchCompressorStations(compressorStations);
        break;
    case 10:
        batchEditPipes(pipes);
        break;
    case 0:
        cout << "Exiting program..." << endl;
        exit(0);
    default:
        cout << "Invalid choice!" << endl;
        break;
    }
}

int main() {
    while (true) {
        showMenu();
        handleChoice();
    }
    return 0;
}