#include <bits/stdc++.h>

using namespace std;

const int GENS = 1000000000;

const int BOARD_N = 50;
const int BOARD_M = 50;

const char OPEN = '.';
const char TREE = '|';
const char LUMBERYARD = '#';

int dx[8] = {-1, +1, 0, 0, -1, +1, -1, +1};
int dy[8] = {0, 0, -1, +1, -1, +1, +1, -1};

bool inside(int x, int y) {
    return min(x, y) >= 0 && x < BOARD_N && y < BOARD_M;
}

char updateCell(vector<string>& board, int x, int y) {
    map<char, int> neighCount;

    for (int i = 0; i < 8; i++) {
        int xx = x + dx[i];
        int yy = y + dy[i];

        if (inside(xx, yy)) {
            neighCount[board[xx][yy]] += 1;
        }
    }

    if (board[x][y] == OPEN && neighCount[TREE] >= 3) {
        return TREE;
    } else if (board[x][y] == TREE && neighCount[LUMBERYARD] >= 3) {
        return LUMBERYARD;
    } else if (board[x][y] == LUMBERYARD) {
        if (neighCount[LUMBERYARD] > 0 && neighCount[TREE] > 0) {
            return LUMBERYARD;
        } else {
            return OPEN;
        }
    } else {
        return board[x][y];
    }
}

vector<string> updateBoard(vector<string> board) {
    vector<string> new_board = board;

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            new_board[i][j] = updateCell(board, i, j);
        }
    }

    return new_board;
}

int main() {
    string line;
    vector<string> board;

    while (getline(cin, line)) {
        board.push_back(line);
    }

    map<vector<string>, int> memo;
    vector<string> test_board = board;    
    int ini_id = -1;
    int end_id = -1;

    // Find cycle information
    for (int t = 0; t < GENS; t++) {
        test_board = updateBoard(test_board);
        if (memo.find(test_board) != memo.end()) {
            ini_id = memo[test_board];
            end_id = t;
            break;
        }
        memo[test_board] = t;
    }
    
    int cycle_len = end_id - ini_id;

    for (int t = 0; t < ini_id + (GENS - ini_id) % cycle_len; t++) {
        board = updateBoard(board);
    }

    map<char, int> cntElements;

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            cntElements[board[i][j]] += 1;
        }
    }
    
    cout << cntElements[TREE] * cntElements[LUMBERYARD] << endl;

    return 0;
}