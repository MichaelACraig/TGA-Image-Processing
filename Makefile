project2: main.o
	g++ main.o -o project2

main.o: main.cpp
	g++ -c main.cpp