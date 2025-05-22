#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

vector<vector<int>> convertMatrixToList(const string& filename) {
    vector<vector<int>> L;
    fstream file;
    file.open(filename,ios::in);
    if (!file.is_open()) {
        cout << "Could not open file " << filename << endl;
        return L;
    }
    string sizeM;
    getline(file, sizeM);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        vector<int> v;
        int col=0;
        int key;
        while (ss >> key) {
            if(key == 1) v.push_back(col);
            col++;
        }
        int sizeV = v.size();
        v.insert(v.begin(),sizeV);
        L.push_back(v);
    }
    file.close();
    return L;
}

vector<vector<int>> convertListToMatrix(const string& filename) {
    fstream file;
    file.open(filename,ios::in);
    if (!file.is_open()) {
        cout << "Could not open file " << filename << endl;
        return vector<vector<int>>();
    }
    string sizeM;
    getline(file, sizeM);
    int n=stoi(sizeM);
    vector<vector<int>> M(n,vector<int>(n,0));
    string line;
    int row=0;
    while (getline(file, line)&&row<n) {
        stringstream ss(line);
        int sizeline;
        int col;
        ss >> sizeline;
        for (int i = 0; i < sizeline; i++) {
            ss >> col;
            M[row][col]=1;
        }
        row++;
    }
    file.close();
    return M;
}

bool isDirected(const vector<vector<int>>& adjMatrix) {
    for (int i = 0; i < adjMatrix.size(); i++) {
        for(int j = 0; j < adjMatrix[i].size(); j++) {
            if(adjMatrix[i][j] != adjMatrix[j][i]) return true;
        }
    }
    return false;
}

int countVertices(const vector<vector<int>>& adjMatrix) {
    return adjMatrix.size();
}

int countEdges(const vector<vector<int>>& adjMatrix) {
    int cnt=0;
    for (int i = 0; i < adjMatrix.size(); i++) {
        for(int j = 0; j < adjMatrix[i].size(); j++) {
            if(adjMatrix[i][j] == 1) cnt++;
        }
    }
    return isDirected(adjMatrix) ? cnt : cnt/2;
}

vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix) {
    vector<int> v;
    for (int i = 0; i < adjMatrix.size(); i++) {
        bool isolated = true;
        for (int j = 0; j < adjMatrix[i].size(); j++) {
            if(adjMatrix[i][j] == 1) {
                isolated = false;
                break;
            }
        }
        if(isolated) {
            for(int k = 0; k < adjMatrix.size(); k++) {
                if(adjMatrix[k][i] == 1) {
                    isolated = false;
                    break;
                }
            }
        }
        if(isolated) v.push_back(i);
    }
    return v;
}

bool isCompleteGraph(const vector<vector<int>>& adjMatrix) {
    for (int i = 0; i < adjMatrix.size(); i++) {
        for (int j = 0; j < adjMatrix[i].size(); j++) {
            if(adjMatrix[i][j] == 0 && i!=j) return false;
        }
    }
    return true;
}

bool isBipartite(const std::vector<std::vector<int>>& adjMatrix) {
    vector<int> color(adjMatrix.size(), -1);
    queue<int> q;
    for (int i = 0; i < adjMatrix.size(); i++) {
        if(color[i] == -1) {
            q.push(i);
            color[i]=0;
            while(!q.empty()) {
                int u = q.front();
                q.pop();
                for(int j = 0; j < adjMatrix.size(); j++) {
                    if(adjMatrix[u][j]) {
                        if(color[j]==-1) {
                            color[j]=1-color[u];
                            q.push(j);
                        }
                        else if(color[j]==color[u]) return false;
                    }
                }
            }
        }
    }
    return true;
}

bool isCompleteBipartite(const vector<vector<int>>& adjMatrix) {
    vector<int> color(adjMatrix.size(), -1);
    queue<int> q;
    for (int i = 0; i < adjMatrix.size(); i++) {
        if(color[i] == -1) {
            q.push(i);
            color[i]=0;
            while(!q.empty()) {
                int u = q.front();
                q.pop();
                for(int j = 0; j < adjMatrix.size(); j++) {
                    if(adjMatrix[u][j]) {
                        if(color[j]==-1) {
                            color[j]=1-color[u];
                            q.push(j);
                        }
                        else if(color[j]==color[u]) return false;
                    }
                }
            }
        }
    }
    vector<int> l;
    vector<int> r;
    for (int i = 0; i < adjMatrix.size(); i++) {
        if(color[i]==0) l.push_back(i);
        else r.push_back(i);
    }
    for (int i = 0; i < l.size(); i++) {
        for(int j = 0; j < r.size(); j++) {
            if(adjMatrix[l[i]][r[j]] == 0) return false;
        }
    }
    return true;
}

vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix) {
    vector<vector<int>> M(adjMatrix.size(), vector<int>(adjMatrix.size(),0));
    for (int i = 0; i < adjMatrix.size(); i++) {
        for (int j = 0; j < adjMatrix[i].size(); j++) {
            if(adjMatrix[i][j] == 1 || adjMatrix[j][i] == 1)  M[i][j] = 1;
        }
    }
    return M;
}

vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix) {
    vector<vector<int>> M(adjMatrix.size(), vector<int>(adjMatrix.size(),0));
    for (int i = 0; i < adjMatrix.size(); i++) {
        for (int j = 0; j < adjMatrix[i].size(); j++) {
            if(i != j && adjMatrix[i][j] == 0) {
                M[i][j] = 1;
                M[j][i] = 1;
            }
        }
    }
    return M;
}

vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix) {
    vector<vector<int>> M = adjMatrix;
    for (int i = 0; i < M.size(); i++) {
        int deg = 0;
        for (int j = 0; j < M[i].size(); j++) deg += M[i][j];
        if (deg % 2 != 0) return {};
    }
    stack<int> s;
    vector<int> E;
    int start = 0;
    while (start < M.size()) {
        int deg = 0;
        for (int i = 0; i < M[start].size(); ++i) {
            deg += M[start][i];
        }
        if (deg > 0) break;
        start++;
    }
    if (start == M.size()) return {};
    s.push(start);
    while(!s.empty()) {
        int v=s.top();
        for(int i = 0; i < M[v].size(); i++) {
            if(M[v][i] == 1) {
                s.push(i);
                M[v][i] = 0;
                M[i][v] = 0;
                break;
            }
        }
        if(v == s.top()) {
            s.pop();
            E.push_back(v);
        }
    }
    reverse(E.begin(),E.end());
    return E;
}

void dfsvisit(int start, vector<vector<int>>& adjMatrix, vector<bool>& visited, vector<vector<int>>& T) {
    visited[start] = true;
    for (int i = 0; i < adjMatrix.size(); i++) {
        if(adjMatrix[start][i] == 1 && !visited[i]) {
            T[start][i] = 1;
            T[i][start] = 1;
            dfsvisit(i, adjMatrix, visited, T);
        }
    }
}

vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
    int n = adjMatrix.size();
    vector<vector<int>> M=adjMatrix;
    vector<vector<int>> T(n, vector<int>(n,0));
    vector<bool> visited(n, false);
    dfsvisit(start,M,visited,T);
    return T;
}

vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
    int n = adjMatrix.size();
    vector<vector<int>> M=adjMatrix;
    vector<vector<int>> T(n, vector<int>(n,0));
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(start);
    visited[start]=true;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(int i = 0; i < n; i++) {
            if(M[u][i] == 1 && !visited[i]) {
                q.push(i);
                visited[i] = true;
                T[u][i] = 1;
                T[i][u] = 1;
            }
        }
    }
    return T;
}

bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix) {
    vector<vector<int>> M=adjMatrix;
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(u);
    visited[u] = true;
    while(!q.empty()) {
        int cur = q.front();
        q.pop();
        if(cur == v) return true;
        for(int i = 0; i < n; i++) {
            if(M[cur][i] == 1 && !visited[i]) {
                q.push(i);
                visited[i] = true;
            }
        }
    }
    return false;
}

vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix) {
    if(start == end) return {start};
    int n = adjMatrix.size();
    vector<vector<int>> M=adjMatrix;
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);
    dist[start]=0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});
    while(!pq.empty()) {
        pair<int, int> top = pq.top();
        pq.pop();
        int cur = top.first;
        int u = top.second;
        if(cur > dist[u]) continue;
        for(int i = 0; i < n; i++) {
            int weight = M[u][i];
            if(weight != 0) {
                int newdist= dist [u] + weight;
                if(newdist < dist[i]) {
                    dist[i] = newdist;
                    parent[i] = u;
                    pq.push({newdist, i});
                }
            }
        }
    }
    vector<int> result;
    if(dist[end] == INT_MAX) return result;
    for(int i=end; i!=-1; i=parent[i]) {
        result.push_back(i);
    }
    reverse(result.begin(),result.end());
    return result;
}

vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<vector<int>> M=adjMatrix;
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);
    dist[start]=0;
    for (int k = 0; k < n - 1; k++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (adjMatrix[u][v] != 0 && dist[u] != INT_MAX) {
                    int weight = adjMatrix[u][v];
                    if (dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                        parent[v] = u;
                    }
                }
            }
        }
    }
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (adjMatrix[u][v] != 0 && dist[u] != INT_MAX) {
                if (dist[u] + adjMatrix[u][v] < dist[v]) {
                    return {};
                }
            }
        }
    }
    vector<int> path;
    if (dist[end] == INT_MAX) return path;

    for (int v = end; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}

