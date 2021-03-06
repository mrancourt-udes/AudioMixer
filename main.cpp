/** **************************************************************
 \file tp5.cpp
 \author Martin Rancourt - 140 59 412
 \author Frederic Poitras - 140 61 677
 \brief Programme pour gerer une liste de chansons et pour generer de nouvelles
 chansons par la manipulation de chansons deja presentes dans la liste. Cette
 liste de chansons est manipulee grâce aux operations suivantes
 - Ajout («ajouter»)
 - Destruction («retirer»)
 - Affichage («afficher»)
 - Mixage de deux chansons («mixer»)
 - Effacement de la voix («karaoke»)
 - Ajout echo («echo»)
 - Acceleration («accelerer»)
 - Ralentissement («ralentir»).
 - Terminer «fin» permet de terminer l'execution du programme.
 <b>Entrees:</b>
 \li (\c clavier) commande - liste de commande (\ Chaine de caracteres)
 \li (\c fichier) fichier - fichiers de musique en format wav (\c fichier)
 
 <b>Sorties:</b>
 \li (\c fichier) fichier - fichiers de musique en format wav (\c fichier)
 *****************************************************************/

#include <iostream>
#include <string>
#include <vector>

#include "chanson.h"
#include "wav.h"

using namespace std;

// Declaration des fonctions prototypes globales
int obtenirChanson(vector<chanson_t> &chansons, bool veuxAfficher);

// Declaration des commandes et constantes globales
const string CMD_MIXER = "mixer";
const string CMD_KARAOKE = "karaoke";
const string CMD_ECHO = "echo";
const string CMD_ACCELERER = "accelerer";
const string CMD_RALENTIR = "ralentir";
const string SEPARATEUR_VERSION = "-V";
const string TITRE = "titre";
const string INTERPRETE = "interprete";
const string OUI = "oui";
const string NON = "non";
const string TRAIN = ">> ";

/** ----------------------------------------------------------------------
 \brief Ce programme est le module principal. Il sert a modifier des
 pistes audio
 ----------------------------------------------------------------------- **/
int main()
{
    // Declaration des fonctions prototype
    void ajouter(vector<chanson_t> &);
    void afficher(vector<chanson_t> &);
    void retirer(vector<chanson_t> &);
    void mixer(vector<chanson_t> &);
    void accelerer(vector<chanson_t> &);
    void ralentir(vector<chanson_t> &);
    void echo(vector<chanson_t> &);
    void karaoke(vector<chanson_t> &);
    
    // Declaration des constantes
    const string CMD_FIN = "fin";
    const string CMD_JOUER = "jouer";
    const string CMD_AJOUTER = "ajouter";
    const string CMD_RETIRER = "retirer";
    const string CMD_AFFICHER = "afficher";
    
    // Declaration des variables
    vector<chanson_t> chansons;
    string commande;
    
    // Lecture de la commande de l'utilisateur
    cout << "Veuilez entrer une commande a executer : ";
    cin >> commande;
    cout << TRAIN << commande << endl; // Train
    
    while (commande != CMD_FIN)
    {
        // Lecteur d'une chanson
        if (commande == CMD_JOUER)
        {
            // Declaration des variables
            string nomFicher;
            int duree;
            
            // Lecture des informations
            cout << "Veuillez entrer le nom du fichier : ";
            cin >> nomFicher;
            cout << TRAIN << nomFicher << endl; // Train
            
            cout << "Veuillez entrer la duree de lecture : ";
            cin >> duree;
            cout << TRAIN << duree << endl; // Train
            
            // Lecture de la chanson
            jouerMusique(nomFicher, duree);
        }
        // Affichage de la liste
        else if (commande == CMD_AFFICHER)
        {
            afficher(chansons);
        }
        // Ajout d'une chanson a la liste
        else if (commande == CMD_AJOUTER)
        {
            ajouter(chansons);
        }
        // Suppression d'une chanson
        else if (commande == CMD_RETIRER)
        {
            retirer(chansons);
        }
        // Mixage de deux chansons
        else if (commande == CMD_MIXER)
        {
            mixer(chansons);
        }
        // Acceleration d'une chanson
        else if (commande == CMD_ACCELERER)
        {
            // Acceleration de la vitesse de la chanson selon le facteur
            accelerer(chansons);
        }
        // Deceleration d'une chanson
        else if (commande == CMD_RALENTIR)
        {
            // Deceleration de la vitesse de la chanson selon le facteur
            ralentir(chansons);
        }
        // Ajout d'Echo sur une chanson
        else if (commande == CMD_ECHO)
        {
            echo(chansons);
        }
        // Conversion d'une chanson en mode Karaoke
        else if (commande == CMD_KARAOKE)
        {
            karaoke(chansons);
        }
        // Commande invalide
        else
        {
            cout << "La commande entree est invalide." << endl;
        }
        
        // Lecture de la commande de l'utilisateur
        cout << endl << "Veuilez entrer une commande a executer : ";
        cin >> commande;
        cout << TRAIN << commande << endl; // Train
        
    }
    
    return 0;
}

