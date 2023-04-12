CXX=g++
FLAGS=-g -Wall 
CXX+FLAGS=${CXX} ${FLAGS}
OBJ=main.o curlManager.o altrepo_export.o
TARGET=prog

${TARGET}: ${OBJ}
	${CXX+FLAGS} ${OBJ} -o $@ -lcurl 

main.o: main.cpp
	${CXX+FLAGS} -c $< -o $@

curlManager.o: curlManager.cpp curlManager.h
	${CXX+FLAGS} -c $< -o $@

altrepo_export.o: altrepo_export.cpp altrepo_export.h
	${CXX+FLAGS} -c $< -o $@

execute: ${TARGET}
	./${TARGET}

clean:
	rm -f *.o ${TARGET}

rebuilt: clean ${TARGET}
