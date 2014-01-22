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


%Fonction CorrectionContrasteLuminosite
%Param�tre   : nomImage       : nom de l'image dont on va corriger le contraste et la luminosit�
%			 : nomImageRetour : nom de l'image de retour
%Retourne    : imageRetour    : la matrice de l'image de retour
%Principe    : Appelle la fonction ContrastEnhancement et �crit l'image de retour

function [imageRetour] = CorrectionContrasteLuminosite(nomImage,nomImageRetour)
    imageRetour = ContrastEnhancement(nomImage);
    imwrite(imageRetour,nomImageRetour,'Quality',100);
end