

# for cube only, mpicc
# Lake Problem 
# Oct. 21, 2014 at Cornell University
# mpicc compile parallel version

CC2 = mpicc  

main: lake_4obj_borg.exe

lake_4obj_borg.exe: ../Borg-1.7/mt19937ar.c ../borg-ms-code/borgms.c lake_4obj_borg.cpp
	$(CC2) -Wall -o lake_4obj_borg.exe ../Borg-1.7/mt19937ar.c ../borg-ms-code/borgms.c \
    lake_4obj_borg.cpp

clean : 
	rm lake_4obj_borg.exe 
