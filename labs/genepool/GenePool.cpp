#include "GenePool.h"
#include "Query.h"
#include <string>
#include <istream>
#include <sstream>
#include <iostream>

// GenePool Member Functions
GenePool::GenePool(std::istream& stream) {
    std::string line;
    while (std::getline(stream, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::istringstream iss(line);
        std::string name;
        std::string gender;
        std::string mother;
        std::string father;

        // parse by tab separation
        std::getline(iss, name, '\t');
        std::getline(iss, gender, '\t');
        std::getline(iss, mother, '\t');
        std::getline(iss, father, '\t');

        // create a new Person object and add it to the gene pool
        Person* person = new Person();
        person->setName(name);
        person->setGender(gender); // name and gender are straightforward
        if (mother == "???") {
            person->setMother(nullptr);
        } else {
            person->setMother(find(mother));
            find(mother)->setChild(person);
        }
        if (father == "???") {
            person->setFather(nullptr);
        } else {
            person->setFather(find(father));
            find(father)->setChild(person);
        }

        personPool[person->name()] = person;
}
}

GenePool::~GenePool() {
    for (auto i = personPool.begin(); i != personPool.end(); ++i) {
        delete i->second;
    }
}

// List all the people in the database.
std::set<Person*> GenePool::everyone() const {
    std::set<Person*> everyPersons;
    for (auto i = personPool.begin(); i != personPool.end(); ++i) {
        everyPersons.insert(i->second);
    }
    return everyPersons;
}

// Find a person in the database by name.
// Return nullptr if there is no such person.
Person* GenePool::find(const std::string& name) const {
    auto i = personPool.find(name); // use built-in find function
    if (i != personPool.end()) {
        return i->second;
    }
    return nullptr;
}