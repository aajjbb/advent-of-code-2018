#include <bits/stdc++.h>

using namespace std;

// Hard coding the input count.
const int SAMPLE_CNT = 773;
const int TEST_CNT = 853;

const int REGISTER_SIZE = 4;
const int OP_COUNT = 16;

// There are only 4 registers
// so the answer vector must have size = 4
vector<int> read_register_state() {
    vector<int> reg(4);
    string line;

    getline(cin, line);

    sscanf(line.c_str(),
        "%*7s [%d, %d, %d, %d]",
        &reg[0],
        &reg[1],
        &reg[2],
        &reg[3]);

    return reg;
}

tuple<int, int, int, int> read_operation() {
    int a, b, c, d;

    cin >> a >> b >> c >> d;

    return make_tuple(a, b, c, d);
}

class Operation {
    public:
        virtual vector<int> operate(tuple<int, int, int, int> op, vector<int> reg_state) = 0;
};

class addr : public Operation {
    public:
        vector<int> operate(tuple<int, int, int, int> op, vector<int> reg_state) {
            reg_state[get<3>(op)] = reg_state[get<1>(op)] + reg_state[get<2>(op)];
            return reg_state;
        }
};

class addi : public Operation {
    public:
        vector<int> operate(tuple<int, int, int, int> op, vector<int> reg_state) {
            reg_state[get<3>(op)] = reg_state[get<1>(op)] + get<2>(op);
            return reg_state;
        }
};

class mulr : public Operation {
    public:
        vector<int> operate(tuple<int, int, int, int> op, vector<int> reg_state) {
            reg_state[get<3>(op)] = reg_state[get<1>(op)] * reg_state[get<2>(op)];
            return reg_state;
        }
};

class muli : public Operation {
    public:
        vector<int> operate(tuple<int, int, int, int> op, vector<int> reg_state) {
            reg_state[get<3>(op)] = reg_state[get<1>(op)] * get<2>(op);
            return reg_state;
        }
};

class banr : public Operation {
    public:
        vector<int> operate(tuple<int, int, int, int> op, vector<int> reg_state) {
            reg_state[get<3>(op)] = reg_state[get<1>(op)] & reg_state[get<2>(op)];
            return reg_state;
        }
};

class bani : public Operation {
    public:
        vector<int> operate(tuple<int, int, int, int> op, vector<int> reg_state) {
            reg_state[get<3>(op)] = reg_state[get<1>(op)] & get<2>(op);
            return reg_state;
        }
};

class borr : public Operation {
    public:
        vector<int> operate(tuple<int, int, int, int> op, vector<int> reg_state) {
            reg_state[get<3>(op)] = reg_state[get<1>(op)] | reg_state[get<2>(op)];
            return reg_state;
        }
};

class bori : public Operation {
    public:
        vector<int> operate(tuple<int, int, int, int> op, vector<int> reg_state) {
            reg_state[get<3>(op)] = reg_state[get<1>(op)] | get<2>(op);
            return reg_state;
        }
};

class setr : public Operation {
    public:
        vector<int> operate(tuple<int, int, int, int> op, vector<int> reg_state) {
            reg_state[get<3>(op)] = reg_state[get<1>(op)];
            return reg_state;
        }
};

class seti : public Operation {
    public:
        vector<int> operate(tuple<int, int, int, int> op, vector<int> reg_state) {
            reg_state[get<3>(op)] = get<1>(op);
            return reg_state;
        }
};

class gtir : public Operation {
    public:
        vector<int> operate(tuple<int, int, int, int> op, vector<int> reg_state) {
            reg_state[get<3>(op)] = get<1>(op) > reg_state[get<2>(op)] ? 1 : 0;
            return reg_state;
        }
};

class gtri : public Operation {
    public:
        vector<int> operate(tuple<int, int, int, int> op, vector<int> reg_state) {
            reg_state[get<3>(op)] = reg_state[get<1>(op)] > get<2>(op) ? 1 : 0;
            return reg_state;
        }
};

