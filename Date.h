#ifndef FINALPROJECT_DATE_H
#define FINALPROJECT_DATE_H

#include <iostream>
#include <string>

using namespace std;

class Date {
protected:
    string months[13] = {"", "Jan", "Feb", "Mar","Apr",
                         "May", "Jun", "Jul","Aug",
                         "Sep", "Oct", "Nov", "Dec"};
    int daysInMonth[13] = {0, 31, 28, 31, 30, 31, 30,
                           31, 31, 30, 31, 30, 31};
public:
    // Variables
    int day;
    int month;
    int year;

    // Constructors
    Date() = default;
    Date(int month, int day, int year);
    Date(string month, int day, int year);
    Date(string dateString);
    Date(Date &date);
    ~Date() = default;

    // Operator functions
    Date operator+ (Date date2);
    Date operator- (Date date2);

    // Member functions
    string getString();
};


Date::Date(int month, int day, int year) {
    this-> day = day;
    this-> month = month;
    this-> year = year;

    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0)
                ++daysInMonth[2];
        } else {
            ++daysInMonth[2];
        }
    }
}


Date::Date(string month, int day, int year) {
    this-> day = day;
    for( int i = 1; i <= 12; i++) {
        if(month == months[i])
            this-> month = i;
    }
    this-> year = year;

    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0)
                ++daysInMonth[2];
        } else {
            ++daysInMonth[2];
        }
    }
}


/**
 * Constructor to let class parse a date from a string.
 * @param dateString Date in format MM/DD/YYYY or ctime string
 */
Date::Date(string dateString) {
    // Determine string format
    if (dateString.length() > 10) {
        // ctime string
        day = stoi(dateString.substr(8,2));

        string stringMonth = dateString.substr(4, 3);
        for (int i = 1; i <= 12; i++) {
            if (stringMonth == months[i])
                month = i;
        }

        year = stoi(dateString.substr(20,4));
    }
    else {
        // DD/MM/YYYY string
        month = stoi(dateString.substr(0,dateString.find('/')));
        dateString = dateString.substr(dateString.find('/')+1);
        day = stoi(dateString.substr(0,dateString.find('/')));
        dateString = dateString.substr(dateString.find('/')+1);
        year = stoi(dateString);
    }
}   // end Date(string dateString) constructor

Date::Date(Date &date){
    this-> day = date.day;
    this-> month = date.month;
    this-> year = date.year;
}

// + operator returns a Date made from the sums of the two dates being added
Date Date::operator+(Date date2) {
    int sumDay = day+date2.day;
    int sumMonth = month+date2.month;
    int sumYear = year+date2.year;

    // Handle overflows in days or months
    while ( sumDay > daysInMonth[sumMonth] ) {
        sumDay -= daysInMonth[month];
        ++sumMonth;

        if ( sumMonth > 12 ) {
            sumMonth -= 12;
            ++sumYear;
        }
    }

    Date sumDate(sumMonth, sumDay, sumYear);
    return sumDate;
}

// - operator returns a Date with member variables of date1.var - date2.var
Date Date::operator-(Date date2) {
    int diffDay = day-date2.day;
    int diffMonth = month-date2.month;
    int diffYear = year-date2.year;

    if ( diffDay < 0 ) {
        diffDay += daysInMonth[month-1];
        --diffMonth;
    }

    if ( diffMonth < 0 ) {
        diffMonth += 12;
    }

    Date diffDate(diffMonth, diffDay,diffYear);
    return diffDate;
}

/**
 *
 * @return string in the format MM/DD/YYYY
 */
string Date::getString() {
    string dateString;

    if (month < 10)
        dateString += "0";
    dateString += to_string(month) + "/";

    if (day < 10)
        dateString += "0";
    dateString += to_string(day) + "/";

    dateString += to_string(year);

    return dateString;
}

#endif //FINALPROJECT_DATE_H
