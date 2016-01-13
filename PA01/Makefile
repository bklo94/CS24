program: stattest.o stats.o
	g++ -o stattest stattest.o stats.o

stattest.o: stattest.cxx
	g++ -c stattest.cxx

stats.o: stats.cxx
	g++ -c stats.cxx stats.h

clean:
	rm -f program stattest.o stats.o *o
