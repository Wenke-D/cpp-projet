#ifndef ENVIRONNEMENT_H
#define ENVIRONNEMENT_H

/*
 *	Traduit un fichier de type définition de labyrinthe au format interne.
 */

enum Case {
    /**
     * case vide (où on peut marcher!)
     */
    EMPTY = 0,
    /**
     * case remplit (où on ne peut pas marcher)
     */
    FILL = 1
};

// affiche un message en haut à gauche de l'écran.
extern void message(const char *format, ...);

// affiche en gros si on a gagné ou perdu la partie et invalide les tirs.
extern void partie_terminee(bool winned);

class Mover;

struct Wall {
    int _x1, _y1; // point de depart.
    int _x2, _y2; // point d'arrivée.
    int _ntex;    // numéro de texture.
};

struct Box {
    int _x, _y; // emplacement.
    int _ntex;  // numéro de texture.
};

class Environnement {
  public:
    static const int
        scale; // facteur d'echelle (defini par moi, mais utilise par vous)
    static const char *texture_dir; // répertoire des textures.
    static const char *modele_dir;  // répertoire des personnages.
    /**
     * la fonction de création du labyrinthe à définir DANS Labyrinthe.cpp de la
     *façon suivante:
     *
     * Environnement* Environnement::init (char* filename) {
     *	return new Labyrinthe (filename);
     * }
     *
     *
     */
    static Environnement *init(char *filename);

    /* date of walls */
    Wall *_walls; // les murs sous forme de tableau de segments.
    int _nwall;   // le nombre de segments.
    /* data of pictures */
    Wall *_picts; // les affiches.
    int _npicts;  // leur nombre.
    /* data of boxes */
    Box *_boxes; // les caisses.
    int _nboxes; // leur nombre.
    /* data of marks (pictures in the ground) */
    Box *_marks; // les marques au sol.
    int _nmarks; // leur nombre.
    /* data of the treasure */
    Box _treasor; // le trésor.
    /* data of guards */
    Mover **_guards; // les gardes (tableau de pointeurs de gardiens).
    int _nguards;    // leur nombre.

    virtual int width() = 0;             // retourne la largeur du labyrinthe.
    virtual int height() = 0;            // retourne la longueur du labyrinthe.
    virtual char data(int i, int j) = 0; // retourne la case (i, j).
    virtual ~Environnement() {}

    /**
     * Reconsidere le labyrinthe pour le reafficher.
     * Fonction a n'appeller QUE si les murs ou les caisses ou le tresor BOUGENT
     */
    void reconfigure();

    /**
     * Load the image for walls
     * @param texture filename of image
     * @return retourne le numero de texture pour le fichier image passé en
     * argument.
     */
    int wall_texture(char *texture);

    /**
     * Recrée les boules de feu des movers.
     * fonction a n'appeller QUE si des gardiens sont recréés.
     */
    void make_fireballs(void);
};

#endif
