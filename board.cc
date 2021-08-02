#include "SpecialActions.h"
#include "board.h"
#include "level.h"
#include "NextBlock.h"
#include "Action.h"
#include "textdisplay.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"
#include "starblock.h"
#include <vector>
#include <string>
#include <iostream>   // Nata: don't forget to delete this once finished

using namespace std;


// for test
// .................................
Board::Board() {
    currentBlock = level->generateBlock();
    nextBlock = level->generateBlock();
    for (int i = 0; i < 18; ++i) {
        vector<Cell> v;
        theBoard.emplace_back(v);
    }
    for (int i = 0; i < 18; ++i) {
        for (int j = 0; j < 11; ++j) {
            Cell c{i, j, false, ' '};
            theBoard[i].emplace_back(c);
        }
    }
}

void Board::print() {
    cout << "....................." << endl;
    for (int i = 0; i < 18; ++i) {
        for (int j = 0; j < 11; ++j) {
            cout << theBoard[i][j].getName();
        }
        cout << endl;
    }
    cout << "....................." << endl;
    vector<string> v = nextBlock->getRotateDefault();
    cout << v[0] << endl;
    cout << v[1] << endl;
    cout << v[2] << endl;
}

// ........................

// a helper to restore the type of cell to ' '
//static void restoreType(shared_ptr<Block> block) {
//
//}

void Board::clearBoard() {
    score = 0;
    //delete currentBlock;   // Nata: detach is enough
    //delete nextBlock;
    delete action;
    action = nullptr;
    block_created = 0;
    clearRow = false;
    newBlock();
    lose = false;
    /*for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 11; j++) {
            theBoard[i][j].clearCell();
        }
    } */ //  Kenisha: I don't think we need this loop, we can just call theBoard.clear()
    theBoard.clear();
}

void Board::init() {
    clearBoard();
    for (int i = 0; i < NUM_ROWS; i++) {
        vector<Cell> tmp;
        // initialize each column
        for (int j = 0; j < NUM_COLS; j++) {
            Cell cur{i, j, false, ' '};
            tmp.push_back(cur);
        }
        // push back each row
        theBoard.push_back(tmp);
    }
    td->attachBoard(this);
}

bool Board::isShiftValid(int angle, int x, int y) {
    bool is_valid = true;
    int rotateAngle = currentBlock->getAngle() + angle;
        rotateAngle = rotateAngle % 360;
    if (rotateAngle < 0) {
        rotateAngle += 360;
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            char currentChar = ' ';
            if (rotateAngle == 0) {
                currentChar = currentBlock->getRotateDefault()[i][j];
            } else if (rotateAngle == 90) {
                currentChar = currentBlock->getRotate90()[i][j];
            } else if (rotateAngle == 180) {
                currentChar = currentBlock->getRotate180()[i][j];
            } else if (rotateAngle == 270) {
                currentChar = currentBlock->getRotate270()[i][j];
            }

            if (currentChar != ' ') {
                int currentAngle = currentBlock->getAngle();
                int blockX = currentBlock->getXcoord();
                int blockY = currentBlock->getYcoord();
                int currentX = currentBlock->getXcoord() + x;
                int currentY = currentBlock->getYcoord() + y;
                if (currentX + j < 0 || currentY + i < 0 || currentX + j > 19 || currentY + i > 19) {
                    is_valid = false;
                }
                if (theBoard[currentY + i][currentX + j].isOccupied() == true) {
                    if (currentX + j < blockX || currentY + i < blockY ||
                    currentX + j > blockX + 3 || currentY + i > blockY + 3) {
                        is_valid = false;
                    }
                    if (currentAngle == 0) {
                        if (currentBlock->getRotateDefault()[y + i][x + j] == ' ') {
                            is_valid = false;
                        }
                    } else if (currentAngle == 90) {
                        if (currentBlock->getRotate90()[y + i][x + j] == ' ') {
                            is_valid = false;
                        }
                    } else if (currentAngle == 180) {
                        if (currentBlock->getRotate180()[y + i][x + j] == ' ') {
                            is_valid = false;
                        }
                    } else if (currentAngle == 270) {
                        if (currentBlock->getRotate270()[y + i][x + j] == ' ') {
                            is_valid = false;
                        }
                    }
                }

            }

        }
    }
    return is_valid;
}


