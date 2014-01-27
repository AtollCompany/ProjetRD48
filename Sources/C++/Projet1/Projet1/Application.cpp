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
#define _CRT_SECURE_NO_WARNINGS
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "DetecteurPeau.h"
#include "LisseurPeau.h"
#include <stdlib.h>
#include <stdio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>

using namespace cv;
using namespace std;

//-----Entete des m�thodes/fonctions-----------------------------------------
bool detecterVisage(Mat);
Mat  lisserPeau(Mat); 
void lisserPeauTest(char*);


//-----Main du programme-----------------------------------------------------
int main(int argc, char *argv[])
{
	//V�rification de l'argument
	if (argc < 3) {
		cerr << "Utilisation de : " << argv[0] << endl;
		cerr << "Argument 1 : nom_image_cible" << endl;
		cerr << "Argument 2 : nom_image_resultat" << endl;
		cerr << "Exemple d'utilisation : nom_executable <nom_fichier_cible> <nom_fichier_resultat>" << endl;
		return -1;
	}

	//Chargement de l'image cible
	Mat monImageCible = imread(argv[1], CV_LOAD_IMAGE_UNCHANGED);
	
	if (monImageCible.empty()){
		cerr << "Erreur: l'image " << argv[1] << " n'a pas pu �tre charg�e" << endl;
		return -2;
	}

	//V�rification du type de l'image
	//L'image est-elle en couleur et poss�de-t-elle trois canaux de couleurs ?


	//V�rification de la pr�sence de visage dans l'image
	if (detecterVisage(monImageCible)){
		cerr << "Erreur: l'image " << argv[1] << " ne contient aucun visage" << endl;
		return -3;
	}

	//Lancement du traitement en tant que tel
	Mat resultat = lisserPeau(monImageCible);

	//Ecriture de l'image r�sultante
	imwrite(argv[2], resultat);

	return 0;
}


//-----Corps des m�thodes/fonctions------------------------------------------

/*
Methode detecterVisage
Param�tre : Mat monImage : la matrice de l'image que l'on veut tester
Retourne  : bool         : true si l'image contient au moins un visage, false sinon
Principe  : Avec un classifieur de Haar on cherche au moins une boite englobante d'un visage,
s'il y en a une, il y a au moins un visage � traiter.
*/
bool detecterVisage(Mat monImage){

	//Chargement du classifieur de Haar
	String classifieur_visage_fichier = "haarcascade_frontalface_default.xml";
	CascadeClassifier classifieur_visage;

	if (!classifieur_visage.load(classifieur_visage_fichier)){
		cerr << "Erreur: Impossible de charger le Detecteur de Haar de visages" << endl;
		exit(-3);
	}
	//Recherche de visage(s) dans l'image
	vector<Rect> visages;
	Mat monImage_niveauxGris;

	cvtColor(monImage, monImage_niveauxGris, CV_BGR2GRAY);
	equalizeHist(monImage_niveauxGris, monImage_niveauxGris);

	classifieur_visage.detectMultiScale(monImage_niveauxGris, visages, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

	//Retour du r�sultat de la recherche
	return visages.empty();
}


/*
Methode lisserPeau
Param�tre : Mat monImage : la matrice de l'image � traiter
Retourne  : Mat          : la matrice de l'image apr�s le lissage
Principe  : Cherche le masque des pixels de peau d'une image et � partir de celui-ci,
on lisse l'image en nous inspirant de la m�thode de Lee et Al.
*/
Mat lisserPeau(Mat monImage){

	//Recherche du masque de peau 
	DetecteurPeau monDetecteurPeau;
	Mat           masquePeau = monDetecteurPeau.getMasquePeauFiltr�(monImage);

	//Lissage de la peau avec la m�thode de Lee et Al.
	LisseurPeau   lisseurPeau;
	Mat           resultat = lisseurPeau.lisserImageMethodeLee(monImage, masquePeau);

	return resultat;
}


/*
Methode lisserPeauTest
Param�tre : char* monImage : le nom de l'image � traiter
Retourne  : void           : la fonction affiche simplement les images issues des diff�rentes �tapes
Principe  : Cherche le masque des pixels de peau d'une image, l'affiche, et � partir de celui-ci,
on lisse l'image en nous inspirant de la m�thode de Lee et Al. puis on affiche l'image r�sultat.
*/
void lisserPeauTest(char* nomImage){
	//Obtention de l'image originale
	Mat monImage = imread(nomImage, CV_LOAD_IMAGE_UNCHANGED);
	imshow("Image Originale", monImage);

	//Detection du masque des pixels de peau
	DetecteurPeau monDetecteurPeau;
	Mat masquePeau;
	masquePeau = monDetecteurPeau.getMasquePeauFiltr�(monImage);
	imshow("Masque des pixels de peau", masquePeau);

	//Lissage de la peau selon la m�thode de Lee et Al.
	LisseurPeau lisseurPeau;
	Mat resultat = lisseurPeau.lisserImageMethodeLee(monImage, masquePeau);
	imshow("Image apr�s Lissage", resultat);

	waitKey(0);
	cvDestroyAllWindows();
}