#ifndef __PUZZLE_H__
#define __PUZZLE_H__

#include <string>
#include <iostream>
#include <cmath>
#include <assert.h>
#include <vector>

#define MAX_STATES 100

using namespace std;


enum heuristicFunction { MISPLACED_TILES, MANHATTAN_DISTANCE };


class Puzzle
{
private:
    // Some variables, such as board string, removed to save space for inefficient algortihms.
    // Perhaps adding some back in would improve A*, which checks toString() when deleting from heap.

    string path;                                                                    // String representation of the moves of the blank tile.
    int pathLength;                                                                 // The length of the path taken to this state.

    int state;                                                                      // Int representation of the current state.
    vector<int> states;                                                             // Int representation of the previous states in the path.

    int fCost;                                                                      // The sum of the heuristic cost and distance from start node.

    int board[3][3];                                                                // Represents the tiles of the board, [rows][columns]
    int goalBoard[3][3];

    int x0, y0;                                                                     // Coordinates of the blank or 0-tile.


    //int hCost;                                                                      // The heuristic estimating the cost from current state to goal state.

public:
    // Constructors.
    Puzzle(string const elements, string const goal);                               // Constructor.
    Puzzle(const Puzzle &p);                                                        // Copy constructor.

    // Public access functions.
    string getPath();                                                               // Returns the path length of the current puzzle.
    int getState();                                                                 // Returns the string of the puzzle state.
    int getPathLength();                                                            // Returns the path taken to the current board state.
    int getFCost();                                                                 // Returns the f-cost of the puzzle.

    // Test for goal.
    bool goalMatch();                                                               // Returns true if puzzle and goal boards match exactly.

    // Blank tile movement.
    bool canMoveLeft(int maxDepth = 0);                                             // Returns true if the blank tile can move left, taking into account max depth.
    bool canMoveUp(int maxDepth = 0);                                               // Returns true if the blank tile can move up, taking into account max depth.
    bool canMoveRight(int maxDepth = 0);                                            // Returns true if the blank tile can move right, taking into account max depth.
    bool canMoveDown(int maxDepth = 0);                                             // Returns true if the blank tile can move down, taking into account max depth.
    Puzzle * move(int x0Change, int y0Change);                                      // Returns new puzzle object with blank tile moved.

    // Efficient search algorithm enablers.
    bool locallyVisited(int state);                                                 // Returns true if the state has been visited in the local path.
    //int hash();                                                                     // Returns the hashed puzzle state.

    // Board state.
    int updateState();                                                              // Converts board state into its integer representation.
    string toString();                                                              // Converts board state into its string representation.
    //void printBoard();                                                              // Outputs the state of the puzzle board.

    // A* functions.
    void updateFCost(heuristicFunction hFunction);                                  // Updates the f-cost of the puzzle.
    int h(heuristicFunction hFunction);                                             // Heuristic function implementation.
};

#endif

