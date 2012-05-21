class MyType
{
public:
	int m;
};


#include "MyType.h"

class MyDepType
{
public:
	void foobar();
	
private:
	MyType m;
};
