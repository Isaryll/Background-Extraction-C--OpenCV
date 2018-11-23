/*
 * Background.h
 *
 *  Created on: 19 de out de 2018
 *      Author: isa
 */

#ifndef INCLUDE_BACKGROUND_H_
#define INCLUDE_BACKGROUND_H_

#include <vector>
#include <GList.h>

#include <conf.h>

using namespace std;

class Background {
	private:
		vector< vector<GList> > model;
		int lines, columns;

	public:
		Mat segm = Mat (120, 160, CV_8UC1);
		Background (): lines(0), columns(0){};
		Background (const Mat& frame);
		void init   (const Mat& frame);
		void update (const Mat& frame);
		Mat foreground(const Mat& frame, const Mat& background);
		Mat background();
		Mat startB(const Mat& frame);
};

#endif /* INCLUDE_BACKGROUND_H_ */
