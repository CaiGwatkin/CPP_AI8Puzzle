#include "puzzle.h"

using namespace std;


////////////////////////////////////////////////////////
// Constructors.
////////////////////////////////////////////////////////

// Constructor.
// Inputs: initial state, goal state.
Puzzle::Puzzle(string const elements, string const goal)
{
    int n = 0;                                                                  // Used for index of elements of puzzle and goal.
    for (int i = 0; i < 3; i++)                                                 // Itterate through rows of puzzle board.
    {
        for (int j = 0; j < 3; j++)                                             // Itterate through columns of puzzle board.
        {
            board[i][j] = elements[n] - '0';                                    // Initialise board with passed elements.

            if (board[i][j] == 0)                                               // Check if the current position on the board is the blank tile.
            {
                x0 = j;                                                         // Set the x coordinate of the blank tile as the current x coordinate.
                y0 = i;                                                         // Set the y coordinate of the blank tile as the current x coordinate.
            }

            goalBoard[i][j] = goal[n] - '0';                                    // Initialise goal board with passed elements.

            n++;                                                                // Go to next element.
        } 
    }

    path = "";                                                                  // Initialise path as blank string.
    state = stoi(elements);                                                     // Initialise stateString as elements.
    states.push_back(state);                                                    // Add first state in path as initial state.
    pathLength = 0;                                                             // Initialise path length to 0.
    fCost = 0;                                                                  // Initialise f-cost to 0.
}

// Copy constructor.
Puzzle::Puzzle(const Puzzle &p) : path(p.path)
{
    for (int i = 0; i < 3; i++)                                                 // Itterate through rows of board.
    {
        for (int j = 0; j < 3; j++)                                             // Itterate through columns of board.
        {
            board[i][j] = p.board[i][j];                                        // Initialise values of this puzzle's board with values from passed puzzle's board.
            goalBoard[i][j] = p.goalBoard[i][j];                                // Initialise values of this puzzle's goal board with values from passed puzzle's goal board.
        }
    }

    path = p.path;                                                              // Initialise the path string from the passed puzzle.
    states = p.states;                                                          // Copy states to this puzzle.
    state = p.state;                                                            // Initialise the state from the passed puzzle.
    pathLength = p.pathLength;                                                  // Initialise the path length from the passed puzzle.
    fCost = 0;                                                                  // Initialise as 0.
    x0 = p.x0;                                                                  // Initialise x coordinate of blank tile as value from passed puzzle.
    y0 = p.y0;                                                                  // Initialise y coordinate of blank tile as value from passed puzzle.
}


////////////////////////////////////////////////////////
// Public access functions.
////////////////////////////////////////////////////////

// Returns the path taken to the current board state.
string Puzzle::getPath()
{
    return path;                                                                // Return the string stored in variable: path.
}

// Returns the current state of the board.
int Puzzle::getState()
{
    return state;                                                               // Return the int stored in variable: state.
}

// Returns the path length of the current puzzle.
int Puzzle::getPathLength()
{
    return pathLength;                                                          // Return the path length.
}

// Returns the f-cost of the puzzle.
int Puzzle::getFCost()
{
    return fCost;                                                               // Returns the f-cost of the puzzle.
}


////////////////////////////////////////////////////////
// Test for goal.
////////////////////////////////////////////////////////

// Returns true if puzzle and goal boards match exactly.
bool Puzzle::goalMatch()
{
    bool match = true;                                                          // Initialise match to true until proven false.
    
    for (int i = 0; i < 3; i++)                                                 // Itterate through rows of puzzle board.
    {
        for (int j = 0; j < 3; j++)                                             // Itterate through columns of puzzle board.
        {
            if (board[i][j] != goalBoard[i][j])                                 // Check if value of tile is not the same as for the goal
            {
                match = false;                                                  // Puzzle is not a match with goal board.
                break;                                                          // No need to check further.
            }
        }

        if (!match) break;                                                      // If found to not be a match no need to check further.
    }

    return match;                                                               // Return whether the puzzle matches the goal or not.
}


////////////////////////////////////////////////////////
// Blank tile movement.
////////////////////////////////////////////////////////