/** ----------------------------------------------------------------------
 \brief Ce module permet d'ajouter une chanson à la liste.
 \param [in] chansons : Liste des chansons contenus dans le mixeur
 contient maintenant un element de plus, soit la chanson ajoutee)
 ----------------------------------------------------------------------- **/
void ajouter(vector<chanson_t> &chansons)
{
    
    // Declaration des constantes
    const string ATTRIBUT = "originale";
    
    // Declaration des variables
    string titre;
    string interprete;
    string nomFichier;
    string mois;
    int jour;
    int annee;
    chanson_t chanson;
    
    // Lecture des informations
    cout << "Titre de la chanson : ";
    cin >> titre;
    cout << TRAIN << titre << endl; // Train
    cout << "Interprete de la chanson : ";
    cin >> interprete;
    cout << TRAIN << interprete << endl; // Train
    cout << "Nom du fichier : ";
    cin >> nomFichier;
    cout << TRAIN << nomFichier << endl; // Train
    cout << "Date d'enregistrement..." << endl;
    cout << "Jour : ";
    cin >> jour;
    cout << TRAIN << jour << endl; // Train
    cout << "Mois : ";
    cin >> mois;
    cout << TRAIN << mois << endl; // Train
    cout << "Annee : ";
    cin >> annee;
    cout << TRAIN << annee << endl; // Train
    
    // Initialistion de la chanson
    init(chanson);
    
    // Modification des parametres de la chanson
    chanson.titre = titre;
    chanson.interprete = interprete;
    chanson.fichier = nomFichier;
    // Attribution de la date
    setDate(chanson.dateEnregistrement, jour, mois, annee);
    chanson.attribut = ATTRIBUT;
    
    // Ajout de la chanson dans la liste
    chansons.push_back(chanson);
    
}

/** ----------------------------------------------------------------------
 \brief Ce module permet d'afficher la liste des chansons triees dans un
 ordre specifie.
 \param [in] chansons : Liste des chansons contenus dans le mixeur
 \param [out] chansons : Liste des chansons contenus dans le mixeur
 ----------------------------------------------------------------------- **/
void afficher(vector<chanson_t> &chansons)
{
    // Declaration des fonctions prototypes
    void trier(vector<chanson_t> &, string critereTri);
    
    // Declaration des constantes
    const int MIN_CHANSONS = 0;
    
    // Declaration des vaariables
    string veuxTrier;
    string critereTri;
    vector<chanson_t> listeAffichage;
    
    // S'il y a au moins une chanson dans la liste
    if (chansons.size() > MIN_CHANSONS)
    {
        // Est-ce que l'utilisateur veut trier la liste
        cout << "Voulez-vous trier la liste ? [" + OUI + "/" + NON + "] : ";
        cin >> veuxTrier;
        cout << TRAIN << veuxTrier << endl; // Train
        
        // L'utilisateur veux trier la liste
        if (veuxTrier == OUI)
        {
            // Critere de tri
            cout << "Dans quel ordre voulez-vous trier la liste ? [" + TITRE + "/" + INTERPRETE + "] : ";
            cin >> critereTri;
            cout << TRAIN << critereTri << endl; // Train
            
            // Triage et recuperation de la liste pour affichahe
            trier(chansons, critereTri);
        }
        
        cout << endl;
        cout << "--------------------------------------- " << endl;
        cout << "-- L i s t e  d e s  c h a n s o n s --" << endl;
        cout << "--------------------------------------- " << endl;
        
        // Pour chaque chanson
        for (int i = 0; i < chansons.size(); i++)
        {
            cout << "-------------------- " << endl;
            cout << "-- Chanson " << i << endl;
            cout << "-------------------- " << endl;
            
            // Affichage des informations
            cout << toString(chansons.at(i)) << endl;
        }
    }
    // La liste de chanons est vide !
    else
    {
        cout << "La liste ne contient aucune chanson" << endl;
    }
}

