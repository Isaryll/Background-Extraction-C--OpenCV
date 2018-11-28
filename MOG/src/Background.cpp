/*
 * Background.cpp
 *
 *  Created on: 19 de out de 2018
 *      Author: isa
 */

#include "Background.h"

/**
 * Initialize the main matrix with the frame's size.
 * @param frame first image from video
 * @return
 * @see
 */
Background::Background(const Mat& frame): lines(frame.rows), columns(frame.cols) {
	init(frame);
}

/**
 * Initialize the main matrix with the frame's pixel value.
 * @param frame first frame from video
 * @return      setup from matrix
 * @see         matrix
 */
void Background::init(const Mat& frame) {
	for (int i = 0; i < lines; i++)
		for(int j = 0; j < columns; j++)
			model[i][j].init(frame.at<Vec3b>(i, j));
}

/**
 * Update all the parameters from the matrix, get the best distributions for background and foreground.
 * @param frame each frame from input video
 * @return      background
 * @see         image background
 */
Mat Background::startB(const Mat& frame) {
	int dist = 0, flag = 0;
	update(frame);
	Mat bg(lines, columns,CV_8UC3);

	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < columns; j++) {
			bg.at<Vec3b>(i,j) = model[i][j].getBestDistributions(dist);
			
			for(int k = 0; k <= dist; k++){
				Vec3d temp = Vec3d(frame.at<Vec3b>(i,j)) - Vec3d(model[i][j].listOfDist[k].getMedia());
				
				if (norm(temp / 255) <= MATCHING2 * model[i][j].listOfDist[k].getDev()) {
					flag=1;
					break;
				}
			}
			
			if(flag == 0) // foreground
				segm.at<uchar>(i,j) = 255;
			else // background
				segm.at<uchar>(i,j) = 0;		
			flag = 0;
		}
	}

	return bg;
}

/**
 * Call the GList update function.
 * @param frame each frame from input video.
 * @return      updated main matrix 
 * @see
 */
void Background::update(const cv::Mat& frame) {
	for(int i = 0; i < lines; i++)
		for(int j = 0; j < columns; j++)
			model[i][j].update(frame.at<Vec3b>(i, j));
}

/**
 * Create the foreground image by subtraction mode.
 * @param frame each frame from input video.
 * @param background created background.
 * @return           created foreground.
 * @see
 */
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