// Returns true if the blank tile can move left, taking into account max depth.
bool Puzzle::canMoveLeft(int maxDepth)
{
    // TODO: Implement a check for local loop.
    //       So far simple check is to make sure last move wasn't opposite.
    bool notMaxDepth = (pathLength < maxDepth || maxDepth == 0);                // True if not at max depth yet or no max depth.
    bool notOnLeftEdge = (x0 > 0);                                              // True if blank tile on left edge.
    bool notOppositeToLastMove = true;                                          // Initialise to true, as for path length 0 it should be true.
    
    if (pathLength > 0)                                                         // Check if path length more than 0 to ensure only checking correct memory.
    {
        notOppositeToLastMove = (path[pathLength - 1] != 'R');                  // True if last move was right, would mean this move is back to previously visited state.
    }

    return (notMaxDepth && notOnLeftEdge && notOppositeToLastMove);             // Blank tile can move left if not on left edge, not opposite to last move, and max depth not yet reached.
}

// Returns true if the blank tile can move up, taking into account max depth.
bool Puzzle::canMoveUp(int maxDepth)
{
    // TODO: Implement a check for local loop.
    //       So far simple check is to make sure last move wasn't opposite.
    bool notMaxDepth = (pathLength < maxDepth || maxDepth == 0);                // True if not at max depth yet or no max depth.
    bool notOnTopEdge = (y0 > 0);                                               // True if blank tile on top edge.
    bool notOppositeToLastMove = true;                                          // Initialise to true, as for path length 0 it should be true.
    
    if (pathLength > 0)                                                         // Check if path length more than 0 to ensure only checking correct memory.
    {
        notOppositeToLastMove = (path[pathLength - 1] != 'D');                  // True if last move was down, would mean this move is back to previously visited state.
    }

    return (notMaxDepth && notOnTopEdge && notOppositeToLastMove);              // Blank tile can move up if not on top edge, not opposite to last move, and max depth not yet reached.
}

// Returns true if the blank tile can move right, taking into account max depth.
bool Puzzle::canMoveRight(int maxDepth)
{
    // TODO: Implement a check for local loop.
    //       So far simple check is to make sure last move wasn't opposite.
    bool notMaxDepth = (pathLength < maxDepth || maxDepth == 0);                // True if not at max depth yet or no max depth.
    bool notOnRightEdge = (x0 < 2);                                             // True if blank tile on right edge.
    bool notOppositeToLastMove = true;                                          // Initialise to true, as for path length 0 it should be true.

    if (pathLength > 0)                                                         // Check if path length more than 0 to ensure only checking correct memory.
    {
        notOppositeToLastMove = (path[pathLength - 1] != 'L');                  // True if last move was left, would mean this move is back to previously visited state.
    }

    return (notMaxDepth && notOnRightEdge && notOppositeToLastMove);            // Blank tile can move right if not on right edge, not opposite to last move, and max depth not yet reached.
}

// Returns true if the blank tile can move down, taking into account max depth.
bool Puzzle::canMoveDown(int maxDepth)
{
    // TODO: Implement a check for local loop.
    //       So far simple check is to make sure last move wasn't opposite.
    bool notMaxDepth = (pathLength < maxDepth || maxDepth == 0);                // True if not at max depth yet or no max depth.
    bool notOnBottomEdge = (y0 < 2);                                            // True if blank tile on bottom edge.
    bool notOppositeToLastMove = true;                                          // Initialise to true, as for path length 0 it should be true.

    if (pathLength > 0)                                                         // Check if path length more than 0 to ensure only checking correct memory.
    {
        notOppositeToLastMove = (path[pathLength - 1] != 'U');                  // True if last move was up, would mean this move is back to previously visited state.
    }

    return (notMaxDepth && notOnBottomEdge && notOppositeToLastMove);           // Blank tile can move down if not on bottom edge, not opposite to last move, and max depth not yet reached.
}

// Returns new puzzle object with blank tile moved.
// Must check if movement can occur BEFORE calling this function.
// Movement must be EITHER change in x position or change in y position.
Puzzle * Puzzle::move(int xChange, int yChange)
{
    Puzzle *p = new Puzzle(*this);                                              // Create pointer to new copy of current puzzle.

    p->board[y0][x0] = p->board[y0 + yChange][x0 + xChange];                    // Move tile adjacent to blank tile into blank tile's current position.
    p->board[y0 + yChange][x0 + xChange] = 0;                                   // Turn old position of moved tile into blank tile.
    
    p->x0 = p->x0 + xChange;                                                    // Modify the x coordinate of the blank tile to reflect the movement.
    p->y0 = p->y0 + yChange;                                                    // Modify the x coordinate of the blank tile to reflect the movement.
    
    if (xChange == -1)                                                          // Moving blank tile to the left.
    {
        p->path = path + "L";                                                   // Add left to path.
    }
    else if (yChange == -1)                                                     // Moving blank tile up.
    {
        p->path = path + "U";                                                   // Add up to path.
    }
    else if (xChange == 1)                                                      // Moving blank tile to the right.
    {
        p->path = path + "R";                                                   // Add right to path.
    }
    else if (yChange == 1)                                                      // Moving blank tile down.
    {
        p->path = path + "D";                                                   // Add down to path.
    }
    
    p->pathLength = pathLength + 1;                                             // Increment path length to reflect movement.
    p->state = p->updateState();                                                // Update board state.
    p->states.push_back(p->state);                                              // Add the new state to the array of states.

    return p;                                                                   // Return the new puzzle object.
}


