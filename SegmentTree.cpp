#include <bits/stdc++.h>

using namespace std;

template <typename T>
class SegmentTree {
private:
    T *tree;
    T *data;
    int sz;
    function<T(T, T)> merger;

    int leftChild(int treeIndex) { return treeIndex * 2 + 1; }

    int rightChild(int treeIndex) { return treeIndex * 2 + 2; }

    void buildSegmentTree(int treeIndex, int l, int r) {
        if (l == r) {
            tree[treeIndex] = data[l];
            return;
        }
        int leftTreeIndex = leftChild(treeIndex);
        int rightTreeIndex = rightChild(treeIndex);
        int mid = (r - l) / 2 + l;
        buildSegmentTree(leftTreeIndex, l, mid);
        buildSegmentTree(rightTreeIndex, mid + 1, r);
        tree[treeIndex] = merger(tree[leftTreeIndex], tree[rightTreeIndex]);
    }

    T query(int treeIndex, int l, int r, int queryL, int queryR) {
        if (l == queryL && r == queryR)
            return tree[treeIndex];
        int mid = (r - l) / 2 + l;
        int leftTreeIndex = leftChild(treeIndex);
        int rightTreeIndex = rightChild(treeIndex);
        if (queryL >= mid + 1)
            return query(rightTreeIndex, mid + 1, r, queryL, queryR);
        else if (queryR <= mid)
            return query(leftTreeIndex, l, mid, queryL, queryR);
        T leftResult = query(leftTreeIndex, l, mid, queryL, mid);
        T rightResult = query(rightTreeIndex, mid + 1, r, mid + 1, queryR);
        return merger(leftResult, rightResult);
    }

    void update(int treeIndex, int l, int r, int index, T e) {
        if (l == r) {
            tree[treeIndex] = e;
            return;
        }
        int mid = (r - l) / 2 + l;
        int leftTreeIndex = leftChild(treeIndex);
        int rightTreeIndex = rightChild(treeIndex);
        if (index <= mid)
            update(leftTreeIndex, l, mid, index, e);
        else
            update(rightTreeIndex, mid + 1, r, index, e);
        tree[treeIndex] = merger(tree[leftTreeIndex], tree[rightTreeIndex]);
    }

public:
    SegmentTree(T arr[], int n, function<T(T, T)> merger) {
        this->merger = merger;
        this->sz = n;
        if (sz > 0) {
            this->data = new T[sz];
            for (int i = 0; i < sz; i++)
                data[i] = arr[i];
            tree = new T[sz * 4];
            buildSegmentTree(0, 0, sz - 1);
        }
    }

    SegmentTree(vector<T> arr, function<T(T, T)> merger) {
        this->merger = merger;
        this->sz = arr.size();
        if (sz > 0) {
            this->data = new T[sz];
            for (int i = 0; i < sz; i++)
                data[i] = arr[i];
            tree = new T[sz * 4];
            buildSegmentTree(0, 0, sz - 1);
        }
    }

    ~SegmentTree() {
        if (sz > 0) {
            delete[]data;
            delete[]tree;
        }
    }

    int size() { return sz; }

    T get(int index) {
        if (index < 0 || index >= sz)
            throw invalid_argument("Index is illegal.");
        return data[index];
    }

    T query(int queryL, int queryR) {
        if (queryL < 0 || queryR >= sz || queryL > queryR)
            throw invalid_argument("Query Range is illegal.");
        return query(0, 0, sz - 1, queryL, queryR);
    }

    void update(int index, T e) {
        if (index < 0 || index >= sz)
            throw invalid_argument("Index is illegal.");
        data[index] = e;
        update(0, 0, sz - 1, index, e);
    }

};

int main() {

//    int arr[] = {-2, 0, 3, -5, 2, -1};
//
//    auto* segmentTree = new SegmentTree<int>(arr, sizeof(arr) / sizeof(int), [](int a, int b){
//        return a + b;
//    });

    vector<int> arr = {-2, 0, 3, -5, 2, -1};

    auto* segmentTree = new SegmentTree<int>(arr, [](int a, int b){
        return a + b;
    });

    cout << segmentTree->query(0, 2) << endl;
    cout << segmentTree->query(2, 5) << endl;
    cout << segmentTree->query(0, 5) << endl;

    segmentTree->update(2, 10);
    cout << segmentTree->query(0, 5) << endl;

    delete segmentTree;

    return 0;
}