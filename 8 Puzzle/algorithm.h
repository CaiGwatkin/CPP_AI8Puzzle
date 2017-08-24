
#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

#include <ctime>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <map>
#include "windows.h"


#include "puzzle.h"
#include "heap.h"


const heuristicFunction HEURISTIC_FUNCTION = MANHATTAN_DISTANCE;


struct HashedPuzzle
{
    string strBoard = "";
    bool visited = false;
};


//Function prototypes
bool memoryOverloaded(MEMORYSTATUSEX memInfo);

void moveBFS(Puzzle &puzzle, int xChange, int yChange, queue<Puzzle> &q, int &numOfLocalLoopsAvoided); // For BFS/PDS no vList.
void movePDS(Puzzle &puzzle, int xChange, int yChange, queue<Puzzle> &q, int &numOfLocalLoopsAvoided); // For BFS/PDS no vList.
void moveBFSV(Puzzle &puzzle, int xChange, int yChange, vector<vector<map<int, int>>> &visitedLists, queue<Puzzle> &q);    // For BFS vList.
void movePDSV(Puzzle &puzzle, int xChange, int yChange, vector<vector<map<int, int>>> &visitedLists, queue<Puzzle> &q);    // For PDS vList.
void moveAStar(Puzzle &puzzle, int xChange, int yChange, vector<vector<map<int, int>>> &expandedLists, heuristicFunction heuristic, Heap &heap);   // For A*.

bool visited(int state, map<int, int> &visitedList);
bool visited(int state, int depth, map<int, int> &visitedList);
bool expanded(int state, int depth, map<int, int> &expandedList);

string breadthFirstSearch(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime,
						  int &numOfLocalLoopsAvoided);
string breadthFirstSearch_with_VisitedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength,
										   float &actualRunningTime);
string progressiveDeepeningSearch_No_VisitedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength,
												 float &actualRunningTime, int &numOfLocalLoopsAvoided, int ultimateMaxDepth);
string progressiveDeepeningSearch_with_NonStrict_VisitedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength,
															 float &actualRunningTime, int ultimateMaxDepth);
string aStar_ExpandedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime,
						  int &numOfDeletionsFromMiddleOfHeap, int &numOfLocalLoopsAvoided, int &numOfAttemptedNodeReExpansions,
						  heuristicFunction heuristic);

#endif