////////////////////////////////////////////////////////
// Efficient search algorithm enablers.
////////////////////////////////////////////////////////

// Returns true if the state has been visited in the local path.
// Deals with local loops.
bool Puzzle::locallyVisited(int state)
{
    bool locallyVisited = false;                                                    // Not visited unless found to be visited.

    for (int i = 0; i < states.size() - 1; i++)                                     // Loop through all states.
    {
        if (states[i] == state)                                                     // Check if this state has been locally visited before.
        {
            locallyVisited = true;                                                  // If state strings match it has been locally visited.
            break;
        }
    }

    return locallyVisited;                                                          // True if state has been locally visited.
}

/*// Returns the hashed puzzle state.
int Puzzle::hash()
{
    int hash = 0;

    return hash;
}*/


////////////////////////////////////////////////////////
// Board state.
////////////////////////////////////////////////////////

// Converts board state into its integer representation.
int Puzzle::updateState()
{
    int state = 0;                                                                  // Initilise int of path.
    int multiplier = 100000000;                                                     // Initialise multiplier so that first tile is first digit.

    for (int i = 0; i < 3; i++)                                                     // Itterate through rows of puzzle board.
    {
        for (int j = 0; j < 3; j++)                                                 // Itterate through columns of puzzle board.
        {
            state += board[i][j] * multiplier;                                      // Add value of tile to end of state string.
            multiplier /= 10;                                                       // Increase multiplier 10x.
        }
    }

    return state;                                                                   // Return the state of the board in string form.
}

// Converts board state into its string representation.
string Puzzle::toString()
{
    string boardState = "";                                                         // Initilise string of path as empty string.
    
    for (int i = 0; i < 3; i++)                                                     // Itterate through rows of puzzle board.
    {
        for (int j = 0; j < 3; j++)                                                 // Itterate through columns of puzzle board.
        {
            boardState.insert(boardState.end(), board[i][j] + '0');                 // Add value of tile to end of state string.
        }
    }

    return boardState;                                                              // Return the state of the board in string form.
}

/*// Outputs the state of the puzzle board.
void Puzzle::printBoard()
{
    cout << "board: "<< endl;

    for (int i = 0; i < 3; i++)                                                     // Itterate through rows of puzzle board.
    {
        for (int j = 0; j < 3; j++)                                                 // Itterate through columns of puzzle board.
        {
            cout << endl << "board[" << i << "][" << j << "] = " << board[i][j];    // Output the board location and tile at that location.
        }
    }

    cout << endl;
}*/


////////////////////////////////////////////////////////
// A* functions.
////////////////////////////////////////////////////////

// Updates the f-cost of the puzzle.
void Puzzle::updateFCost(heuristicFunction hFunction)
{
    fCost = h(hFunction) + pathLength;                                          // Use the h-cost and path length to calculate the f-cost.
}

// Heuristic function implementation.
int Puzzle::h(heuristicFunction hFunction)
{
    int sum = 0;                                                                // Initialise sum as zero.
    int h = 0;                                                                  // Initialise heuristic as zero.
    int numOfMisplacedTiles = 0;                                                // Initialise number of misplaced tiles as zero.
    
    switch(hFunction)                                                           // Use the heuristic function type to determine the 
    {
        case MISPLACED_TILES:                                                   // If using misplaced tiles as the heuristic function.
            for (int i = 0; i < 3; i++)                                         // Itterate through rows of boards.
            {
                for (int j = 0; j < 3; j++)                                     // Itterate through columns of boards.
                {
                    if (board[i][j] != 0 && board[i][j] != goalBoard[i][j])     // Check if the tile is the same as the goal board tile, ignore blank tile.
                    {
                        numOfMisplacedTiles++;                                  // If the tiles are different then it is a misplaced tile.
                    }
                }
            }

            h = numOfMisplacedTiles;                                            // Set h as the final number of misplaced tiles.
            break;
                 
        case MANHATTAN_DISTANCE:                                                // If using Manhattan Distance as the heuristic function.
            for (int i = 0; i < 3; i++)                                         // Itterate through rows of puzzle board.
            {
                for (int j = 0; j < 3; j++)                                     // Itterate through columns of puzzle board.
                {
                    int tile = board[i][j];                                     // Get the tile number.

                    if (tile == 0) continue;                                    // Ignore blank tile.

                    bool found = false;                                         // Initialise to show that current tile has not been found in goal board.

                    for (int k = 0; k < 3; k++)                                 // Itterate through rows of puzzle board.
                    {
                        for (int l = 0; l < 3; l++)                             // Itterate through columns of puzzle board.
                        {
                            if (goalBoard[k][l] == tile)                        // Check if correct tile found.
                            {
                                sum += abs(i - k) + abs(j - l);                 // Add the Manhattan Distance of the current tile from the goal tile to sum.
                                found = true;                                   // Current tile has been found in goal board.
                                break;                                          // No need to check further.
                            }
                        }

                        if (found) break;                                       // Break loop if tile found.
                    }
                }
            }
            
            h = sum;                                                            // Set h as the sum of Manhattan Distances.
    };
    
    return h;                                                                   // Return the heuristic value of the puzzle.
}





