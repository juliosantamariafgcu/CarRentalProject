#ifndef FINALPROJECT_RENTALCONTRACT_H
#define FINALPROJECT_RENTALCONTRACT_H

#include <iostream>
#include <string>
#include "Vehicle.h"
#include "Customer.h"

using namespace std;

class RentalContract {
protected:
    Customer * customer;
    string customerLicense;
    Vehicle * vehicle;
    string vehicleVIN;
    Date startDate;
    int rentalDays;
    bool waiverIsSigned;
    bool hasExtraInsurance;

public:
    RentalContract() = default;
    RentalContract(string CSV);
    RentalContract(string customerLicense, string vehicleVin, Date startDate,
                   int rentalDays, bool waiverIsSigned, bool hasExtraInsurance);
    RentalContract(RentalContract * copyContract);
    ~RentalContract() = default;

    RentalContract operator=(RentalContract copyContract);

    void signWaiver() {     waiverIsSigned = true;      }
    void addInsurance() {   hasExtraInsurance = true;   }
    Customer * getCustomer() { return customer; }
    Vehicle * getVehicle() { return vehicle; }
    void findCustomer(Customer customerArray[], int totalCustomers);
    void findVehicle(Vehicle vehicleArray[], int totalVehicles);
    string getCSVString();
    void display();
    float calcPrice();
};

/**
 * Used in building RentalContract array from RentalContract.csv data.
 * @param CSV
 * @param customerArray
 * @param totalCustomers
 * @param totalVehicles
 * @param vehicleArray
 */
RentalContract::RentalContract(string CSV) {
    // Get a value up to the next comma, remove the value and the comma, repeat.
    customerLicense = CSV.substr(0,CSV.find(','));
    CSV = CSV.substr(CSV.find(',')+1);
    vehicleVIN = CSV.substr(0,CSV.find(","));
    CSV = CSV.substr(CSV.find(",")+1);

    // Get start date
    int month = stoi(CSV.substr(0,CSV.find(",")));
    CSV = CSV.substr(CSV.find(",")+1);
    int day = stoi(CSV.substr(0,CSV.find(",")));
    CSV = CSV.substr(CSV.find(",")+1);
    int year = stoi(CSV.substr(0,CSV.find(",")));
    CSV = CSV.substr(CSV.find(",")+1);

    Date tempDate(month, day, year);
    startDate = tempDate;

    rentalDays = stoi(CSV.substr(0,CSV.find(",")));
    CSV = CSV.substr(CSV.find(",")+1);
    waiverIsSigned = stoi(CSV.substr(0,CSV.find(",")));
    CSV = CSV.substr(CSV.find(",")+1);
    hasExtraInsurance = stoi(CSV.substr(0,CSV.find(",")));
}


RentalContract::RentalContract(string customerLicense, string vehicleVIN,
                               Date startDate, int rentalDays, bool waiverIsSigned,
                               bool hasExtraInsurance) {
    this-> customerLicense = customerLicense;
    this-> vehicleVIN = vehicleVIN;
    this-> startDate = startDate;
    this-> rentalDays = rentalDays;
    this-> waiverIsSigned = waiverIsSigned;
    this-> hasExtraInsurance = hasExtraInsurance;
}


RentalContract::RentalContract(RentalContract * copyContract) {
    this-> customer = copyContract -> customer;
    this-> customerLicense = copyContract -> customerLicense;
    this-> vehicle = copyContract -> vehicle;
    this-> vehicleVIN = copyContract -> vehicleVIN;
    this-> startDate = copyContract -> startDate;
    this-> rentalDays = copyContract -> rentalDays;
    this-> waiverIsSigned = copyContract -> waiverIsSigned;
    this-> hasExtraInsurance = copyContract -> hasExtraInsurance;
}


RentalContract RentalContract::operator=(RentalContract copyContract) {
    this-> customer = copyContract.customer;
    this-> customerLicense = copyContract.customerLicense;
    this-> vehicle = copyContract.vehicle;
    this-> vehicleVIN = copyContract.vehicleVIN;
    this-> startDate = copyContract.startDate;
    this-> rentalDays = copyContract.rentalDays;
    this-> waiverIsSigned = copyContract.waiverIsSigned;
    this-> hasExtraInsurance = copyContract.hasExtraInsurance;

    return this;
}


void RentalContract::findCustomer(Customer customerArray[], int totalCustomers) {
    for (int i = 0; i < totalCustomers; i++) {
        if( customerArray[i].getLicense() == customerLicense ) {
            customer = &customerArray[i];
        }
    }
}

void RentalContract::findVehicle(Vehicle vehicleArray[], int totalVehicles) {
    for (int i = 0; i < totalVehicles; i++) {
        if (vehicleArray[i].getVIN() == vehicleVIN) {
            vehicle = &vehicleArray[i];
            vehicle->rent();
        }
    }
}


string RentalContract::getCSVString() {
    string CSVString = customerLicense +","+ vehicleVIN +","+ to_string(startDate.month)
                       +","+ to_string(startDate.day) +","+ to_string(startDate.year)
                       +","+ to_string(rentalDays) +","+ to_string(waiverIsSigned)
                       +","+ to_string(hasExtraInsurance);

    return CSVString;
}


void RentalContract::display() {
    Date rentalPeriod(0,rentalDays,0);
    Date endDate = startDate + rentalPeriod;
    cout << "Customer: " << customer->getLast() << ", " << customer->getFirst() << endl
         << "  |  Vehicle: " << vehicle->getYear() << " " << vehicle->getMake() << " " << vehicle->getModel() << endl
         << "  |  Start Date: " << startDate.getString() << endl
         << "  |  End Date: " << endDate.getString() << endl
         << "  |  Total Price: $" << calcPrice() << endl
         << "  |  Waivers signed? " << (waiverIsSigned? "Yes":"No") << endl
         << "  |  Rental insurance? " << (hasExtraInsurance? "Yes":"No") << "\n\n";
}


float RentalContract::calcPrice() {
    const float salesTax = 0.069;
    float subtotal = vehicle->getDailyRate() * rentalDays;
    float total = subtotal + (subtotal * salesTax);

    return total;
}

#endif //FINALPROJECT_RENTALCONTRACT_H
