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

using namespace std;

// Le type S est le type utilisé pour identifier les sommets
template<class S>
class Graphe {
public:
		// Interface public pour créer le graphe

		void ajouterAreteOrientee(const S &s1, const S &s2);

		void dijkstra(S, S, int);

private:
		struct Sommet {
				bool visite = false;
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

/*
 * Cette méthode me permet de compter le nombre de noeuds parents depuis un noeud p
 */
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

/*
 * Au lieu de d'utiliser l'operateur [], qui renvoie 0, cette méthode me renvoie l'infinie dans le cas où le noeud n'a
 * pas été inséré dans la map. Au début de dijkstra les distances sont initialisées à l'infini
 */
template<class S>
const double Graphe<S>::getDistance(const map<const S, double> &m, const S &key) {
	auto it = m.find(key);
	if (it == m.end())
		return INFINITY;
	return it->second;
}

/* Cette méthode se charge de construire un chemin de la taille qui lui est donnée avec une modification de l'algo de
 * dijkstra.
 */
template<class S>
void Graphe<S>::dijkstra(S debut, const S fin, int min_path_length) {
	map<S, S> parents;
	priority_queue<pair<double, S>, vector<pair<double, S>>, Graphe::comparator> file;
	// Cette structure permet de garder la distance la plus courte toujours au top
	map<const S, double> dist;
	file.push(make_pair(0.0, debut));
	dist[debut] = 0.0;

	while (!file.empty()) {
		const pair<double, S> p = file.top();
		file.pop();

		if (p.second == fin) break;

		int c_p = countPath(parents, p.second);
		double u = getDistance(dist, p.second);

		//cout << file.size() << endl;

		//ne devrait normalement jamais arrivé
		if (u == INFINITY) {
			cerr << "distance infinie" << endl;
			exit(-1);
		}

		Sommet &s = sommets.find(p.second)->second;

		if (s.visite) continue;
		s.visite = true;

		for (S it : s.voisins) {
			double _cout = it.distance(p.second);
			int c_it = countPath(parents, it);
			double d = u + _cout;
			if (it != fin && c_it == c_p && c_p < min_path_length - 1) {
				Sommet &tmp = sommets[it];
				if (!tmp.visite) {
					parents[it] = p.second;
					dist[it] = d;
					file.push(make_pair(d, it));
				}
			} else if (it == fin && d < getDistance(dist, it) && c_p == min_path_length - 1) {
				parents[it] = p.second;
				dist[it] = d;
				file.push(make_pair(d, it));
			}
		}
		/*
		if (c_it <= c_p && d < Dw &&
				((it != fin && c_p < min_path_length - 1) || (it == fin && c_p >= min_path_length - 1))) {
			parents[it] = p.second;
			dist[it] = d;
			file.push(make_pair(d, it));
		} else if (it != fin && c_it == 1) {
			parents[it] = p.second;
			dist[it] = d;
			file.push(make_pair(d, it));
		}
	}*/
	}

	S tmp = fin;
	typename map<S, S>::iterator it;
	vector<S> res;
	//double r = 0;

	do {
		res.push_back(tmp);
		it = parents.find(tmp);
		if (it == parents.end()) break;
		//cout << *tmp << endl;
		//double t = tmp.distance(it->second);
		//cout << t << endl;
		//r += t;
		tmp = it->second;
	} while (it != parents.end());

	//cout << "taille: " << res.size() << endl;
	//cout << r << endl;
	//cout << "distance totale: " << dist[fin] << endl;

	for (auto it2 = res.rbegin(); it2 != res.rend(); it2++)
		cout << *it2 << endl;
}

#endif
