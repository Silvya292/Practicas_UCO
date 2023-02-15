//contador.cc
//Body of class Contador

#include "contador.h"
#include <iostream>

using namespace std;

Contador::Contador(int valor, int min, int max){
    if(valor<min || valor>max || min>max){ //Si el valor está fuera de rango o el límite mínimo es menor al máximo, se ponen los valores por defecto
        valor=0;
        min=0;
        max=1000;
    }
    valor_=valor;
    min_=min;
    max_=max;
    list_.push_back(*this); //Si todos los valores son correctos se añaden a la lista
}

void Contador::control(){ //Función de control del contador
    if(valor_<min_){ //Si el valor es menor al límite inferior, éste se iguala al límite
        valor_=min_;
    }
    else if(valor_>max_){ //Si el valor es mayor al límite superior, éste se iguala al límite
        valor_=max_;
    }
    list_.push_back(*this); //Se añade a la lista
}

Contador Contador::operator=(const int &valor){ //Asignación de un valor a un objeto de la clase
    valor_=valor;
    control(); //Se comprueba que los valores sean válidos
    return *this; //Se devuelve el valor al que apunta el puntero this
}

Contador Contador::operator=(const Contador &cont){ //Asignación de un Contador a un objeto de la clase
    valor_=cont.valor_;
    min_=cont.min_;
    max_=cont.max_;
    control(); //Se comprueba que los valores sean válidos
    return *this; //Se devuelve el valor al que apunta el puntero this
}

Contador Contador::operator++(void){ //Prefijo ++c
    ++valor_;
    control(); //Se comprueba que los valores sean válidos
    return *this; //Se devuelve el valor al que apunta el puntero this
}

Contador Contador::operator++(int){ //Postfijo c++
    Contador cont=*this;
    ++valor_;
    control(); //Se comprueba que los valores sean válidos
    return cont;
}

Contador Contador::operator--(void){ //Prefijo --c
    --valor_;
    control(); //Se comprueba que los valores sean válidos
    return *this; //Se devuelve el valor al que apunta el puntero this
}

Contador Contador::operator--(int){ //Postfijo c++
    Contador cont=*this;
    --valor_;
    control(); //Se comprueba que los valores sean válidos
    return cont; //Se devuelve el valor del contador
}

Contador Contador::operator+(const int &n){
    valor_=valor_+n;
    control(); //Se comprueba que los valores sean válidos
    return *this; //Se devuelve el valor al que apunta el puntero this
}

Contador operator+(const int &n,const Contador &cont){
    Contador aux;
    aux.valor_=n+cont.valor_;
    aux.min_=cont.min_;
    aux.max_=cont.max_;
    aux.control(); //Se comprueba que los valores sean válidos
    return aux; //Se devuelve el valor del contador auxiliar aux
}

Contador Contador::operator-(const int &n){
    valor_=valor_-n;
    control(); //Se comprueba que los valores sean válidos
    return *this; //Se devuelve el valor al que apunta el puntero this
}

Contador operator-(const int &n,const Contador &cont){
    Contador aux;
    aux.valor_=n-cont.valor_;
    aux.min_=cont.min_;
    aux.max_=cont.max_;
    aux.control(); //Se comprueba que los valores sean válidos
    return aux; //Se devuelve el valor del contador auxiliar aux
}

bool Contador::undo(const int &n){ //Deshace las n últimas operaciones
    if(n>=(int) list_.size() || n<1){ //Se comprueba que el valor de n sea válido
        return false;
    }
    for(int i=0;i<n;i++){
        list_.pop_back(); //Se elimina la última operación realizada
    }
    *this=list_.back(); //Se devuelve la nueva lista
    return true;
}