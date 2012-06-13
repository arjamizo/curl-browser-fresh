all: main
main: main.cpp
	g++ main.cpp -o main -llibcurl
run: main
	./main
