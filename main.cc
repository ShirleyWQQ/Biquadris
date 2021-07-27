#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "need more sequence.txt" << std::endl;
        return 1;
    }

    string cmd;
    int times = 1;
    string s1 = "left", s2 = "right", s3 = "down", s4 = "clockwise", s5 = "counterclockwise", s6 = "drop",
        s7 = "levelup", s8 = "leveldown", s9 = "norandom", s10 = "random", s11 = "sequence", s12 = "restart";


    // Have to guarentee that the macro languages are different
    while (true) {
        cin >> cmd;
        if (cin.eof()) break;
        if (cmd[0] == '0') {
            cout << "invalid input" << endl;
            continue;
        }
        if (cmd[0] >= '1' && cmd[0] <= '9') {
            string num;
            int count = 0;
            int len = cmd.size();
            for (int i = 0; i < len; ++i) {
                num += cmd[i];
                if (cmd[i] > '9' || cmd[i] < '1') {
                    break;
                }
                ++count;
            }
            times = stoi(num);
            cmd = cmd.substr(count);
        }

        // deal with macro language
        int size = cmd.size();
        if (size > 1 && s1.find(cmd) == string::npos && s2.find(cmd) == string::npos && s3.find(cmd) == string::npos &&
            s4.find(cmd) == string::npos && s5.find(cmd) == string::npos && s6.find(cmd) == string::npos &&
            s7.find(cmd) == string::npos && s8.find(cmd) == string::npos && s9.find(cmd) == string::npos &&
            s10.find(cmd) == string::npos && s11.find(cmd) == string::npos && s12.find(cmd) == string::npos) {
            cout << "invalid input" << endl;
            continue;
        }
        if (cmd[0] == 'l') {
            if (size <= 2) {
                cout << "unable to determine which command" << endl;
                continue;
            }
            if (cmd[2] == 'f') {
                cmd = s1;
            }
            else if (size <= 5) {
                cout << "unable to determine which command" << endl;
                continue;
            }
            else if (cmd[5] == 'u') {
                cmd = s7;
            }
            else {
                cmd = s8;
            }
        }
        else if (cmd[0] == 'r') {
            if (size == 1) {
                cout << "unable to determine which command" << endl;
                continue;
            }
            if (cmd[1] == 'i') {
                cmd = s2;
            }
            else if (cmd[1] == 'a') {
                cmd = s10;
            }
            else {
                cmd = s12;
            }
        }
        else if (cmd[0] == 'd') {
            if (size == 1) {
                cout << "unable to determine which command" << endl;
                continue;
            }
            if (cmd[1] == 'o') {
                cmd = s3;
            }
            else {
                cmd = s6;
            }
        }
        else if (cmd[0] == 'c') {
            if (size == 1) {
                cout << "unable to determine which command" << endl;
                continue;
            }
            if (cmd[1] == 'l') {
                cmd = s4;
            }
            else {
                cmd = s5;
            }
        }
        else if (cmd[0] == 'n') {
            cmd = s9;
        }
        else if (cmd[0] == 's') {
            cmd = s11;
        }

        if (cmd != "I" && cmd != "J" && cmd != "L" && cmd != "O" &&
            cmd != "S" && cmd != "Z" && cmd != "T" && cmd.size() == 1) {
            cout << "invalid input" << endl;
            continue;
        }

        // multipliers don't apply to these commands
        if (cmd == "restart" || cmd == "norandom" || cmd == "random") {
            times = 1;
        }

        // input is truely applied starting here
        if (cmd == s1) {

        }
        else if (cmd == s2) {

        }
        else if (cmd == s3) {
            
        }
        else if (cmd == s4) {

        }
        else if (cmd == s5) {

        }
        else if (cmd == s6) {

        }
        else if (cmd == s7) {

        }
        else if (cmd == s8) {

        }
        else if (cmd == s9) {

        }
        else if (cmd == s10) {

        }
        else if (cmd == "I" || cmd == "J" || cmd == "L" || cmd == "O" || 
                 cmd == "S" || cmd == "Z" || cmd == "T") {

        }
        else if (cmd == s11) {

        }
        else if (cmd == s12) {

        }
        else {
            cerr << "Unrecognized command " << cmd << "!" << endl;
            continue;
        }
    }

    return 0;
}
