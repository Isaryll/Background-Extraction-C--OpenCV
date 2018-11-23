/*
 * Gaussian.h
 *
 *  Created on: 19 de out de 2018
 *      Author: isa
 */

#ifndef INCLUDE_GAUSSIAN_H_
#define INCLUDE_GAUSSIAN_H_

#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <conf.h>

using namespace cv;
using namespace std;

class Gaussian {
	private:
		Vec3b media;
		double dev;
		double weight;

	public:
		Gaussian(const Vec3b& media = 0, const double& dev = 0.2, const double& weight = 1/100);
        inline void	setMedia (const Vec3b&	m) { media = m;  }
		inline void setWeight (const double& w) { weight = w; }
		void setDev (const double&	d) { dev = d; }				
        inline Vec3b getMedia() const { return media; }
		inline double getDev() const { return dev; }
		inline double getWeight() const { return weight; }
		double prob (const Vec3b& current) const;
};

#endif /* INCLUDE_GAUSSIAN_H_ */
