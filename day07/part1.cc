#include <bits/stdc++.h>

using namespace std;

const int MAX_GRAPH = 26;

int convert_letter(char arg) {
  return arg - 'A';
}

char convert_integer(int arg) {
  return (char) ('A' + arg);
}

tuple<int, int> process_line(string arg) {
  int a, b;

  sscanf(arg.c_str(),
         "Step %c must be finished before step %c can begin.",
         &a,
         &b);

  return make_tuple(convert_letter(a), convert_letter(b));
}

vector<int> topological_sort(
                             vector<vector<int> > graph,
                             vector<int> in_degree) {
  vector<int> order;
  priority_queue<int, vector<int>, greater<int> > pq;

  for (int i = 0; i < (int) graph.size(); i++) {
    if (in_degree[i] == 0) {
      pq.push(i);
    }
  }

  while (!pq.empty()) {
    int curr = pq.top();
    pq.pop();

    order.push_back(curr);

    for (int i = 0; i < graph[curr].size(); i++) {
      int next = graph[curr][i];

      in_degree[next] -= 1;

      if (in_degree[next] == 0) {
        pq.push(next);
      }
    }
  }

  return order;
}

int main(int argc, char *argv[]) {
  string line;
  vector<vector<int> > graph(MAX_GRAPH, vector<int>());
  vector<int> in_degree(MAX_GRAPH);

  while (getline(cin, line)) {
    int a, b;
    tuple<int, int> edge = process_line(line);
    tie(a, b) = edge;

    in_degree[b] += 1;
    graph[a].push_back(b);
  }

  vector<int> order = topological_sort(graph, in_degree);

  for (int i = 0; i < (int) order.size(); i++) {
    cout << convert_integer(order[i]);
  }

  cout << endl;

  return 0;
}
