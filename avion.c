#include "avion.h"
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <myconio.h>

typedef struct liste
{
    element *head;
    element *tail;
} liste;
/*****/
static liste piste;

/********************************/

void cree_liste()
{
    piste.head = NULL;
    piste.tail = NULL;
}

/***/

unsigned vide_liste()
{
    return (piste.head == NULL && piste.tail == NULL);
}

/***/

int taille_liste_av()
{
    int nb = 0;
    element *tmp = piste.head;
    while (tmp)
    {
        nb++;
        tmp = tmp->suivant;
    }
    return nb;
}

/*******RECHERCHE*******/

unsigned recherche_av(char *ch)
{
    element *aux = piste.head;
    while (aux && strcmp(ch, aux->avion->identifiant) != 0)
        aux = aux->suivant;
    if (aux)
        return 1;
    return 0;
}
unsigned recherche_cp(char *ch)
{
    element *aux = piste.head;
    while (aux && strcmp(ch, aux->avion->compagnie->nom) != 0)
        aux = aux->suivant;
    if (aux)
        return 1;
    return 0;
}
unsigned recherche_de(char *ch)
{
    element *aux = piste.head;
    while (aux && strcmp(ch, aux->avion->heur_deco) != 0)
        aux = aux->suivant;
    if (aux)
        return 1;
    return 0;
}

void recherche_ident()
{
    char ch[7];
    do
    {
        printf(" Donner l'identifiant d'avion a recherche: ");
        scanf("%s", ch);
    } while (!((strlen(ch) == 6) && (toupper(ch[0]) <= 'Z') && (toupper(ch[0]) >= 'A') && (toupper(ch[1]) <= 'Z') && (toupper(ch[1]) >= 'A') && (toupper(ch[2]) <= 'Z') && (toupper(ch[2]) >= 'A') && ((ch[3]) <= '9') && ((ch[3]) >= '0') && ((ch[4]) <= '9') && (toupper(ch[4]) >= '0') && ((ch[5]) <= '9') && ((ch[5]) >= '0')));
    if (recherche_av(ch))
    {
        printf(" %s existe dans la liste des avions\n", ch);
        affiche_avion(ch);
    }
    else
        printf(" %s n'existe pas dans la liste des avions\n", ch);
}

void recherche_comp()
{
    char ch[20];
    element *aux = piste.head;
    printf(" Donner la compagnie a rechercher : ");
    fflush(stdin);
    gets(ch);
    if (recherche_cp(ch))
    {
        printf(" %s existe dans la liste des avions\n", ch);
        affiche_comp(ch);
    }
    else
        printf(" %s n'existe pas dans la liste des avions\n", ch);
}
void recherche_deco()
{
    char ch[9];
    element *aux = piste.head;
    do
    {
        printf(" Donner l'heure de decollage a rechercher: ");
        scanf("%s", ch);
    } while (!verif_heure(ch));
    if (recherche_de(ch))
    {
        printf(" %s existe dans la liste des avions\n", ch);
        affiche_deco(ch);
    }
    else
        printf(" %s n'existe pas dans la liste des avions\n", ch);
}

/********AJOUTER*********/
unsigned verif_heure(char *ch)
{
    if (strlen(ch) != 8)
        return 0;
    for (int i = 0; i < strlen(ch); i++)
        if (!isdigit(ch[i]) && ch[i] != ':')
            return 0;
    char hh[3];
    hh[0] = ch[0];
    hh[1] = ch[1];
    hh[2] = '\0';
    char mm[3];
    mm[0] = ch[3];
    mm[1] = ch[4];
    mm[2] = '\0';
    char ss[3];
    ss[0] = ch[6];
    ss[1] = ch[7];
    ss[2] = '\0';

    int heure = atoi(hh);
    int minute = atoi(mm);
    int seconde = atoi(ss);
    return ((seconde >= 0 && seconde <= 59) && (minute >= 0 && minute <= 59) && (heure >= 0 && heure <= 23));
}

unsigned verif_digit(char *ch)
{
    for (int i = 0; ch[i] != '\0'; i++)
    {
        if (!isdigit(ch[i]))
            return 0;
    }
    return 1;
}

