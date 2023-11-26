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
void mostPositive(obj arr[],int num)
{
    buildMinHeap(arr,arraySize);
    for (int i = 0; i < num; i++)
    {
        if (arr[i].value > 0)
        {
            cout << "Date: " << arr[i].date << ", Value: " << arr[i].value  << endl;

        }
        else
            break;

    }

}
//dates of each of the N most negative changes
void mostNegative(obj arr[],int num)
{
    buildMaxHeap(arr,arraySize);
    for (int i = 0; i < num; i++)
    {
        if (arr[i].value < 0)
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
    float Sij=0;
    float Smax=0;
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
    cout<<"Start date is: "<<arr[i].date<<" End date is: "<<arr[jm].date<<endl;
    return Smax;

}

int main()
{
    obj arr[arraySize];
    getData(arr);

   /* for (int i = 0; i < arraySize; i++) {
        cout << "Date: " << arr[i].date << ", Value: " << arr[i].value << endl;
    } */
int choice;
    cout<<"Greetings!"<<endl;
    cout<<"How could we serve you today?"<<endl;
    cout<<"Service 1: Find the dates of the most positive changes  of the exchange rate from the mean M at a given day"<<endl;
    cout<<"Service 2: Find the dates of the most negative changes  of the exchange rate from the mean M at a given day"<<endl;
    cout<<"Service 3: Both service 1&2"<<endl;
    cout<<"Service 4: Find the start date and the end date of the contiguous period over which the sum\n"
          "of rate changes is maximum"<<endl;
    cout<<"Service 5: Both service 3&4"<<endl;
    cout<<"Please enter your choice below"<<endl;
    cin>>choice;

    if(choice==1)
    {
        int c;
        int number;
        cout<<"Would you like to use the average as the mean here or would you like to insert a number of your own"<<endl;
        cout<<"1: average"<<endl;
        cout<<"2: my own"<<endl;
        cin>>c;
        cout<<"Moreover, how many values would you like"<<endl;
        if(c==1)
        {
            float f= mean(arr);
            updateValues(arr,f);
            mostPositive(arr,10);
        }
        else
        {
            float x;
            cout<<"Please enter a mean of your own"<<endl;
            cin>>x;
            updateValues(arr,x);
            mostPositive(arr,10);
        }
        cout<<"Done! Thank you!"<<endl;
    }
    else if(choice==2)
    {
        int c;
        int number;
        cout<<"Would you like to use the average as the mean here or would you like to insert a number of your own"<<endl;
        cout<<"1: average"<<endl;
        cout<<"2: my own"<<endl;
        cin>>c;
        cout<<"Moreover, how many values would you like"<<endl;
        cin>>number;
        if(c==1)
        {
            float e= mean(arr);
            updateValues(arr,e);
            mostNegative(arr,number);
        }
        else
        {
            float p=0.0;
            cout<<"Please enter a mean of your own"<<endl;
            cin>>p;
            updateValues(arr,p);
            mostNegative(arr,number);
        }
        cout<<"Done! Thank you!"<<endl;
    }
    else if(choice==3)
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
        if (c == 1) {
            float e = mean(arr);
            updateValues(arr, e);
            cout<<"Top positive "<<number<<" changes are "<<endl;
            mostPositive(arr, number);
            cout<<"Top negative "<<number<<" changes are "<<endl;
            mostNegative(arr, number);
        } else {
            float x;
            cout << "Please enter a mean of your own" << endl;
            cin >> x;
            cout<<"Top positive "<<number<<" changes are "<<endl;
            updateValues(arr,x);
            mostPositive(arr, number);
            cout<<"Top negative "<<number<<" changes are "<<endl;
            mostNegative(arr, number);
        }
        cout << "Done! Thank you!" << endl;
    }

    else if(choice==4)
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
            g= maxSubSeq(arr,arraySize);
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
            y= maxSubSeq(arr,arraySize);
            cout<<endl;
            cout<<"The summation between those dates is "<<y<<endl;


        }
    }
    else if(choice==5)
    {

    }



    return 0;
}

