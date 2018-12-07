#include <bits/stdc++.h>

using namespace std;

const int MAX_GRAPH = 26;
const int PROCESS_CONSTANT = 60;
const int WORKERS = 5;

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

int construct_time(vector<vector<int> > graph,
                   vector<int> in_degree,
                   const int workers) {
  int time_spent = 0;

  queue<tuple<int, int> > q;
  deque<int> waitlist;

  for (int i = 0; i < (int) graph.size(); i++) {
    if (in_degree[i] == 0) {
      if (q.size() < workers) {
        q.push(make_tuple(i, i + PROCESS_CONSTANT + 1));
      } else {
        waitlist.push_back(i);
      }
    }
  }

  while (!q.empty()) {
    vector<tuple<int, int> > q_buffer;

    while (!q.empty()) {
      tuple<int, int> tp = q.front();
      int label, time_left;
      q.pop();

      tie(label, time_left) = tp;
      time_left -= 1;

      if (time_left <= 0) {
        for (int i = 0; i < (int) graph[label].size(); i++) {
          int child = graph[label][i];

          in_degree[child] -= 1;

          if (in_degree[child] == 0) {
            waitlist.push_back(child);
          }
        }
      } else {
        q_buffer.push_back(make_tuple(label, time_left));
      }
    }

    // re-insert elements that hasn't finished yet.
    for (int i = 0; i < q_buffer.size(); i++) {
      q.push(q_buffer[i]);
    }

    // insert elements from the waitlist
    while (q.size() < workers && !waitlist.empty()) {
      int label = waitlist.front();
      q.push(make_pair(label, label + PROCESS_CONSTANT + 1));

      waitlist.pop_front();
    }

    time_spent += 1;
  }

  return time_spent;
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

  for (int i = 0; i < MAX_GRAPH; i++) {
    sort(graph[i].begin(), graph[i].end());
  }

  cout << construct_time(graph, in_degree, WORKERS) << endl;

  return 0;
}
