#include <headers.h>
int book_found = 0;
int j = 4;

static int checkBook(void *NotUsed, int argc, char **argv, char **azColName)
{
    for (size_t i = 0; i < argc; i++)
        book_found = 1;
    return 0;
}

static int listBooks(void *NotUsed, int argc, char **argv, char **azColName)
{
    gotoxy(3, j);
    printf("%s", argv[0]);
    gotoxy(9, j);
    printf("%s", argv[1] ? argv[1] : "NULL");
    gotoxy(28, j);
    printf("%s", argv[2] ? argv[2] : "NULL");
    gotoxy(46, j);
    printf("%s", argv[3] ? argv[3] : "NULL");
    gotoxy(58, j);
    printf("%s", argv[5]);
    gotoxy(70, j);
    printf("%s", argv[4]);
    printf("\n\n");
    j++;
    return 0;
}

void addBook()
{
    BOOK book;
    char sql[400];
    char choice;

    system("cls");
    gotoxy(10, 3);
    printf("Enter the Information Below");
    gotoxy(10, 4), printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(10, 5), printf("\xB2"), gotoxy(46, 5), printf("\xB2");
    gotoxy(10, 6), printf("\xB2"), gotoxy(12, 6), printf("Book Title: "), gotoxy(46, 6), printf("\xB2");
    gotoxy(10, 7), printf("\xB2"), gotoxy(46, 7), printf("\xB2");
    gotoxy(10, 8), printf("\xB2"), gotoxy(12, 8), printf("Author: "), gotoxy(46, 8), printf("\xB2");
    gotoxy(10, 9), printf("\xB2"), gotoxy(46, 9), printf("\xB2");
    gotoxy(10, 10), printf("\xB2"), gotoxy(12, 10), printf("Genre: "), gotoxy(46, 10), printf("\xB2");
    gotoxy(10, 11), printf("\xB2"), gotoxy(46, 11), printf("\xB2");
    gotoxy(10, 12), printf("\xB2"), gotoxy(12, 12), printf("Quantity: "), gotoxy(46, 12), printf("\xB2");
    gotoxy(10, 13), printf("\xB2"), gotoxy(46, 13), printf("\xB2");
    gotoxy(10, 14), printf("\xB2"), gotoxy(12, 14), printf("Rack no: "), gotoxy(46, 14), printf("\xB2");
    gotoxy(10, 15), printf("\xB2"), gotoxy(46, 15), printf("\xB2");
    gotoxy(10, 16), printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

    gotoxy(24, 6), scanf("%s", book.title);
    gotoxy(20, 8), scanf("%s", book.author);
    gotoxy(19, 10), scanf("%s", book.genre);
    gotoxy(22, 12), scanf("%d", &book.quantity);
    gotoxy(21, 14), scanf("%d", &book.rackno);

    sprintf(sql, "INSERT INTO books (title,author,genre,rack_no,quantity)"
                 "VALUES ('%s', '%s', '%s', %d, %d);",
            book.title, book.author, book.genre, book.rackno, book.quantity);
    int res = exec_sql(sql);
    system("cls");
    if (res == 0)
    {
        gotoxy(10, 12), printf("Book added to records.");
    }
    else
    {
        gotoxy(10, 12), printf("Something went wrong. You can always try again.");
    }
    gotoxy(10, 13), printf("Press 'c' to add another book, or 'b' to return: ");
    choice = getch();
    if (choice == 'c' || choice == 'C')
        addBook();
    else
        booksMenu();
}
void editBook()
{
    int id;
    BOOK book;
    char sql[400];
    char choice;

    system("cls");
    gotoxy(10, 3);
    printf("Enter the Information Below");
    gotoxy(10, 4), printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(10, 5), printf("\xB2"), gotoxy(46, 5), printf("\xB2");
    gotoxy(10, 6), printf("\xB2"), gotoxy(12, 6), printf("Enetr the ID of Book: "), gotoxy(46, 6), printf("\xB2");
    gotoxy(10, 7), printf("\xB2"), gotoxy(46, 7), printf("\xB2");
    gotoxy(10, 8), printf("\xB2"), gotoxy(46, 8), printf("\xB2");
    gotoxy(10, 9), printf("\xB2"), gotoxy(46, 9), printf("\xB2");
    gotoxy(10, 10), printf("\xB2"), gotoxy(46, 10), printf("\xB2");
    gotoxy(10, 11), printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

    gotoxy(34, 6), scanf("%d", &id);
    sprintf(sql, "SELECT id from books WHERE id = %d", id);
    exec_sql_with_callback(sql, checkBook);
    if (book_found)
    {
        system("cls");
        gotoxy(10, 3);
        printf("Enter the new details. Re-enter the old value in order to not update it.");
        gotoxy(10, 4), printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        gotoxy(10, 5), printf("\xB2"), gotoxy(46, 5), printf("\xB2");
        gotoxy(10, 6), printf("\xB2"), gotoxy(12, 6), printf("Book Title: "), gotoxy(46, 6), printf("\xB2");
        gotoxy(10, 7), printf("\xB2"), gotoxy(46, 7), printf("\xB2");
        gotoxy(10, 8), printf("\xB2"), gotoxy(12, 8), printf("Author: "), gotoxy(46, 8), printf("\xB2");
        gotoxy(10, 9), printf("\xB2"), gotoxy(46, 9), printf("\xB2");
        gotoxy(10, 10), printf("\xB2"), gotoxy(12, 10), printf("Genre: "), gotoxy(46, 10), printf("\xB2");
        gotoxy(10, 11), printf("\xB2"), gotoxy(46, 11), printf("\xB2");
        gotoxy(10, 12), printf("\xB2"), gotoxy(12, 12), printf("Quantity: "), gotoxy(46, 12), printf("\xB2");
        gotoxy(10, 13), printf("\xB2"), gotoxy(46, 13), printf("\xB2");
        gotoxy(10, 14), printf("\xB2"), gotoxy(12, 14), printf("Rack no: "), gotoxy(46, 14), printf("\xB2");
        gotoxy(10, 15), printf("\xB2"), gotoxy(46, 15), printf("\xB2");
        gotoxy(10, 16), printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

        gotoxy(24, 6), scanf("%s", book.title);
        gotoxy(20, 8), scanf("%s", book.author);
        gotoxy(19, 10), scanf("%s", book.genre);
        gotoxy(22, 12), scanf("%d", &book.quantity);
        gotoxy(21, 14), scanf("%d", &book.rackno);
        sprintf(sql, "UPDATE books set title = '%s' , author = '%s', genre = '%s', rack_no = %d, quantity = %d  where id =%d;", book.title, book.author, book.genre, book.rackno, book.quantity, id);
        int res = exec_sql(sql);
        system("cls");
        if (res == 0)
        {
            gotoxy(10, 12), printf("Book updated sucessfully.");
        }
        else
        {
            gotoxy(10, 12), printf("Something went wrong. You can always try again.");
        }
    }
    else
    {
        system("cls");
        gotoxy(10, 12), printf("Book with ID: %d not found.", id);
    }
    book_found = 0;
    gotoxy(10, 13), printf("Press 'c' to edit another book, or 'b' to return: ");
    choice = getch();
    if (choice == 'c' || choice == 'C')
        editBook();

    booksMenu();
}
void issueBook()
{
    system("cls");
    gotoxy(10, 15), printf("This feature is currently not available.");
    gotoxy(10, 16), printf("Press any key to return back...");
    getch();
}
void viewBooks()
{
    char sql[50];
    system("cls");
    gotoxy(2, 1);
    printf("********************************** Book List ********************************");
    gotoxy(2, 2);
    printf(" ID    BOOK NAME          AUTHOR            GENRE       QTY         Rack No. ");
    sprintf(sql, "SELECT * FROM books");
    exec_sql_with_callback(sql, listBooks);
    j = 4;
    getch();
}
void deleteBook()
{
    int id;
    char sql[100];
    char choice;

    system("cls");
    gotoxy(10, 3);
    printf("Enter the Information Below");
    gotoxy(10, 4), printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(10, 5), printf("\xB2"), gotoxy(46, 5), printf("\xB2");
    gotoxy(10, 6), printf("\xB2"), gotoxy(12, 6), printf("Enter the ID of Book to delete: "), gotoxy(46, 6), printf("\xB2");
    gotoxy(10, 7), printf("\xB2"), gotoxy(46, 7), printf("\xB2");
    gotoxy(10, 8), printf("\xB2"), gotoxy(46, 8), printf("\xB2");
    gotoxy(10, 9), printf("\xB2"), gotoxy(46, 9), printf("\xB2");
    gotoxy(10, 10), printf("\xB2"), gotoxy(46, 10), printf("\xB2");
    gotoxy(10, 11), printf("\xB2"), gotoxy(46, 11), printf("\xB2");
    gotoxy(10, 12), printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(26, 8), scanf("%d", &id);

    sprintf(sql, "SELECT id from books WHERE id = %d", id);
    exec_sql_with_callback(sql, checkBook);
    if (book_found)
    {
        gotoxy(12, 10), printf("Confirm ? [Y|N]: ");
        choice = getch();
        if (choice == 121 || choice == 89)
        {
            sprintf(sql, "DELETE from books where id = %d ", id);
            int res = exec_sql(sql);
            if (res == 0)
            {
                system("cls");
                gotoxy(10, 12), printf("Book with ID: %d deleted sucessfully..", id);
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
    book_found = 0;
    booksMenu();
}
void searchBook()
{
    system("cls");
    gotoxy(10, 15), printf("This feature is currently not available.");
    gotoxy(10, 16), printf("Press any key to return back...");
    getch();
}
