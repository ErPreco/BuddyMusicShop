#include "dependencies/dbconfig.h"
#include "dependencies/dbutils.h"

int main(int argc, char **argv) {
    PGconn *conn = estConn(argv[1], argv[2], argv[3], argv[4], argv[5]);

    // Dichiaro la variabile dei risultati
    PGresult *res;

    printf("L'artista che ha venduto di più (in termini di prezzi degli articoli venduti) nel mese di febbraio dell'anno corrente.\n\n");

    // Elimino la view se esiste gia'
    char *query = "drop view if exists venditearticolo";

    execCommand(conn, "drop_view", query, &res);

    // Creo la view
    query =
        "create view venditearticolo (articolomusicale, somma) as "
        "select pa.articolomusicale, sum(pa.prezzotot) as somma "
        "from (select cat.articolomusicale, reg.quantita * cat.prezzo as prezzotot "
        "from (select * "
        "from scontrino as s "
        "where s.data >= '2024-02-01' and s.data <= '2024-02-29') as vf, registro as reg, catalogo as cat "
        "where vf.data = reg.datascontrino and vf.ora = reg.orascontrino and reg.catalogo = cat.articolomusicale) as pa "
        "group by pa.articolomusicale";

    execCommand(conn, "create_view", query, &res);

    // Creo la query
    query =
        "select prod.artista "
        "from (select va.articolomusicale, va.somma	"
        "from venditearticolo as va "
        "where va.somma = (select max(somma) from venditearticolo)) as art, produzione as prod "
        "where art.articolomusicale = prod.articolomusicale";

    execQuery(conn, "query", query, &res);

    // Stampo l'intestazione della colonna
    printf("%s\n", PQfname(res, 0));

    // Stampo il valore selezionato
    int tuple = PQntuples(res);
    for (int i = 0; i < tuple; i++) {
        printf("%s\n", PQgetvalue(res, i, 0));
    }

    PQclear(res);

    return 0;
}
