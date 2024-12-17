#include "Pipe.h"
#include "Utils.h"
#include <iostream>

using namespace std;

Pipe::Pipe() : name(""), length(0), diameter(0), in_repair(false) {}

Pipe::Pipe(string n, double l, double d, bool r) : name(n), length(l), diameter(d), in_repair(r) {}

string Pipe::getName() const { return name; }
double Pipe::getLength() const { return length; }
double Pipe::getDiameter() const { return diameter; }
bool Pipe::isInRepair() const { return in_repair; }

void Pipe::setRepair(bool r) { in_repair = r; }

void Pipe::print() const {
    cout << "Name: " << name << endl;
    cout << "Length: " << length << " km" << endl;
    cout << "Diameter: " << diameter << " mm" << endl;
    cout << "In repair: " << (in_repair ? "Yes" : "No") << endl;
}

void Pipe::read() {
    cout << "Enter pipe name: ";
    getline(cin, name);
    length = safeDoubleInput("Enter pipe length (in km): ");
    diameter = safeDoubleInput("Enter pipe diameter (in mm): ");
    in_repair = safeIntInput("In repair? (1 - yes, 0 - no): ") == 1;
}