/*
// Sets the depth of the puzzle.
void Puzzle::setDepth(int d)
{
    depth = d;                                                                  // Make depth the passed integer.
}
*/

/*
// Updates the h-cost of the puzzle.
void Puzzle::updateHCost(heuristicFunction hFunction)
{
    hCost = h(hFunction);                                                       // Use the passed heuristic function to calculate the h-cost.
}


// Gets the h-cost of the puzzle.
int Puzzle::getHCost()
{
    return hCost;                                                               // Returns the h-cost of the puzzle.
}
*/

/*
// Gets the g-cost, or path length, of the puzzle.
int Puzzle::getGCost()
{
    return pathLength;                                                          // Returns the path length of the puzzle.
}
*/




/*
// Returns true if the blank tile can move left.
bool Puzzle::canMoveLeft()
{
    // TODO: Implement a check for local loop.
    //       So far simple check is to make sure last move wasn't opposite.
    bool notOnLeftEdge = (x0 > 0);                                              // True if blank tile on left edge.
    bool notOppositeToLastMove = true;                                          // Initialise to true, as for path length 0 it should be true.
    
    if (pathLength > 0)                                                         // Check if path length more than 0 to ensure only checking correct memory.
    {
        notOppositeToLastMove = (path[pathLength - 1] != 'R');                  // True if last move was right, would mean this move is back to previously visited state.
    }

    return (notOnLeftEdge && notOppositeToLastMove);                            // Blank tile can move left if not on left edge and not opposite to last move.
}


// Returns true if the blank tile can move up.
bool Puzzle::canMoveUp()
{
    // TODO: Implement a check for local loop.
    //       So far simple check is to make sure last move wasn't opposite.
    bool notOnTopEdge = (y0 > 0);                                               // True if blank tile on top edge.
    bool notOppositeToLastMove = true;                                          // Initialise to true, as for path length 0 it should be true.
    
    if (pathLength > 0)                                                         // Check if path length more than 0 to ensure only checking correct memory.
    {
        notOppositeToLastMove = (path[pathLength - 1] != 'D');                  // True if last move was down, would mean this move is back to previously visited state.
    }

    return (notOnTopEdge && notOppositeToLastMove);                             // Blank tile can move up if not on top edge and not opposite to last move.
}


// Returns true if the blank tile can move right.
bool Puzzle::canMoveRight()
{
    // TODO: Implement a check for local loop.
    //       So far simple check is to make sure last move wasn't opposite.
    bool notOnRightEdge = (x0 < 2);                                             // True if blank tile on right edge.
    bool notOppositeToLastMove = true;                                          // Initialise to true, as for path length 0 it should be true.

    if (pathLength > 0)                                                         // Check if path length more than 0 to ensure only checking correct memory.
    {
        notOppositeToLastMove = (path[pathLength - 1] != 'L');                  // True if last move was left, would mean this move is back to previously visited state.
    }

    return (notOnRightEdge && notOppositeToLastMove);                           // Blank tile can move right if not on right edge and not opposite to last move.
}


// Returns true if the blank tile can move down.
bool Puzzle::canMoveDown()
{
    // TODO: Implement a check for local loop.
    //       So far simple check is to make sure last move wasn't opposite.
    bool notOnBottomEdge = (y0 < 2);                                            // True if blank tile on bottom edge.
    bool notOppositeToLastMove = true;                                          // Initialise to true, as for path length 0 it should be true.

    if (pathLength > 0)                                                         // Check if path length more than 0 to ensure only checking correct memory.
    {
        notOppositeToLastMove = (path[pathLength - 1] != 'U');                  // True if last move was up, would mean this move is back to previously visited state.
    }

    return (notOnBottomEdge && notOppositeToLastMove);                          // Blank tile can move down if not on bottom edge and not opposite to last move.
}*/