void Board::move(int angle, int x, int y) {
    int currentAngle = currentBlock->getAngle();
    vector<string> currentRotation;
    if (currentAngle == 0) {
        currentRotation = currentBlock->getRotateDefault();
    } else if (currentAngle == 90) {
        currentRotation = currentBlock->getRotate90();
    } else if (currentAngle == 180) {
        currentRotation = currentBlock->getRotate180();
    } else if (currentAngle == 270) {
        currentRotation = currentBlock->getRotate270();
    }
    int currentX = currentBlock->getXcoord();
    int currentY = currentBlock->getYcoord();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (currentRotation[i][j] != ' ') {
                theBoard[currentY + i][currentX + j].clearCell();
            }

        }
    }
    int rotateAngle = currentAngle + angle;
    rotateAngle = rotateAngle % 360;
    if (rotateAngle < 0) {
        rotateAngle += 360;
    }
    vector<string> rotation;
    if (rotateAngle == 0) {
        rotation = currentBlock->getRotateDefault();
    } else if (rotateAngle == 90) {
        rotation = currentBlock->getRotate90();
    } else if (rotateAngle == 180) {
        rotation = currentBlock->getRotate180();
    } else if (rotateAngle == 270) {
        rotation = currentBlock->getRotate270();
    }
    currentBlock->setXcoord(currentX + x);
    currentBlock->setYcoord(currentY + y);
    currentBlock->setAngle(rotateAngle);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (rotation[i][j] != ' ') {
                theBoard[currentY + y + i][currentX + x + j].setName(rotation[i][j]);
            }
        }
    }

}


void Board::left(int steps) {
    for (int i = 0; i < steps; i++) {
        if (isShiftValid(0, -1, 0) == false) {
            break;
        } else {
            move(0, -1, 0);
        }
    }
    if (level_n >= 3 && isShiftValid(0, 0, 1) == true) {
        move(0, 0, 1);
    }
    if (action != nullptr) {
        Heavy * h = dynamic_cast<Heavy *>(action);
        if (h != nullptr) {
            for (int i = 0; i < 2; ++i) {
                if (isShiftValid(0, 0, 1) == false) {
                   drop();
                   break;
                } else {
                   move(0, 0, 1);
                }
            }
        }
    }
    print();
}



void Board::right(int steps) {
    for (int i = 0; i < steps; i++) {
        if (isShiftValid(0, 1, 0) == false) {
            break;
        } else {
            move(0, 1, 0);
        }
    }
    if (level_n >= 3 && isShiftValid(0, 0, 1) == true) {
        move(0, 0, 1);
    }
    if (action != nullptr) {
        Heavy * h = dynamic_cast<Heavy *>(action);
        if (h != nullptr) {
            for (int i = 0; i < 2; ++i) {
                if (isShiftValid(0, 0, 1) == false) {
                   drop();
                   break;
                } else {
                   move(0, 0, 1);
                }
            }
        }
    }
    print();
}


void Board::down(int steps) {
    for (int i = 0; i < steps; i++) {
        if (isShiftValid(0, 0, 1) == false) {
            break;
        } else {
            move(0, 0, 1);
        }
    }
    if (level_n >= 3 && isShiftValid(0, 0, 1) == true) {
        move(0, 0, 1);
    }
    print();
}


void Board::drop() {
    while (isShiftValid(0, 0, 1) == true) {
        move(0, 0, 1);
    }
    newBlock();
    delete action;
    action = nullptr;
    *turn += 1;
    detectRow();
    print();
}

void Board::clockwise(int angle) {
    if (isShiftValid(angle, 0, 0) == true) {
        move(angle, 0, 0);
    }
    if (level_n >= 3 && isShiftValid(0, 0, 1) == true) {
        move(0, 0, 1);
    }
    print();
}


void Board::counterclockwise(int angle) {
    if (isShiftValid(-1 * angle, 0, 0) == true) {
        move(-1 * angle, 0, 0);
    }
    if (level_n >= 3 && isShiftValid(0, 0, 1) == true) {
        move(0, 0, 1);
    }
    print();
}

