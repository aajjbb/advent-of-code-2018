#include <bits/stdc++.h>

using namespace std;

// There are only 4 registers
// so the answer vector must have size = 4
vector<int> read_register_state(ifstream& input) {
    vector<int> reg(4);
    string line;
    cout << line << endl;
    sscanf(line.c_str(),
        "%*7s [%d, %d, %d, %d]",
        &reg[0],
        &reg[1],
        &reg[2],
        &reg[3]);

    return reg;
}

tuple<int, int, int, int> read_operation(ifstream& input) {
    int a, b, c, d;

    input >> a >> b >> c >> d;
    cout << a << " " << b << " " << c << " " << d << endl;
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
    ifstream operator_input("day16-part1-input.txt");
    //ifstream example_input("day16-part2-input.txt");

    if (!operator_input.is_open()) {
        cout << "Failed to read input\n";
        return -1;
    }

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

    const int limit = 3;
    const int OP_COUNT = 16;
    int ans = 0;

    // Store the input data in vectors
    vector<vector<int> > reg_init_state_data, reg_final_state_data;
    vector<tuple<int, int, int, int> > operation_data;
    vector<vector<int> > operation_grouping(OP_COUNT, vector<int>());

    // Maps a integer operator number with an index in operator vector.
    map<int, int> operation_mapping;

    // Memorizes wether an operation has already been matched.
    vector<bool> found_op(OP_COUNT, false);
    vector<bool> found_operator_list(OP_COUNT, false);

    while (operator_input.get() && operator_input.gcount() == 1) {
        operator_input.unget();

        vector<int> reg_init_state = read_register_state(operator_input);
        tuple<int, int, int, int> op = read_operation(operator_input);
        // I don't know why I had to read this fake like.
        getline(operator_input, dummy_line);
        vector<int> reg_final_state = read_register_state(operator_input);

        // Reads the empty line between every entry.
        getline(operator_input, dummy_line);

        reg_init_state_data.push_back(reg_final_state);
        operation_data.push_back(op);
        reg_final_state_data.push_back(reg_final_state);

        // group results for each operation
        operation_grouping[get<0>(op)].push_back(operation_data.size() - 1);
    }

    operator_input.close();

    // Iteratively find mappings for each operator
    while (1) {
        bool has_found = false;

        for (int i = 0; i < OP_COUNT; i++) {
            if (found_op[i]) {
                continue;
            }

            int correct_operator_id = -1;
            int complete_match_count = 0;

            for (int j = 0; j < operators.size(); j++) {
                if (found_operator_list[j]) {
                    continue;
                }

                int match = 0;
                int attempted = 0;

                for (int k = 0; k < operation_grouping[i].size(); k++) {
                    int input_id = operation_grouping[i][k];

                    vector<int> result = operators[j]->operate(
                        operation_data[input_id],
                        reg_init_state_data[input_id]
                    );

                    if (result == reg_final_state_data[input_id]) {
                        match += 1;
                    }
                }

                if (match == operation_grouping[i].size()) {
                    complete_match_count += 1;
                    correct_operator_id = j;
                }
            }

            if (complete_match_count == 1) {
                found_op[i] = true;
                found_operator_list[correct_operator_id] = true;
                operation_mapping[i] = correct_operator_id;
                has_found = true;
            }
        }

        if (!has_found) {
            break;
        }
    }

    cout << ans << "\n";

    return 0;
}