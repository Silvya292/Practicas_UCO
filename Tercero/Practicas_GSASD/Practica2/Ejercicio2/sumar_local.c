#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int sumar_local(int operand1, int operand2){
    int result=operand1+operand2;
    return result;
}

int main(int argc, char const *argv[]){
    int operand1, operand2;

    printf("Este programa mide el tiempo consumido tras 100.000 llamadas a una función SUMA local.\n");
    printf("Introduzca el primer operando: ");
    scanf("%d", &operand1);
    printf("Introduzca el segundo operando: ");
    scanf("%d", &operand2);

    int result=0;
    clock_t start=clock();

    for(int i=0;i<100000;i++){
        result=result+sumar_local(operand1,operand2);
    }

    clock_t end=clock();
    double time=(double) (end-start) / CLOCKS_PER_SEC;

    printf("El resultado de la suma es %d y el tiempo consumido han sido %f segundos.\n",result,time);
    exit(0);

}