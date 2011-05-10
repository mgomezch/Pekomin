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

pekomin: pekomin.o Triple.o KinematicSeek.o KinematicFlee.o KinematicArrive.o KinematicWander.o Seek.o Flee.o Arrive.o Align.o VelocityMatch.o Pursue.o Evade.o Face.o
	$(CXX) $(CXXFLAGS) -o pekomin *.o $(LDLIBS) 

Face.o: Face.cpp Face.hpp Align.hpp Behavior.hpp
	$(CXX) $(CXXOPTS) -c Align.cpp $(LDLIBS)

Evade.o: Evade.cpp Evade.hpp Flee.hpp Behavior.hpp
	$(CXX) $(CXXOPTS) -c Evade.cpp $(LDLIBS)

Pursue.o: Pursue.cpp Pursue.hpp Seek.hpp Behavior.hpp
	$(CXX) $(CXXOPTS) -c Pursue.cpp $(LDLIBS)

VelocityMatch.o: VelocityMatch.cpp VelocityMatch.hpp Behavior.hpp
	$(CXX) $(CXXOPTS) -c VelocityMatch.cpp $(LDLIBS)

Align.o: Align.cpp Align.hpp Behavior.hpp
	$(CXX) $(CXXOPTS) -c Align.cpp $(LDLIBS)

Arrive.o: Arrive.cpp Arrive.hpp Behavior.hpp
	$(CXX) $(CXXOPTS) -c Arrive.cpp $(LDLIBS)

Flee.o: Flee.cpp Flee.hpp Behavior.hpp
	$(CXX) $(CXXOPTS) -c Flee.cpp $(LDLIBS)

Seek.o: Seek.cpp Seek.hpp Behavior.hpp
	$(CXX) $(CXXOPTS) -c Seek.cpp $(LDLIBS)

KinematicWander.o: KinematicWander.cpp KinematicWander.hpp Kinematic.hpp Behavior.hpp util.hpp
	$(CXX) $(CXXOPTS) -c KinematicWander.cpp $(LDLIBS)

KinematicArrive.o: KinematicArrive.cpp KinematicArrive.hpp Kinematic.hpp Behavior.hpp
	$(CXX) $(CXXOPTS) -c KinematicArrive.cpp $(LDLIBS)

KinematicFlee.o: KinematicFlee.cpp KinematicFlee.hpp Kinematic.hpp Behavior.hpp
	$(CXX) $(CXXOPTS) -c KinematicFlee.cpp $(LDLIBS)

KinematicSeek.o: KinematicSeek.cpp KinematicSeek.hpp Kinematic.hpp Behavior.hpp
	$(CXX) $(CXXOPTS) -c KinematicSeek.cpp $(LDLIBS)

pekomin.o: pekomin.cpp Triple.hpp
	$(CXX) $(CXXFLAGS) -c pekomin.cpp

Triple.o: Triple.cpp Triple.hpp
	$(CXX) $(CXXFLAGS) -c Triple.cpp

util.o: util.cpp util.hpp
	$(CXX) $(CXXFLAGS) -c util.cpp
