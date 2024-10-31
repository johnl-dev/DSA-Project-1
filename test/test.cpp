#include <iostream>
using namespace std;

int* extractMax(int arr[], int size)
{
    arr[0] = arr[size-1];
    arr[size-1] = 0;

    int i = 0;
    while (arr[i] < arr[2*i+1] || arr[i] < arr[2*i+2]) {
        if(size < 2*i+1) {
            break;
        }
        if (arr[2*i+2] < arr[2*i+1]) {
            swap(arr[i], arr[2*i+1]);
            i = 2*i+1;
        }
        if (size < 2*i+2) {
            break;
        }
        if(arr[2*i+1] < arr[2*i+2]){
            swap(arr[i], arr[2*i+1]);
            arr[2*i+2] = temp;
            i = 2*i+2;
        }
    }
    return arr;
}
