#ifndef FINALPROJECT_CUSTOMER_H
#define FINALPROJECT_CUSTOMER_H

#include <iostream>
#include <string>
#include "Date.h"
#include "Person.h"

using namespace std;

class Customer : public Person {
protected:
    string licenseState;
    string license;

public:
    Customer() = default; // Default constructors required to make the first array
    Customer(string firstname, string lastname, Date birthdate, string licenseState, string license); // for making a new customer
    Customer(string commaSeparatedValues); // for loading from CSV
    Customer(Customer * copyCustomer); // for building a new array

    Customer operator=(Customer copyCustomer); // used with copy constructor when building a new array

    string getLicenseState() {  return licenseState; }
    string getLicense() {   return license;     }

    string getCSVString();  // returns string of data members for updating CSV file
    void display(); // displays data members to console
};


Customer::Customer(string firstname, string lastname, Date birthdate, string licenseState, string license) { // constructor crea
    this-> firstname = firstname;
    this-> lastname = lastname;
    this-> birthdate = birthdate;
    this-> licenseState = licenseState;
    this-> license = license;
}


Customer::Customer(string commaSeparatedValues) {
    // Get a value up to the next comma, remove the value and the comma, repeat.
    firstname = commaSeparatedValues.substr(0,commaSeparatedValues.find(','));
    commaSeparatedValues = commaSeparatedValues.substr(commaSeparatedValues.find(',')+1);
    lastname = commaSeparatedValues.substr(0,commaSeparatedValues.find(","));
    commaSeparatedValues = commaSeparatedValues.substr(commaSeparatedValues.find(",")+1);
    licenseState = commaSeparatedValues.substr(0,commaSeparatedValues.find(","));
    commaSeparatedValues = commaSeparatedValues.substr(commaSeparatedValues.find(",")+1);
    license = commaSeparatedValues.substr(0,commaSeparatedValues.find(","));
    commaSeparatedValues = commaSeparatedValues.substr(commaSeparatedValues.find(",")+1);
    int month = stoi(commaSeparatedValues.substr(0,commaSeparatedValues.find(",")));
    commaSeparatedValues = commaSeparatedValues.substr(commaSeparatedValues.find(",")+1);
    int day = stoi(commaSeparatedValues.substr(0,commaSeparatedValues.find(",")));
    commaSeparatedValues = commaSeparatedValues.substr(commaSeparatedValues.find(",")+1);
    int year = stoi(commaSeparatedValues.substr(0,commaSeparatedValues.find(",")));

    Date tempDate(month, day, year);
    birthdate = tempDate;
}


Customer::Customer(Customer * copyCustomer) {
    this-> firstname = copyCustomer->firstname;
    this-> lastname = copyCustomer->lastname;
    this-> birthdate = copyCustomer->birthdate;
    this-> licenseState = copyCustomer->licenseState;
    this-> license = copyCustomer->license;
}


Customer Customer::operator=(Customer copyCustomer) {
    this-> firstname = copyCustomer.firstname;
    this-> lastname = copyCustomer.lastname;
    this-> birthdate = copyCustomer.birthdate;
    this-> licenseState = copyCustomer.licenseState;
    this-> license = copyCustomer.license;

    return this;
}

/**
 * Returns data members for updating the CSV in the following format:
 * firstname,lastname,state,license,birth_month,birth_day,birth_year
 * @return Returns a CSV formatted string.
 */
string Customer::getCSVString() {
    string dataMembers = firstname + "," +
                         lastname + "," +
                         licenseState + "," +
                         license + "," +
                         to_string(birthdate.month) + "," +
                         to_string(birthdate.day) + "," +
                         to_string(birthdate.year);
    return dataMembers;
}

void Customer::display() {
    cout << lastname << ", " << firstname << endl
         << "  |  DOB: " << birthdate.getString() << endl
         << "  |  License: " << licenseState << " " << license << "\n\n";
}

#endif //FINALPROJECT_CUSTOMER_H
