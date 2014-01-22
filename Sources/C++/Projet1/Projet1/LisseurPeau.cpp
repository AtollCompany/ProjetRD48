/*
-----------------------------------------------------------------------------
Polytech Nantes
2013-2014 INFO5
-----------------------------------------------------------------------------
Projet de Recherche et d�veloppement
Sujet 48 Magic Portrait
-----------------------------------------------------------------------------
Etudiants:
Pierre-Yves HERVO
Paul-Fran�ois JEAU
-----------------------------------------------------------------------------
*/

//-----Librairies et Headers-------------------------------------------------
#include "LisseurPeau.h"
#include "opencv2\opencv.hpp"
#include<stdio.h>

/*Il existe 4 types de flous sous openCv, pour voir l'effet de chacun de ses flous, d�commenter le code dans EssaiFlous et
le lancer. Les 4 types de flous sont flou homogene, flou gaussien, flou m�dian, flou bilat�ral.
Nous avons choisi d'utiliser le flou gaussien car c'est celui qui montre les meilleurs r�sultats en ne d�t�riorant pas trop l'image ou
en donnant un aspet aquarel a la photo*/


//-----Corps des m�thodes/fonctions------------------------------------------
//Constructeur
LisseurPeau::LisseurPeau(void){
}


//Destructeur
LisseurPeau::~LisseurPeau(void){
}


/*
Methode lisserImageFiltreGaussien
Param�tre : Mat imageEnEntree : la matrice de l'image que l'on veut rendre floue
Retourne  : Mat               : la matrice de l'image cette fois ci floue
Principe  : On applique un flou de type gaussien sur la matrice avec un noyau d'une certaine taille.
*/
Mat LisseurPeau::lisserImageFiltreGaussien(Mat monImageEnEntree){
	Mat imageLiss�e;
	GaussianBlur(monImageEnEntree, imageLiss�e, cv::Size(7, 7), 2, 2);
	//Am�lioration possible : d�viation standard hauteur du visage/100 voir article 
	return imageLiss�e;
}


/*
Methode lisserImageMethodeLee
Param�tre : Mat imageEnEntree : la matrice de l'image que l'on veut am�liorer par lissage de la peau
		  : Mat masquePeau    : la matrice des pixels de peau de l'image
Retourne  : Mat               : la matrice avec la peau liss�e
Principe  : A partir du masque de peau, on va pouvoir combiner la valeur floue et la valeur originale des pixels 
relevant de la peau afin d'obtenir un lissage homog�ne.
*/
Mat LisseurPeau::lisserImageMethodeLee(Mat monImageEnEntree, Mat masquePeau){
	Mat imageFinale;
	imageFinale = Mat::zeros(monImageEnEntree.size(), CV_8UC3);
	Mat imageLiss�e = lisserImageFiltreGaussien(monImageEnEntree);

	for (int i = 0; i < masquePeau.rows; i++){
		for (int j = 0; j < masquePeau.cols; j++){
			if ((float)masquePeau.at<unsigned char>(i, j) == 255){
				imageFinale.at<Vec3b>(i, j) = imageLiss�e.at<Vec3b>(i, j)*0.5 + monImageEnEntree.at<Vec3b>(i, j)*0.5;
			}
			else{
				imageFinale.at<Vec3b>(i, j) = monImageEnEntree.at<Vec3b>(i, j);
			}
		}
	}
	return imageFinale;
}