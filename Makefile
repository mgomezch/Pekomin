CC=gcc
CCOPTS=-Wall
CXX=g++
CXXOPTS=-Wall -std=gnu++0x
LD=ld
LDLIBS=-lm
LDLIBS=-lpng -lglut -lGLU -lGL -lX11 -lm `sdl-config --cflags --libs` -lSDL_mixer -lSDL_image
LDFLAGS=


all: pekomin

distclean:
	rm -f *.gch *.o *~ Makefile pekomin

clean:
	rm -f *.gch Wander.o KinematicSeek.o KinematicArrive.o Static.o Align.o VelocityMatch.o Kinematic.o Flee.o Face.o Separation.o main.o Triple.o util.o Ent.o LookWhereYoureGoing.o Direct.o gl.o KinematicFlee.o Seek.o Actor.o Arrive.o Dynamic.o KinematicWander.o RuntimePekomin.o Evade.o Pursue.o pekomin

pekomin: Wander.o KinematicSeek.o KinematicArrive.o Static.o Align.o VelocityMatch.o Kinematic.o Flee.o Face.o Separation.o main.o Triple.o util.o Ent.o LookWhereYoureGoing.o Direct.o gl.o KinematicFlee.o Seek.o Actor.o Arrive.o Dynamic.o KinematicWander.o RuntimePekomin.o Evade.o Pursue.o
	$(CXX) $(CXXOPTS) -o pekomin Wander.o KinematicSeek.o KinematicArrive.o Static.o Align.o VelocityMatch.o Kinematic.o Flee.o Face.o Separation.o main.o Triple.o util.o Ent.o LookWhereYoureGoing.o Direct.o gl.o KinematicFlee.o Seek.o Actor.o Arrive.o Dynamic.o KinematicWander.o RuntimePekomin.o Evade.o Pursue.o $(LDLIBS)

Wander.o: Wander.cpp Wander.hpp Mobile.hpp util.hpp Face.hpp Ent.hpp Kinematic.hpp Triple.hpp Behavior.hpp
	$(CXX) $(CXXOPTS) -c Wander.cpp

KinematicSeek.o: KinematicSeek.cpp KinematicSeek.hpp Ent.hpp Kinematic.hpp Triple.hpp Behavior.hpp
	$(CXX) $(CXXOPTS) -c KinematicSeek.cpp

KinematicArrive.o: KinematicArrive.cpp KinematicArrive.hpp Ent.hpp Kinematic.hpp Triple.hpp Behavior.hpp
	$(CXX) $(CXXOPTS) -c KinematicArrive.cpp

Static.o: Static.cpp Static.hpp Behavior.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c Static.cpp

Align.o: Align.cpp Align.hpp Mobile.hpp Kinematic.hpp Ent.hpp Behavior.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c Align.cpp

VelocityMatch.o: VelocityMatch.cpp VelocityMatch.hpp Mobile.hpp Kinematic.hpp Ent.hpp Behavior.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c VelocityMatch.cpp

Kinematic.o: Kinematic.cpp Kinematic.hpp Behavior.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c Kinematic.cpp

Flee.o: Flee.cpp Flee.hpp Mobile.hpp Kinematic.hpp Ent.hpp Behavior.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c Flee.cpp

Face.o: Face.cpp Face.hpp Mobile.hpp Kinematic.hpp Ent.hpp Behavior.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c Face.cpp

Separation.o: Separation.cpp Separation.hpp Mobile.hpp Kinematic.hpp Ent.hpp Behavior.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c Separation.cpp

main.o: main.cpp game.hpp gl.hpp Align.hpp Arrive.hpp Evade.hpp Face.hpp Flee.hpp Kinematic.hpp KinematicArrive.hpp KinematicFlee.hpp KinematicSeek.hpp KinematicWander.hpp LookWhereYoureGoing.hpp Pursue.hpp Seek.hpp Separation.hpp Triple.hpp VelocityMatch.hpp Wander.hpp Behavior.hpp
	$(CXX) $(CXXOPTS) -c main.cpp

Triple.o: Triple.cpp Triple.hpp
	$(CXX) $(CXXOPTS) -c Triple.cpp

util.o: util.cpp util.hpp
	$(CXX) $(CXXOPTS) -c util.cpp

Ent.o: Ent.cpp Ent.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c Ent.cpp

LookWhereYoureGoing.o: LookWhereYoureGoing.cpp LookWhereYoureGoing.hpp Mobile.hpp Kinematic.hpp Ent.hpp Behavior.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c LookWhereYoureGoing.cpp

Direct.o: Direct.cpp Direct.hpp Behavior.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c Direct.cpp

gl.o: gl.cpp gl.hpp game.hpp
	$(CXX) $(CXXOPTS) -c gl.cpp

KinematicFlee.o: KinematicFlee.cpp KinematicFlee.hpp Ent.hpp Kinematic.hpp Triple.hpp Behavior.hpp
	$(CXX) $(CXXOPTS) -c KinematicFlee.cpp

Seek.o: Seek.cpp Seek.hpp Mobile.hpp Kinematic.hpp Ent.hpp Behavior.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c Seek.cpp

Actor.o: Actor.cpp Actor.hpp Mobile.hpp Behavior.hpp Ent.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c Actor.cpp

Arrive.o: Arrive.cpp Arrive.hpp Mobile.hpp Kinematic.hpp Ent.hpp Behavior.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c Arrive.cpp

Dynamic.o: Dynamic.cpp Dynamic.hpp Behavior.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c Dynamic.cpp

KinematicWander.o: KinematicWander.cpp KinematicWander.hpp Ent.hpp util.hpp Kinematic.hpp Triple.hpp Behavior.hpp
	$(CXX) $(CXXOPTS) -c KinematicWander.cpp

RuntimePekomin.o: RuntimePekomin.cpp RuntimePekomin.hpp gl.hpp Actor.hpp Mobile.hpp Behavior.hpp Ent.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c RuntimePekomin.cpp

Evade.o: Evade.cpp Evade.hpp Mobile.hpp Kinematic.hpp Ent.hpp Behavior.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c Evade.cpp

Pursue.o: Pursue.cpp Pursue.hpp Mobile.hpp Kinematic.hpp Ent.hpp Behavior.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c Pursue.cpp