/** ----------------------------------------------------------------------
 \brief Recupere et retourne une chanson parmi la liste des chansons
 \param [in] chansons : Liste des chansons contenus dans le mixeur
 \param [in] veuxAfficher : Indique si on doit demande a l'utilisateur
 d'afficher la liste ou non
 \return indice : indice de la chanson
 ----------------------------------------------------------------------- **/
int obtenirChanson(vector<chanson_t> &chansons, bool veuxAfficher)
{
    // Declaration des fonctions prototypes
    void afficher(vector<chanson_t> &chansons);
    
    // Declaration des variables
    string reponse;
    int indice;
    
    // Si parametre veuxAfficher est a vrai, on demande a l'utilisateur s'il veux
    // voir la liste des chansons
    if (veuxAfficher)
    {
        cout << "Souhaitez-vous voir la liste des chansons ? [" + OUI + "/" + NON + "] : ";
        cin >> reponse;
        cout << TRAIN << reponse << endl; // Train
        
        // Lutilisateur veux voir la liste de chansons
        if (reponse == OUI)
        {
            // Affichage de la liste des chansons
            afficher(chansons);
        }
    }
    
    // Obtention de l'indice de la chanson
    cout << "Entrez le numero de la chanson choisie : ";
    cin >> indice;
    cout << TRAIN << indice << endl; // Train
    
    return indice;
}

/** ----------------------------------------------------------------------
 \brief Cette operation permet de retirer une chanson de la liste.
 \param [in] chansons : Liste des chansons contenus dans le mixeur
 \param [out] chansons : Liste des chansons contenus dans le mixeur (cette liste
 contient maintenant un element de moins, soit la chanson retiree)
 ----------------------------------------------------------------------- **/
void retirer(vector<chanson_t> &chansons)
{
    // indice de la chanson a retirer
    int indice;
    
    // Affichage de la liste selon la demande de l'utilisateur
    indice = obtenirChanson(chansons, true);
    
    // Suppression de la chanson de la liste
    chansons.erase(chansons.begin() + indice);
}

/** ----------------------------------------------------------------------
 \brief Cette operation permet de creer (ajouter) une nouvelle chanson
 par le mixage de deux chansons deja presentes dans la liste
 \param [in] chansons : Liste des chansons contenus dans le mixeur
 \param [out] chansons : Liste des chansons contenus dans le mixeur (cette liste
 contient maintenant un element de plus, soit la chanson mixee)
 ----------------------------------------------------------------------- **/
void mixer(vector<chanson_t> &chansons)
{
    // Declaration des variables
    int indice1;
    int indice2;
    unsigned int nbTraite = 0;
    MusiqueWAV titre;
    MusiqueWAV titre1;
    MusiqueWAV titre2;
    EchantillonStereo nouvelEchatillon;
    
    //Obtenir les chansons et le contenu musical
    indice1 = obtenirChanson(chansons, true);
    indice2 = obtenirChanson(chansons, false);
    titre2 = lireChanson(chansons.at(indice2).fichier);
    titre1 = lireChanson(chansons.at(indice1).fichier);
    
    // Creation de la nouvelle chanson
    chansons.push_back(chansons.at(indice1));
    // Modification du nom de fichier de la chanson
    chansons.back().fichier += SEPARATEUR_VERSION + recupererProchaineVersion(chansons.at(indice1).nbCopies);
    // Mise a jout de l'attribut de la chanson
    chansons.back().attribut = CMD_MIXER;
    
    titre = titre1;
    titre.echantillon.clear();
    
    if (titre1.tailleData > titre2.tailleData)
    {
        titre.tailleData = titre2.tailleData;
    }
    
    // Generation des echantillons
    while(nbTraite < titre.tailleData / 4)
    {
        nouvelEchatillon.gauche = titre1.echantillon[nbTraite].gauche / 2
        + titre2.echantillon[nbTraite].gauche / 2;
        
        nouvelEchatillon.droite = titre1.echantillon[nbTraite].droite / 2
        + titre2.echantillon[nbTraite].droite / 2;
        
        titre.echantillon.push_back(nouvelEchatillon);
        
        nbTraite++;
    }
    
    // Enregistrement de la chanson dans un fichier WAV avec son nouveau nom
    ecrireChanson(titre, chansons.back().fichier);
    
    // increment du nombre de version de la chanson originale
    chansons.at(indice1).nbCopies++;
}

