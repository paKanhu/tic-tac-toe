/*
Tic Tac Toe

Copyright (C) 2014 Prasannajit Acharya - Kanhu

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>

int startTheGame();
void displayTheOption();
void displayTheScores();
void displayTheCredit();
int startTheGame();
void displayTheBoard();
int checkThePlace(int);
int getThePosition();
int isTwiceOccured(char);
int crossPlace();
int midPlace();
void playerMove(int, char);
int winCheck();
void createUserDataFile();
void initializeBoard();

char base[3][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};
char const * FILEPATH = "tic-tac-toe.txt";  // Game data will be stored here

int main()
{
    char choice[3];

    system("title TIC TAC TOE");

    while(1)
    {
        system("cls");
        printf("\n            ===============\n");
        printf("            | TIC TAC TOE |\n");
        printf("            ===============\n");
        printf("            |             |\n");
        printf("            |  1. Start   |\n");
        printf("            |  2. Option  |\n");
        printf("            |  3. Scores  |\n");
        printf("            |  4. Credit  |\n");
        printf("            |  5. Exit    |\n");
        printf("            ===============\n\n");
        printf("Enter your choice: ");
        fgets(choice, sizeof(choice), stdin);

        switch(atoi(choice))
        {
            case 1:
                startTheGame();
                break;
            case 2:
                displayTheOption();
                break;
            case 3:
                displayTheScores();
                break;
            case 4:
                displayTheCredit();
                break;
            case 5:
                return(0);
            default:
                printf("Invalid choice. Try again...\n\n");
                system("pause");
        }
    }
    return 0;
}

int startTheGame()
{
    char choice[3], ch;
    int index, easyIndex, hardIndex;
    int position;
    int isFirstTurn;
    int i, j;
    int isWin;
    int playerEasyWinScore = 0;
    int playerEasyLostScore = 0;
    int playerEasyTieScore = 0;
    int playerHardWinScore = 0;
    int playerHardLostScore = 0;
    int playerHardTieScore = 0;
    int gameplay;   // 0 - Easy gameplay, 1 - Hard gameplay
    int isSavedEasy, isSavedHard;
    char easy[3][3], hard[3][3];
    FILE *userFile = fopen(FILEPATH, "r");

    if(userFile == NULL)
    {
        createUserDataFile();
        userFile = fopen(FILEPATH, "r");
    }

    fscanf(userFile, "%d", &gameplay);
    fscanf(userFile, "%d %d %d", &playerEasyWinScore, &playerEasyLostScore, &playerEasyTieScore);
    fscanf(userFile, "%d %d %d", &playerHardWinScore, &playerHardLostScore, &playerHardTieScore);
    fscanf(userFile, "%d %d", &isSavedEasy, &isSavedHard);

    // Check for any saved game
    if(isSavedEasy)
    {
        fscanf(userFile, "%d", &easyIndex);
        for(i = 0; i < 3; i++)
        {
            for(j = 0; j < 3; j++)
            {
                ch = getc(userFile);
                if(ch != '\n')
                    easy[i][j] = ch;
                ch = getc(userFile);
                if(ch != '\n')
                    easy[i][j] = ch;
            }
        }
    }

    if(isSavedHard)
    {
        fscanf(userFile, "%d", &hardIndex);
        for(i = 0; i < 3; i++)
        {
            for(j = 0; j < 3; j++)
            {
                ch = getc(userFile);
                if(ch != '\n')
                    hard[i][j] = ch;
                ch = getc(userFile);
                if(ch != '\n')
                    hard[i][j] = ch;
            }
        }
    }

    fclose(userFile);

    if( (gameplay && isSavedHard) || (!gameplay && isSavedEasy) )
    {
        system("cls");
        printf("You have a saved game.\n");
        printf("1. Continue\n");
        printf("2. New Game\n");
        printf("New Game will overwrite the saved game of current gameplay.\n");
        printf("Enter your choice:(Default - Continue) ");
        fgets(choice, sizeof(choice), stdin);

        if(gameplay)
        {
            isSavedHard = 0;
            userFile = fopen(FILEPATH, "r+");
            fprintf(userFile, "%d\n", gameplay);
            fprintf(userFile, "%d %d %d\n", playerEasyWinScore, playerEasyLostScore, playerEasyTieScore);
            fprintf(userFile, "%d %d %d\n", playerHardWinScore, playerHardLostScore, playerHardTieScore);
            fprintf(userFile, "%d %d\n", isSavedEasy, isSavedHard);
            if(isSavedEasy)
            {
                fprintf(userFile, "%d\n", easyIndex);
                for(i = 0; i < 3; i++)
                    for(j = 0; j < 3; j++)
                        fprintf(userFile, "%c\n", easy[i][j]);
            }
            fclose(userFile);
        }
        else
        {
            isSavedEasy = 0;
            userFile = fopen(FILEPATH, "r+");
            fprintf(userFile, "%d\n", gameplay);
            fprintf(userFile, "%d %d %d\n", playerEasyWinScore, playerEasyLostScore, playerEasyTieScore);
            fprintf(userFile, "%d %d %d\n", playerHardWinScore, playerHardLostScore, playerHardTieScore);
            fprintf(userFile, "%d %d\n", isSavedEasy, isSavedHard);
            if(isSavedHard)
            {
                fprintf(userFile, "%d\n", hardIndex);
                for(i = 0; i < 3; i++)
                    for(j = 0; j < 3; j++)
                        fprintf(userFile, "%c\n", hard[i][j]);
            }
            fclose(userFile);
        }

        if( (atoi(choice)) == 2)
        {
            initializeBoard();
            index = 0;
        }
        else
        {
            if(gameplay && isSavedHard)
            {
                index = hardIndex;
                for(i = 0; i < 3; i++)
                    for(j = 0; j < 3; j++)
                        base[i][j] = hard[i][j];
            }
            else
            {
                index = easyIndex;
                for(i = 0; i < 3; i++)
                    for(j = 0; j < 3; j++)
                        base[i][j] = easy[i][j];
            }
        }
    }
    else
    {
        initializeBoard();
        index = 0;
    }

    // Start the game
    for(isFirstTurn = 1; index < 9; index++)
    {
        if(index % 2 == 0)
        {
            while(1)
            {
                system("cls");
                displayTheBoard();

                if (!isFirstTurn)
                {
                    printf("AI move: %d\n", position);
                }
                else
                {
                    isFirstTurn = 0;
                }

                printf("Enter the position at which you want to put X: (0: Menu) ");
                fgets(choice, sizeof(choice), stdin);

                position = atoi(choice);

                switch(position)
                {
                    case 0:
                        system("cls");
                        printf("\nDo you want to save and quit? (Default - Resume)\n");
                        printf("1. Resume\n2. Save and Quit\n3. Quit without saving\n\n");
                        printf("Enter your choice: ");
                        fgets(choice, sizeof(choice), stdin);

                        switch(atoi(choice))
                        {
                            case 1:
                                continue;
                                break;
                            case 2:
                                if(gameplay)
                                    isSavedHard = 1;
                                else
                                    isSavedEasy = 1;

                                userFile = fopen(FILEPATH, "r+");
                                fprintf(userFile, "%d\n", gameplay);
                                fprintf(userFile, "%d %d %d\n", playerEasyWinScore, playerEasyLostScore, playerEasyTieScore);
                                fprintf(userFile, "%d %d %d\n", playerHardWinScore, playerHardLostScore, playerHardTieScore);
                                fprintf(userFile, "%d %d\n", isSavedEasy, isSavedHard);

                                if(gameplay)
                                {
                                    if(isSavedEasy == 1)
                                    {
                                        fprintf(userFile, "%d\n", easyIndex);
                                        for(i = 0; i < 3; i++)
                                            for(j = 0; j < 3; j++)
                                                fprintf(userFile, "%c\n",easy[i][j]);
                                    }
                                    fprintf(userFile, "%d\n", index);
                                    for(i = 0; i < 3; i++)
                                        for(j = 0; j < 3; j++)
                                            fprintf(userFile, "%c\n",base[i][j]);
                                }
                                else
                                {
                                    fprintf(userFile, "%d\n", index);
                                    for(i = 0; i < 3; i++)
                                        for(j = 0; j < 3; j++)
                                            fprintf(userFile, "%c\n",base[i][j]);
                                    if(isSavedHard == 1)
                                    {
                                        fprintf(userFile, "%d\n", hardIndex);
                                        for(i = 0; i < 3; i++)
                                            for(j = 0; j < 3; j++)
                                                fprintf(userFile, "%c\n",hard[i][j]);
                                    }
                                }
                                fclose(userFile);
                                return(0);
                                break;
                            case 3:
                                return(0);
                                break;
                            default:
                                continue;
                        }
                        break;
                    case 1:
                    //Fall through
                    case 2:
                    //Fall through
                    case 3:
                    //Fall through
                    case 4:
                    //Fall through
                    case 5:
                    //Fall through
                    case 6:
                    //Fall through
                    case 7:
                    //Fall through
                    case 8:
                    //Fall through
                    case 9:
                        if(checkThePlace(position))
                            break;
                        else
                        {
                            printf("\nERROR:Position is not available.\n");
                            printf("Try again.\n\n");
                            system("pause");
                            continue;
                        }
                        break;
                    default:
                        printf("\nERROR:Position is not valid.\n");
                        printf("Try again.\n\n");
                        system("pause");
                        continue;
                }
                break;
            }
            playerMove(position, 'X');  // User's move
        }
        else
        {
            position = getThePosition();
            playerMove(position, 'O');  // AI's move
        }

        system("cls");
        displayTheBoard();

        isWin = winCheck();     // Check the win conditions

        if(isWin)
        {
            if(index % 2 == 0)  // User wins
            {
                printf("               == You won ==\n\n");
                if(gameplay)
                    playerHardWinScore++;
                else
                    playerEasyWinScore++;
            }
            else    // AI wins
            {
                printf("               = You lost! =\n\n");
                if(gameplay)
                    playerHardLostScore++;
                else
                    playerEasyLostScore++;
            }
            break;
        }
    }

    if(!isWin)
    {
        printf("               ==== TIE ====\n\n");
        if(gameplay)
            playerHardTieScore++;
        else
            playerEasyTieScore++;
    }

    userFile = fopen(FILEPATH, "r+");
    fprintf(userFile, "%d\n", gameplay);
    fprintf(userFile, "%d %d %d\n", playerEasyWinScore, playerEasyLostScore, playerEasyTieScore);
    fprintf(userFile, "%d %d %d\n", playerHardWinScore, playerHardLostScore, playerHardTieScore);
    fclose(userFile);

    printf("\nEnter 1 to retry, or press any other key to go to Main Menu: ");
    fgets(choice, sizeof(choice), stdin);
    if(atoi(choice) == 1)
        startTheGame();
    return(0);
}


/**
 * To display the game board
 */
