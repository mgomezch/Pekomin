CC=gcc
CFLAGS=-Wall
CXX=g++
CXXFLAGS=-Wall
LD=ld
LDLIBS=-lm
LDFLAGS=

all: pekomin

clean:
	rm -f *.gch *.o *~ pekomin 

pekomin: pekomin.o Ent.o Triple.o Behavior.o Static.o Kinematic.o KinematicSeek.o KinematicFlee.o KinematicArrive.o KinematicWander.o util.o
	$(CXX) $(CXXFLAGS) -o pekomin *.o $(LDLIBS) 

KinematicWander.o: KinematicWander.cpp KinematicWander.hpp Kinematic.hpp util.hpp
	$(CXX) $(CXXFLAGS) -c KinematicWander.cpp

KinematicArrive.o: KinematicArrive.cpp KinematicArrive.hpp Kinematic.hpp
	$(CXX) $(CXXFLAGS) -c KinematicArrive.cpp

KinematicFlee.o: KinematicFlee.cpp KinematicFlee.hpp Kinematic.hpp
	$(CXX) $(CXXFLAGS) -c KinematicFlee.cpp

KinematicSeek.o: KinematicSeek.cpp KinematicSeek.hpp Kinematic.hpp
	$(CXX) $(CXXFLAGS) -c KinematicSeek.cpp

Kinematic.o: Kinematic.cpp Kinematic.hpp Static.hpp
	$(CXX) $(CXXFLAGS) -c Kinematic.cpp

Static.o: Static.cpp Static.hpp Behavior.hpp
	$(CXX) $(CXXFLAGS) -c Static.cpp

Behavior.o: Behavior.cpp Behavior.hpp Triple.hpp
	$(CXX) $(CXXFLAGS) -c Behavior.cpp

pekomin.o: pekomin.cpp Triple.hpp
	$(CXX) $(CXXFLAGS) -c pekomin.cpp

Ent.o: Ent.cpp Ent.hpp Triple.hpp
	$(CXX) $(CXXFLAGS) -c Ent.cpp

Triple.o: Triple.cpp Triple.hpp
	$(CXX) $(CXXFLAGS) -c Triple.cpp

util.o: util.cpp util.hpp
	$(CXX) $(CXXFLAGS) -c util.cpp
