#pragma once
#include "domain.h"
const int CAPACITY = 1;

template<typename Elem> class Vector_Dinamic;

template<typename Elem> class Iterator_Vector{
private:
    const Vector_Dinamic<Elem> &vector_dinamic;
    int pozitie{};
public:
    explicit Iterator_Vector(const Vector_Dinamic<Elem>& vector_dinamic);
    Iterator_Vector(const Vector_Dinamic<Elem>& vector_dinamic, int pozitie);
    void urmator();
    Elem& element();
    Iterator_Vector operator++();
    bool operator==(const Iterator_Vector<Elem>& it) const;
    bool operator!=(const Iterator_Vector<Elem>& it) const;
    Elem &operator*();
};


template<typename Elem>
class Vector_Dinamic{
private:
    int capacitate{};
    int numar{0};
    Elem *elemente;

    void resize();
public:

    Vector_Dinamic();

    // rule of three
    Vector_Dinamic(const Vector_Dinamic<Elem>& other);
    Vector_Dinamic<Elem>& operator=(const Vector_Dinamic<Elem> &other);
    ~Vector_Dinamic();


    [[nodiscard]] int get_nr_elems() const;
    void set_elem(int pozitie, const Elem& element);
    Elem get_elem(int pozitie);

    void add(const Elem& element);
    void remove(int pozitie);

    Iterator_Vector <Elem> begin() const;
    Iterator_Vector <Elem> end();

    friend class Iterator_Vector <Elem>;
};

template<typename Elem>
Vector_Dinamic<Elem>:: Vector_Dinamic() : capacitate(CAPACITY), elemente{new Elem[CAPACITY]} {}

template<typename Elem>
Vector_Dinamic<Elem> ::Vector_Dinamic(const Vector_Dinamic<Elem> &other) : capacitate{other.capacitate}, numar{other.numar}, elemente{new Elem[capacitate]} {
    for(int i = 0; i < other.numar; i++){
        *(elemente + i) = other.elemente[i];
    }
}

template<typename Elem>
Vector_Dinamic<Elem> &Vector_Dinamic<Elem>:: operator=(const Vector_Dinamic<Elem> &other){
    if (this != &other) {
        Elem* auxiliar = new Elem[other.capacitate];
        for (int i = 0; i < other.numar; i++) {
            *(auxiliar + i) = other.elemente[i];
        }
        delete[] this->elemente;
        this->elemente = auxiliar;
        this->capacitate = other.capacitate;
        this->numar = other.numar;
    }
    return *this;
}

template<typename Elem>
Vector_Dinamic<Elem>::~Vector_Dinamic(){
    delete[] elemente;
}


template<typename Elem>
void Vector_Dinamic<Elem>::resize() {
    if(numar >= capacitate) {
        capacitate *= 2;
        Elem* auxiliar = new Elem[capacitate];
        for(int i = 0; i < numar; ++i) {
            *(auxiliar + i) = *(elemente+i);
        }
        delete[] elemente;
        elemente = auxiliar;
    }
}


template<typename Elem>
void Vector_Dinamic<Elem>::add(const Elem& element) {
    resize();
    this->elemente[this->numar++] = element;
}

template<typename Elem>
int Vector_Dinamic<Elem>::get_nr_elems() const {
    return this->numar;
}


template<typename Elem>
void Vector_Dinamic<Elem>::remove(int pozitie) {
    for(int i = pozitie; i < this->numar - 1; i++){
        *(elemente+ i) = *(elemente + (i + 1));
    }
    this->numar--;
}

template<typename Elem>
void Vector_Dinamic <Elem>:: set_elem(int pozitie, const Elem& element){
    *(elemente+pozitie) = element;
}


template<typename Elem>
Elem Vector_Dinamic<Elem>:: get_elem(int pozitie){
    return *(elemente + pozitie);
}

template<typename Elem>
Iterator_Vector<Elem> Vector_Dinamic<Elem>::begin() const {
    return Iterator_Vector(*this);
}

template<typename Elem>
Iterator_Vector<Elem> Vector_Dinamic<Elem>::end() {
    return Iterator_Vector(*this, this -> numar);
}

template<typename Elem>
Iterator_Vector<Elem>::Iterator_Vector(const Vector_Dinamic<Elem> &vector):vector_dinamic{vector} {}

template<typename Elem>
Iterator_Vector<Elem>::Iterator_Vector(const Vector_Dinamic<Elem> &vector, int pozitie):vector_dinamic{vector},pozitie{pozitie} {}


template<typename Elem>
void Iterator_Vector<Elem>::urmator() {
    pozitie++;
}

template<typename Elem>
Elem& Iterator_Vector<Elem>::element() {
    return vector_dinamic.elemente[pozitie];
}

template<typename Elem>
Iterator_Vector<Elem> Iterator_Vector<Elem>::operator++() {
    urmator();
    return *this;
}

template<typename Elem>
Elem &Iterator_Vector<Elem>::operator*(){
    return element();
}

template<typename Elem>
bool Iterator_Vector<Elem>::operator!=(const Iterator_Vector<Elem> &it) const {
    return it.pozitie != pozitie;
}

template<typename Elem>
bool Iterator_Vector<Elem>:: operator==(const Iterator_Vector<Elem>&it) const{
    return it.pozitie == pozitie;
}