void displayTheBoard()
{
    int gameplay;

    FILE *userFile = fopen(FILEPATH, "r");
    if(userFile == NULL)
    {
        createUserDataFile();
        userFile = fopen(FILEPATH, "r");
    }
    fscanf(userFile, "%d", &gameplay);
    fclose(userFile);

    printf("\n               TIC TAC TOE \n");
    printf("             ===============\n");
    if(gameplay)
        printf("             ===== Hard ====\n");
    else
        printf("             ===== Easy ====\n");
    printf("             ===============\n\n");
    printf("               %c | %c | %c \n", base[0][0], base[0][1], base[0][2]);   // First row
    printf("              ------------\n");
    printf("               %c | %c | %c \n", base[1][0], base[1][1], base[1][2]);   // Second row
    printf("              ------------\n");
    printf("               %c | %c | %c \n", base[2][0], base[2][1], base[2][2]);   // Third row
    printf("\n\n\n");
}

/**
 * To check if a position is available or not
 * @param  position position in the array to be checked if it is available or not
 * @return 0 for not available, 1 if the place is available/free
 */
int checkThePlace(int position)
{
    switch(position)
    {
        case 1:
            if((base[0][0] == 'X') || (base[0][0] == 'O'))
                return 0;
            break;
        case 2:
            if((base[0][1] == 'X') || (base[0][1] == 'O'))
                return 0;
            break;
        case 3:
            if((base[0][2] == 'X') || (base[0][2] == 'O'))
                return 0;
            break;
        case 4:
            if((base[1][0] == 'X') || (base[1][0] == 'O'))
                return 0;
            break;
        case 5:
            if((base[1][1] == 'X') || (base[1][1] == 'O'))
                return 0;
            break;
        case 6:
            if((base[1][2] == 'X') || (base[1][2] == 'O'))
                return 0;
            break;
        case 7:
            if((base[2][0] == 'X') || (base[2][0] == 'O'))
                return 0;
            break;
        case 8:
            if((base[2][1] == 'X') || (base[2][1] == 'O'))
                return 0;
            break;
        case 9:
            if((base[2][2] == 'X') || (base[2][2] == 'O'))
                return 0;
            break;
        default:
            return 0;
    }
    return 1;
}

