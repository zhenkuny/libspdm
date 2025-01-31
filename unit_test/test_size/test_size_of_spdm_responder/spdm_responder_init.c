/**
    Copyright Notice:
    Copyright 2021 DMTF. All rights reserved.
    License: BSD 3-Clause License. For full text see link: https://github.com/DMTF/libspdm/blob/main/LICENSE.md
**/

#include "spdm_responder.h"

return_status SpdmResponderSendMessage(IN void *spdm_context,
				       IN uintn message_size, IN void *message,
				       IN uint64 timeout)
{
	// Dummy
	return RETURN_SUCCESS;
}

return_status SpdmResponderReceiveMessage(IN void *spdm_context,
					  IN OUT uintn *message_size,
					  IN OUT void *message,
					  IN uint64 timeout)
{
	// Dummy
	return RETURN_SUCCESS;
}

void *spdm_server_init(void)
{
	void *spdm_context;
	spdm_data_parameter_t parameter;
	uint8 data8;
	uint16 data16;
	uint32 data32;
	boolean has_rsp_pub_cert;
	boolean has_rsp_priv_key;
	boolean has_req_pub_cert;

	spdm_context = (void *)allocate_pool(spdm_get_context_size());
	if (spdm_context == NULL) {
		return NULL;
	}
	spdm_init_context(spdm_context);
	spdm_register_device_io_func(spdm_context, SpdmResponderSendMessage,
				     SpdmResponderReceiveMessage);
	spdm_register_transport_layer_func(spdm_context,
					   spdm_transport_mctp_encode_message,
					   spdm_transport_mctp_decode_message);

	has_rsp_pub_cert = FALSE;
	has_rsp_priv_key = FALSE;
	has_req_pub_cert = FALSE;

	data8 = 0;
	zero_mem(&parameter, sizeof(parameter));
	parameter.location = SPDM_DATA_LOCATION_LOCAL;
	spdm_set_data(spdm_context, SPDM_DATA_CAPABILITY_CT_EXPONENT,
		      &parameter, &data8, sizeof(data8));

	data32 =
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_CERT_CAP |
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_CHAL_CAP |
		//           SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_MEAS_CAP_NO_SIG |
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_MEAS_CAP_SIG |
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_ENCRYPT_CAP |
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_MAC_CAP |
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_MUT_AUTH_CAP |
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_KEY_EX_CAP |
		//           SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_PSK_CAP_RESPONDER |
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_PSK_CAP_RESPONDER_WITH_CONTEXT |
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_ENCAP_CAP |
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_HBEAT_CAP |
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_KEY_UPD_CAP |
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_HANDSHAKE_IN_THE_CLEAR_CAP /* |
           SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_PUB_KEY_ID_CAP*/
		;
	if (!has_rsp_pub_cert) {
		data32 &= ~SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_CERT_CAP;
	} else {
		data32 |= SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_CERT_CAP;
	}
	if (!has_rsp_priv_key) {
		data32 &= ~SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_CHAL_CAP;
		data32 &= ~SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_MEAS_CAP_SIG;
		data32 |= SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_MEAS_CAP_NO_SIG;
	} else {
		data32 |= SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_CHAL_CAP;
		data32 |= SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_MEAS_CAP_SIG;
		data32 &= ~SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_MEAS_CAP_NO_SIG;
	}
	if (!has_req_pub_cert) {
		data32 &= ~SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_MUT_AUTH_CAP;
	} else {
		data32 |= SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_MUT_AUTH_CAP;
	}
	spdm_set_data(spdm_context, SPDM_DATA_CAPABILITY_FLAGS, &parameter,
		      &data32, sizeof(data32));

	data32 = SPDM_ALGORITHMS_BASE_ASYM_ALGO_TPM_ALG_RSASSA_2048;
	spdm_set_data(spdm_context, SPDM_DATA_BASE_ASYM_ALGO, &parameter,
		      &data32, sizeof(data32));
	data32 = SPDM_ALGORITHMS_BASE_HASH_ALGO_TPM_ALG_SHA_256;
	spdm_set_data(spdm_context, SPDM_DATA_BASE_HASH_ALGO, &parameter,
		      &data32, sizeof(data32));
	data16 = SPDM_ALGORITHMS_DHE_NAMED_GROUP_FFDHE_2048;
	spdm_set_data(spdm_context, SPDM_DATA_DHE_NAME_GROUP, &parameter,
		      &data16, sizeof(data16));
	data16 = SPDM_ALGORITHMS_KEY_SCHEDULE_HMAC_HASH;
	spdm_set_data(spdm_context, SPDM_DATA_AEAD_CIPHER_SUITE, &parameter,
		      &data16, sizeof(data16));
	data16 = SPDM_ALGORITHMS_KEY_SCHEDULE_HMAC_HASH;
	spdm_set_data(spdm_context, SPDM_DATA_KEY_SCHEDULE, &parameter, &data16,
		      sizeof(data16));

	return spdm_context;
}