/** ----------------------------------------------------------------------
 \brief Cette operation permet de creer une nouvelle chanson a partir
 d'une chanson deja presente dans la liste en enlevant la voix.
 \param [in] chansons : Liste des chansons contenus dans le mixeur
 \param [out] chansons : Liste des chansons contenus dans le mixeur (cette liste
 contient maintenant un element de plus, soit la chanson sans parole)
 ----------------------------------------------------------------------- **/
void karaoke(vector<chanson_t> &chansons)
{
    // Declaration des fonctions prototypes
    void afficher(vector<chanson_t> &);
    
    // Declaration des variables
    int indice;
    unsigned int nbTraite = 0;
    MusiqueWAV titre;
    MusiqueWAV titre1;
    
    // Obtention la chanson et le contenu musical
    indice = obtenirChanson(chansons, true);
    titre1 = lireChanson(chansons.at(indice).fichier);
    
    // Creation de la nouvelle chanson
    chansons.push_back(chansons.at(indice));
    // Modification du nom de fichier de la chanson
    chansons.back().fichier += SEPARATEUR_VERSION + recupererProchaineVersion(chansons.back().nbCopies);
    // Mise a jout de l'attribut de la chanson
    chansons.back().attribut = CMD_ACCELERER;
    
    titre = titre1;
    
    // Suppression de la voix sur la nouvelle chanson
    // Generation des echantillons
    while(nbTraite < titre.tailleData / 4)
    {
        
        titre.echantillon[nbTraite].gauche = (titre1.echantillon[nbTraite].gauche
                                              - titre1.echantillon[nbTraite].droite) / 2;
        titre.echantillon[nbTraite].droite = (titre1.echantillon[nbTraite].gauche
                                              - titre1.echantillon[nbTraite].droite) / 2;
        
        nbTraite++;
    }
    
    ecrireChanson(titre, chansons.back().fichier);
    
    // increment du nombre de version de la chanson originale
    chansons.at(indice).nbCopies++;
    
}

/** ---------------------------------------------------------------------
 \brief Cette fonction permet de creer une nouvelle chanson a partir
 d'une chanson deja presente dans la liste en ajoutant un effet d'echo
 \param [in] chansons : Liste des chansons contenus dans le mixeur
 \param [out] chansons : Liste des chansons contenus dans le mixeur (cette liste
 contient maintenant un element de plus, soit la chanson avec le mode echo)
 ----------------------------------------------------------------------- **/
void echo(vector<chanson_t> &chansons)
{
    // Declaration des constantes
    const int borneDacalage = 10050;
    const int decalage = 10000;
    
    // Declaration des variables
    int indice;
    MusiqueWAV titre;
    MusiqueWAV titre1;
    unsigned int nbTraite = 0;
    
    // Obtention la chanson et le contenu musical
    indice = obtenirChanson(chansons, true);
    titre1 = lireChanson(chansons.at(indice).fichier);
    
    // Creation de la nouvelle chanson
    chansons.push_back(chansons.at(indice));
    // Modification du nom de fichier de la chanson
    chansons.back().fichier += SEPARATEUR_VERSION + recupererProchaineVersion(chansons.back().nbCopies);
    // Mise a jout de l'attribut de la chanson
    chansons.back().attribut = CMD_ECHO;
    
    titre = titre1;
    while(nbTraite < titre.tailleData / 4)
    {
        if (nbTraite > borneDacalage)
        {
            titre.echantillon[nbTraite].gauche = titre1.echantillon[nbTraite].gauche
            + titre1.echantillon[nbTraite-decalage].gauche;
            
            titre.echantillon[nbTraite].droite = titre1.echantillon[nbTraite].droite
            + titre1.echantillon[nbTraite-decalage].droite;
        }
        else
        {
            titre.echantillon[nbTraite].gauche = titre1.echantillon[nbTraite].gauche;
            titre.echantillon[nbTraite].droite = titre1.echantillon[nbTraite].droite;
        }
        nbTraite += 2;
    }
    ecrireChanson(titre, chansons.back().fichier);
    
    // increment du nombre de version de la chanson originale
    chansons.at(indice).nbCopies++;
}