void insere_tete_avion()
{
    element *aux = (element *)malloc(sizeof(element));
    aux->avion = (avion *)malloc(sizeof(avion));
    aux->avion->compagnie = (compagnie *)malloc(sizeof(compagnie));
    gotoxy(20, 5);
    printf("+--------------+---------------------+");
    gotoxy(20, 6);
    printf("| IDENTIFIANT ");
    gotoxy(35, 6);
    printf("|");
    gotoxy(57, 6);
    printf("|");

    gotoxy(20, 7);
    printf("+--------------+---------------------+");
    gotoxy(20, 8);
    printf("| CARBURANT ");
    gotoxy(35, 8);
    printf("|");
    gotoxy(57, 8);
    printf("|");

    gotoxy(20, 9);
    printf("+--------------+---------------------+");
    gotoxy(20, 10);
    printf("| CONSOMMATION ");
    gotoxy(35, 10);
    printf("|");
    gotoxy(57, 10);
    printf("|");

    gotoxy(20, 11);
    printf("+--------------+---------------------+");
    gotoxy(20, 12);
    printf("| DECOLLAGE ");
    gotoxy(35, 12);
    printf("|");
    gotoxy(57, 12);
    printf("|");

    gotoxy(20, 13);
    printf("+--------------+---------------------+");
    gotoxy(20, 14);
    printf("| COMPAGNIE ");
    gotoxy(35, 14);
    printf("|");
    gotoxy(57, 14);
    printf("|");

    gotoxy(20, 15);
    printf("+--------------+---------------------+");
    gotoxy(20, 16);
    printf("| ACRONYME ");
    gotoxy(35, 16);
    printf("|");
    gotoxy(57, 16);
    printf("|");

    gotoxy(20, 17);
    printf("+--------------+---------------------+");
    do
    {
        gotoxy(37, 6);
        printf("                   ");
        gotoxy(37, 6);
        scanf("%s", aux->avion->identifiant);
    } while (!(recherche_av(aux->avion->identifiant) == 0 && (strlen(aux->avion->identifiant) == 6) && (toupper(aux->avion->identifiant[0]) <= 'Z') && (toupper(aux->avion->identifiant[0]) >= 'A') && (toupper(aux->avion->identifiant[1]) <= 'Z') && (toupper(aux->avion->identifiant[1]) >= 'A') && (toupper(aux->avion->identifiant[2]) <= 'Z') && (toupper(aux->avion->identifiant[2]) >= 'A') && ((aux->avion->identifiant[3]) <= '9') && ((aux->avion->identifiant[3]) >= '0') && ((aux->avion->identifiant[4]) <= '9') && (toupper(aux->avion->identifiant[4]) >= '0') && ((aux->avion->identifiant[5]) <= '9') && ((aux->avion->identifiant[5]) >= '0')));

    char digit[50];

    do
    {
        gotoxy(37, 8);
        printf("                    ");
        gotoxy(37, 8);
        scanf("%s", digit);
    } while (!verif_digit(digit));
    aux->avion->carburant = atoi(digit);

    do
    {
        gotoxy(37, 10);
        printf("                    ");
        gotoxy(37, 10);
        scanf("%s", digit);
    } while (!verif_digit(digit));
    aux->avion->consommation = atoi(digit);

    do
    {
        gotoxy(37, 12);
        printf("                    ");
        gotoxy(37, 12);
        scanf("%s", aux->avion->heur_deco);
    } while (!verif_heure(aux->avion->heur_deco));

    gotoxy(37, 14);
    printf("                    ");
    gotoxy(37, 14);
    fflush(stdin);
    gets(aux->avion->compagnie->nom);
    do
    {
        gotoxy(37, 16);
        printf("                    ");
        gotoxy(37, 16);
        scanf("%s", aux->avion->compagnie->acronyme);
    } while (!((aux->avion->compagnie->acronyme[0] == toupper(aux->avion->identifiant[0])) && (aux->avion->compagnie->acronyme[1] == toupper(aux->avion->identifiant[1])) && (aux->avion->compagnie->acronyme[2] == toupper(aux->avion->identifiant[2])) && strlen(aux->avion->compagnie->acronyme) == 3));
    gotoxy(20, 18);
    if (vide_liste())
    {
        piste.head = aux;
        piste.tail = aux;
        aux->suivant = NULL;
    }
    else
    {
        aux->suivant = piste.head;
        piste.head = aux;
    }
}

