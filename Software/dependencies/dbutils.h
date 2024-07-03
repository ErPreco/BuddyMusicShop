#ifndef DB_UTILS_H
#define DB_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include "include/libpq-fe.h"

void checkResults(PGresult *res, const PGconn *conn);
void checkCommand(PGresult *res, const PGconn *conn);

void execQuery(PGconn *conn, char *stmtName, char *query, PGresult **res);
void execCommand(PGconn *conn, char *stmtName, char *command, PGresult **res);

#endif
