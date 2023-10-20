#include <stdio.h>

int count=0;
void merge(int arr[], int left[], int leftSize, int right[], int rightSize);
void mergeSort(int arr[], int size);


void merge(int arr[], int left[], int leftSize, int right[], int rightSize){ // function to merge two sorted parts.
    int i = 0, j = 0, k = 0;
    
    while (i < leftSize && j < rightSize) {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else{
            arr[k++] = right[j++];
            count ++;
        }
    }
    
    while (i < leftSize){
        arr[k++] = left[i++];
    }
    while (j < rightSize){
        arr[k++] = right[j++];
    }
}

void mergeSort(int arr[], int size){    // Function that performs sorting.
    if(size<= 1){
        return;
    }
    int mid = size / 2;
    int left[mid];
    int right[size - mid];
    
    for (int i = 0; i < mid; i++){
        left[i] = arr[i];
    }
    for (int i = mid; i < size; i++){
        right[i - mid] = arr[i];
    }
    mergeSort(left, mid);       // recursively calling for smaller halves after breaking into smaller sub-array.
    mergeSort(right, size - mid);
    
    merge(arr, left, mid, right, size - mid);   // after that merging those chunks.
}

int main() {            // main body.
    int n;
    printf("\nEnter no of elements : ");
    scanf("%d", &n);
    
    int arr[n];
    printf("Enter the array data : ");
    for (int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    mergeSort(arr, n);
    
    printf("No of inversion possible : %d\n",count);
    return 0;
}
