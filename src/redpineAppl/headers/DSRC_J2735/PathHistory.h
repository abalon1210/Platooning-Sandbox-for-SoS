/*
 * Generated by asn1c-0.9.27 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "J2735.asn"
 */

#ifndef	_PathHistory_H_
#define	_PathHistory_H_


#include <asn_application.h>

/* Including external dependencies */
#include "GPSstatus.h"
#include "Count.h"
#include <OCTET_STRING.h>
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>
#include <constr_CHOICE.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum crumbData_PR {
	crumbData_PR_NOTHING,	/* No components present */
	crumbData_PR_pathHistoryPointSets_01,
	crumbData_PR_pathHistoryPointSets_02,
	crumbData_PR_pathHistoryPointSets_03,
	crumbData_PR_pathHistoryPointSets_04,
	crumbData_PR_pathHistoryPointSets_05,
	crumbData_PR_pathHistoryPointSets_06,
	crumbData_PR_pathHistoryPointSets_07,
	crumbData_PR_pathHistoryPointSets_08,
	crumbData_PR_pathHistoryPointSets_09,
	crumbData_PR_pathHistoryPointSets_10
} crumbData_PR;

/* Forward declarations */
struct FullPositionVector;
struct PathHistoryPointType_01;

/* PathHistory */
typedef struct PathHistory {
	struct FullPositionVector	*initialPosition	/* OPTIONAL */;
	GPSstatus_t	*currGPSstatus	/* OPTIONAL */;
	Count_t	*itemCnt	/* OPTIONAL */;
	struct crumbData {
		crumbData_PR present;
		union PathHistory__crumbData_u {
			struct pathHistoryPointSets_01 {
				A_SEQUENCE_OF(struct PathHistoryPointType_01) list;
				
				/* Context for parsing across buffer boundaries */
				asn_struct_ctx_t _asn_ctx;
			} pathHistoryPointSets_01;
			OCTET_STRING_t	 pathHistoryPointSets_02;
			OCTET_STRING_t	 pathHistoryPointSets_03;
			OCTET_STRING_t	 pathHistoryPointSets_04;
			OCTET_STRING_t	 pathHistoryPointSets_05;
			OCTET_STRING_t	 pathHistoryPointSets_06;
			OCTET_STRING_t	 pathHistoryPointSets_07;
			OCTET_STRING_t	 pathHistoryPointSets_08;
			OCTET_STRING_t	 pathHistoryPointSets_09;
			OCTET_STRING_t	 pathHistoryPointSets_10;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} crumbData;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PathHistory_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PathHistory;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "FullPositionVector.h"
#include "PathHistoryPointType-01.h"

#endif	/* _PathHistory_H_ */
#include <asn_internal.h>
