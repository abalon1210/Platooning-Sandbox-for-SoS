/*
 * Generated by asn1c-0.9.27 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "J2735.asn"
 */

#ifndef	_WiperStatus_H_
#define	_WiperStatus_H_


#include <asn_application.h>

/* Including external dependencies */
#include "WiperStatusFront.h"
#include "WiperRate.h"
#include "WiperStatusRear.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* WiperStatus */
typedef struct WiperStatus {
	WiperStatusFront_t	 statusFront;
	WiperRate_t	 rateFront;
	WiperStatusRear_t	*statusRear	/* OPTIONAL */;
	WiperRate_t	*rateRear	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} WiperStatus_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_WiperStatus;

#ifdef __cplusplus
}
#endif

#endif	/* _WiperStatus_H_ */
#include <asn_internal.h>
