/*
 * Generated by asn1c-0.9.27 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "J2735.asn"
 */

#ifndef	_SnapshotDistance_H_
#define	_SnapshotDistance_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* SnapshotDistance */
typedef struct SnapshotDistance {
	long	 d1;
	long	 s1;
	long	 d2;
	long	 s2;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SnapshotDistance_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SnapshotDistance;

#ifdef __cplusplus
}
#endif

#endif	/* _SnapshotDistance_H_ */
#include <asn_internal.h>
