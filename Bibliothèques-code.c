#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>

// Definition de la structure utilisateur
typedef struct {
    int ID;
    char pass[20];
} utilisateur;

// Definition de la structure Book
typedef struct Book {
    int ID;
    char titre[50];
    char auteur[50];
    int anneePublication;
    int numCopies;
    char availability[20];
    struct Book *next;
} Book;

// Definition de la structure queue_node pour la gestion de la file d'attente
typedef struct queue_node {
    int userID;
    int bookID;
    struct queue_node *next;
} queue_node;

// Pointeur vers la titre de la file d'attente
queue_node *queuehead = NULL;

// Fonction pour charger les livres a partir d'un fichier
Book *load_file() {
    Book *head = NULL;
    Book *last = NULL;
    FILE *f = fopen("livres.txt", "r");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return NULL;
    }
    char line[200];
    while (fgets(line, sizeof(line), f) != NULL) {
        Book *new_book = (Book *)malloc(sizeof(Book));
        if (new_book == NULL) {
            printf("Erreur d'allocation memoire\n");
            fclose(f);
            return head;
        }
        sscanf(line, "%d,%49[^,],%49[^,],%d,%d,%19s",
               &(new_book->ID), new_book->titre, new_book->auteur,
               &(new_book->anneePublication), &(new_book->numCopies), new_book->availability);
        new_book->next = NULL;
        if (head == NULL) {
            head = new_book;
        } else {
            last->next = new_book;
        }
        last = new_book;
    }
    fclose(f);
    return head;
}

// Fonction pour rechercher des livres par date de publication
void rechercher_par_date(Book *head) {
    int date;
    int cmp = 0;
    printf("Entrer la date du livre : \n");
    scanf("%d", &date);
    Book *node = head;
    while (node != NULL) {
        if (node->anneePublication == date) {
            printf("ID: %d\tTitre: %s\tAuteur: %s\tAnnee de publication: %d\tNombre de copies: %d\tAvailability: %s\n",
                   node->ID, node->titre, node->auteur, node->anneePublication, node->numCopies, node->availability);
            cmp++;
        }
        node = node->next;
    }
    if (cmp == 0) {
        printf("Aucun livre ecrit dans cette annee...\n");
    }
}

// Fonction pour rechercher des livres par ID
void rechercher_par_ID(Book *head) {
    int bookID;
    printf("Entrer le ID du livre : \n");
    scanf("%d", &bookID);
    Book *node = head;
    while (node != NULL) {
        if (node->ID == bookID) {
            printf("ID: %d\tTitre: %s\tAuteur: %s\tAnnee de publication: %d\tNombre de copies: %d\tAvailability: %s\n",
                   node->ID, node->titre, node->auteur, node->anneePublication, node->numCopies, node->availability);
            return;
        }
        node = node->next;
    }
    printf("Livre n'existe pas...\n");
}

// Fonction pour rechercher des livres par auteur
void rechercher_par_auteur(Book *head) {
    char aut[50];
    int cmp = 0;
    printf("Entrer le nom d'auteur du livre : \n");
    getchar();
    scanf("%[^\n]", aut);
    Book *node = head;
    while (node != NULL) {
        if (strcmp(node->auteur, aut) == 0) {
            printf("ID: %d\tTitre: %s\tAuteur: %s\tAnnee de publication: %d\tNombre de copies: %d\tAvailability: %s\n",
                   node->ID, node->titre, node->auteur, node->anneePublication, node->numCopies, node->availability);
            cmp++;
        }
        node = node->next;
    }
    if (cmp == 0) {
        printf("L'auteur %s n'a pas de livres dans cette liste!!!\n", aut);
    } else {
        printf("L'auteur %s a %d livres dans cette liste...\n", aut, cmp);
    }
}

// Fonction pour rechercher des livres par titre

void search_by_titre(Book *tete) {
    char titre_rechercher[50];
    int cmp=0;
    printf("Entrez le titre recherché :\n");
    getchar();
    scanf("%[^\n]", titre_rechercher);
    Book *node = tete;
    while (node != NULL) {
        if (strcmp(node->titre, titre_rechercher) == 0) {
            printf("ID: %d\tTitre: %s\tAuteur: %s\tAnnee de publication: %d\tNombre de copies: %d\tAvailability: %s\n",
                   node->ID, node->titre, node->auteur, node->anneePublication, node->numCopies, node->availability);
            cmp++;
        }
        node = node->next;
    }if (cmp == 0) {
        printf("Aucun livre avec ce titre...\n");
    }
}

