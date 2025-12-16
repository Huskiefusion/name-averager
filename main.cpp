#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <set>
#include <map>
#include <cassert>
#include <algorithm>
#include "nameEntry.hpp"

using namespace std;

void findAvgName(const int& maxNameSize, const vector<unordered_map<char, int>>& letterTable){
    assert(maxNameSize >= letterTable.size()); // Trying to make a name longer than we have letters for
    for(int i=0; i < maxNameSize; i++){ 
        double totalValue=0, total=0;
        for(auto c: letterTable[i]){
            totalValue += c.first*c.second;
            total += c.second;
        }
        
        cout << (char)(totalValue/total) ;
    }

}

void findMedianName(const int& maxNameSize, const vector<unordered_map<char, int>>& letterTable){
    assert(maxNameSize >= letterTable.size()); // Trying to make a name longer than we have letters for
    for(int i=0; i < maxNameSize; i++){ 
        vector<pair<char, int>> letterArr(letterTable[i].begin(), letterTable[i].end());
        sort(letterArr.begin(), letterArr.end(), [](pair<char, int> &a, pair<char, int> &b){
            return a.second > b.second;
        });
        cout << letterArr[letterArr.size()/2].first;
    }
}

void findModeName(const int& maxNameSize, const vector<unordered_map<char, int>>& letterTable){
    assert(maxNameSize >= letterTable.size()); // Trying to make a name longer than we have letters for
    
    for(int i=0; i < maxNameSize; i++){
        int max=0; char maxLetter='\0';
        for(auto p: letterTable[i]){
            if(p.second > max){
                max=p.second;
                maxLetter=p.first;
            }
        }
        cout << maxLetter;
    }
}


int main(){
    // read file
    ifstream nameFile("names.csv");
    string line;
    getline(nameFile, line); // clear the formatting line
    vector<NameEntry> maleNameArr(1000); // there are 1000 lines in the csv file
    vector<NameEntry> femaleNameArr(1000); 
    vector<string> fields(5); // for storing fields as we read the csv
    int maxNameSize = 0, maxMaleName=0, maxFemaleName=0; // gets updated in the csv read loop

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
        // maxMale
        maxMaleName = (fields[1].size() > maxMaleName) ? fields[1].size():maxMaleName;
        //maxFemale
        maxFemaleName = (fields[3].size() > maxFemaleName) ? fields[3].size():maxFemaleName;
    }
    maxNameSize = (maxFemaleName > maxMaleName) ? maxFemaleName : maxMaleName;
    cout << maxNameSize << ", " << maxMaleName <<", "<<maxFemaleName <<  endl;

    // the world is my cloyster
    vector<unordered_map<char, int>> letterTable(maxNameSize), 
    maleTable(maxMaleName), 
    femaleTable(maxFemaleName);
    // read male names to hash table (and also the merged table)
    for(auto nameE: maleNameArr){
        for(int i=0; i < nameE.name.size(); i++){
            maleTable[i][nameE.name[i]]+=nameE.count;
            letterTable[i][nameE.name[i]]+=nameE.count;
        }
    }
    // read female names to hash table (and also the merged table)
    for(auto nameE: femaleNameArr){
        for(int i=0; i < nameE.name.size(); i++){
            femaleTable[i][nameE.name[i]]+=nameE.count;
            letterTable[i][nameE.name[i]]+=nameE.count;
        }
    }
    

    cout << "--- Generic Name ---" << endl;
    cout << "Mean: ";
    findAvgName(maxNameSize, letterTable);
    cout << endl;
    cout << "Median: ";
    findMedianName(maxNameSize, letterTable);
    cout << endl;
    cout << "Mode: ";
    findModeName(maxNameSize, letterTable);
    cout << endl << endl;

    cout << "--- Male Name ---" << endl;
    cout << "Mean: ";
    findAvgName(maxMaleName, maleTable);
    cout << endl;
    cout << "Median: ";
    findMedianName(maxMaleName, maleTable);
    cout << endl;
    cout << "Mode: ";
    findModeName(maxMaleName, maleTable);
    cout << endl << endl;

    cout << "--- Female Name ---" << endl;
    cout << "Mean: ";
    findAvgName(maxFemaleName, femaleTable);
    cout << endl;
    cout << "Median: ";
    findMedianName(maxFemaleName, femaleTable);
    cout << endl;
    cout << "Mode: ";
    findModeName(maxFemaleName, femaleTable);
    cout << endl << endl;
    return 0;
}