/**
 * To get the position for computer player
 * @return position where computer player will place 'O'
 */
int getThePosition()
{
    int position;
    int gameplay;

    FILE *userFile = fopen(FILEPATH, "r");
    if(userFile == NULL)
    {
        createUserDataFile();
        userFile = fopen(FILEPATH, "r");
    }
    fscanf(userFile, "%d", &gameplay);
    fclose(userFile);

    // This sequence of execution is important for proper AI move
    // Below steps are for AI's move position

    // Check for the **win** position
    position = isTwiceOccured('O');
    if(position)
        return position;

    // Check for the lose position to prevent it
    if(!gameplay)   // In ** easy ** mode AI may do sily mistake
    {
        if((rand() % 10) != 0)
        {
            position = isTwiceOccured('X');
            if(position)
                return position;
        }
    }
    else
    {
        position = isTwiceOccured('X');
        if(position)
            return position;
    }


    // Just for the centre position
    if(checkThePlace(5))
        return 5;

    // The only difference between ** easy ** and ** hard ** mode
    if(gameplay)            // If game play is hard
    {
        position = midPlace();
        if(position)
            return position;
    }

    // Random position, if all of the above conditions are not satisfied
    if((rand() % 2) == 0)
    {
        position = crossPlace();
        return position;
    }
    else
    {
        while(1)
        {
            position = rand() % 10;
            if(checkThePlace(position))
                return position;
        }
    }

}

