#include <bits/stdc++.h>


using namespace std;


void topk1(int arr[], int k, int n){
    auto shiftdown = [](int arr[], int i, int n){
        int v = arr[i];
        while(i* 2 + 1 < n){
            int j = i * 2 + 1;
            if(j + 1 < n && arr[j + 1] > arr[j])
                ++j;
            if(arr[j] > v){
                arr[i] = arr[j];
                i = j;
            } else
                break;
        }
        arr[i] = v;
    };
    for(int i = (k - 2) / 2; i >= 0; --i)
        shiftdown(arr, i, k);
    for(int i = k; i < n; ++i){
        if(arr[i] < arr[0]){
            swap(arr[0], arr[i]);
            shiftdown(arr, 0, k);
        }
    }
    for(int i = k - 1; i > 0; --i){
        swap(arr[0], arr[i]);
        shiftdown(arr, 0, i);
    }
}


void topk2(int arr[], int k, int n){
    int l = 0, r = n - 1;
    while(l < r){
        swap(arr[l], arr[rand() % (r - l + 1) + l]);
        int v = arr[l];
        int i = l + 1, j = r;
        while(true){
            while(i <= r && arr[i] < v) ++i;
            while(j > l && arr[j] > v)  --j;
            if(i >= j)
                break;
            swap(arr[i], arr[j]);
            ++i, --j;
        }
        swap(arr[l], arr[j]);
        if(j + 1 == k)
            break;
        else if(j + 1 < k)
            l = j + 1;
        else
            r = j - 1;
    }
    sort(arr, arr + k);
}

bool isSame(const int arr1[], const int arr2[], int n){
    for(int i = 0; i < n; ++i){
        if(arr1[i] != arr2[i])
            return false;
    }
    return true;
}


int main(int argc, char* argv[]){

    srand(time(nullptr));
    const int n = 1000000;
    const int k = 1000;

    int *arr = new int[n];
    for(int i = 0; i < n; ++i)
        arr[i] = rand() % n;
    int *arr2 = new int[n];
    copy(arr, arr + n, arr2);
    int *arr3 = new int[n];
    copy(arr, arr + n, arr3);

    clock_t t1 = clock();
    sort(arr, arr + n);
    clock_t t2 = clock();
    cout << (double)(t2 - t1) / CLOCKS_PER_SEC << endl;

    t1 = clock();
    topk1(arr2, k, n);
    t2 = clock();
    assert(isSame(arr, arr2, k));
    cout << (double)(t2 - t1) / CLOCKS_PER_SEC << endl;

    t1 = clock();
    topk2(arr3, k, n);
    t2 = clock();
    assert(isSame(arr, arr2, k));
    cout << (double)(t2 - t1) / CLOCKS_PER_SEC << endl;

    delete []arr;
    delete []arr2;
    delete []arr3;

    return 0;
}