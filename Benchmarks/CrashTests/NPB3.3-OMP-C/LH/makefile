SHELL=/bin/sh
BENCHMARK=lh
BENCHMARKU=LH

include ../config/make.def

include ../sys/make.common

OBJS = lh.o \
       level_hashing.o \
       hash.o \
       ${COMMON}/print_results.o  \
       ${COMMON}/${RAND}.o \
       ${COMMON}/c_timers.o \
       ${COMMON}/wtime.o ../my_include/my_include.o


${PROGRAM}: config ${OBJS}
	${CLINK} ${CLINKFLAGS} -o ${PROGRAM} ${OBJS} ${C_LIB}

.c.o:
	${CCOMPILE} $<

lh.o: lh.c level_hashing.h npbparams.h

level_hashing.o : level_hashing.c level_hashing.h npbparams.h

hash.o : hash.c hash.h npbparams.h

clean:
	- rm -f *.o *~ 
	- rm -f npbparams.h core
	- if [ -d rii_files ]; then rm -r rii_files; fi
