//  File: CarRentalSystem.cpp
// Class: COP 3003, Spring 2023, CRN 15049
//   Who: Niel Patel, Julio Santamaria, David West
//  Desc: A mock rental system for a car rental company.
//        Final project for Programming II
//------------------------------------------------------------------------------

#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include "RentalContract.h"
#include <stdlib.h>

using namespace std;

const string CUSTOMER_CSV = "data/Customers.csv";
const string VEHICLE_CSV = "data/Vehicles.csv";
const string CONTRACT_CSV = "data/RentalContracts.csv";

Date getToday();    // Makes a string with the current date and time.

// ---------------------- Create New Object Prototypes ---------------------- //
Customer newCustomer();
Vehicle newVehicle();
RentalContract newContract(int totalCustomers, Customer * customerArray,
                           int totalVehicles, Vehicle * vehicleArray);

// ------------------- Delete Object from Array Prototypes ------------------ //
Customer * deleteCustomer( int & numCustomers, Customer oldCustomerArray[],
                           RentalContract contractArray[], int numContracts );
Vehicle * deleteVehicle( int & numVehicles, Vehicle oldVehicleArray[],
                         RentalContract contractArray[], int numContracts );

// ------------ Templated Prototypes for Array and File Handling ------------ //
template <class T> T * loadCSV(string filePath, int & totalItems, T targetArray[]);
template <class T> T * addObjectToArray(T newObject, int & arrayDimension, T oldObjectArray[], string csvFilePath,
                                        RentalContract contractArray[], int numContracts);
template <class T> bool saveObjectToCSV(T object, string filePath);
template <class T> void updateCSV(T objectArray, int arraySize, string filePath);
template <class T> void displayArray(int totalItems, T array[]);


int main() {
    // ------------------------------ Startup  ------------------------------ //
    Date today(getToday());

    // Create and fill a Customer array with data from Customers.csv
    int totalCustomers { 0 };
    Customer * customerList;
    customerList = loadCSV(CUSTOMER_CSV, totalCustomers, customerList);

    // Create and fill a Vehicle array with data from Vehicles.csv
    int totalVehicles { 0 };
    Vehicle * vehicleList;
    vehicleList = loadCSV(VEHICLE_CSV, totalVehicles, vehicleList);

    // Create and fill a RentalContract array with data from RentalContracts.csv
    int totalContracts { 0 };
    RentalContract * contractList;
    contractList = loadCSV(CONTRACT_CSV, totalContracts, contractList);
    // Find Customer/Vehicle within their respective arrays to load pointers
    for (int i = 0; i < totalContracts; i++) {
        contractList[i].findCustomer(customerList, totalCustomers);
        contractList[i].findVehicle(vehicleList, totalVehicles);
    }

    // ----------------------------- Main Loop ------------------------------ //
    string userResponse;
    int userSelection;
    while(true) {
        cout << "-----| MAIN MENU |------------------------------------" << "\n\n"
             << "  1. View existing customers" << endl
             << "  2. Add a new customer" << endl
             << "  3. Delete a customer" << endl
             << " --------------------------- " << endl
             << "  4. View existing vehicles" << endl
             << "  5. Add a new vehicle" << endl
             << "  6. Delete a vehicle" << endl
             << " --------------------------- " << endl
             << "  7. View existing car rentals" << endl
             << "  8. Create a new car rental" << "\n\n"
             << "Select a number or type EXIT to end program: ";
        cin >> userResponse;

        if (userResponse == "EXIT" || userResponse == "exit" ||
            userResponse == "Exit") {
            break;
        } else {
            userSelection = atoi(userResponse.c_str());
        }

        switch (userSelection) {
            case 1:
                system("cls");
                cout << "-----|  Existing Customers  |-------------------------" << "\n\n";
                displayArray(totalCustomers, customerList);
                break;
            case 2:
                system("cls");
                customerList = addObjectToArray(newCustomer(), totalCustomers,
                                                customerList,CUSTOMER_CSV,
                                                contractList, totalContracts);
                for (int i = 0; i < totalContracts; i++) {
                    contractList[i].findCustomer(customerList, totalCustomers);
                }
                break;
            case 3:
                system("cls");
                customerList = deleteCustomer( totalCustomers, customerList,
                                           contractList, totalContracts );
                break;
            case 4:
                system("cls");
                cout << "-----|  Existing Vehicles  |--------------------------" << "\n\n";
                displayArray(totalVehicles, vehicleList);
                break;
            case 5:
                system("cls");
                vehicleList = addObjectToArray(newVehicle(), totalVehicles,
                                               vehicleList, VEHICLE_CSV,
                                               contractList, totalContracts);
                for (int i = 0; i < totalContracts; i++) {
                    contractList[i].findVehicle(vehicleList, totalVehicles);
                }
                break;
            case 6:
                system("cls");
                vehicleList = deleteVehicle( totalVehicles, vehicleList,
                                               contractList, totalContracts );
                break;
            case 7:
                system("cls");
                cout << "-----|  Rentals In Progress  |------------------------" << "\n\n";
                displayArray(totalContracts, contractList);
                break;
            case 8:
                system("cls");
                try {
                    contractList = addObjectToArray(newContract(totalCustomers,
                                                                customerList,
                                                                totalVehicles,
                                                                vehicleList),
                                                    totalContracts,
                                                    contractList,
                                                    CONTRACT_CSV,
                                                    contractList,
                                                    totalContracts);

                    contractList[totalContracts - 1].findCustomer(customerList,
                                                                  totalCustomers);
                    contractList[totalContracts - 1].findVehicle(vehicleList,
                                                                 totalVehicles);
                    updateCSV(vehicleList, totalVehicles, VEHICLE_CSV);
                }
                catch(int errorNum){}
                break;
            default:
                system("cls");
                cout << "Unable to interpret your input. Please try again." << endl;
                system("pause");
        }
        system("cls");
    }


    return 0;
}


