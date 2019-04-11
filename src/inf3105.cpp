
#include "DocumentXML.h"
#include "Histoire.h"

#include <algorithm>
#include <math.h>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

vector< Histoire *> * lireDocuments( string a_nomFichier ) {
    vector<Histoire *> * histoires = new vector< Histoire * >();
    DocumentXML * listeFichiers = lireFichierXML( a_nomFichier );

    Element * courrant = listeFichiers->racine();
    vector< Contenu * >::const_iterator it = courrant->begin();

    // trouver <liste>
    while( ! ( * it )->estElement() ) ++ it;
    courrant = ( Element * )( * it );

    for( Contenu * contenu : * courrant ) {
        if( contenu->estElement() ) {
            Element * element = ( Element * )contenu;

            DocumentXML * doc = lireFichierXML( element->attribut( string( "fichier" ) ) );

            vector<Histoire *> * h = extraireHistoires( * doc );

            histoires->insert( histoires->end(), h->begin(), h->end() );
        }
    }

    return histoires;
}

bool estCaractereMot( char c );

int main() {
    vector<Histoire *> * histoires = lireDocuments( string( "listeDocument.xml" ) );

	
}