void insere_queue_avion()
{
    element *aux = (element *)malloc(sizeof(element));
    aux->avion = (avion *)malloc(sizeof(avion));
    aux->avion->compagnie = (compagnie *)malloc(sizeof(compagnie));
    gotoxy(20, 5);
    printf("+--------------+---------------------+");
    gotoxy(20, 6);
    printf("| IDENTIFIANT ");
    gotoxy(35, 6);
    printf("|");
    gotoxy(57, 6);
    printf("|");

    gotoxy(20, 7);
    printf("+--------------+---------------------+");
    gotoxy(20, 8);
    printf("| CARBURANT ");
    gotoxy(35, 8);
    printf("|");
    gotoxy(57, 8);
    printf("|");

    gotoxy(20, 9);
    printf("+--------------+---------------------+");
    gotoxy(20, 10);
    printf("| CONSOMMATION ");
    gotoxy(35, 10);
    printf("|");
    gotoxy(57, 10);
    printf("|");

    gotoxy(20, 11);
    printf("+--------------+---------------------+");
    gotoxy(20, 12);
    printf("| DECOLLAGE ");
    gotoxy(35, 12);
    printf("|");
    gotoxy(57, 12);
    printf("|");

    gotoxy(20, 13);
    printf("+--------------+---------------------+");
    gotoxy(20, 14);
    printf("| COMPAGNIE ");
    gotoxy(35, 14);
    printf("|");
    gotoxy(57, 14);
    printf("|");

    gotoxy(20, 15);
    printf("+--------------+---------------------+");
    gotoxy(20, 16);
    printf("| ACRONYME ");
    gotoxy(35, 16);
    printf("|");
    gotoxy(57, 16);
    printf("|");

    gotoxy(20, 17);
    printf("+--------------+---------------------+");
    do
    {
        gotoxy(37, 6);
        printf("                   ");
        gotoxy(37, 6);
        scanf("%s", aux->avion->identifiant);
    } while (!(recherche_av(aux->avion->identifiant) == 0 && (strlen(aux->avion->identifiant) == 6) && (toupper(aux->avion->identifiant[0]) <= 'Z') && (toupper(aux->avion->identifiant[0]) >= 'A') && (toupper(aux->avion->identifiant[1]) <= 'Z') && (toupper(aux->avion->identifiant[1]) >= 'A') && (toupper(aux->avion->identifiant[2]) <= 'Z') && (toupper(aux->avion->identifiant[2]) >= 'A') && ((aux->avion->identifiant[3]) <= '9') && ((aux->avion->identifiant[3]) >= '0') && ((aux->avion->identifiant[4]) <= '9') && (toupper(aux->avion->identifiant[4]) >= '0') && ((aux->avion->identifiant[5]) <= '9') && ((aux->avion->identifiant[5]) >= '0')));

    char digit[50];

    do
    {
        gotoxy(37, 8);
        printf("                    ");
        gotoxy(37, 8);
        scanf("%s", digit);
    } while (!verif_digit(digit));
    aux->avion->carburant = atoi(digit);

    do
    {
        gotoxy(37, 10);
        printf("                    ");
        gotoxy(37, 10);
        scanf("%s", digit);
    } while (!verif_digit(digit));
    aux->avion->consommation = atoi(digit);

    do
    {
        gotoxy(37, 12);
        printf("                    ");
        gotoxy(37, 12);
        scanf("%s", aux->avion->heur_deco);
    } while (!verif_heure(aux->avion->heur_deco));

    gotoxy(37, 14);
    printf("                    ");
    gotoxy(37, 14);
    fflush(stdin);
    gets(aux->avion->compagnie->nom);
    do
    {
        gotoxy(37, 16);
        printf("                    ");
        gotoxy(37, 16);
        scanf("%s", aux->avion->compagnie->acronyme);
    } while (!((aux->avion->compagnie->acronyme[0] == toupper(aux->avion->identifiant[0])) && (aux->avion->compagnie->acronyme[1] == toupper(aux->avion->identifiant[1])) && (aux->avion->compagnie->acronyme[2] == toupper(aux->avion->identifiant[2])) && strlen(aux->avion->compagnie->acronyme) == 3));
    gotoxy(20, 18);
    aux->suivant = NULL;
    if (vide_liste())
    {
        piste.head = aux;
        piste.tail = aux;
    }
    else
    {
        piste.tail->suivant = aux;
        piste.tail = aux;
    }
}