Date getToday() {
    time_t now = time(0);
    string date_time = ctime(&now);
    Date returnDate(date_time);

    return returnDate;
}


/**
 * Prompts user for info to make a new Customer.
 * @return Returns customer class of new customer
 */
Customer newCustomer(){
    cout << "-----| New Customer |---------------------------------" << "\n\n";
    cout << "Enter First Name: ";
    string fName;
    cin >> fName;

    cout << "\nEnter Last Name: ";
    string lName;
    cin >> lName;

    // Get date of birth as a string and make new Date object
    cout << "\nEnter Date of Birth (MM/DD/YYYY): ";
    string birthdateString;
    cin >> birthdateString;
    Date birthdate(birthdateString);

    cout << "\nEnter State of License (ex. FL): ";
    string licenseState;
    cin >> licenseState;

    cout << "\nEnter License Number: ";
    string licenseNum;
    cin >> licenseNum;

    Customer returnCustomer = new Customer(fName, lName,
                                           birthdate, licenseState, licenseNum);

    return returnCustomer;
}


/**
 * Prompts user for info on a new vehicle.
 * @return Returns vehicle class of new vehicle
 */
Vehicle newVehicle(){
    cout << "-----| New Vehicle |----------------------------------" << "\n\n";
    cout << "Enter VIN of Vehicle: ";
    string vinVehicle;
    cin >> vinVehicle;

    cout << "\nEnter Make of Vehicle: ";
    string makeVehicle;
    cin >> makeVehicle;

    cout << "\nEnter Model of Vehicle: ";
    string modelVehicle;
    cin >> modelVehicle;

    cout << "\nEnter Vehicle Year: ";
    int yearVehicle;
    cin >> yearVehicle;

    cout << "\nEnter Number of Miles: ";
    float milesVehicle;
    cin >> milesVehicle;

    cout << "\nEnter License Plate Number: ";
    string plateNumber;
    cin >> plateNumber;

    cout << "\nEnter License Rental Price: ";
    int rentalPrice;
    cin >> rentalPrice;

    Vehicle returnVehicle(vinVehicle, makeVehicle, modelVehicle,
                          yearVehicle, milesVehicle, plateNumber,
                          rentalPrice);

    return returnVehicle;
}


