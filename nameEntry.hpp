#pragma once
#include <iostream>

using namespace std;

struct NameEntry {
    // idk if i want to use this?
    int rank, count;
    string name;
    NameEntry(int rank=-1, string name="", int count=-1){
        this->rank=rank;
        this->name=name;
        this->count=count;
    };
};

ostream& operator<<(ostream& lhs, NameEntry& rhs){
    lhs << "{" << rhs.rank << "," << rhs.name << "," << rhs.count << "}";
    return lhs;
}