void insere_pos_avion()
{
    int x;
    printf(" Saisit La position de l'insertion : ");
    scanf("%d", &x);
    if (x == 1)
    {
        insere_tete_avion();
        return;
    }
    if (x == taille_liste_av() + 1)
    {
        insere_queue_avion();
        return;
    }
    element *aux = (element *)malloc(sizeof(element));
    aux->avion = (avion *)malloc(sizeof(avion));
    aux->avion->compagnie = (compagnie *)malloc(sizeof(compagnie));
    gotoxy(20, 5);
    printf("+--------------+---------------------+");
    gotoxy(20, 6);
    printf("| IDENTIFIANT ");
    gotoxy(35, 6);
    printf("|");
    gotoxy(57, 6);
    printf("|");

    gotoxy(20, 7);
    printf("+--------------+---------------------+");
    gotoxy(20, 8);
    printf("| CARBURANT ");
    gotoxy(35, 8);
    printf("|");
    gotoxy(57, 8);
    printf("|");

    gotoxy(20, 9);
    printf("+--------------+---------------------+");
    gotoxy(20, 10);
    printf("| CONSOMMATION ");
    gotoxy(35, 10);
    printf("|");
    gotoxy(57, 10);
    printf("|");

    gotoxy(20, 11);
    printf("+--------------+---------------------+");
    gotoxy(20, 12);
    printf("| DECOLLAGE ");
    gotoxy(35, 12);
    printf("|");
    gotoxy(57, 12);
    printf("|");

    gotoxy(20, 13);
    printf("+--------------+---------------------+");
    gotoxy(20, 14);
    printf("| COMPAGNIE ");
    gotoxy(35, 14);
    printf("|");
    gotoxy(57, 14);
    printf("|");

    gotoxy(20, 15);
    printf("+--------------+---------------------+");
    gotoxy(20, 16);
    printf("| ACRONYME ");
    gotoxy(35, 16);
    printf("|");
    gotoxy(57, 16);
    printf("|");

    gotoxy(20, 17);
    printf("+--------------+---------------------+");
    do
    {
        gotoxy(37, 6);
        printf("                   ");
        gotoxy(37, 6);
        scanf("%s", aux->avion->identifiant);
    } while (!(recherche_av(aux->avion->identifiant) == 0 && (strlen(aux->avion->identifiant) == 6) && (toupper(aux->avion->identifiant[0]) <= 'Z') && (toupper(aux->avion->identifiant[0]) >= 'A') && (toupper(aux->avion->identifiant[1]) <= 'Z') && (toupper(aux->avion->identifiant[1]) >= 'A') && (toupper(aux->avion->identifiant[2]) <= 'Z') && (toupper(aux->avion->identifiant[2]) >= 'A') && ((aux->avion->identifiant[3]) <= '9') && ((aux->avion->identifiant[3]) >= '0') && ((aux->avion->identifiant[4]) <= '9') && (toupper(aux->avion->identifiant[4]) >= '0') && ((aux->avion->identifiant[5]) <= '9') && ((aux->avion->identifiant[5]) >= '0')));

    char digit[50];

    do
    {
        gotoxy(37, 8);
        printf("                    ");
        gotoxy(37, 8);
        scanf("%s", digit);
    } while (!verif_digit(digit));
    aux->avion->carburant = atoi(digit);

    do
    {
        gotoxy(37, 10);
        printf("                    ");
        gotoxy(37, 10);
        scanf("%s", digit);
    } while (!verif_digit(digit));
    aux->avion->consommation = atoi(digit);

    do
    {
        gotoxy(37, 12);
        printf("                    ");
        gotoxy(37, 12);
        scanf("%s", aux->avion->heur_deco);
    } while (!verif_heure(aux->avion->heur_deco));

    gotoxy(37, 14);
    printf("                    ");
    gotoxy(37, 14);
    fflush(stdin);
    gets(aux->avion->compagnie->nom);
    do
    {
        gotoxy(37, 16);
        printf("                    ");
        gotoxy(37, 16);
        scanf("%s", aux->avion->compagnie->acronyme);
    } while (!((aux->avion->compagnie->acronyme[0] == toupper(aux->avion->identifiant[0])) && (aux->avion->compagnie->acronyme[1] == toupper(aux->avion->identifiant[1])) && (aux->avion->compagnie->acronyme[2] == toupper(aux->avion->identifiant[2])) && strlen(aux->avion->compagnie->acronyme) == 3));
    gotoxy(20, 18);
    aux->suivant = NULL;
    element *auxi = piste.head;
    element *forfree;
    int k = 0;
    while (k != x - 2)
    {
        k++;
        auxi = auxi->suivant;
    }
    forfree = auxi->suivant;
    auxi->suivant = aux;
    aux->suivant = forfree;
}

