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


%Fonction AugmentationProfondeurChamp
%Param�tre   : nomImage       : nom de l'image dont on veut am�liorer la profondeur de champ
%			 : nomImageRetour : nom de l'image de retour
%Retourne    : imageRetour    : la matrice de l'image de retour
%Principe    : Cette fonction va calculer une version floue de l'image originale et calculer
%la carte de profondeur. Ensuite gr�ce � la carte, on peut construire une image dont les pixels
%qui sont sup�rieurs � un seuil de profondeur sont flous.

function [imageRetour] = AugmentationProfondeurChamp(nomImage,nomImageRetour)

	addpath('DefocusEstimation_Sources\');
	
    %Image Floue
    imageOriginale=imread(nomImage);
    w = fspecial('disk',8);
    %w = fspecial('gaussian',[64 64],6);
    imageFloue = imfilter(imageOriginale,w,'replicate');
    
    
    %Carte de profondeur
    imageOriginale_Double=im2double(imread(nomImage));
    eth=0.1;
    carteBordure=edge(rgb2gray(imageOriginale_Double),'canny',eth,1);
    std=1;
    lambda=0.001;
    flouMaximum=3;
    [sDMap, fDmap] = defocusEstimation(imageOriginale_Double,carteBordure,std,lambda,flouMaximum);

    
    %Detection de la boite englobante du visage
    detecteurVisage = vision.CascadeObjectDetector; 		
    boitesEnglobantes = step(detecteurVisage,imageOriginale); 
    
    x=boitesEnglobantes(1);
    y=boitesEnglobantes(2);
    hauteur_boite=boitesEnglobantes(3);
    largeur_boite=boitesEnglobantes(4);
    
    %Calcul du seuil de profondeur moyen pour le visage dans la boite
    SEUIL = mean(fDmap(x:x+hauteur_boite,y:y+largeur_boite));
   
    %Construction de l'image r�sultante, si � une position donn�e, le pixel
    %est � une profondeur sup�rieure � la profondeur moyenne au niveau du
    %visage, on choisit la version floue sinon on prend la version
    %originale du pixel
    s = size(imageOriginale);
    imageRetour = imageOriginale;
    for i=1:s(1)
        for j=1:s(2)
            if(fDmap(i,j)>SEUIL)
                imageRetour(i,j) = imageFloue(i,j);
            end;
        end;
    end;
 
    %Ecriture du r�sultat
    imwrite(imageRetour,nomImageRetour,'Quality',100); 
end

