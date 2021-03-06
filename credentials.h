/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _CREDENTIALS_H_RPCGEN
#define _CREDENTIALS_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct cred_in {
	char username[256];
	char password[256];
};
typedef struct cred_in cred_in;

struct cred_out {
	long rescode;
	long usercount;
};
typedef struct cred_out cred_out;

#define CREDENTIALS_PROG 0x13451111
#define CREDENTIALS_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define REGISTERPROC 1
extern  cred_out * registerproc_1(cred_in *, CLIENT *);
extern  cred_out * registerproc_1_svc(cred_in *, struct svc_req *);
#define LOGINPROC 2
extern  cred_out * loginproc_1(cred_in *, CLIENT *);
extern  cred_out * loginproc_1_svc(cred_in *, struct svc_req *);
extern int credentials_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define REGISTERPROC 1
extern  cred_out * registerproc_1();
extern  cred_out * registerproc_1_svc();
#define LOGINPROC 2
extern  cred_out * loginproc_1();
extern  cred_out * loginproc_1_svc();
extern int credentials_prog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_cred_in (XDR *, cred_in*);
extern  bool_t xdr_cred_out (XDR *, cred_out*);

#else /* K&R C */
extern bool_t xdr_cred_in ();
extern bool_t xdr_cred_out ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_CREDENTIALS_H_RPCGEN */
