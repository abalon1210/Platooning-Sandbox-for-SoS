/*
 * Generated by asn1c-0.9.27 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "J2735.asn"
 */

#ifndef	_ColorState_H_
#define	_ColorState_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum ColorState {
	ColorState_dark	= 0,
	ColorState_green	= 1,
	ColorState_green_flashing	= 9,
	ColorState_yellow	= 2,
	ColorState_yellow_flashing	= 10,
	ColorState_red	= 4,
	ColorState_red_flashing	= 12
} e_ColorState;

/* ColorState */
typedef long	 ColorState_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ColorState;
asn_struct_free_f ColorState_free;
asn_struct_print_f ColorState_print;
asn_constr_check_f ColorState_constraint;
ber_type_decoder_f ColorState_decode_ber;
der_type_encoder_f ColorState_encode_der;
xer_type_decoder_f ColorState_decode_xer;
xer_type_encoder_f ColorState_encode_xer;

#ifdef __cplusplus
}
#endif

#endif	/* _ColorState_H_ */
#include <asn_internal.h>
