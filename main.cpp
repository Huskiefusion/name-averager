#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <set>
#include <map>
#include <algorithm>
#include "nameEntry.hpp"

using namespace std;

struct SortByValue{
    bool operator()(const pair<char, int>& p1, 
        const pair<char, int>& p2 ){
            return p1.second < p2.second;
    }
};


int main(){
    // read file
    ifstream nameFile("names.csv");
    string line;
    getline(nameFile, line); // clear the formatting line
    vector<NameEntry> maleNameArr(1000); // there are 1000 lines in the csv file
    vector<NameEntry> femaleNameArr(1000); 
    vector<string> fields(5); // for storing fields as we read the csv
    int maxNameSize = 0; // gets updated in the csv read loop

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

        // update maxNameSize
        maxNameSize = (fields[1].size() > maxNameSize) ? fields[1].size():maxNameSize;
        maxNameSize = (fields[3].size() > maxNameSize) ? fields[3].size():maxNameSize;
    }
    
    // the world is my cloyster
    vector<unordered_map<char, int>> letterTable(maxNameSize); // unordered, not sorted
    for(auto nameE: maleNameArr){
        for(int i=0; i < nameE.name.size(); i++){
            letterTable[i][nameE.name[i]]+=nameE.count;
        }
    }

    // Mean of male names
    cout << "--- MEAN NAME ---" << endl;
    for(int i=0; i < maxNameSize; i++){ 
        double totalValue=0, total=0;
        for(auto c: letterTable[i]){
            totalValue += c.first*c.second;
            total += c.second;
        }
        
        cout << (char)(totalValue/total) ;
    }
    cout << endl << endl;

    //Median of male names
    cout << "--- MEDIAN NAME ---" << endl;

    for(int i=0; i < maxNameSize; i++){ 
        vector<pair<char, int>> letterArr(letterTable[i].begin(), letterTable[i].end());
        sort(letterArr.begin(), letterArr.end(), [](pair<char, int> &a, pair<char, int> &b){
            return a.second > b.second;
        });
        cout << letterArr[letterArr.size()/2].first;
    }
    cout << endl << endl;
    return 0;
}