#include <bits/stdc++.h>

using namespace std;

class Operation {
    public:
        virtual vector<int> operate(tuple<string, int, int, int> op, vector<int> reg_state) = 0;
};

class addr : public Operation {
    public:
        vector<int> operate(tuple<string, int, int, int> op, vector<int> reg_state) {
            reg_state[get<3>(op)] = reg_state[get<1>(op)] + reg_state[get<2>(op)];
            return reg_state;
        }
};

class addi : public Operation {
    public:
        vector<int> operate(tuple<string, int, int, int> op, vector<int> reg_state) {
            reg_state[get<3>(op)] = reg_state[get<1>(op)] + get<2>(op);
            return reg_state;
        }
};

class mulr : public Operation {
    public:
        vector<int> operate(tuple<string, int, int, int> op, vector<int> reg_state) {
            reg_state[get<3>(op)] = reg_state[get<1>(op)] * reg_state[get<2>(op)];
            return reg_state;
        }
};

class muli : public Operation {
    public:
        vector<int> operate(tuple<string, int, int, int> op, vector<int> reg_state) {
            reg_state[get<3>(op)] = reg_state[get<1>(op)] * get<2>(op);
            return reg_state;
        }
};

class banr : public Operation {
    public:
        vector<int> operate(tuple<string, int, int, int> op, vector<int> reg_state) {
            reg_state[get<3>(op)] = reg_state[get<1>(op)] & reg_state[get<2>(op)];
            return reg_state;
        }
};

class bani : public Operation {
    public:
        vector<int> operate(tuple<string, int, int, int> op, vector<int> reg_state) {
            reg_state[get<3>(op)] = reg_state[get<1>(op)] & get<2>(op);
            return reg_state;
        }
};

class borr : public Operation {
    public:
        vector<int> operate(tuple<string, int, int, int> op, vector<int> reg_state) {
            reg_state[get<3>(op)] = reg_state[get<1>(op)] | reg_state[get<2>(op)];
            return reg_state;
        }
};

class bori : public Operation {
    public:
        vector<int> operate(tuple<string, int, int, int> op, vector<int> reg_state) {
            reg_state[get<3>(op)] = reg_state[get<1>(op)] | get<2>(op);
            return reg_state;
        }
};

class setr : public Operation {
    public:
        vector<int> operate(tuple<string, int, int, int> op, vector<int> reg_state) {
            reg_state[get<3>(op)] = reg_state[get<1>(op)];
            return reg_state;
        }
};

class seti : public Operation {
    public:
        vector<int> operate(tuple<string, int, int, int> op, vector<int> reg_state) {
            reg_state[get<3>(op)] = get<1>(op);
            return reg_state;
        }
};

class gtir : public Operation {
    public:
        vector<int> operate(tuple<string, int, int, int> op, vector<int> reg_state) {
            reg_state[get<3>(op)] = get<1>(op) > reg_state[get<2>(op)] ? 1 : 0;
            return reg_state;
        }
};

class gtri : public Operation {
    public:
        vector<int> operate(tuple<string, int, int, int> op, vector<int> reg_state) {
            reg_state[get<3>(op)] = reg_state[get<1>(op)] > get<2>(op) ? 1 : 0;
            return reg_state;
        }
};

class gtrr : public Operation {
    public:
        vector<int> operate(tuple<string, int, int, int> op, vector<int> reg_state) {
            reg_state[get<3>(op)] = reg_state[get<1>(op)] > reg_state[get<2>(op)] ? 1 : 0;
            return reg_state;
        }
};

class eqir : public Operation {
    public:
        vector<int> operate(tuple<string, int, int, int> op, vector<int> reg_state) {
            reg_state[get<3>(op)] = get<1>(op) == reg_state[get<2>(op)] ? 1 : 0;
            return reg_state;
        }
};

class eqri : public Operation {
    public:
        vector<int> operate(tuple<string, int, int, int> op, vector<int> reg_state) {
            reg_state[get<3>(op)] = reg_state[get<1>(op)] == get<2>(op) ? 1 : 0;
            return reg_state;
        }
};

class eqrr : public Operation {
    public:
        vector<int> operate(tuple<string, int, int, int> op, vector<int> reg_state) {
            reg_state[get<3>(op)] = reg_state[get<1>(op)] == reg_state[get<2>(op)] ? 1 : 0;
            return reg_state;
        }
};

int main() {
    map<string, Operation*> operators = {
        {"addr", new addr()},
        {"addi", new addi()},
        {"mulr", new mulr()},
        {"muli", new muli()},
        {"banr", new banr()},
        {"bani", new bani()},
        {"borr", new borr()},
        {"bori", new bori()},
        {"setr", new setr()},
        {"seti", new seti()},
        {"gtir", new gtir()},
        {"gtri", new gtri()},
        {"gtrr", new gtrr()},
        {"eqir", new eqir()},
        {"eqri", new eqri()},
        {"eqrr", new eqrr()},
    };

    const int REG_COUNT = 6;

    int ip_reg = 0;
    vector<tuple<string, int, int, int> > inst;
    vector<int> registers(REG_COUNT);

    string line;
    getline(cin, line);

    sscanf(line.c_str(), "#ip %d", &ip_reg);

    int ip = registers[ip_reg];

    while (getline(cin, line)) {
        string op;
        int a, b, c;

        istringstream ss(line);
        
        ss >> op >> a >> b >> c;

        inst.push_back(make_tuple(op, a, b, c));
    }

    while (ip >= 0 && ip < inst.size()) {
        registers[ip_reg] = ip;

        tuple<string, int, int, int> instruction = inst[ip];
        
        registers = operators[get<0>(instruction)]->operate(
            inst[ip], 
            registers
        );

        ip = registers[ip_reg];
        ip += 1;
    }

    cout << registers[0] << endl;

    return 0;
}