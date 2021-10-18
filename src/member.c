#include <headers.h>
int member_found = 0;
int k = 4;

static int checkMember(void *NotUsed, int argc, char **argv, char **azColName)
{
    for (size_t i = 0; i < argc; i++)
        member_found = 1;
    return 0;
}
static int listMembers(void *NotUsed, int argc, char **argv, char **azColName)
{
    gotoxy(3, k);
    printf("%s", argv[0]);
    gotoxy(9, k);
    printf("%s", argv[1] ? argv[1] : "NULL");
    gotoxy(29, k);
    printf("%s", argv[2] ? argv[2] : "NULL");
    gotoxy(49, k);
    printf("%s", argv[3] ? argv[3] : "NULL");
    printf("\n\n");
    k++;
    return 0;
}

void addMember()
{
    MEMBER member;
    char sql[400];
    char choice;

    system("cls");
    gotoxy(10, 3);
    printf("Enter the Information Below");
    gotoxy(10, 4), printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(10, 5), printf("\xB2"), gotoxy(46, 5), printf("\xB2");
    gotoxy(10, 6), printf("\xB2"), gotoxy(12, 6), printf("Name: "), gotoxy(46, 6), printf("\xB2");
    gotoxy(10, 7), printf("\xB2"), gotoxy(46, 7), printf("\xB2");
    gotoxy(10, 8), printf("\xB2"), gotoxy(12, 8), printf("Address: "), gotoxy(46, 8), printf("\xB2");
    gotoxy(10, 9), printf("\xB2"), gotoxy(46, 9), printf("\xB2");
    gotoxy(10, 10), printf("\xB2"), gotoxy(12, 10), printf("Contact: "), gotoxy(46, 10), printf("\xB2");
    gotoxy(10, 11), printf("\xB2"), gotoxy(46, 11), printf("\xB2");
    gotoxy(10, 12), printf("\xB2"), gotoxy(46, 12), printf("\xB2");
    gotoxy(10, 13), printf("\xB2"), gotoxy(46, 13), printf("\xB2");
    gotoxy(10, 14), printf("\xB2"), gotoxy(46, 14), printf("\xB2");
    gotoxy(10, 15), printf("\xB2"), gotoxy(46, 15), printf("\xB2");
    gotoxy(10, 16), printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

    gotoxy(18, 6), scanf("%s", member.name);
    gotoxy(21, 8), scanf("%s", member.address);
    gotoxy(21, 10), scanf("%s", member.contact);
    printf("sucess");
    sprintf(sql, "INSERT INTO members (name,address,contact)"
                 "VALUES ('%s', '%s', '%s');",
            member.name, member.address, member.contact);
    int res = exec_sql(sql);
    system("cls");
    if (res == 0)
    {
        gotoxy(10, 12), printf("Member added to records.");
    }
    else
    {
        gotoxy(10, 12), printf("Something went wrong. You can always try again.");
    }
    gotoxy(10, 13), printf("Press 'c' to add another member, or 'b' to return: ");
    choice = getch();
    if (choice == 'c' || choice == 'C')
        addMember();
    else
        membersMenu();
}
void editMember()
{
    int id;
    MEMBER member;
    char sql[400];
    char choice;

    system("cls");
    gotoxy(10, 3);
    printf("Enter the Information Below");
    gotoxy(10, 4), printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(10, 5), printf("\xB2"), gotoxy(46, 5), printf("\xB2");
    gotoxy(10, 6), printf("\xB2"), gotoxy(12, 6), printf("Enetr the ID of Member: "), gotoxy(46, 6), printf("\xB2");
    gotoxy(10, 7), printf("\xB2"), gotoxy(46, 7), printf("\xB2");
    gotoxy(10, 8), printf("\xB2"), gotoxy(46, 8), printf("\xB2");
    gotoxy(10, 9), printf("\xB2"), gotoxy(46, 9), printf("\xB2");
    gotoxy(10, 10), printf("\xB2"), gotoxy(46, 10), printf("\xB2");
    gotoxy(10, 11), printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

    gotoxy(24, 6), scanf("%d", &id);
    sprintf(sql, "SELECT id from members WHERE id = %d", id);
    exec_sql_with_callback(sql, checkMember);
    if (member_found)
    {
        system("cls");
        gotoxy(10, 3);
        printf("Enter the new details. Re-enter the old value in order to not update it.");
        gotoxy(10, 4), printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        gotoxy(10, 5), printf("\xB2"), gotoxy(46, 5), printf("\xB2");
        gotoxy(10, 6), printf("\xB2"), gotoxy(12, 6), printf("Name: "), gotoxy(46, 6), printf("\xB2");
        gotoxy(10, 7), printf("\xB2"), gotoxy(46, 7), printf("\xB2");
        gotoxy(10, 8), printf("\xB2"), gotoxy(12, 8), printf("Address: "), gotoxy(46, 8), printf("\xB2");
        gotoxy(10, 9), printf("\xB2"), gotoxy(46, 9), printf("\xB2");
        gotoxy(10, 10), printf("\xB2"), gotoxy(12, 10), printf("Contact: "), gotoxy(46, 10), printf("\xB2");
        gotoxy(10, 11), printf("\xB2"), gotoxy(46, 11), printf("\xB2");
        gotoxy(10, 12), printf("\xB2"), gotoxy(46, 12), printf("\xB2");
        gotoxy(10, 13), printf("\xB2"), gotoxy(46, 13), printf("\xB2");
        gotoxy(10, 14), printf("\xB2"), gotoxy(46, 14), printf("\xB2");
        gotoxy(10, 15), printf("\xB2"), gotoxy(46, 15), printf("\xB2");
        gotoxy(10, 16), printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

        gotoxy(18, 6), scanf("%s", member.name);
        gotoxy(21, 8), scanf("%s", member.address);
        gotoxy(21, 10), scanf("%s", member.contact);
        sprintf(sql, "UPDATE books set name = '%s' , address = '%s', contact = '%s' where id =%d;", member.name, member.address, member.contact, id);

        int res = exec_sql(sql);
        system("cls");
        if (res == 0)
        {
            gotoxy(10, 12), printf("Member updated sucessfully.");
        }
        else
        {
            gotoxy(10, 12), printf("Something went wrong. You can always try again.");
        }
    }
    else
    {
        system("cls");
        gotoxy(10, 12), printf("Member with ID: %d not found.", id);
    }
    member_found = 0;
    gotoxy(10, 13), printf("Press 'c' to edit another member, or 'b' to return: ");
    choice = getch();
    if (choice == 99 || choice == 67)
        editMember();

    membersMenu();
}
void viewMembers()
{
    char sql[50];
    system("cls");
    gotoxy(2, 1);
    printf("********************* Members List ************************");
    gotoxy(2, 2);
    printf(" ID    NAME                ADDRESS             CONTACT        ");
    sprintf(sql, "SELECT * FROM members");
    exec_sql_with_callback(sql, listMembers);
    k = 4;
    getch();
}
void deleteMember()
{
    int id;
    char sql[100];
    char choice;

    system("cls");
    gotoxy(10, 3);
    printf("Enter the Information Below");
    gotoxy(10, 4), printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(10, 5), printf("\xB2"), gotoxy(46, 5), printf("\xB2");
    gotoxy(10, 6), printf("\xB2"), gotoxy(12, 6), printf("Enter the ID of Member to delete: "), gotoxy(46, 6), printf("\xB2");
    gotoxy(10, 7), printf("\xB2"), gotoxy(46, 7), printf("\xB2");
    gotoxy(10, 8), printf("\xB2"), gotoxy(46, 8), printf("\xB2");
    gotoxy(10, 9), printf("\xB2"), gotoxy(46, 9), printf("\xB2");
    gotoxy(10, 10), printf("\xB2"), gotoxy(46, 10), printf("\xB2");
    gotoxy(10, 11), printf("\xB2"), gotoxy(46, 11), printf("\xB2");
    gotoxy(10, 12), printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(26, 8), scanf("%d", &id);

    sprintf(sql, "SELECT id from members WHERE id = %d", id);
    exec_sql_with_callback(sql, checkMember);
    if (member_found)
    {
        gotoxy(12, 10), printf("Confirm ? [Y|N]: ");
        choice = getch();
        if (choice == 121 || choice == 89)
        {
            sprintf(sql, "DELETE from members where id = %d ", id);
            int res = exec_sql(sql);
            if (res == 0)
            {
                system("cls");
                gotoxy(10, 12), printf("Member with ID: %d deleted sucessfully..");
                gotoxy(10, 14), printf("Press any key to return back...");
                getch();
            }
            else
            {
                system("cls");
                gotoxy(10, 12), printf("Operation failed!");
                gotoxy(10, 14), printf("Press any key to return back...");
                getch();
            }
        }
    }
    else
    {
        gotoxy(12, 10), printf("ID not found. Exiting prompt...");
        Sleep(2000);
    }
    member_found = 0;
    membersMenu();
}
void searchMember()
{

    system("cls");
    gotoxy(10, 15), printf("This feature is currently not available.");
    gotoxy(10, 16), printf("Press any key to return back...");
    getch();
}
