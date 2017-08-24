//////////////////////////////////////////////////////////////////////////
//  8-PUZZLE PROBLEM
//  
//  Start-up codes by n.h.reyes@massey.ac.nz
//
//  Name(s): Cai Gwatkin - 15146508
//  Date: 
//
//////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm> //used by transform - to lower case
#include <exception>

#include "graphics.h"
#include "algorithm.h"

using namespace std;

#define OUTPUT_LENGTH 2 /* Length of output string. */

const int HEIGHT = 400; /**< Height of board for rendering in pixels. */
const int WIDTH  = 400; /**< Width of board for rendering in pixels. */


//////////////////////////////////////////////////////
// Function prototypes
void update(int **board);
void displayBoard(string const elements); 
void AnimateSolution(string const initialState, string const goalState, string path);
//////////////////////////////////////////////////////


/**
 * Main function to kick off the game.
 */

int main( int argc, char* argv[] )
{
    string path;

    // Following commented code for testing only
    //~ cout << "=========<< SEARCH ALGORITHMS >>=========" << endl;

    if (argc < 5)                                                       // If not enough arguments program should be exited.
    {
        cout << "SYNTAX: main.exe <TYPE_OF_RUN = \"batch_run\" or \"single_run\"> ALGORITHM_NAME \"INITIAL STATE\" \"GOAL STATE\" " << endl;    // Display error text to show what should have been passed to program.
        exit(1);                                                        // Close executable.
    }

    // Following commented code for testing only
    //~ cout << "Parameters supplied" << endl;
    //~ for (int i=1; i < argc; i++)
    //~ {
    //~     cout << setw(2) << i << ") " << argv[i] << endl;
    //~ }
    
    // Initialise variables.
    string typeOfRun(argv[1]);                                          // Type of run, should be batch_run or single_run.
    string algorithmSelected(argv[2]);                                  // The algorithm selected to be used to solve the puzzle.
    string initialState(argv[3]);                                       // Initial state of the puzzle.
    string goalState(argv[4]);                                          // Goal state for the puzzle.
    
    std::transform(typeOfRun.begin(), typeOfRun.end(), typeOfRun.begin(), ::tolower);   // Ensure type of run is lower-case.
    std::transform(algorithmSelected.begin(), algorithmSelected.end(), algorithmSelected.begin(), ::tolower);   // Ensure algorithm selected is lower-case.
    
    int pathLength = 0;                                                 // The path length of the solution.
    int depth = 0;                                                      // The depth of the solution.
    int numOfStateExpansions = 0;                                       // The number of state expansions performed during run-time.
    int maxQLength = 0;                                                 // The max length that the queue was during run-time.
    int numOfDeletionsFromMiddleOfHeap = 0;                             // The number of deletions of elements from the middle of the heap.
    int numOfLocalLoopsAvoided = 0;                                     // The number of local loops detected and avoided.
    int numOfAttemptedNodeReExpansions = 0;                             // The number of attempted expansions of nodes already expanded.

    float actualRunningTime = 0.0;                                      // The time it took the algorithm to find the solution.

    // Following commented code for testing only
    //~ cout << "typeOfRun = " << typeOfRun << endl;
    //~ cout << "algorithmSelected = " << algorithmSelected << endl;
    
    try
    {
        if (typeOfRun == "single_run") cout << endl << "===========================================<< EXPERIMENT RESULTS >>===========================================" << endl;
        
        // Run algorithm.
        if (algorithmSelected == "breadth_first_search")                // Check if algorithm selected is Breadth First Search.
        {
            path = breadthFirstSearch(initialState, goalState, numOfStateExpansions, maxQLength, actualRunningTime, numOfLocalLoopsAvoided);    // Solve using Breadth First Search.
        }

        else if (algorithmSelected == "breadth_first_search_vlist")     // Check if algorithm selected is Breadth First Search with Visited List.
        {
            path = breadthFirstSearch_with_VisitedList(initialState, goalState, numOfStateExpansions, maxQLength, actualRunningTime);   // Solve using Breadth First Search with Visited List.
        }

        else if (algorithmSelected == "pds_no_vlist")                   // Check if algorithm selected is Progressive Deepenging Search.
        {
            path = progressiveDeepeningSearch_No_VisitedList(initialState, goalState, numOfStateExpansions, maxQLength, actualRunningTime, numOfLocalLoopsAvoided, 5000);  // Solve using Progressive Deepenging Search.
        }

        else if (algorithmSelected == "pds_nonstrict_vlist")            // Check if algorithm selected is Progressive Deepenging Search with Non-Strict Visited List.
        {
            path = progressiveDeepeningSearch_with_NonStrict_VisitedList(initialState, goalState, numOfStateExpansions, maxQLength, actualRunningTime, 5000);    // Solve using Progressive Deepenging Search with Non-Strict Visited List.
        }

        else if (algorithmSelected == "astar_explist_misplacedtiles")   // Check if algorithm selected is A* with Expanded List using Misplaced Tiles for heuristic values.
        {
            path = aStar_ExpandedList(initialState, goalState, numOfStateExpansions, maxQLength, actualRunningTime, numOfDeletionsFromMiddleOfHeap,numOfLocalLoopsAvoided ,numOfAttemptedNodeReExpansions, MISPLACED_TILES); // Solve using A* with Expanded List using Misplaced Tiles for heuristic values.
        }

        else if (algorithmSelected == "astar_explist_manhattan")        // Check if algorithm selected is A* with Expanded List using Manhattan Distance for heuristic values.
        {
            path = aStar_ExpandedList(initialState, goalState, numOfStateExpansions, maxQLength, actualRunningTime, numOfDeletionsFromMiddleOfHeap,numOfLocalLoopsAvoided ,numOfAttemptedNodeReExpansions, MANHATTAN_DISTANCE);  // Solve using A* with Expanded List using Manhattan Distance for heuristic values.
        }
        
        pathLength = path.size();
        
        // Output results.
        if (algorithmSelected == "breadth_first_search")
        {
            cout << setw(31) << std::left << "1) breadth_first_search";
        }
        else if (algorithmSelected == "breadth_first_search_vlist")
        {
            cout << setw(31) << std::left << "2) breadth_first_search_vlist";
        }
        else if (algorithmSelected == "pds_no_vlist")
        {
            cout << setw(31) << std::left << "3) pds_no_vlist";
        }
        else if (algorithmSelected == "pds_nonstrict_vlist")
        {
            cout << setw(31) << std::left << "4) pds_nonstrict_vlist";
        }
        else if (algorithmSelected == "astar_explist_misplacedtiles")
        {
            cout << setw(31) << std::left << "5) astar_explist_misplacedtiles";
        }
        else if (algorithmSelected == "astar_explist_manhattan")
        {
            cout << setw(31) << std::left << "6) astar_explist_manhattan";
        }
    }

    catch (exception &e)                                                    // Ensure no exception when running algorithm.
    {
        cout << "Standard exception: " << e.what() << endl;
    }

    if (typeOfRun == "batch_run")                                           // Check if a batch run is being performed and output results.
    {
        string reasonForNonCompletion = "";

        if (pathLength == 0)                                                // Path length of 0 means no solution was found by the algorthm.
        {
            reasonForNonCompletion = "no_solution";
        }
        else if (path == "memory overload")                                 // Memory overloaded and algorithm aborted.
        {
            reasonForNonCompletion = "RAM_overload";
            path = "";                                                      // Clear path so no solution animated.
            pathLength = 0;                                                 // Path length updated.
        }
        else if (path == "ultimate max depth reached")                      // PDS algorithm reached ultimate max depth and aborted.
        {
            reasonForNonCompletion = "max_depth_reached";
            path = "";                                                      // Clear path so no solution animated.
            pathLength = 0;                                                 // Path length updated.
        }

        cout  << setprecision(6) << std::setfill(' ')   << std::fixed << std::right << ' ' <<  setw(10) << pathLength;
        cout  << setprecision(6) << std::setfill(' ')   << std::fixed << std::right << ' ' <<  setw(10) << numOfStateExpansions;
        cout  << setprecision(6) << std::setfill(' ')   << std::fixed << std::right << ' ' <<  setw(19) << maxQLength;
        cout  << setprecision(6) << std::setfill(' ')   << std::fixed << std::right << ' ' <<  setw(15) << actualRunningTime;
        cout  << setprecision(6) << std::setfill(' ')   << std::fixed << std::right << ' ' <<  setw(15) << numOfDeletionsFromMiddleOfHeap;
        cout  << setprecision(6) << std::setfill(' ')   << std::fixed << std::right << ' ' <<  setw(15) << numOfAttemptedNodeReExpansions;
        cout  << setprecision(6) << std::setfill(' ')   << std::fixed << std::right << ' ' <<  setw(19) << reasonForNonCompletion << endl;
    }
    else if (typeOfRun == "single_run")                                     // Check if a single run is being performed and output results.
    {
        if (pathLength == 0)
        {
            cout << "\n\n*---- NO SOLUTION found. (Q is empty!) ----*" << endl; // Path length of 0 means no solution was found by the algorthm.
        }
        else if (path == "memory overload")                                 // Memory overloaded and algorithm aborted.
        {
            cout << "\n\n*---- NO SOLUTION found. (RAM overloaded!) ----*" << endl;
            path = "";                                                      // Clear path so no solution animated.
            pathLength = 0;                                                 // Path length updated.
        }
        else if (path == "ultimate max depth reached")                      // PDS algorithm reached ultimate max depth and aborted.
        {
            cout << "\n\n*---- NO SOLUTION found. (Ultimate max depth reached!) ----*" << endl;
            path = "";                                                      // Clear path so no solution animated.
            pathLength = 0;                                                 // Path length updated.
        }

        cout << setprecision(6) << setw(25) << std::setfill(' ') <<  std::right << endl << endl << "Initial State:"      << std::fixed << ' ' << setw(12)                    <<  initialState << endl;
        cout << setprecision(6) << setw(25) << std::setfill(' ') <<  std::right << "Goal State:"                         << std::fixed << ' ' << setw(12)                    <<  goalState << endl;
        cout << setprecision(6) << setw(25) << std::setfill(' ') <<  std::right << endl <<  "Path Length:"               << std::fixed << ' ' << setw(12)                    <<  pathLength << endl;
        cout << setprecision(6) << setw(25) << std::setfill(' ') <<  std::right << "Num Of State Expansions:"            << std::fixed << ' ' << setw(12)                    <<  numOfStateExpansions << endl;
        cout << setprecision(6) << setw(25) << std::setfill(' ') <<  std::right << "Max Q Length:"                       << std::fixed << ' ' << setw(12)                    <<  maxQLength << endl;
        cout << setprecision(6) << setw(25) << std::setfill(' ') <<  std::right << "Actual Running Time:"                << std::fixed << ' ' << setprecision(6) << setw(12) <<  actualRunningTime << endl;
        cout << setprecision(6) << setw(25) << std::setfill(' ') <<  std::right << "Num of Deletions from MiddleOfHeap:" << std::fixed << ' ' << setprecision(6) << setw(12) <<  numOfDeletionsFromMiddleOfHeap << endl;
        cout << setprecision(6) << setw(25) << std::setfill(' ') <<  std::right << "Num of Attempted Node ReExpansions:" << std::fixed << ' ' << setprecision(6) << setw(12) <<  numOfAttemptedNodeReExpansions << endl;
        cout << "===============================================================================================================" << endl << endl;
        
        if (path != "") AnimateSolution(initialState, goalState, path);     // If a solution was found for single run then animation should be displayed.
    }

    // Show that we have exited without an error.
    return 0;
}


