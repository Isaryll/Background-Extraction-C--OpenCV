/*
 * Gaussian.cpp
 *
 *  Created on: 22 de out de 2018
 *      Author: isa
 */

#include <Gaussian.h>

/**
 * Function description.
 * @param
 * @param
 * @param
 * @return
 * @see
 */
Gaussian::Gaussian(const Vec3b& media, const double& dev, const double& weight): media(media), weight(weight) {
	setDev(dev);
} 

/**
 * Function description.
 * @param
 * @return
 * @see
 */
double Gaussian::prob(const cv::Vec3b& current) {
	Vec3d temp = Vec3d(current) - Vec3d(media);
	temp /= 255;
	
	if(dev < DEVSAT) 
		dev = DEVSAT;
	
	double num = exp(-0.5 * (temp[0] * temp[0] + temp[1] * temp[1] + temp[2] * temp[2])/(dev*dev));
	double den = PART * sqrt(dev*dev*dev*dev*dev*dev);
	return num/den;
}
