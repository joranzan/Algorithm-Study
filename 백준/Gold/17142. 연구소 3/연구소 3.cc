// 17142. 연구소3
#include <bits/stdc++.h>
#define INF 987654321

using namespace std;

typedef pair<int, pair<int, int>> P;

int N, M, answer = INF;
int table[51][51], safe_place, virous_size;
bool visited[51][51];
const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
vector<pair<int, int>> virous;

void bfs(vector<pair<int, int>> &activ);
void dfs(int cnt, int next, vector<pair<int, int>> &activ);

int main(void) {
    cin.tie(nullptr);
    cin.sync_with_stdio(false);

    cin >> N >> M;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> table[i][j];
            if(table[i][j] == 2) {
                virous.push_back({i, j});
                virous_size++;
            }
            if(table[i][j] == 0)
                safe_place++; 
        }
    }

    vector<pair<int, int>> activated;
    dfs(0, 0, activated);

    cout << (answer >= INF ? -1 : answer) << "\n";

    return 0;
}

void bfs(vector<pair<int, int>> &activ) {
    queue<P> q;
    int tmp_safe_place = safe_place, min_time = 0;
    
    for(int i = 0; i < N; i++)
        memset(visited[i], 0, N);
    for(int i = 0; i < M; i++) {
        int active_row = activ[i].first, active_col = activ[i].second;
        q.push({0, {active_row, active_col}});
        visited[active_row][active_col] = true;
    }

    while(!q.empty()) {
        int cur_time = q.front().first, cur_row = q.front().second.first, cur_col = q.front().second.second;
        q.pop();

        min_time = cur_time;

        if(table[cur_row][cur_col] == 0)
            tmp_safe_place--;
        
        if(min_time >= answer || tmp_safe_place <= 0)
            break;

        for(int i = 0; i < 4; i++) {
            int new_row = cur_row + dx[i], new_col = cur_col + dy[i];

            if(new_row < 0 || new_row >= N || new_col < 0 || new_col >= N)
                continue;
            if(visited[new_row][new_col] || table[new_row][new_col] == 1)
                continue;
            
            visited[new_row][new_col] = true;
            q.push({cur_time + 1, {new_row, new_col}});
        }
    }

    if(tmp_safe_place <= 0)
        answer = min(answer, min_time);
}

void dfs(int cnt, int next, vector<pair<int, int>> &activ) {
    if(cnt == M) {
        bfs(activ);
        return ;
    }

    for(int i = next; i < virous_size; i++) {
        activ.push_back(virous[i]);
        dfs(cnt + 1, i + 1, activ);
        activ.pop_back();
    }
}