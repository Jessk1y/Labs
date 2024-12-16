#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;


struct Pipe {
    string name; 
    double length;
    double diameter;
    bool inRepair;
};


struct KS {
    string name;
    int numWorkshops;
    int workshopsWorking;
    double efficiency;
};


void addPipe(vector<Pipe>& pipes);
void addKS(vector<KS>& kss);
void showAll(const vector<Pipe>& pipes, const vector<KS>& kss);
void editPipe(vector<Pipe>& pipes);
void editKS(vector<KS>& kss);
void saveData(const vector<Pipe>& pipes, const vector<KS>& kss);
void loadData(vector<Pipe>& pipes, vector<KS>& kss);
void checkInput(int& number);

int main() {
    vector<Pipe> pipes;
    vector<KS> kss;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add pipe\n";
        cout << "2. Add KC\n";
        cout << "3. Show all objects\n";
        cout << "4. Edit pipe\n";
        cout << "5. Edit KC\n";
        cout << "6. Save\n";
        cout << "7. Load\n";
        cout << "0. Exit\n";
        cout << "Write action number: ";

        int choice;
        checkInput(choice);

        switch (choice) {
        case 1:
            addPipe(pipes);
            break;
        case 2:
            addKS(kss);
            break;
        case 3:
            showAll(pipes, kss);
            break;
        case 4:
            editPipe(pipes);
            break;
        case 5:
            editKS(kss);
            break;
        case 6:
            saveData(pipes, kss);
            break;
        case 7:
            loadData(pipes, kss);
            break;
        case 0:
            return 0;
        default:
            cout << "incorrect number!\n";
        }
    }
}

