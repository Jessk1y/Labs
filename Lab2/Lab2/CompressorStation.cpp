#include "CompressorStation.h"
#include "Utils.h"
#include <iostream>

using namespace std;

CompressorStation::CompressorStation() : name(""), num_shops(0), working_shops(0), efficiency(0) {}

CompressorStation::CompressorStation(string n, int shops, int working, double eff)
    : name(n), num_shops(shops), working_shops(working), efficiency(eff) {}

string CompressorStation::getName() const { return name; }
int CompressorStation::getNumShops() const { return num_shops; }
int CompressorStation::getWorkingShops() const { return working_shops; }
double CompressorStation::getEfficiency() const { return efficiency; }
double CompressorStation::getUnusedShopPercent() const { return (num_shops - working_shops) * 100.0 / num_shops; }

void CompressorStation::startShop() {
    if (working_shops < num_shops) {
        working_shops++;
        cout << "Shop started!" << endl;
    }
    else {
        cout << "All shops are already working!" << endl;
    }
}

void CompressorStation::stopShop() {
    if (working_shops > 0) {
        working_shops--;
        cout << "Shop stopped!" << endl;
    }
    else {
        cout << "All shops are already stopped!" << endl;
    }
}

void CompressorStation::print() const {
    cout << "Compressor Station Name: " << name << endl;
    cout << "Number of shops: " << num_shops << endl;
    cout << "Working shops: " << working_shops << endl;
    cout << "Efficiency: " << efficiency << endl;
}

void CompressorStation::read() {
    cout << "Enter compressor station name: ";
    getline(cin, name);
    num_shops = safeIntInput("Enter number of shops: ");
    working_shops = safeIntInput("Enter number of working shops: ");
    while (working_shops > num_shops) {
        cout << "Error: number of working shops cannot exceed total number of shops!" << endl;
        working_shops = safeIntInput("Enter number of working shops: ");
    }
    efficiency = safeDoubleInput("Enter efficiency: ");
}