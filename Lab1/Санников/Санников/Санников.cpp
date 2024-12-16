#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <sstream>
#include <algorithm>

using namespace std;

// Function to validate numerical input
template <typename T>
T getValidInput(const string& prompt) {
    T value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            return value;
        }
    }
}

// Function to validate positive numerical input
template <typename T>
T getValidPositiveInput(const string& prompt) {
    T value;
    while (true) {
        value = getValidInput<T>(prompt);
        if (value <= 0) {
            cout << "Invalid input. Please enter a positive number." << endl;
        }
        else {
            return value;
        }
    }
}

// Structure for Pipe
struct Pipe {
    string kilometerMark;
    double length;
    double diameter;
    bool isInRepair;

    void readFromConsole() {
        cout << "Enter kilometer mark: ";
        cin >> kilometerMark;
        length = getValidPositiveInput<double>("Enter length: ");
        diameter = getValidPositiveInput<double>("Enter diameter: ");
        char repairChoice;
        while (true) {
            cout << "Is the pipe under repair? (y/n): ";
            cin >> repairChoice;
            if (repairChoice == 'y' || repairChoice == 'n') {
                isInRepair = (repairChoice == 'y');
                break;
            }
            else {
                cout << "Invalid input. Please enter 'y' or 'n'." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

            }
        }

    }

    void printToConsole() const {
        cout << "Kilometer Mark: " << kilometerMark << endl;
        cout << "Length: " << length << " km" << endl;
        cout << "Diameter: " << diameter << " mm" << endl;
        cout << "In Repair: " << (isInRepair ? "Yes" : "No") << endl;
    }

    void setRepairStatus(bool status) {
        isInRepair = status;
    }

    void saveToFile(ofstream& file) const {
        file << "Pipe_Start" << endl;
        file << "Kilometer Mark: " << kilometerMark << endl;
        file << "Length: " << length << endl;
        file << "Diameter: " << diameter << endl;
        file << "In Repair: " << isInRepair << endl;
        file << "Pipe_End" << endl;
    }

    void loadFromFile(ifstream& file) {
        string line;
        getline(file, line); // Read "Pipe_Start"
        if (line != "Pipe_Start") {
            return;
        }
        getline(file, line);
        kilometerMark = line.substr(line.find(":") + 2);

        getline(file, line);
        length = stod(line.substr(line.find(":") + 2));

        getline(file, line);
        diameter = stod(line.substr(line.find(":") + 2));


        getline(file, line);
        isInRepair = (line.substr(line.find(":") + 2) == "1"); // read and set boolean value

        getline(file, line); // Read "Pipe_End"
    }
};

// Structure for Compressor Station (CS)
struct CompressorStation {
    string name;
    int totalWorkshops;
    int workshopsInWork;
    double efficiency;

    void readFromConsole() {
        cout << "Enter CS name: ";
        cin >> name;
        totalWorkshops = getValidPositiveInput<int>("Enter total number of workshops: ");
        workshopsInWork = getValidInput<int>("Enter number of workshops in work: ");
        while (workshopsInWork > totalWorkshops) {
            cout << "Invalid input. Workshops in work can not be more than total workshops" << endl;
            workshopsInWork = getValidInput<int>("Enter number of workshops in work: ");
        }
        while (true) {
            efficiency = getValidPositiveInput<double>("Enter efficiency: ");
            if (efficiency <= 100) {
                break;
            }
            else {
                cout << "Invalid input. Efficiency cannot be more than 100" << endl;
            }
        }
    }

    void printToConsole() const {
        cout << "CS Name: " << name << endl;
        cout << "Total Workshops: " << totalWorkshops << endl;
        cout << "Workshops in Work: " << workshopsInWork << endl;
        cout << "Efficiency: " << efficiency << endl;
    }

    void startWorkshop() {
        if (workshopsInWork < totalWorkshops) {
            workshopsInWork++;
            cout << "Workshop started. Workshops in work: " << workshopsInWork << endl;
        }
        else {
            cout << "All workshops are already in work." << endl;
        }
    }

    void stopWorkshop() {
        if (workshopsInWork > 0) {
            workshopsInWork--;
            cout << "Workshop stopped. Workshops in work: " << workshopsInWork << endl;
        }
        else {
            cout << "No workshops are currently in work." << endl;
        }
    }

    void saveToFile(ofstream& file) const {
        file << "CS_Start" << endl;
        file << "CS Name: " << name << endl;
        file << "Total Workshops: " << totalWorkshops << endl;
        file << "Workshops in Work: " << workshopsInWork << endl;
        file << "Efficiency: " << efficiency << endl;
        file << "CS_End" << endl;
    }

    void loadFromFile(ifstream& file) {
        string line;
        getline(file, line); // Read "CS_Start"
        if (line != "CS_Start") {
            return;
        }

        getline(file, line);
        name = line.substr(line.find(":") + 2);


        getline(file, line);
        totalWorkshops = stoi(line.substr(line.find(":") + 2));

        getline(file, line);
        workshopsInWork = stoi(line.substr(line.find(":") + 2));


        getline(file, line);
        efficiency = stod(line.substr(line.find(":") + 2));

        getline(file, line); // Read "CS_End"
    }
};

// Global vectors to store pipes and CSs
vector<Pipe> pipes;
vector<CompressorStation> css;

// Function to display menu
void displayMenu() {
    cout << "\nMenu:" << endl;
    cout << "1. Add Pipe" << endl;
    cout << "2. Add CS" << endl;
    cout << "3. View All Objects" << endl;
    cout << "4. Edit Pipe" << endl;
    cout << "5. Edit CS" << endl;
    cout << "6. Save" << endl;
    cout << "7. Load" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
}

