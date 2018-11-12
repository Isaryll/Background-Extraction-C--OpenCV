/*
 * GList.h
 *
 *  Created on: 19 de out de 2018
 *      Author: isa
 */

#ifndef INCLUDE_GLIST_H_
#define INCLUDE_GLIST_H_

#include <conf.h>
#include <Gaussian.h>
#include <vector>

using namespace std;

class GList {
private:
	vector<Gaussian> listOfDist;

public:
	GList();

	void update (const Vec3b& current);
	double prob (const Vec3b& current);
	void sort ();
	Vec3b getBestDistributions ();
	void init (const Vec3b& current);
};

#endif /* INCLUDE_GLIST_H_ */
