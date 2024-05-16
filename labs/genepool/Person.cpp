#include "Person.h"

// Person Member Functions
Person::Person() { // creates empty person :(
    personName = "";
    personGender = Gender::ANY;
    personMother = nullptr;
    personFather = nullptr;
}

const std::string& Person::name()   const {
return personName;
}
Gender             Person::gender() const {
return personGender;
}
Person*            Person::mother() {
return personMother;
}
Person*            Person::father() {
return personFather;
}

void Person::setName(std::string myName) {
    personName = myName;
    return;
}
void Person::setGender(std::string myGender) {
    if (myGender == "male") {
        personGender = Gender::MALE;
    } else if (myGender == "female") {
        personGender = Gender::FEMALE;
    }
}
void Person::setMother(Person* mom) { // all set functions set the pointer passed from genepool. the logic was done there
    personMother = mom;
    return;
}
void Person::setFather(Person* dad) {
    personFather = dad;
    return;
}
void Person::setChild(Person* kid) {
    personChildren.insert(kid);
    return;
}

std::set<Person*> Person::ancestors(PMod pmod) {
    std::set<Person*> myAncestors;
    if (this->personMother != nullptr && (pmod == PMod::ANY || pmod == PMod::MATERNAL)) { // mom side
        myAncestors.insert(this->personMother); // if mom, then add mom and call function again. do same for dad
        std::set<Person*> maternalAncestors = this->personMother->ancestors(PMod::MATERNAL);
        myAncestors.insert(maternalAncestors.begin(), maternalAncestors.end());
    }
    if (this->personFather != nullptr && (pmod == PMod::ANY || pmod == PMod::PATERNAL)) { // dad side
        myAncestors.insert(this->personFather);
        std::set<Person*> paternalAncestors = this->personFather->ancestors(PMod::PATERNAL);
        myAncestors.insert(paternalAncestors.begin(), paternalAncestors.end());
    }
    return myAncestors;
}
std::set<Person*> Person::aunts(PMod pmod, SMod smod) {
    std::set<Person*> myAunts;
    std::set<Person*> parents = this->parents(pmod);
    for (Person* parent : parents) {
        for (Person* sister : parent->sisters(PMod::ANY, smod)) { 
            if (sister != nullptr) {
                myAunts.insert(sister);
            }
        }
    }
    return myAunts;
}
std::set<Person*> Person::brothers(PMod pmod, SMod smod) {
    std::set<Person*> brothers;
    std::set<Person*> mySiblings = this->siblings(pmod, smod);
    for (Person* sibling : mySiblings) {
        if (sibling->gender() == Gender::MALE) { // only add males
            brothers.insert(sibling);
        }
    }
    return brothers;
}
std::set<Person*> Person::children() {
    return personChildren;
}
std::set<Person*> Person::cousins(PMod pmod, SMod smod) {
    std::set<Person*> myCousins; // if maternal, create mom side set. do same for paternal
    if (this->personMother != nullptr && (pmod == PMod::ANY || pmod == PMod::MATERNAL)) { 
        std::set<Person*> momSiblings = this->personMother->siblings(PMod::ANY, smod);
        for (Person* sibling : momSiblings) {
            for (Person* child : sibling->children()) {
                if (child != nullptr) {
                    myCousins.insert(child);
                }
            }
        }
    }
    if (this->personFather != nullptr && (pmod == PMod::ANY || pmod == PMod::PATERNAL)) {
        std::set<Person*> dadSiblings = this->personFather->siblings(PMod::ANY, smod);
        for (Person* sibling : dadSiblings) {
            for (Person* child : sibling->children()) {
                if (child != nullptr) {
                    myCousins.insert(child);
                }
            }
        }
    }
    return myCousins;
}
std::set<Person*> Person::daughters() {
    std::set<Person*> myDaughters;
    for (Person* child : personChildren) {
        if (child != nullptr && child->gender() == Gender::FEMALE) {
            myDaughters.insert(child);
        }
    }
    return myDaughters;
}
std::set<Person*> Person::descendants() {
    std::set<Person*> myDescendants; 
    if (!this->personChildren.empty()) { // if children, call function again
        for (Person* child : personChildren) {
            myDescendants.insert(child);
            std::set<Person*> childDescendants = child->descendants(); // make descendant set for each child
            myDescendants.insert(childDescendants.begin(), childDescendants.end()); // add descendant set to main set
        }
    }
    return myDescendants;
}
std::set<Person*> Person::grandchildren() {
    std::set<Person*> myGrandchildren;
    for (Person* child : personChildren) { // my children
        for (Person* grandchild : child->children()) { // my children children
            if (grandchild != nullptr) {
                myGrandchildren.insert(grandchild); 
            }
        }
    }
    return myGrandchildren;

}
std::set<Person*> Person::granddaughters() {
    std::set<Person*> myGranddaughters;
    std::set<Person*> grandchildren = this->grandchildren();
    for (Person* grandchild : grandchildren) {
        if (grandchild != nullptr && grandchild->gender() == Gender::FEMALE) {
            myGranddaughters.insert(grandchild);
        
        }
    }
    return myGranddaughters;
}
std::set<Person*> Person::grandfathers(PMod pmod) {
    std::set<Person*> myGrandfatherSet;
    Person* myMom = this->mother();
    Person* myDad = this->father();
    if (myMom != nullptr && (pmod == PMod::ANY || pmod == PMod::MATERNAL)) { // IF maternal or any, add mom dad if possible
        if (myMom->father() != nullptr) {
            myGrandfatherSet.insert(myMom->father());
        }
    }
    if (myDad != nullptr && (pmod == PMod::ANY || pmod == PMod::PATERNAL)) { // IF paternal or any, add dad dad if possible
        if (myDad->father() != nullptr) {
            myGrandfatherSet.insert(myDad->father());
        }
    }
    return myGrandfatherSet;
}
std::set<Person*> Person::grandmothers(PMod pmod) {
    std::set<Person*> myGrandmotherSet;
    Person* myMom = this->mother();
    Person* myDad = this->father();
    // check if grandparent is valid and pmod
    if (myMom != nullptr && (pmod == PMod::ANY || pmod == PMod::MATERNAL)) { // IF maternal or any, add mom mom if possible
        if (myMom->mother() != nullptr) {
            myGrandmotherSet.insert(myMom->mother());
        }
    }
    if (myDad != nullptr && (pmod == PMod::ANY || pmod == PMod::PATERNAL)) { // IF paternal or any, add dad mom if possible
        if (myDad->mother() != nullptr) {
            myGrandmotherSet.insert(myDad->mother());
        }
    }
    return myGrandmotherSet;
}
std::set<Person*> Person::grandparents(PMod pmod) {
    std::set<Person*> myGrandparentSet;
    Person* myMom = this->mother();
    Person* myDad = this->father();
    // check if grandparent is valid and pmod
    if (myMom != nullptr && (pmod == PMod::ANY || pmod == PMod::MATERNAL)) { // IF maternal or any, add parents if possible
        if (myMom->mother() != nullptr) {
            myGrandparentSet.insert(myMom->mother());
        }
        if (myMom->father() != nullptr) {
            myGrandparentSet.insert(myMom->father());
        }
    }
    if (myDad != nullptr && (pmod == PMod::ANY || pmod == PMod::PATERNAL)) { // IF paternal or any, add parents if possible
        if (myDad->mother() != nullptr) {
            myGrandparentSet.insert(myDad->mother());
        }
        if (myDad->father() != nullptr) {
            myGrandparentSet.insert(myDad->father());
        }
    }
    return myGrandparentSet;
}
std::set<Person*> Person::grandsons() {
    std::set<Person*> myGrandsons;
    std::set<Person*> grandchildren = this->grandchildren();
    for (Person* grandchild : grandchildren) {
        if (grandchild != nullptr && grandchild->gender() == Gender::MALE) {
            myGrandsons.insert(grandchild);
        
        }
    }
    return myGrandsons;
}
std::set<Person*> Person::nephews(PMod pmod, SMod smod) {
    std::set<Person*> nephews;
    std::set<Person*> Siblings = this->siblings(pmod, smod);
    for (Person* sibling : Siblings) {
        for (Person* son : sibling->sons()) { 
            if (son != nullptr) {
                nephews.insert(son);
            }
        }
    }
    return nephews;
}
std::set<Person*> Person::nieces(PMod pmod, SMod smod) {
    std::set<Person*> nieces;
    std::set<Person*> Siblings = this->siblings(pmod, smod);
    for (Person* sibling : Siblings) {
        for (Person* daughter : sibling->daughters()) { 
            if (daughter != nullptr) {
                nieces.insert(daughter);
            }
        }
    }
    return nieces;
}
std::set<Person*> Person::parents(PMod pmod) {
    std::set<Person*> myParents;
    // check if parent is valid and pmod
    if (this->mother() != nullptr && (pmod == PMod::ANY || pmod == PMod::MATERNAL)) {
        myParents.insert(personMother);
    }
    if (this->father() != nullptr && (pmod == PMod::ANY || pmod == PMod::PATERNAL)) {
        myParents.insert(personFather);
    }
    return myParents;
}
std::set<Person*> Person::siblings(PMod pmod, SMod smod) {
    std::set<Person*> siblings;
    Person* myMom = this->mother();
    Person* myDad = this->father();
    // check if parent is valid, then check if child of parent is half or full
    if (myMom != nullptr && (pmod == PMod::ANY || pmod == PMod::MATERNAL)) { // check if maternal or any
        for (Person* child : myMom->children()) {
            if (child != nullptr && child != this) { // first check if the child is not yourself nor nullptr
                if (smod == SMod::ANY) {
                    siblings.insert(child); // next check if any, full, or half
                } else if (smod == SMod::FULL) { // only add if parents match
                    if (child->father() == this->father() && child->mother() == this->mother() && this->father() != nullptr) {
                        siblings.insert(child);
                    }
                } else if (smod == SMod::HALF) { // only add if mom matches and dad doesnt
                    if (child->mother() == this->mother() && child->father() != this->father()) {
                        siblings.insert(child);
                    }
                }
            }
        }
    }
    if (myDad != nullptr && (pmod == PMod::ANY || pmod == PMod::PATERNAL)) { 
        for (Person* child : myDad->children()) {
            if (child != nullptr && child != this) { // first check if the child is not yourself nor nullptr
                if (smod == SMod::ANY) {
                    siblings.insert(child); // next check if any, full, or half
                } else if (smod == SMod::FULL) { // only add if parents match
                    if (child->father() == this->father() && child->mother() == this->mother() && this->mother() != nullptr) {
                        siblings.insert(child);
                    }
                } else if (smod == SMod::HALF) { // only add if dad matches and mom doesnt
                    if (child->mother() != this->mother() && child->father() == this->father()) {
                        siblings.insert(child);
                    }
                }
            }
        }
    }
    return siblings;
}
std::set<Person*> Person::sisters(PMod pmod, SMod smod) {
    std::set<Person*> sisters;
    std::set<Person*> mySiblings = this->siblings(pmod, smod);
    for (Person* sibling : mySiblings) {
        if (sibling->gender() == Gender::FEMALE) { // only add females
            sisters.insert(sibling);
        }
    }
    return sisters;
}
std::set<Person*> Person::sons() {
    std::set<Person*> sons;
    for (Person* child : personChildren) {
        if (child != nullptr && child->gender() == Gender::MALE) {
            sons.insert(child);
        }
    }
    return sons;
}
std::set<Person*> Person::uncles(PMod pmod, SMod smod) {
    std::set<Person*> uncles;
    std::set<Person*> parents = this->parents(pmod);
    for (Person* parent : parents) {
        for (Person* brother : parent->brothers(PMod::ANY, smod)) { 
            if (brother != nullptr) {
                uncles.insert(brother);
            }
        }
    }
    return uncles;
}