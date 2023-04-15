CXX=g++
FLAGS=-g -Wall 
CXX+FLAGS=${CXX} ${FLAGS}

LIBPATH=lib/
HEADERS=${LIBPATH}include/
SOURCES=${LIBPATH}src/
OBJECTS=${SOURCES}altrepo_export.o ${SOURCES}curlManager.o\
		${SOURCES}fileManager.o
LIB_NAME=libaltrepo_export.so
LIB_VERSION=0.0.1
LIB=${LIB_NAME}.${LIB_VERSION}
LIBRARY=${LIBPATH}${LIB}
LIBOTHER=-lcurl

TARGET=prog

${TARGET}: ${LIBRARY} main.cpp unique.o
	${CXX+FLAGS} main.cpp unique.o -o $@ -L${LIBPATH} -laltrepo_export

unique.o: unique.cpp unique.h
	${CXX+FLAGS} -c $< -o $@

${LIBRARY}: ${OBJECTS}
	${CXX+FLAGS} -shared ${OBJECTS} -o $@ ${LIBOTHER}
	cd ${LIBPATH} && ln -sf ${LIB} ${LIB_NAME}

${SOURCES}altrepo_export.o: ${SOURCES}altrepo_export.cpp \
							${HEADERS}altrepo_export.h
	${CXX+FLAGS} -fPIC -c $< -o $@

${SOURCES}curlManager.o: ${SOURCES}curlManager.cpp ${HEADERS}curlManager.h
	${CXX+FLAGS} -fPIC -c $< -o $@

${SOURCES}fileManager.o: ${SOURCES}fileManager.cpp ${HEADERS}fileManager.h
	${CXX+FLAGS} -fPIC -c $< -o $@

library: ${LIBRARY}
	ls ${LIBPATH}lib*

clean:
	rm -f *.o ${SOURCES}*.o ${TARGET} ${LIBPATH}${LIB_NAME} ${LIBRARY}

rebuild: clean ${TARGET}