void checkInput(int& number) {
    while (!(cin >> number)) {
        cout << "Incorrect number!" << endl;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}


void addPipe(vector<Pipe>& pipes) {
    Pipe newPipe;
    cout << "Enter the name of pipe: ";
    cin >> newPipe.name;
    cout << "Enter the length of the pipe: ";
    cin >> newPipe.length;
    cout << "Enter the pipe diameter: ";
    cin >> newPipe.diameter;
    newPipe.inRepair = false;
    pipes.push_back(newPipe);
    cout << "Pipe added.\n";
}

void editPipe(vector<Pipe>& pipes) {
    if (pipes.empty()) {
        cout << "The pipe list is empty.\n";
        return;
    }

    cout << "Enter the pipe number to edit (from 1): ";
    int pipeIndex;
    cin >> pipeIndex;

    if (pipeIndex < 1 || pipeIndex > pipes.size()) {
        cout << "Incorrect pipe number.\n";
        return;
    }

    cout << "The current state of the pipe:\n";
    cout << "Name: " << pipes[pipeIndex - 1].name << endl;
    cout << "Length: " << pipes[pipeIndex - 1].length << endl;
    cout << "Diameter: " << pipes[pipeIndex - 1].diameter << endl;
    cout << "Under repair: " << (pipes[pipeIndex - 1].inRepair ? "Yes" : "No") << endl;

    cout << "Enter the new status 'under repair' (0 - no, 1 - yes): ";
    int repairStatus;
    cin >> repairStatus;

    pipes[pipeIndex - 1].inRepair = (repairStatus == 1);
    cout << "The pipe has been updated.\n";
}


void addKS(vector<KS>& kss) {
    KS newKS;
    cout << "Enter the name of the KC: ";
    cin >> newKS.name;
    cout << "Enter the number of workshops: ";
    cin >> newKS.numWorkshops;
    cout << "Enter the number of working workshops: ";
    cin >> newKS.workshopsWorking;
    while (newKS.workshopsWorking > newKS.numWorkshops) {
        cout << "Number of Working workshops more than number of workshops!" << endl;
        cout << "Enter again number of working workshops: ";
        cin >> newKS.workshopsWorking;
    }
    cout << "Enter the efficiency (a number from 0 to 1): ";
    cin >> newKS.efficiency;
    while (newKS.efficiency < 0 || newKS.efficiency > 1) {
        cout << "Enter 0 or 1!" << endl;
        cout << "Enter again number the efficiency: ";
        cin >> newKS.workshopsWorking;
    }
    kss.push_back(newKS);
    cout << "KC added.\n";
}

void editKS(vector<KS>& kss) {
    if (kss.empty()) {
        cout << "The list of KC is empty.\n";
        return;
    }

    cout << "Enter the KS number to edit (from 1): ";
    int ksIndex;
    cin >> ksIndex;

    if (ksIndex < 1 || ksIndex > kss.size()) {
        cout << "Incorrect KC number.\n";
        return;
    }

    cout << "Current state of KC:\n";
    cout << "Name: " << kss[ksIndex - 1].name << endl;
    cout << "Number of workshops: " << kss[ksIndex - 1].numWorkshops << endl;
    cout << "Workshops in operation: " << kss[ksIndex - 1].workshopsWorking << endl;
    cout << "Efficiency: " << kss[ksIndex - 1].efficiency << endl;

    cout << "Enter the action:\n";
    cout << "1. Start the workshop\n";
    cout << "2. Stop the workshop\n";
    cout << "Enter the action number: ";

    int action;
    cin >> action;

    if (action == 1) {
        if (kss[ksIndex - 1].workshopsWorking < kss[ksIndex - 1].numWorkshops) {
            kss[ksIndex - 1].workshopsWorking++;
            cout << "The workshop is running.\n";
        }
        else {
            cout << "All workshops are already running.\n";
        }
    }
    else if (action == 2) {
        if (kss[ksIndex - 1].workshopsWorking > 0) {
            kss[ksIndex - 1].workshopsWorking--;
            cout << "The workshop is stopped.\n";
        }
        else {
            cout << "All workshops have already been stopped.\n";
        }
    }
    else {
        cout << "Wrong choice of action.\n";
    }
}


void showAll(const vector<Pipe>& pipes, const vector<KS>& kss) {
    if (pipes.empty() && kss.empty()) {
        cout << "The list of objects is empty.\n";
        return;
    }

    cout << "Pipe list:\n";
    for (size_t i = 0; i < pipes.size(); ++i) {
        cout << "Pipe " << i + 1 << ":\n";
        cout << "Name: " << pipes[i].name << endl;
        cout << "Length: " << pipes[i].length << endl;
        cout << "Diameter: " << pipes[i].diameter << endl;
        cout << "Under repair: " << (pipes[i].inRepair ? "Yes" : "No") << endl;
    }

    cout << "\list of KC:\n";
    for (size_t i = 0; i < kss.size(); ++i) {
        cout << "KC " << i + 1 << ":\n";
        cout << "Name: " << kss[i].name << endl;
        cout << "Number of workshops: " << kss[i].numWorkshops << endl;
        cout << "Workshops in operation: " << kss[i].workshopsWorking << endl;
        cout << "Efficiency: " << kss[i].efficiency << endl;
    }
}

void saveData(const vector<Pipe>& pipes, const vector<KS>& kss) {
    ofstream outfile("data.txt");
    if (!outfile.is_open()) {
        cout << "Error opening a file for writing.\n";
        return;
    }

    outfile << "Pipes:\n";
    for (const auto& pipe : pipes) {
        outfile << pipe.name << " " << pipe.length << " " << pipe.diameter << " " << pipe.inRepair << endl;
    }

    outfile << "KS:\n";
    for (const auto& ks : kss) {
        outfile << ks.name << " " << ks.numWorkshops << " " << ks.workshopsWorking << " " << ks.efficiency << endl;
    }

    outfile.close();
    cout << "The data is saved to a file.\n";
}

void loadData(vector<Pipe>& pipes, vector<KS>& kss) {
    ifstream infile("data.txt");
    if (!infile.is_open()) {
        cout << "Error opening the file for reading.\n";
        return;
    }

    string line;
    bool isPipeSection = true;

    while (getline(infile, line)) {
        if (line == "Pipes:") {
            isPipeSection = true;
            continue;
        }
        else if (line == "KS:") {
            isPipeSection = false;
            continue;
        }

        if (isPipeSection) {
            Pipe newPipe;
            stringstream ss(line);
            ss >> newPipe.name >> newPipe.length >> newPipe.diameter >> newPipe.inRepair;
            pipes.push_back(newPipe);
        }
        else {
            KS newKS;
            stringstream ss(line);
            ss >> newKS.name >> newKS.numWorkshops >> newKS.workshopsWorking >> newKS.efficiency;
            kss.push_back(newKS);
        }
    }

    infile.close();
    cout << "The data is downloaded from a file.\n";
}