#define _CRT_SECURE_NO_WARNINGS
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "DetecteurPeau.h"
#include "CorrectionsGenerales.h"
#include "LisseurPeau.h"
#include <stdlib.h>
#include <stdio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>

using namespace cv;
using namespace std;

// Entete de fonctions
void getPeauImage(char*);
void corrigerImage(char*);
void getPeauApresCorrection(char*);
void lisserImage(char*);

int main(int argc, char *argv[])
{
	char *nomImage = "images/v2.jpg";

	//getPeauImage(nomImage);
	//corrigerImage(nomImage);
	//getPeauApresCorrection(nomImage);
	lisserImage(nomImage);
	return 0;
}

void getPeauApresCorrection(char* nomImage){
	Mat monImage = imread(nomImage, CV_LOAD_IMAGE_UNCHANGED);
	Mat imageCorrigee;
	CorrectionGenerales cg;
	imageCorrigee = cg.corrigerLuminosit�(monImage);
	imshow("Image Originale", imageCorrigee);

	DetecteurPeau monDetecteurPeau;
	Mat masquePeau;
	//Le pointeur vers l'image originale est modifi� :(
	masquePeau = monDetecteurPeau.getMasquePeauFiltr�(imageCorrigee);
	imshow("Masque de peau", masquePeau);
	waitKey(0);
	cvDestroyAllWindows();

}

void getPeauImage(char* nomImage){
	Mat monImage = imread(nomImage, CV_LOAD_IMAGE_UNCHANGED);
	imshow("Image Originale", monImage);
	DetecteurPeau monDetecteurPeau;
	Mat masquePeau;
	masquePeau = monDetecteurPeau.getMasquePeauFiltr�(monImage);
	imshow("Masque de peau", masquePeau);
	waitKey(0);
	cvDestroyAllWindows();
}

void corrigerImage(char* nomImage){
	Mat monImage = imread(nomImage, CV_LOAD_IMAGE_UNCHANGED);
	imshow("Image Originale", monImage);
	Mat imageCorrigee;

	CorrectionGenerales cg;
	imageCorrigee = cg.corrigerContrasteEtLuminosit�(monImage);
	
	imshow("Image Corrig�e", imageCorrigee);
	waitKey(0);
	cvDestroyAllWindows();
}

void lisserImage(char* nomImage){
	//Obtention de l'image originale
	Mat monImage = imread(nomImage, CV_LOAD_IMAGE_UNCHANGED);
	imshow("Image Originale", monImage);

	//Detection du masque des pixels de peau
	DetecteurPeau monDetecteurPeau;
	Mat masquePeau;
	masquePeau = monDetecteurPeau.getMasquePeauFiltr�(monImage);
	imshow("Masque des pixels de peau", masquePeau);

	//Lissage de la peau selon la m�thode de Lee
	LisseurPeau lisseurPeau;
	Mat resultat = lisseurPeau.lisserImageMethodeLee(monImage, masquePeau);
	imshow("Image apr�s Lissage", resultat);
	
	waitKey(0);
	cvDestroyAllWindows();
}