// Fonction pour ajouter un nouveau livre
void add_book(Book **head) {
    Book *new_book = (Book *)malloc(sizeof(Book));
    if (new_book == NULL) {
        printf("Erreur d'allocation memoire\n");
        return;
    }

    printf("Saisir ID: ");
    scanf("%d", &(new_book->ID));
    printf("Saisir titre: ");
    getchar();
    scanf("%[^\n]", new_book->titre);
    printf("Saisir auteur: ");
    getchar();
    scanf("%[^\n]", new_book->auteur);
    printf("Saisir date de publication: ");
    scanf("%d", &(new_book->anneePublication));
    printf("Saisir nombre de copies: ");
    scanf("%d", &(new_book->numCopies));
    printf("Saisir disponibilite: ");
    scanf("%s", new_book->availability);

    new_book->next = NULL;
    if (*head == NULL) {
        *head = new_book;
    } else {
        Book *node = *head;
        while (node->next != NULL) {
            node = node->next;
        }
        node->next = new_book;
    }
    printf("Le livre a ete ajoute avec succï¿½s.\n\n");
}

// Fonction pour afficher la liste des livres
void afficherLivre(Book *head) {
    Book *node = head;
    while (node != NULL) {
        printf("ID: %d\tTitre: %s\tAuteur: %s\tAnnee de publication: %d\tNombre de copies: %d\tAvailability: %s\n",
               node->ID, node->titre, node->auteur, node->anneePublication, node->numCopies, node->availability);
        printf("\n");
        node = node->next;
    }
}

// Fonction pour sauvegarder la liste des livres dans un fichier
void save_to_file(Book *head) {
    FILE *f = fopen("livres.txt", "w");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    Book *node = head;
    while (node != NULL) {
        fprintf(f, "%d,%s,%s,%d,%d,%s\n",
                node->ID, node->titre, node->auteur, node->anneePublication,
                node->numCopies, node->availability);
        node = node->next;
    }
    fclose(f);
}

// Fonction pour ajouter un utilisateur
void ajoute_utilisateur() {
    printf("Ajout d'un utilisateur\n");

    utilisateur usr;
    printf("Ajouter l'ID: ");
    scanf("%d", &usr.ID);
    printf("Mot de passe: ");
    scanf("%s", usr.pass);

    FILE *f = fopen("utilisateur.txt", "a");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
        return;
    }
    fprintf(f, "%d %s\n", usr.ID, usr.pass);
    fclose(f);

    printf("L'utilisateur a ete ajoute avec succes\n");
}

// Fonction pour verifier les informations de connexion de l'utilisateur
int utilisateur_bib(int id, char password[20]) {
    int found = 0;
    FILE *f = fopen("utilisateur.txt", "r");
    if (f == NULL) {
        printf("Erreur de lecture de fichier...\n");
        return -1;
    }
    utilisateur usr;
    while (fscanf(f, "%d %19s", &usr.ID, usr.pass) == 2) {
        if (usr.ID == id) {
            found = 1;
            break;
        }
    }
    fclose(f);
    if (found == 1) {
        if (strcmp(usr.pass, password) == 0) {
            printf("Connexion reussie d'utilisateur %d\n", usr.ID);
            return 0;
        } else {
            printf("Mot de passe invalide!\n");
            return 1;
        }
    } else {
        printf("utilisateur introuvable...\n");
        return 2;
    }
}

// Fonction pour reserver un livre
void book_reservation(Book *head, int userID) {
    int bookID;
    printf("Entrer l'ID du livre que vous souhaitez reserver: ");
    scanf("%d", &bookID);

    Book *current = head;
    while (current != NULL) {
        if (current->ID == bookID) {
            break;
        }
        current = current->next;
    }

    if (current == NULL) {
        printf("Ce livre n'existe pas.\n");
        return;
    }

    if (strcmp(current->availability, "reserver") == 0) {
        printf("Ce livre est indisponible.\n");
        return;
    }

    current->numCopies--;

    if (current->numCopies == 0) {
        strcpy(current->availability, "reserver");
    }

    queue_node *new_node = (queue_node *)malloc(sizeof(queue_node));
    new_node->userID = userID;
    new_node->bookID = bookID;
    new_node->next = NULL;

    if (queuehead == NULL) {
        queuehead = new_node;
    } else {
        queue_node *current = queuehead;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }

    printf("Le livre a ete reserve avec succes.\n");
}

