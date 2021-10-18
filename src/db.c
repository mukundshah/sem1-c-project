#include <headers.h>

sqlite3 *db;
char *zErrMsg = 0;
int record;
int flag = 0;
static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    for (size_t i = 0; i < argc; i++)
        printf("%s : %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    printf("\n");
    return 0;
}

void openDB(){
    record = sqlite3_open("storage.db", &db);
    if(record){
        fprintf(stderr, "Can't open database: %s\n",sqlite3_errmsg(db));
        exit(0);
    } 
}

void closeDB(){
    sqlite3_close(db);
}


void connectDB()
{
    openDB();
    closeDB();
}

void createDbAndTables(){
    openDB();
    char *table_admin, *table_books, *table_members;
    table_admin = "CREATE TABLE admin("
                  "id      INTEGER      PRIMARY KEY     AUTOINCREMENT,"
                  "username           CHAR(50)    NOT NULL,"
                  "password            CHAR(100)     NOT NULL,"
                  "security_answer        CHAR(50) NOT NULL);";

    table_books = "CREATE TABLE books("
                  "id      INTEGER      PRIMARY KEY     AUTOINCREMENT,"
                  "title           CHAR(50)    NOT NULL,"
                  "author            CHAR(50)     NOT NULL,"
                  "genre        CHAR(50),"
                  "rack_no            INT,"
                  "quantity            INT     NOT NULL);";

    table_members = "CREATE TABLE members("
                  "id      INTEGER      PRIMARY KEY     AUTOINCREMENT,"
                  "name           CHAR(50)    NOT NULL,"
                  "address            CHAR(50)     NOT NULL,"
                  "contact        CHAR(50) NOT NULL);";

    record = sqlite3_exec(db, table_admin, callback, 0, &zErrMsg);
    if(record != SQLITE_OK){
        fprintf(stderr, "SQL err: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } 
    // else {
    //     fprintf(stdout, "Table 'admin' created sucessfully\n");
    // }

    record = sqlite3_exec(db, table_books, callback, 0, &zErrMsg);
    if(record != SQLITE_OK){
        fprintf(stderr, "SQL err: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } 
    // else {
    //     fprintf(stdout, "Table 'books' created sucessfully\n");
    // }

    record = sqlite3_exec(db, table_members, callback, 0, &zErrMsg);
    if(record != SQLITE_OK){
        fprintf(stderr, "SQL err: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } 
    // else {
    //     fprintf(stdout, "Table 'members' created sucessfully\n");
    // }
    closeDB();
}

int exec_sql(char *sql){
    openDB();
    record = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if(record != SQLITE_OK){
        fprintf(stderr, "SQL err: %s\n", zErrMsg);
        return -1;
    } else {
        return 0;
    }
    
    closeDB();
}

void exec_sql_with_callback(char *sql, int (*custom_callback)(void*,int,char**,char**)){
    openDB();
    record = sqlite3_exec(db, sql, custom_callback, 0, &zErrMsg);
    closeDB();
}