/**
 * To check if there is two target items in any row, column and diagonal
 * @param  target X or O to be checked
 * @return the position if there is two target items in any row, column and diagonal otherwise 0
 */
int isTwiceOccured(char target)
{
    int position;
    int i, j;
    int count;

    // Row Check
    for(i = 0; i < 3; i++)
    {
        count = 0;

        for(j = 0; j < 3; j++)
        {
            if(base[i][j] == target)
                count++;

            else
                position = base[i][j] - 48;
        }

        if(count == 2)
            if(checkThePlace(position))
                return position;
    }

    // Column Check
    for(j = 0; j < 3; j++)
    {
        count = 0;

        for(i = 0; i < 3; i++)
        {
            if(base[i][j] == target)
                count++;
            else
                position = base[i][j] - 48;
        }

        if(count == 2)
            if(checkThePlace(position))
                return position;
    }

    // 1st Diagonal Check
    count = 0;

    for(i = 0; i < 3; i++)
    {
        if(base[i][i] == target)
            count++;
        else
            position = base[i][i] - 48;
    }

    if(count == 2)
        if(checkThePlace(position))
            return position;

    // 2nd Diagonal Check
    count = 0;

    if(base[0][2] == target)
        count++;
    else
        position = base[0][2] - 48;

    if(base[1][1] == target)
        count++;
    else
        position = base[1][1] - 48;

    if(base[2][0] == target)
        count++;
    else
        position = base[2][0] - 48;

    if(count == 2)
        if(checkThePlace(position))
            return position;

    // No twos are same
    return 0;
}

/**
 * To place the O in the opposite side of diagonal of X
 * @return the position where O will be placed
 */
int crossPlace()
{
    if(base[0][0] == 'X')
        if(checkThePlace(9))
            return 9;

    if(base[0][2] == 'X')
        if(checkThePlace(7))
            return 7;

    if(base[2][0] == 'X')
        if(checkThePlace(3))
            return 3;

    if(base[2][2] == 'X')
        if(checkThePlace(1))
            return 1;

    if(checkThePlace(1))
        return 1;

    if(checkThePlace(3))
        return 3;

    if(checkThePlace(7))
        return 7;

    if(checkThePlace(9))
        return 9;
}

/**
 * To place the O in the middle position of row or column if any diagonal has 2 X at each end
 * @return      the position where O will be placed
 */
int midPlace()
{
    if(base[0][0] == base[2][2])
        if(base[0][0] == 'X')
        {
            if(checkThePlace(2))
                return 2;

            if(checkThePlace(4))
                return 4;

            if(checkThePlace(6))
                return 6;

            if(checkThePlace(8))
                return 8;
        }

    if(base[0][2] == base[2][0])
        if(base[0][2] == 'X')
        {
            if(checkThePlace(2))
                return 2;

            if(checkThePlace(4))
                return 4;

            if(checkThePlace(6))
                return 6;

            if(checkThePlace(8))
                return 8;
        }

    return 0;
}