/*
 * Flicker-free implementation of the 8-puzzle board game using the BGI
 * graphics library for Windows.
 */

void AnimateSolution(string const initialState, string const goalState, string path)
{
    cout << endl << "--------------------------------------------------------------------" << endl;

    if (path == "")                                                         // If no solution found then nothing to animate.
    {
         cout << endl << "Nothing to animate." << endl;
         return;
    }
    else                                                                    // Otherwise animate the solution.
    {
        cout << endl << "Animating solution..." << endl;
        cout << "Plan of action = " << path << endl;
    }
    
    Puzzle *p = new Puzzle(initialState, goalState);                        // Create new puzzle object for the puzzle.
    Puzzle *nextState;                                                      // To be used to create the next state of the puzzle.
    
    string strState = p->toString();                                        // The state of the puzzle as a string to be displayed to user.

    displayBoard(strState);                                                 // Display the initial state of the puzzle.

    cout << "--------------------------------------------------------------------" << endl;
          
    for (unsigned int i = 0; i < path.length(); i++)                        // Itterate over steps in path to display path to user.
    {
        cout << endl << "Step #" << i + 1 << ")  ";

        switch (path[i])                                                    // Check the value of the character at the point in the path and display the corresponding word.
        {

            case 'L': nextState = p->move(-1, 0);
                cout << "[LEFT]" << endl;
                break;

            case 'U': nextState = p->move(0, -1);
                cout << "[UP]" << endl;
                break;

            case 'R': nextState = p->move(1, 0);
                cout << "[RIGHT]" << endl;
                break;

            case 'D': nextState = p->move(0, 1);
                cout << "[DOWN]" << endl;
                break;
        }
        delete p;                                                           // Free memory.
        p = nextState;                                                      // Make next puzzle state the current puzzle state.

        strState = p->toString();                                           // Update the string of current state of puzzle.

        displayBoard(strState);                                             // Display current state.
    }
    
    delete p;                                                               // Free memory.    
    cout << endl << "Animation done." << endl;                              // Done.
    
    cout << "--------------------------------------------------------------------" << endl;
}


