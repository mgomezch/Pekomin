CC=gcc
CCOPTS=-Wall
CXX=g++
CXXOPTS=-Wall -std=gnu++0x
LD=ld
LDLIBS=-lm
LDLIBS=-lpng -lglut -lGLU -lGL -lX11 -lm # `sdl-config --cflags --libs` -lSDL_mixer -lSDL_image
LDFLAGS=


all: pekomin

distclean:
	rm -f *.gch *.o *~ Makefile tags pekomin

clean:
	rm -f *.gch Wander.o KinematicSeek.o KinematicArrive.o Align.o VelocityMatch.o Flee.o Face.o Separation.o main.o Player.o Triple.o parse.o util.o Ent.o Phantom.o LookWhereYoureGoing.o gl.o KinematicFlee.o game.o Flock.o Seek.o Actor.o Arrive.o KinematicWander.o RuntimePekomin.o Evade.o Pursue.o pekomin

pekomin: Wander.o KinematicSeek.o KinematicArrive.o Align.o VelocityMatch.o Flee.o Face.o Separation.o main.o Player.o Triple.o parse.o util.o Ent.o Phantom.o LookWhereYoureGoing.o gl.o KinematicFlee.o game.o Flock.o Seek.o Actor.o Arrive.o KinematicWander.o RuntimePekomin.o Evade.o Pursue.o
	$(CXX) $(CXXOPTS) -o pekomin Wander.o KinematicSeek.o KinematicArrive.o Align.o VelocityMatch.o Flee.o Face.o Separation.o main.o Player.o Triple.o parse.o util.o Ent.o Phantom.o LookWhereYoureGoing.o gl.o KinematicFlee.o game.o Flock.o Seek.o Actor.o Arrive.o KinematicWander.o RuntimePekomin.o Evade.o Pursue.o $(LDLIBS)

Wander.o: Wander.cpp Wander.hpp Mobile.hpp util.hpp Phantom.hpp Kinematic.hpp Ent.hpp Actor.hpp Behavior.hpp Triple.hpp Families.hpp DirectStatic.hpp Static.hpp DirectKinematic.hpp Dynamic.hpp
	$(CXX) $(CXXOPTS) -c Wander.cpp

KinematicSeek.o: KinematicSeek.cpp KinematicSeek.hpp Ent.hpp Kinematic.hpp Triple.hpp Behavior.hpp
	$(CXX) $(CXXOPTS) -c KinematicSeek.cpp

KinematicArrive.o: KinematicArrive.cpp KinematicArrive.hpp Ent.hpp DirectKinematic.hpp Triple.hpp Behavior.hpp
	$(CXX) $(CXXOPTS) -c KinematicArrive.cpp

Align.o: Align.cpp Align.hpp Mobile.hpp util.hpp Kinematic.hpp Ent.hpp Behavior.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c Align.cpp

VelocityMatch.o: VelocityMatch.cpp VelocityMatch.hpp Mobile.hpp Kinematic.hpp Ent.hpp Behavior.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c VelocityMatch.cpp

Flee.o: Flee.cpp Flee.hpp Mobile.hpp Kinematic.hpp Ent.hpp Behavior.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c Flee.cpp

Face.o: Face.cpp Face.hpp Mobile.hpp util.hpp Kinematic.hpp Ent.hpp Behavior.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c Face.cpp

Separation.o: Separation.cpp Separation.hpp Mobile.hpp Kinematic.hpp Ent.hpp Behavior.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c Separation.cpp

main.o: main.cpp Behaviors.hpp game.hpp gl.hpp RuntimePekomin.hpp parse.hpp Player.hpp Phantom.hpp util.hpp Align.hpp Arrive.hpp Evade.hpp Face.hpp Flee.hpp Flock.hpp KinematicArrive.hpp KinematicFlee.hpp KinematicSeek.hpp KinematicWander.hpp LookWhereYoureGoing.hpp Pursue.hpp Seek.hpp Separation.hpp VelocityMatch.hpp Wander.hpp Ent.hpp Actor.hpp Mobile.hpp Kinematic.hpp DirectKinematic.hpp Triple.hpp Behavior.hpp Families.hpp DirectStatic.hpp Static.hpp Dynamic.hpp
	$(CXX) $(CXXOPTS) -c main.cpp

