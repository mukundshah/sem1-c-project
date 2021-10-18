#include <headers.h>
int user_allowed = 0;
static int checkUser(void *NotUsed, int argc, char **argv, char **azColName)
{
    for (size_t i = 0; i < argc; i++)
        user_allowed = 1;
    return 0;
}

void adminLogin(char **current_user)
{
    char username[50], password[16];
    char *hashed_password;
    char sql[200];
    system("cls");
    gotoxy(10, 10);
    printf("Username: ");
    gotoxy(10, 11);
    printf("Password: ");
    gotoxy(20, 10);
    scanf("%s", username);
    gotoxy(20, 11);
    getPassword(password);
    sprintf(sql, "SELECT username, password from admin WHERE username = '%s' AND password = '%s'", username, password);
    exec_sql_with_callback(sql, checkUser);
    while (!user_allowed)
    {
        system("cls");
        gotoxy(10, 10);
        printf("Username: ");
        gotoxy(10, 11);
        printf("Password: ");
        gotoxy(10, 15);
        printf("Invalid username or password");
        gotoxy(20, 10);
        scanf("%s", username);
        gotoxy(20, 11);
        getPassword(password);
        sprintf(sql, "SELECT username, password from admin WHERE username = '%s' AND password = '%s'", username, password);
        exec_sql_with_callback(sql, checkUser);
    }
    *current_user = username;
    user_allowed = 0;
    system("cls");
    gotoxy(10, 11);
    printf("Login sucessful! Press any key to continue...");
    getch();
    mainMenu();
}
void adminSignup()
{
    createSuperUser();
}
void adminSignout()
{
    system("cls");
    startApp();
}

void forgotPassword()
{
    char username[50], security_answer[50];
    char *hashed_password;
    char sql[200];
    system("cls");
    gotoxy(10, 10);
    printf("Username: ");
    gotoxy(10, 11);
    printf("What is your pet's name? : ");
    gotoxy(20, 10);
    scanf("%s", username);
    gotoxy(37, 11);
    scanf("%s", security_answer);
    sprintf(sql, "SELECT username, password from admin WHERE username = '%s' AND security_answer = '%s'", username, security_answer);
    exec_sql_with_callback(sql, checkUser);
    while (!user_allowed)
    {
        system("cls");
        gotoxy(10, 10);
        printf("Username: ");
        gotoxy(10, 11);
        printf("What is your pet's name? : ");
        gotoxy(10, 15);
        printf("Invalid username or security answer");
        gotoxy(20, 10);
        scanf("%s", username);
        gotoxy(37, 11);
        scanf("%s", security_answer);
    }
    user_allowed = 0;
    changePassword(username, 1);
    system("cls");
    gotoxy(10, 11);
    printf("Password reset sucessfully! Press any key to continue...");
    getch();
    mainMenu();
}
