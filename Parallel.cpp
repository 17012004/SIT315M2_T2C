#include <iostream>
#include <thread>

// Partition function
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quicksort function
void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        // Create threads for left and right partitions
        std::thread left_thread(quicksort, arr, low, pi - 1);
        std::thread right_thread(quicksort, arr, pi + 1, high);

        // Join threads
        left_thread.join();
        right_thread.join();
    }
}

int main() {
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Original array:";
    for (int i = 0; i < arr_size; ++i) {
        std::cout << " " << arr[i];
    }
    std::cout << std::endl;

    quicksort(arr, 0, arr_size - 1);

    std::cout << "Sorted array:";
    for (int i = 0; i < arr_size; ++i) {
        std::cout << " " << arr[i];
    }
    std::cout << std::endl;

    return 0;
}