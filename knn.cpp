#include <bits/stdc++.h>

using namespace std;


namespace utils {
    template<typename T>
    void printVec(const vector<T> &nums) {
        if (nums.empty()) {
            cout << "[]" << endl;
            return;
        }
        cout << "[ ";
        for (const T &u:nums)
            cout << u << " ";
        cout << "]" << endl;
    }

    template<typename T>
    void printVec(const vector<T> &nums, int l, int r) {
        if (l > r)
            return;
        cout << "[ ";
        for (int i = l; i <= r; i++)
            cout << nums[i] << " ";
        cout << "]" << endl;
    }

    template<typename T>
    void printVvec(const vector<vector<T>> &nums) {
        if (nums.empty())
            return;
        cout << "[" << endl;
        for (const vector<T> &v:nums) {
            cout << "[ ";
            for (const T &u:v)
                cout << u << " ";
            cout << "]" << endl;
        }
        cout << "]" << endl;
    }
}

class kNN {
private:
    vector<vector<double>> x_train;
    vector<int> y_train;
    int k;
public:
    kNN(int n_neighbors) : k(n_neighbors) {}

    void fit(const vector<vector<double>> &X_train, const vector<int> &Y_train) {
        assert(X_train.size() == Y_train.size());
        assert(!X_train[0].empty());
        x_train = X_train;
        y_train = Y_train;
    }

    vector<int> predict(const vector<vector<double>> &x_predict) {
        int m = x_predict.size();
        assert(m > 0);
        assert(x_predict[0].size() == x_train[0].size());
        vector<int> res(m);
        for (int i = 0; i < m; ++i) {
            vector<pair<double, int>> distances(x_train.size());
            for (int j = 0; j < x_train.size(); ++j) {
                int d = 0;
                for (int x = 0; x < x_train[j].size(); ++x) {
                    d += pow(x_train[j][x] - x_predict[i][x], 2);
                }
                d = sqrt(d);
                distances[j] = make_pair(d, j);
            }
            sort(distances.begin(), distances.end());
            partial_sort(distances.begin(), distances.begin() + k, distances.end());
            unordered_map<int, int> f;
            for (int j = 0; j <= k; ++j)
                ++f[y_train[distances[j].second]];
            int cnt = INT_MIN;
            int pred = -1;
            for (const auto[p, q] : f) {
                if (q > cnt) {
                    cnt = q;
                    pred = p;
                }
            }
            res[i] = pred;
        }
        return res;
    }
};


int main(int argc, char* argv[]) {


    vector<vector<double>> raw_data_X = {{3.393533211, 2.331273381},
                                         {3.110073483, 1.781539638},
                                         {1.343808831, 3.368360954},
                                         {3.582294042, 4.679179110},
                                         {2.280362439, 2.866990263},
                                         {7.423436942, 4.696522875},
                                         {5.745051997, 3.533989803},
                                         {9.172168622, 2.511101045},
                                         {7.792783481, 3.424088941},
                                         {7.939820817, 0.791637231}
    };
    vector<int> raw_data_y = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1};

    kNN knn_cls(6);
    knn_cls.fit(raw_data_X, raw_data_y);

    vector<vector<double>> x_pred = {{8.093607318, 3.365731514}};
    utils::printVec(knn_cls.predict(x_pred));

    return 0;
}