#include "algorithm.h"


using namespace std;


///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  Breadth-First Search 
//
// Move Generator:  
//
////////////////////////////////////////////////////////////////////////////////////////////
string breadthFirstSearch(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength,
                          float &actualRunningTime, int &numOfLocalLoopsAvoided)
{
    bool solutionFound = false;                                                             // True when the solution is found.
    string path = "";                                                                       // Stores the path of the solution.
    clock_t startTime;                                                                      // Stores the start time of the algorithm.
    queue<Puzzle> q;                                                                        // Initialise queue of puzzles.

    MEMORYSTATUSEX memInfo;                                                                 // Initialise memory information variable.
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);                                              // Ensure correct length.

    maxQLength = 0;                                                                         // Initialise max length of queue to 0.
    numOfStateExpansions = 0;                                                               // Initialise number of state expansions to 0.


    startTime = clock();                                                                    // Start timing the algorithm.

    q.emplace(Puzzle(initialState, goalState));                                             // Add initial puzzle state to end of queue.

    while (!solutionFound && !q.empty())                                                    // Loop while no solution found and queue is not empty.
    {
        Puzzle puzzle = q.front();                                                          // Get the first element in queue.
        q.pop();                                                                            // Remove element from queue.

        if (puzzle.goalMatch())                                                             // Check if puzzle is in goal state.
        {
            path = puzzle.getPath();                                                        // Save path to goal.
            solutionFound = true;                                                           // Solution has been found.
            break;
        }
        else                                                                                // Perform state expansion as goal not found.
        {
            numOfStateExpansions++;                                                         // State expansion occurring, increment.
        }

        if (puzzle.canMoveLeft())                                                           // Check if blank tile can move left.
        {
            moveBFS(puzzle, -1, 0, q, numOfLocalLoopsAvoided);                              // Create puzzle and add to queue if not locally visited.
        }

        if (puzzle.canMoveUp())                                                             // Check if blank tile can move up.
        {
            moveBFS(puzzle, 0, -1, q, numOfLocalLoopsAvoided);                              // Create puzzle and add to queue if not locally visited.
        }

        if (puzzle.canMoveRight())                                                          // Check if blank tile can move right.
        {
            moveBFS(puzzle, 1, 0, q, numOfLocalLoopsAvoided);                               // Create puzzle and add to queue if not locally visited.
        }

        if (puzzle.canMoveDown())                                                           // Check if blank tile can move down.
        {
            moveBFS(puzzle, 0, 1, q, numOfLocalLoopsAvoided);                               // Create puzzle and add to queue if not locally visited.
        }

        int qLength = q.size();                                                             // Get the size of the queue after state expansion.
        if (qLength > maxQLength)                                                           // Check if current queue is larger than max queue length so far.
        {
            maxQLength = qLength;                                                           // Save new max queue length as current queue size.
        }

        if (memoryOverloaded(memInfo))                                                      // Check if memory overloaded.
        {
            actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);              // Save running time of algorithm.
            return "memory overload";                                                       // Stop algorithm and return no solution due to memory overload.
        }
    }

    actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);                      // Save running time of algorithm.

    return path;
}


