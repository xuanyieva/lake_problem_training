lake_problem_training
=====================

  A multi-objective  lake problem originated from Carpenter et al., 1999.

To run the specific variables version, download the var.txt, lake_4obj_spec.cpp, SOWs_Type6.txt and put them in the same folder, use g++ to compile in the cygwin.


To run the borg version, download the lake_4obj_borg.cpp,SOWs_Type6.txt,makefile and put them in the same folder(Borg 1.7 folder is out of the folder), type make in the command line for compiling, and then type   ./lake_4obj_borg to run the model.




For the Matlab version, the following step should be followed:
1)Check and install compiler  running mex-setup at the matlab command line.If there is not any compiler, it will show NONE. In this case, try to install one. On Windows 7/8, Matlab 2012~2014, Windows SDK 7.1 is recommended (go to http://www.mathworks.com/matlabcentral/answers/101105-how-do-i-install-microsoft-windows-sdk-7-1 to get more details).
2)Compile Borg  put the Borg.dll, Borg.lib, borg.m, lake4obj.m, nativeborg.cpp, and borg.h into the same folder,and run the command mex nativeborg.cpp Borg.lib.
3)Get  results  run command  [vars, objs，constrs] = borg(100, 4, 1, @lake4obj, 10000, zeros(1,100), 0.1*ones(1,100), 0.01*ones(1,4)); in Matlab.

To get more informations on BORG Matlab Wrapper, please go to http://waterprogramming.wordpress.com/2014/01/21/compiling-the-borg-matlab-wrapper/.