///////////////////////////////////////////////



/*
// Returns new puzzle object with blank tile moved to the left.
Puzzle * Puzzle::moveLeft()
{
    Puzzle *p = new Puzzle(*this);                                              // Create pointer to new copy of current puzzle.
    
    if (canMoveLeft())                                                          // Ensure blank tile can move to the left.
    {
        p->board[y0][x0] = p->board[y0][x0-1];                                  // Move tile to the left of the blank tile into the blank tile's current location.
        p->board[y0][x0-1] = 0;                                                 // Turn old position of moved tile into blank tile.
        
        p->x0--;                                                                // Decrement the x coordinate of the blank tile to reflect the movement.
        p->path = path + "L";                                                   // Add left to path.
        p->pathLength = pathLength + 1;                                         // Increment path length to reflect movement.
        p->depth = depth + 1;                                                   // Increment depth to reflect new depth in search tree.
    }

    p->strBoard = p->toString();                                                // Update string of board state.
    p->states.push_back(p->toString());                                        // Add the new state to the array of states.

    return p;                                                                   // Return the new puzzle object.
}


// Returns new puzzle object with blank tile moved up.
Puzzle * Puzzle::moveUp()
{
    Puzzle *p = new Puzzle(*this);                                              // Create pointer to new copy of current puzzle.
    
    if (canMoveUp())                                                            // Ensure blank tile can move up.
    {
        p->board[y0][x0] = p->board[y0-1][x0];                                  // Move tile above the blank tile into the blank tile's current location.
        p->board[y0-1][x0] = 0;                                                 // Turn old position of moved tile into blank tile.
        
        p->y0--;                                                                // Decrement the y coordinate of the blank tile to reflect the movement.
        p->path = path + "U";                                                   // Add up to path.
        p->pathLength = pathLength + 1;                                         // Increment path length to reflect movement.
        p->depth = depth + 1;                                                   // Increment depth to reflect new depth in search tree.
    }

    p->strBoard = p->toString();                                                // Update string of board state.
    p->states.push_back(p->toString());                                        // Add the new state to the array of states.
    
    return p;                                                                   // Return the new puzzle object.
}


// Returns new puzzle object with blank tile moved to the right.
Puzzle * Puzzle::moveRight()
{
    Puzzle *p = new Puzzle(*this);                                              // Create pointer to new copy of current puzzle.
    
    if (canMoveRight())                                                         // Ensure blank tile can move to the right.
    {
        p->board[y0][x0] = p->board[y0][x0+1];                                  // Move tile to the right of the blank tile into the blank tile's current location.
        p->board[y0][x0+1] = 0;                                                 // Turn old position of moved tile into blank tile.
        
        p->x0++;                                                                // Increment the x coordinate of the blank tile to reflect the movement.
        p->path = path + "R";                                                   // Add right to path.
        p->pathLength = pathLength + 1;                                         // Increment path length to reflect movement.
        p->depth = depth + 1;                                                   // Increment depth to reflect new depth in search tree.
    }
    
    p->strBoard = p->toString();                                                // Update string of board state.
    p->states.push_back(p->toString());                                        // Add the new state to the array of states.
    
    return p;                                                                   // Return the new puzzle object.
}


// Returns new puzzle object with blank tile moved down.
Puzzle * Puzzle::moveDown()
{
    Puzzle *p = new Puzzle(*this);                                              // Create pointer to new copy of current puzzle.
    
    if (canMoveDown())                                                          // Ensure blank tile can move down.
    {
        p->board[y0][x0] = p->board[y0+1][x0];                                  // Move tile below the blank tile into the blank tile's current location.
        p->board[y0+1][x0] = 0;                                                 // Turn old position of moved tile into blank tile.
        
        p->y0++;                                                                // Increment the y coordinate of the blank tile to reflect the movement.
        p->path = path + "D";                                                   // Add down to path.
        p->pathLength = pathLength + 1;                                         // Increment path length to reflect movement.
        p->depth = depth + 1;                                                   // Increment depth to reflect new depth in search tree.
    }

    p->strBoard = p->toString();                                                // Update string of board state.
    p->states.push_back(p->toString());                                        // Add the new state to the array of states.
    
    return p;                                                                   // Return the new puzzle object.
}
*/


/*
// Gets the depth of the puzzle.
int Puzzle::getDepth()
{
    return depth;                                                               // Returns the depth of the puzzle.
}*/



/////////////////////////////////////////////////////



