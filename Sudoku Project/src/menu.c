//  Created by Robin Winkler on 10.04.18.
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "../include/constants.h"
#include "../include/gameplay.h"
#include "../include/menu.h"
#include "../include/consolePrinter.h"
#include "../include/validator.h"
#include "../include/importer.h"
#include "../include/input.h"

int mainMenu(int status)
{
    char selection = '\0';

    CLS;

    if (status == 0) {
        printf("Falsche Eingabe entdeckt!\n");
    }

    printf("Hauptmenü:\n");
    printf("Bitte wählen:\n");
    printf("n - neues Spiel\n");
    printf("e - Spiel beenden\n");
    printf("Eingabe: ");
    selection = getInput();

    return validateMenuInput(selection);
}

struct s_sudoku newGame()
{
    char selection = '\0';
    struct s_sudoku sudoku;
    #if defined(PLATFORM) && PLATFORM == 1
        //https://cboard.cprogramming.com/c-programming/88690-path-file-relative-program.html
        char path[MAX_PATH];
        GetCurrentDirectory(sizeof(path), path);
    #elif defined(PLATFORM) && PLATFORM == 2
        char path[1024];
        getcwd(path, sizeof(path));
    #endif
    //printf("path: %s", path);

    printf("Levelauswahl:\n");
    printf("Bitte wählen:\n");
    printf("1 - leichtes Level spielen\n");
    printf("2 - mittleres Level spielen\n");
    printf("3 - schweres Level spielen\n");
    printf("z - Zurück zum Hauptmenü\n");
    printf("Eingabe: ");
    selection = getInput();

    CLS;

    //TODO: Errorhandling vom sudoku

    switch (selection) {
        case '1':
            printf("leichtes Level ausgewählt.\n");
            sudoku = getSudokuFromFile(strcat(path, "\\files\\relax.sudoku"));
            break;
        case '2':
            printf("mittleres Level ausgewählt.\n");
            sudoku = getSudokuFromFile(strcat(path, "\\files\\genius.sudoku"));
            break;
        case '3':
            printf("schweres Level ausgewählt.\n");
            sudoku = getSudokuFromFile(strcat(path, "\\files\\mastermind.sudoku"));
            break;
        case '0':
            //return 1;
            //EASTER EGG
            CLS;
            printf("Geheimes Easter Egg gefunden!\n");
            sudoku = getSudokuFromFile(strcat(path, "\\files\\easterEgg.sudoku"));
            getchar();
            break;
        case 'z':
            sudoku.navigation = -1;
            return sudoku;
            break;
        default:
            sudoku.navigation = 0;
            return sudoku;
            break;
    }

    return gameRoutine(sudoku);
}
