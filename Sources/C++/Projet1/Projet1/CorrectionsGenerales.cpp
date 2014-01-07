#include "CorrectionsGenerales.h"
#include "opencv2\opencv.hpp"

//Constructeur
CorrectionGenerales::CorrectionGenerales(void){
}

//Destructeur
CorrectionGenerales::~CorrectionGenerales(void){
}


Mat CorrectionGenerales::corrigerContrasteEtLuminosit�(Mat imageEnEntree){
	//alpha [1.0-3.0]
	//beta  [0-100]
	imageEnEntree.convertTo(imageEnEntree, -1, 1.3, 5);
	return imageEnEntree;
}


Mat CorrectionGenerales::corrigerLuminosit�(Mat imageEnEntree){
	Mat imageYCrCb;

	cvtColor(imageEnEntree, imageYCrCb, CV_BGR2YCrCb);
	vector<Mat> channels;
	split(imageYCrCb, channels);

	equalizeHist(channels[0], channels[0]);

	merge(channels, imageYCrCb);
	Mat imageCorrig�e;
	cvtColor(imageYCrCb, imageCorrig�e, CV_YCrCb2BGR);

	return imageCorrig�e;
}


Mat CorrectionGenerales::corrigerBruit(Mat imageEnEntree){
	return Mat();
}