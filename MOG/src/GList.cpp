/*
 * GList.cpp
 *
 *  Created on: 22 de out de 2018
 *      Author: isa
 */

#include "GList.h"

/**
 * Define the List size.
 * @param 
 * @return
 * @see
 */
GList::GList():listOfDist(K) {}

/**
 * Update in all iterations each necessary list's position.
 * Sort and normalize the list.
 * @param current current pixel value
 * @return
 * @see
 */
void GList::update(const Vec3b& current) {
	double sum = 0, i = 0;

	for(i = 0; i < K; i++) {
		Vec3d temp = Vec3d(current) - Vec3d(listOfDist[i].getMedia());
		temp /= 255;

		if (norm(temp) <= MATCHING * listOfDist[i].getDev()) { // background
			listOfDist[i].setWeight((1-ALPHA) * listOfDist[i].getWeight() + ALPHA);
			double max = listOfDist[i].prob(listOfDist[i].getMedia());
			double ro = ALPHA * listOfDist[i].prob(current)/max;
			listOfDist[i].setMedia((1-ro) * listOfDist[i].getMedia() + ro * current);
			double dev = listOfDist[i].getDev();
			dev = (1 - ro) * dev*dev + ro * (temp[0]* temp[0]+ temp[1] * temp[1]+ temp[2] * temp[2]);
			dev = sqrt(dev);
			listOfDist[i].setDev(dev);
			break;
		}
	}

	if (i == K) {
		listOfDist[K - 1].setWeight(WEIGHT);
		listOfDist[K - 1].setMedia(current);
		listOfDist[K - 1].setDev(DEVIATTION);
	}

	for (int i = 0; i < K; i++) {
		sum += listOfDist[i].getWeight();
	}

	for (int i = 0; i < K; i++) {
		listOfDist[i].setWeight(listOfDist[i].getWeight()/sum);
	}

	sort();
}

/**
 * Calcule the pixel value from prob function.
 * @param current current pixel value.
 * @return        prob value
 * @see
 */
double GList::prob(const Vec3b& current) {
	double prob = 0;

	for (int i = 0; i < K; i++) {
		prob += listOfDist[i].prob(current) * listOfDist[i].getWeight();
	}

	return prob;
}

/**
 * Sort the main list.
 * @param
 * @return
 * @see
 */
void GList::sort() {
	for(int j=0; j<K-1; j++)
	for (int i = 0; i < K-1; i++) {
		if((listOfDist[i].getWeight()/listOfDist[i].getDev()) < (listOfDist[i+1].getWeight()/listOfDist[i+1].getDev())) {
			Gaussian temp = listOfDist[i];
			listOfDist[i] = listOfDist[i+1];
			listOfDist[i+1] = temp;
		}
	}
}

/**
 * Initialize each list from the main matrix.
 * @param current current pixel value.
 * @return
 * @see
 */
void GList::init(const Vec3b& current) {
	for (int i = 0; i < K; i++){
		listOfDist[i] = Gaussian(current);
	}
}

/**
 * Get the best distributions from the list, based on the Threshold.
 * @param distr number of valid distributions
 * @return      final value from the media.
 * @see
 */
Vec3b GList::getBestDistributions(int &distr) {
	int i = 0;
	double thresh = 0;
	Vec3b final = {0,0,0};
	
	for(i = 0; i < K; i++) {
		thresh += listOfDist[i].getWeight();
		if (thresh > THRESHOLD)
			break;
	}

	if (i >= K)
		i = K-1;

	for(int j = 0; j <= 0; j++) {
		final += listOfDist[j].getMedia();
	}

	distr = i;
	
	return final;
}