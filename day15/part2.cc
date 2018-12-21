#include <bits/stdc++.h>

using namespace std;

const int INF = INT_MAX / 5;

const char ELF = 'E';
const char EMPTY = '.';
const char GOBLIN = 'G';
const char WALL = '#';

const int ATTACK_POWER = 3;
const int DEFAULT_HIT_POINTS = 200;

const int DIRECTIONS_CNT = 4;
const int dx[DIRECTIONS_CNT] = {-1, 0, +1, 0};
const int dy[DIRECTIONS_CNT] = {0, -1, 0, +1};

struct Unit {
    bool alive;
    int x, y;
    int attack_points;
    int hit_points;
    char type;

    Unit(int _x, int _y, char _type, int _attack_points, int _hit_points) {
        alive = true;
        x = _x;
        y = _y;
        attack_points = _attack_points;
        hit_points = _hit_points;
        type = _type;
    }

    bool operator<(const Unit& other) const {
        if (x != other.x) {
            return x < other.x;
        } else {
            return y < other.y;
        }
    }
};

bool is_unit(char type) {
    return type == ELF || type == GOBLIN;
}

bool inside(int x, int y, const vector<string>& board) {
    return min(x, y) >= 0
     && x < board.size()
     && y < board[0].size();
}

bool in_range(int x, int y, vector<string>& board) {
    if (!inside(x, y, board) || !is_unit(board[x][y])) {
        return false;
    }

    for (int i = 0; i < DIRECTIONS_CNT; i++) {
        int xx = x + dx[i];
        int yy = y + dy[i];

        if (inside(xx, yy, board)
            && is_unit(board[xx][yy])
            && board[x][y] != board[xx][yy]) {

            return true;
        }
    }

    return false;
}

int get_enemy_id(int x,
                 int y,
                 const vector<string> board,
                 vector<Unit> units) {

    // hit_points, x, y, id
    tuple<int, int, int, int> best_tuple =
      make_tuple(INF, INF, INF, INF);

    for (int i = 0; i < DIRECTIONS_CNT; i++) {
        int xx = x + dx[i];
        int yy = y + dy[i];

        if (inside(xx, yy, board)
            && board[x][y] != board[xx][yy]) {

            for (int k = 0; k < units.size(); k++) {
                if (!units[k].alive) {
                    continue;
                }

                if (units[k].hit_points > 0 && units[k].x == xx && units[k].y == yy) {
                    tuple<int, int, int, int> tmp_tuple = make_tuple(
                        units[k].hit_points,
                        units[k].x,
                        units[k].y,
                        k
                    );

                    if (best_tuple > tmp_tuple) {
                        best_tuple = tmp_tuple;
                    }
                }
            }
        }
    }

    return get<3>(best_tuple);
}

vector<Unit> find_units(const vector<string>& board, const int elf_attack_points) {
    const int n = board.size();
    const int m = board[0].size();

    vector<Unit> units;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] == ELF) {
                units.push_back(Unit(i, j, ELF, elf_attack_points, DEFAULT_HIT_POINTS));
            } else if (board[i][j] == GOBLIN) {
                units.push_back(Unit(i, j, GOBLIN, ATTACK_POWER, DEFAULT_HIT_POINTS));
            }
        }
    }

    return units;
}

vector<vector<int> > get_dists(int x, int y, const vector<string>& board) {
    const int n = board.size();
    const int m = board[0].size();

    vector<vector<int> > dists(n, vector<int>(m, INF));
    queue<tuple<int, int> > q;

    dists[x][y] = 0;
    q.push(make_tuple(x, y));

    while (!q.empty()) {
        int cx, cy;
        tie(cx, cy) = q.front();
        q.pop();

        for (int i = 0; i < DIRECTIONS_CNT; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if (!inside(nx, ny, board) || board[nx][ny] != EMPTY) {
                continue;
            }

            if (dists[nx][ny] > dists[cx][cy] + 1) {
                dists[nx][ny] = dists[cx][cy] + 1;
                q.push(make_tuple(nx, ny));
            }
        }
    }

    return dists;
}

