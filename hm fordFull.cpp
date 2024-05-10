#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e9; // Бесконечность для представления очень большого числа

// Функция для поиска увеличивающего пути с помощью обхода в глубину (DFS)
bool dfs(vector<vector<int>>& graph, vector<int>& parent, vector<bool>& visited, int u, int sink) {
    visited[u] = true;
    if (u == sink) return true;

    for (int v = 0; v < graph.size(); ++v) {
        if (!visited[v] && graph[u][v] > 0) {
            parent[v] = u;
            if (dfs(graph, parent, visited, v, sink)) return true;
        }
    }
    return false;
}

// Реализация алгоритма Форда-Фалкерсона
int fordFulkerson(vector<vector<int>>& graph, int source, int sink) {
    int maxFlow = 0;
    vector<int> parent(graph.size(), -1);

    while (true) {
        vector<bool> visited(graph.size(), false);
        if (!dfs(graph, parent, visited, source, sink)) break;

        // Находим минимальную пропускную способность на пути
        int pathFlow = INF;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, graph[u][v]);
        }

        // Обновляем пропускные способности рёбер
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            graph[u][v] -= pathFlow;
            graph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main() {
    vector<vector<int>> graph = {
        {0, 8, 0, 0, 3, 0},
        {0, 0, 9, 0, 0, 0},
        {0, 0, 0, 0, 7, 2},
        {0, 0, 0, 0, 0, 5},
        {0, 0, 0, 4, 0, 0},
        {0, 0, 0, 0, 0, 0}
    };

    int source = 0; // Исток
    int sink = graph.size() - 1; // Сток

    int maxFlow = fordFulkerson(graph, source, sink);
    cout << "max " << maxFlow << endl;

    return 0;
}