CXX = g++

main : main.cpp database.o utils.o
	$(CXX) -o main main.cpp database.o utils.o

database.o : utils.o database.h database.cpp
	$(CXX) -c -o database.o database.cpp 

utils.o : utils.h utils.cpp
	$(CXX) -c -o utils.o utils.cpp 

clean : 
	rm *.o main 