///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  Breadth-First Search with VisitedList
//
// Move Generator:  
//
////////////////////////////////////////////////////////////////////////////////////////////
string breadthFirstSearch_with_VisitedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength,
                                           float &actualRunningTime)
{
    bool solutionFound = false;                                                             // True when the solution is found.
    string path = "";                                                                       // Stores the path of the solution.
    clock_t startTime;                                                                      // Stores the start time of the algorithm.
    queue<Puzzle> q;                                                                        // Initialise queue of puzzles.

    map<int, vector<vector<map<int, int>>>> visitedLists;                                   // Stores non-strict expanded lists.
    for (int i = 0; i < 9; i++)                                                             // Set up empty expanded lists.
    {
        pair<map<int, vector<vector<map<int, int>>>>::iterator, bool> mapPair =
            visitedLists.emplace(i, vector<vector<map<int, int>>>(9, vector<map<int, int>>(9, map<int, int>())));   // Need 9 entries in each level (for each of the possible first 3 digits of state).
    }

    MEMORYSTATUSEX memInfo;                                                                 // Initialise memory information variable.
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);                                              // Ensure correct length.

    maxQLength = 0;                                                                         // Initialise max length of queue to 0.
    numOfStateExpansions = 0;                                                               // Initialise number of state expansions to 0.


    startTime = clock();                                                                    // Start timing the algorithm.

    q.emplace(Puzzle(initialState, goalState));                                             // Add initial puzzle state to end of queue.

    while (!solutionFound && !q.empty())                                                    // Loop while no solution found and queue is not empty.
    {
        Puzzle puzzle = q.front();                                                          // Get the first element in queue.
        q.pop();                                                                            // Remove element from queue.

        if (puzzle.goalMatch())                                                             // Check if puzzle is in goal state.
        {
            path = puzzle.getPath();                                                        // Save path to goal.
            solutionFound = true;                                                           // Solution has been found.
            break;
        }
        else                                                                                // Perform state expansion as goal not found.
        {
            numOfStateExpansions++;                                                         // State expansion occurring, increment.
        }

        int mapKey = puzzle.getState() / 100000000;                                         // Get the key of the vector of vectors of maps.

        if (puzzle.canMoveLeft())                                                           // Check if blank tile can move left.
        {
            moveBFSV(puzzle, -1, 0, visitedLists.at(mapKey), q);                            // Create puzzle and add to queue if not locally visited.
        }

        if (puzzle.canMoveUp())                                                             // Check if blank tile can move up.
        {
            moveBFSV(puzzle, 0, -1, visitedLists.at(mapKey), q);                            // Create puzzle and add to queue if not locally visited.
        }

        if (puzzle.canMoveRight())                                                          // Check if blank tile can move right.
        {
            moveBFSV(puzzle, 1, 0, visitedLists.at(mapKey), q);                             // Create puzzle and add to queue if not locally visited.
        }

        if (puzzle.canMoveDown())                                                           // Check if blank tile can move down.
        {
            moveBFSV(puzzle, 0, 1, visitedLists.at(mapKey), q);                             // Create puzzle and add to queue if not locally visited.
        }

        int qLength = q.size();                                                             // Get the size of the queue after state expansion.
        if (qLength > maxQLength)                                                           // Check if current queue is larger than max queue length so far.
        {
            maxQLength = qLength;                                                           // Save new max queue length as current queue size.
        }

        if (memoryOverloaded(memInfo))                                                      // Check if memory overloaded.
        {
            actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);              // Save running time of algorithm.
            return "memory overload";                                                       // Stop algorithm and return no solution due to memory overload.
        }
    }

    actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);                      // Save running time of algorithm.

    return path;
}

