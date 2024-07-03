#include "dependencies/dbconfig.h"
#include "dependencies/dbutils.h"

int main(int argc, char **argv) {
    PGconn *conn = estConn(argv[1], argv[2], argv[3], argv[4], argv[5]);

    // Dichiaro la variabile dei risultati
    PGresult *res;

    printf("Il numero di degli articoli venduti per genere musicale ordinati in modo decrescente.\n\n");

    // Creo la query
    char *query =
        "select gen.tipo as genere, count(*) as quantita "
        "from scontrino as sco, registro as reg, catalogo as cat, articolomusicale as am, genere as gen "
        "where sco.data = reg.datascontrino and sco.ora = reg.orascontrino and reg.catalogo = cat.articolomusicale and "
        "cat.articolomusicale = am.codicearticolo and am.genere = gen.tipo "
        "group by gen.tipo "
        "order by quantita desc";

    execQuery(conn, "query", query, &res);

    // Trovo il numero di tuple
    int tuple = PQntuples(res);

    // Stampo le intestazioni delle colonne
    printf("%-12s ", PQfname(res, 0));
    printf("%s\n", PQfname(res, 1));

    // Stampo i valori selezionati
    for (int i = 0; i < tuple; i++) {
        printf("%-12s ", PQgetvalue(res, i, 0));
        printf("%s ", PQgetvalue(res, i, 1));
    }

    PQclear(res);

    return 0;
}
