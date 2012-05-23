# Workshop 11. Mai 2012

## Inhalt

Roter Faden: Objektorientierung

- (einfache) Vererbung
- virtual functions
- (einfache) Type-Casts in einer Klassen-Hierarchie
- mehr zu member access control (protected)
- Anwendung von Objektorientierung

### Folien zum Vortrag

Die Vortragsfolien stehen als [PDF](https://github.com/downloads/kit-cpp-workshop/workshop-ss12-03/slides.pdf) zum Download bereit. Außerdem liegt der LaTeX-Quellcode zu den Folien im Ordner `slides`.

### Screencast

Eine Aufzeichnung des Vortrags steht zum [Download](http://ubuntuone.com/2lthL8UEWij5CbLh3vPqTx) bereit. Aufgrund technischer Schwierigkeiten lässt die Bildqualität leider dieses Mal etwas zu wünschen übrig.

 - ab 00:00 Namespaces
 - ab 03:30 Einführung in das Thema des Workshops
 - ab 04:50 Vererbung
 - ab 15:34 Erläuterung des Bitmap24-Frameworks
 - ab 36:43 Vorstellung der Aufgaben

### Addenda

Nachdem das ganze nicht so toll gelaufen ist und auch keine Zeit mehr für eine ordentliche Dokumentation des Bitmap-Frameworks blieb, hier vier Nachträge zum Workshop:

* [Doxygen-Dokumentation des Bitmap-Frameworks](https://github.com/downloads/kit-cpp-workshop/workshop-ss12-03/bitmap-framework-doc-html.zip)
* [Kurze Übersicht über das Bitmap-Framework](https://github.com/downloads/kit-cpp-workshop/workshop-ss12-03/addendum-bmp.pdf)
* [Referenz zur Vererbung](https://github.com/downloads/kit-cpp-workshop/workshop-ss12-03/addendum-inheritance.pdf)
* [Etwas mehr zu Headern](https://github.com/downloads/kit-cpp-workshop/workshop-ss12-03/addendum-header.pdf)

## Aufgaben

Sendet, nachdem ihr alle Aufgaben abgearbeitet habt, einen Pull-Request an das Workshop-Repository. Stellt sicher, dass ihr vorher alle eure Änderungen in euren Fork übertragen habt. Nennt euren Workshop-Betreuer im Text des Pull-Requests, einer der Betreuer (bevorzugt der genannte) wird dann eure Lösungen durchsehen, kommentieren und nach Abschluss des Reviews den Pull-Request als abgelehnt markieren.


ACHTUNG: Ziel ist, dass die Instanzen in Aufgabe 2 nach dem Initialisieren über das IBatchDrawable-Interface verwendet werden können, und zwar auf beliebige BatchBitmap24-Instanzen.


### Aufgabe 1:
Implementiere (jeweils) einen Algorithmus, um:
- Ein Bitmap24 mit einer Farbe zu füllen.
- Eine Linie in ein Bitmap24 zu zeichnen.


### Aufgabe 2:
Verwende RelativeCoordinate!
Schreibe (jeweils) Klassen, die von IBatchDrawable erben. Die Instanzen der Klassen sollen (jeder Punkt eine eigene Klasse):
- Ein BatchBitmap24 mit seiner aktuellen Farbe füllen.
- Eine Linie in ein BatchBitmap24 zeichnen, von der aktuellen Position zu einer Koordinate (Paramter) - die aktuelle Position des BatchBitmap24 soll anschließend der Endpunkt der Linie sein.


### Aufgabe 3:
Verwende RelativeCoordinate!
Schreibe (jeweils) Klassen, deren Instanzen (jeder Punkt eine eigene Klasse):
- Ein Dreieck an der aktuellen Position zeichnen.
- Ein Rechteck an der aktuellen Position zeichnen.


### Bonusaufgaben:
- das ganze noch für Kreise
- Bezierkurven
- zeichne Schrödingers Katze