///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  
//
// Move Generator:  
//
////////////////////////////////////////////////////////////////////////////////////////////
string progressiveDeepeningSearch_No_VisitedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength,
                                                 float &actualRunningTime, int &numOfLocalLoopsAvoided, int ultimateMaxDepth)
{
    int maxDepth = 1;                                                                       // The maximum depth the algorithm will search.
    bool solutionFound = false;                                                             // True when the solution is found.
    string path = "";                                                                       // Stores the path of the solution.
    clock_t startTime;                                                                      // Stores the start time of the algorithm.
    queue<Puzzle> q;                                                                        // Initialise queue of puzzles.

    MEMORYSTATUSEX memInfo;                                                                 // Initialise memory information variable.
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);                                              // Ensure correct length.

    maxQLength = 0;                                                                         // Initialise max length of queue to 0.
    numOfStateExpansions = 0;                                                               // Initialise number of state expansions to 0.


    startTime = clock();                                                                    // Start timing the algorithm.

    q.push(Puzzle(initialState, goalState));                                                // Add initial puzzle state to queue.

    while (!solutionFound)                                                                  // Loop while no solution found and queue is not empty.
    {
        if (q.empty() && maxDepth < ultimateMaxDepth)                                       // If queue is empty, current depth search complete.
        {
            maxDepth++;                                                                     // Increment max depth of search.
            q.push(Puzzle(initialState, goalState));                                        // Add initial puzzle state to queue.
        }
        else if (maxDepth == ultimateMaxDepth)                                              // Check if ultimate max depth reached.
        {
            return "ultimate max depth reached";                                            // Stop algortihm and return ultimate max depth reached.
        }

        Puzzle puzzle = q.front();                                                          // Get the first element in queue.
        q.pop();                                                                            // Remove element from queue.

        if (puzzle.goalMatch())                                                             // Check if puzzle is in goal state.
        {
            path = puzzle.getPath();                                                        // Save path to goal.
            solutionFound = true;                                                           // Solution has been found.
            break;
        }
        else                                                                                // Perform state expansion as goal not found.
        {
            numOfStateExpansions++;                                                         // State expansion occurring, increment.
        }

        if (puzzle.canMoveDown(maxDepth))                                                   // Check if blank tile can move down.
        {
            movePDS(puzzle, 0, 1, q, numOfLocalLoopsAvoided);                               // Create puzzle and add to queue if not locally visited.
        }

        if (puzzle.canMoveRight(maxDepth))                                                  // Check if blank tile can move right.
        {
            movePDS(puzzle, 1, 0, q, numOfLocalLoopsAvoided);                               // Create puzzle and add to queue if not locally visited.
        }

        if (puzzle.canMoveUp(maxDepth))                                                     // Check if blank tile can move up.
        {
            movePDS(puzzle, 0, -1, q, numOfLocalLoopsAvoided);                              // Create puzzle and add to queue if not locally visited.
        }

        if (puzzle.canMoveLeft(maxDepth))                                                   // Check if blank tile can move left.
        {
            movePDS(puzzle, -1, 0, q, numOfLocalLoopsAvoided);                              // Create puzzle and add to queue if not locally visited.
        }

        int qLength = q.size();                                                             // Get the size of the queue after state expansion.
        if (qLength > maxQLength)                                                           // Check if current queue is larger than max queue length so far.
        {
            maxQLength = qLength;                                                           // Save new max queue length as current queue size.
        }

        if (memoryOverloaded(memInfo))                                                      // Check if memory overloaded.
        {
            actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);              // Save running time of algorithm.
            return "memory overload";                                                       // Stop algorithm and return no solution due to memory overload.
        }
    }

    actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);                      // Save running time of algorithm.

    return path;
}
    



