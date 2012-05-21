void check();	// deklariert die Funktion
class MyIncompleteType;	// deklariert den Typen

class MyType	// definiert den Typen
{
public:
	int m;
	void test();
};

int main()
{
	check();	// OK, die Funktion wurde vorher deklariert
	MyIncompleteType m;	// Fehler, der Typ wurde NICHT voher definiert
	MyType mt;	// OK
	mt.test();	// OK, die Funktion wurde vorher deklariert
}

void check() { /* do something */ }
void MyType::test() { /* ... */ }
