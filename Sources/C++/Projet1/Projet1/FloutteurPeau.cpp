#include "FloutteurPeau.h"
#include "opencv2\opencv.hpp"
#include<stdio.h>

/*Il existe 4 types de flous sous openCv, pour voir l'effet de chacun de ses flous, d�commenter le code dans EssaiFlous et
le lancer. Les 4 types de flous sont flou homogene, flou gaussien, flou m�dian, flou bilat�ral.
Nous avons choisi d'utiliser le flou gaussien car c'est celui qui montre les meilleurs r�sultats en ne d�t�riorant pas trop l'image ou
en donnant un aspet aquarel a la photo*/

//constructeur
FloutteurPeau::FloutteurPeau(void){
}

//Destructeur
FloutteurPeau::~FloutteurPeau(void){
}

void FloutteurPeau::flouterImageTotale(char * imagename){
	Mat monImage = imread(imagename, CV_LOAD_IMAGE_UNCHANGED);
	Mat matriceFlou;
	imshow("Image Originale", monImage);
	GaussianBlur(monImage, matriceFlou, cv::Size(15, 15), 2, 2); //plus tard deviation standart hauteur de face/100 voir article
	imshow("image flout�e", matriceFlou);
	waitKey(0);
	cvDestroyAllWindows();
}