Player.o: Player.cpp gl.hpp Player.hpp Mobile.hpp Ent.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c Player.cpp

Triple.o: Triple.cpp Triple.hpp
	$(CXX) $(CXXOPTS) -c Triple.cpp

parse.o: parse.cpp Behaviors.hpp game.hpp Mobile.hpp parse.hpp Player.hpp RuntimePekomin.hpp Align.hpp Arrive.hpp Evade.hpp Face.hpp Flee.hpp Flock.hpp KinematicArrive.hpp KinematicFlee.hpp KinematicSeek.hpp KinematicWander.hpp LookWhereYoureGoing.hpp Pursue.hpp Seek.hpp Separation.hpp VelocityMatch.hpp Wander.hpp Ent.hpp Actor.hpp Kinematic.hpp DirectKinematic.hpp Triple.hpp Behavior.hpp Families.hpp DirectStatic.hpp Static.hpp Dynamic.hpp
	$(CXX) $(CXXOPTS) -c parse.cpp

util.o: util.cpp util.hpp
	$(CXX) $(CXXOPTS) -c util.cpp

Ent.o: Ent.cpp Ent.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c Ent.cpp

Phantom.o: Phantom.cpp Phantom.hpp gl.hpp Actor.hpp Mobile.hpp Behavior.hpp Families.hpp Ent.hpp DirectStatic.hpp Static.hpp DirectKinematic.hpp Kinematic.hpp Dynamic.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c Phantom.cpp

LookWhereYoureGoing.o: LookWhereYoureGoing.cpp LookWhereYoureGoing.hpp Mobile.hpp util.hpp Kinematic.hpp Ent.hpp Behavior.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c LookWhereYoureGoing.cpp

gl.o: gl.cpp gl.hpp game.hpp Player.hpp Ent.hpp Mobile.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c gl.cpp

KinematicFlee.o: KinematicFlee.cpp KinematicFlee.hpp Ent.hpp Kinematic.hpp Triple.hpp Behavior.hpp
	$(CXX) $(CXXOPTS) -c KinematicFlee.cpp

game.o: game.cpp game.hpp Player.hpp Ent.hpp Mobile.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c game.cpp

Flock.o: Flock.cpp Flock.hpp Phantom.hpp Kinematic.hpp Mobile.hpp Actor.hpp Behavior.hpp Triple.hpp Ent.hpp Families.hpp DirectStatic.hpp Static.hpp DirectKinematic.hpp Dynamic.hpp
	$(CXX) $(CXXOPTS) -c Flock.cpp

Seek.o: Seek.cpp Seek.hpp Mobile.hpp Kinematic.hpp Ent.hpp Behavior.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c Seek.cpp

Actor.o: Actor.cpp Actor.hpp util.hpp Mobile.hpp Behavior.hpp Families.hpp Ent.hpp DirectStatic.hpp Static.hpp DirectKinematic.hpp Kinematic.hpp Dynamic.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c Actor.cpp

Arrive.o: Arrive.cpp Arrive.hpp Mobile.hpp Kinematic.hpp Ent.hpp Behavior.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c Arrive.cpp

KinematicWander.o: KinematicWander.cpp KinematicWander.hpp Ent.hpp util.hpp Kinematic.hpp Triple.hpp Behavior.hpp
	$(CXX) $(CXXOPTS) -c KinematicWander.cpp

RuntimePekomin.o: RuntimePekomin.cpp RuntimePekomin.hpp gl.hpp Actor.hpp Mobile.hpp Behavior.hpp Families.hpp Ent.hpp DirectStatic.hpp Static.hpp DirectKinematic.hpp Kinematic.hpp Dynamic.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c RuntimePekomin.cpp

Evade.o: Evade.cpp Evade.hpp Mobile.hpp Kinematic.hpp Ent.hpp Behavior.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c Evade.cpp

Pursue.o: Pursue.cpp Pursue.hpp Mobile.hpp Kinematic.hpp Ent.hpp Behavior.hpp Triple.hpp
	$(CXX) $(CXXOPTS) -c Pursue.cpp

