#include <bits/stdc++.h>

using namespace std;

// There are only 4 registers
// so the answer vector must have size = 4
vector<int> read_register_state() {
    cout << "in\n";
    vector<int> reg(4);
    string line;
    getline(cin, line);
    cout << line << endl;
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

    const int limit = 3;
    int ans = 0;

    while (!cin.eof()) {
        vector<int> reg_init_state = read_register_state();
        tuple<int, int, int, int> op = read_operation();
        // Intrigued by why I had to add this getline here.
        getline(cin, dummy_line);
        vector<int> reg_final_state = read_register_state();

        getline(cin, dummy_line);

        int ambiguous_op = 0;

        for (const auto& test_operator : operators) {
            vector<int> result = test_operator->operate(op, reg_init_state);

            if (result == reg_final_state) {
                ambiguous_op += 1;
            }
        }

        if (ambiguous_op >= limit) {
            ans += 1;
        }
    }

    cout << ans << "\n";

    return 0;
}