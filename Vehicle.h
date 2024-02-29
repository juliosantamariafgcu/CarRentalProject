#ifndef FINALPROJECT_VEHICLE_H
#define FINALPROJECT_VEHICLE_H

#include <iostream>
#include <string>

using namespace std;

class Vehicle {
protected:
    string vin{};
    string make{};
    string model{};
    int year{};
    float miles{};
    string license{};
    int dailyRate{};
    bool isRented = false;
public:
    Vehicle() = default;
    Vehicle(string vin, string make, string model, int year, float miles, string license, int dailyRental);
    Vehicle(string CSV);
    Vehicle(Vehicle * copyVehicle);

    Vehicle operator=(Vehicle copyVehicle);

    void rent() {   isRented = true;    }
    void release() {    isRented = false;   }
    string getVIN() {   return vin;     }
    string getMake() {  return make;    }
    string getModel() { return model;   }
    int getYear() {  return year;    }
    float getDailyRate() {  return dailyRate; }// returns daily rental price
    bool getStatus() { return isRented; }
    string getCSVString();
    void display();
};


Vehicle::Vehicle (string vin, string make, string model, int year, float miles, string license, int dailyRate) {
this -> vin = vin;
this -> make = make;
this -> model = model;
this -> year = year;
this -> miles = miles;
this -> license = license;
this -> dailyRate = dailyRate;
this-> isRented = isRented;
}


Vehicle::Vehicle(Vehicle * copyVehicle) {
    this -> vin = copyVehicle -> vin;
    this -> make = copyVehicle -> make;
    this -> model = copyVehicle -> model;
    this -> year = copyVehicle -> year;
    this -> miles = copyVehicle -> miles;
    this -> license = copyVehicle -> license;
    this -> dailyRate = copyVehicle -> dailyRate;
    this -> isRented = copyVehicle -> isRented;
}


Vehicle::Vehicle (string CSV) {
    // Get a value up to the next comma, remove the value and the comma, repeat.
    vin = CSV.substr(0,CSV.find(','));
    CSV = CSV.substr(CSV.find(',')+1);
    make = CSV.substr(0,CSV.find(","));
    CSV = CSV.substr(CSV.find(",")+1);
    model = CSV.substr(0,CSV.find(","));
    CSV = CSV.substr(CSV.find(",")+1);
    year = stoi(CSV.substr(0,CSV.find(",")));
    CSV = CSV.substr(CSV.find(",")+1);
    miles = stof(CSV.substr(0,CSV.find(",")));
    CSV = CSV.substr(CSV.find(",")+1);
    license = CSV.substr(0,CSV.find(","));
    CSV = CSV.substr(CSV.find(",")+1);
    dailyRate = stoi(CSV.substr(0,CSV.find(",")));
    CSV = CSV.substr(CSV.find(",")+1);
    isRented = stoi(CSV.substr(0,CSV.find(",")));
}

Vehicle Vehicle::operator=(Vehicle copyVehicle) {
    this-> vin = copyVehicle.vin;
    this-> make = copyVehicle.make;
    this-> model = copyVehicle.model;
    this-> year = copyVehicle.year;
    this-> miles = copyVehicle.miles;
    this-> license = copyVehicle.license;
    this-> dailyRate = copyVehicle.dailyRate;
    this-> isRented = copyVehicle.isRented;

    return this;
}

string Vehicle::getCSVString() {
    string dataMembers = vin + "," +
                         make + "," +
                         model + "," +
                         to_string(year) + "," +
                         to_string(miles) + "," +
                         license + "," +
                         to_string(dailyRate) + "," +
                         to_string(isRented);
    return dataMembers;
}

void Vehicle::display() {
    cout << "" << year << " " << make << " " << model << endl
         << "  |  Plate: " << license << endl
         << "  |  Miles: " << miles << endl
         << "  |  Daily Rate: $" << dailyRate << endl
         << "  |  Currently rented: " << (isRented ? "Yes":"No") << "\n\n";
}


#endif //FINALPROJECT_VEHICLE_H
