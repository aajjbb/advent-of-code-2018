#include <bits/stdc++.h>

using namespace std;

enum EventKind { WAKES, FALLS, GUARD };

const int DATE_INFO_SIZE = 5;
const int SLEEP_INTERVAL = 60;

struct Event {
  int id;
  int date_vec[DATE_INFO_SIZE];
  EventKind kind;

  Event(int _year, int _month, int _day, int _hour, int _minute, int _id, EventKind _kind) {
    date_vec[0] = _year;
    date_vec[1] = _month;
    date_vec[2] = _day;
    date_vec[3] = _hour;
    date_vec[4] = _minute;
    kind = _kind;
    id = _id;
  }

  bool operator<(Event& other) const {
    for (int i = 0; i < DATE_INFO_SIZE; i++) {
      if (date_vec[i] != other.date_vec[i]) {
        return date_vec[i] < other.date_vec[i];
      }
    }
    return true;
  }
};

EventKind convert_kind(string arg) {
  if (arg == "falls") {
    return EventKind::FALLS;
  } else if (arg == "wakes") {
    return EventKind::WAKES;
  } else {
    return EventKind::GUARD;
  }
}

int main() {
  string line;

  vector<Event> events;
  map<int, vector<int> > sum_asleep;

  while (getline(cin, line)) {
    int year, month, day, hour, minute, id;
    char kind_str[6];
    sscanf(line.c_str(), "[%d-%d-%d %d:%d] %5s #%d", &year, &month, &day, &hour, &minute, kind_str, &id);

    EventKind kind = convert_kind(string(kind_str));

    sum_asleep[id] = vector<int>(SLEEP_INTERVAL);

    events.push_back(Event(year, month, day, hour, minute, id, kind));
  }

  sort(events.begin(), events.end());

  int active_guard = 0;
  int last_awake = 0;

  for (int i = 0; i < (int) events.size(); i++) {
    if (events[i].kind == EventKind::GUARD) {
      active_guard = events[i].id;
      last_awake = events[i].date_vec[4];
    } else if (events[i].kind == EventKind::WAKES) {
      for (int j = last_awake + 1; j < events[i].date_vec[4]; j++) {
        sum_asleep[active_guard][j] += 1;
      }
      last_awake = events[i].date_vec[4];
    } else {
      last_awake = events[i].date_vec[4] - 1;
    }
  }

  int global_guard_id = 0;
  int global_most_slept_minute = 0;
  int global_most_slept_minute_count = 0;

  for (auto const iter : sum_asleep) {
    int guard_id = iter.first;
    int sleep_sum = 0;
    int most_slept_minute = 0;
    int most_slept_minute_count = 0;

    for (int i = 0; i < SLEEP_INTERVAL; i++) {
      sleep_sum += iter.second[i];

      if (most_slept_minute_count < iter.second[i]) {
        most_slept_minute_count = iter.second[i];
        most_slept_minute = i;
      }
    }

    if (global_most_slept_minute_count < most_slept_minute_count) {
      global_guard_id = guard_id;
      global_most_slept_minute = most_slept_minute;
      global_most_slept_minute_count = most_slept_minute_count;
    }
  }

  cout << global_guard_id * global_most_slept_minute << "\n";

  return 0;
}
