CC = g++
MPICC = mpicc

LIBS = -lm


main: LakeProblem.exe

LakeProblem.exe: ../MOEAFramework/MOEAFramework-2.3/examples/moeaframework.c  lake_4obj_borg.cpp
	$(CC)  -o LakeProblem.exe  ../MOEAFramework/MOEAFramework-2.3/examples/moeaframework.c  lake_4obj_borg.cpp  $(LIBS)
   
 clean:
	rm LakeProblem.exe