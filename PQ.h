#include <bits/stdc++.h>
using namespace std;

template <class T>
class PriorityQueue{
    private :
    set<T> ascend_elems;
    set<T,greater<T>> descend_elems;
    bool ascend = true;

    public : 
    PriorityQueue(){};
    PriorityQueue(bool);
    void InsererElem(T);
    void AfficherSet();
    T Pop();
};