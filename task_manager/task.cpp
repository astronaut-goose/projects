#include <iostream>
#include <sqlite3.h>
#include <stdio.h>
#include <fstream>
#include <string>

#include "task.h"

Task::Task(){};
Task::~Task(){};

static int callback(void *data, int argc, char **argv, char **azColName)
{
    int i;
    static int pid = 1;
    //fprintf(stderr, "%s: ", (const char*)data);  // to wyświetla "Callback function called:"

    for(i = 0; i<argc; i++) {
        //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        printf("   %d       %s\n", pid, argv[i] ? argv[i] : "NULL");
        pid++;
    }
    //printf("\n");
    return 0;
}

sqlite3 *db;                // database
char *zErrMsg = 0;          // for error handling
int rc;                     // managing database requests
const char *sql;            // for SQL statements
sqlite3_stmt* st;
const char* data = "Callback function called";
//const char* db_name = "taskDB.db";
const char* uri = "file:/home/lukasz/Desktop/cpp_projects/task_manager/taskDB.db";

void Task::checkDB()
{
    // OPEN DATABASE
    //rc = sqlite3_open(db_name, &db);
    rc = sqlite3_open_v2(uri, &db, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE | SQLITE_OPEN_URI, NULL);

    if(rc){
        fprintf(stderr, "can't open database: %s\n", sqlite3_errmsg(db));
    }

    // CREATE SQL STATEMENT [CREATE A TABLE]
    sql =   "CREATE TABLE IF NOT EXISTS Tasks("
            "id INTEGER PRIMARY KEY     AUTOINCREMENT,"
            "Name           TEXT        NOT NULL);" ;

    // EXECUTE SQL STATEMENT |EXECUTE|
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

    if(rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    // CLOSE DATABASE
    sqlite3_close(db);
}
void Task::show()
{
    // OPEN DATABASE
    //rc = sqlite3_open(db_name, &db);
    rc = sqlite3_open_v2(uri, &db, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE | SQLITE_OPEN_URI, NULL);

    if(rc){
        fprintf(stderr, "can't open database: %s\n", sqlite3_errmsg(db));
    }

    // CREATE SQL STATEMENT [SELECT OPERATION]
    sql = "SELECT Name FROM Tasks";

    printf("  ID      Task name\n");
    printf("------   ----------------------------------------------------\n");

    // EXECUTE SQL STATEMENT
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

    if(rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    // CLOSE DATABASE
    sqlite3_close(db);
}

void Task::addTask(std::string taskName)
{
    // OPEN DATABASE
    //rc = sqlite3_open(db_name, &db);
    rc = sqlite3_open_v2(uri, &db, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE | SQLITE_OPEN_URI, NULL);

    if(rc){
        fprintf(stderr, "can't open database: %s\n", sqlite3_errmsg(db));
    }

    // CREATE SQL STATEMENT [INSERT OPERATION]

    sql =   "INSERT INTO Tasks (Name)"
            "VALUES (?);";


    sqlite3_prepare_v2( db, sql, -1, &st, NULL);
    sqlite3_bind_text(st, 1, taskName.c_str(), taskName.length(), SQLITE_TRANSIENT);

    // EXECUTE SQL STATEMENT |STEP|
    rc = sqlite3_step(st);
    if (rc != SQLITE_DONE){
        fprintf(stderr, "Error inserting data: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(st);

    // CLOSE DATABASE
    sqlite3_close(db);
}

void Task::updateTask(int taskID, std::string taskName)
{
    // OPEN DATABASE
    //rc = sqlite3_open(db_name, &db);
    rc = sqlite3_open_v2(uri, &db, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE | SQLITE_OPEN_URI, NULL);

    if(rc){
        fprintf(stderr, "can't open database: %s\n", sqlite3_errmsg(db));
    }

    // CREATE SQL STATEMENT [DELETE OPERATION]
    sql = "UPDATE Tasks SET Name = ? WHERE id in (SELECT id FROM Tasks LIMIT 1 OFFSET ?)" ;

    int tmp = taskID - 1;

    sqlite3_prepare_v2( db, sql, -1, &st, NULL);
    sqlite3_bind_text(st, 1, taskName.c_str(), taskName.length(), SQLITE_TRANSIENT);
    sqlite3_bind_int(st, 2, tmp);

    // EXECUTE SQL STATEMENT |STEP|
    rc = sqlite3_step(st);
    if (rc != SQLITE_DONE){
        fprintf(stderr, "Error inserting data: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(st);

    // CLOSE DATABASE
    sqlite3_close(db);
}

void Task::deleteTask(int taskID)
{
    // OPEN DATABASE
    //rc = sqlite3_open(db_name, &db);
    rc = sqlite3_open_v2(uri, &db, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE | SQLITE_OPEN_URI, NULL);

    if(rc){
        fprintf(stderr, "can't open database: %s\n", sqlite3_errmsg(db));
    }

    // CREATE SQL STATEMENT [DELETE OPERATION]
    sql = "DELETE FROM Tasks WHERE id in (SELECT id FROM Tasks LIMIT 1 OFFSET ?)" ;

    int tmp = taskID - 1;

    sqlite3_prepare_v2( db, sql, -1, &st, NULL);
    sqlite3_bind_int(st, 1, tmp);

    // EXECUTE SQL STATEMENT |STEP|
    rc = sqlite3_step(st);
    if (rc != SQLITE_DONE){
        fprintf(stderr, "Error inserting data: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(st);

    // CLOSE DATABASE
    sqlite3_close(db);
}
