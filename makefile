


CXX = g++
CXXFLAGS = -Wall -g

proj3:  Strand.o Sequencer.o Sequencer.h proj3.cpp
	$(CXX) $(CXXFLAGS) Strand.o Sequencer.o Sequencer.h proj3.cpp -o proj3

Strand.o: Strand.cpp Strand.h
	$(CXX) $(CXXFLAGS) -c Strand.cpp

Sequencer.o: Sequencer.h Sequencer.cpp Strand.h Strand.o
	$(CXX) $(CXXFLAGS) -c Sequencer.cpp

clean:
	rm *.o*
	rm *~
	rm vgcore*
val: proj3
	valgrind --leak-check=yes ./proj3 proj3_data3.txt  


run:
	./proj3
