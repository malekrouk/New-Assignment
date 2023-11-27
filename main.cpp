#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

const int arraySize = 6668; // array size

struct obj { // node
    float value;
    string date;
};

// heapify algorithm for max heap
void heapifyMax(vector<obj>& v, int n, int i) {
    int max = i; // parent
    int l = 2 * i + 1; // left child
    int r = 2 * i + 2; // right child

    // left child >> parent
    if (l < n && v[l].value > v[max].value)
        max = l;

    // right child >> parent
    if (r < n && v[r].value > v[max].value)
        max = r;

    // parent is not the largest
    if (max != i) {
        swap(v[i], v[max]); // therefore swap with the largest child

        // another subtree
        heapifyMax(v, n, max);
    }
}

// ascending order using heapify
void buildMaxHeap(vector<obj>& heap) {
    // build max-heap
    for (int i = (heap.size()-1) / 2 - 1; i >= 0; i--)
        heapifyMax(heap, heap.size(), i);
}



// heapify algorithm for min heap
void heapifyMin(vector<obj>& arr, int n, int i) {
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
        swap(arr[i], arr[min]); // therefore swap with the smallest child

        // another subtree
        heapifyMin(arr, n, min);
    }
}

// descending order using heapify
void buildMinHeap(vector<obj>& heap) {
    // build min-heap.
    for (int i = (heap.size()-1) / 2 - 1; i >= 0; i--)
        heapifyMin(heap, heap.size(), i);

}

void adjustMinHeap(vector<obj>& heap) {


        int s = heap.size() - 1;
        int i = 0;
        int j = 2 * i + 1;
        int r = 2 * i + 2;
        int minChild = 0;

        swap(heap[0], heap[s]);

        while (r <= s) // stop condition at the last element
        {
            if (r < s && heap[r].value < heap[j].value)
                minChild = r;
            else
                minChild = j;

            if (heap[i].value > heap[minChild].value) {
                swap(heap[i], heap[minChild]);
                i = minChild;
                j = 2 * i + 1;
                r = 2 * i + 2;
            } else
                break;
        }
        heap.pop_back();



}


// get the data from the file
void getData(vector<obj>& arr) {
    ifstream file("input.txt");
    string line;

    if (!file.is_open())
        cout << "File not open" << endl;
    else {
        int index = 0;
        while (getline(file, line)) // fill vector
        {
            istringstream stream(line);
            obj o;
            stream >> o.date >> o.value;
            arr.push_back(o);
            index++; // next element
        }
    }

    file.close();
}

// amount of change of the exchange rate from the mean M at a given day
void updateValues(vector<obj>& arr, float mean) {
    for (int i = 0; i < arr.size(); i++)
        arr[i].value = arr[i].value - mean;
}

// dates of each of the N most positive changes
void mostPositive(vector<obj>& arr, int num) {
    buildMaxHeap(arr);


    for (int i = 0; i < num; i++)
    {
        obj d=arr.front();
        swap(arr.front(),arr.back());
        arr.pop_back();
        heapifyMax(arr,arr.size(),0);

        if (arr[i].value > 0)
        {
            cout << "Date: " << d.date << ", Value: " << d.value << endl;

        }
        else
            break;
    }
}

// dates of each of the N most negative changes
void mostNegative(vector<obj>& arr, int num)
{
    buildMinHeap(arr);


    for (int i = 0; i < num; i++)
    {
        obj d=arr.front();
        swap(arr.front(),arr.back());
        arr.pop_back();
        heapifyMin(arr,arr.size(),0);

        if (arr[i].value < 0)
        {
            cout << "Date: " << d.date << ", Value: " << d.value << endl;

        }
        else
            break;
    }
}

// calculate mean
float mean(vector<obj>& arr) {
    float avg = 0.0;
    for (int i = 0; i < arr.size(); i++)
        avg += arr[i].value;
    avg = avg / arr.size();
    return avg;
}

// maximum subsequence sum algorithm
float maxSubSeq(vector<obj>& arr) {
    int i = 1;
    int im = 0;
    int jm = 0;
    float Sij = 0;
    float Smax = 0;

    for (int j = 1; j <= arr.size(); j++) {
        Sij = Sij + arr[j].value;
        if (Sij > Smax) {
            Smax = Sij;
            im = i;
            jm = j;
        } else if (Sij < 0) {
            i = j + 1;
            Sij = 0;
        }
    }
    cout << "Start date is: " << arr[im].date << " End date is: " << arr[jm].date << endl;
    return Smax;
}

