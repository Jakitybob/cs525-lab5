//------------------------------------------------------------------------------
//
// File Name:	unique_elements.cpp
// Author(s):	jacob.yates
// Course:		CS525F26A
// Project:		Lab 5: STL
// Purpose:		
//
//------------------------------------------------------------------------------

#include <iostream>
#include <vector>
#include <random>

static const int ARRAY_SIZE = 100;

int main(int argc, char** argv) 
{
    // Set up the random number generator
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<int> distribution(1, 5000000);

    // Create the array and populate it with numbers
    int* array = new int[ARRAY_SIZE];
    for (int index = 0; index < ARRAY_SIZE; index++)
    {
        array[index] = distribution(generator);
        std::cout << array[index] << " ";
    }

    std::cout << std::endl;

    // Generate the array of 10 million integers
        // Test each unique element in set
        // Test each unique element in sorted unique vector
        // Test each unique element in unordered set

    // Free up the array memory
    delete[] array;
}

void TestSet(int* array)
{

}