test : 
#Question
	g++ -c test.cpp
	g++ -g -o debug1 test.o
	g++ -O3 -o railtest test.o