// for level
void Board::addLevel(int n, int seed, bool set_seed, string file) {
        delete level;
    level_n = n;
        if (n == 0) {
                level = new levelZero{ file, seed, set_seed };
        }
        else if (n == 1) {
                level = new levelOne{ seed, set_seed };
        }
        else if (n == 2) {
                level = new levelTwo{ seed, set_seed };
        }
        else if (n == 3) {
                level = new levelThree{ seed, set_seed };
        }
        else {
                level = new levelFour{ seed, set_seed, this };
        }
}

// This is a  helper
Block* helperBlock(int x, int y, char c) {
  Block * block;
  if (c == 'L') {
    block = new Lblock{x, y, 0, false, 0, 'L'};
  } else if (c == 'I') {
      block = new Iblock{x, y, 0, false, 0, 'I'};
  }
   else if (c == 'J') {
      block = new Jblock{x, y, 0, false, 0, 'J'};
  }
   else if (c == 'O') {
      block = new Oblock{x, y, 0, false, 0, 'O'};
  }
   else if (c == 'S') {
      block = new Sblock{x, y, 0, false, 0, 'S'};
  }
   else if (c == 'Z') {
      block = new Zblock{x, y, 0, false, 0, 'Z'};
  }
   else if (c == 'T') {
      block = new Tblock{x, y, 0, false, 0, 'T'};
  }
   else {
      block = new Starblock{x, y, 0, false, 0, '*'};
  }
  return block;
}

// for block
void Board::newBlock(char c) {
    ++block_created;
    delete currentBlock;
        if (c == 'n') {
                currentBlock = nextBlock;
                nextBlock = level->generateBlock();
        }
        else {
        // Nata: careful! new block should always fit the current position
        --block_created;
        int x = currentBlock->getXcoord();
        int y = currentBlock->getYcoord();
        this->currentBlock = helperBlock(x, y, c);
        }
    if (block_created % 5 == 0) {
        clearRow = false;
    }
    print();
}


// opponent
void Board::attach(Board* opponent, int* n) {
        this->opponent = opponent;
        turn = n;
        td->attachOpponent(opponent);
}

void Board::addAction(Board* opponent, string s) {
    delete opponent->action;
        cout << "choose an action" << endl;
        string in;
        cin >> in;
        if (in == "blind") {
                opponent->action = new Blind;
                opponent->action->applyAction();
        }
        else if (in == "heavy") {
                opponent->action = new Heavy;
        }
        else {
                char c;
                cin >> c;
                opponent->action = new Force;
                delete opponent->currentBlock;
                opponent->currentBlock = helperBlock(0, 0, c);
                // notify

        }
}

void Board::dropStar() {
    Block* tmp = currentBlock;
    currentBlock = helperBlock(0, 5, '*');
    while (isShiftValid(0, 0, 1) == true) {
        move(0, 0, 1);
    }
    delete currentBlock;
    detectRow();
    currentBlock = tmp;
}

void Board::detectRow() {
    int count = 0;
    for (int row = 17; row >= 3; --row ) {
        for (int col = 0; col < 11; ++col) {
            if (theBoard[row][col].getName() == ' ') {
                break;
            }
            if (col == 10) {
                for (int i = row + 1; i >= 3; --i) {
                    for (int j = 0; j < 11; ++j) {
                        theBoard[i - 1][j] = theBoard[i][j];
                    }
                }
                for (int j = 0; j < 11; ++j) {
                    theBoard[3][j].clearCell();
                }
                --row;
                ++count;
            }
        }
    }
    if (count > 0) {
        clearRow = true;
    }
    if (count > 1) {
        addAction(opponent, " ");
    }
}

void Board::setRandom(bool set, string s) {
        level->changeState(set, s);
}

bool Board::determineLose() {
        return lose;
}

int Board::determineScore() {
        return score;
}

vector<vector<Cell>> Board::getBoard() {
    return theBoard;
}

ostream &operator<<(ostream &out, const Board &b) {
    out << *(b.td) << endl;
    return out;
}

// Destructor
Board::~Board() {
    delete level;
    delete action;
    delete currentBlock;
    delete nextBlock;
}


