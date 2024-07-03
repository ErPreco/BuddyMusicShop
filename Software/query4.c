#include "dependencies/dbconfig.h"
#include "dependencies/dbutils.h"

int main(int argc, char **argv) {
    PGconn *conn = estConn(argv[1], argv[2], argv[3], argv[4], argv[5]);

    // Dichiaro la variabile dei risultati
    PGresult *res;

    printf("Le e-mail dei clienti che hanno effettuato delle prenotazioni per una spesa totale superiore alla cifra indicata; ordinarle in modo decrescente secondo la spesa.\n\n");

    // Creo la query
    char *query =
        "select sco.cliente, sum(cat.prezzo) spesatotale "
        "from scontrino as sco, registro as reg, catalogo as cat "
        "where sco.data = reg.datascontrino and sco.ora = reg.orascontrino and reg.catalogo = cat.articolomusicale and "
        "sco.cliente is not null "
        "group by sco.cliente "
        "having sum(cat.prezzo) > $1 "
        "order by spesatotale desc";

    // Preparo la query
    PQprepare(conn, "query", query, 1, NULL);

    // Acquisisco il parametro
    char num[4];
    printf("Inserire la soglia di spesa da verificare: ");
    scanf("%4s", num);
    const char *param = num;

    // Eseguo la query
    res = PQexecPrepared(conn, "query", 1, &param, NULL, 0, 0);
    checkResults(res, conn);

    // Trovo il numero di tuple
    int tuple = PQntuples(res);

    // Stampo le intestazioni delle colonne
    printf("%-40s ", PQfname(res, 0));
    printf("%s\n", PQfname(res, 1));

    // Stampo i valori selezionati
    for (int i = 0; i < tuple; i++) {
        printf("%-40s ", PQgetvalue(res, i, 0));
        printf("%s\n", PQgetvalue(res, i, 1));
    }

    PQclear(res);

    return 0;
}
