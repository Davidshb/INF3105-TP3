/*  INF3105 - Structures de données et algorithmes
    Lab 11 -- Graphes / Représentations et algorithmes de base
    http://ericbeaudry.uqam.ca/INF3105/lab11/
*/
#if !defined(__GRAPHE_H__)
#define __GRAPHE_H__

#include <queue>
#include <map>
#include <vector>
#include <iostream>
#include <utility>
#include <math.h>

#define MIN_PATH_LENGTH 5

using namespace std;

// Le type S est le type utilisé pour identifier les sommets
template<class S>
class Graphe {
public:
		// Interface public pour créer le graphe

		void ajouterAreteOrientee(const S &s1, const S &s2);

		void dijkstra(S, S);

private:
		struct Sommet {
				vector<S> voisins;// ensemble des sommets accessibles via les arêtes sortantes du sommet.
				// Cela est légèrement différent de la page 120 des notes de cours.
				// C'est voulu, car ici les arêtes ne sont pas étiquetées par un poids (ex: distance).
				// Pour attacher une étiquette, il suffirait de modifier pour : map<S, A> sortants;
		};

		class comparator {
		public:
				bool operator()(pair<double, S> &p1, pair<double, S> &p2) {
					return p1.first > p2.first;
				}
		};

		map<S, Sommet> sommets; // identification --> sommet

public:
private:
		const double getDistance(const map<const S, double> &, const S &);

		int countPath(const map<S, S> &, S) const;
};

template<class S>
void Graphe<S>::ajouterAreteOrientee(const S &s1, const S &s2) {
	sommets[s1].voisins.push_back(s2);
}

template<class S>
int Graphe<S>::countPath(const map<S, S> &m, S p) const {
	int res = 1;
	typename map<S, S>::const_iterator it;
	while ((it = m.find(p)) != m.end()) {
		res++;
		p = it->second;
	}

	return res;
}

template<class S>
const double Graphe<S>::getDistance(const map<const S, double> &m, const S &key) {
	auto it = m.find(key);
	if (it == m.end())
		return INFINITY;
	return it->second;
}

template<class S>
void Graphe<S>::dijkstra(S debut, const S fin) {
	map<S, S> parents;
	priority_queue<pair<double, S>, vector<pair<double, S>>, Graphe::comparator> file;
	map<const S, double> dist;
	file.push(make_pair(0.0, debut));
	dist[debut] = 0.0;

	while (!file.empty()) {
		const pair<double, S> p = file.top();
		file.pop();
		int c = countPath(parents, p.second);
		double u = getDistance(dist, p.second);
		//cout << file.size() << endl;

		if (u == INFINITY) { //ne devrait normalement jamais arrivé
			cerr << "distance infinie" << endl;
			break;
		}

		Sommet &s = sommets.find(p.second)->second;
		map<const S, double> dist2;

		for (S it : s.voisins) {
			double _cout = it.distance(p.second);
			if (_cout == 0.0) continue;

			int c_ = countPath(parents, it);
			double d = u + _cout;
			//double Dw = getDistance(dist, it);

			if (c_ < c && ((it != fin && c < MIN_PATH_LENGTH - 1 && d < getDistance(dist, it)) ||
			               (it == fin && c >= MIN_PATH_LENGTH - 1 && d < getDistance(dist, it)))) {
				parents[it] = p.second;
				dist[it] = d;
				file.push(make_pair(d, it));
			} else if ((it != fin && c < MIN_PATH_LENGTH - 1 && _cout < getDistance(dist2, it)) ||
			           (it == fin && c >= MIN_PATH_LENGTH - 1 && _cout < getDistance(dist2, it))) {
				parents[it] = p.second;
				dist2[it] = _cout;
				dist[it] = d;
				file.push(make_pair(d, it));
			}
		}
	}

	S *tmp = &fin;
	typename map<S, S>::iterator it;
	vector<S> res;

	do {
		res.
						push_back(*tmp);
		cout << *tmp <<
		     endl;
		it = parents.find(*tmp);
		tmp = &it->second;
	} while (it != parents.

					end()

					);

	for (
		S &s
					: res)
		cout << s <<
		     endl;
}

#endif
