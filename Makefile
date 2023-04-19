CXX=g++
FLAGS=-g -Wall 
CXX+FLAGS=${CXX} ${FLAGS}

LIB_PATH=lib/
LIB_HEADERS=${LIB_PATH}include/
LIB_SOURCES=${LIB_PATH}src/
LIB_OBJ=${LIB_SOURCES}altrepo_export.o ${LIB_SOURCES}curlManager.o\
		${LIB_SOURCES}fileManager.o

	# library naming
LIB_ROOT_NAME=altrepoexport
LIB_PERIOD=0
LIB_VERSION=0.1
LIB_SONAME=lib${LIB_ROOT_NAME}.so.${LIB_PERIOD}
LIB_LINK_NAME=lib${LIB_ROOT_NAME}.so
LIB_REAL_NAME=${LIB_SONAME}.${LIB_VERSION}
LIBRARY=${LIB_PATH}${LIB_REAL_NAME}
LIB_OTHER=-lcurl

	# install path
PREFIX=/usr/local
INCLUDE_PATH=/include/altrepo/

PROG_NAME=prog

${LIBRARY}: ${LIB_OBJ}
	${CXX+FLAGS} -shared ${LIB_OBJ} -o $@ ${LIB_OTHER}
	cd ${LIB_PATH} && ln -sf ${LIB_REAL_NAME} ${LIB_LINK_NAME}

${LIB_SOURCES}altrepo_export.o: ${LIB_SOURCES}altrepo_export.cpp \
							    ${LIB_HEADERS}altrepo_export.h
	${CXX+FLAGS} -fPIC -c $< -o $@

${LIB_SOURCES}curlManager.o: ${LIB_SOURCES}curlManager.cpp \
							 ${LIB_HEADERS}curlManager.h
	${CXX+FLAGS} -fPIC -c $< -o $@

${LIB_SOURCES}fileManager.o: ${LIB_SOURCES}fileManager.cpp \
							 ${LIB_HEADERS}fileManager.h
	${CXX+FLAGS} -fPIC -c $< -o $@

library: ${LIBRARY}
	ls ${LIB_PATH}lib*
.PHONY: library

install: ${LIBRARY}
	cd ${LIB_PATH} && install -m 644 ${LIB_REAL_NAME} ${PREFIX}/lib && \
	cd ${PREFIX}/lib && ln -sf ${LIB_REAL_NAME} ${LIB_SONAME} && \
		ln -sf ${LIB_SONAME} ${LIB_LINK_NAME} && ldconfig
	mkdir -p ${PREFIX}${INCLUDE_PATH} && \
		install -m 644 ${LIB_HEADERS}*.h ${PREFIX}${INCLUDE_PATH}
.PHONY: install

uninstall:
	rm -rf ${PREFIX}/include/altrepo
	rm -f ${PREFIX}/lib/*${LIB_ROOT_NAME}* && ldconfig
.PHONY: uninstall

${PROG_NAME}: main.cpp unique.o
	${CXX+FLAGS} $< unique.o -o $@ -l${LIB_ROOT_NAME}

unique.o: unique.cpp unique.h
	${CXX+FLAGS} -c $< -o $@

clean:
	rm -f *.o ${LIB_SOURCES}*.o ${PROG_NAME} ${LIBRARY}\
			  ${LIB_PATH}${LIB_LINK_NAME}
.PHONY: clean

rebuild: clean ${LIBRARY} ${PROG_NAME}
