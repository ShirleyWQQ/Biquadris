#include "textdisplay.h"
#include "board.h"
#include <iostream>  // delete this
using namespace std;

TextDisplay::TextDisplay() {}

TextDisplay::~TextDisplay() {
}

void TextDisplay::attachBoard(Board* board) {
    this->board = board;
}
void TextDisplay::attachOpponent(Board* opponent) {
    this->opponent = opponent;
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
    out << "Level:    " << td.board->getLevel() << "      " << "Level:    " << td.opponent->getLevel() << endl;
    out << "Score:    " << td.board->getScore() << "      " << "Score:    " << td.opponent->getScore() << endl;
    out << "-----------" << "      " << "-----------" << endl;
    for (int i = 0; i < td.NUM_ROWS; i++) {
        cout << "-";
        for (int j = 0; j < td.NUM_COLS; j++) {
            out << td.board->getBoard()[i][j].getName();
        }
        cout << "-";
        out << "      ";
        cout << "-";
        for (int j = 0; j < td.NUM_COLS; j++) {
            out << td.opponent->getBoard()[i][j].getName();
        }
        cout << "-";
        out << endl;
    }
    out << "-----------" << "      " << "-----------" << endl;
    out << "Next:      " << "      " << "Next:      " << endl;
    for (int i = 2; i < 5; i++) {
        out << td.board->getNextBlock()->getRotateDefault()[i] << "            " << td.opponent->getNextBlock()->getRotateDefault()[i] << endl;
    }
    cout << "error td display" << endl;
    return out;
}
