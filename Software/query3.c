#include "dependencies/dbconfig.h"
#include "dependencies/dbutils.h"

int main(int argc, char **argv) {
    PGconn *conn = estConn(argv[1], argv[2], argv[3], argv[4], argv[5]);

    // Dichiaro la variabile dei risultati
    PGresult *res;

    printf("Le etichette discografiche ordinate in modo decrescente secondo il numero di vinili incisi.\n\n");

    // Creo la query
    char *query =
        "select ed.nome, count(*) numerovinili "
        "from vinile as vin, articolomusicale as am, etichettadiscografica as ed "
        "where vin.articolomusicale = am.codicearticolo and am.etichettadiscografica = ed.nome "
        "group by ed.nome "
        "order by numerovinili desc";

    execQuery(conn, "query", query, &res);

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
