CXX=g++
FLAGS=-g -Wall 
CXX+FLAGS=${CXX} ${FLAGS}
OBJ=main.o curlManager.o altrepo_export.o fileManager.o unique.o
TARGET=prog

${TARGET}: ${OBJ}
	${CXX+FLAGS} ${OBJ} -o $@ -lcurl 

main.o: main.cpp
	${CXX+FLAGS} -c $< -o $@

curlManager.o: curlManager.cpp curlManager.h
	${CXX+FLAGS} -c $< -o $@

fileManager.o: fileManager.cpp fileManager.h
	${CXX+FLAGS} -c $< -o $@

altrepo_export.o: altrepo_export.cpp altrepo_export.h
	${CXX+FLAGS} -c $< -o $@

unique.o: unique.cpp unique.h
	${CXX+FLAGS} -c $< -o $@

execute: ${TARGET}
	./${TARGET} i586 p10 p9

clean:
	rm -f *.o ${TARGET}

rebuilt: clean ${TARGET}