///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  
//
// Move Generator:  
//
////////////////////////////////////////////////////////////////////////////////////////////
string progressiveDeepeningSearch_with_NonStrict_VisitedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength,
                                                             float &actualRunningTime, int ultimateMaxDepth)
{
    int maxDepth = 1;                                                                       // The maximum depth the algorithm will search.
    bool solutionFound = false;                                                             // True when the solution is found.
    string path = "";                                                                       // Stores the path of the solution.
    clock_t startTime;                                                                      // Stores the start time of the algorithm.
    queue<Puzzle> q;                                                                        // Initialise queue of puzzles.

    map<int, vector<vector<map<int, int>>>> visitedLists;                                   // Stores non-strict expanded lists.
    for (int i = 0; i < 9; i++)                                                             // Set up empty expanded lists.
    {
        pair<map<int, vector<vector<map<int, int>>>>::iterator, bool> mapPair =
            visitedLists.emplace(i, vector<vector<map<int, int>>>(9, vector<map<int, int>>(9, map<int, int>())));   // Need 9 entries in each level (for each of the possible first 3 digits of state).
    }

    MEMORYSTATUSEX memInfo;                                                                 // Initialise memory information variable.
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);                                              // Ensure correct length.

    maxQLength = 0;                                                                         // Initialise max length of queue to 0.
    numOfStateExpansions = 0;                                                               // Initialise number of state expansions to 0.


    startTime = clock();                                                                    // Start timing the algorithm.

    q.emplace(Puzzle(initialState, goalState));                                             // Add initial puzzle state to end of queue.

    while (!solutionFound)                                                                  // Loop while no solution found and queue is not empty.
    {
        if (q.empty() && maxDepth < ultimateMaxDepth)                                       // If queue is empty, current depth search complete.
        {
            maxDepth++;                                                                     // Increment max depth of search.

            visitedLists.clear();                                                           // Reset map.
            for (int i = 0; i < 9; i++)                                                     // Set up empty expanded lists.
            {
                pair<map<int, vector<vector<map<int, int>>>>::iterator, bool> mapPair =
                    visitedLists.emplace(i, vector<vector<map<int, int>>>(9, vector<map<int, int>>(9, map<int, int>())));   // Need 9 entries in each level (for each of the possible first 3 digits of state).
            }

            q.push(Puzzle(initialState, goalState));                                        // Add initial puzzle state to queue.
        }
        else if (maxDepth == ultimateMaxDepth)                                              // Check if ultimate max depth reached.
        {
            return "ultimate max depth reached";                                            // Stop algortihm and return ultimate max depth reached.
        }

        Puzzle puzzle = q.front();                                                          // Get the first element in queue.
        q.pop();                                                                            // Remove element from queue.

        if (puzzle.goalMatch())                                                             // Check if puzzle is in goal state.
        {
            path = puzzle.getPath();                                                        // Save path to goal.
            solutionFound = true;                                                           // Solution has been found.
            break;
        }
        else                                                                                // Perform state expansion as goal not found.
        {
            numOfStateExpansions++;                                                         // State expansion occurring, increment.
        }

        int mapKey = puzzle.getState() / 100000000;                                         // Get the key of the vector of vectors of maps.

        if (puzzle.canMoveDown(maxDepth))                                                   // Check if blank tile can move down.
        {
            movePDSV(puzzle, 0, 1, visitedLists.at(mapKey), q);                             // Create puzzle and add to queue if not locally visited.
        }

        if (puzzle.canMoveRight(maxDepth))                                                  // Check if blank tile can move right.
        {
            movePDSV(puzzle, 1, 0, visitedLists.at(mapKey), q);                             // Create puzzle and add to queue if not locally visited.
        }

        if (puzzle.canMoveUp(maxDepth))                                                     // Check if blank tile can move up.
        {
            movePDSV(puzzle, 0, -1, visitedLists.at(mapKey), q);                            // Create puzzle and add to queue if not locally visited.
        }

        if (puzzle.canMoveLeft(maxDepth))                                                   // Check if blank tile can move left.
        {
            movePDSV(puzzle, -1, 0, visitedLists.at(mapKey), q);                            // Create puzzle and add to queue if not locally visited.
        }

        int qLength = q.size();                                                             // Get the size of the queue after state expansion.
        if (qLength > maxQLength)                                                           // Check if current queue is larger than max queue length so far.
        {
            maxQLength = qLength;                                                           // Save new max queue length as current queue size.
        }

        if (memoryOverloaded(memInfo))                                                      // Check if memory overloaded.
        {
            actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);              // Save running time of algorithm.
            return "memory overload";                                                       // Stop algorithm and return no solution due to memory overload.
        }
    }

    actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);                      // Save running time of algorithm.

    return path;
}
    

