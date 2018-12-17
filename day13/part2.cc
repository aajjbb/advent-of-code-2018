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
    int id;
    int x, y;
    int dir;
    int intersection_cnt = 0;

    cart(int _id, int _x, int _y, int _dir) {
        id = _id;
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
                ans.push_back(cart(ans.size() + 1, i, j, cart_pos));
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

    vector<vector<set<int> > > cnt_presence(MAXN, vector<set<int> >(MAXN));
    vector<cart> carts = find_carts(table);
    int tick = 0;

    while (carts.size() > 1) {
        sort(carts.begin(), carts.end());
        set<int> inactive;

        for (int i = 0; i < carts.size(); i++) {
            if (inactive.count(carts[i].id)) {
                continue;
            }
            cnt_presence[carts[i].x][carts[i].y].erase(carts[i].id);
            update_cart(carts[i], table);
            cnt_presence[carts[i].x][carts[i].y].insert(carts[i].id);

            if (cnt_presence[carts[i].x][carts[i].y].size() > 1) {
                inactive.insert(cnt_presence[carts[i].x][carts[i].y].begin(), cnt_presence[carts[i].x][carts[i].y].end());
                cnt_presence[carts[i].x][carts[i].y].clear();
            }
        }

        vector<cart> active_carts;

        for (int i = 0; i < carts.size(); i++) {
            if (!inactive.count(carts[i].id)) {
                active_carts.push_back(carts[i]);
            }
        }

        carts = active_carts;
        tick++;
    }

    cout << carts.size() << " " << carts.begin()->y << " " << carts.begin()->x << "\n";

    return 0;
}