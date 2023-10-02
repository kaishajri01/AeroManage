typedef struct compagnie
{
    char nom[50];
    char acronyme[4];
} compagnie;
typedef struct avion
{
    char identifiant[7];
    int carburant;
    int consommation;
    char heur_deco[9];
    compagnie *compagnie;
} avion;
typedef struct element
{
    avion *avion;
    struct element *suivant;
} element;

/*********************/

void cree_liste();
unsigned vide_liste();
int taille_liste_av();

unsigned recherche_av(char *);
unsigned recherche_cp(char *);
unsigned recherche_de(char *);

void recherche_ident();
void recherche_comp();
void recherche_deco();

unsigned verif_heure(char *);
unsigned verif_digit(char *);

void insere_tete_avion();
void insere_queue_avion();
void insere_pos_avion();

void supprimer_tete_av();
void supprimer_queue_av();
void suppression_pos_av();
void suppression_av_donne();
void suppression_comp_donne();

void modifier_ident();
void modifier_comp();
void tri_avion();

void affiche_avion_donne();
void affiche_comp_donne();
void affiche_liste_donne();

void affiche_avion(char *);
void affiche_comp(char *);
void affiche_deco(char *);

void inserer_queue(avion *, compagnie *);
void Enregistrement();
void Chargement();

int fich_vide();
