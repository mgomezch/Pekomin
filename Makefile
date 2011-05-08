LDLIBS = -lm

all: pekomin

clean:
	rm -f *.gch *.o pekomin

pekomin: pekomin.o Triple.o
	g++ $(CXXOPTS) -o pekomin *.o $(LDLIBS)

pekomin.o: pekomin.cpp Triple.hpp
	g++ $(CXXOPTS) -c pekomin.cpp $(LDLIBS) 

Triple.o: Triple.cpp Triple.hpp
	g++ $(CXXOPTS) -c Triple.cpp $(LDLIBS)

