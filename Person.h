#ifndef FINALPROJECT_PERSON_H
#define FINALPROJECT_PERSON_H

#include <iostream>
#include <string>
#include "Date.h"

using namespace std;

class Person {
protected:
    string firstname;
    string lastname;
    Date birthdate;

public:
    Person() = default; // Default constructor

    string getFirst(){    return firstname;   }
    string getLast(){     return lastname;    }
    Date getDOB(){      return birthdate;   }
};


#endif //FINALPROJECT_PERSON_H