RentalContract newContract(int totalCustomers, Customer * customerArray, int totalVehicles, Vehicle * vehicleArray) {
    cout << "-----|  New Car Rental  |-----------------------------" << "\n\n";
    // Get a Customer for the contract.
    cout << "Enter the licence number of the customer: ";
    string driversLicense;
    cin >> driversLicense;

    bool customerFound { false };
    for (int i = 0; i < totalCustomers; i++)
        if (driversLicense == customerArray[i].getLicense())
            customerFound = true;

    if (!customerFound) {
        cout << "Customer not found. Do you need to add a new customer?"
             << endl;
        system("pause");
        throw 123;
    }

    // Get a Vehicle for the contract.
    cout << "Enter the VIN of the vehicle: ";
    string vehicleID;
    cin >> vehicleID;

    bool vehicleFound { false };
    for (int i = 0; i < totalVehicles; i++)
        if (vehicleID == vehicleArray[i].getVIN())
            vehicleFound = true;

    if (!vehicleFound) {
        cout << "Vehicle not found. Do you need to add a new vehicle?" << endl;
        system("pause");
        throw 456;

    }

    cout << "Enter the start date in the format MM/DD/YYYY: ";
    string dateString;
    cin >> dateString;
    Date startDate(dateString);

    cout << "How many days is the vehicle being rented? ";
    int rentalDays;
    cin >> rentalDays;

    cout << "Has the customer signed the necessary paperwork? (Yes/No): ";
    string waiverInput;
    cin >> waiverInput;

    bool waiverSigned { false };
    if (waiverInput[0] == 'Y' || waiverInput[0] == 'y')
        waiverSigned = true;
    if (waiverInput[0] == 'N' || waiverInput[0] == 'n')
        waiverSigned = false;

    cout << "Does the customer wish for car rental insurance? (Yes/No): ";
    string insuranceInput;
    cin >> insuranceInput;

    bool rentalInsurance { false };
    if (insuranceInput[0] == 'Y' || insuranceInput[0] == 'y')
        rentalInsurance = true;
    if (insuranceInput[0] == 'N' || insuranceInput[0] == 'n')
        rentalInsurance = false;

    RentalContract newContract(driversLicense, vehicleID, startDate, rentalDays,
                               waiverSigned, rentalInsurance);
    return newContract;
}


/**
 * If customer has no RentalContracts, deletes the customer, rebuilds the array,
 * and removes the customer from the CSV. Updates existing RentalContracts for
 * new Customer pointer.
 * @param customer Customer to be deleted.
 * @param numCustomers Number of customers in array before deletion.
 * @param oldCustomerArray Array from which to delete the customer.
 * @param contractArray Array of RentalContracts to check.
 * @param numContracts Number of contracts in RentalContracts array.
 * @return Returns array of size n-1 without the removed customer.
 */