/**************SUPPRIMER*****************/

void supprimer_tete_av()
{
    element *q = piste.head;
    piste.head = q->suivant;
    free(q);
    if (piste.head == NULL)
        piste.tail = NULL;
}
void supprimer_queue_av()
{
    element *aux1 = piste.head, *aux2, *aux3;
    if (piste.head == piste.tail)
    {
        aux3 = piste.head;
        free(aux3);
        piste.head = NULL;
        piste.tail = NULL;
    }
    else
    {
        while (aux1->suivant)
        {
            aux2 = aux1;
            aux1 = aux1->suivant;
        }
        piste.tail = aux2;
        piste.tail->suivant = NULL;
        free(aux1);
    }
}
void suppression_pos_av()
{
    int pos;
    do
    {
        printf(" A partir de quelle position voulez vous supprimer : ");
        scanf("%d", &pos);
    } while (pos < 1 || pos > taille_liste_av());
    if (pos == 1)
        cree_liste();
    else if (pos == taille_liste_av())
        supprimer_queue_av();
    else
    {
        element *aux = piste.head;
        while (pos - 1)
        {
            pos--;
            aux = aux->suivant;
        }
        element *s = piste.head;
        while (s->suivant != aux)
        {
            s = s->suivant;
        }
        s->suivant = NULL;
        piste.tail = s;
        element *a;
        while (aux)
        {
            a = aux->suivant;
            free(aux);
            aux = a;
        }
        free(a);
    }
}

void suppression_av_donne()
{
    element *aux = piste.head;
    char info[7];
    printf(" Donner l'identifiant d'avion a supprimer: ");
    scanf("%s", info);
    if (recherche_av(info))
    {
        if (strcmp(info, aux->avion->identifiant) == 0)
            supprimer_tete_av();
        else if (strcmp(info, piste.tail->avion->identifiant) == 0)
            supprimer_queue_av();
        else
        {
            while (strcmp(info, aux->suivant->avion->identifiant) != 0)
            {
                aux = aux->suivant;
            }
            aux->suivant = aux->suivant->suivant;
        }
    }
    else
        printf(" Cette avion n'existe pas!\n");
}
void suppression_comp_donne()
{
    char ch[20];
    printf(" Donner la compagnie a supprimer : ");
    fflush(stdin);
    gets(ch);
    element *tmp = piste.head;
    do
    {
        while (tmp && strcmp(ch, tmp->avion->compagnie->nom))
            tmp = tmp->suivant;
        if (piste.head == tmp)
        {
            supprimer_tete_av();
            tmp = piste.head;
        }
        else if (tmp == piste.tail)
        {
            supprimer_queue_av();
            return;
        }
        else
        {
            if (tmp)
            {
                element *aux = piste.head;
                while (aux->suivant != tmp)
                    aux = aux->suivant;
                element *freed = aux->suivant;
                aux->suivant = freed->suivant;
                free(freed);
                tmp = piste.head;
            }
        }
    } while (tmp);
}

/*****MODIFIER*****/
void modifier_ident()
{
    char ch[7], ch1[7], ac[4];
    printf(" Donner l'ancien identifiant a modifier : ");
    scanf("%s", ch);
    do
    {
        printf(" Donner le nouveau identifiant : ");
        scanf("%s", ch1);
    } while (recherche_av(ch1));
    if (recherche_av(ch))
    {
        element *tmp = piste.head;
        while (tmp && strcmp(ch, tmp->avion->identifiant))
            tmp = tmp->suivant;
        if (tmp)
        {
            ac[0] = toupper(ch1[0]);
            ac[1] = toupper(ch1[1]);
            ac[2] = toupper(ch1[2]);
            strcpy(tmp->avion->identifiant, ch1);
            strcpy(tmp->avion->compagnie->acronyme, ac);
        }
    }
    else
        printf(" Cette avion n'existe pas !\n");
}

void modifier_comp()
{
    char ch[7];
    char ch1[20];
    printf(" Donner l'identifiant d'avion concernee : ");
    scanf(" %s", ch);
    fflush(stdin);
    gets(ch1);
    element *tmp = piste.head;
    while (tmp && strcmp(ch, tmp->avion->identifiant))
        tmp = tmp->suivant;
    if (tmp)
        strcpy(tmp->avion->compagnie->nom, ch1);
    else
        printf(" Verifier l'identifiant svp !");
}

