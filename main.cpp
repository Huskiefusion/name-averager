#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "nameEntry.hpp"

using namespace std;



int main(){
    // read file
    ifstream nameFile("names.csv");
    string line;
    getline(nameFile, line); // clear the formatting line
    vector<NameEntry> maleNameArr(1000); // there are 1000 lines in the csv file
    vector<NameEntry> femaleNameArr(1000); 
    vector<string> fields(5); // for storing fields as we read the csv
    while(getline(nameFile, line)){ // read the whole csv file
        stringstream lineStream(line);
        getline(lineStream, line, ',');
        fields[0] = line; // rank
        getline(lineStream, line, ',');
        fields[1] = line; // male name
        getline(lineStream, line, ',');
        fields[2] = line; // male count
        getline(lineStream, line, ',');
        fields[3] = line; // female name
        getline(lineStream, line);
        fields[4] = line; // female count
        try{
            int rank = stoi(fields[0]), mCount = stoi(fields[2]), fCount = stoi(fields[4]);
            // rank goes from 1-1000 so -1 (0-999)
            maleNameArr[rank-1] = NameEntry(rank, fields[1], mCount);
            femaleNameArr[rank-1] = NameEntry(rank, fields[3], fCount);
        }
        catch(exception) {
            throw "stoi() call failed!";
        }
    }
    
    for(auto name : maleNameArr){
        cout << name << endl;
    }
    return 0;
}