// #include <variables.h>
#include <headers.h>
COORD coord = {0, 0};
void gotoxy(int x, int y)
{
    coord.X = x;
    coord.Y = y; // X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void returnfunc()
{
    printf(" \nPress ENTER to return to main menu");
    if (getch() == 13) //allow only use of enter
        mainMenu();
}

void creditAndClose()
{
    system("cls");
    gotoxy(10, 3);
    printf("Author: Mukund Shah");
    gotoxy(10, 5);
    printf("GitHub: mukundshah");
    gotoxy(10, 10);
    printf("CSC 110 - C Programming");
    gotoxy(10, 11);
    printf("Department of CSIT,");
    gotoxy(10, 12);
    printf("Amrit Science Campus, ");
    gotoxy(10, 13);
    printf("IOST, Tribhuvan University, Nepal");
    gotoxy(10, 17);
    printf("Exiting in 3 second");
    for (size_t i = 0; i < 3; i++)
    {
        Sleep(1000);
        printf("...");
    }
    system("cls");
    exit(0);
}

void getPassword(char *pwd_dest)
{
    char temp_passP[25];
    int i = 0;
    while (1)
    {
        temp_passP[i] = getch();
        if (temp_passP[i] == 13)
            break;
        else if (temp_passP[i] == 8)
        {
            if (i != 0)
            {
                printf("\b \b");
                i--;
            }
            else
                printf("\a");
        }
        else
        {
            printf("*");
            *(pwd_dest + i) = temp_passP[i];
            i++;
        }
        *(pwd_dest + i) = '\0';
    }
}
