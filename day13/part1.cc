#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500;

enum Directions {
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3,
};

const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

const string cart_symbols = "^>v<";
const string turn_signs = "\\ /";

struct cart {
    int x, y;
    int dir;
    int intersection_cnt = 0;

    cart(int _x, int _y, int _dir) {
        x = _x;
        y = _y;
        dir = _dir;
        intersection_cnt = 0;
    }

    void update_insersection_dir() {
        if (intersection_cnt == 0) {
            dir = (dir - 1 + 4) % 4;
        } else if (intersection_cnt == 1) {
            // In the second time, it stays in the same direction
        } else if (intersection_cnt == 2) {
            dir = (dir + 1) % 4;
        }

        intersection_cnt += 1;
        intersection_cnt %= 3;
    }

    bool operator<(const cart& other) {
        if (y != other.y) {
            return y < other.y;
        } else {
            return x < other.x;
        }
    }
};

vector<cart> find_carts(vector<string> table) {
    vector<cart> ans;

    for (int i = 0; i < table.size(); i++) {
        for (int j = 0; j < table[i].size(); j++) {
            int cart_pos = cart_symbols.find(table[i][j]);

            if (cart_pos != string::npos) {
                ans.push_back(cart(i, j, cart_pos));
            }
        }
    }

    return ans;
}

void update_cart(cart& crt, vector<string> table) {
    if (table[crt.x][crt.y] == '+') {
        crt.update_insersection_dir();
        crt.x += dx[crt.dir];
        crt.y += dy[crt.dir];
    } else {
        if (turn_signs.find(table[crt.x][crt.y]) != string::npos) {
            //cout << table[crt.x][crt.y] << " " << crt.dir << endl;
            if (crt.dir == Directions::UP && table[crt.x][crt.y] == '/') {
                crt.dir = Directions::RIGHT;
            } else if (crt.dir == Directions::UP && table[crt.x][crt.y] == '\\') {
                crt.dir = Directions::LEFT;
            } else if (crt.dir == Directions::RIGHT && table[crt.x][crt.y] == '/') {
                crt.dir = Directions::UP;
            } else if (crt.dir == Directions::RIGHT && table[crt.x][crt.y] == '\\') {
                crt.dir = Directions::DOWN;
            } else if (crt.dir == Directions::DOWN && table[crt.x][crt.y] == '\\') {
                crt.dir = Directions::RIGHT;
            } else if (crt.dir == Directions::DOWN && table[crt.x][crt.y] == '/') {
                crt.dir = Directions::LEFT;
            } else if (crt.dir == Directions::LEFT && table[crt.x][crt.y] == '\\') {
                crt.dir = Directions::UP;
            } else if (crt.dir == Directions::LEFT && table[crt.x][crt.y] == '/') {
                crt.dir = Directions::DOWN;
            }
        }
        crt.x += dx[crt.dir];
        crt.y += dy[crt.dir];
    }
}

int main() {
    string line;

    vector<string> table;

    while (getline(cin, line)) {
        table.push_back(line);
    }

    vector<vector<int> > cnt_presence(MAXN, vector<int>(MAXN, 0));
    vector<cart> carts = find_carts(table);
    int tick = 0;
    bool has_collision = false;

    while (!has_collision) {
        sort(carts.begin(), carts.end());

        for (int i = 0; i < carts.size(); i++) {
            cnt_presence[carts[i].x][carts[i].y] -= 1;
            update_cart(carts[i], table);
            cnt_presence[carts[i].x][carts[i].y] += 1;

            if (cnt_presence[carts[i].x][carts[i].y] > 1) {
                has_collision = true;

                cout << carts[i].y << "," << carts[i].x << "\n";

                break;
            }
        }
        tick++;
    }

    return 0;
}