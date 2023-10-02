#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif
#include "avion.h"
#include <tchar.h>
//#include <myconio.h>
#include <stdio.h>
#include <windows.h>

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void addmenus(HWND);
void CreateBtt(HWND hwnd);

HWND hname, hage, hout, hogo, Add, Finnish;
HDC hdc;
HMENU hmenu;

HBITMAP hlogoImage, hgenerateImage;
int intro = 1;
char ch[30];
long p;
/*  Make the class name into a global variable  */
TCHAR szClassName[] = _T("Gestionnaire d'aeroport");

int WINAPI WinMain(HINSTANCE hThisInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszArgument,
                   int nCmdShow)
{
    HWND hwnd;        /* This is the handle for our window */
    MSG messages;     /* Here messages to the application are saved */
    WNDCLASSEX wincl; /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure; /* This function is called by windows */
    wincl.style = CS_DBLCLKS;            /* Catch double-clicks */
    wincl.cbSize = sizeof(WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL; /* No menu */
    wincl.cbClsExtra = 0;      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND + 7;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx(&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx(
        0,                             /* Extended possibilites for variation */
        szClassName,                   /* Classname */
        _T("Gestionnaire d'aeroport"), /* Title Text */
        WS_OVERLAPPEDWINDOW,           /* default window */
        CW_USEDEFAULT,                 /* Windows decides the position */
        CW_USEDEFAULT,                 /* where the window ends up on the screen */
        1920,                          /* The programs width */
        1080,                          /* and height in pixels */
        HWND_DESKTOP,                  /* The window is a child-window to desktop */
        NULL,                          /* No menu */
        hThisInstance,                 /* Program Instance handler */
        NULL                           /* No Window Creation data */
    );

    /* Make the window visible on the screen */
    ShowWindow(hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage(&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HBITMAP hBmp;
    /* if(intro)
    {
        system("start test.exe") ;
        intro=0;
    }*/

    switch (message) /* handle the messages */
    {

    case WM_COMMAND:
        switch (wParam)
        {
        case 1:
            system("cls");
            if (fich_vide())
            {
                if (!vide_liste())
                    MessageBox(hwnd, " La liste n'est pas vide\nEssayer de faire le mise a jour", " CREATION", MB_OK | MB_ICONHAND);
                else
                {
                    cree_liste();
                    system("color 9F");
                    ShowWindow(hwnd, SW_HIDE);
                    printf("\n\t\t\t  - Ajout en tete -   \n");
                    insere_tete_avion();
                    system("pause");
                    ShowWindow(hwnd, SW_NORMAL);
                    system("cls");
                    while (MessageBox(hwnd, "       Vous voulez ajouter un autre avion ?", " CREATION", MB_YESNO | MB_ICONQUESTION) == IDYES)
                    {
                        system("cls");
                        system("color 9F");
                        ShowWindow(hwnd, SW_HIDE);
                        printf("\n\t\t\t  - Ajout en queue -  \n");
                        insere_queue_avion();
                        system("pause");
                        ShowWindow(hwnd, SW_NORMAL);
                        system("cls");
                    }
                }
            }
            else
            {
                MessageBox(hwnd, "       Le fichier n'est pas vide\nEssayer de faire le chargement", " CREATION", MB_OK | MB_ICONWARNING);
            }
            break;
        case 211:
            if (vide_liste())
            {
                if (fich_vide())
                    MessageBox(hwnd, "       Essayer de faire la creation", " AJOUT", MB_OK | MB_ICONWARNING);
                else
                    MessageBox(hwnd, "       Le fichier n'est pas vide\nEssayer de faire le chargement", " AJOUT", MB_OK | MB_ICONWARNING);
            }
            else
            {
                system("cls");
                system("color 9F");
                ShowWindow(hwnd, SW_HIDE);
                printf("\n\t\t\t  - Ajout en tete -   \n");
                insere_tete_avion();
                system("pause");
                ShowWindow(hwnd, SW_NORMAL);
                system("cls");
            }
            break;
        case 212:
            if (vide_liste())
            {
                if (fich_vide())
                    MessageBox(hwnd, "       Essayer de faire la creation", " AJOUT", MB_OK | MB_ICONWARNING);
                else
                    MessageBox(hwnd, "       Le fichier n'est pas vide\nEssayer de faire le chargement", " AJOUT", MB_OK | MB_ICONWARNING);
            }
            else
            {
                system("cls");
                system("color 9F");
                ShowWindow(hwnd, SW_HIDE);
                printf("\n\t\t\t  - Ajout en queue -   \n");
                insere_queue_avion();
                system("pause");
                ShowWindow(hwnd, SW_NORMAL);
                system("cls");
            }
            break;
        case 213:
            if (vide_liste())
            {
                if (fich_vide())
                    MessageBox(hwnd, "       Essayer de faire la creation", " AJOUT", MB_OK | MB_ICONWARNING);
                else
                    MessageBox(hwnd, "       Le fichier n'est pas vide\nEssayer de faire le chargement", " AJOUT", MB_OK | MB_ICONWARNING);
            }
            else
            {
                system("cls");
                system("color 9F");
                ShowWindow(hwnd, SW_HIDE);
                printf("\n\t\t\t  - Ajout dans une position -  \n");
                insere_pos_avion();
                system("pause");
                ShowWindow(hwnd, SW_NORMAL);
                system("cls");
            }
            break;
        case 221:
            if (vide_liste())
            {
                if (fich_vide())
                    MessageBox(hwnd, "       Essayer de faire la creation", " SUPPRIME", MB_OK | MB_ICONWARNING);
                else
                    MessageBox(hwnd, "       Le fichier n'est pas vide\nEssayer de faire le chargement", " SUPPRIME", MB_OK | MB_ICONWARNING);
            }
            else if (MessageBox(hwnd, "       Vous voulez Supprimer en tete ?", " SUPPRIME", MB_YESNO | MB_ICONQUESTION) == IDYES)
            {
                supprimer_tete_av();
            }
            break;
        case 222:
            if (vide_liste())
            {
                if (fich_vide())
                    MessageBox(hwnd, "       Essayer de faire la creation", " SUPPRIME", MB_OK | MB_ICONWARNING);
                else
                    MessageBox(hwnd, "       Le fichier n'est pas vide\nEssayer de faire le chargement", " SUPPRIME", MB_OK | MB_ICONWARNING);
            }
            else if (MessageBox(hwnd, "       Vous voulez Supprimer en queue ?", " SUPPRIME", MB_YESNO | MB_ICONQUESTION) == IDYES)
            {
                supprimer_queue_av();
            }
            break;
        case 223:
            if (vide_liste())
            {
                if (fich_vide())
                    MessageBox(hwnd, "       Essayer de faire la creation", " SUPPRIME", MB_OK | MB_ICONWARNING);
                else
                    MessageBox(hwnd, "       Le fichier n'est pas vide\nEssayer de faire le chargement", " SUPPRIME", MB_OK | MB_ICONWARNING);
            }
            else
            {
                system("cls");
                system("color 9F");
                ShowWindow(hwnd, SW_HIDE);
                printf("\n\t\t\t\t\t   - Suppession a partir d'une position -  \n");
                suppression_pos_av();
                system("pause");
                ShowWindow(hwnd, SW_NORMAL);
                system("cls");
            }
            break;
        case 224:
            if (vide_liste())
            {
                if (fich_vide())
                    MessageBox(hwnd, "       Essayer de faire la creation", " SUPPRIME", MB_OK | MB_ICONWARNING);
                else
                    MessageBox(hwnd, "       Le fichier n'est pas vide\nEssayer de faire le chargement", " SUPPRIME", MB_OK | MB_ICONWARNING);
            }
            else
            {
                system("cls");
                system("color 9F");
                ShowWindow(hwnd, SW_HIDE);
                printf("\n\t\t\t\t\t   - Suppession d'un avion donne -   \n");
                suppression_av_donne();
                system("pause");
                ShowWindow(hwnd, SW_NORMAL);
                system("cls");
            }
            break;
        case 225:
            if (vide_liste())
            {
                if (fich_vide())
                    MessageBox(hwnd, "       Essayer de faire la creation", " SUPPRIME", MB_OK | MB_ICONWARNING);
                else
                    MessageBox(hwnd, "       Le fichier n'est pas vide\nEssayer de faire le chargement", " SUPPRIME", MB_OK | MB_ICONWARNING);
            }
            else
            {
                system("cls");
                system("color 9F");
                ShowWindow(hwnd, SW_HIDE);
                printf("\n\t\t\t\t\t   - Suppession des avions d'une compagnie donnee -   \n");
                suppression_comp_donne();
                system("pause");
                ShowWindow(hwnd, SW_NORMAL);
                system("cls");
            }
            break;
        case 231:
            if (vide_liste())
            {
                if (fich_vide())
                    MessageBox(hwnd, "       Essayer de faire la creation", " MODIFICATION", MB_OK | MB_ICONWARNING);
                else
                    MessageBox(hwnd, "       Le fichier n'est pas vide\nEssayer de faire le chargement", " MODIFICATION", MB_OK | MB_ICONWARNING);
            }
            else
            {
                system("cls");
                system("color 9F");
                ShowWindow(hwnd, SW_HIDE);
                printf("\n\t\t\t\t\t   - Identifiant -   \n");
                modifier_ident();
                system("pause");
                ShowWindow(hwnd, SW_NORMAL);
                system("cls");
            }
            break;
        case 232:
            if (vide_liste())
            {
                if (fich_vide())
                    MessageBox(hwnd, "       Essayer de faire la creation", " MODIFICATION", MB_OK | MB_ICONWARNING);
                else
                    MessageBox(hwnd, "       Le fichier n'est pas vide\nEssayer de faire le chargement", " MODIFICATION", MB_OK | MB_ICONWARNING);
            }
            else
            {
                system("cls");
                system("color 9F");
                ShowWindow(hwnd, SW_HIDE);
                printf("\n\t\t\t\t\t   - Compagnie -   \n");
                modifier_comp();
                system("pause");
                ShowWindow(hwnd, SW_NORMAL);
                system("cls");
            }
            break;
        case 31:
            if (vide_liste())
            {
                if (fich_vide())
                    MessageBox(hwnd, "       Essayer de faire la creation", " RECHERCHE", MB_OK | MB_ICONWARNING);
                else
                    MessageBox(hwnd, "       Le fichier n'est pas vide\nEssayer de faire le chargement", " RECHERCHE", MB_OK | MB_ICONWARNING);
            }
            else
            {
                system("cls");
                system("color 9F");
                ShowWindow(hwnd, SW_HIDE);
                printf("\n\t\t\t\t\t   - Recherche par identifiant avion -   \n");
                recherche_ident();
                system("pause");
                ShowWindow(hwnd, SW_NORMAL);
                system("cls");
            }
            break;
        case 32:
            if (vide_liste())
            {
                if (fich_vide())
                    MessageBox(hwnd, "       Essayer de faire la creation", " RECHERCHE", MB_OK | MB_ICONWARNING);
                else
                    MessageBox(hwnd, "       Le fichier n'est pas vide\nEssayer de faire le chargement", " RECHERCHE", MB_OK | MB_ICONWARNING);
            }
            else
            {
                system("cls");
                system("color 9F");
                ShowWindow(hwnd, SW_HIDE);
                printf("\n\t\t\t\t\t   - Recherche par compagnie -   \n");
                recherche_comp();
                system("pause");
                ShowWindow(hwnd, SW_NORMAL);
                system("cls");
            }
            break;
        case 33:
            if (vide_liste())
            {
                if (fich_vide())
                    MessageBox(hwnd, "       Essayer de faire la creation", " RECHERCHE", MB_OK | MB_ICONWARNING);
                else
                    MessageBox(hwnd, "       Le fichier n'est pas vide\nEssayer de faire le chargement", " RECHERCHE", MB_OK | MB_ICONWARNING);
            }
            else
            {
                system("color 9F");
                ShowWindow(hwnd, SW_HIDE);
                printf("\n\t\t\t\t\t   - Recherche par heure de decollage -  \n");
                recherche_deco();
                system("pause");
                ShowWindow(hwnd, SW_NORMAL);
                system("cls");
            }
            break;
        case 34:
            if (vide_liste())
            {
                if (fich_vide())
                    MessageBox(hwnd, "       Essayer de faire la creation", " TRI", MB_OK | MB_ICONWARNING);
                else
                    MessageBox(hwnd, "       Le fichier n'est pas vide\nEssayer de faire le chargement", " TRI", MB_OK | MB_ICONWARNING);
            }
            else if (MessageBox(hwnd, "       Vous voulez faire le TRI ?", " TRI", MB_YESNO | MB_ICONQUESTION) == IDYES)
            {
                tri_avion();
            }
            break;
        case 41:
            if (vide_liste())
            {
                if (fich_vide())
                    MessageBox(hwnd, "       Essayer de faire la creation", " ENREGISTREMENT", MB_OK | MB_ICONWARNING);
                else
                    MessageBox(hwnd, "       Le fichier n'est pas vide\nEssayer de faire le chargement", " ENREGISTREMENT", MB_OK | MB_ICONWARNING);
            }
            else if (MessageBox(hwnd, "       Vous voulez enregistrer la liste ?", " ENREGISTREMENT", MB_YESNO | MB_ICONQUESTION) == IDYES)
            {
                Enregistrement();
            }
            break;
        case 42:
            if (fich_vide())
                MessageBox(hwnd, " Essayer de faire la creation\nOu remplir le fichier", " TRI", MB_OK | MB_ICONWARNING);
            else if (MessageBox(hwnd, "       Vous voulez charger une liste ?", " CHARGEMENT", MB_YESNO | MB_ICONQUESTION) == IDYES)
            {
                Chargement();
            }
            break;
        case 43:
            ShellExecute(NULL, "open", "chargement.txt", NULL, NULL, SW_SHOWNORMAL);
            break;
        case 51:
            if (vide_liste())
            {
                if (fich_vide())
                    MessageBox(hwnd, "       Essayer de faire la creation", " AFFICHE", MB_OK | MB_ICONWARNING);
                else
                    MessageBox(hwnd, "       Le fichier n'est pas vide\nEssayer de faire le chargement", " AFFICHE", MB_OK | MB_ICONWARNING);
            }
            else
            {
                system("cls");
                system("color 9F");
                ShowWindow(hwnd, SW_HIDE);
                printf("\n\t\t\t\t\t   - Information sur l'avion -   \n\n");
                affiche_avion_donne();
                system("pause");
                ShowWindow(hwnd, SW_NORMAL);
                system("cls");
            }
            break;
        case 52:
            if (vide_liste())
            {
                if (fich_vide())
                    MessageBox(hwnd, "       Essayer de faire la creation", " AFFICHE", MB_OK | MB_ICONWARNING);
                else
                    MessageBox(hwnd, "       Le fichier n'est pas vide\nEssayer de faire le chargement", " AFFICHE", MB_OK | MB_ICONWARNING);
            }
            else
            {
                system("cls");
                system("color 9F");
                ShowWindow(hwnd, SW_HIDE);
                printf("\n\t\t\t\t\t   - Contenu de la liste des avions -   \n");
                affiche_liste_donne();
                system("pause");
                ShowWindow(hwnd, SW_NORMAL);
                system("cls");
            }
            break;
        case 53:
            if (vide_liste())
            {
                if (fich_vide())
                    MessageBox(hwnd, "       Essayer de faire la creation", " AFFICHE", MB_OK | MB_ICONWARNING);
                else
                    MessageBox(hwnd, "       Le fichier n'est pas vide\nEssayer de faire le chargement", " AFFICHE", MB_OK | MB_ICONWARNING);
            }
            else
            {
                system("cls");
                system("color 9F");
                ShowWindow(hwnd, SW_HIDE);
                printf("\n\t\t\t\t\t   - Contenu de la compagnie -   \n");
                affiche_comp_donne();
                system("pause");
                ShowWindow(hwnd, SW_NORMAL);
                system("cls");
            }
            break;
        case 61:
            ShellExecute(NULL, "open", "projet_avion.pdf", NULL, NULL, SW_SHOWNORMAL);
            break;
        case 621:
            ShellExecute(NULL, "open", "CV_Yessine.JPG", NULL, NULL, SW_SHOWNORMAL);
            break;
        case 622:
            ShellExecute(NULL, "open", "CV_Kais.JPG", NULL, NULL, SW_SHOWNORMAL);
            break;

        case 10:
            if (MessageBox(hwnd, "       Vous voulez quitter ?", " QUITTER", MB_YESNO | MB_ICONQUESTION) == IDYES)
            {
                DestroyWindow(hwnd);
                system("cls");
            }
            break;
        }
    case WM_CREATE:
        addmenus(hwnd);
        //         CreateBtt(hwnd) ;
        /*****************ajouter fond **********************/
        hBmp = LoadImage(NULL, "Background.bmp", IMAGE_BITMAP, 1537, 843, LR_LOADFROMFILE);

        break;

    case WM_PAINT:
    {

        PAINTSTRUCT ps;
        hdc = BeginPaint(hwnd, &ps);

        DrawState(hdc, NULL, NULL, (long)hBmp, 0, 0, 0, 0, 0, DST_BITMAP);

        EndPaint(hwnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0); /* send a WM_QUIT to the message queue */
        break;
    default: /* for messages that we don't deal with */
        return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}

void addmenus(HWND hwnd)
{
    hmenu = CreateMenu();
    HMENU htp1 = CreateMenu();
    HMENU hex1 = CreateMenu();
    HMENU htp2 = CreateMenu();
    HMENU hex2_1 = CreateMenu();
    HMENU hex2_2 = CreateMenu();
    HMENU hex2_3 = CreateMenu();
    HMENU htp3 = CreateMenu();
    HMENU htp4 = CreateMenu();
    HMENU htp5 = CreateMenu();
    HMENU htp6 = CreateMenu();
    HMENU hex6_1 = CreateMenu();

    //AppendMenu(hmenu,MF_STRING,0,"cr�ation du repertoire");
    /*******************************************************/
    AppendMenu(hmenu, MF_STRING, 1, " Creation du repertoire Avion ");

    /***************************************************************/

    AppendMenu(hmenu, MF_POPUP, (UINT_PTR)htp2, " Mise a jour des avion ");

    AppendMenu(htp2, MF_POPUP, (UINT_PTR)hex2_1, "Ajouter un nouvel avion");
    AppendMenu(hex2_1, MF_STRING, 211, "Ajout en tete"); /*Sous partie de l'ex2*/
    AppendMenu(hex2_1, MF_STRING, 212, "Ajout en queue");
    AppendMenu(hex2_1, MF_STRING, 213, "Ajout dans une position");

    AppendMenu(htp2, MF_POPUP, (UINT_PTR)hex2_2, "Supprimer un avion");
    AppendMenu(hex2_2, MF_STRING, 221, "Suppession en tete"); /*Sous partie de l'ex2*/
    AppendMenu(hex2_2, MF_STRING, 222, "Suppession en queue");
    AppendMenu(hex2_2, MF_STRING, 223, "Suppession a partir d'une position");
    AppendMenu(hex2_2, MF_STRING, 224, "Suppession d'un avion donne");
    AppendMenu(hex2_2, MF_STRING, 225, "Suppession des avions d'une compagnie donnee");

    AppendMenu(htp2, MF_POPUP, (UINT_PTR)hex2_3, "Modifier les donnees d'un avion");
    AppendMenu(hex2_3, MF_STRING, 231, "Identifiant"); /*Sous partie de l'ex2*/
    AppendMenu(hex2_3, MF_STRING, 232, "Compagnie");
    /***************************************************************/
    AppendMenu(hmenu, MF_POPUP, (UINT_PTR)htp3, " Recherche et Tri ");

    AppendMenu(htp3, MF_STRING, 31, "Recherche par identifiant avion");
    AppendMenu(htp3, MF_STRING, 32, "Recherche par compagnie");
    AppendMenu(htp3, MF_STRING, 33, "Recherche par heure de decollage");
    AppendMenu(htp3, MF_STRING, 34, "Tri");

    /***************************************************************/
    AppendMenu(hmenu, MF_POPUP, (UINT_PTR)htp4, " Enregistrement et chargement ");

    AppendMenu(htp4, MF_STRING, 41, "Enregistrer dans un fichier");
    AppendMenu(htp4, MF_STRING, 42, "Charger d'apres un fichier");
    AppendMenu(htp4, MF_STRING, 43, "Ouvrir le fichier");
    /***************************************************************/
    AppendMenu(hmenu, MF_POPUP, (UINT_PTR)htp5, " Affichage ");

    AppendMenu(htp5, MF_STRING, 51, "Afficher un avion");
    AppendMenu(htp5, MF_STRING, 53, "Afficher par nom du compagnie");
    AppendMenu(htp5, MF_STRING, 52, "Afficher la liste des avions");
    /***************************************************************/
    AppendMenu(hmenu, MF_POPUP, (UINT_PTR)htp6, " A propos ");

    AppendMenu(htp6, MF_STRING, 61, "Enonce");
    AppendMenu(htp6, MF_POPUP, (UINT_PTR)hex6_1, "Developpeurs");
    AppendMenu(hex6_1, MF_STRING, 621, "Miled Yessine");
    AppendMenu(hex6_1, MF_STRING, 622, "Hajri Kais");
    /***************************************************************/
    AppendMenu(hmenu, MF_STRING, 10, "Quitter");
    SetMenu(hwnd, hmenu);
}
