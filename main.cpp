#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;


struct obj { // node
    float value;
    string date;
};

// heapify algorithm for max heap
void heapifyMax(vector<obj>& v, int n, int i) {
    int max=i; // parent
    int l=2*i+1; // left child
    int r=2*i+2; // right child

    // left child >> parent
    if (l<n && v[l].value > v[max].value)
        max=l;

    // right child >> parent
    if (r<n && v[r].value > v[max].value)
        max=r;

    // parent is not the largest
    if (max!=i) {
        swap(v[i], v[max]); // therefore swap with the largest child

        // another subtree
        heapifyMax(v, n, max);
    }
}

// ascending order using heapify
void buildMaxHeap(vector<obj>& heap)
{
    // build max-heap
    for (int i=(heap.size()-1) / 2-1; i >= 0; i--)
        heapifyMax(heap, heap.size(), i);
}



// heapify algorithm for min heap
void heapifyMin(vector<obj>& v, int n, int i)
{
    int min=i;
    int l=2*i+1; // left child
    int r=2*i+2; // right child

    // left child < parent
    if (l < n && v[l].value < v[min].value)
        min = l;

    // right child < parent
    if (r < n && v[r].value < v[min].value)
        min = r;

    // parent is not the smallest
    if (min != i) {
        swap(v[i], v[min]); // therefore swap with the smallest child

        // another subtree
        heapifyMin(v, n, min);
    }
}

// descending order using heapify
void buildMinHeap(vector<obj>& heap) {
    // build min-heap
    for (int i=(heap.size()-1) / 2 - 1; i >= 0; i--)
        heapifyMin(heap, heap.size(), i);

}

// get the data from the file
void getData(vector<obj>& v) {
    ifstream file("input.txt");
    string line;

    if (!file.is_open())
        cout << "File not open" << endl;
    else {
        int index = 0;
        while (getline(file, line)) // fill vector
        {
            istringstream stream(line); //https://www.geeksforgeeks.org/processing-strings-using-stdistringstream/
            obj o;
            stream>>o.date>>o.value; //using stream and >> will read until whitespace is reached
            v.push_back(o);
            index++; // next element
        }
    }
    file.close();
}

// amount of change of the exchange rate from the mean M at a given day
void updateValues(vector<obj>& heap, float mean)
{
    for (int i = 0; i < heap.size(); i++)
        heap[i].value = heap[i].value - mean;
}

// dates of each of the N most positive changes
void mostPositive(vector<obj>& heap, int num)
{
    buildMaxHeap(heap);


    for (int i = 0; i < num; i++)
    {
        obj d=heap.front(); //d is now the front element of the array
        swap(heap.front(),heap.back()); //swap first and last elements
        heap.pop_back(); //delete last element
        heapifyMax(heap,heap.size(),0); //adjust the heap after deletion

        if (heap[i].value > 0)
            cout << "Date: " << d.date << ", Value: " << d.value << endl; 
        else
            break;
    }
}

// dates of each of the N most negative changes
void mostNegative(vector<obj>& heap, int num)
{
    buildMinHeap(heap);

    for (int i = 0; i < num; i++)
    {
        obj d=heap.front(); //d is now the front element of the array
        swap(heap.front(),heap.back()); //swap first and last elements
        heap.pop_back(); //delete last element
        heapifyMin(heap,heap.size(),0); //adjust the heap after deletion

        if (heap[i].value < 0)
            cout << "Date: " << d.date << ", Value: " << d.value << endl;
        else
            break;
    }
}

// calculate mean
float mean(vector<obj>& v) {
    float avg = 0.0;
    for (int i = 0; i < v.size(); i++)
        avg += v[i].value;
    avg = avg / v.size();
    return avg;
}

// maximum subsequence sum algorithm
float maxSubSeq(vector<obj>& v) {
    int i = 1;
    int im = 0;
    int jm = 0;
    float Sij = 0;
    float Smax = 0;

    for (int j = 1; j <= v.size(); j++) {
        Sij = Sij + v[j].value;
        if (Sij > Smax) {
            Smax = Sij;
            im = i;
            jm = j;
        } else if (Sij < 0) {
            i = j + 1;
            Sij = 0;
        }
    }
    cout << "Start date is: " << v[im].date << " End date is: " << v[jm].date << endl;
    return Smax;
}

int main() {
    vector<obj> heap;
    getData(heap);

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
            float f = mean(heap);
            updateValues(heap, f);
            mostPositive(heap, 10);
        } else {
            float x;
            cout << "Please enter a mean of your own" << endl;
            cin >> x;
            updateValues(heap, x);
            mostPositive(heap, 10);
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
            float e = mean(heap);
            updateValues(heap, e);
            mostNegative(heap, number);
        } else {
            float p = 0.0;
            cout << "Please enter a mean of your own" << endl;
            cin >> p;
            updateValues(heap, p);
            mostNegative(heap, number);
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
            float e = mean(heap);
            updateValues(heap, e);
            cout << "Top positive " << number << " changes are " << endl;
            mostPositive(heap, number);
            cout << "Top negative " << number << " changes are " << endl;
            mostNegative(heap, number);
        } else {
            float x;
            cout << "Please enter a mean of your own" << endl;
            cin >> x;
            cout << "Top positive " << number << " changes are " << endl;
            updateValues(heap, x);
            mostPositive(heap, number);
            cout << "Top negative " << number << " changes are " << endl;
            mostNegative(heap, number);
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
            float e= mean(heap);
            float g=0.0;
            updateValues(heap,e);
            g= maxSubSeq(heap);
            cout<<endl;
            cout<<"The summation between those dates is "<<g<<endl;

        }
        else
        {
            float x=0.0;
            float y=0.0;
            cout<<"Please enter a mean of your own"<<endl;
            cin>>x;
            updateValues(heap,x);
            y= maxSubSeq(heap);
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
            float e = mean(heap);
            updateValues(heap, e);
            cout<<"Top positive "<<number<<" changes are "<<endl;
            mostPositive(heap, number);
            cout<<"Top negative "<<number<<" changes are "<<endl;
            mostNegative(heap, number);
        }
        else
        {
            float x;
            cout << "Please enter a mean of your own" << endl;
            cin >> x;
            cout << "Top positive " << number << " changes are " << endl;
            updateValues(heap, x);
            mostPositive(heap, number);
            cout << "Top negative " << number << " changes are " << endl;
            mostNegative(heap, number);
        }

        cout<<endl<<endl;
        cout<<"Now to get the start date and the end date of the contiguous period over which the sum of rate changes is maximum"<<endl;

        getData(heap); //initialize
        int b;
        cout << "Would you like to use the average as the mean here or would you like to insert a number of your own"
             << endl;
        cout << "1: average" << endl;
        cout << "2: my own" << endl;
        cin >> b;
        if(c==1)
        {
            float e= mean(heap);
            float g=0.0;
            updateValues(heap,e);
            g= maxSubSeq(heap);
            cout<<endl;
            cout<<"The summation between those dates is "<<g<<endl;

        }
        else
        {
            float x=0.0;
            float y=0.0;
            cout<<"Please enter a mean of your own"<<endl;
            cin>>x;
            updateValues(heap,x);
            y= maxSubSeq(heap);
            cout<<endl;
            cout<<"The summation between those dates is "<<y<<endl;


        }


    }



    return 0;
}