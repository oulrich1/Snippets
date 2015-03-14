LIBS = -pthread

stuff: main.o arrays.o
	g++ -o test_pthreads main.o arrays.o $(LIBS)

arrays.o:	 arrays.cpp
	g++ $(LIBS) -c arrays.cpp 

clean:
	rm -rf *.o
