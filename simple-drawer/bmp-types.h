#ifndef H_BMPTYPES
#define H_BMPTYPES




/** \file bmp-types.h
 * internal header for basic (integer) file types
 *
 * ACHTUNG TEILNEHMER!!!!
 *
 * Diese Datei ist nur ein interner Header, welcher vom Bitmap-Framework ver-
 * wendet wird.
 * Er liefert Datentypen, die an verschiedenen Stellen intern benötigt werden.
 * Du musst diesen Header NICHT selbst inkludieren, er wird schon an die
 * Stellen eingebunden, wo er benötigt wird.
 *
 * EINFACH NICHT WEITER BEACHTEN!
 * (notwendig, aber für die Bearbeitung der Aufgaben irrelevant)
 */


#include "least-types.h"

namespace bmp
{
	typedef unsigned char byte;

	typedef least_types :: least<  signed, 16>::type     int_least16_t;
	typedef least_types :: least<unsigned, 16>::type    uint_least16_t;
	typedef least_types :: least<  signed, 32>::type     int_least32_t;
	typedef least_types :: least<unsigned, 32>::type    uint_least32_t;
}




#endif // H_BMPTYPES