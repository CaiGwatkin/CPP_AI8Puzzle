#include "heap.h"


// Insert a new element in the Heap
void Heap::insert(Puzzle *newElement)
{
    data.push_back(newElement);                                                             // Add new element to the end of the heap.
    stateSearchData.push_back(newElement->getState());                                      // Add state of new element to end of companion heap.
    int last = data.size() - 1;                                                             // The index of the last element in the heap.

    if (last == 0)                                                                          // Check if only one element in heap.
    {
        return;                                                                             // Skip sorting.
    }

    sortUp(last);                                                                           // Sort added element upward into heap.
}

// Returns true if the heap is empty.
bool Heap::empty()
{
    return data.empty();                                                                    // Return the emptiness of the vector.
}

// Returns the size of the heap.
int Heap::size()
{
    return data.size();                                                                     // Return the size of the heap vector.
}

// Returns the value of the root element of the Heap.
Puzzle * Heap::rootData()
{
    return data[0];                                                                         // Return the data at the root index.
}

// Deletes the root from the Heap.
// Ensure rootData() called if you wish to use the data at the root BEFORE calling this function.
void Heap::deleteRoot()
{
    int last = data.size() - 1;                                                             // The index of the last node in the heap.

    if (last < 0)                                                                           // Ensure heap is not empty.
    {
        return;                                                                             // No root, can't delete.
    }

    data[0] = data[last];                                                                   // Copy data at bottom of heap to top of heap.
    data.pop_back();                                                                        // Delete the data from the heap.

    stateSearchData[0] = stateSearchData[last];                                             // Copy data at bottom of companion heap to top of heap.
    stateSearchData.pop_back();                                                             // Delete the data from the companion heap.

    sortDown();                                                                             // Sort the swapped data back into the heap.
}

// Searches heap for specified elements and deletes those.
// Returns the number of elements deleted from the heap.
int Heap::deleteElement(int state)
{
    int numDeleted = 0;                                                                     // Initialise as none deleted.
    vector<int>::iterator begin = stateSearchData.begin(), end = stateSearchData.end();     // Get the iterators for the beginning and end of the vector.
    bool possiblyElements = true;                                                           // To begin with there are possible elements to delete.

    while (possiblyElements)                                                                // Loop while there might be elements to delete.
    {
        vector<int>::iterator it = find(stateSearchData.begin(), stateSearchData.end(), state); // Find element with passed state in companion data vector.

        if (it != stateSearchData.end())                                                    // Check if element found.
        {
            int index = it - stateSearchData.begin();                                       // Get the index of the element.
            stateSearchData[index] = stateSearchData[stateSearchData.size() - 1];           // Replace element with element from bottom of heap.
            stateSearchData.pop_back();                                                     // Delete last element.
            data[index] = data[data.size() - 1];                                            // Replace element with element from bottom of heap.
            data.pop_back();                                                                // Delete last element.
            sortDown(index);                                                                // Sort the moved element back into the heap.
            numDeleted++;                                                                   // Increment number deleted.
        }
        else                                                                                // Element not found.
        {
            possiblyElements = false;                                                       // No more elements to delete.
        }
    }

    return numDeleted;
}

// Sorts the element at the given index downwards into the heap.
// Normally used for index 0 after a deleteRoot(), however can be used after deleteElement() if original index of deleted element passed.
void Heap::sortDown(int sortIndex)
{
    int parentIndex = sortIndex;                                                            // The initial index of the parent node.
    int leftChildIndex = parentIndex * 2 + 1;                                               // The left child node of the parent node.
    int rightChildIndex = parentIndex * 2 + 2;                                              // The right child node of the parent node.
    int last = data.size() - 1;                                                             // The index of the last element in the heap.

    while (leftChildIndex <= last)                                                          // Sort while left child exists.
    {
        int swapChildIndex = 0;                                                             // Initialise the index of the child to swap.
        int swapChildFCost = 0;                                                             // Initialise the f-cost of the child to swap.

        if (rightChildIndex <= last)                                                        // Check if right child exists to find which child to use for swap.
        {
            int leftChildFCost = data[leftChildIndex]->getFCost();                          // Get the f-cost of the left child.
            int rightChildFCost = data[rightChildIndex]->getFCost();                        // Get the f-cost of the right child.

            if (leftChildFCost < rightChildFCost)                                           // Check which of the left and right child nodes has a lesser f-cost.
            {
                swapChildFCost = leftChildFCost;                                            // Set swap f-cost to left child's f-cost.
                swapChildIndex = leftChildIndex;                                            // Set swap index to left child's index.
            }
            else
            {
                swapChildFCost = rightChildFCost;                                           // Set swap f-cost to right child's f-cost.
                swapChildIndex = rightChildIndex;                                           // Set swap index to right child's index.
            }
        }
        else
        {
            swapChildFCost = data[leftChildIndex]->getFCost();                              // Set swap f-cost to left child's f-cost.
            swapChildIndex = leftChildIndex;                                                // Set swap index to left child's index.
        }

        
        if (swapChildFCost < data[parentIndex]->getFCost())                                 // Check if swap should occur (child f-cost less than parent).
        {
            swap(data[swapChildIndex], data[parentIndex]);                                  // Swap positions in heap.
            swap(stateSearchData[swapChildIndex], stateSearchData[parentIndex]);            // Swap positions in companion heap.
        }

        parentIndex = swapChildIndex;                                                       // Update parent index as the swapped child index.
        leftChildIndex = parentIndex * 2 + 1;                                               // Update left child index to that of the new parent.
        rightChildIndex = parentIndex * 2 + 2;                                              // Update right child index to that of the new parent.
    }
}

// Sorts the element at the given index upwards into the heap.
// Normally used for last node after an insert().
void Heap::sortUp(int sortIndex)
{
    int childIndex = sortIndex;                                                             // Initialise child index as passed index.
    bool swapping = true;                                                                   // Swapping may need to occur.

    while (swapping == true && childIndex > 0)                                              // While swapping may need to occur and child index not source node.
    {
        int parentIndex = 0;                                                                // Initialise parent index.

        if (childIndex % 2 == 0)                                                            // Check if current node is a right child or left child.
        {
            parentIndex = childIndex / 2 - 1;                                               // Node is a right child, set parent node.
        }
        else
        {
            parentIndex = childIndex / 2;                                                   // Node is a left child, set parent node.
        }

        swapping = false;                                                                   // Swapping may not need to occur again.

        if (data[childIndex]->getFCost() < data[parentIndex]->getFCost())                   // Check if swap needed (child f-cost less than parent).
        {
            swap(data[childIndex], data[parentIndex]);                                      // Swap data between child and parent nodes.
            swap(stateSearchData[childIndex], stateSearchData[parentIndex]);                // Swap positions in companion heap.
            swapping = true;                                                                // Swap should be checked again.
            childIndex = parentIndex;                                                       // Parent index becomes new child index.
        }
    }
}

