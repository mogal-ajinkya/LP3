#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;
/*
TC BEST o(nlogn) worst o(N^2)
SC BEST o(logn) worst o(N)
*/
class quicks {
public:
    vector<int> arr;

    quicks(vector<int> array) {
        arr = array;
    }

    void display() {
        for (auto i : arr) cout << i << " ";
        cout << endl;
    }

    // Deterministic partition with the pivot as the first element
    int partition(int low, int high) {
        int pivot = arr[low];
        int i = low + 1;

        for (int j = low + 1; j <= high; j++) {
            if (arr[j] < pivot) {
                swap(arr[i++], arr[j]);
            }
        }
        swap(arr[low], arr[i - 1]);  // Place pivot at its correct position
        return i - 1;
    }

    // Randomized partition with a random pivot
    int partition_random(int low, int high) {
        int pivot = low + rand() % (high - low + 1);  // Random pivot index
        cout << "Randomized pivot: " << arr[pivot] << endl;
        swap(arr[low], arr[pivot]);  // Move pivot to the beginning
        return partition(low, high);
    }

    // Deterministic QuickSort
    void sort_d(int low, int high) {
        if (low < high) {
            int pivot = partition(low, high);
            cout << "Array after deterministic partition (pivot: " << arr[pivot] << "): ";
            display();

            sort_d(low, pivot - 1);
            sort_d(pivot + 1, high);
        }
    }

    // Randomized QuickSort
    void sort_r(int low, int high) {
        if (low < high) {
            int pivot = partition_random(low, high);
            cout << "Array after randomized partition (pivot: " << arr[pivot] << "): ";
            display();

            sort_r(low, pivot - 1);
            sort_r(pivot + 1, high);
        }
    }
};

int main() {
    srand(time(0));  // Seed for random number generation

    cout << "Enter the number of elements in the array: ";
    int n;
    cin >> n;

    vector<int> v(n);
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    cout << "\nDeterministic QuickSort:\n";
    quicks obj1(v);
    obj1.sort_d(0, n - 1);
    cout << "Final array after deterministic QuickSort: ";
    obj1.display();

    cout << "\nRandomized QuickSort:\n";
    quicks obj2(v);
    obj2.sort_r(0, n - 1);
    cout << "Final array after randomized QuickSort: ";
    obj2.display();
    
    return 0;
}