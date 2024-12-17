#ifndef PIPE_H
#define PIPE_H

#include <string>

class Pipe {
private:
    std::string name;
    double length;
    double diameter;
    bool in_repair;

public:
    Pipe();
    Pipe(std::string n, double l, double d, bool r);

    std::string getName() const;
    double getLength() const;
    double getDiameter() const;
    bool isInRepair() const;

    void setRepair(bool r);

    void print() const;
    void read();
};

#endif // PIPE_H
