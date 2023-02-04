#if !defined(ARBRE_H)
#define ARBRE_H
template <typename T>
class noeud {
public:
    T info;
    noeud* sag;
    noeud* sad;
    noeud(T x);
};
template <typename T>
class arbre {
private:
    noeud<T>* root;
public:
    arbre();
    bool est_vide();
    void max_arbre();
    void afficher_noeud(noeud<T>*);
    void insertion_equilibre(T);
    noeud<T>* chercher(T);
    void supprimer(T);
    void affichage_infixe();
    void Affichage_2D();
    void afficher_longueur()
    {
        std::cout << "Longueur  = " << height(root) << std::endl;
    }
private:
    noeud<T>* insertion_equilibrerec(T, noeud<T>*);
    noeud<T>* chercher_recurs(T, noeud<T>*);
    noeud<T>* supprimerrec(T, noeud<T>*);
    void infixe(noeud<T>*);
    void Affichage_2Drecurs(noeud<T>* nd, int space);
    int getBalance(noeud<T>*);
    int height(noeud<T>*);
    noeud<T>* maxrec(noeud<T>*);
    noeud<T>* rightRotation(noeud<T>*);
    noeud<T>* leftRotation(noeud<T>*);
    noeud<T>* min(noeud<T>*);



};

#endif 