try: project.o 
	cc  project.o  -o try

project.o: project.c 
	cc -Wall -c project.c

