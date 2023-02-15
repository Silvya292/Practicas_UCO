/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _PRUEBA_H_RPCGEN
#define _PRUEBA_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct operandos {
	int a;
	int b;
};
typedef struct operandos operandos;

#define CALCULADORA_PROG 0x20000001
#define CALCULADORA_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define SUMA 1
extern  int * suma_1(operandos *, CLIENT *);
extern  int * suma_1_svc(operandos *, struct svc_req *);
#define MULTIPLICACION 2
extern  int * multiplicacion_1(operandos *, CLIENT *);
extern  int * multiplicacion_1_svc(operandos *, struct svc_req *);
#define RESTA 3
extern  int * resta_1(operandos *, CLIENT *);
extern  int * resta_1_svc(operandos *, struct svc_req *);
#define DIVISION 4
extern  int * division_1(operandos *, CLIENT *);
extern  int * division_1_svc(operandos *, struct svc_req *);
#define POTENCIA 5
extern  int * potencia_1(operandos *, CLIENT *);
extern  int * potencia_1_svc(operandos *, struct svc_req *);
#define MODULO 6
extern  int * modulo_1(operandos *, CLIENT *);
extern  int * modulo_1_svc(operandos *, struct svc_req *);
extern int calculadora_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define SUMA 1
extern  int * suma_1();
extern  int * suma_1_svc();
#define MULTIPLICACION 2
extern  int * multiplicacion_1();
extern  int * multiplicacion_1_svc();
#define RESTA 3
extern  int * resta_1();
extern  int * resta_1_svc();
#define DIVISION 4
extern  int * division_1();
extern  int * division_1_svc();
#define POTENCIA 5
extern  int * potencia_1();
extern  int * potencia_1_svc();
#define MODULO 6
extern  int * modulo_1();
extern  int * modulo_1_svc();
extern int calculadora_prog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_operandos (XDR *, operandos*);

#else /* K&R C */
extern bool_t xdr_operandos ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_PRUEBA_H_RPCGEN */