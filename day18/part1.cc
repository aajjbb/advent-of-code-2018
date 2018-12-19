#include <bits/stdc++.h>

using namespace std;

const int GENS = 10;

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

    for (int t = 0; t < GENS; t++) {
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