#include <bits/stdc++.h>

using namespace std;

void __mergesort(int arr[], int aux[], int l, int r) {
    if (l >= r)
        return;
    int mid = (r - l) / 2 + l;
    __mergesort(arr, aux, l, mid);
    __mergesort(arr, aux, mid + 1, r);
    for (int i = l; i <= r; ++i)
        aux[i] = arr[i];
    int i = l, j = mid + 1;
    for (int k = l; k <= r; ++k) {
        if (i > mid)
            arr[k] = aux[j++];
        else if (j > r)
            arr[k] = aux[i++];
        else if (aux[i] < aux[j])
            arr[k] = aux[i++];
        else
            arr[k] = aux[j++];
    }
}

void mergesort(int arr[], int n) {
    int *aux = new int[n];
    __mergesort(arr, aux, 0, n - 1);
}


void __quicksort(int arr[], int l, int r) {
    if (l >= r)
        return;
    swap(arr[l], arr[rand() % (r - l + 1) + l]);
    int v = arr[l];
    int i = l + 1, j = r;
    while (true) {
        while (i <= r && arr[i] < v) ++i;
        while (j > l && arr[j] > v) --j;
        if (i >= j)
            break;
        swap(arr[i], arr[j]);
        ++i, --j;
    }
    swap(arr[l], arr[j]);
    __quicksort(arr, l, j - 1);
    __quicksort(arr, j + 1, r);
}

void quicksort(int arr[], int n) {
    __quicksort(arr, 0, n - 1);
}

void shiftdown(int arr[], int i, int n) {
    int v = arr[i];
    while (i * 2 + 1 < n) {
        int j = i * 2 + 1;
        if (j + 1 < n && arr[j + 1] > arr[j])
            ++j;
        if (v < arr[j]) {
            arr[i] = arr[j];
            i = j;
        } else {
            break;
        }
    }
    arr[i] = v;
}

void heapsort(int arr[], int n) {
    for (int i = (n - 1 - 1) / 2; i >= 0; --i)
        shiftdown(arr, i, n);
    int j = n - 1;
    while (j >= 0) {
        swap(arr[0], arr[j]);
        shiftdown(arr, 0, j);
        --j;
    }
}

bool isSorted(const int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        if (arr[i] > arr[i + 1])
            return false;
    }
    return true;
}

bool isSame(const int arr1[], const int arr2[], int n) {
    for(int i = 0; i < n; ++i){
        if(arr1[i] != arr2[i])
            return false;
    }
    return true;
}


int main(int argc, char* argv[]) {

    srand(time(nullptr));
    int n = 1000000;
    int *arr = new int[n];
    for (int i = 0; i < n; ++i)
        arr[i] = rand() % n;
    int* arr2 = new int[n];
    copy(arr, arr + n, arr2);
    int* arr3 = new int[n];
    copy(arr, arr + n, arr3);
    int* arr4 = new int[n];
    copy(arr, arr + n, arr4);
    int* arr5 = new int[n];
    copy(arr, arr + n, arr5);
    int* arr6 = new int[n];
    copy(arr, arr + n, arr6);

    clock_t t1, t2;
    double cost_t;

    t1 = clock();
    mergesort(arr, n);
    t2 = clock();
    assert(isSorted(arr, n));
    cost_t = (double) (t2 - t1) / CLOCKS_PER_SEC;
    printf("mergeSort : %f\n", cost_t);

    t1 = clock();
    quicksort(arr2, n);
    t2 = clock();
    assert(isSorted(arr2, n));
    cost_t = (double) (t2 - t1) / CLOCKS_PER_SEC;
    printf("quickSort : %f\n", cost_t);

    t1 = clock();
    heapsort(arr3, n);
    t2 = clock();
    assert(isSorted(arr3, n));
    cost_t = (double) (t2 - t1) / CLOCKS_PER_SEC;
    printf("heapSort  : %f\n", cost_t);

    t1 = clock();
    sort(arr4, arr4 + n);
    t2 = clock();
    assert(isSorted(arr4, n));
    cost_t = (double) (t2 - t1) / CLOCKS_PER_SEC;
    printf("stl quickSort : %f\n", cost_t);

    t1 = clock();
    stable_sort(arr5, arr5 + n);
    t2 = clock();
    assert(isSorted(arr5, n));
    cost_t = (double) (t2 - t1) / CLOCKS_PER_SEC;
    printf("stl mergeSort : %f\n", cost_t);

    t1 = clock();
    partial_sort(arr6, arr6 + n, arr6 + n);
    t2 = clock();
    assert(isSorted(arr6, n));
    cost_t = (double) (t2 - t1) / CLOCKS_PER_SEC;
    printf("stl heapSort  : %f\n", cost_t);

    assert(isSame(arr, arr2, n));
    assert(isSame(arr, arr3, n));
    assert(isSame(arr, arr4, n));
    assert(isSame(arr, arr5, n));
    assert(isSame(arr, arr6, n));

    return 0;
}

