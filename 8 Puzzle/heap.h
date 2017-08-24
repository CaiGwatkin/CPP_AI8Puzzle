//////////////////////////////////////////////
//  Cai Gwatkin                             //
//////////////////////////////////////////////
//  This program reads in numbers from      //
//  text files, sorts adds them to a Heap,  //
//  and sorts them into ascending order     //
//////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

#include "puzzle.h"

using namespace std;


// Heap class with functions specific to finding the number of comparisons when using Heap Sort method
class Heap
{
private:
    vector<Puzzle *> data;
    vector<int> stateSearchData;

public:
    Heap() { };
    ~Heap() { };
    void insert(Puzzle *newElement);
    bool empty();
    int size();
    Puzzle * rootData();
    void deleteRoot();
	int deleteElement(int state);
    void sortDown(int sortIndex = 0);
    void sortUp(int sortIndex);
};

