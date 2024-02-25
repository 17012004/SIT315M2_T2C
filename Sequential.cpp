#include <iostream>
#include <thread>
#include <chrono> // Include chrono for time measurement

// Function to partition the array and return the pivot index
int partition(int array[], int start, int end) {
    int pivot = array[end]; // Selecting the last element as the pivot
    int i = start - 1; // Index of the smaller element

    for (int j = start; j < end; ++j) {
        if (array[j] <= pivot) {
            ++i; // Increment index of smaller element
            std::swap(array[i], array[j]);
        }
    }
    std::swap(array[i + 1], array[end]);
    return i + 1; // Return the partitioning index
}

// Function to implement the Quicksort algorithm
void quicksort(int array[], int start, int end) {
    if (start < end) {
        // Partitioning index
        int partitionIndex = partition(array, start, end);

        // Create threads for left and right partitions
        std::thread leftThread(quicksort, array, start, partitionIndex - 1);
        std::thread rightThread(quicksort, array, partitionIndex + 1, end);

        // Join threads
        leftThread.join();
        rightThread.join();
    }
}

int main() {
    int inputArray[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    int size = sizeof(inputArray) / sizeof(inputArray[0]);

    std::cout << "Original array:";
    for (int i = 0; i < size; ++i) {
        std::cout << " " << inputArray[i];
    }
    std::cout << std::endl;

    // Start time measurement
    auto startTime = std::chrono::high_resolution_clock::now();

    // Perform quicksort on the array
    quicksort(inputArray, 0, size - 1);

    // End time measurement
    auto endTime = std::chrono::high_resolution_clock::now();

    // Calculate and print the time taken to sort
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    std::cout << "Time taken to sort: " << duration.count() << " microseconds" << std::endl;

    std::cout << "Sorted array:";
    for (int i = 0; i < size; ++i) {
        std::cout << " " << inputArray[i];
    }
    std::cout << std::endl;

    return 0;
}
