
//  Created by Robin Winkler on 21.04.18.
#include <stdio.h>
#include <string.h>
#include "../include/constants.h"
#include "../include/converter.h"
#include "../include/exporter.h"

#define MAXCHARACTERS 255

//http://www.zentut.com/c-tutorial/c-read-text-file/
struct s_sudoku writeSudokuToFile(struct s_sudoku sudoku){
    FILE *fp;
    printf("Lade Datei!");
    fp = fopen("files\\save.sudoku", "w");
    if(fp == NULL)
    {
        printf("Datei wurde nicht gefunden! Moment...");
        freopen("files\\save.sudoku", "w", fp);
    }
    printf("Hab jetzt die Datei!");

    int i, j;
    /*
    for (i = 0; i < 9; i++)
    {
        arrayIndex = 0;
        for (j = 0; j < 9; j++)
        {
            for (k = 0; k < 3; k++)
            {
                fprintf(fp, (sudoku.a_sudoku[j][k][i]) + '0');
            }
        }
    }
    */
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            printf("Schreibe: %c", (sudoku.a_sudoku[getBlockFromLineAndRow(i, j)][getBlockRowFromRow(j)][getBlockLineFromLine(i)]) + '0');
            fprintf(fp, "%c", ((sudoku.a_sudoku[getBlockFromLineAndRow(i, j)][getBlockRowFromRow(j)][getBlockLineFromLine(i)]) + '0'));
        }
        fprintf(fp, "\n");
    }
}