/**
 * Update the board and draw it to the screen. This function displays the
 * board updates in a flicker-free way.
 *
 * @param board 3 x 3 array containing the current board state,
 *              0 indicates an empty space.
 */

void displayBoard(string const elements)
{
    // Setting up the graphics.
    int board[3][3];                                                        // 3x3 board.
    int n = 0;
    
    for (int i = 0; i < 3; i++)                                             // Loop through rows of board.
    {
        for (int j = 0; j < 3; j++)                                         // Loop through columns.
        {
            board[i][j] = elements.at(n) - '0';                             // Sets the value of the element at that coordinate.
            n++;                                                            // Next element.
        }
    }
    
    static bool setup = false;                                              // Setup initialised to false as setup has not occured.

    if (!setup)                                                             // If not setup then setup.
    {
        int graphDriver = 0;
        int graphMode = 0;
        initgraph(&graphDriver, &graphMode, "", WIDTH, HEIGHT);             // Initialise the graph.
        
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);                           // Set text style for start message.
        settextjustify(CENTER_TEXT, CENTER_TEXT);                           // Set text to centred.
        outtextxy(getmaxx()/2,getmaxy()/2,"press any key to start.");       // Output start message.
        cout << endl << endl << "press any key to start." << endl << endl;
        getch();                                                            // Wait for user input.
        
        setup = true;                                                       // Setup now complete.
    }

    // Variables for the function.
    int xIncrement = (WIDTH - 40) / 3;                                      // Grid's raster width.
    int yIncrement = ((HEIGHT - 6) - 40) / 3;                               // Grid's raster height.
    int x = 0;                                                              // Temporary x positions.
    int y = 0;                                                              // Temporary y positions.
    char outputString[OUTPUT_LENGTH];                                       // Holder for output strings in the GUI.
    static bool visual;                                                     // Indicator which visual page to draw to prevent flickers.

    // Initalising the variables.
    strncpy(outputString, "", OUTPUT_LENGTH);
    // Even though this is not necessary here the protected version of "strcpy" is used in this case. It should ALWAYS be used to prevent boundary overwrites!

    // Initialising the GUI.
    setactivepage(visual);                                                  // The current active page is set as visual, so that updates happen to a different screen before being shown.
    setbkcolor(BLACK);                                                      // Background colour is set to black.
    cleardevice();                                                          // Clear the screen.
    setfillstyle(SOLID_FILL, WHITE);                                        // Fill with text with white.
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 6);                                // Set text style.
    settextjustify(CENTER_TEXT, CENTER_TEXT);                               // Make text centred.

    // Display different coloured squares for different numbers.
    y = 10;                                                                 // Initialise y coordinate for first square.
    
    for (int i = 0; i < 3; i++)                                             // Loop through each row to make 3 squares tall.
    {
        x = 10;                                                             // Initial x coordinate for square.

        for (int j = 0; j < 3; j++)                                         // Loop through each column to make 3 squares wide.
        {
            if (board[i][j] != 0)                                           // Colour all squares except top left.
            {
                setcolor(board[i][j]);                                      // Set different colour for each square.
                bar(x, y, x + xIncrement, y + yIncrement);                  // Draw square.
            }

            x += xIncrement;                                                // Make x coordinate edge of drawn square.
            x += 10;                                                        // Increment x to go to next square.
        }

        y += yIncrement;                                                    // Make y coordinate edge of drawn square.
        y += 10;                                                            // Increment y to go to next square.
    }

    /* Display the actual numbers. */
    y = 8 * HEIGHT / 40;                                                    // Initialise y coordinate for first square.

    for (int i = 0; i < 3; i++)                                             // Loop through each row of squares.
    {
        x = WIDTH / 6;                                                      // Initialise x coordinate for first square.

        for (int j = 0; j < 3; j++)                                         // Loop through each column of squares.
        {
            setcolor(WHITE);                                                // Use white for colour of text for the square's number.
            setbkcolor(board[i][j]);                                        // Set the text's background colour to that of the square.

            if (board[i][j] != 0)                                           // Number all squares except top left.
            {
                snprintf(outputString, OUTPUT_LENGTH, "%d", board[i][j]);   // Create the string with the squares number as outputString.
                outtextxy(x, y, outputString);                              // Output the text in the square.
                moveto(0, 0);                                               // Move back origin of outtextxy.
            }

            x += 2 * (WIDTH / 6);                                           // Increment x to go to next column.
        }

        y += 13 * HEIGHT / 40;                                              // Increment y to go to next row.
    }

    // Set the page to display.
    setvisualpage(visual);                                                  // Set the page to display.
    visual = !visual;                                                       // Make visual not previous visual so that updates are all finished before displayed.

    delay(100);                                                             // Wait 100 milliseconds.
}


