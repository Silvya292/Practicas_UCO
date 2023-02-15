/* Define la estructura de parametros de entrada de las funciones */
struct operandos
{
	int a;
	int b;
};


program CALCULADORA_PROG {
    version CALCULADORA_VERS {
	int SUMA(operandos) = 1;	/* numero de procedimiento = 1 */
	int MULTIPLICACION(operandos) = 2; /*numero de procedimiento = 2*/
	int RESTA(operandos) = 3; /*numero de procedimiento = 3*/
	int DIVISION(operandos) = 4; /*numero de procedimiento = 4*/
	int POTENCIA(operandos) = 5; /*numero de procedimiento = 5*/
	int MODULO(operandos) = 6; /*numero de procedimiento = 6*/
    } = 1;			/* numero de version = 1 */
} = 0x20000001;			/* numero de programa = 0x20000001 */
			       /* 0x20000000 - 0x3fffffff para usuarios*/

