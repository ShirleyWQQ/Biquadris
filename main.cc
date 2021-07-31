#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "Board.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc > 10) {
        cout << "too many arguments" << endl;
        return 1;
    }
    bool textOnly = false;
    bool set_seed = false;
    int seed;
    string file1 = "sequence1.txt";
    string file2 = "sequence2.txt";
    int level = 0;
    for (int i = 1; i < argc; ++i) {
        string commandLine = string(argv[i]);
        if (commandLine == "-scriptfile1") {
            file1 = string(argv[i + 1]);
            ++i;
        }
        else if (commandLine == "-scriptfile2") {
            file2 = string(argv[i + 1]);
            ++i;
        }
        else if (commandLine == "-text") {
            textOnly = true;
        }
        else if (commandLine == "-seed") {
            seed = stoi(string(argv[i + 1]));
            set_seed = true;
            ++i;
        }
        else if (commandLine == "-startlevel") {
            level = stoi(string(argv[i + 1]));
            ++i;
        }
        else {
            cout << "invalid argument" << endl;
            return 1;
        }
    }
    // set up boards
    int turn = 0;
    Board player1;
    Board player2;
    player1.attach(&player2, &turn);
    player2.attach(&player1, &turn);
    player1.addLevel(level, seed, set_seed, file1);
    player2.addLevel(level, seed, set_seed, file2);

    string s1 = "left", s2 = "right", s3 = "down", s4 = "clockwise", s5 = "counterclockwise", s6 = "drop",
        s7 = "levelup", s8 = "leveldown", s9 = "norandom", s10 = "random", s11 = "sequence", s12 = "restart";

    bool read_sequence = false;
    string sequence;
    int tmp_times = 0;
    ifstream f;

    while (true) {
        string cmd;
        int times = 1;
        if (read_sequence == true) {
            f >> cmd;
            if (f.fail()) {
                --tmp_times;
                if (tmp_times > 0) {
                    f = ifstream{ sequence };
                    f >> cmd;
                    if (f.fail()) cmd = "abcd";
                }
                else {
                    read_sequence = false;
                    cin >> cmd;
                    if (cin.fail()) break;
                }
            }
        }
        else {
            cin >> cmd;
            if (cin.fail()) break;
        }
        if (cmd[0] >= '0' && cmd[0] <= '9') {
            string num;
            int count = 0;
            int len = cmd.size();
            for (int i = 0; i < len; ++i) {
                num += cmd[i];
                if (cmd[i] > '9' || cmd[i] < '0') {
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
            cout << "Unrecognized command " << cmd << "!" << endl;
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
            cout << "Unrecognized command " << cmd << "!" << endl;
            continue;
        }

        // input is truely applied starting here
        if (cmd == s1) {  //left
            for (int i = 0; i < times; ++i) {
                if (turn % 2 == 0) {
                    player1.left(1);
                }
                else {
                    player2.left(1);
                }
            }
        }
        else if (cmd == s2) {  //right
            for (int i = 0; i < times; ++i) {
                if (turn % 2 == 0) {
                    player1.right(1);
                }
                else {
                    player2.right(1);
                }
            }
        }
        else if (cmd == s3) {  //down

        }
        else if (cmd == s4) {  //clockwise
            for (int i = 0; i < times; ++i) {
                if (turn % 2 == 0) {
                    player1.clockwise(90);
                }
                else {
                    player2.clockwise(90);
                }
            }
        }
        else if (cmd == s5) {  //counterclockwise
            for (int i = 0; i < times; ++i) {
                if (turn % 2 == 0) {
                    player1.counterclockwise(90);
                }
                else {
                    player2.counterclockwise(90);
                }
            }
        }
        else if (cmd == s6) {  //drop
            
        }
        else if (cmd == s7) {  //levelup
            if (level + times <= 4) {
                level += times;
                if (turn % 2 == 0) {
                    player1.addLevel(level, seed, false, file1);
                }
                else {
                    player2.addLevel(level, seed, false, file2);
                }
            }
        }
        else if (cmd == s8) {  //leveldown
            if (level - times >= 0) {
                level -= times;
                if (turn % 2 == 0) {
                    player1.addLevel(level, seed, false, file1);
                }
                else {
                    player2.addLevel(level, seed, false, file2);
                }
            }
        }
        else if (cmd == s9) {  //norandom
            if (turn % 2 == 0) {
                player1.setRandom(false, file1);
            }
            else {
                player2.setRandom(false, file2);
            }
        }
        else if (cmd == s10) {  //random
            string newFile;
            cin >> newFile;
            if (turn % 2 == 0) {
                player1.setRandom(true, newFile);
            }
            else {
                player2.setRandom(true, newFile);
            }
        }
        else if (cmd == "I" || cmd == "J" || cmd == "L" || cmd == "O" ||
            cmd == "S" || cmd == "Z" || cmd == "T") {

        }
        else if (cmd == s11) {  //sequence
            read_sequence = true;
            cin >> sequence;
            f = ifstream{ sequence };
            tmp_times = times;
        }
        else if (cmd == s12) {  //restart

        }
        else {
            cout << "Unrecognized command " << cmd << "!" << endl;
            continue;
        }

        if (player1.determineLose() == true || player2.determineLose() == true) {
            if (player1.determineLose()) {
                cout << "player2 wins" << endl;
            }
            else {
                cout << "player1 wins" << endl;
            }
            int score1 = play1.determineScore();
            int score2 = play2.determineScore();
            cout << "the highest score is " << max(score1, score2) << endl;
            cout << "Game is Over" << endl;
            break;
        }
    }

    return 0;
}
