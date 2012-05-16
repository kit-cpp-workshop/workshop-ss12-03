#include <string>
using namespace std;

class CParent
{
public:
	string name;
	int pos;
	
	void print();
	void set();
	
	virtual bool check();
	virtual void apply();
};
