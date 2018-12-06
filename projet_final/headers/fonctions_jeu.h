//nombre de joueur
#define N 5
//nombre des chevaux
#define NC 4
//succes 
#define S 10

void affichage_debut();
void affichage_fin();
void initialisation(int tab[N][NC],int nombreJoueur,int nombreChevaux);
void afficher_etat_jeu(int tab[N][NC],int nombreJoueur,int nombreChevaux);
int enregistrer( int tab[N][NC],int i , int chv , int de ,int nombreJoueur,int nombreChevaux,int succes);
int jouer(int i, int nombreChevaux,int nombreJoueur, int numeroJoueur,int succes, int pipeAnn[][2], int pipePereFils[][2],int pipeFilsPere[2], int etat_jeu[N][NC]);
void remplir(int *tab, int n);
int num_cheval(int nombreChevaux);
int de();

