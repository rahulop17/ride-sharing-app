#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

unordered_map<int, int> dijkstra(int src, const unordered_map<int, vector<pair<int, int>>>& adj) {
    unordered_map<int, int> dist;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, src));
    dist[src] = 0;

    while (!pq.empty()) {
        pair<int, int> top = pq.top(); pq.pop();
        int d = top.first;
        int u = top.second;

        if (d > dist[u]) continue;

        const vector<pair<int, int>>& neighbors = adj.at(u);
        for (size_t k = 0; k < neighbors.size(); ++k) {
            int v = neighbors[k].first;
            int w = neighbors[k].second;

            if (!dist.count(v) || d + w < dist[v]) {
                dist[v] = d + w;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    return dist;
}

// Passenger structure
struct Passenger {
    int pickup;
    int dropoff;
};

int main() {
    int V, E;
    cin >> V >> E;

    unordered_map<int, vector<pair<int, int>>> adj;

    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w)); // undirected
    }

    int P;
    cin >> P;
    vector<Passenger> passengers(P);
    set<int> relevantNodes;

    for (int i = 0; i < P; ++i) {
        int x1, x2;
        cin >> x1 >> x2;
        passengers[i] = {x1, x2};
        relevantNodes.insert(x1);
        relevantNodes.insert(x2);
    }

    unordered_map<int, unordered_map<int, int>> allDistances;
    for (set<int>::iterator it = relevantNodes.begin(); it != relevantNodes.end(); ++it) {
        allDistances[*it] = dijkstra(*it, adj);
    }

    for (int i = 0; i < P; ++i) {
        for (int j = i + 1; j < P; ++j) {
            int X1 = passengers[i].pickup;
            int X2 = passengers[i].dropoff;
            int Y1 = passengers[j].pickup;
            int Y2 = passengers[j].dropoff;

            int dXsolo = allDistances[X1][X2];
            int dYsolo = allDistances[Y1][Y2];

            int d1 = INF, d2 = INF, d3 = INF, d4 = INF;

            // Scenario 1: X1 -> Y1 -> X2 -> Y2
            if (allDistances[X1].count(Y1) && allDistances[Y1].count(X2) && allDistances[X2].count(Y2)) {
                int total = allDistances[X1][Y1] + allDistances[Y1][X2] + allDistances[X2][Y2];
                if (total <= 1.25 * dXsolo && total <= 1.25 * dYsolo)
                    d1 = total;
            }

            // Scenario 2: X1 -> Y1 -> Y2 -> X2
            if (allDistances[X1].count(Y1) && allDistances[Y1].count(Y2) && allDistances[Y2].count(X2)) {
                int total = allDistances[X1][Y1] + allDistances[Y1][Y2] + allDistances[Y2][X2];
                if (total <= 1.25 * dXsolo && total <= 1.25 * dYsolo)
                    d2 = total;
            }

            // Scenario 3: Y1 -> X1 -> X2 -> Y2
            if (allDistances[Y1].count(X1) && allDistances[X1].count(X2) && allDistances[X2].count(Y2)) {
                int total = allDistances[Y1][X1] + allDistances[X1][X2] + allDistances[X2][Y2];
                if (total <= 1.25 * dXsolo && total <= 1.25 * dYsolo)
                    d3 = total;
            }

            // Scenario 4: Y1 -> X1 -> Y2 -> X2
            if (allDistances[Y1].count(X1) && allDistances[X1].count(Y2) && allDistances[Y2].count(X2)) {
                int total = allDistances[Y1][X1] + allDistances[X1][Y2] + allDistances[Y2][X2];
                if (total <= 1.25 * dXsolo && total <= 1.25 * dYsolo)
                    d4 = total;
            }

            // Scenario 5: travel alone
            int d5 = dXsolo + dYsolo;

            int finalDistance = min(min(min(min(d1, d2), d3), d4), d5);

            cout << "Passenger " << i << " and " << j << " -> Min shared cost = " << finalDistance << endl;
        }
    }

    return 0;
}
