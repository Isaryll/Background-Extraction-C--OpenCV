/*
 * Background.cpp
 *
 *  Created on: 19 de out de 2018
 *      Author: isa
 */

#include "Background.h"

Background::Background(const Mat& frame): lines(frame.rows), columns(frame.cols) {
	init(frame);
}

Mat Background::startB(const Mat& frame) {
	update(frame);
	Mat bg(lines, columns,CV_8UC3);

	for (int i = 0; i < lines; i++)
		for (int j = 0; j < columns; j++)
			bg.at<Vec3b>(i,j) = model[i][j].getBestDistributions();

	return bg;
}

void Background::init(const Mat& frame)
{
	if(!lines && !columns) {
		lines = frame.rows;
		columns= frame.cols;
	}
	model = vector< vector<GList> >(lines, vector<GList>(columns));

	for (int i = 0; i < lines; i++)
		for(int j = 0; j < columns; j++)
			model[i][j].init(frame.at<Vec3b>(i, j));
}

void Background::update(const cv::Mat& frame) {
	int flag = 0;
	
	for(int i = 0; i < lines; i++) {
		for(int j = 0; j < columns; j++) {
			flag = model[i][j].update(frame.at<Vec3b>(i, j));
			if(flag == 0) // foreground
				segm.at<uchar>(i,j) = 0;
			else // background
				segm.at<uchar>(i,j) = 255;
		}
	}
}

Mat Background::foreground(const Mat& frame, const Mat& background) {
	Mat foreground(lines, columns, CV_8UC3);
	cvtColor(Mat(background - frame), foreground, CV_BGR2GRAY);
	
	for(int i = 0; i < lines; i++){
		for (int j = 0; j < columns; j++){
			if( foreground.at<uchar>(i,j) > LTHRESHOLD)
				foreground.at<uchar>(i,j) = 255;
			else
				foreground.at<uchar>(i,j) = 0;
		}
	}
	return foreground;
}