all:
	g++ -c *.cpp 
	g++ *.o -o test

clear: 
	rm -f *.o
	rm -f test
