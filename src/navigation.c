#include <headers.h>

char *current_user;
void startApp()
{
    while (1)
    {
        system("cls");
        gotoxy(10, 9);
        printf("1. Admin Login");
        gotoxy(10, 11);
        printf("2. Admin Sign up");
        gotoxy(10, 13);
        printf("3. Forgot Password");
        gotoxy(10, 15);
        printf("q. Exit Application");
        gotoxy(10, 17);
        printf("Enter your choice: ");
        switch (getch())
        {
        case '1':
            adminLogin(&current_user);
            // mainMenu();
            break;
        case '2':
            adminSignup();
            break;
        case '3':
            forgotPassword();
            break;
        case 'q':
        case 'Q':
            creditAndClose();
            break;
        default:
            gotoxy(10, 19);
            printf("\aWrong Entry!! Please re-enter correct option.");
            getch(); //holds the screen until a key is pressed
        }
    }
}

void mainMenu()
{
    while (1)
    {
        system("cls");
        gotoxy(10, 3);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        gotoxy(10, 5);
        printf("\xDB\xDB\xDB\xDB\xB2 1. Books   ");
        gotoxy(10, 7);
        printf("\xDB\xDB\xDB\xDB\xB2 2. Members");
        gotoxy(10, 9);
        printf("\xDB\xDB\xDB\xDB\xB2 3. My Account");
        gotoxy(10, 11);
        printf("\xDB\xDB\xDB\xDB\xB2 s. Sign out");
        gotoxy(10, 13);
        printf("\xDB\xDB\xDB\xDB\xB2 q. Close Application");
        gotoxy(10, 19);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        gotoxy(10, 21);
        printf("Enter your choice: ");
        switch (getch())
        {
        case '1':
            booksMenu();
            break;
        case '2':
            membersMenu();
            break;
        case '3':
            myAccountMenu();
            break;
        case 's':
        case 'S':
            adminSignout();
            break;
        case 'q':
        case 'Q':
            creditAndClose();
            break;
        default:
            gotoxy(10, 23);
            printf("\aWrong Entry!! Please re-enter correct option.");
            getch(); //holds the screen until a key is pressed
        }
    }
}

void booksMenu()
{
    while (1)
    {
        system("cls");
        gotoxy(10, 3);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 BOOKS \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        gotoxy(10, 5);
        printf("\xDB\xDB\xDB\xDB\xB2 1. Add Book   ");
        gotoxy(10, 7);
        printf("\xDB\xDB\xDB\xDB\xB2 2. Issue Book");
        gotoxy(10, 9);
        printf("\xDB\xDB\xDB\xDB\xB2 3. Delete Book");
        gotoxy(10, 11);
        printf("\xDB\xDB\xDB\xDB\xB2 4. Search Book");
        gotoxy(10, 13);
        printf("\xDB\xDB\xDB\xDB\xB2 5. View Book List");
        gotoxy(10, 15);
        printf("\xDB\xDB\xDB\xDB\xB2 6. Edit Book Record ");
        gotoxy(10, 17);
        printf("\xDB\xDB\xDB\xDB\xB2 r. Return to Main Menu ");
        gotoxy(10, 19);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        gotoxy(10, 21);
        printf("Enter your choice: ");
        switch (getch())
        {
        case '1':
            addBook();
            break;
        case '2':
            issueBook();
            break;
        case '3':
            deleteBook();
            break;
        case '4':
            searchBook();
            break;
        case '5':
            viewBooks();
            break;
        case '6':
            editBook();
            break;
        case 'r':
        case 'R':
            mainMenu();
        default:
            gotoxy(10, 23);
            printf("\aWrong Entry!! Please re-enter correct option.");
            getch(); //holds the screen until a key is pressed
        }
    }
}

void membersMenu()
{
    while (1)
    {
        system("cls");
        gotoxy(10, 3);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MEMBERS \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        gotoxy(10, 5);
        printf("\xDB\xDB\xDB\xDB\xB2 1. Add Member   ");
        gotoxy(10, 7);
        printf("\xDB\xDB\xDB\xDB\xB2 2. Delete Member");
        gotoxy(10, 9);
        printf("\xDB\xDB\xDB\xDB\xB2 3. Search Member");
        gotoxy(10, 11);
        printf("\xDB\xDB\xDB\xDB\xB2 4. View Members List");
        gotoxy(10, 13);
        printf("\xDB\xDB\xDB\xDB\xB2 5. Edit Member Record");
        gotoxy(10, 15);
        printf("\xDB\xDB\xDB\xDB\xB2 r. Return to Main Menu ");
        gotoxy(10, 19);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        gotoxy(10, 21);
        printf("Enter your choice:");
        switch (getch())
        {
        case '1':
            addMember();
            break;
        case '2':
            deleteMember();
            break;
        case '3':
            searchMember();
            break;
        case '4':
            viewMembers();
            break;
        case '5':
            editMember();
            break;
        case 'r':
        case 'R':
            mainMenu();
        default:
            gotoxy(10, 23);
            printf("\aWrong Entry!! Please re-enter correct option.");
            getch(); //holds the screen until a key is pressed
        }
    }
}

void myAccountMenu()
{
    while (1)
    {
        system("cls");
        gotoxy(10, 3);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MY ACCOUNT \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        gotoxy(10, 5);
        // printf("\xDB\xDB\xDB\xDB\xB2 1. Edit Details   ");
        // gotoxy(10,7);
        printf("\xDB\xDB\xDB\xDB\xB2 1. Change Password");
        gotoxy(10, 7);
        printf("\xDB\xDB\xDB\xDB\xB2 r. Return to Main Menu ");
        gotoxy(10, 19);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        gotoxy(10, 21);
        printf("Enter your choice:");
        switch (getch())
        {
        case '1':
            //     editAccountDetails();
            //     break;
            // case '2':
            changePassword(current_user, 0);
            // gotoxy(10,13);
            // printf("press any key to continue....");
            // getch();
            break;
        case 'r':
        case 'R':
            mainMenu();
        default:
            gotoxy(10, 23);
            printf("\aWrong Entry!!Please re-enter correct option");
            getch(); //holds the screen until a key is pressed
        }
    }
}
