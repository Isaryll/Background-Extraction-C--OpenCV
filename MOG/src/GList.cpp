/*
 * GList.cpp
 *
 *  Created on: 22 de out de 2018
 *      Author: isa
 */

#include "GList.h"

GList::GList():listOfDist(K) {}

int GList::update(const Vec3b& current) {
	Gaussian gaussian(current);
	int flag = 0;
	double sum = 0;

	for(int i = 0; i < K; i++) {
		Vec3d temp = Vec3b(current - listOfDist[i].getMedia());
		if (sqrt(norm(temp)) <= MATCHING * listOfDist[i].getDev()) { // background
			listOfDist[i].setWeight((1-ALPHA) * listOfDist[i].getWeight() + ALPHA);
			double ro = ALPHA * listOfDist[i].prob(current);
			listOfDist[i].setMedia((1-ro) * listOfDist[i].getMedia() + ro * current);
			Mat mat(temp);
			listOfDist[i].setDev((1-ro) * listOfDist[i].getDev() + ro * Mat(mat.t() * mat).at<double>(0,0));
			flag++;			
		} else { // foreground
			listOfDist[K-1].setWeight(WEIGHT);
			listOfDist[K-1].setMedia(current);
			listOfDist[K-1].setDev(DEVIATTION);
		}

	}

	sort();

	for (int i = 0; i < K; i++) {
		sum += listOfDist[i].getWeight();
	}

	for (int i = 0; i < K; i++) {
		listOfDist[i].setWeight(listOfDist[i].getWeight()/sum);
	}

	return flag;
}

double GList::prob(const Vec3b& current) {
	double prob = 0;

	for (int i = 0; i < K; i++) {
		prob += listOfDist[i].prob(current) * listOfDist[i].getWeight();
	}

	return prob;
}

void GList::sort() {

	for (int i = 0; i < K-1; i++) {
		if((listOfDist[i].getWeight()/listOfDist[i].getDev()) < (listOfDist[i+1].getWeight()/listOfDist[i+1].getDev())) {
			Gaussian temp = listOfDist[i];
			listOfDist[i] = listOfDist[i+1];
			listOfDist[i+1] = temp;
		}
	}
}

void GList::init(const Vec3b& current) {

	for (int i = 0; i < K; i++){
		listOfDist[i] = Gaussian(current);
	}
}

Vec3b GList::getBestDistributions() {
	int dist = 1;
	double thresh = 0;
	double sum = 0;
	double weight = 0;
	Vec3b final;

	for(int i = 0; i < K; i++) {
		thresh += listOfDist[i].getWeight();
		if(thresh <= THRESHOLD) {
			dist++;
		}
	}

	for (int i = 0; i < dist; i++) {
		sum += listOfDist[i].getWeight();
	}

	for(int i = 0; i < dist; i++) {
		weight = listOfDist[i].getWeight()/sum;
		final += listOfDist[i].getMedia() * weight;
	}

	/*for(int i = 0; i < dist; i++) {
		final += listOfDist[i].getDev() * listOfDist[i].getWeight();
	}*/

	return final;
}
