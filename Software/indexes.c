#include "dependencies/dbconfig.h"
#include "dependencies/dbutils.h"

int main(int argc, char **argv) {
    PGconn *conn = estConn(argv[1], argv[2], argv[3], argv[4], argv[5]);

    // Dichiaro la variabile dei risultati
    PGresult *res;

    printf("Crea gli indici utili per le query 1 e 4.\n");

    // Creo gli indici e gli eseguo
    char *query = "drop index if exists data_scontrino_idx_btree";
    execCommand(conn, "drop_idx1", query, &res);
    query = "create index data_scontrino_idx_btree on scontrino(data)";
    execCommand(conn, "idx1", query, &res);

    query = "drop index if exists ora_scontrino_idx_hash";
    execCommand(conn, "drop_idx2", query, &res);
    query = "create index ora_scontrino_idx_hash on scontrino using hash(ora)";
    execCommand(conn, "idx2", query, &res);

    query = "drop index if exists data_registro_idx_hash";
    execCommand(conn, "drop_idx3", query, &res);
    query = "create index data_registro_idx_hash on registro using hash(datascontrino)";
    execCommand(conn, "idx3", query, &res);

    query = "drop index if exists ora_registro_idx_hash";
    execCommand(conn, "drop_idx4", query, &res);
    query = "create index ora_registro_idx_hash on registro using hash(orascontrino)";
    execCommand(conn, "idx4", query, &res);

    query = "drop index if exists catalogo_registro_idx_hash";
    execCommand(conn, "drop_idx5", query, &res);
    query = "create index catalogo_registro_idx_hash on registro using hash(catalogo)";
    execCommand(conn, "idx5", query, &res);

    query = "drop index if exists articolomusicale_catalogo_idx_hash";
    execCommand(conn, "drop_idx6", query, &res);
    query = "create index articolomusicale_catalogo_idx_hash on catalogo using hash(articolomusicale)";
    execCommand(conn, "idx6", query, &res);

    PQclear(res);

    return 0;
}