string aStar_ExpandedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime,
                          int &numOfDeletionsFromMiddleOfHeap, int &numOfLocalLoopsAvoided, int &numOfAttemptedNodeReExpansions,
                          heuristicFunction heuristic)
{
    bool solutionFound = false;                                                             // True when the solution is found.
    string path = "";                                                                       // Stores the path of the solution.
    clock_t startTime;                                                                      // Stores the start time of the algorithm.
    Heap heap;                                                                              // Initialise heap of puzzles.

    map<int, vector<vector<map<int, int>>>> expandedLists;                                  // Stores non-strict expanded lists.
    for (int i = 0; i < 9; i++)                                                             // Set up empty expanded lists.
    {
        pair<map<int, vector<vector<map<int, int>>>>::iterator, bool> mapPair =
            expandedLists.emplace(i, vector<vector<map<int, int>>>(9, vector<map<int, int>>(9, map<int, int>())));  // Need 9 entries in each level (for each of the possible first 3 digits of state).
    }

    MEMORYSTATUSEX memInfo;                                                                 // Initialise memory information variable.
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);                                              // Ensure correct length.

    numOfDeletionsFromMiddleOfHeap = 0;                                                     // Initialise the number of mid-heap deletions to 0.
    numOfAttemptedNodeReExpansions = 0;
    maxQLength = 0;                                                                         // Initialise max length of heap to 0.
    numOfStateExpansions = 0;                                                               // Initialise number of state expansions to 0.


    startTime = clock();                                                                    // Start timing the algorithm.

    Puzzle * firstPuzzle = new Puzzle(initialState, goalState);                             // Create first puzzle.
    firstPuzzle->updateFCost(heuristic);                                                    // Get the f-cost of the puzzle.
    heap.insert(firstPuzzle);                                                               // Add initial puzzle state to heap.
    while (!solutionFound && !heap.empty())                                                 // Loop while no solution found and heap is not empty.
    {
        Puzzle * puzzle = heap.rootData();                                                  // Get the first element in heap.
        heap.deleteRoot();                                                                  // Remove element from heap.

        int state = puzzle->getState();                                                     // Get the state of the puzzle. 

        if (puzzle->goalMatch())                                                            // Check if puzzle is in goal state.
        {
            path = puzzle->getPath();                                                       // Save path to goal.
            delete puzzle;                                                                  // Free memory.
            solutionFound = true;                                                           // Solution has been found.

            break;
        }
        else                                                                                // To perform state expansion as goal not found.
        {
            //int depth = puzzle->getPathLength();                                            // Get the depth of the puzzle.
            int mapKey = state / 100000000;                                                 // Get the key of the vector of vectors of maps.
            int listIndex = (state / 10000000) % 10;                                        // Get the index of the vector of maps.
            int mapIndex = (state / 1000000) % 10;                                          // Get the index of the expanded list map to add the state to.

            // For non-strict expanded list, change 0 to depth.
            pair<map<int, int>::iterator, bool> mapPair = expandedLists.at(mapKey).at(listIndex).at(mapIndex).emplace(state, 0);    // Add state to expanded list.

            // Below is for non-strict expanded list.
            /*if (!get<1>(mapPair))                                                           // If there is already an element in the map with the current state.
            {
                if (depth < get<0>(mapPair)->second)                                        // Only expand if new depth less than last 
                {
                    get<0>(mapPair)->second = depth;                                        // Update depth.
                    numOfAttemptedNodeReExpansions++;
                }
                else
                {
                    continue;                                                               // Don't expand state
                }
            }*/

            numOfDeletionsFromMiddleOfHeap += heap.deleteElement(state);                    // Remove any puzzles with the same state from the heap.
            numOfStateExpansions++;                                                         // State expansion occurring, increment.
        }

        int mapKey = state / 100000000;                                                     // Get the key of the vector of vectors of maps.

        if (puzzle->canMoveLeft())                                                          // Check if blank tile can move left.
        {
            moveAStar(*puzzle, -1, 0, expandedLists.at(mapKey), heuristic, heap);           // Create new puzzle and add to heap if applicable.
        }

        if (puzzle->canMoveUp())                                                            // Check if blank tile can move up.
        {
            moveAStar(*puzzle, 0, -1, expandedLists.at(mapKey), heuristic, heap);           // Create new puzzle and add to heap if applicable.
        }

        if (puzzle->canMoveRight())                                                         // Check if blank tile can move right.
        {
            moveAStar(*puzzle, 1, 0, expandedLists.at(mapKey), heuristic, heap);            // Create new puzzle and add to heap if applicable.
        }

        if (puzzle->canMoveDown())                                                          // Check if blank tile can move down.
        {
            moveAStar(*puzzle, 0, 1, expandedLists.at(mapKey), heuristic, heap);            // Create new puzzle and add to heap if applicable.
        }

        delete puzzle;                                                                      // Free memory.

        int heapLength = heap.size();                                                       // Get the size of the heap after state expansion.
        if (heapLength > maxQLength)                                                        // Check if current heap is larger than max queue length so far.
        {
            maxQLength = heapLength;                                                        // Save new max queue length as current heap size.
        }


        if (memoryOverloaded(memInfo))                                                      // Check if memory overloaded.
        {
            actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);              // Save running time of algorithm.
            return "memory overload";                                                       // Stop algorithm and return no solution due to memory overload.
        }
    }

    actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);                      // Save running time of algorithm.

    return path;        
}

