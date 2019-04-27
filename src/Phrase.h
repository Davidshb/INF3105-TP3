/*
 * Phrase.h
 *
 *  Created on: 2017-04-11
 *      Author: boust_000
 */

#ifndef PHRASE_H_
#define PHRASE_H_


#include <functional>
#include <string>

using namespace std;

class Phrase {
private :
protected :
		int _nMot;
		string _ordonnee;
public :
		string _original;
		Phrase(void);

		Phrase(string a_original);

		Phrase(const Phrase &a_phrase);

		virtual ~Phrase(void);

		int nMot(void) const;

		int nLettre(void) const;

		double rougeW_ord(const Phrase &, function<double(double)>) const;

		double distance(const Phrase &) const;

		bool operator<(const Phrase &) const;

		bool operator!=(const Phrase&) const;

		bool operator==(const Phrase&) const;

		friend ostream &operator<<(ostream &a_out, const Phrase &a_phrase);
};


#endif /* PHRASE_H_ */
