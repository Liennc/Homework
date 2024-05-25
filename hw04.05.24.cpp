#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int maxn = 1e5;
vector<int> g[maxn]; // рёбра из левой доли в правую
int mt[maxn]; //  (-1, если ни с какой)
bool used[maxn]; // путь dfs-ом

bool dfs(int v) {
    if (used[v])
        return false;
    used[v] = true;
    for (int u : g[v]) {
        if (mt[u] == -1 || dfs(mt[u])) {
            mt[u] = v;
            return true;
        }
    }
    return false;
}

int main() {
    int n; // количество вершин в левой доли
    int m; // количество вершин в правой доли

    memset(mt, -1, sizeof mt);
    int max_matching = 0; // Переменная для хранения размера максимального паросочетания
    for (int i = 0; i < n; i++) { // Проходим по всем вершинам левой доли
        memset(used, 0, sizeof used);
        if (dfs(i)) {
            max_matching++; // Увеличиваем размер паросочетания
        }
    }

    cout << max_matching << endl;

    return 0;
}

