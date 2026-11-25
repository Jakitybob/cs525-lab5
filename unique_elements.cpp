//------------------------------------------------------------------------------
//
// File Name:	unique_elements.cpp
// Author(s):	jacob.yates
// Course:		CS525F26A
// Project:		Lab 5: STL
// Purpose:		This program looks at the differences in time between inserting
//              thousands to millions of elements into STL data structures where
//              at the end of the insertion each element should be unique, and 
//              all duplicates should be ignored. These tests encompass std::set,
//              std::vector (plus std::sort and std::unique), and std::unordered_map.
//
//------------------------------------------------------------------------------

#include <iostream>
#include <vector> 
#include <random> 
#include <set> 
#include <algorithm>
#include <unordered_set>
#include <chrono>

// Function headers
void TestSet(int*);
void TestVector(int*);
void TestUnorderedSet(int*);

// Static variables (sizes and whatnot)
static const int ARRAY_SIZE = 1000000;
static const int ROW_SIZE = 5; // the number of numbers printed per row

// Whether or not to print the actual contents of the array (off by default cuz duh)
bool printDataContents = false;

int main(int, char**) 
{
    // Set up the random number generator
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<int> distribution(1, 5000000);

    // Create the array and populate it with numbers
    int* array = new int[ARRAY_SIZE];
    for (int index = 0; index < ARRAY_SIZE; index++)
        array[index] = distribution(generator);

    // Run each test, outputting the contents of each 
    // data member as well as the time it took to run
    TestSet(array);
    TestVector(array);
    TestUnorderedSet(array);

    // Free up the array memory
    delete[] array;
}

// Inserts every element from the array into
// an std::set of integers, which will 
// automatically sort out duplicates.
void TestSet(int* array)
{
    // Record the start time
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
    
    // Insert each element from the array, dupes will automatically be ignored
    std::set<int> set;
    for (int index = 0; index < ARRAY_SIZE; index++)
    {
        set.insert(array[index]);
    }

    // Record the end time 
    std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
    std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    // Output the data from the test
    std::cout << "std::set test: ";

    if (printDataContents)
    {
        std::cout << std::endl;
        int rowCount = 0;
        for (auto iter = set.begin(); iter != set.end(); iter++)
        {
            std::cout << (*iter) << " ";
            rowCount++;

            // Start a new line if at the row entry limit
            if (rowCount > ROW_SIZE) 
            {
                std::cout << std::endl;
                rowCount = 0;
            }
        }

        std::cout << "\n-----------------------------------------" << std::endl;
    }

    // Print the time information
    std::cout << "Duration: " << duration.count() << " ms." << std::endl;
}

// Places every element of the array into 
// an std::vector then sorts it, before
// erasing any duplicates.
void TestVector(int* array)
{
    // Record the start time
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

    // Insert each element from the array
    std::vector<int> vector;
    for (int index = 0; index < ARRAY_SIZE; index++)
        vector.push_back(array[index]);

    // Sort the array
    std::sort(vector.begin(), vector.end());

    // Make the array unique
    std::vector<int>::iterator iterator = std::unique(vector.begin(), vector.end());
    vector.resize(std::distance(vector.begin(), iterator)); // anything past iter is now junk

    // Record the end time 
    std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
    std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    // Output the data from the test
    std::cout << "std::vector + std::unique + std::sort test: ";

    if (printDataContents)
    {
        std::cout << std::endl;
        int rowCount = 0;
        for (auto iter = vector.begin(); iter != vector.end(); iter++)
        {
            std::cout << (*iter) << " ";
            rowCount++;

            // Start a new line if at the row entry limit
            if (rowCount > ROW_SIZE) 
            {
                std::cout << std::endl;
                rowCount = 0;
            }
        }

        std::cout << "\n-----------------------------------------" << std::endl;
    }

    // Print the time information
    std::cout << "Duration: " << duration.count() << " ms." << std::endl;
}

void TestUnorderedSet(int* array)
{
    // Record the start time
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

    // Insert each element of the array into the set
    std::unordered_set<int> unordered_set;
    for (int index = 0; index < ARRAY_SIZE; index++)
    {
        unordered_set.insert(array[index]);
    }

    // Record the end time 
    std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
    std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    // Output the data from the test
    std::cout << "std::unordered_set test: ";

    if (printDataContents)
    {
        std::cout << std::endl;
        int rowCount = 0;
        for (auto iter = unordered_set.begin(); iter != unordered_set.end(); iter++)
        {
            std::cout << (*iter) << " ";
            rowCount++;

            // Start a new line if at the row entry limit
            if (rowCount > ROW_SIZE) 
            {
                std::cout << std::endl;
                rowCount = 0;
            }
        }

        std::cout << "\n-----------------------------------------" << std::endl;
    }

    // Print the time information
    std::cout << "Duration: " << duration.count() << " ms." << std::endl;
}