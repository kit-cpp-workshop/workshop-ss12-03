#include "CParent.h"

class CChild
	: public CParent
{
public:
	double rot;
	
	void turn();
	void set();
	
	virtual void apply();
};
