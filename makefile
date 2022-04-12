all:memcheck out

memcheck:
	g++ -c -o memcheck.o memcheck.cpp --std=c++11
out:
	g++ -o run memcheck.o main.cpp 
clean:
	rm *.o run