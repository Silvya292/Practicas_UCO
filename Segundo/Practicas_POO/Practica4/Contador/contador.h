//contador.h
//Definition of class Contador

#ifndef CONTADOR_H
#define CONTADOR_H

#include <list>

using namespace std;

class Contador{
    private:
        int valor_,min_,max_; //Valor del contador y rangos
        void control(); //Función para comprobar si el valor supera alguno de los rangos
        list <Contador> list_; //Lista de las operaciones realizadas
    public:
        Contador(int valor=0,int min=0,int max=1000); //Constructor de la clase
        Contador operator=(const int &valor); //Asignación de un valor a un objeto de la clase
        Contador operator=(const Contador &cont); //Asignación de un Contador a un objeto de la clase
        Contador operator++(void); //Incremento del contador en 1 (++c)
        Contador operator++(int); //Incremento del contador en 1 (c++)
        Contador operator--(void); //Decremento del contador en 1 (--c)
        Contador operator--(int); //Decremento del contador en 1 (c--)
        Contador operator+(const int &n); //Incremento de n al valor del contador
        friend Contador operator+(const int &n,const Contador &cont); //Incremento de n al valor del contador pasado como argumento
        Contador operator-(const int &n); //Decremento de n al valor del contador
        friend Contador operator-(const int &n,const Contador &cont); //Decremento de n al valor del contador pasado como argumento
        bool undo(const int &n=1); //Deshace las n últimas operaciones
        inline int get() const{return valor_;} //Función que devuelve el valor actual del contador
};

#endif