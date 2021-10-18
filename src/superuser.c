#include <headers.h>

int username_exists = 0;

static int checkUsername(void *NotUsed, int argc, char **argv, char **azColName)
{
    for (size_t i = 0; i < argc; i++)
        username_exists = 1;
    return 0;
}

void changePassword(char *username, int reset_flag)
{
    char old_pwd[16], new_pwd[16], confirm_new_pwd[16];
    char sql[200];
    system("cls");
    if (reset_flag)
    {
        gotoxy(10, 11);
        printf("Enter new password: ");
        gotoxy(10, 12);
        printf("Confirm new password: ");

        gotoxy(30, 11);
        getPassword(new_pwd);
        gotoxy(32, 12);
        getPassword(confirm_new_pwd);
        while (strcmp(new_pwd, confirm_new_pwd) != 0)
        {
            system("cls");
            gotoxy(10, 11);
            printf("Enter new password: ");
            gotoxy(10, 12);
            printf("Confirm new password: ");
            gotoxy(10, 15);
            printf("Password did not matched! Enter again");
            gotoxy(30, 11);
            getPassword(new_pwd);
            gotoxy(32, 12);
            getPassword(confirm_new_pwd);
        }
        sprintf(sql, "SELECT username from admin WHERE username = '%s'", username);
        exec_sql_with_callback(sql, checkUsername);
    }
    else
    {
        gotoxy(10, 10);
        printf("Current password: ");
        gotoxy(10, 11);
        printf("Enter new password: ");
        gotoxy(10, 12);
        printf("Confirm new password: ");
        gotoxy(28, 10);
        getPassword(old_pwd);
        gotoxy(28, 11);
        getPassword(new_pwd);
        gotoxy(32, 12);
        getPassword(confirm_new_pwd);
        while (strcmp(new_pwd, confirm_new_pwd) != 0)
        {
            system("cls");
            gotoxy(10, 10);
            printf("Current password: ");
            gotoxy(10, 11);
            printf("Enter new password: ");
            gotoxy(10, 12);
            printf("Confirm new password: ");
            gotoxy(10, 15);
            printf("Password did not matched! Enter again");
            gotoxy(28, 10);
            getPassword(old_pwd);
            gotoxy(28, 11);
            getPassword(new_pwd);
            gotoxy(32, 12);
            getPassword(confirm_new_pwd);
        }
        sprintf(sql, "SELECT username from admin WHERE username = '%s' AND password = '%s'", username, old_pwd);
        exec_sql_with_callback(sql, checkUsername);
    }
    if (username_exists)
    {
        sprintf(sql, "UPDATE admin set password = '%s' WHERE username = '%s'", new_pwd, username);
        exec_sql(sql);
        username_exists = 0;
    }
    else
    {
        system("cls");
        gotoxy(10, 15);
        printf("Failed!!! Press any key to return.");
        getch();
        username_exists = 0;
        reset_flag ? startApp() : mainMenu();
    }
}

void createSuperUser()
{
    char username[50], password[16], confirm_password[16], security_answer[50];
    char *hashed_password;
    char sql[200];
    system("cls");
    gotoxy(10, 10);
    printf("Username: ");
    gotoxy(10, 11);
    printf("Password: ");
    gotoxy(10, 12);
    printf("Confirm password: ");
    gotoxy(10, 13);
    printf("What is your pet's name? : ");
    gotoxy(20, 10);
    scanf("%s", username);

    sprintf(sql, "SELECT username from admin WHERE username = '%s'", username);
    exec_sql_with_callback(sql, checkUsername);
    while (username_exists)
    {
        system("cls");
        gotoxy(10, 10);
        printf("Username: ");
        gotoxy(10, 11);
        printf("Password: ");
        gotoxy(10, 12);
        printf("Confirm password: ");
        gotoxy(10, 13);
        printf("What is your pet's name? : ");
        gotoxy(10, 15);
        printf("Username already exist! Please use another username.");
        gotoxy(20, 10);
        scanf("%s", username);
    }
    gotoxy(20, 11);
    getPassword(password);
    gotoxy(28, 12);
    getPassword(confirm_password);
    gotoxy(37, 13);
    scanf("%s", security_answer);
    while (strcmp(password, confirm_password) != 0)
    {
        system("cls");
        gotoxy(10, 10);
        printf("Username: %s", username);
        gotoxy(10, 11);
        printf("Password: ");
        gotoxy(10, 12);
        printf("Confirm password: ");
        gotoxy(10, 13);
        printf("What is your pet's name? : ");
        gotoxy(10, 15);
        printf("Password did not matched! Enter again");
        gotoxy(20, 11);
        getPassword(password);
        gotoxy(28, 12);
        getPassword(confirm_password);
        gotoxy(37, 13);
        scanf("%s", security_answer);
    }
    hashed_password = password;
    system("cls");
    sprintf(sql, "INSERT INTO admin (username,password,security_answer) "
                 "VALUES ('%s', '%s', '%s');",
            username, hashed_password, security_answer);
    if (exec_sql(sql) == 0)
    {
        gotoxy(10, 12);
        printf("Admin created sucessfuly.");
        Sleep(1000);
    }
    else
    {
        gotoxy(10, 12);
        printf("Signup failed !! Please try again.");
        Sleep(1000);
        createSuperUser();
    }
    username_exists = 0;
}