// Creates puzzle and adds to queue if not locally visited.
// For BFS and PDS with no visited list.
void moveBFS(Puzzle &puzzle, int xChange, int yChange, queue<Puzzle> &q, int &numOfLocalLoopsAvoided)
{
    Puzzle * newPuzzle = puzzle.move(xChange, yChange);                                     // Create the new puzzle.

    if (!puzzle.locallyVisited(newPuzzle->getState()))                                      // Check if puzzle locally visited.
    {
        q.emplace(*newPuzzle);                                                              // Add new puzzle to end of queue.
    }
    else                                                                                    // Puzzle has been locally visited.
    {
        delete newPuzzle;                                                                   // Free memory.
        numOfLocalLoopsAvoided++;                                                           // Increment number of local loops avoided.
    }
}

// Creates puzzle and adds to queue if not visited.
// For BFS with visited list.
void moveBFSV(Puzzle &puzzle, int xChange, int yChange, vector<vector<map<int, int>>> &visitedLists, queue<Puzzle> &q)
{
    Puzzle * newPuzzle = puzzle.move(xChange, yChange);                                     // Create the new puzzle.
    int state = newPuzzle->getState();                                                      // Get the state of the puzzle.
    int listIndex = (state / 10000000) % 10;                                                // Use the second number of the puzzle state to determine which visited list to check.
    int mapIndex = (state / 1000000) % 10;                                                  // Use the second number of the puzzle state to determine which visited list to check.

    if (!visited(state, visitedLists.at(listIndex).at(mapIndex)))                           // Check if state visited.
    {
        q.emplace(*newPuzzle);                                                              // Add new puzzle to end of queue.
    }
    else                                                                                    // Puzzle has been visited.
    {
        delete newPuzzle;                                                                   // Free memory.
    }
}

// Creates puzzle and adds to queue if not locally visited.
// For BFS and PDS with no visited list.
void movePDS(Puzzle &puzzle, int xChange, int yChange, queue<Puzzle> &q, int &numOfLocalLoopsAvoided)
{
    Puzzle * newPuzzle = puzzle.move(xChange, yChange);                                     // Create the new puzzle.

    if (!puzzle.locallyVisited(newPuzzle->getState()))                                      // Check if puzzle locally visited.
    {
        q.push(*newPuzzle);                                                                 // Add new puzzle to end of queue.
    }
    else                                                                                    // Puzzle has been locally visited.
    {
        delete newPuzzle;                                                                   // Free memory.
        numOfLocalLoopsAvoided++;                                                           // Increment number of local loops avoided.
    }
}

// Creates puzzle and adds to queue if not visited.
// For PDS with non-strict visited list.
void movePDSV(Puzzle &puzzle, int xChange, int yChange, vector<vector<map<int, int>>> &visitedLists, queue<Puzzle> &q)
{
    Puzzle * newPuzzle = puzzle.move(xChange, yChange);                                     // Create the new puzzle.
    int state = newPuzzle->getState();                                                      // Get the state of the puzzle.
    int depth = newPuzzle->getPathLength();                                                 // Get the depth of the state.
    int listIndex = (state / 10000000) % 10;                                                // Use the second number of the puzzle state to determine which visited list to check.
    int mapIndex = (state / 1000000) % 10;                                                  // Use the second number of the puzzle state to determine which visited list to check.

    if (!visited(state, visitedLists.at(listIndex).at(mapIndex)))                           // Check if state visited.
    {
        q.push(*newPuzzle);                                                                 // Add new puzzle to end of queue.
    }
    else                                                                                    // Puzzle has been visited.
    {
        delete newPuzzle;                                                                   // Free memory.
    }
}

