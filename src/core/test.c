#include <stdio.h>
#include "plugins/sqlite3/sqlite3.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    for (size_t i = 0; i < argc; i++)
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    printf("\n");
    return 0;
}

int main(){
    sqlite3 *db;
    char *zErrMsg = 0;
    int record;
    char *sql;

    record = sqlite3_open("test.db", &db);

    if (record){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }

    sql = "CREATE TABLE COMPANY(" \
        "ID INT PRIMARY KEY     NOT NULL," \
        "NAME           TEXT    NOT NULL," \
        "AGE            INT     NOT NULL," \
        "ADDRESS        CHAR(50)," \
        "SALARY         REAL );";

    /* Execute SQL statement */
    record = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    
    if( record != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Table created successfully\n");
    }


    sqlite3_close(db);
}