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
#include<opencv\cv.h>
using namespace std;
using namespace cv;

//-----Entete des m�thodes/fonctions-----------------------------------------
class LisseurPeau{

public:
	LisseurPeau(void);
	~LisseurPeau(void);

	Mat lisserImageFiltreGaussien(Mat);
	Mat lisserImageMethodeLee(Mat, Mat);

};