Customer * deleteCustomer(int & numCustomers, Customer oldCustomerArray[],
                          RentalContract contractArray[], int numContracts) {
    cout << "-----|  Delete Customer  |----------------------------" << "\n";
    cout << "Note: Customer must have no current rental contracts.\n\n"
         << "Enter the license number for the customer to delete: ";
    string customerLicense;
    cin >> customerLicense;

    // Check for rental contracts
    for (int i = 0; i < numContracts; i++) {
        if (contractArray[i].getCustomer()->getLicense() == customerLicense) {
            system("cls");
            cout << "-----|  Delete Customer  |-------------------------" << "\n\n";
            cout << "  Unable to delete customer with current rental contract!" << "\n\n";
            system("pause");
            return oldCustomerArray;
        }
    }

    // Find index of customer in customerArray
    int customerIndex;
    for (int i = 0; i < numCustomers; i++) {
        if (oldCustomerArray[i].getLicense() == customerLicense) {
            customerIndex = i;
            i = numCustomers;       // Exit loop when customer is found
        }
    }

    // Build new array without customer to delete
    Customer * newCustomerArray = new Customer[ numCustomers - 1];
    for (int i = 0; i < customerIndex; i++) {
        newCustomerArray[i] = oldCustomerArray[i];
    }
    for (int i = customerIndex+1; i < numCustomers; i++) {
        newCustomerArray[i-1] = oldCustomerArray[i];
    }

    delete[] oldCustomerArray;
    --numCustomers;

    // Overwrite CSV with new array
    ofstream file;
    file.open (CUSTOMER_CSV);
    if (file.is_open()) {
        for (int i = 0; i < numCustomers; i++) {
            file << newCustomerArray[i].getCSVString() << '\n';
        }
        file.close();

        // Acknowledge successful deletion
        system("cls");
        cout << "-----|  Delete Customer  |-------------------------" << "\n\n";
        cout << "Customer deleted successfully." << "\n\n";
        system("pause");
    }
    else {
        cout << "Unable to open " << CUSTOMER_CSV << ".";
    }

    // Update Customer pointer on contracts.
    for (int i = 0; i < numContracts; i++) {
        contractArray[i].findCustomer(newCustomerArray, numCustomers);
    }

    return newCustomerArray;
}


/**
 * If vehicle has no RentalContracts, deletes the vehicle, rebuilds the array,
 * and removes the vehicle from the CSV. Updates existing RentalContracts for
 * new Customer pointer.
 * @param vehicle Vehicle to be deleted.
 * @param numVehicles Number of vehicle in array before deletion.
 * @param oldVehicleArray Array from which to delete the vehicle.
 * @param contractArray Array of RentalContracts to check.
 * @param numContracts Number of contracts in RentalContracts array.
 * @return Returns array of size n-1 without the removed vehicle.
 */
Vehicle * deleteVehicle(int & numVehicles, Vehicle oldVehicleArray[],
                          RentalContract contractArray[], int numContracts) {
    cout << "-----|  Delete Vehicle  |-----------------------------" << "\n";
    cout << "Note: Vehicle must not be currently rented.\n\n"
         << "Enter the vehicle VIN to delete: ";
    string vehicleVIN;
    cin >> vehicleVIN;

    // Check for rental contracts
    for (int i = 0; i < numContracts; i++) {
        if (contractArray[i].getVehicle()->getVIN() == vehicleVIN) {
            cout << "Unable to delete vehicle with current rental contract!"
                 << endl;
            return oldVehicleArray;
        }
    }

    // Find index of vehicle in vehicleArray
    int vehicleIndex;
    for (int i = 0; i < numVehicles; i++) {
        if (oldVehicleArray[i].getVIN() == vehicleVIN) {
            vehicleIndex = i;
            i = numVehicles;       // Exit loop when vehicle is found
        }
    }

    // Build new array without vehicle to delete
    Vehicle * newVehicleArray = new Vehicle[ numVehicles - 1];
    for (int i = 0; i < vehicleIndex; i++) {
        newVehicleArray[i] = oldVehicleArray[i];
    }
    for (int i = vehicleIndex+1; i < numVehicles; i++) {
        newVehicleArray[i-1] = oldVehicleArray[i];
    }

    delete[] oldVehicleArray;
    --numVehicles;

    // Overwrite CSV with new array
    ofstream file;
    file.open (VEHICLE_CSV);
    if (file.is_open()) {
        for (int i = 0; i < numVehicles; i++) {
            file << newVehicleArray[i].getCSVString() << '\n';
        }
        file.close();

        // Acknowledge successful deletion
        system("cls");
        cout << "-----|  Delete Vehicle  |-------------------------" << "\n\n";
        cout << "Vehicle deleted successfully." << "\n\n";
        system("pause");
    }
    else {
        system("cls");
        cout << "-----|  Delete Vehicle  |-------------------------" << "\n\n";
        cout << "Unable to open " << VEHICLE_CSV << "." << "\n\n";
        system("pause");
    }

    // Update Vehicle pointer on contracts for newVehicleArray.
    for (int i = 0; i < numContracts; i++) {
        contractArray[i].findVehicle(newVehicleArray, numVehicles);
    }

    return newVehicleArray;
}