/**
 * To place the target item in the array according to the position
 * @param position position where target will be placed
 * @param target   X or O, what will be placed at the position
 */
void playerMove(int position, char target)
{
    switch(position)
    {
        case 1:
            base[0][0] = target;
            break;
        case 2:
            base[0][1] = target;
            break;
        case 3:
            base[0][2] = target;
            break;
        case 4:
            base[1][0] = target;
            break;
        case 5:
            base[1][1] = target;
            break;
        case 6:
            base[1][2] = target;
            break;
        case 7:
            base[2][0] = target;
            break;
        case 8:
            base[2][1] = target;
            break;
        case 9:
            base[2][2] = target;
            break;
    }
}

/**
 * To check the win conditions
 * @return      1 if someone wins, 0 otherwise
 */
int winCheck()
{
    if(base[0][0] == base[0][1])
        if(base[0][0] ==  base[0][2])
            return 1;

    if(base[1][0] == base[1][1])
        if(base[1][0] ==  base[1][2])
            return 1;

    if(base[2][0] == base[2][1])
        if(base[2][0] ==  base[2][2])
            return 1;

    if(base[0][0] == base[1][0])
        if(base[0][0] ==  base[2][0])
            return 1;

    if(base[0][1] == base[1][1])
        if(base[0][1] ==  base[2][1])
            return 1;

    if(base[0][2] == base[1][2])
        if(base[0][2] ==  base[2][2])
            return 1;

    if(base[0][0] == base[1][1])
        if(base[0][0] ==  base[2][2])
            return 1;

    if(base[0][2] == base[1][1])
        if(base[0][2] ==  base[2][0])
            return 1;

    return 0;
}

void displayTheOption()
{
    int gameplay;   // 0 - Easy gameplay, 1 - Hard gameplay
    char choice[3];
    FILE *userFile = fopen(FILEPATH, "r+");

    if(userFile == NULL)
    {
        createUserDataFile();
        userFile = fopen(FILEPATH, "r+");
    }

    system("cls");
    printf("\n\n\n               === Option ==");
    printf("\n               |  0. Easy  |");
    printf("\n               |  1. Hard  |");
    printf("\n               =============\n\n");
    printf("Enter your gameplay difficulty (default: Easy): ");
    fgets(choice, sizeof(choice), stdin);
    gameplay = atoi(choice);
    switch(gameplay)
    {
        case 1:
            gameplay = 1;
            break;
        default:
            gameplay = 0;
    }

    fprintf(userFile, "%d\n", gameplay);
    fclose(userFile);
}

void displayTheScores()
{
    int win, lost, tie, gameplay;
    FILE *userFile = fopen(FILEPATH, "r");

    system("cls");

    if(userFile == NULL)
    {
        createUserDataFile();
        userFile = fopen(FILEPATH, "r");
    }

    printf("\n\n\n               === Score ===");

    fscanf(userFile, "%d", &gameplay);
    fscanf(userFile, "%d %d %d", &win, &lost, &tie);
    printf("\n               *** Easy ***");
    printf("\n               Win: %d", win);
    printf("\n               Lost: %d", lost);
    printf("\n               Tie: %d", tie);

    fscanf(userFile, "%d %d %d", &win, &lost, &tie);
    printf("\n               *** Hard ***");
    printf("\n               Win: %d", win);
    printf("\n               Lost: %d", lost);
    printf("\n               Tie: %d", tie);
    printf("\n               =============\n\n");
    fclose(userFile);
    system("pause");
}

void displayTheCredit()
{
    system("cls");
    printf("\n\n\n               === Credit ==");
    printf("\n               *************");
    printf("\n               *github.com/*");
    printf("\n               ** paKanhu **");
    printf("\n               *************");
    printf("\n               *** GPLv3 ***");
    printf("\n               *************\n\n");
    system("pause");
}

void createUserDataFile()
{
    FILE *userFile = fopen(FILEPATH, "w");
    if(userFile == NULL)
    {
        printf("\n\n\nCannot create score file.\nTerminating program.\n\n");
        system("pause");
        exit(2);
    }
    fprintf(userFile, "0\n0 0 0\n0 0 0\n0 0\n");
    fclose(userFile);
    system("attrib +h tic-tac-toe.txt");
}

void initializeBoard()
{
    int i, j;
    int index = 49; // ASCII char '1' is 49 in decimal
    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
            base[i][j] = index++;
}
