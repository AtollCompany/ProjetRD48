%
%-----------------------------------------------------------------------------
%Polytech Nantes
%2013-2014 INFO5
%-----------------------------------------------------------------------------
%Projet de Recherche et d�veloppement
%Sujet 48 Magic Portrait
%-----------------------------------------------------------------------------
%Etudiants:
%Pierre-Yves HERVO
%Paul-Fran�ois JEAU
%-----------------------------------------------------------------------------
%


%Fonction TraitementDefocusPuisContrasteLuminosite
%Param�tre   : nomImage       : nom de l'image dont on veut am�liorer la
%                               profondeur de champ et le 
%                               contraste/luminosit�
%			 : nomImageApresAugmentationDefocus : nom de l'image de retour
%			 apr�s l'augmentation de la profondeur de champ
%			 : nomImageApresCorrectionContLum : nom de l'image de retour
%			 apr�s la correction du contraste et de la luminosit�
%			 : redimensionner : Y ou N pour indiquer s'il faut
%			 redimensionner l'image de base ou non
%			 : taille : taille de la dimension maximale de l'image

%Principe    : Cette fonction lance successivement tous les traitements
%Matlab pour am�liorer une image.

function TraitementDefocusPuisContrasteLuminosite(nomImageOriginale,nomImagePeauLisse,nomImageApresAugmentationDefocus,nomImageApresCorrectionContLum,redimensionner,taille)


imageOriginale = imread(nomImageOriginale);

%Redimensionnement si pr�cis�
if(redimensionner=='Y')
    imwrite(Redimensionnement(nomImagePeauLisse,taille),nomImagePeauLisse,'Quality',100); 
	imageOriginale = Redimensionnement(nomImageOriginale,taille);
end;

subplot(1,2,1);
imshow(imageOriginale);


%Augmentation de la profondeur de champ
AugmentationProfondeurChamp(nomImagePeauLisse,nomImageApresAugmentationDefocus);

%Puis correction de la luminosit� et du contraste
CorrectionContrasteLuminosite(nomImageApresAugmentationDefocus,nomImageApresCorrectionContLum);
subplot(1,2,2);
imageApresCorrectionContLum = imread(nomImageApresCorrectionContLum);
imshow(imageApresCorrectionContLum);
end