// Function to add a new pipe
void addPipe() {
    Pipe newPipe;
    newPipe.readFromConsole();
    pipes.push_back(newPipe);
    cout << "Pipe added." << endl;
}

// Function to add a new CS
void addCS() {
    CompressorStation newCS;
    newCS.readFromConsole();
    css.push_back(newCS);
    cout << "CS added." << endl;
}


// Function to view all objects
void viewAllObjects() {
    cout << "\nPipes:\n";
    for (size_t i = 0; i < pipes.size(); ++i) {
        cout << "Pipe #" << (i + 1) << ":" << endl;
        pipes[i].printToConsole();
        cout << "----------\n";
    }
    cout << "\nCompressor Stations:\n";
    for (size_t i = 0; i < css.size(); ++i) {
        cout << "CS #" << (i + 1) << ":" << endl;
        css[i].printToConsole();
        cout << "----------\n";
    }
}
// Function to edit a pipe's repair status
void editPipe() {
    if (pipes.empty()) {
        cout << "No pipes to edit." << endl;
        return;
    }
    int index;
    while (true) {
        index = getValidInput<int>("Enter the index of the pipe to edit (starting from 1): ");
        if (index >= 1 && index <= pipes.size()) {
            break;
        }
        else {
            cout << "Invalid index, try again." << endl;
        }
    }

    char repairChoice;
    while (true) {
        cout << "Set pipe repair status? (y/n): ";
        cin >> repairChoice;
        if (repairChoice == 'y' || repairChoice == 'n') {
            pipes[index - 1].setRepairStatus(repairChoice == 'y');
            break;
        }
        else {
            cout << "Invalid input, try again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    cout << "Pipe status updated." << endl;
}

// Function to edit a CS's workshops
void editCS() {
    if (css.empty()) {
        cout << "No CSs to edit." << endl;
        return;
    }

    int index;
    while (true) {
        index = getValidInput<int>("Enter the index of the CS to edit (starting from 1): ");
        if (index >= 1 && index <= css.size()) {
            break;
        }
        else {
            cout << "Invalid index, try again." << endl;
        }
    }


    int workshopAction;
    while (true) {
        cout << "Choose action for workshops (1 - start, 2 - stop): ";
        cin >> workshopAction;
        if (workshopAction == 1 || workshopAction == 2) {
            break;
        }
        else {
            cout << "Invalid input, try again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

    }
    if (workshopAction == 1) {
        css[index - 1].startWorkshop();
    }
    else {
        css[index - 1].stopWorkshop();
    }

}
// Function to save data to file
void saveData() {
    if (pipes.empty() && css.empty()) {
        cout << "Nothing to save. No pipes or CSs have been added." << endl;
        return;
    }

    if (!pipes.empty()) {
        ofstream pipesFile("pipes.txt");
        if (pipesFile.is_open()) {
            pipesFile << "Number of Pipes: " << pipes.size() << endl;
            for (const auto& pipe : pipes) {
                pipe.saveToFile(pipesFile);
            }
            pipesFile.close();
            cout << "Pipes data saved to pipes.txt" << endl;
        }
        else {
            cout << "Error opening pipes.txt for saving." << endl;
        }
    }
    else {
        cout << "No pipes to save." << endl;
    }


    if (!css.empty()) {
        ofstream csFile("cs.txt");
        if (csFile.is_open()) {
            csFile << "Number of CSs: " << css.size() << endl;
            for (const auto& cs : css) {
                cs.saveToFile(csFile);
            }
            csFile.close();
            cout << "CS data saved to cs.txt" << endl;
        }
        else {
            cout << "Error opening cs.txt for saving." << endl;
        }
    }
    else {
        cout << "No CSs to save." << endl;
    }

}

// Function to load data from file
void loadData() {
    pipes.clear();
    css.clear();

    ifstream pipesFile("pipes.txt");
    if (pipesFile.is_open()) {
        string line;
        int numPipes = 0;
        while (getline(pipesFile, line)) {
            if (line.find("Number of Pipes: ") != string::npos) {
                numPipes = stoi(line.substr(line.find(":") + 2));
                for (int i = 0; i < numPipes; ++i) {
                    Pipe pipe;
                    pipe.loadFromFile(pipesFile);
                    pipes.push_back(pipe);
                }
            }
        }
        pipesFile.close();
        if (pipes.empty()) {
            cout << "pipes.txt file is empty." << endl;
        }
        else {
            cout << "Pipes data loaded from pipes.txt" << endl;
        }
    }
    else {
        cout << "Error opening pipes.txt for loading." << endl;
    }

    ifstream csFile("cs.txt");
    if (csFile.is_open()) {
        string line;
        int numCSs = 0;
        while (getline(csFile, line)) {
            if (line.find("Number of CSs: ") != string::npos) {
                numCSs = stoi(line.substr(line.find(":") + 2));
                for (int i = 0; i < numCSs; ++i) {
                    CompressorStation cs;
                    cs.loadFromFile(csFile);
                    css.push_back(cs);
                }
            }
        }
        csFile.close();
        if (css.empty()) {
            cout << "cs.txt file is empty." << endl;
        }
        else {
            cout << "CS data loaded from cs.txt" << endl;
        }
    }
    else {
        cout << "Error opening cs.txt for loading." << endl;
    }
}


int main() {
    int choice;
    do {
        displayMenu();
        choice = getValidInput<int>("");

        switch (choice) {
        case 1:
            addPipe();
            break;
        case 2:
            addCS();
            break;
        case 3:
            viewAllObjects();
            break;
        case 4:
            editPipe();
            break;
        case 5:
            editCS();
            break;
        case 6:
            saveData();
            break;
        case 7:
            loadData();
            break;
        case 0:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}