class gtrr : public Operation {
    public:
        vector<int> operate(tuple<int, int, int, int> op, vector<int> reg_state) {
            reg_state[get<3>(op)] = reg_state[get<1>(op)] > reg_state[get<2>(op)] ? 1 : 0;
            return reg_state;
        }
};

class eqir : public Operation {
    public:
        vector<int> operate(tuple<int, int, int, int> op, vector<int> reg_state) {
            reg_state[get<3>(op)] = get<1>(op) == reg_state[get<2>(op)] ? 1 : 0;
            return reg_state;
        }
};

class eqri : public Operation {
    public:
        vector<int> operate(tuple<int, int, int, int> op, vector<int> reg_state) {
            reg_state[get<3>(op)] = reg_state[get<1>(op)] == get<2>(op) ? 1 : 0;
            return reg_state;
        }
};

class eqrr : public Operation {
    public:
        vector<int> operate(tuple<int, int, int, int> op, vector<int> reg_state) {
            reg_state[get<3>(op)] = reg_state[get<1>(op)] == reg_state[get<2>(op)] ? 1 : 0;
            return reg_state;
        }
};

int main() {
    vector<Operation*> operators = {
        new addr(),
        new addi(),
        new mulr(),
        new muli(),
        new banr(),
        new bani(),
        new borr(),
        new bori(),
        new setr(),
        new seti(),
        new gtir(),
        new gtri(),
        new gtrr(),
        new eqir(),
        new eqri(),
        new eqrr(),
    };

    string dummy_line;

    // Store the input data in vectors
    vector<vector<int> > reg_init_state_data, reg_final_state_data;
    vector<tuple<int, int, int, int> > operation_data;

    // Maps a integer operator number with an index in operator vector.
    vector<int> op_mapper(OP_COUNT, -1);

    for (int t = 0; t < SAMPLE_CNT; t++) {
        vector<int> reg_init_state = read_register_state();
        tuple<int, int, int, int> op = read_operation();
        // I don't know why I had to read this fake like.
        getline(cin, dummy_line);
        vector<int> reg_final_state = read_register_state();

        // Reads the empty line between every entry.
        getline(cin, dummy_line);

        reg_init_state_data.push_back(reg_init_state);
        operation_data.push_back(op);
        reg_final_state_data.push_back(reg_final_state);
    }

    vector<set<int> > possibilities(OP_COUNT);
    set<int> found;

    // Initially, everyone is possible.
    for (int i = 0; i < OP_COUNT; i++) {
      for (int j = 0; j < OP_COUNT; j++) {
        possibilities[i].insert(j);
      }
    }

    // Discard impossible operations
    for (int sample_id = 0; sample_id < operation_data.size(); sample_id++) {
      for (int i = 0; i < OP_COUNT; i++) {
        if (found.count(i)) {
          continue;
        }

        vector<int> result = operators[i]->operate(
                                                   operation_data[sample_id],
                                                   reg_init_state_data[sample_id]);

        if (result != reg_final_state_data[sample_id]) {
          possibilities[get<0>(operation_data[sample_id])].erase(i);
        }
      }
    }

    // Iteratively find mappings for each operator
    while (1) {
        bool has_found = false;

        for (int i = 0; i < OP_COUNT; i++) {
          if (possibilities[i].size() == 1) {
            int mapped = *possibilities[i].begin();

            op_mapper[i] = mapped;
            found.insert(mapped);
            has_found = true;

            for (const auto& mapped: found) {
              for (int i = 0; i < OP_COUNT; i++) {
                possibilities[i].erase(mapped);
              }
            }
          }
        }

        if (!has_found) {
          break;
        }
    }

    // Read test program data
    vector<int> registers(REGISTER_SIZE, 0);

    for (int t = 0; t < TEST_CNT; t++) {
      tuple<int, int, int, int> op = read_operation();
      int opcode = op_mapper[get<0>(op)];

      registers = operators[opcode]->operate(op, registers);
    }

    cout << registers[0] << "\n";

    return 0;
}
