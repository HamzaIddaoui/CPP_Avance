#include <iostream>
#include <vector>
#include "Arbre.h"
#include <time.h>
#define COUNT 10
using namespace std;

template <class T>
Noeud<T>::Noeud(T info){
    this->info = info;
    this->fd = this->fg = NULL;
}

template <class T>
Noeud<T>::Noeud(T info, Noeud<T> *fg, Noeud<T> *fd){
    this->info = info;
    this->fg = fg;
    this->fd = fd;
}

template <class T>
Arbre<T>::Arbre(T info){
    this->racine = new Noeud<T>(info);
}

template <class T>
Arbre<T>::Arbre(Noeud<T> *nd){
    this->racine = nd;
};

template <class T>
int Arbre<T>::Hauteur(Noeud<T> *nd){
    int h = 0;
    if(nd != nullptr){
        int d_hauteur = Hauteur(nd->fd);
        int g_hauteur = Hauteur(nd->fg);
        int max_hauteur = max(d_hauteur,g_hauteur);
        h = max_hauteur +1;
    }
    return h;
};

template <class T>
Noeud<T>* Arbre<T>::difference(Noeud<T> *nd){
    Noeud<T> *t;
    t = nd->fd;
    nd->fd = t->fg;
    t->fg = nd;
    return t;
}

template <class T> 
Noeud<T>* Arbre<T>::rotation_dd(Noeud<T>* nd){
    Noeud<T> *t;
    t = nd->fd;
    nd->fd = t->fg;
    t->fg = nd;
    return t;
}

template <class T> 
Noeud<T>* Arbre<T>::rotation_gg(Noeud<T>* nd){
    Noeud<T> *t;
    t = nd->fg;
    nd->fg = t->fd;
    t->fd = nd;
    return t;
}

template <class T> 
Noeud<T>* Arbre<T>::rotation_gd(Noeud<T>* nd){
    Noeud<T> *t;
    t = nd->fg;
    nd->fg = rotation_dd(t);
    return rotation_gg(nd);
}

template <class T> 
Noeud<T>* Arbre<T>::rotation_dg(Noeud<T>* nd){
    Noeud<T> *t;
    t = nd->fd;
    nd->fd = rotation_gg(t);
    return rotation_dd(nd);
}

template <class T>
Noeud<T>* Arbre<T>::Balancer(Noeud<T>* nd){

    int bal_factor = difference(nd);
    if (bal_factor > 1)
    {
       if (difference(nd->fg) > 0)
       nd = rotation_gg(nd);
       else
       nd = rotation_gd(nd);
    }
    else if (bal_factor < -1)
    {
       if (difference(nd->fd) > 0)
       nd = rotation_dg(nd);
       else
       nd = rotation_dd(nd);
    }
    return nd;
}

template <class T>
Noeud<T>* Arbre<T>::Insertion(Noeud<T>* nd,T v){
    if (nd == NULL)
      {
         nd = new Noeud<T>*;
         nd->info = v;
         nd->fg = NULL;
         nd->fd = NULL;
         return nd;
      }
      else if (v< nd->info)
      {
         nd->fg= insert(nd->fg, v);
         nd = balance(nd);
      }
      else if (v >= nd->info)
      {
         nd->fd= insert(nd->fd, v);
         nd = balance(nd);
      }
      return nd;
}

template <class T>
Noeud<T>* Arbre<T>::InsererInfos(Noeud<T> *racine,T info){
    if(racine == NULL) {
        racine = new Noeud<T>(info);
        return racine;
    }
    if(info > racine->info)
        racine->fd = this->InsererInfos(racine->fd,info);
    else {
        racine->fg = this->InsererInfos(racine->fg,info);
    }
    return racine;
};


template <class T>
void Arbre<T>::InsererInfos(T info){
    this->racine = this->Insertion(this,info);
};


template <class T>
void Arbre<T>::print2DUtil(Noeud<T> *nd,int space){
    if (nd == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(nd->fd, space);
 
    // Print current node after space
    // count
    cout << endl;
    for (int i = COUNT; i < space; i++)
        cout << " ";
    cout << nd->info << "\n";
 
    // Process left child
    print2DUtil(nd->fg, space);
};

template <class T>
void Arbre<T>::print2D(){
    this->print2DUtil(this->racine,0);
};

template <class T>
void Arbre<T>::ParcourirArbre(Noeud<T> * nd){
    if(nd == NULL) return;
    cout << nd->info << " ";
    this->ParcourirArbre(nd->fd);
    this->ParcourirArbre(nd->fg);
}

template <class T>
void Arbre<T>::ParcourirArbre(){
    time_t start,end;
    time(&start);
    this->ParcourirArbre(this->racine);
    time(&end);
    double time_taken = double(end - start);
    cout << "Temps d'execution = " << time_taken << endl;
}

template <class T>
bool Arbre<T>::RechercherArbre(Noeud<T> *nd, T elem){
    if(nd->info == elem) return true;
    if(!nd) return false;
    if(elem > nd->info) return this->RechercherArbre(nd->fd,elem);
    return this->RechercherArbre(nd->fg,elem);
}

template <class T>
bool Arbre<T>::RechercherArbreBST(T elem){
    return this->RechercherArbre(this->racine,elem);
}




int main() 
{ 
    Arbre<int> *arb = new Arbre<int>(5);
    time_t start,end;
    for(int i=0;i < 100000 ; i++)  arb->InsererInfos(rand());
    
    //arb->print2D();
    cout << endl;
    //arb->ParcourirArbre();
    time(&start);
    cout << "La valeur 11110 existe ? :" << arb->RechercherArbreBST(145) << endl;
    time(&end);
    double time_taken = double(end - start);
    cout << "Temps de recherche = " << time_taken << endl;
    return 0;
}