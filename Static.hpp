#ifndef _STATIC_HPP
#define _STATIC_HPP

#include "Ent.hpp"

using namespace std;

class Static: public Ent {
	public:

	Static() {}
	
	Static(Triple p, double o) : Ent(p,o) {}
	
	string type();
	
	Triple asVector();

};

#endif
