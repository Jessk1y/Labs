#ifndef COMPRESSORSTATION_H
#define COMPRESSORSTATION_H

#include <string>

class CompressorStation {
private:
    std::string name;
    int num_shops;
    int working_shops;
    double efficiency;

public:
    CompressorStation();
    CompressorStation(std::string n, int shops, int working, double eff);

    std::string getName() const;
    int getNumShops() const;
    int getWorkingShops() const;
    double getEfficiency() const;
    double getUnusedShopPercent() const;

    void startShop();
    void stopShop();

    void print() const;
    void read();
};

#endif // COMPRESSORSTATION_H