/******TRI******/
void tri_avion()
{
    int i;
    avion *m;
    element *tmp = piste.head, *tmp1 = tmp->suivant;
    for (i = 0; i < taille_liste_av(); i++)
    {
        tmp = piste.head;
        tmp1 = tmp->suivant;
        while (tmp->suivant && tmp1)
        {
            if (tmp->avion->consommation > tmp1->avion->consommation)
            {
                m = tmp->avion;
                tmp->avion = tmp1->avion;
                tmp1->avion = m;
            }
            tmp = tmp->suivant;
            tmp1 = tmp1->suivant;
        }
    }
}

/*****AFFICHE*****/
void affiche_avion_donne()
{
    element *aux = piste.head;
    char info[7];
    printf(" Donner l'identifiant d'avion a afficher: ");
    scanf("%s", info);
    if (recherche_av(info))
    {
        while (strcmp(info, aux->avion->identifiant) && aux)
            aux = aux->suivant;
        gotoxy(11, 5);
        printf("+---+---------------+-------------+----------------+-------------+---------------------+------------+");
        gotoxy(11, 6);
        printf("| # |  Identifiant  |  Carburant  |  Consommation  |  Decollage  |      Compagnie      |  Acronyme  |");
        gotoxy(11, 7);
        printf("+---+---------------+-------------+----------------+-------------+---------------------+------------+");
        if (aux)
        {
            gotoxy(11, 8);
            printf("| %d | ", 1);
            gotoxy(18, 8);
            printf("%s", aux->avion->identifiant);
            gotoxy(31, 8);
            printf("|");
            gotoxy(34, 8);
            printf("%d", aux->avion->carburant);
            gotoxy(45, 8);
            printf("|");
            gotoxy(48, 8);
            printf("%d", aux->avion->consommation);
            gotoxy(62, 8);
            printf("|");
            gotoxy(65, 8);
            printf("%s", aux->avion->heur_deco);
            gotoxy(76, 8);
            printf("|");
            gotoxy(80, 8);
            printf("%s", aux->avion->compagnie->nom);
            gotoxy(98, 8);
            printf("|");
            gotoxy(103, 8);
            printf("%s", aux->avion->compagnie->acronyme);
            gotoxy(111, 8);
            printf("|");
            gotoxy(11, 9);
            printf("+---+---------------+-------------+----------------+-------------+---------------------+------------+");
        }
    }
    else
        printf(" L'identifiant n'existe pas !");
    printf("\n");
}
void affiche_liste_donne()
{
    int i = 1, y = 8;
    element *aux = piste.head;
    if (vide_liste())
    {
        printf(" Aucun Avion a afficher !\n");
        return;
    }
    gotoxy(11, 5);
    printf("+---+---------------+-------------+----------------+-------------+---------------------+------------+");
    gotoxy(11, 6);
    printf("| # |  Identifiant  |  Carburant  |  Consommation  |  Decollage  |      Compagnie      |  Acronyme  |");
    gotoxy(11, 7);
    printf("+---+---------------+-------------+----------------+-------------+---------------------+------------+");

    while (aux)
    {
        gotoxy(11, y);
        printf("| %d | ", i);
        gotoxy(18, y);
        printf("%s", aux->avion->identifiant);
        gotoxy(31, y);
        printf("|");
        gotoxy(34, y);
        printf("%d", aux->avion->carburant);
        gotoxy(45, y);
        printf("|");
        gotoxy(48, y);
        printf("%d", aux->avion->consommation);
        gotoxy(62, y);
        printf("|");
        gotoxy(65, y);
        printf("%s", aux->avion->heur_deco);
        gotoxy(76, y);
        printf("|");
        gotoxy(80, y);
        printf("%s", aux->avion->compagnie->nom);
        gotoxy(98, y);
        printf("|");
        gotoxy(103, y);
        printf("%s", aux->avion->compagnie->acronyme);
        gotoxy(111, y);
        printf("|");
        gotoxy(11, y + 1);
        printf("+---+---------------+-------------+----------------+-------------+---------------------+------------+");
        aux = aux->suivant;
        i++;
        y += 2;
    }
    printf("\n");
}
void affiche_comp_donne()
{
    int i = 1, y = 8;
    char ch[20];
    element *aux = piste.head;
    printf(" Donner la compagnie a rechercher : ");
    fflush(stdin);
    gets(ch);

    if (recherche_cp(ch))
    {
        gotoxy(11, 5);
        printf("+---+---------------+-------------+----------------+-------------+---------------------+------------+");
        gotoxy(11, 6);
        printf("| # |  Identifiant  |  Carburant  |  Consommation  |  Decollage  |      Compagnie      |  Acronyme  |");
        gotoxy(11, 7);
        printf("+---+---------------+-------------+----------------+-------------+---------------------+------------+");

        while (aux)
        {
            if (strcmp(aux->avion->compagnie->nom, ch) == 0)
            {
                gotoxy(11, y);
                printf("| %d | ", i);
                gotoxy(18, y);
                printf("%s", aux->avion->identifiant);
                gotoxy(31, y);
                printf("|");
                gotoxy(34, y);
                printf("%d", aux->avion->carburant);
                gotoxy(45, y);
                printf("|");
                gotoxy(48, y);
                printf("%d", aux->avion->consommation);
                gotoxy(62, y);
                printf("|");
                gotoxy(65, y);
                printf("%s", aux->avion->heur_deco);
                gotoxy(76, y);
                printf("|");
                gotoxy(80, y);
                printf("%s", aux->avion->compagnie->nom);
                gotoxy(98, y);
                printf("|");
                gotoxy(103, y);
                printf("%s", aux->avion->compagnie->acronyme);
                gotoxy(111, y);
                printf("|");
                gotoxy(11, y + 1);
                printf("+---+---------------+-------------+----------------+-------------+---------------------+------------+");
                i++;
                y += 2;
            }
            aux = aux->suivant;
        }
    }
    else
        printf(" La compagnie %s n'existe pas !", ch);
    printf("\n");
}

