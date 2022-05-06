#include "ticto.h"
#include "libstl/stdio.h"
#include "libstl/strings.h"
#include "drivers/input/keyboard.h"

bool printResult(int result);
char printBoard();
int readYourMove();
int getIndex(int number);
int computerMove(int lastMove);

char board[10] = { 0 };
char human;
char computer;
int move = 0;
char result;

bool ticto_update() {
    // Print text on the screen with 30 spaces before text
    printf("                              TIC TAC TOE");
    // Print text on screen with 15 spaces before text
    printf("               CREATIVE COMPUTING  MORRISTOWN, NEW JERSEY");
    // THIS PROGRAM PLAYS TIC TAC TOE
    printf("THE BOARD IS NUMBERED:");
    printf("1  2  3");
    printf("4  5  6");
    printf("7  8  9");
    print("\n\nDO YOU WANT 'X' OR 'O'");
    char key = getchar();
    printf("");
    // cleanup the board
    for(int i=0; i < 10; i++) {
        board[i]=' ';
    }
    // X GOES FIRST
    if (key == 'X' || key == 'x') {
        human = 'X';
        computer = 'O';
        move = readYourMove();
        if (move == -50) return true;
        board[move] = human;
        printBoard();
    } else {
        human = 'O';
        computer = 'X';
    }

    for(;;){
        move = computerMove(move);
        board[move] = computer;
        printf("\n\nTHE COMPUTER MOVES TO %d... \n", move);
        result = printBoard();
        if (printResult(result)) break;
        move = readYourMove();
        if (move == -50) break;
        board[move] = human;
        result = printBoard();
        if (printResult(result)) break;
    }
    return true;
}

bool printResult(int result) {
    if (result == '\0') {
        printf("IT'S A DRAW. THANK YOU.");
        return true;
    } else if (result == computer) {
        printf("I WIN, TURKEY!!!");
        return true;
    } else if (result == human) {
        printf("YOU BEAT ME!! GOOD GAME.");
        return true;
    }

    return false;
}
char printBoard() {
    for (int i=1; i < 10; i++){
        putc(' ');
        putc(board[i]);
        if (i % 3 == 0) {
            if (i < 9) {
                print("\n---+---+---\n");
            } else {
                print("\n");
            }
        } else {
            print(" !");
        }
    }
    // horizontal check
    for (int i = 1; i <= 9; i += 3) {
        if (board[i] != ' ' && (board[i] == board[i+1]) && (board[i+1] == board[i+2])) {
            return board[i];
        }
    }
    // vertical check
    for (int i = 1; i <= 3; i++) {
        if (board[i] != ' ' && (board[i] == board[i+3]) && (board[i] == board[i+6])) {
            return board[i];
        }
    }
    // cross
    if (board[5] != ' ') {
        if ((board[1] == board[5] && board[9] == board[5]) || (board[3] == board[5] && board[7] == board[5])) {
            return board[5];
        }
    }
    // draw check
    for (int i = 1; i <= 9; i++) {
        if (board[i] == ' ') {
            return ' ';
        }
    }
    return '\0';
}

int readYourMove()  {
    int number = 0;
    for(;;) {
        print("\n\nWHERE DO YOU MOVE? ");
        char key = getchar();
        putc('\n');
        if (key == '0') {
            printf("THANKS FOR THE GAME.");
            return -50;
        }
        if (key >= '1' && key <= '9') {
            number = key - '0';
            if (number > 9 || board[number] != ' ') {
                printf("THAT SQUARE IS OCCUPIED.\n");
                continue;
            }
        }
        return number;
    }
}

int getIndex(int number) {
    return ((number - 1) % 8) + 1; //number - 8 * (int)((number - 1) / 8);
}

int computerMove(int lastMove) {
    int boardMap[] = {0, 1, 2, 3, 6, 9, 8, 7, 4, 5};
    int index;
    for (size_t i = 0; i < sizeof(boardMap); i++)
    {
        if (boardMap[i] == lastMove)
        {
            index = i;
            break;
        }
    }

    if (lastMove == 0 || board[5] == ' '){
        return 5;
    }

    if (lastMove == 5 && board[1] == ' ') {
        return 1;
    }
    if (board[5] == human) {
        // check possible win
        if (board[1] == computer && board[2] == ' ' && board[3] == computer) {
            return 2;
        }
        if (board[7] == computer && board[8] == ' ' && board[9] == computer) {
            return 8;
        }
        if (board[1] == computer && board[4] == ' ' && board[7] == computer) {
            return 4;
        }
        if (board[3] == computer && board[6] == ' ' && board[7] == computer) {
            return 6;
        }
        // check cross
        int crossIndex = boardMap[getIndex(index + 4)];
        if (board[crossIndex] == ' ') {
            return crossIndex;
        }
        int stepForward2 = boardMap[getIndex(index + 2)];
        if (board[stepForward2] == ' ') {
            return stepForward2;
        }
        int stepBackward2 = boardMap[getIndex(index + 6)];
        if (board[stepBackward2] == ' ') {
            return stepBackward2;
        }
        int stepForward1 = boardMap[getIndex(index + 1)];
        if (board[stepForward1] == ' ') {
            return stepForward1;
        }
        int stepBackward1 = boardMap[getIndex(index + 7)];
        if (board[stepBackward1] == ' ') {
            return stepBackward1;
        }
        int stepForward3 = boardMap[getIndex(index + 3)];
        if (board[stepForward3] == ' ') {
            return stepForward3;
        }
        int stepBackward3 = boardMap[getIndex(index + 5)];
        if (board[stepBackward3] == ' ') {
            return stepBackward3;
        }
    } else {
        // check possible win
        if (board[1] == computer && board[9] == ' ') {
            return 9;
        }
        if (board[9] == computer && board[1] == ' ') {
            return 1;
        }
        if (board[3] == computer && board[7] == ' ') {
            return 7;
        }
        if (board[7] == computer && board[3] == ' ') {
            return 3;
        }
        // if corner
        if (index % 2 == 1) {
            int stepForward2 = boardMap[getIndex(index + 2)];
            if (board[stepForward2] == ' ') {
                return stepForward2;
            }
            int stepBackward2 = boardMap[getIndex(index + 6)];
            if (board[stepBackward2] == ' ') {
                return stepBackward2;
            }
        } else {
            int stepForward1 = boardMap[getIndex(index + 1)];
            if (board[stepForward1] == ' ') {
                return stepForward1;
            }
            int stepBackward1 = boardMap[getIndex(index + 7)];
            if (board[stepBackward1] == ' ') {
                return stepBackward1;
            }
            int stepForward3 = boardMap[getIndex(index + 3)];
            if (board[stepForward3] == ' ') {
                return stepForward3;
            }
            int stepBackward3 = boardMap[getIndex(index + 5)];
            if (board[stepBackward3] == ' ') {
                return stepBackward3;
            }
                    int crossIndex = boardMap[getIndex(index + 4)];
            if (board[crossIndex] == ' ') {
                return crossIndex;
            }
            int stepForward2 = boardMap[getIndex(index + 2)];
            if (board[stepForward2] == ' ') {
                return stepForward2;
            }
            int stepBackward2 = boardMap[getIndex(index + 6)];
            if (board[stepBackward2] == ' ') {
                return stepBackward2;
            }
        }
    }

    return 0;
}