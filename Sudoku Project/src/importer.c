//  Created by Robin Winkler on 21.04.18.
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../include/constants.h"
#include "../include/converter.h"
#include "../include/importer.h"

#define MAXCHARACTERS 255

//http://www.zentut.com/c-tutorial/c-read-text-file/
struct s_sudoku getSudokuFromFile(char filename[]){
    FILE *fp;
    char str[MAXCHARACTERS];
    struct s_sudoku sudoku;
    sudoku.error = 0;
    int i, j = 0;

    fp = fopen(filename, "r");
    if (fp == NULL){
        //printf("Could not open file %s",filename);
        sudoku.error = 1;
        return sudoku;
    }

    i=0;
    while (fgets(str, MAXCHARACTERS, fp) != NULL){
        for(j=0; j<(strlen(str)); j++){
            if(str[j] != '\n' && (int)str[j] != 13){
                sudoku.a_sudoku[getBlockFromLineAndRow(i,j)][getBlockLineFromLine(j)][getBlockRowFromRow(i)] = (int)str[j] - '0'; //minus 48 da die numbern im ascii code bei 48 bzw bei dem zeichen 0 anfangen
                sudoku.a_originalSudoku[getBlockFromLineAndRow(i,j)][getBlockLineFromLine(j)][getBlockRowFromRow(i)] = (int)str[j] - '0'; //doppelt, da auch die Werte unter der &a_originalSudoku Referenz zu finden sind und nicht auf &a_sudoku referenzieren
                //printf("char: %c, int: %i", str[j]-'0', str[j]-'0');
                //getchar();
                //printf("i: %i, j: %i\n", i, j);
                //printf("Test: %c, Block: %i, Spalte: %i, Zeile: %i\n", str[j], getBlockFromLineAndRow(i,j), getBlockLineFromLine(j), getBlockRowFromRow(i));
                //getchar();
            }
        }
        i++;
        //printf("%s", str);
        //printf("Lenght: %i\n", strlen(str));
    }
    fclose(fp);

    //Debug
    //printf("%i", sudoku.a_sudoku[1][0][0]);
    //getchar();

    return sudoku;
}

void getAbsoluteFilePath(char *buffer, char a_subDir[32], char a_fileName[32])
{
    int i = 0;
    for(;i<=sizeof(buffer);i++)
    {
        buffer[i] = '\0';
    }
    #if defined(PLATFORM) && PLATFORM == 1
        //https://cboard.cprogramming.com/c-programming/88690-path-file-relative-program.html
        char path[MAX_PATH];
        GetCurrentDirectory(sizeof(path), path);
    #elif defined(PLATFORM) && PLATFORM == 2
        char path[1024];
        getcwd(path, sizeof(path));
    #endif

    strcat(buffer, path);
    strcat(buffer, DS);
    strcat(buffer, a_subDir);
    strcat(buffer, DS);
    strcat(buffer, a_fileName);
    //printf("path: %s\n", buffer);
    //getchar();
}

int getPathSize()
{
    #if defined(MAX_PATH)
        int path = MAX_PATH;
    #else
        int path = 1024;
    #endif // defined
    return path+sizeof(DS)+sizeof(DS)+sizeof(".sudoku")+64;
}
