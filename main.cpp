#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

const int arraySize = 7000;

struct obj {
    float value;
    string date;
};

void heapifyMax(obj arr[], int n, int i) {
    int max = i; // parent
    int l = 2 * i + 1; // left child
    int r = 2 * i + 2; // right child

    // left child >> parent
    if (l < n && arr[l].value > arr[max].value)
        max = l;

    // right child >> parent
    if (r < n && arr[r].value > arr[max].value)
        max = r;

    // parent is not the largest
    if (max != i) {
        swap(arr[i], arr[max]);

        // another subtree
        heapifyMax(arr, n, max);
    }
}

void heapSortMax(obj arr[], int n) {
    // build max-heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyMax(arr, n, i);

    // delete element from heap
    for (int i = n - 1; i >= 0; i--) {
        // place deleted node at the end
        swap(arr[0], arr[i]);

        heapifyMax(arr, i, 0);
    }
}

void heapifyMin(obj arr[], int n, int i) {
    int min = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    // left child < parent
    if (l < n && arr[l].value < arr[min].value)
        min = l;

    // right child < parent
    if (r < n && arr[r].value < arr[min].value)
        min = r;

    // parent is not the smallest
    if (min != i) {
        swap(arr[i], arr[min]);

        // another subtree
        heapifyMin(arr, n, min);
    }
}

// Main function to do the heap sort (min heap).
void heapSortMin(obj arr[], int n) {
    // build min-heap.
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyMin(arr, n, i);

    // delete element from heap
    for (int i = n - 1; i >= 0; i--) {
        // place deleted node at the end
        swap(arr[0], arr[i]);

        heapifyMin(arr, i, 0);
    }
}

void getData(obj arr[]) {
    ifstream file("input.txt");
    string line;

    if (!file.is_open())
        cout << "File not open" << endl;
    else
    {
        cout << "File is open" << endl;
        int index = 0;
        while (getline(file, line))
            {
                cout << "Read: " << line << endl;
                istringstream stream(line);
                stream >> arr[index].date >> arr[index].value;
                index++;
            }
    }

    file.close();
}

void mostNegative(obj array[],int num,int avg)
{

}

int main() {

    obj arr[arraySize];
    getData(arr);



   /* for (int i = 0; i < arraySize; i++) {
        cout << "Date: " << arr[i].date << ", Value: " << arr[i].value << endl;
    }
*/
    return 0;
}

