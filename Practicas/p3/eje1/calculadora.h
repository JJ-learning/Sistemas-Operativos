/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _CALCULADORA_H_RPCGEN
#define _CALCULADORA_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif

#define N 50

struct vector_cal {
	struct {
		u_int vector_len;
		int *vector_val;
	} vector;
};
typedef struct vector_cal vector_cal;

#define CALCULADORA 0x30000050
#define CALCULADORA_VER 1

#if defined(__STDC__) || defined(__cplusplus)
#define media 1
extern  int * media_1(vector_cal *, CLIENT *);
extern  int * media_1_svc(vector_cal *, struct svc_req *);
#define maximo 2
extern  int * maximo_1(vector_cal *, CLIENT *);
extern  int * maximo_1_svc(vector_cal *, struct svc_req *);
#define factorial 3
extern  int * factorial_1(vector_cal *, CLIENT *);
extern  int * factorial_1_svc(vector_cal *, struct svc_req *);
extern int calculadora_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define media 1
extern  int * media_1();
extern  int * media_1_svc();
#define maximo 2
extern  int * maximo_1();
extern  int * maximo_1_svc();
#define factorial 3
extern  int * factorial_1();
extern  int * factorial_1_svc();
extern int calculadora_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_vector_cal (XDR *, vector_cal*);

#else /* K&R C */
extern bool_t xdr_vector_cal ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_CALCULADORA_H_RPCGEN */
