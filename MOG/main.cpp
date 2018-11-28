/*
 * main.cpp
 *
 *  Created on: 19 de out de 2018
 *      Author: isa
 */

//OpenCV
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>
//C
#include <stdio.h>
//C++
#include <iostream>
//Project
#include "conf.h"
#include <Background.h>

using namespace cv;
using namespace std;

int keyboard;

void processVideo(char* filename);

/**
 * Main function. Represents the verifications about the file description.
 * Includes a function about the video processing.
 * @param argc argument about the file description
 * @param argv argument about the file name
 * @return     closes the program
 * @see        an image by frame
 */
int main(int argc, char* argv[]) {

    if(argc != 3) {
        cerr << "Incorret input list" << endl;
        cerr << "exiting..." << endl;
        return EXIT_FAILURE;
    }

    namedWindow("Frame");
    namedWindow("Background");
    namedWindow("Segmentation By Subtraction");
    namedWindow("Segmentation By Match");

    if(strcmp(argv[1], "-vid") == 0) {
    	processVideo(argv[2]);
    }
    else {
        cerr << "Please, check the input parameters." << endl;
        cerr << "Exiting..." << endl;
        return EXIT_FAILURE;
    }

    destroyAllWindows();
    return EXIT_SUCCESS;
}


/**
 * That function represents all the process for the background subtraction/segmentation.
 * Needs to call Background Class. Saves a video result.
 * @param filename video name
 * @return         void
 * @see            background subtraction
 */
void processVideo(char* filename) {
	VideoCapture capture(filename);
	
	if(!capture.isOpened()) {
		cerr << "Unable to open video file: " << filename << endl;
		exit(EXIT_FAILURE);
    }

	Mat frame;
	Mat background;
	capture >> frame;
	Background model(frame);
	VideoWriter out_capture("output.avi", CV_FOURCC('M','J','P','G'), 30, Size(160,120));

	while(true) {
		if(!capture.read(frame)) {
			cerr << "Unable to read next frame." << endl;
			cerr << "Exiting..." << endl;
			exit(EXIT_FAILURE);
		}

		GaussianBlur(frame, frame, Size(3, 3), 1.7);

		background = model.startB(frame);

		stringstream frameNumber;
		frameNumber << capture.get(CAP_PROP_POS_FRAMES);
		string frameN = frameNumber.str();
		putText(frame, frameN.c_str(), Point(15, 15), FONT_HERSHEY_SIMPLEX, 0.5 , Scalar(0,0,0));
		putText(background, frameN.c_str(), Point(15, 15), FONT_HERSHEY_SIMPLEX, 0.5 , Scalar(0,0,0));
		
		out_capture.write(background);
        
        imshow("Frame", frame);
        imshow("Background", background);
        imshow("Segmentation By Subtraction", model.foreground(frame, background));
        imshow("Segmentation By Match", model.segm);

        keyboard = waitKey(30);
        
        if (keyboard == 27)
			break;
        
        capture >> frame;
	}

	capture.release();
}