// Creates new puzzle and adds to heap if not expanded.
// For A* with expanded list.
void moveAStar(Puzzle &puzzle, int xChange, int yChange, vector<vector<map<int, int>>> &expandedLists, heuristicFunction heuristic, Heap &heap)
{
    Puzzle * newPuzzle = puzzle.move(xChange, yChange);                                     // Create the new puzzle.
    int state = newPuzzle->getState();                                                      // Get the state of the puzzle.
    int depth = newPuzzle->getPathLength();                                                 // Get the depth of the puzzle.
    int listIndex = (state / 10000000) % 10;                                                // Get the index of the vector of maps.
    int mapIndex = (state / 1000000) % 10;                                                  // Get the index of the expanded list map to add the state to.

    if (!expanded(state, depth, expandedLists[listIndex][mapIndex]))                        // Check if state expanded.
    {
        newPuzzle->updateFCost(heuristic);                                                  // Get the f-cost of the puzzle.
        heap.insert(newPuzzle);                                                             // Add new puzzle to heap.
    }
    else                                                                                    // State has been expanded.
    {
        delete newPuzzle;                                                                   // Free memory.
    }
}


// Returns true if state visited before; using strict visited list.
// Linear search.
bool visited(int state, map<int, int> &visitedList)
{
    pair<map<int, int>::iterator, bool> mapPair = visitedList.emplace(state, 0);            // Attempt to add state to visited list.
    return !get<1>(mapPair);                                                                // Return true if state not in visited list.
}

// Returns true if state visited before; using non-strict visited list.
// Linear search.
bool visited(int state, int depth, map<int, int> &visitedList)
{
    pair<map<int, int>::iterator, bool> mapPair = visitedList.emplace(state, depth);        // Attempt to add state to visited list.

    if(get<1>(mapPair))                                                                     // Emplace returns true if key did not previously exist (therefore not visited).
    {
        return false;                                                                       // State has not been visited.
    }
    else
    {
        if (depth < get<0>(mapPair)->second)                                                // State has been visited, check the depth it was when visited.
        {

            get<0>(mapPair)->second = depth;                                                // Current depth is lower than visited depth, replace.
            return false;                                                                   // State has not been visited.
        }
        else                                                                                // Current depth lower than when visited.
        {
            return true;                                                                    // State has been visited.
        }
    }
}

// Returns true if the state expanded before; using strict expanded list.
// Linear search.
bool expanded(int state, int depth, map<int, int> &expandedList)
{
    map<int, int>::iterator it = expandedList.find(state);                                  // Get the iterator for the puzzle key if it exists in the map.
    if(it != expandedList.end())                                                            // Check if map contained the number representing the state of the puzzle.
    {
        return true;                                                                        // State has been expanded.

        // Below is for non-strict expanded list.
        /*if (it->second > depth)                                                             // State has been expanded, check the depth it was when expanded.
        {
            return false;                                                                   // State has not been expanded.
        }
        else                                                                                // Current depth lower than when expanded.
        {
            return true;                                                                    // State has been expanded.
        }*/
    }
    else
    {
        return false;                                                                       // State has not been expanded.
    }
}

// Returns true if 95% of system memory being used.
bool memoryOverloaded(MEMORYSTATUSEX memInfo)
{
    // To ensure no memory overload:
    GlobalMemoryStatusEx(&memInfo);                                                     // Get memory status.
    DWORDLONG totalPhysMem = memInfo.ullTotalPhys;                                      // Get total physical memory of system.
    DWORDLONG physMemUsed = totalPhysMem - memInfo.ullAvailPhys;                        // Get memory used by system.

    if (physMemUsed >= totalPhysMem * 0.95)                                             // Check if used memory is 95% of total memory.
    {
        return true;                                                                    // Stop algorithm and return no solution due to memory overload.
    }
    else
    {
        return false;                                                                   // Memory not overloaded.
    }
}

