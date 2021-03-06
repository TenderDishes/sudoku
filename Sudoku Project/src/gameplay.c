//  Created by Team-FMR on 10.04.18.

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../include/constants.h"
#include "../include/converter.h"
#include "../include/gameplay.h"
#include "../include/consolePrinter.h"
#include "../include/input.h"
#include "../include/exporter.h"
#include "../include/validator.h"

/*
game rountine
params: struct s_sudoku sudoku
returns: struct s_sudoku sudoku
*/
struct s_sudoku gameRoutine(struct s_sudoku sudoku)
{
    int gameLoop = 1;
    int input = 0;
    const int offset = 9;

    int i, j, k;

    int x = 16;
    int y = 5+offset;

    int row = 0;
    int line = 0;

    int cursorBoundary[2][2] = {{4,offset},{28,12+offset}};

    char path[getPathSize()];

    sudoku.timeStart = time(NULL);
    while (gameLoop)
    {
        CLS;
        //menu strings
        printf("Moves: %i\n", sudoku.moves);
        printf("0-9 -> Wert an Stelle eintragen\n");
        printf("s -> Spielstand speichern und Spiel beenden\n");
        printf("h -> L\x94sungshinweis einblenden\n");
        printf("m -> Hauptmen\x81\n");
        printf("e -> Spiel beenden\n\n");

        //if the sudoku is successfully solved then end the game
        if(printSudoku(sudoku))
        {
            gameLoop = 0;
            sudoku.navigation = 3;
            sudoku.timeEnd = time(NULL);
            return sudoku;
        }

        //Move the cursor to the desired position and don't let it get out of the board
        cursorGoTo(x,y);

        input = getMove();
        switch(input)
        {
        case -1: //left
            if(x > cursorBoundary[0][0])
            {
                x-=2;
            }
            break;
        case 1: //right
            if(x < cursorBoundary[1][0])
            {
                x+=2;
            }
            break;
        case 2: //up
            if(y > cursorBoundary[0][1])
            {
                y--;
            }
            break;
        case -2: //down
            if(y < cursorBoundary[1][1])
            {
                y++;
            }
            break;

        //if a number was entered write it into the current sudoku field if allowed
        case '0' ... '9':
            input -= '0';
            row = (x/2)-cursorBoundary[0][0]+2;
            line = y-cursorBoundary[0][1];
            if(getBlockFromCursor(row,line) != -1 && getRowFromCursor(row,line) != -1 && getLineFromCursor(row,line) != -1 && sudoku.a_originalSudoku[getBlockFromCursor(row,line)][getRowFromCursor(row,line)][getLineFromCursor(row,line)] == 0)
            {
                sudoku.a_sudoku[getBlockFromCursor(row,line)][getRowFromCursor(row,line)][getLineFromCursor(row,line)] = input;
                sudoku.moves++;
            }
            break;

        //if the h-key was pressed, activate the help for the current editable field the cursor is standing on
        case 'h':
            row = (x/2)-cursorBoundary[0][0]+2;
            line = y-cursorBoundary[0][1];

            solveSudoku(sudoku.a_validSudoku);
            if(getBlockFromCursor(row,line) != -1 && getRowFromCursor(row,line) != -1 && getLineFromCursor(row,line) != -1 && sudoku.a_originalSudoku[getBlockFromCursor(row,line)][getRowFromCursor(row,line)][getLineFromCursor(row,line)] == 0)
            {
                int blockFromCurser = getBlockFromCursor(row, line);
                int rowFromCurser = getRowFromCursor(row,line);
                int lineFromCurser = getLineFromCursor(row, line);

                sudoku.a_sudoku[blockFromCurser][rowFromCurser][lineFromCurser] = sudoku.a_validSudoku[blockFromCurser][rowFromCurser][lineFromCurser];
                sudoku.moves++;
            }
            break;

        //end the game when e was pressed
        case 'e':
            sudoku.navigation = 1;
            return sudoku;
            break;

        //return to the menu
        case 'm':
            sudoku.navigation = -1;
            return sudoku;
            break;

        //if the button s was pressed then save the current state and end the game
        case 's':
            sudoku.timeEnd = time(NULL);
            getAbsoluteFilePath(path, "files", "saveFile.sudoku");
            writeSudokuToFile(path, sudoku);
            getAbsoluteFilePath(path, "files", "saveOriginalState.sudoku");
            for (i = 0; i < 9; i++)//blocks
            {
                for (j = 0; j < 3; j++)//block lines
                {
                    for (k = 0; k < 3; k++)//block row
                    {
                        sudoku.a_sudoku[i][j][k] = sudoku.a_originalSudoku[i][j][k];
                    }
                }
            }
            writeSudokuToFile(path, sudoku);
            sudoku.navigation = 1;
            return sudoku;
            break;
        default:
            break;
        }
    }

    sudoku.error = 2;
    return sudoku;
}
