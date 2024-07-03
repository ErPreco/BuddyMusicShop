#include "dependencies/dbconfig.h"
#include "dependencies/dbutils.h"

int main(int argc, char **argv) {
    PGconn *conn = estConn(argv[1], argv[2], argv[3], argv[4], argv[5]);

    // Dichiaro la variabile dei risultati
    PGresult *res;

    printf("Il producer e l'etichetta discografica che hanno collaborato alla produzione dell'album indicato inciso su CD.\n\n");

    // Creo la query
    char *query =
        "select producer.nome, producer.cognome, cdsel.etichettadiscografica "
        "from (select * "
        "from articolomusicale as am join cd on am.codicearticolo = cd.articolomusicale "
        "where am.nome = $1::varchar) as cdsel, produzione, artista as art, collaborazione as collab, producer "
        "where cdsel.codicearticolo = produzione.articolomusicale and produzione.artista = art.nomearte and "
        "art.nomearte = collab.artista and collab.producer = producer.codicefiscale";

    // Preparo la query
    PQprepare(conn, "query", query, 1, NULL);

    // Acquisisco il parametro
    char cdName[50];
    printf("Inserire il nome dell'album: ");
    scanf("%50s", cdName);
    const char *param = cdName;

    // Eseguo la query
    res = PQexecPrepared(conn, "query", 1, &param, NULL, 0, 0);
    checkResults(res, conn);

    // Trovo il numero di tuple
    int tuple = PQntuples(res);

    // Stampo le intestazioni delle colonne
    printf("%-15s ", PQfname(res, 0));
    printf("%-15s ", PQfname(res, 1));
    printf("%s\n", PQfname(res, 2));

    // Stampo i valori selezionati
    for (int i = 0; i < tuple; i++) {
        printf("%-15s ", PQgetvalue(res, i, 0));
        printf("%-15s ", PQgetvalue(res, i, 1));
        printf("%s\n", PQgetvalue(res, i, 2));
    }

    PQclear(res);

    return 0;
}
