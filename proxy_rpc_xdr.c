/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "proxy_rpc.h"

bool_t
xdr_proxy_rpc_in (XDR *xdrs, proxy_rpc_in *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->arg, ~0))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_proxy_rpc_out (XDR *xdrs, proxy_rpc_out *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->len))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->res, ~0))
		 return FALSE;
	return TRUE;
}