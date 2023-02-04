#include <iostream>
#include <cstdlib>
#include "arbre_equilibre.h"
#define space 20
#define max( a, b) ((a)>(b)? (a) : (b)) 
using namespace std; 
//constructeur du noeud
template <typename T>
noeud<T>::noeud(T x)
{
    this->info = x;
    this->sag = nullptr;
    this->sad = nullptr;
}
//afficher un noeud
template <typename T>
void arbre<T>::afficher_noeud(noeud<T>* nd)
{
    if (nd)
    {
        cout << "Info =  " << nd->info << endl;
    }
    else
    {
        cout << "Pas de donées a afficher" << endl;
    }

}
//constructeur de l'arbre
template <typename T>
arbre<T>::arbre()
{
      this->root = nullptr;
}
//Est_vide 
template <typename T>
bool arbre<T>::est_vide()
{
    return (this->root == nullptr);

}
//affichage infixe
template <typename T>
void arbre<T>::infixe(noeud<T>* nd)
{
    if (nd)
    {
        infixe(nd->sag);
        cout << nd->info << "\t";
        infixe(nd->sad);
    }
}
template <typename T>
void arbre<T>::affichage_infixe()
{
    if (est_vide())
        cout << "l'arbre est vide" << endl;
    else 
        infixe(this->root);
}
//chercher
template <typename T>
noeud<T>* arbre<T>::chercher_recurs(T x, noeud<T>* elem)
{
    if (elem == nullptr)
        return nullptr;
    if (x > elem->info)
        return chercher_recurs(x, elem->sad);
    else if (x < elem->info)
        return chercher_recurs(x, elem->sag);
    return elem;

}
template <typename T>
noeud<T>* arbre<T>::chercher(T x)
{
    return chercher_recurs(x, root);
}
//affichage 2D
template <typename T>
void arbre<T>::Affichage_2Drecurs(noeud<T>* nd, int spa)
{
    if (!nd)
        return;
    spa += space;
    Affichage_2Drecurs(nd->sad, spa);
    cout << endl;
    for (int i = space; i < spa; i++)
    {
        cout << " ";
    }
    cout << nd->info << endl;
    Affichage_2Drecurs(nd->sag, spa);

}
template <typename T>
void arbre<T>::Affichage_2D()
{
    Affichage_2Drecurs(root,5);
}
////////
template <typename T>
int arbre<T>::height(noeud<T>* nd)
{
    if (!nd)
        return 0;
    return max(height(nd->sag), height(nd->sad)) + 1;
}
template <typename T>
int arbre<T>::getBalance(noeud<T>* nd)
{
    if (!nd)
        return -1;
    return (height(nd->sag) - height(nd->sad));

}
template <typename T>
noeud<T>* arbre<T>::leftRotation(noeud<T>* nd)
{
    noeud<T>* x = nd->sad, * y = x->sag;
    x->sag = nd;
    nd->sad = y;
    return x;
}
template <typename T>
noeud<T>* arbre<T>::rightRotation(noeud<T>* nd)
{
    noeud<T>* x = nd->sag, * y = x->sad;
    x->sad = nd;
    nd->sag = y;
    return x;
}
template <typename T>
noeud<T>* arbre<T>::min(noeud<T>* nd)
{

    while (nd->sag)
        nd = nd->sag;
    return nd;
}
template <typename T>
noeud<T>* arbre<T>::maxrec(noeud<T>* nd)
{
    while (nd->sad)
        nd = nd->sad;
    return nd;
}
template <typename T>
void arbre<T>::max_arbre()
{
    cout << "le max est :    ";
    this->afficher_noeud(maxrec(root));
}
//////// 

//Inserer  
template <typename T>
noeud<T>* arbre<T>::insertion_equilibrerec(T x, noeud<T>* elem)
{
    if (!elem)
    {
        return (noeud<T>*) new noeud<T>(x);
    }
    if (elem->info > x)
    {
        elem->sag = insertion_equilibrerec(x, elem->sag);

    }
    else if (elem->info < x)
    {
        elem->sad = insertion_equilibrerec(x, elem->sad);
    }
    int bal = getBalance(elem);
    if (bal > 1 && x < elem->sag->info)     return  rightRotation(elem);
    if (bal < -1 && x > elem->sad->info)   return   leftRotation(elem);
    if (bal > 1 && x > elem->sag->info) 
    {
        elem->sag = leftRotation(elem->sag);
        return rightRotation(elem);
    }
    if (bal < -1 && x < elem->sad->info)
    {
        elem->sad = rightRotation(elem->sad);
        return leftRotation(elem);
    }
    return elem;
}
template <typename T>
void arbre<T>::insertion_equilibre(T x)
{
    this->root = insertion_equilibrerec(x, this->root);
}

//supprimer
template <typename T>
noeud<T>* arbre<T>::supprimerrec(T x, noeud<T>* nd)
{
    if (!nd) return nullptr;
    if (nd->info > x) nd->sag = supprimerrec(x, nd->sag);
    else if (nd->info < x) nd->sad = supprimerrec(x, nd->sad);
    else
    {
        noeud<T>* temp;
        if (!nd->sag)
        {
            noeud<T>* temp = nd->sad;
            delete nd;
            return temp;
        }

        else if ((!nd->sad))
        {
            temp = nd->sag;
            delete nd;
            return temp;
        }
        else
        {
            temp = min(nd->sad);
            nd->info = temp->info;
            nd->sad = supprimerrec(temp->info, nd->sad);
        }
    }
    int bal = getBalance(nd);
    if (bal == 2 && getBalance(nd->sag) >= 0)
        return rightRotation(nd);
    if (bal == 2 && getBalance(nd->sag) == -1)
    {
        nd->sag = leftRotation(nd->sag);
        return rightRotation(nd);
    }
    if (bal == -2 && getBalance(nd->sad) <= 0)
        return leftRotation(nd);
    if (bal == -2 && getBalance(nd->sag) >= 0)
    {
        nd->sad = rightRotation(nd->sad);
        return leftRotation(nd);
    }
    return nd;

}
template <typename T>
void arbre<T>::supprimer(T x)
{
    this->root = supprimerrec(x, this->root);
}


