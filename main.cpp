#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

const int arraySize = 6668; // array size

struct obj { //node
    float value;
    string date;
};
// heapify algorithm for max heap
void heapifyMax(obj arr[], int n, int i)
{
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
 // ascending order
void buildMaxHeap(obj arr[], int n) {
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
// heapify algorithm for min heap
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

// descending order
void buildMinHeap(obj arr[], int n) {
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
//get the data from the file
void getData(obj arr[]) {
    ifstream file("input.txt");
    string line;

    if (!file.is_open())
        cout << "File not open" << endl;
    else
    {
        cout << "File is open" << endl;
        int index = 0;
        while (getline(file, line))//fill array
            {
                //cout << "Read: " << line << endl;
                istringstream stream(line); //https://www.geeksforgeeks.org/processing-strings-using-stdistringstream/
                stream >> arr[index].date >> arr[index].value; //using stream and >> will read until whitespace is reached
                index++; //next element
            }
    }

    file.close();
}
//amount of change of
//the exchange rate from the mean M at a given day
void updateValues(obj arr[],float mean)
{
    for (int i = 0; i < arraySize; i++)
        arr[i].value = arr[i].value - mean;

}
//dates of each of the N most positive changes
void mostPositive(obj arr[],int num, float mean)
{
    buildMinHeap(arr,arraySize);
    for (int i = 0; i < num; i++)
    {
        if (arr[i].value > mean)
        {
            cout << "Date: " << arr[i].date << ", Value: " << arr[i].value  << endl;

        }
        else
            break;

    }

}
//dates of each of the N most negative changes
void mostNegative(obj arr[],int num,float mean)
{
    buildMaxHeap(arr,arraySize);
    for (int i = 0; i < num; i++)
    {
        if (arr[i].value < mean)
            cout << "Date: " << arr[i].date << ", Value: " << arr[i].value << endl;
        else
            break;
    }

}
//calc mean
float mean(obj arr[])
{
    float avg=0.0;
    for (int i = 0; i < arraySize; i++)
        avg += arr[i].value;
    avg=avg/arraySize;
    return avg;

}
//maximum subsequence sum algorithm
float maxSubSeq(obj arr[], int n)
{
    int i=1;
    int im=0;
    int jm=0;
    float Sij=0,Smax=0;
    int newI;
    int newJ;
    for(int j=1;j<=n;j++)
    {
        Sij=Sij+arr[j].value;
        if(Sij>Smax)
        {


            Smax=Sij;im=i;
            jm=j;
        }
        else if (Sij<0)
        {i=j+1; Sij=0;}
    }
    cout<<arr[i].date<<" "<<arr[jm].date;
    return Smax;

}

int main()
{
    obj arr[arraySize];
    getData(arr);
    float f= mean(arr);
    updateValues(arr,f);
  // mostPositive(arr,50,1.18555);
   //mostNegative(arr,10,f);
   float m=0.0;
    m=maxSubSeq(arr,arraySize);
    cout<<endl;
    cout<<"Sum is "<<m<<endl;
    mostNegative(arr,10,f);

   // buildMinHeap(arr,arraySize);
   /* for (int i = 0; i < arraySize; i++) {
        cout << "Date: " << arr[i].date << ", Value: " << arr[i].value << endl;
    } */


    return 0;
}

