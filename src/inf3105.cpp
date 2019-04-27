/*
 * Sehoubo David
 * SEHK89100006
 */

#include "graphe.h"
#include "DocumentXML.h"
#include "Histoire.h"

#include <algorithm>
#include <math.h>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

vector<Histoire *> *lireDocuments(string a_nomFichier) {
	vector<Histoire *> *histoires = new vector<Histoire *>();
	DocumentXML *listeFichiers = lireFichierXML(a_nomFichier);

	Element *courrant = listeFichiers->racine();
	vector<Contenu *>::const_iterator it = courrant->begin();

	// trouver <liste>
	while (!(*it)->estElement()) ++it;
	courrant = (Element *) (*it);

	for (Contenu *contenu : *courrant) {
		if (contenu->estElement()) {
			Element *element = (Element *) contenu;

			DocumentXML *doc = lireFichierXML(element->attribut(string("fichier")));

			vector<Histoire *> *h = extraireHistoires(*doc);

			histoires->insert(histoires->end(), h->begin(), h->end());
		}
	}

	return histoires;
}

bool estCaractereMot(char c);

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <histoire à résumer>" << endl;
		exit(-1);
	}

	vector<Histoire *> *histoires = lireDocuments(string("listeDocument.xml")), *tmp = new vector<Histoire *>();
	Histoire *histoire = nullptr;
	string titre(argv[1]);

	while (!histoires->empty()) {
		Histoire *&h = histoires->back();
		histoires->pop_back();
		if (titre == h->titre() ||
		    (h->titre().find(titre) == 0 && titre.length() + 11 == h->titre().length()))
			tmp->push_back(h);
		else
			delete h;
	}

	if (tmp->empty()) {
		cerr << "Cette histoire n'est pas disponible" << endl;
		exit(-1);
	}

	tmp->back()->removeLast();
	histoire = tmp->back();
	tmp->pop_back();

	while (!tmp->empty()) {
		tmp->back()->removeLast();
		for (const auto &it : *tmp->back())
			histoire->ajouterPhrase(it);
		tmp->pop_back();
	}

	Graphe<Phrase> graphe;
	auto end = histoire->end();

	for (auto it = histoire->begin(); it != end; ++it)
		for (auto it2 = it + 1; it2 != end; ++it2)
			if (it->distance(*it2) != 0.0)
				graphe.ajouterAreteOrientee(*it, *it2);

	graphe.dijkstra(*histoire->begin(), *(--histoire->end()), 5);

	return EXIT_SUCCESS;
}