/** ----------------------------------------------------------------------
 \brief Cette operation permet de creer une nouvelle chanson a partir
 d'une chanson deja presente dans la liste en accelerant le rythme de
 la chanson.
 \param [in] chansons : Liste des chansons contenus dans le mixeur
 \param [out] chansons : Liste des chansons contenus dans le mixeur (cette liste
 contient maintenant un element de plus, soit la chanson acceleree)
 ----------------------------------------------------------------------- **/
void accelerer(vector<chanson_t> &chansons)
{
    // Declaration des variables
    int facteur;
    int indice;
    MusiqueWAV titre;
    MusiqueWAV titre1;
    
    // Obtention la chanson et le contenu musical
    indice = obtenirChanson(chansons, true);
    titre1 = lireChanson(chansons.at(indice).fichier);
    
    // Lecture du facteur d'acceleration
    cout << "Veuillez entrer le facteur d'acceleration : ";
    cin >> facteur;
    cout << TRAIN << facteur << endl; // Train
    
    // Creation de la nouvelle chanson
    chansons.push_back(chansons.at(indice));
    // Modification du nom de fichier de la chanson
    chansons.back().fichier += SEPARATEUR_VERSION + recupererProchaineVersion(chansons.back().nbCopies);
    // Mise a jout de l'attribut de la chanson
    chansons.back().attribut = CMD_ACCELERER;
    
    titre = titre1;
    titre.tauxEchantillon = int(titre.tauxEchantillon * facteur);
    ecrireChanson(titre, chansons.back().fichier);
    
    // increment du nombre de version de la chanson originale
    chansons.at(indice).nbCopies++;
}

/** ----------------------------------------------------------------------
 \brief Ce module permet de creer une nouvelle chanson a partir d'une
 chanson deja presente dans la liste en ralentissant le rythme de la chanson
 \param [in] chansons : Liste des chansons contenus dans le mixeur
 \param [out] chansons : Liste des chansons contenus dans le mixeur (cette liste
 contient maintenant un element de plus, soit la chanson ralentie)
 ----------------------------------------------------------------------- **/
void ralentir(vector<chanson_t> &chansons)
{
    // Declaration des variables
    int facteur;
    int indice;
    MusiqueWAV titre;
    MusiqueWAV titre1;
    
    // Obtention la chanson et le contenu musical
    indice = obtenirChanson(chansons, true);
    titre1 = lireChanson(chansons.at(indice).fichier);
    
    // Lecture du facteur d'acceleration
    cout << "Veuillez entrer le facteur de ralentissement : ";
    cin >> facteur;
    cout << TRAIN << facteur << endl; // Train
    
    // Creation de la nouvelle chanson
    chansons.push_back(chansons.at(indice));
    // Modification du nom de fichier de la chanson
    chansons.back().fichier += SEPARATEUR_VERSION + recupererProchaineVersion(chansons.back().nbCopies);
    // Mise a jout de l'attribut de la chanson
    chansons.back().attribut = CMD_RALENTIR;
    
    titre = titre1;
    titre.tauxEchantillon = int(titre.tauxEchantillon / facteur);
    ecrireChanson(titre, chansons.back().fichier);
    
    // increment du nombre de version de la chanson originale
    chansons.at(indice).nbCopies++;
}

/** ----------------------------------------------------------------------
 \brief Ce module permet de trier la liste des chansons dans un ordre
 specifie.
 \param [in] chansons : Liste des chansons contenus dans le mixeur
 \param [in] critereTri : Critere de tri (titre ou interprete)
 \return listeSortie : Liste des chansons contenus dans le mixeur triee selon
 le critere de tri
 ----------------------------------------------------------------------- **/
