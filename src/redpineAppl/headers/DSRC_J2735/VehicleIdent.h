/*
 * Generated by asn1c-0.9.27 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "J2735.asn"
 */

#ifndef	_VehicleIdent_H_
#define	_VehicleIdent_H_


#include <asn_application.h>

/* Including external dependencies */
#include "DescriptiveName.h"
#include "VINstring.h"
#include <IA5String.h>
#include "TemporaryID.h"
#include "VehicleType.h"
#include "VehicleGroupAffected.h"
#include "ResponderGroupAffected.h"
#include "IncidentResponseEquipment.h"
#include <constr_CHOICE.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum vehicleClass_PR {
	vehicleClass_PR_NOTHING,	/* No components present */
	vehicleClass_PR_vGroup,
	vehicleClass_PR_rGroup,
	vehicleClass_PR_rEquip
} vehicleClass_PR;

/* VehicleIdent */
typedef struct VehicleIdent {
	DescriptiveName_t	*name	/* OPTIONAL */;
	VINstring_t	*vin	/* OPTIONAL */;
	IA5String_t	*ownerCode	/* OPTIONAL */;
	TemporaryID_t	*id	/* OPTIONAL */;
	VehicleType_t	*vehicleType	/* OPTIONAL */;
	struct vehicleClass {
		vehicleClass_PR present;
		union VehicleIdent__vehicleClass_u {
			VehicleGroupAffected_t	 vGroup;
			ResponderGroupAffected_t	 rGroup;
			IncidentResponseEquipment_t	 rEquip;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *vehicleClass;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} VehicleIdent_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_VehicleIdent;

#ifdef __cplusplus
}
#endif

#endif	/* _VehicleIdent_H_ */
#include <asn_internal.h>
