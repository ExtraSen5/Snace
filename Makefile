all:
	g++-6 -c *.cpp 
	g++-6 *.o -o test

clear: 
	rm -f *.o
	rm -f test
