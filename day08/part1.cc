#include <bits/stdc++.h>

using namespace std;

const int MAX_TREE_SIZE = 100;

vector<int> tree[MAX_TREE_SIZE];
vector<int> tree_metadata[MAX_TREE_SIZE];

void build_tree(int node_id) {
    int child, meta;

    cin >> child >> meta;

    for (int i = 0; i < child; i++) {
        build_tree(node_id + i + 1);
    }

    for (int i = 0; i < meta; i++) {
        int mt_value;
        cin >> mt_value;

        tree_metadata[node_id].push_back(mt_value);
    }
}

int main() {
    build_tree(1);

    int metadata_sum = 0;

    for (int i = 0; i < MAX_TREE_SIZE; i++) {
        metadata_sum += accumulate(tree_metadata[i].begin(), tree_metadata[i].end(), 0);
    }

    cout << metadata_sum << "\n";

    return 0;
}