/**
 * Update the board and draw it to the screen. This function displays the
 * board updates in a flicker-free way.
 *
 * @param board 3 x 3 array containing the current board state,
 *              0 indicates an empty space.
 */
/*
void update(int **board)
{
    // Setting up the graphics.
    static bool setup = false;                                              // Not setup yet.

    if (!setup)                                                             // If not setup then setup.
    {
        int graphDriver = 0;
        int graphMode = 0;
        initgraph(&graphDriver, &graphMode, "", WIDTH, HEIGHT);             // Initialise the graph.
        setup = true;                                                       // Setup complete.
    }

    // Variables for the function.
    int xIncrement = (WIDTH - 40) / 3;                                      // Grid's raster width.
    int yIncrement = ((HEIGHT - 6) - 40) / 3;                               // Grid's raster height.
    int x = 0;                                                              // Temporary x positions.
    int y = 0;                                                              // Temporary y positions.
    char outputString[OUTPUT_LENGTH];                                       // Holder for output strings in the GUI.
    static bool visual;                                                     // Indicator which visual page to draw to to prevent flickers.

    // Initalising the variables.
    strncpy(outputString, "", OUTPUT_LENGTH);                               // Initialise outputString to blank string.

    // Initialising the GUI.
    setactivepage(visual);                                                  // The current active page is set as visual, so that updates happen to a different screen before being shown.
    setbkcolor(BLACK);                                                      // Background colour is set to black.
    cleardevice();                                                          // Clear the screen.
    setfillstyle(SOLID_FILL, WHITE);                                        // Fill with text with white.
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 6);                                // Set text style.
    settextjustify(CENTER_TEXT, CENTER_TEXT);                               // Make text centred.

    // Display different coloured squares for different numbers.
    y = 10;                                                                 // Initialise y coordinate for first square.

    for (int i = 0; i < 3; i++)                                             // Loop through each row to make 3 squares tall.
    {
        x = 10;                                                             // Initial x coordinate for square.

        for (int j = 0; j < 3; j++)                                         // Loop through each column to make 3 squares wide.
        {
            if (board[i][j] != 0)                                           // Colour all squares except top left.
            {
                setcolor(board[i][j]);                                      // Set different colour for each square.
                bar(x, y, x + xIncrement, y + yIncrement);                  // Draw square.
            }

            x += xIncrement;                                                // Make x coordinate edge of drawn square.
            x += 10;                                                        // Increment x to go to next square.
        }

        y += yIncrement;                                                    // Make y coordinate edge of drawn square.
        y += 10;                                                            // Increment y to go to next square.
    }

    // Display the actual numbers.
    y = 8 * HEIGHT / 40;                                                    // Initialise y coordinate for first square.

    for (int i = 0; i < 3; i++)                                             // Loop through each row of squares.
    {
        x = WIDTH / 6;                                                      // Initialise x coordinate for first square.

        for (int j = 0; j < 3; j++)                                         // Loop through each column of squares.
        {
            setcolor(WHITE);                                                // Use white for colour of text for the square's number.
            setbkcolor(board[i][j]);                                        // Set the text's background colour to that of the square.

            if (board[i][j] != 0)                                           // Number all squares except top left.
            {
                snprintf(outputString, OUTPUT_LENGTH, "%d", board[i][j]);   // Create the string with the squares number as outputString.
                outtextxy(x, y, outputString);                              // Output the text in the square.
                moveto(0, 0);                                               // Move back origin of outtextxy.
            }

            x += 2 * (WIDTH / 6);                                           // Increment x to go to next column.
        }

        y += 13 * HEIGHT / 40;                                              // Increment y to go to next row.
    }

    // Set the page to display.
    setvisualpage(visual);                                                  // Set the page to display.
    visual = !visual;                                                       // Make visual not previous visual so that updates are all finished before displayed.

    delay(100);                                                             // Wait 100 milliseconds.
}*/