void affiche_avion(char *info)
{
    element *aux = piste.head;
    while (strcmp(info, aux->avion->identifiant) && aux)
        aux = aux->suivant;
    gotoxy(11, 5);
    printf("+---+---------------+-------------+----------------+-------------+---------------------+------------+");
    gotoxy(11, 6);
    printf("| # |  Identifiant  |  Carburant  |  Consommation  |  Decollage  |      Compagnie      |  Acronyme  |");
    gotoxy(11, 7);
    printf("+---+---------------+-------------+----------------+-------------+---------------------+------------+");
    if (aux)
    {
        gotoxy(11, 8);
        printf("| %d | ", 1);
        gotoxy(18, 8);
        printf("%s", aux->avion->identifiant);
        gotoxy(31, 8);
        printf("|");
        gotoxy(34, 8);
        printf("%d", aux->avion->carburant);
        gotoxy(45, 8);
        printf("|");
        gotoxy(48, 8);
        printf("%d", aux->avion->consommation);
        gotoxy(62, 8);
        printf("|");
        gotoxy(65, 8);
        printf("%s", aux->avion->heur_deco);
        gotoxy(76, 8);
        printf("|");
        gotoxy(80, 8);
        printf("%s", aux->avion->compagnie->nom);
        gotoxy(98, 8);
        printf("|");
        gotoxy(103, 8);
        printf("%s", aux->avion->compagnie->acronyme);
        gotoxy(111, 8);
        printf("|");
        gotoxy(11, 9);
        printf("+---+---------------+-------------+----------------+-------------+---------------------+------------+");
    }
    printf("\n");
}
void affiche_comp(char *info)
{
    int i = 1, y = 8;
    element *aux = piste.head;

    gotoxy(11, 5);
    printf("+---+---------------+-------------+----------------+-------------+---------------------+------------+");
    gotoxy(11, 6);
    printf("| # |  Identifiant  |  Carburant  |  Consommation  |  Decollage  |      Compagnie      |  Acronyme  |");
    gotoxy(11, 7);
    printf("+---+---------------+-------------+----------------+-------------+---------------------+------------+");

    while (aux)
    {
        if (strcmp(aux->avion->compagnie->nom, info) == 0)
        {
            gotoxy(11, y);
            printf("| %d | ", i);
            gotoxy(18, y);
            printf("%s", aux->avion->identifiant);
            gotoxy(31, y);
            printf("|");
            gotoxy(34, y);
            printf("%d", aux->avion->carburant);
            gotoxy(45, y);
            printf("|");
            gotoxy(48, y);
            printf("%d", aux->avion->consommation);
            gotoxy(62, y);
            printf("|");
            gotoxy(65, y);
            printf("%s", aux->avion->heur_deco);
            gotoxy(76, y);
            printf("|");
            gotoxy(80, y);
            printf("%s", aux->avion->compagnie->nom);
            gotoxy(98, y);
            printf("|");
            gotoxy(103, y);
            printf("%s", aux->avion->compagnie->acronyme);
            gotoxy(111, y);
            printf("|");
            gotoxy(11, y + 1);
            printf("+---+---------------+-------------+----------------+-------------+---------------------+------------+");
            i++;
            y += 2;
        }
        aux = aux->suivant;
    }
    printf("\n");
}
void affiche_deco(char *info)
{
    int i = 1, y = 8;
    element *aux = piste.head;

    gotoxy(11, 5);
    printf("+---+---------------+-------------+----------------+-------------+---------------------+------------+");
    gotoxy(11, 6);
    printf("| # |  Identifiant  |  Carburant  |  Consommation  |  Decollage  |      Compagnie      |  Acronyme  |");
    gotoxy(11, 7);
    printf("+---+---------------+-------------+----------------+-------------+---------------------+------------+");

    while (aux)
    {
        if (strcmp(aux->avion->heur_deco, info) == 0)
        {
            gotoxy(11, y);
            printf("| %d | ", i);
            gotoxy(18, y);
            printf("%s", aux->avion->identifiant);
            gotoxy(31, y);
            printf("|");
            gotoxy(34, y);
            printf("%d", aux->avion->carburant);
            gotoxy(45, y);
            printf("|");
            gotoxy(48, y);
            printf("%d", aux->avion->consommation);
            gotoxy(62, y);
            printf("|");
            gotoxy(65, y);
            printf("%s", aux->avion->heur_deco);
            gotoxy(76, y);
            printf("|");
            gotoxy(80, y);
            printf("%s", aux->avion->compagnie->nom);
            gotoxy(98, y);
            printf("|");
            gotoxy(103, y);
            printf("%s", aux->avion->compagnie->acronyme);
            gotoxy(111, y);
            printf("|");
            gotoxy(11, y + 1);
            printf("+---+---------------+-------------+----------------+-------------+---------------------+------------+");
            i++;
            y += 2;
        }
        aux = aux->suivant;
    }
    printf("\n");
}
/*****CHARGEMENT*****/