/**
 * Loads a class array with objects created from a CSV file.
 * @tparam T - Class
 * @param filePath - Relative location of CSV file.
 * @param totalItems - Initialized at 0. Used to track array size for later expansion.
 * @param targetArray - Array to fill. Defines output class.
 * @return Returns a class array pointer.
 */
template <class T>
T * loadCSV(string filePath, int & totalItems, T targetArray[]){
    string line;
    ifstream file (filePath);

    // Find how many customers are in the file
    if (file.is_open()) {
        while (getline (file,line)) {
            ++totalItems;
        }
    }
    else {
        cout << "Unable to open " << filePath << "." << endl;
        return new T[0];
    }

    T * newArray = new T[totalItems];

    file.clear();      // Clear end-of-file flag
    file.seekg(0);     // Position to start of file

    if (file.is_open()) {
        for (int i = 0; i < totalItems; i++) {
            getline (file, line);
            newArray[i] = new T(line);
        }
        file.close();

    }
    return newArray;
} // end loadCSV


/**
 * Adds an object to a full array of the same class. Auto-updates Customer/Vehicle
 * pointers in RentalClass array.
 * @tparam T - Any class.
 * @param newObject Object to add to array.
 * @param arrayDimension Number of members in array BEFORE new object is added.
 * @param oldObjectArray Array to add the object to.
 * @return Returns a pointer to a class array of previous size + 1 with the new
 * object added to last position.
 */
template <class T>
T * addObjectToArray(T newObject, int & arrayDimension, T oldObjectArray[], string csvFilePath,
                     RentalContract contractArray[], int numContracts) {
    // Make new array from old array +1 space and load with old array's data
    T * newObjectArray = new T[ arrayDimension + 1];
    for (int i = 0; i < arrayDimension; i++) {
        newObjectArray[i] = oldObjectArray[i];
    }
    // Add new object to last space
    newObjectArray[arrayDimension] = newObject;

    delete[] oldObjectArray;
    ++arrayDimension;

    saveObjectToCSV(newObject, csvFilePath);


    return newObjectArray;
}   // end addObjectToArray


/**
 * Saves an object to a CSV file.
 * @tparam T - Any class with a getCSVString() function that return a CSV formatted string.
 * @param object - Object to be saved at end of CSV file.
 * @param filePath - Relative location of CSV file.
 * @return True if upload successful, false if unsuccessful.
 */
template <class T>
bool saveObjectToCSV(T object, string filePath) {
    bool success = true;

    ofstream file;
    file.open (filePath, ios::app);
    if (file.is_open()) {
        file << object.getCSVString() << "\n";
        file.close();
    }
    else {
        cout << "Unable to open " << VEHICLE_CSV <<". YOUR CHANGES WILL NOT BE SAVED.";
        success = false;
    }

    return success;
}   // end saveObjectToCSV


template <class T>
void updateCSV(T objectArray, int arraySize, string filePath){
    ofstream file;
    file.open (filePath);
    if (file.is_open()) {
        for (int i = 0; i < arraySize; i++) {
            file << objectArray[i].getCSVString() << '\n';
        }file.close();
    }
    else {
        cout << "Unable to open " << filePath <<". YOUR CHANGES WILL NOT BE SAVED.";
    }
}


template <class T>
void displayArray(int totalItems, T array[]) {
    for (int i = 0; i < totalItems; i++) {
        array[i].display();
    }
    cout << endl;
    system("pause");
}
