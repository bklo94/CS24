
polytest2: polytest2.o poly2.o
	g++ -Wall -g -std=c++0x poly2.o polytest2.o -lm -o polytest2

# this compiles your test program and your poly2 class together
polyexam2: polyexam2.o poly2.o
	g++ -Wall -g -std=c++0x poly2.o polyexam2.o -lm -o polyexam2

# this compiles your poly2 class, which isn't executable (no main)
poly2.o: poly2.h poly2.cxx
	g++ -Wall -g -std=c++0x -c poly2.cxx -o poly2.o

# this compiles your test program, which is executable
polytest2.o: poly2.h polytest2.cxx
	g++ -Wall -g -std=c++0x -c polytest2.cxx -o polytest2.o

# this compiles your test program, which is executable
polyexam2.o: poly2.h polyexam2.cxx
	g++ -Wall -g -std=c++0x -c polyexam2.cxx -o polyexam2.o

# this deletes all the output files
clean:
	rm $(EXPENDABLES)
