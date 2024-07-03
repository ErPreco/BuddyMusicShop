#include "dbutils.h"

void checkResults(PGresult *res, const PGconn *conn) {
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        printf("Risultati inconsistenti %s\n", PQerrorMessage(conn));
        PQclear(res);
        exit(1);
    }
}

void checkCommand(PGresult *res, const PGconn *conn) {
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        printf("Comando fallito %s\n", PQerrorMessage(conn));
        PQclear(res);
        exit(1);
    }
}

void execQuery(PGconn *conn, char *stmtName, char *query, PGresult **res) {
    PQprepare(conn, stmtName, query, 0, NULL);
    *res = PQexecPrepared(conn, stmtName, 0, NULL, NULL, 0, 0);
    checkResults(*res, conn);
}

void execCommand(PGconn *conn, char *stmtName, char *command, PGresult **res) {
    PQprepare(conn, stmtName, command, 0, NULL);
    *res = PQexecPrepared(conn, stmtName, 0, NULL, NULL, 0, 0);
    checkCommand(*res, conn);
}
