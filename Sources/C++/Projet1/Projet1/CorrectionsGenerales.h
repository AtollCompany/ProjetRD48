#pragma once
#include<opencv\cv.h>
using namespace std;
using namespace cv;

class CorrectionGenerales{

public:
	CorrectionGenerales(void);
	~CorrectionGenerales(void);

	Mat corrigerContrasteEtLuminosit�(Mat imageEnEntree);
	Mat corrigerLuminosit�(Mat imageEnEntree);
	Mat corrigerBruit(Mat imageEnEntree);

};