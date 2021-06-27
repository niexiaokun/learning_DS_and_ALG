#include <bits/stdc++.h>


using namespace std;


// b表示模式串，m表示模式串的长度
vector<int> getNexts(string b) {
    vector<int> next(b.size());
    next[0] = -1;
    int k = -1;
    for (int i = 1; i < b.size(); ++i) {
        while (k != -1 && b[k + 1] != b[i]) {
            k = next[k];
        }
        if (b[k + 1] == b[i]) {
            ++k;
        }
        next[i] = k;
    }
    return next;
}
// a, b分别是主串和模式串；n, m分别是主串和模式串的长度。
vector<int> kmp(string& a, string& b, const vector<int>& next) {
    int n = a.size(), m = b.size();
    int j = 0;
    vector<int> res;
    for (int i = 0; i < n; ++i) {
        while (j > 0 && a[i] != b[j]) { // 一直找到a[i]和b[j]
            j = next[j - 1] + 1;
        }
        if (a[i] == b[j]) {
            ++j;
        }
        if (j == m) { // 找到匹配模式串的了
            res.emplace_back(i - m + 1);
            j = next[j - 1] + 1;
        }
    }
    return res;
}


int main(int argc, char* argv[]){

    return 0;
}