void trier(vector<chanson_t>& liste, string critereTri)
{
    // Declaration des fonctions prototypes
    void regrouperTitre(vector<chanson_t>, vector<chanson_t>, vector<chanson_t> &);
    void regrouperInterprete(vector<chanson_t>, vector<chanson_t>, vector<chanson_t> &);

    // Declaration des constantes
    const int LONGEUR_MINIMALE = 1;
    
    // Declaration des variables
    int milieu;
    
    // si longueur > 1
    if (liste.size() > LONGEUR_MINIMALE)
    {
        // trouve le milieu de la liste pour creer deux listes, liste1 et liste2, de longueur lg1 et lg2
        milieu = int(liste.size() / 2);
        
        vector<chanson_t> liste1(liste.begin(), liste.begin() + milieu);
        vector<chanson_t> liste2(liste.begin() + milieu, liste.end());
        
        // On vide la liste afin de remettre les element tries dedans
        liste.clear();
        
        // tri fusion recursif sut la premiere liste
        trier(liste1, critereTri);
        // tri fusion recursif sur la deuxieme liste
        trier(liste2, critereTri);
        
        if (critereTri == TITRE)
        {
            // regroupement des deux listes selon le titre
            regrouperTitre(liste1, liste2, liste);
        }
        else if (critereTri == INTERPRETE)
        {
            // regroupement des deux listes selon l'interprete
            regrouperInterprete(liste1, liste2, liste);
        }
    }
}

/** ----------------------------------------------------------------------
 \brief Ce module permet de regrouper deux listes par ordre de titre
 \param [in] liste1 : Premiere liste de chansons a regrouper
 \param [in] liste2 : Deuxieme liste de chansons a regrouper
 \param [in] listeRegroupee : Liste de chansons regroupee
 \param [out] listeRegroupee : Liste de chansons regroupee
 ----------------------------------------------------------------------- **/
void regrouperTitre(vector<chanson_t> liste1, vector<chanson_t> liste2, vector<chanson_t> &listeRegroupee) {
    
    // → tant qu'une des listes n'est pas vide
    while ( liste1.size() > 0 && liste2.size() > 0 )
    {
        // → on compare les elements courants des deux listes
        // → on choisit le plus petit element
        // → on le copie dans la liste de sortie
        if ( liste1.front().titre < liste2.front().titre )
        {
            listeRegroupee.push_back(liste1.front());
            liste1.erase(liste1.begin()); // → on avance dans la liste contenant le plus petit element
        }
        else
        {
            listeRegroupee.push_back(liste2.front());
            liste2.erase(liste2.begin()); // → on avance dans la liste contenant le plus petit element
        }
    }
    // → on copie les elements restant de la liste non vide dans la liste de sortie pour obtenir une liste triee
    if (liste1.size() == 0)
    {
        while(liste2.size() > 0)
        {
            listeRegroupee.push_back(liste2.front());
            liste2.erase(liste2.begin());
        }
    }
    else if (liste2.size() == 0)
    {
        while(liste1.size() > 0)
        {
            listeRegroupee.push_back(liste1.front());
            liste1.erase(liste1.begin());
        }
    }
}

/** ----------------------------------------------------------------------
 \brief Ce module permet de regrouper deux listes par ordre d'interprete
 \param [in] liste1 : Premiere liste de chansons a regrouper
 \param [in] liste2 : Deuxieme liste de chansons a regrouper
 \param [in] listeRegroupee : Liste de chansons regroupee
 \param [out] listeRegroupee : Liste de chansons regroupee
 ----------------------------------------------------------------------- **/
void regrouperInterprete(vector<chanson_t> liste1, vector<chanson_t> liste2, vector<chanson_t> &listeRegroupee) {
    
    // → tant qu'une des listes n'est pas vide
    while ( liste1.size() > 0 && liste2.size() > 0 )
    {
        // → on compare les elements courants des deux listes
        // → on choisit le plus petit element
        // → on le copie dans la liste de sortie
        if ( liste1.front().interprete < liste2.front().interprete )
        {
            listeRegroupee.push_back(liste1.front());
            liste1.erase(liste1.begin()); // → on avance dans la liste contenant le plus petit element
        }
        else
        {
            listeRegroupee.push_back(liste2.front());
            liste2.erase(liste2.begin()); // → on avance dans la liste contenant le plus petit element
        }
    }
    // → on copie les elements restant de la liste non vide dans la liste de sortie pour obtenir une liste triee
    if (liste1.size() == 0)
    {
        while(liste2.size() > 0)
        {
            listeRegroupee.push_back(liste2.front());
            liste2.erase(liste2.begin());
        }
    }
    else if (liste2.size() == 0)
    {
        while(liste1.size() > 0)
        {
            listeRegroupee.push_back(liste1.front());
            liste1.erase(liste1.begin());
        }
    }
}