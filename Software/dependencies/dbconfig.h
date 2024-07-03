#ifndef DB_CONFIG_H
#define DB_CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include "include/libpq-fe.h"

PGconn* estConn(char* host, char* username, char* db, char* port, char* psw);

#endif
