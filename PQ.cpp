#include<iostream>
#include <bits/stdc++.h>
#include "PQ.h"
#include <chrono>
using namespace std;
using namespace std::chrono;


template <class T>
PriorityQueue<T>::PriorityQueue(bool ascend){
    this->ascend = ascend;
};

template <class T>
void PriorityQueue<T>::InsererElem(T elem){
    (this->ascend) ? this->ascend_elems.insert(elem) : this->descend_elems.insert(elem);
};

template <class T>
void PriorityQueue<T>::AfficherSet(){
   typename set<T>::iterator it;
   cout << endl ;
   if(this->ascend) { 
      for (auto it = this->ascend_elems.begin() ; it != this->ascend_elems.end() ; it++)
      cout << *it << " \t";
   } else { 
      for (auto it = this->descend_elems.begin() ; it != this->descend_elems.end() ; it++)
      cout << *it << " \t";
   }
}

template <class T>
T PriorityQueue<T>::Pop(){ 
    T elem;
    if(this->ascend) { 
        elem = *(this->ascend_elems.begin());
        this->ascend_elems.erase(this->ascend_elems.begin());
        return elem;
    } else { 
        elem = *(this->descend_elems.begin());
        this->descend_elems.erase(this->descend_elems.begin());
        return elem;
    }
}

int main() {
    PriorityQueue<int> * PQ = new PriorityQueue<int>(false);
    auto start = high_resolution_clock::now();
    for (int i = 0; i < 10000000; i++)
      PQ->InsererElem(rand());
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    //PQ->AfficherSet();
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;
    return 0;
}