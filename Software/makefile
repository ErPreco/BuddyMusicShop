CC = gcc
FLAGS = -Wall
DEP_DIR = dependencies
INC_DIR = dependencies/include

make:
	${CC} -o query1.out query1.c ${DEP_DIR}/dbconfig.c ${DEP_DIR}/dbutils.c -I ${INC_DIR} -lpq ${FLAGS}
	${CC} -o query2.out query2.c ${DEP_DIR}/dbconfig.c ${DEP_DIR}/dbutils.c -I ${INC_DIR} -lpq ${FLAGS}
	${CC} -o query3.out query3.c ${DEP_DIR}/dbconfig.c ${DEP_DIR}/dbutils.c -I ${INC_DIR} -lpq ${FLAGS}
	${CC} -o query4.out query4.c ${DEP_DIR}/dbconfig.c ${DEP_DIR}/dbutils.c -I ${INC_DIR} -lpq ${FLAGS}
	${CC} -o query5.out query5.c ${DEP_DIR}/dbconfig.c ${DEP_DIR}/dbutils.c -I ${INC_DIR} -lpq ${FLAGS}
	${CC} -o query6.out query6.c ${DEP_DIR}/dbconfig.c ${DEP_DIR}/dbutils.c -I ${INC_DIR} -lpq ${FLAGS}
	${CC} -o indexes.out indexes.c ${DEP_DIR}/dbconfig.c ${DEP_DIR}/dbutils.c -I ${INC_DIR} -lpq ${FLAGS}

clean:
	rm *.out