int main() {
    vector<obj> arr;
    getData(arr);

    int choice;
    cout << "Greetings!" << endl;
    cout << "How could we serve you today?" << endl;
    cout << "Service 1: Find the dates of the most positive changes  of the exchange rate from the mean M at a given day"
         << endl;
    cout << "Service 2: Find the dates of the most negative changes  of the exchange rate from the mean M at a given day"
         << endl;
    cout << "Service 3: Both service 1&2" << endl;
    cout << "Service 4: Find the start date and the end date of the contiguous period over which the sum\n"
            "of rate changes is maximum"
         << endl;
    cout << "Service 5: Both service 3&4" << endl;
    cout << "Please enter your choice below" << endl;
    cin >> choice;

    if (choice == 1) {
        int c;
        int number;
        cout << "Would you like to use the average as the mean here or would you like to insert a number of your own"
             << endl;
        cout << "1: average" << endl;
        cout << "2: my own" << endl;
        cin >> c;
        cout << "Moreover, how many values would you like" << endl;
        if (c == 1) {
            float f = mean(arr);
            updateValues(arr, f);
            mostPositive(arr, 10);
        } else {
            float x;
            cout << "Please enter a mean of your own" << endl;
            cin >> x;
            updateValues(arr, x);
            mostPositive(arr, 10);
        }
        cout << "Done! Thank you!" << endl;
    } else if (choice == 2) {
        int c;
        int number;
        cout << "Would you like to use the average as the mean here or would you like to insert a number of your own"
             << endl;
        cout << "1: average" << endl;
        cout << "2: my own" << endl;
        cin >> c;
        cout << "Moreover, how many values would you like" << endl;
        cin >> number;
        if (c == 1) {
            float e = mean(arr);
            updateValues(arr, e);
            mostNegative(arr, number);
        } else {
            float p = 0.0;
            cout << "Please enter a mean of your own" << endl;
            cin >> p;
            updateValues(arr, p);
            mostNegative(arr, number);
        }
        cout << "Done! Thank you!" << endl;
    } else if (choice == 3) {
        int c;
        int number;
        cout << "Would you like to use the average as the mean here or would you like to insert a number of your own"
             << endl;
        cout << "1: average" << endl;
        cout << "2: my own" << endl;
        cin >> c;
        cout << "Moreover, how many values would you like" << endl;
        cin >> number;
        if (c == 1) {
            float e = mean(arr);
            updateValues(arr, e);
            cout << "Top positive " << number << " changes are " << endl;
            mostPositive(arr, number);
            cout << "Top negative " << number << " changes are " << endl;
            mostNegative(arr, number);
        } else {
            float x;
            cout << "Please enter a mean of your own" << endl;
            cin >> x;
            cout << "Top positive " << number << " changes are " << endl;
            updateValues(arr, x);
            mostPositive(arr, number);
            cout << "Top negative " << number << " changes are " << endl;
            mostNegative(arr, number);
        }
        cout << "Done! Thank you!" << endl;
    }   else if(choice==4)
    {
        int c;
        cout << "Would you like to use the average as the mean here or would you like to insert a number of your own"
             << endl;
        cout << "1: average" << endl;
        cout << "2: my own" << endl;
        cin >> c;
        if(c==1)
        {
            float e= mean(arr);
            float g=0.0;
            updateValues(arr,e);
            g= maxSubSeq(arr);
            cout<<endl;
            cout<<"The summation between those dates is "<<g<<endl;

        }
        else
        {
            float x=0.0;
            float y=0.0;
            cout<<"Please enter a mean of your own"<<endl;
            cin>>x;
            updateValues(arr,x);
            y= maxSubSeq(arr);
            cout<<endl;
            cout<<"The summation between those dates is "<<y<<endl;


        }
    }
    else if(choice==5)
    {
        int c;
        int number;
        cout << "Would you like to use the average as the mean here or would you like to insert a number of your own"
             << endl;
        cout << "1: average" << endl;
        cout << "2: my own" << endl;
        cin >> c;
        cout << "Moreover, how many values would you like" << endl;
        cin >> number;
        if (c == 1)
        {
            float e = mean(arr);
            updateValues(arr, e);
            cout<<"Top positive "<<number<<" changes are "<<endl;
            mostPositive(arr, number);
            cout<<"Top negative "<<number<<" changes are "<<endl;
            mostNegative(arr, number);
        }
        else
        {
            float x;
            cout << "Please enter a mean of your own" << endl;
            cin >> x;
            cout << "Top positive " << number << " changes are " << endl;
            updateValues(arr, x);
            mostPositive(arr, number);
            cout << "Top negative " << number << " changes are " << endl;
            mostNegative(arr, number);
        }

        cout<<endl<<endl;
        cout<<"Now to get the start date and the end date of the contiguous period over which the sum of rate changes is maximum"<<endl;

        getData(arr); //initialize
        int b;
        cout << "Would you like to use the average as the mean here or would you like to insert a number of your own"
             << endl;
        cout << "1: average" << endl;
        cout << "2: my own" << endl;
        cin >> b;
        if(c==1)
        {
            float e= mean(arr);
            float g=0.0;
            updateValues(arr,e);
            g= maxSubSeq(arr);
            cout<<endl;
            cout<<"The summation between those dates is "<<g<<endl;

        }
        else
        {
            float x=0.0;
            float y=0.0;
            cout<<"Please enter a mean of your own"<<endl;
            cin>>x;
            updateValues(arr,x);
            y= maxSubSeq(arr);
            cout<<endl;
            cout<<"The summation between those dates is "<<y<<endl;


        }


    }



    return 0;
}