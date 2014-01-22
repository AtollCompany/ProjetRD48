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

#include "DetecteurPeau.h"
#include "opencv2\opencv.hpp"

//-----Corps des m�thodes/fonctions------------------------------------------
//Constructeur
DetecteurPeau::DetecteurPeau(void){
	
	//On fixe l'intervalle des couleurs de la peau en YCrCb
	Y_MIN = 80;
	Y_MAX = 255;

	Cb_MIN = 85;
	Cb_MAX = 135;
	
	Cr_MIN = 135;
	Cr_MAX = 180;
}


//Destructeur
DetecteurPeau::~DetecteurPeau(void){
}


/*
Methode getMasquePeau
Param�tre : Mat imageEnEntree : la matrice de l'image dont on veut le masque des pixels de peau
Retourne  : Mat               : la matrice qui contient le masque de pixels de peau
Principe  : On passe l'image dans le domaine de couleur YCrCb puis on d�tecte tous les pixels qui sont
dans les intervalles d�finis comme caract�ristiques des piels de peau.
*/
Mat DetecteurPeau::getMasquePeau(Mat imageEnEntree){
	Mat masquePeau;
	//Passage de l'image de l'espace de couleurs BGR vers YCrCb pour les traitements
	cvtColor(imageEnEntree, masquePeau, COLOR_BGR2YCrCb);
	//Filtrage des pixels appartenant � l'intervalle des pixels de peau  
	inRange(masquePeau, Scalar(Y_MIN, Cr_MIN, Cb_MIN), Scalar(Y_MAX, Cr_MAX, Cb_MAX), masquePeau);
	return masquePeau;
}


/*
Methode getMasquePeauFiltr�
Param�tre : Mat imageEnEntree : la matrice de l'image dont on veut le masque des pixels de peau apr�s optimisation
Retourne  : Mat               : la matrice qui contient le masque de pixels de peau apr�s traitements morphologiques
Principe  : On appelle la m�thode getMasquePeau, et � partir du masque de pixels de peau, on applique des
op�rateurs morphologiques pour rendre le masque plus net.
*/
//Methode qui va simplifier le masque de peau obtenu normalement avec des operations morphologiques
Mat DetecteurPeau::getMasquePeauFiltr�(Mat imageEnEntree){
	Mat masquePeauNormal = DetecteurPeau::getMasquePeau(imageEnEntree);
	Mat masquePeauDilat�, masquePeauErod�;

	//Nous obtenons de bons r�sultats avec une dilatation et deux �rosions
	dilate(masquePeauNormal, masquePeauDilat�, Mat(), Point(-1, -1), 1, 1, 1);
	erode(masquePeauDilat�,  masquePeauErod�,  Mat(), Point(-1, -1), 2, 1, 1);

	return masquePeauErod�;
}

