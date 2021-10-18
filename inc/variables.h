// #include<stdio.h>
// #include<conio.h>
// #include <stdlib.h>
// #include<string.h>
// #include<time.h>

#ifndef VARIABLES_H
# define VARIABLES_H
#include  <windows.h>

FILE *databse;

//list of global variable
char findBook;
char password[16];

typedef struct
{
    int id;
    char title[20];
    char author[20];
    int quantity;
    int rackno;
    char genre[20];
} BOOK;

typedef struct
{
    int id;
    char name[20];
    char address[20];
    char contact[20];
} MEMBER;



//list of function prototype
// char catagories[][15]={"History","Non-Fiction","Fiction","Mystery","Thriller","Architecture", "Romance", "Poetry", "Science", "Journal", "Psychology"};
int exec_sql(char *sql);
void openDB();
void closeDB();

void connectDB();
void createDbAndTables();
void exec_sql_with_callback(char *sql, int (*callback)(void *, int, char **, char **));
void returnfunc();

void startApp();

void adminLogin(char **);
void adminSignup();
void adminSignout();
void forgotPassword();

void mainMenu ();
void booksMenu ();
void membersMenu ();
void myAccountMenu();

void addBook();
void editBook();
void issueBook();
void viewBooks();
void deleteBook();
void searchBook();

void addMember();
void editMember();
void viewMembers();
void deleteMember();
void searchMember();

void changePassword(char *username, int reset_flag);
void createSuperUser();
void editAccountDetails();

int  getData(int);
int  checkId(int);
void closeApplication(void);
void Password();
void getPassword(char *);
void issueRecord();
void creditAndClose();
void gotoxy();


#endif
