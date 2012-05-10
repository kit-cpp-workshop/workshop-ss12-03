/// ··· Inheritance ("Vererbung") ···
namespace Slide1 {
/// Eine Klasse kann von einer anderen "erben", und übernimmt dann all deren Attribute.
/// Die Syntax dafür ist wie folgt:

class ParentClass {
    // ...
};

class ChildClass : public ParentClass {
    // ...
};

}

namespace Slide2 {
/// Methoden können als "virtuell" deklariert werden.
/// Dann (und nur dann) kann die "Kind"-Klasse eine eigene Implementierung angeben.

class ParentClass {
public:
    virtual void theFunction() {
        // ... irgendetwas
    }
};

class ChildClass : public ParentClass {
public:
    virtual void theFunction() {
        // ... irgendetwas anderes
        /// theFunction() aus ParentClass wird *nicht* aufgerufen!
    };
};

}

namespace Slide3 {
/// Methoden und Attribute können als "protected" deklariert werden.
/// Dann können Klassen, die von der Klasse erben, auf diese zugreifen, für alle anderen
/// sind die Attribute aber quasi "private".

class ParentClass {
protected:
    int foo;
};

class ChildClass : public ParentClass {
public:
    void theFunction() {
        int bar = foo +3; // okay
    };
};

// angenommen, myobj ist vom Typ ChildClass
int bar = myobj.foo + 3; // Fehler

}

namespace Slide4 {
/// Von einer Kind- zu einer Basisklasse kommt man sehr einfach:

class ParentClass { };
class ChildClass : public ParentClass { };

ChildClass* child = new ChildClass();
ParentClass* childAsBase = child;

/// Anders herum benötigt man sogenannte "casts".
/// Beispiel: dynamic_cast prüft hier, ob "base" eine gültige "child"-Instanz ist;
/// wenn nicht, ist das Ergebis einfach "0".

ParentClass* base = new ParentClass();
ChildClass* baseAsChild = dynamic_cast<ChildClass*>(base);
/// Hier ist nun baseAsChild einfach "0".

ParentClass* base = ChildClass();
ChildClass* baseAsChild = dynamic_cast<ChildClass*>(base);
/// Hier ist baseAsChild eine gültige Instanz von ChildClass.

/// Ist man nicht sicher, ob der Cast funktioniert, so muss man das Ergebnis überprüfen:
// if ( baseAsChild ) {
//     // tu was mit baseAsChild
// }

/// Weitere cast-Typen: static_cast, reinterpret_cast [, const_cast]

}