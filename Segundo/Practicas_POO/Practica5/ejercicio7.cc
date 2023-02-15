#include <iostream>
using namespace std;

template <class T> class MiClase{ //Clase MiClase de tipo abstracto T
    private:
        T x_,y_; //Se definen dos variables de tipo T
    public:
        MiClase(T a, T b){x_=a;y_=b;}; //Constructor de la clase
        inline T div(){return x_/y_;}; //División de dos variables de tipo T
        inline T prod(){return x_*y_;}; //Producto de dos variables de tipo T
        inline T add(){return x_+y_;}; //Suma de dos variables de tipo
        inline T sub(){return x_-y_;}; //Diferencia de dos variables de tipo T
        inline T greater(){ //Comparación de dos variables de tipo T
            if(x_>y_){return x_;}
            else{return y_;}
        };
};

int main(){
    MiClase <int> objectInt(10,3); //Se define un objeto de la clase MiClase de tipo int
    MiClase <double> objectDouble(3.3,5.5); //Se define un objeto de la clase MiClase de tipo double

    cout << "Valores enteros: 10 3\n";
    cout << "División entera = " << objectInt.div() << "\n";
    cout << "Multiplicación entera = " << objectInt.prod() << "\n";
    cout << "Suma entera = " << objectInt.add() << "\n";
    cout << "Diferencia entera = " << objectInt.sub() << "\n";
    cout << "El mayor entero es: " << objectInt.greater() << "\n\n";

    cout << "Valores reales: 3.3 5.5\n";
    cout << "División real = " << objectDouble.div() << "\n";
    cout << "Multiplicación real = " << objectDouble.prod() << "\n";
    cout << "Suma real = " << objectDouble.add() << "\n";
    cout << "Diferencia real = " << objectDouble.sub() << "\n";
    cout << "El mayor real es: " << objectDouble.greater() << "\n";
}