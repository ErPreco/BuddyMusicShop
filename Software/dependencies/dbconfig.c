#include "dbconfig.h"

#include <string.h>

PGconn* estConn(char* host, char* username, char* db, char* port, char* psw) {
    char conninfo[250];

    if (psw == NULL) {
        psw = "-";  // far finta che la password sia vuota, se fornisco una stringa vuota va in errore
    }

    if (host == NULL || username == NULL || db == NULL || port == NULL) {
        printf("Inserire tutti i parametri per il collegamento al database\n");
        exit(1);
    }

    sprintf(conninfo, " user=%s password=%s dbname=%s host=%s port=%d ", username, psw, db, host, atoi(port));

    // Eseguo la connessione al database
    PGconn* conn;
    conn = PQconnectdb(conninfo);

    // Verifico lo stato di connessione
    if (PQstatus(conn) != CONNECTION_OK) {
        printf("Errore di connessione: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        exit(1);
    }

    return conn;
}
