#include <bits/stdc++.h>

using namespace std;

const int MAXN = 60;
const int MAX_MAP = 600;

int X[MAXN];
int Y[MAXN];

int dst[MAX_MAP][MAX_MAP];
int color[MAX_MAP][MAX_MAP];
bool visited[MAX_MAP][MAX_MAP];

const int dx[4] = {0, 0, -1, +1};
const int dy[4] = {-1, +1, 0, 0};

bool inside(int arg_x, int arg_y) {
  return arg_x >= 0
    && arg_y >= 0
    && arg_x < MAX_MAP
    && arg_y < MAX_MAP;
}

bool is_infinite(int curr_x, int curr_y, int curr_color) {
  if (curr_x == 0
      || curr_y == 0
      || curr_x == MAX_MAP - 1
      || curr_y == MAX_MAP - 1) {
    return true;
  }

  visited[curr_x][curr_y] = true;

  bool answer = false;

  for (int i = 0; i < 4; i++) {
    int next_x = curr_x + dx[i];
    int next_y = curr_y + dy[i];

    if (!inside(next_x, next_y)) {
      continue;
    }

    if (!visited[next_x][next_y]
        && color[next_x][next_y] == curr_color) {
      answer |= is_infinite(next_x, next_y, curr_color);
    }
  }

  return answer;
}

int get_area(int curr_x, int curr_y, int curr_color) {
  if (!inside(curr_x, curr_y)) {
    return 0;
  }

  visited[curr_x][curr_y] = true;

  int answer = 1;

  for (int i = 0; i < 4; i++) {
    int next_x = curr_x + dx[i];
    int next_y = curr_y + dy[i];

    if (!inside(next_x, next_y)) {
      continue;
    }

    if (!visited[next_x][next_y]
        && color[next_x][next_y] == curr_color) {
      answer += get_area(next_x, next_y, curr_color);
    }
  }

  return answer;
}

void bfs(int init_x, int init_y, int kind) {
  queue<tuple<int, int> > q;
  q.push(make_tuple(init_x, init_y));

  color[init_x][init_y] = kind;
  dst[init_x][init_y] = 0;

  while (!q.empty()) {
    int curr_x, curr_y;
    tie(curr_x, curr_y) = q.front();
    q.pop();

    for (int i = 0; i < 4; i++) {
      int next_x = curr_x + dx[i];
      int next_y = curr_y + dy[i];
      int curr_dist = abs(init_x - next_x) + abs(init_y - next_y);

      if (!inside(next_x, next_y)) {
        continue;
      }

      if (dst[next_x][next_y] > curr_dist) {
        color[next_x][next_y] = kind;
        dst[next_x][next_y] = curr_dist;

        q.push(make_tuple(next_x, next_y));
      } else if (dst[next_x][next_y] == curr_dist
                 && color[next_x][next_y] != kind) {
        color[next_x][next_y] = 0;
      }
    }
  }
}

int main() {
  int N = 1;

  memset(dst, 63, sizeof(dst));
  memset(color, 0, sizeof(color));

  while (scanf("%d, %d", &Y[N], &X[N]) == 2) {
    bfs(X[N], Y[N], N);
    N += 1;
  }

  int best_area = 0;

  for (int i = 1; i < N; i++) {
    memset(visited, false, sizeof(visited));
    if (is_infinite(X[i], Y[i], i)) {
      continue;
    }
    memset(visited, false, sizeof(visited));
    int curr_area = get_area(X[i], Y[i], i);
    best_area = max(best_area, curr_area);
  }

  cout << best_area << "\n";

  return 0;
}