void inserer_queue(avion *info, compagnie *comp)
{
    element *new = (element *)malloc(sizeof(element));
    new->avion = (avion *)malloc(sizeof(avion));
    new->avion->compagnie = (compagnie *)malloc(sizeof(compagnie));
    new->avion->carburant = info->carburant;
    new->avion->consommation = info->consommation;
    strcpy(new->avion->heur_deco, info->heur_deco);
    strcpy(new->avion->identifiant, info->identifiant);
    *(new->avion->compagnie) = *comp;
    new->suivant = NULL;
    if (vide_liste())
    {
        piste.head = new;
    }
    else
    {
        (piste.tail)->suivant = new;
    }
    piste.tail = new;
}
void Enregistrement()
{
    FILE *F = fopen("chargement.txt", "w+");
    element *aux = piste.head;
    while (aux)
    {
        fprintf(F, "%s/%d/%d/%s/%s/%s/ \n", aux->avion->identifiant, aux->avion->carburant, aux->avion->consommation, aux->avion->heur_deco, aux->avion->compagnie->nom, aux->avion->compagnie->acronyme);
        aux = aux->suivant;
    }
    fclose(F);
}
void Chargement()
{
    element *aux = (element *)malloc(sizeof(element));
    aux->avion = (avion *)malloc(sizeof(avion));
    aux->avion->compagnie = (compagnie *)malloc(sizeof(compagnie));
    FILE *F = fopen("chargement.txt", "r+");
    while (fscanf(F, "%[^/]/%d/%d/%[^/]/%[^/]/%[^/]/ ", aux->avion->identifiant, &aux->avion->carburant, &aux->avion->consommation, aux->avion->heur_deco, aux->avion->compagnie->nom, aux->avion->compagnie->acronyme) != EOF)
    {
        inserer_queue(aux->avion, aux->avion->compagnie);
    }
    fclose(F);
}

/*****FICHIER*****/
int fich_vide()
{
    long a;
    int b;
    FILE *f = fopen("chargement.txt", "r");
    fseek(f, 0, SEEK_END);
    a = (long)ftell(f);
    if (a != 0)
        return 0;
    else
        return 1;
}
