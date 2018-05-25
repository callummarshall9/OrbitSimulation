hellomake: *.cpp
	g++ -c -g -pthread main.cpp
	g++ *.o -lpthread -o orbit_simulator -lsfml-graphics -lsfml-window -lsfml-system
