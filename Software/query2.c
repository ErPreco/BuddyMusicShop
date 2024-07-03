#include "dependencies/dbconfig.h"
#include "dependencies/dbutils.h"

int main(int argc, char **argv) {
    PGconn *conn = estConn(argv[1], argv[2], argv[3], argv[4], argv[5]);

    // Dichiaro la variabile dei risultati
    PGresult *res;

    printf("Gli articoli (codice, descrizione, etichetta discografica, codice bundle) che appartengono al prossimo evento in modo che si visionino prima tutti i bundle.\n\n");

    // Creo la query
    char *query =
        "select codicearticolo, descrizione, etichettadiscografica, codicebundle "
        "from (select * "
        "from evento "
        "where data = (select min(data) from evento where numeroarticolivenduti is null)) as prossimoevento "
        "join articolomusicale on prossimoevento.genere = articolomusicale.genere "
        "order by etichettadiscografica desc";

    execQuery(conn, "query", query, &res);

    // Trovo il numero di tuple
    int tuple = PQntuples(res);

    // Stampo le intestazioni delle colonne
    printf("%-20s ", PQfname(res, 0));
    printf("%-80s ", PQfname(res, 1));
    printf("%-40s ", PQfname(res, 2));
    printf("%s\n", PQfname(res, 3));

    // Stampo i valori selezionati
    for (int i = 0; i < tuple; i++) {
        printf("%-20s ", PQgetvalue(res, i, 0));
        printf("%-80s ", PQgetvalue(res, i, 1));
        printf("%-40s ", PQgetvalue(res, i, 2));
        printf("%s\n", PQgetvalue(res, i, 3));
    }

    PQclear(res);

    return 0;
}