// Fonction principale
int main() {
    int choix, choix1;
    int id;
    int connect = 1;
    char password[20];

    // Charger les livres a partir du fichier
    Book *listeLivres = load_file();
    while (1) {
        system("cls");
        printf(".............................bienvenue.............................\n");
        printf("Veuillez choisir une option :\n");
        printf("1 - UTILISATEUR\n");
        printf("2 - Ajouter un utilisateur\n");
        printf("0 - Exit\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                system("cls");
                printf("Entrer votre utilisateur ID : ");
                scanf("%d", &id);
                printf("Entrer votre utilisateur password : ");
                scanf("%s", password);
                system("cls");
                int isUSR = utilisateur_bib(id, password);
                if (isUSR == 0) {
                    connect = 1;
                    while (connect) {
                        system("cls");
                        printf("Bonjour Mr %d\n", id);
                        printf("Veuillez choisir une option :\n");
                        printf("1 - Ajouter un livre\n");
                        printf("2 - Rechercher un livre\n");
                        printf("3 - Voir la liste complete des livres\n");
                        printf("4 - Reserver un livre\n");
                        printf("0 - Se deconnecter\n");
                        printf("Choix : ");
                        scanf("%d", &choix);
                        system("cls");

                        switch (choix) {
                            case 0:
                                printf("Deconnexion...\n");
                                sleep(2);
                                connect = 0;
                                break;
                            case 1:
                                add_book(&listeLivres);
                                printf("Appuyez sur n'importe quelle touche pour continuer...\n");
                                getch();
                                break;
                            case 2:
                                printf("Veuillez choisir une option :\n");
                                printf("1 - Rechercher par ID\n");
                                printf("2 - Rechercher par annee de publication\n");
                                printf("3 - Rechercher par auteur\n");
                                printf("4 - Rechercher par titre\n");
                                printf("5 - Revenir au menu principal\n");
                                printf("Choix : ");
                                scanf("%d", &choix1);
                                switch (choix1) {
                                    case 1:
                                        printf("Rechercher par ID\n");
                                        rechercher_par_ID(listeLivres);
                                        printf("Appuyez sur n'importe quelle touche pour continuer...\n");
                                        getch();
                                        break;
                                    case 2:
                                        printf("Rechercher par annee de publication\n");
                                        rechercher_par_date(listeLivres);
                                        printf("Appuyez sur n'importe quelle touche pour continuer...\n");
                                        getch();
                                        break;
                                    case 3:
                                        printf("Rechercher par auteur\n");
                                        rechercher_par_auteur(listeLivres);
                                        printf("Appuyez sur n'importe quelle touche pour continuer...\n");
                                        getch();
                                        break;
                                    case 4:
                                    	printf("Rechercher par titre\n");
                                    	search_by_titre(listeLivres);
                                    	printf("Appuyez sur n'importe quelle touche pour continuer...\n");
                                        getch();
                                        break;
                                    case 5:
                                        break;
                                    default:
                                        printf("Choix invalide !\n");
                                }
                                break;
                            case 3:
                                afficherLivre(listeLivres);
                                printf("Appuyez sur n'importe quelle touche pour continuer...\n");
                                getch();
                                break;
                            case 4:
                                book_reservation(listeLivres, id);
                                printf("Appuyez sur n'importe quelle touche pour continuer...\n");
                                getch();
                                break;
                            default:
                                printf("Choix invalide !\n");
                        }
                    }
                } else {
                    printf("Mot de passe incorrect !\n");
                    sleep(2);
                }
                break;
            case 2:
                system("cls");
                ajoute_utilisateur();
                printf("Appuyez sur n'importe quelle touche pour continuer...\n");
                getch();
                break;
            case 0:
                printf("Deconnexion...\n");
                printf("Enregistrement de donnees...\n");
                save_to_file(listeLivres);
                printf("Les livres sont enregistres avec succï¿½s !\n");
                return 0;
            default:
                system("cls");
                printf("Choix invalide...\n");
                break;
        }
    }
    return 0;
}

