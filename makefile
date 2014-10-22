CC = g++
MPICC = mpicc
CFLAGS = -O3
LDFLAGS = -Wl,-R,\.
LIBS = -lm
UNAME_S = $(shell uname -s)

ifneq (, $(findstring SunOS, $(UNAME_S)))
	LIBS += -lnsl -lsocket -lresolv
else ifneq (, $(findstring MINGW, $(UNAME_S)))
	# MinGW is not POSIX compliant
else
	POSIX = yes
endif

compile:
	$(CC) $(CFLAGS) $(LDFLAGS) -o lake_4obj_borg.exe lake_4obj_borg.cpp ../Borg-1.7/borg.c ../Borg-1.7/mt19937ar.c $(LIBS)

ifdef POSIX
	$(CC) $(CFLAGS) $(LDFLAGS) -o borg.exe ../Borg-1.7/frontend.c ../Borg-1.7/borg.c ../Borg-1.7/mt19937ar.c $(LIBS)
endif

.PHONY: compile

