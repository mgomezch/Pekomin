LDLIBS = -lm

all: pekomin

clean:
	rm -f *.gch *.o *.*~ *~ pekomin 

pekomin: pekomin.o Ent.o Triple.o Behavior.o Static.o Kinematic.o KinematicSeek.o KinematicFlee.o KinematicArrive.o KinematicWander.o
	g++ $(CXXOPTS) -o pekomin *.o $(LDLIBS)

KinematicWander.o: KinematicWander.cpp KinematicWander.hpp Kinematic.hpp util.hpp
	g++ $(CXXOPTS) -c KinematicWander.cpp $(LDLIBS)

KinematicArrive.o: KinematicArrive.cpp KinematicArrive.hpp Kinematic.hpp
	g++ $(CXXOPTS) -c KinematicArrive.cpp $(LDLIBS)

KinematicFlee.o: KinematicFlee.cpp KinematicFlee.hpp Kinematic.hpp
	g++ $(CXXOPTS) -c KinematicFlee.cpp $(LDLIBS)

KinematicSeek.o: KinematicSeek.cpp KinematicSeek.hpp Kinematic.hpp
	g++ $(CXXOPTS) -c KinematicSeek.cpp $(LDLIBS)

Kinematic.o: Kinematic.cpp Kinematic.hpp Static.hpp
	g++ $(CXXOPTS) -c Kinematic.cpp $(LDLIBS)

Static.o: Static.cpp Static.hpp Behavior.hpp
	g++ $(CXXOPTS) -c Static.cpp $(LDLIBS)

Behavior.o: Behavior.cpp Behavior.hpp Triple.hpp
	g++ $(CXXOPTS) -c Behavior.cpp $(LDLIBS)

pekomin.o: pekomin.cpp Triple.hpp
	g++ $(CXXOPTS) -c pekomin.cpp $(LDLIBS) 

Ent.o: Ent.cpp Ent.hpp Triple.hpp
	g++ $(CXXOPTS) -c Ent.cpp $(LDLIBS)

Triple.o: Triple.cpp Triple.hpp
	g++ $(CXXOPTS) -c Triple.cpp $(LDLIBS)

