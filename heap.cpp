#include <bits/stdc++.h>

using namespace std;


template <typename T>
class MaxIndexHeap{
private:
    int capacity;
    int count;
    int *indexes;
    int *reverse;
    T *data;

    void shiftDown(int i){
        int v = indexes[i];
        while(i*2+1 < count){
            int j = i*2+1;
            if(j+1 < count && data[indexes[j+1]] > data[indexes[j]])
                ++j;
            if(data[indexes[j]] > data[v]){
                indexes[i] = indexes[j];
                reverse[indexes[i]] = i;
                i = j;
            } else
                break;
        }
        indexes[i] = v;
        reverse[v] = i;
    }
    void shiftUp(int i){
        int v = indexes[i];
        while(i > 0){
            int j = (i - 1) / 2;
            if(data[indexes[j]] < data[v]){
                indexes[i] = indexes[j];
                reverse[reverse[i]] = i;
                i = j;
            } else
                break;
        }
        indexes[i] = v;
        reverse[v] = i;
    }
public:
    MaxIndexHeap(int n){
        count = 0;
        capacity = n;
        data = new T[n];
        indexes = new int[n];
        reverse = new int[n];
    }
    MaxIndexHeap(T arr[], int n){
        capacity = count = n;
        data = new T[n];
        indexes = new int[n];
        for(int i = 0; i < n; ++i){
            data[i] = arr[i];
            indexes[i] = reverse[i] = i;
        }
        for(int i = (n - 1) / 2; i >= 0; --i){
            shiftDown(i);
        }
    }
    void insert(T item){
        assert(count < capacity);
        data[count] = item;
        indexes[count] = count;
        reverse[count] = count;
        ++count;
        shiftUp(count - 1);
    }
    T extractMax(){
        T ret = data[indexes[0]];
        indexes[0] = indexes[--count];
        reverse[indexes[count]] = 0;
        shiftDown(0);
        return ret;
    }
    int extractMaxIndex(){
        int ret = indexes[0];
        indexes[0] = indexes[--count];
        reverse[indexes[count]] = 0;
        shiftDown(0);
        return ret;
    }
    T getItem(int i){
        return data[i];
    }
    void change(int i, T item){
        data[i] = item;
        int j = reverse[i];
        shiftDown(j);
        shiftUp(j);
    }
    ~MaxIndexHeap(){
        if(data)
            delete []data;
        if(indexes)
            delete []indexes;
        if(reverse)
            delete []reverse;
    }
};


int main(int argc, char* argv[]){

    return 0;
}