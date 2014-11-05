lake_problem_training
=====================

  A multi-objective  lake problem originated from Carpenter et al., 1999.

  Use algorithms in MOEAFramework to solve the problem, the name is still lake_problem_borg but they don't only solve by BORG.
  
  to run, put the MOEAFramework_version_Demo.jar into the same folder, and run make to get LakeProblem.exe  (if run in the cube, put the exe into examples folder)
  then type:
  
javac -classpath MOEAFramework-2.3-Demo.jar LakeProblem.java   to compile  (here we generate a class which can be invoked in some algorithm, but directly run it will get nothing. 

java -classpath MOEAFramework-2.3-Demo.jar LakeProblem   to run.