void move_unit(int unit_id, vector<Unit>& units, vector<string>& board) {
    vector<int> enemy_vec;

    // Get enemies ids
    for (int j = 0; j < units.size(); j++) {
        if (!units[j].alive || units[j].type == units[unit_id].type) {
            continue;
        }

        enemy_vec.push_back(j);
    }

    // dist, t_x, t_y, r_x, r_x
    tuple<int, int, int, int, int> best_tuple = make_tuple(INF, INF, INF, INF, INF);

    for (int k = 0; k < DIRECTIONS_CNT; k++) {
        int xx = units[unit_id].x + dx[k];
        int yy = units[unit_id].y + dy[k];

        if (!inside(xx, yy, board) || board[xx][yy] != EMPTY) {
            continue;
        }

        vector<vector<int> > dists = get_dists(xx, yy, board);

        for (int j = 0; j < enemy_vec.size(); j++) {
            int enemy_id = enemy_vec[j];

            for (int d = 0; d < DIRECTIONS_CNT; d++) {
                int en_x = units[enemy_id].x + dx[d];
                int en_y = units[enemy_id].y + dy[d];

                if (!inside(en_x, en_y, board) || board[en_x][en_y] != EMPTY) {
                    continue;
                }

                int local_dist = dists[en_x][en_y];

                tuple<int, int, int, int, int> local_tuple = make_tuple(
                    local_dist,
                    en_x,
                    en_y,
                    xx,
                    yy);

                if (best_tuple > local_tuple) {
                    best_tuple = local_tuple;
                }
            }
        }
    }

    int best_dist = get<0>(best_tuple);
    int new_x = get<3>(best_tuple);
    int new_y = get<4>(best_tuple);

    if (inside(new_x, new_y, board) && best_dist < INF) {
        board[new_x][new_y] = board[units[unit_id].x][units[unit_id].y];
        board[units[unit_id].x][units[unit_id].y] = EMPTY;

        units[unit_id].x = new_x;
        units[unit_id].y = new_y;
    }
}

void attack(int unit_id,
            vector<Unit>& units,
            vector<string>& board,
            map<char, int>& cnt_units) {

    if (!units[unit_id].alive) {
        assert(false);
    }

    int enemy_id = get_enemy_id(units[unit_id].x,
                                units[unit_id].y,
                                board,
                                units);

    units[enemy_id].hit_points -= units[unit_id].attack_points;

    if (units[enemy_id].hit_points <= 0) {
        int type = units[enemy_id].type;

        board[units[enemy_id].x][units[enemy_id].y] = EMPTY;
        cnt_units[type] -= 1;
        units[enemy_id].alive = false;
    }
}

int main() {
    string line;
    vector<string> base_board;

    while (getline(cin, line)) {
        base_board.push_back(line);
    }

    int low = 4, high = 100, mid;
    int result = -1;

    while (low <= high) {
        mid = low + (high - low) / 2;

        vector<string> board = base_board;
        vector<Unit> units = find_units(board, mid);
        map<char, int> cnt_units;

        int rounds = 0;

        for (const auto& unit : units) {
            cnt_units[unit.type] += 1;
        }

        int elf_units = cnt_units[ELF];

        while (min(cnt_units[ELF], cnt_units[GOBLIN]) > 0) {
            sort(units.begin(), units.end());

            for (int i = 0; i < (int) units.size(); i++) {
                if (!units[i].alive) {
                    continue;
                }
                if (!in_range(units[i].x, units[i].y, board)) {
                    move_unit(i, units, board);
                }

                if (in_range(units[i].x, units[i].y, board)) {
                    attack(i, units, board, cnt_units);
                }
            }

            rounds += 1;
        }
        if (cnt_units[ELF] == elf_units) {
            int hit_points_left = 0;

            for (int i = 0; i < (int) units.size(); i++) {
                if (!units[i].alive) {
                    continue;
                }
                hit_points_left += units[i].hit_points;
            }

            result = hit_points_left * (rounds - 1);

            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    cout << result << "\n";

    return 0;
}