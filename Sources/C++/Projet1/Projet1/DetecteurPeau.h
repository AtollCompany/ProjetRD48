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

#pragma once
//Inspir� du travail de http://razibdeb.wordpress.com/2013/09/10/skin-detection-in-c-using-opencv/

#include<opencv\cv.h>
using namespace std;
using namespace cv;

//-----Entete des m�thodes/fonctions-----------------------------------------
class DetecteurPeau{

public:
	DetecteurPeau(void);
	~DetecteurPeau(void);

	Mat getMasquePeau(Mat);
	Mat getMasquePeauFiltr�(Mat);
	Mat getMatriceEtiquettage(Mat);
	unsigned char inf(unsigned char etiquetteCourante, unsigned char etiquetteAdjacente);
	void determinerEtiquette(Mat * matriceEtiquettage, int numeroLigne, int numeroColonne, unsigned char *numeroEtiquette);
	Rect detecterCadreVisage(Mat );
	set<unsigned char> getEnsembleEtiquette(Mat, Rect);
	Mat changerMasquePeau(Mat , set<unsigned char> , Mat );
	
private:
	int Y_MIN;
	int Y_MAX;
	int Cb_MIN;
	int Cb_MAX;
	int Cr_MIN;
	int Cr_MAX;
};