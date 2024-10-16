/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "rpc.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

int *
innerproduct_1(inputData *argp, CLIENT *clnt)
{
	static int clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, INNERPRODUCT,
		(xdrproc_t) xdr_inputData, (caddr_t) argp,
		(xdrproc_t) xdr_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

avgArray *
averages_1(inputData *argp, CLIENT *clnt)
{
	static avgArray clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, AVERAGES,
		(xdrproc_t) xdr_inputData, (caddr_t) argp,
		(xdrproc_t) xdr_avgArray, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

productVector *
product_1(inputData *argp, CLIENT *clnt)
{
	static productVector clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, PRODUCT,
		(xdrproc_t) xdr_inputData, (caddr_t) argp,
		(xdrproc_t) xdr_productVector, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}
