/**
    Copyright Notice:
    Copyright 2021 DMTF. All rights reserved.
    License: BSD 3-Clause License. For full text see link: https://github.com/DMTF/libspdm/blob/main/LICENSE.md
**/

#include "spdm_unit_test.h"
#include <spdm_requester_lib_internal.h>
#include <spdm_secured_message_lib_internal.h>

static uint8 m_local_psk_hint[32];
static uint8 m_dummy_key_buffer[MAX_AEAD_KEY_SIZE];
static uint8 m_dummy_salt_buffer[MAX_AEAD_IV_SIZE];

static void spdm_secured_message_set_dummy_finished_key(
	IN void *spdm_secured_message_context)
{
	spdm_secured_message_context_t *secured_message_context;

	secured_message_context = spdm_secured_message_context;
	secured_message_context->finished_key_ready = TRUE;
}

void spdm_secured_message_set_response_handshake_encryption_key(
	IN void *spdm_secured_message_context, IN void *key, IN uintn key_size)
{
	spdm_secured_message_context_t *secured_message_context;

	secured_message_context = spdm_secured_message_context;
	ASSERT(key_size == secured_message_context->aead_key_size);
	copy_mem(secured_message_context->handshake_secret
			 .response_handshake_encryption_key,
		 key, secured_message_context->aead_key_size);
}

void spdm_secured_message_set_response_handshake_salt(
	IN void *spdm_secured_message_context, IN void *salt,
	IN uintn salt_size)
{
	spdm_secured_message_context_t *secured_message_context;

	secured_message_context = spdm_secured_message_context;
	ASSERT(salt_size == secured_message_context->aead_iv_size);
	copy_mem(secured_message_context->handshake_secret
			 .response_handshake_salt,
		 salt, secured_message_context->aead_iv_size);
}

return_status spdm_requester_psk_finish_test_send_message(IN void *spdm_context,
							  IN uintn request_size,
							  IN void *request,
							  IN uint64 timeout)
{
	spdm_test_context_t *spdm_test_context;

	spdm_test_context = get_spdm_test_context();
	switch (spdm_test_context->case_id) {
	case 0x1:
		return RETURN_DEVICE_ERROR;
	case 0x2:
		return RETURN_SUCCESS;
	case 0x3:
		return RETURN_SUCCESS;
	case 0x4:
		return RETURN_SUCCESS;
	case 0x5:
		return RETURN_SUCCESS;
	case 0x6:
		return RETURN_SUCCESS;
	case 0x7:
		return RETURN_SUCCESS;
	case 0x8:
		return RETURN_SUCCESS;
	case 0x9:
		return RETURN_SUCCESS;
	case 0xA:
		return RETURN_SUCCESS;
	case 0xB:
		return RETURN_SUCCESS;
	case 0xC:
		return RETURN_SUCCESS;
	case 0xD:
		return RETURN_SUCCESS;
	case 0xE:
		return RETURN_SUCCESS;
	default:
		return RETURN_DEVICE_ERROR;
	}
}

return_status spdm_requester_psk_finish_test_receive_message(
	IN void *spdm_context, IN OUT uintn *response_size,
	IN OUT void *response, IN uint64 timeout)
{
	spdm_test_context_t *spdm_test_context;

	spdm_test_context = get_spdm_test_context();
	switch (spdm_test_context->case_id) {
	case 0x1:
		return RETURN_DEVICE_ERROR;

	case 0x2: {
		spdm_psk_finish_response_t *spdm_response;
		uint8 temp_buf[MAX_SPDM_MESSAGE_BUFFER_SIZE];
		uintn temp_buf_size;
		uint32 session_id;
		spdm_session_info_t *session_info;

		session_id = 0xFFFFFFFF;
		temp_buf_size = sizeof(spdm_psk_finish_response_t);
		spdm_response = (void *)temp_buf;

		spdm_response->header.spdm_version = SPDM_MESSAGE_VERSION_11;
		spdm_response->header.request_response_code =
			SPDM_PSK_FINISH_RSP;
		spdm_response->header.param1 = 0;
		spdm_response->header.param2 = 0;

		spdm_transport_test_encode_message(spdm_context, &session_id,
						   FALSE, FALSE, temp_buf_size,
						   temp_buf, response_size,
						   response);
		session_info = spdm_get_session_info_via_session_id(
			spdm_context, session_id);
		if (session_info == NULL) {
			return RETURN_DEVICE_ERROR;
		}
		/* WALKAROUND: If just use single context to encode message and then decode message */
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->handshake_secret.response_handshake_sequence_number--;
	}
		return RETURN_SUCCESS;

	case 0x3: {
		spdm_psk_finish_response_t *spdm_response;
		uint8 temp_buf[MAX_SPDM_MESSAGE_BUFFER_SIZE];
		uintn temp_buf_size;
		uint32 session_id;
		spdm_session_info_t *session_info;

		session_id = 0xFFFFFFFF;
		temp_buf_size = sizeof(spdm_psk_finish_response_t);
		spdm_response = (void *)temp_buf;

		spdm_response->header.spdm_version = SPDM_MESSAGE_VERSION_11;
		spdm_response->header.request_response_code =
			SPDM_PSK_FINISH_RSP;
		spdm_response->header.param1 = 0;
		spdm_response->header.param2 = 0;

		spdm_transport_test_encode_message(spdm_context, &session_id,
						   FALSE, FALSE, temp_buf_size,
						   temp_buf, response_size,
						   response);
		session_info = spdm_get_session_info_via_session_id(
			spdm_context, session_id);
		if (session_info == NULL) {
			return RETURN_DEVICE_ERROR;
		}
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->handshake_secret.response_handshake_sequence_number--;
	}
		return RETURN_SUCCESS;

	case 0x4: {
		spdm_error_response_t spdm_response;
		uint32 session_id;
		spdm_session_info_t *session_info;

		session_id = 0xFFFFFFFF;
		spdm_response.header.spdm_version = SPDM_MESSAGE_VERSION_11;
		spdm_response.header.request_response_code = SPDM_ERROR;
		spdm_response.header.param1 = SPDM_ERROR_CODE_INVALID_REQUEST;
		spdm_response.header.param2 = 0;

		spdm_transport_test_encode_message(spdm_context, &session_id,
						   FALSE, FALSE,
						   sizeof(spdm_response),
						   &spdm_response,
						   response_size, response);
		session_info = spdm_get_session_info_via_session_id(
			spdm_context, session_id);
		if (session_info == NULL) {
			return RETURN_DEVICE_ERROR;
		}
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->handshake_secret.response_handshake_sequence_number--;
	}
		return RETURN_SUCCESS;

	case 0x5: {
		spdm_error_response_t spdm_response;
		uint32 session_id;
		spdm_session_info_t *session_info;

		session_id = 0xFFFFFFFF;
		spdm_response.header.spdm_version = SPDM_MESSAGE_VERSION_11;
		spdm_response.header.request_response_code = SPDM_ERROR;
		spdm_response.header.param1 = SPDM_ERROR_CODE_BUSY;
		spdm_response.header.param2 = 0;

		spdm_transport_test_encode_message(spdm_context, &session_id,
						   FALSE, FALSE,
						   sizeof(spdm_response),
						   &spdm_response,
						   response_size, response);
		session_info = spdm_get_session_info_via_session_id(
			spdm_context, session_id);
		if (session_info == NULL) {
			return RETURN_DEVICE_ERROR;
		}
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->handshake_secret.response_handshake_sequence_number--;
	}
		return RETURN_SUCCESS;

	case 0x6: {
		static uintn sub_index1 = 0;
		if (sub_index1 == 0) {
			spdm_error_response_t spdm_response;
			uint32 session_id;
			spdm_session_info_t *session_info;

			session_id = 0xFFFFFFFF;
			spdm_response.header.spdm_version =
				SPDM_MESSAGE_VERSION_11;
			spdm_response.header.request_response_code = SPDM_ERROR;
			spdm_response.header.param1 = SPDM_ERROR_CODE_BUSY;
			spdm_response.header.param2 = 0;

			spdm_transport_test_encode_message(
				spdm_context, &session_id, FALSE, FALSE,
				sizeof(spdm_response), &spdm_response,
				response_size, response);
			sub_index1++;
			session_info = spdm_get_session_info_via_session_id(
				spdm_context, session_id);
			if (session_info == NULL) {
				return RETURN_DEVICE_ERROR;
			}
			((spdm_secured_message_context_t
				  *)(session_info->secured_message_context))
				->handshake_secret
				.response_handshake_sequence_number--;
		} else if (sub_index1 == 1) {
			spdm_psk_finish_response_t *spdm_response;
			uint8 temp_buf[MAX_SPDM_MESSAGE_BUFFER_SIZE];
			uintn temp_buf_size;
			uint32 session_id;
			spdm_session_info_t *session_info;

			session_id = 0xFFFFFFFF;
			temp_buf_size = sizeof(spdm_psk_finish_response_t);
			spdm_response = (void *)temp_buf;

			spdm_response->header.spdm_version =
				SPDM_MESSAGE_VERSION_11;
			spdm_response->header.request_response_code =
				SPDM_PSK_FINISH_RSP;
			spdm_response->header.param1 = 0;
			spdm_response->header.param2 = 0;

			spdm_transport_test_encode_message(
				spdm_context, &session_id, FALSE, FALSE,
				temp_buf_size, temp_buf, response_size,
				response);
			session_info = spdm_get_session_info_via_session_id(
				spdm_context, session_id);
			if (session_info == NULL) {
				return RETURN_DEVICE_ERROR;
			}
			((spdm_secured_message_context_t
				  *)(session_info->secured_message_context))
				->handshake_secret
				.response_handshake_sequence_number--;
		}
	}
		return RETURN_SUCCESS;

	case 0x7: {
		spdm_error_response_t spdm_response;
		uint32 session_id;
		spdm_session_info_t *session_info;

		session_id = 0xFFFFFFFF;
		spdm_response.header.spdm_version = SPDM_MESSAGE_VERSION_11;
		spdm_response.header.request_response_code = SPDM_ERROR;
		spdm_response.header.param1 = SPDM_ERROR_CODE_REQUEST_RESYNCH;
		spdm_response.header.param2 = 0;

		spdm_transport_test_encode_message(spdm_context, &session_id,
						   FALSE, FALSE,
						   sizeof(spdm_response),
						   &spdm_response,
						   response_size, response);
		session_info = spdm_get_session_info_via_session_id(
			spdm_context, session_id);
		if (session_info == NULL) {
			return RETURN_DEVICE_ERROR;
		}
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->handshake_secret.response_handshake_sequence_number--;
	}
		return RETURN_SUCCESS;

	case 0x8: {
		spdm_error_response_data_response_not_ready_t spdm_response;
		uint32 session_id;
		spdm_session_info_t *session_info;

		session_id = 0xFFFFFFFF;
		spdm_response.header.spdm_version = SPDM_MESSAGE_VERSION_11;
		spdm_response.header.request_response_code = SPDM_ERROR;
		spdm_response.header.param1 =
			SPDM_ERROR_CODE_RESPONSE_NOT_READY;
		spdm_response.header.param2 = 0;
		spdm_response.extend_error_data.rd_exponent = 1;
		spdm_response.extend_error_data.rd_tm = 1;
		spdm_response.extend_error_data.request_code = SPDM_PSK_FINISH;
		spdm_response.extend_error_data.token = 0;

		spdm_transport_test_encode_message(spdm_context, &session_id,
						   FALSE, FALSE,
						   sizeof(spdm_response),
						   &spdm_response,
						   response_size, response);
		session_info = spdm_get_session_info_via_session_id(
			spdm_context, session_id);
		if (session_info == NULL) {
			return RETURN_DEVICE_ERROR;
		}
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->handshake_secret.response_handshake_sequence_number--;
	}
		return RETURN_SUCCESS;

	case 0x9: {
		static uintn sub_index2 = 0;
		if (sub_index2 == 0) {
			spdm_error_response_data_response_not_ready_t
				spdm_response;
			uint32 session_id;
			spdm_session_info_t *session_info;

			session_id = 0xFFFFFFFF;
			spdm_response.header.spdm_version =
				SPDM_MESSAGE_VERSION_11;
			spdm_response.header.request_response_code = SPDM_ERROR;
			spdm_response.header.param1 =
				SPDM_ERROR_CODE_RESPONSE_NOT_READY;
			spdm_response.header.param2 = 0;
			spdm_response.extend_error_data.rd_exponent = 1;
			spdm_response.extend_error_data.rd_tm = 1;
			spdm_response.extend_error_data.request_code =
				SPDM_PSK_FINISH;
			spdm_response.extend_error_data.token = 1;

			spdm_transport_test_encode_message(
				spdm_context, &session_id, FALSE, FALSE,
				sizeof(spdm_response), &spdm_response,
				response_size, response);
			sub_index2++;
			session_info = spdm_get_session_info_via_session_id(
				spdm_context, session_id);
			if (session_info == NULL) {
				return RETURN_DEVICE_ERROR;
			}
			((spdm_secured_message_context_t
				  *)(session_info->secured_message_context))
				->handshake_secret
				.response_handshake_sequence_number--;
		} else if (sub_index2 == 1) {
			spdm_psk_finish_response_t *spdm_response;
			uint8 temp_buf[MAX_SPDM_MESSAGE_BUFFER_SIZE];
			uintn temp_buf_size;
			uint32 session_id;
			spdm_session_info_t *session_info;

			session_id = 0xFFFFFFFF;
			temp_buf_size = sizeof(spdm_psk_finish_response_t);
			spdm_response = (void *)temp_buf;

			spdm_response->header.spdm_version =
				SPDM_MESSAGE_VERSION_11;
			spdm_response->header.request_response_code =
				SPDM_PSK_FINISH_RSP;
			spdm_response->header.param1 = 0;
			spdm_response->header.param2 = 0;

			spdm_transport_test_encode_message(
				spdm_context, &session_id, FALSE, FALSE,
				temp_buf_size, temp_buf, response_size,
				response);
			session_info = spdm_get_session_info_via_session_id(
				spdm_context, session_id);
			if (session_info == NULL) {
				return RETURN_DEVICE_ERROR;
			}
			((spdm_secured_message_context_t
				  *)(session_info->secured_message_context))
				->handshake_secret
				.response_handshake_sequence_number--;
		}
	}
		return RETURN_SUCCESS;

  case 0xA:
  {
    static uint16 error_code = SPDM_ERROR_CODE_RESERVED_00;

    spdm_error_response_t    spdm_response;
    uint32                 session_id;
    spdm_session_info_t      *session_info;

    session_id = 0xFFFFFFFF;

    if(error_code <= 0xff) {
      zero_mem (&spdm_response, sizeof(spdm_response));
      spdm_response.header.spdm_version = SPDM_MESSAGE_VERSION_11;
      spdm_response.header.request_response_code = SPDM_ERROR;
      spdm_response.header.param1 = (uint8) error_code;
      spdm_response.header.param2 = 0;

      spdm_transport_test_encode_message (spdm_context, &session_id, FALSE, FALSE, sizeof(spdm_response), &spdm_response, response_size, response);
      session_info = spdm_get_session_info_via_session_id (spdm_context, session_id);
      ((spdm_secured_message_context_t*)(session_info->secured_message_context))->handshake_secret.response_handshake_sequence_number --;
    }

    error_code++;
    if(error_code == SPDM_ERROR_CODE_BUSY) { //busy is treated in cases 5 and 6
      error_code = SPDM_ERROR_CODE_UNEXPECTED_REQUEST;
    }
    if(error_code == SPDM_ERROR_CODE_RESERVED_0D) { //skip some reserved error codes (0d to 3e)
      error_code = SPDM_ERROR_CODE_RESERVED_3F;
    }
    if(error_code == SPDM_ERROR_CODE_RESPONSE_NOT_READY) { //skip response not ready, request resync, and some reserved codes (44 to fc)
      error_code = SPDM_ERROR_CODE_RESERVED_FD;
    }
  }
    return RETURN_SUCCESS;
	case 0xB: {
		spdm_psk_finish_response_t *spdm_response;
		uint8 temp_buf[MAX_SPDM_MESSAGE_BUFFER_SIZE];
		uintn temp_buf_size;
		uint32 session_id;
		spdm_session_info_t *session_info;

		session_id = 0xFFFFFFFF;
		temp_buf_size = sizeof(spdm_psk_finish_response_t);
		spdm_response = (void *)temp_buf;

		spdm_response->header.spdm_version = SPDM_MESSAGE_VERSION_11;
		spdm_response->header.request_response_code =
			SPDM_PSK_FINISH_RSP;
		spdm_response->header.param1 = 0;
		spdm_response->header.param2 = 0;

		spdm_transport_test_encode_message(spdm_context, &session_id,
						   FALSE, FALSE, temp_buf_size,
						   temp_buf, response_size,
						   response);
		session_info = spdm_get_session_info_via_session_id(
			spdm_context, session_id);
		if (session_info == NULL) {
			return RETURN_DEVICE_ERROR;
		}
		/* WALKAROUND: If just use single context to encode message and then decode message */
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->handshake_secret.response_handshake_sequence_number--;
	}
		return RETURN_SUCCESS;

	case 0xC: {
		spdm_psk_finish_response_t *spdm_response;
		uint8 temp_buf[MAX_SPDM_MESSAGE_BUFFER_SIZE];
		uintn temp_buf_size;
		uint32 session_id;
		spdm_session_info_t *session_info;

		session_id = 0xFFFFFFFF;
		temp_buf_size = sizeof(spdm_psk_finish_response_t);
		spdm_response = (void *)temp_buf;

		spdm_response->header.spdm_version = SPDM_MESSAGE_VERSION_11;
		spdm_response->header.request_response_code =
			SPDM_PSK_FINISH_RSP;
		spdm_response->header.param1 = 0;
		spdm_response->header.param2 = 0;

		spdm_transport_test_encode_message(spdm_context, &session_id,
						   FALSE, FALSE, temp_buf_size,
						   temp_buf, response_size,
						   response);
		session_info = spdm_get_session_info_via_session_id(
			spdm_context, session_id);
		if (session_info == NULL) {
			return RETURN_DEVICE_ERROR;
		}
		/* WALKAROUND: If just use single context to encode message and then decode message */
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->handshake_secret.response_handshake_sequence_number--;
	}
		return RETURN_SUCCESS;

	case 0xD: {
		spdm_psk_finish_response_t *spdm_response;
		uint8 temp_buf[MAX_SPDM_MESSAGE_BUFFER_SIZE];
		uintn temp_buf_size;
		uint32 session_id;
		spdm_session_info_t *session_info;

		session_id = 0xFFFFFFFF;
		temp_buf_size = sizeof(spdm_psk_finish_response_t);
		spdm_response = (void *)temp_buf;

		spdm_response->header.spdm_version = SPDM_MESSAGE_VERSION_11;
		spdm_response->header.request_response_code =
			SPDM_FINISH_RSP; //wrong response code
		spdm_response->header.param1 = 0;
		spdm_response->header.param2 = 0;

		spdm_transport_test_encode_message(spdm_context, &session_id,
						   FALSE, FALSE, temp_buf_size,
						   temp_buf, response_size,
						   response);
		session_info = spdm_get_session_info_via_session_id(
			spdm_context, session_id);
		if (session_info == NULL) {
			return RETURN_DEVICE_ERROR;
		}
		/* WALKAROUND: If just use single context to encode message and then decode message */
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->handshake_secret.response_handshake_sequence_number--;
	}
		return RETURN_SUCCESS;

	case 0xE: {
		spdm_psk_finish_response_t *spdm_response;
		uint8 temp_buf[MAX_SPDM_MESSAGE_BUFFER_SIZE];
		uintn temp_buf_size;
		uint32 session_id;
		spdm_session_info_t *session_info;

		session_id = 0xFFFFFFFF;
		temp_buf_size = sizeof(spdm_psk_finish_response_t);
		spdm_response = (void *)temp_buf;

		spdm_response->header.spdm_version = SPDM_MESSAGE_VERSION_11;
		spdm_response->header.request_response_code =
			SPDM_PSK_FINISH_RSP;
		spdm_response->header.param1 = 0;
		spdm_response->header.param2 = 0;

		spdm_transport_test_encode_message(spdm_context, &session_id,
						   FALSE, FALSE, temp_buf_size,
						   temp_buf, response_size,
						   response);
		session_info = spdm_get_session_info_via_session_id(
			spdm_context, session_id);
		if (session_info == NULL) {
			return RETURN_DEVICE_ERROR;
		}
		/* WALKAROUND: If just use single context to encode message and then decode message */
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->handshake_secret.response_handshake_sequence_number--;
	}
		return RETURN_SUCCESS;
	default:
		return RETURN_DEVICE_ERROR;
	}
}

/**
  Test 1: when no PSK_FINISH_RSP message is received, and the client returns
  a device error.
  Expected behavior: client returns a Status of RETURN_DEVICE_ERROR.
**/
void test_spdm_requester_psk_finish_case1(void **state)
{
	return_status status;
	spdm_test_context_t *spdm_test_context;
	spdm_context_t *spdm_context;
	uint32 session_id;
	void *data;
	uintn data_size;
	void *hash;
	uintn hash_size;
	spdm_session_info_t *session_info;

	spdm_test_context = *state;
	spdm_context = spdm_test_context->spdm_context;
	spdm_test_context->case_id = 0x1;
	spdm_context->connection_info.connection_state =
		SPDM_CONNECTION_STATE_NEGOTIATED;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_PSK_CAP;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_ENCRYPT_CAP;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_MAC_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_PSK_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_ENCRYPT_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_MAC_CAP;
	read_responder_public_certificate_chain(m_use_hash_algo,
						m_use_asym_algo, &data,
						&data_size, &hash, &hash_size);
	spdm_reset_message_a(spdm_context);
	spdm_context->connection_info.algorithm.base_hash_algo =
		m_use_hash_algo;
	spdm_context->connection_info.algorithm.base_asym_algo =
		m_use_asym_algo;
	spdm_context->connection_info.algorithm.dhe_named_group =
		m_use_dhe_algo;
	spdm_context->connection_info.algorithm.aead_cipher_suite =
		m_use_aead_algo;
	spdm_context->connection_info.peer_used_cert_chain_buffer_size =
		data_size;
	copy_mem(spdm_context->connection_info.peer_used_cert_chain_buffer,
		 data, data_size);
	zero_mem(m_local_psk_hint, 32);
	copy_mem(&m_local_psk_hint[0], TEST_PSK_HINT_STRING,
		 sizeof(TEST_PSK_HINT_STRING));
	spdm_context->local_context.psk_hint_size =
		sizeof(TEST_PSK_HINT_STRING);
	spdm_context->local_context.psk_hint = m_local_psk_hint;

	session_id = 0xFFFFFFFF;
	session_info = &spdm_context->session_info[0];
	spdm_session_info_init(spdm_context, session_info, session_id, TRUE);
	spdm_secured_message_set_session_state(
		session_info->secured_message_context,
		SPDM_SESSION_STATE_HANDSHAKING);
	spdm_secured_message_set_dummy_finished_key (session_info->secured_message_context);

	status = spdm_send_receive_psk_finish(spdm_context, session_id);
	assert_int_equal(status, RETURN_DEVICE_ERROR);
	free(data);
}

/**
  Test 2: receiving a correct PSK_FINISH_RSP message.
  Expected behavior: client returns a Status of RETURN_SUCCESS and
  session is established.
**/
void test_spdm_requester_psk_finish_case2(void **state)
{
	return_status status;
	spdm_test_context_t *spdm_test_context;
	spdm_context_t *spdm_context;
	uint32 session_id;
	void *data;
	uintn data_size;
	void *hash;
	uintn hash_size;
	spdm_session_info_t *session_info;

	spdm_test_context = *state;
	spdm_context = spdm_test_context->spdm_context;
	spdm_test_context->case_id = 0x2;
	spdm_context->connection_info.connection_state =
		SPDM_CONNECTION_STATE_NEGOTIATED;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_PSK_CAP;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_ENCRYPT_CAP;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_MAC_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_PSK_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_ENCRYPT_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_MAC_CAP;
	read_responder_public_certificate_chain(m_use_hash_algo,
						m_use_asym_algo, &data,
						&data_size, &hash, &hash_size);
	spdm_reset_message_a(spdm_context);
	spdm_context->connection_info.algorithm.base_hash_algo =
		m_use_hash_algo;
	spdm_context->connection_info.algorithm.base_asym_algo =
		m_use_asym_algo;
	spdm_context->connection_info.algorithm.dhe_named_group =
		m_use_dhe_algo;
	spdm_context->connection_info.algorithm.aead_cipher_suite =
		m_use_aead_algo;
	spdm_context->connection_info.peer_used_cert_chain_buffer_size =
		data_size;
	copy_mem(spdm_context->connection_info.peer_used_cert_chain_buffer,
		 data, data_size);
	zero_mem(m_local_psk_hint, 32);
	copy_mem(&m_local_psk_hint[0], TEST_PSK_HINT_STRING,
		 sizeof(TEST_PSK_HINT_STRING));
	spdm_context->local_context.psk_hint_size =
		sizeof(TEST_PSK_HINT_STRING);
	spdm_context->local_context.psk_hint = m_local_psk_hint;

	session_id = 0xFFFFFFFF;
	session_info = &spdm_context->session_info[0];
	spdm_session_info_init(spdm_context, session_info, session_id, TRUE);
	spdm_secured_message_set_session_state(
		session_info->secured_message_context,
		SPDM_SESSION_STATE_HANDSHAKING);
	set_mem(m_dummy_key_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_key_size,
		(uint8)(0xFF));
	spdm_secured_message_set_response_handshake_encryption_key(
		session_info->secured_message_context, m_dummy_key_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_key_size);
	set_mem(m_dummy_salt_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_iv_size,
		(uint8)(0xFF));
	spdm_secured_message_set_response_handshake_salt(
		session_info->secured_message_context, m_dummy_salt_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_iv_size);
	((spdm_secured_message_context_t *)(session_info
						    ->secured_message_context))
		->handshake_secret.response_handshake_sequence_number = 0;
	spdm_secured_message_set_dummy_finished_key (session_info->secured_message_context);

	status = spdm_send_receive_psk_finish(spdm_context, session_id);
	assert_int_equal(status, RETURN_SUCCESS);
	assert_int_equal(
		spdm_secured_message_get_session_state(
			spdm_context->session_info[0].secured_message_context),
		SPDM_SESSION_STATE_ESTABLISHED);
	free(data);
}

/**
  Test 3: requester state has not been negotiated, as if GET_VERSION,
  GET_CAPABILITIES and NEGOTIATE_ALGORITHMS had not been exchanged.
  Expected behavior: client returns a Status of RETURN_UNSUPPORTED.
**/
void test_spdm_requester_psk_finish_case3(void **state)
{
	return_status status;
	spdm_test_context_t *spdm_test_context;
	spdm_context_t *spdm_context;
	uint32 session_id;
	void *data;
	uintn data_size;
	void *hash;
	uintn hash_size;
	spdm_session_info_t *session_info;

	spdm_test_context = *state;
	spdm_context = spdm_test_context->spdm_context;
	spdm_test_context->case_id = 0x3;
	spdm_context->connection_info.connection_state =
		SPDM_CONNECTION_STATE_NOT_STARTED;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_PSK_CAP;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_ENCRYPT_CAP;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_MAC_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_PSK_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_ENCRYPT_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_MAC_CAP;
	read_responder_public_certificate_chain(m_use_hash_algo,
						m_use_asym_algo, &data,
						&data_size, &hash, &hash_size);
	spdm_reset_message_a(spdm_context);
	spdm_context->connection_info.algorithm.base_hash_algo =
		m_use_hash_algo;
	spdm_context->connection_info.algorithm.base_asym_algo =
		m_use_asym_algo;
	spdm_context->connection_info.algorithm.dhe_named_group =
		m_use_dhe_algo;
	spdm_context->connection_info.algorithm.aead_cipher_suite =
		m_use_aead_algo;
	spdm_context->connection_info.peer_used_cert_chain_buffer_size =
		data_size;
	copy_mem(spdm_context->connection_info.peer_used_cert_chain_buffer,
		 data, data_size);
	zero_mem(m_local_psk_hint, 32);
	copy_mem(&m_local_psk_hint[0], TEST_PSK_HINT_STRING,
		 sizeof(TEST_PSK_HINT_STRING));
	spdm_context->local_context.psk_hint_size =
		sizeof(TEST_PSK_HINT_STRING);
	spdm_context->local_context.psk_hint = m_local_psk_hint;

	session_id = 0xFFFFFFFF;
	session_info = &spdm_context->session_info[0];
	spdm_session_info_init(spdm_context, session_info, session_id, TRUE);
	spdm_secured_message_set_session_state(
		session_info->secured_message_context,
		SPDM_SESSION_STATE_HANDSHAKING);
	set_mem(m_dummy_key_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_key_size,
		(uint8)(0xFF));
	spdm_secured_message_set_response_handshake_encryption_key(
		session_info->secured_message_context, m_dummy_key_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_key_size);
	set_mem(m_dummy_salt_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_iv_size,
		(uint8)(0xFF));
	spdm_secured_message_set_response_handshake_salt(
		session_info->secured_message_context, m_dummy_salt_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_iv_size);
	((spdm_secured_message_context_t *)(session_info
						    ->secured_message_context))
		->handshake_secret.response_handshake_sequence_number = 0;
	spdm_secured_message_set_dummy_finished_key (session_info->secured_message_context);

	status = spdm_send_receive_psk_finish(spdm_context, session_id);
	assert_int_equal(status, RETURN_UNSUPPORTED);
	free(data);
}

/**
  Test 4: the requester is setup correctly, but receives an ERROR message
  indicating InvalidParameters.
  Expected behavior: client returns a Status of RETURN_DEVICE_ERROR.
**/
void test_spdm_requester_psk_finish_case4(void **state)
{
	return_status status;
	spdm_test_context_t *spdm_test_context;
	spdm_context_t *spdm_context;
	uint32 session_id;
	void *data;
	uintn data_size;
	void *hash;
	uintn hash_size;
	spdm_session_info_t *session_info;

	spdm_test_context = *state;
	spdm_context = spdm_test_context->spdm_context;
	spdm_test_context->case_id = 0x4;
	spdm_context->connection_info.connection_state =
		SPDM_CONNECTION_STATE_NEGOTIATED;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_PSK_CAP;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_ENCRYPT_CAP;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_MAC_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_PSK_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_ENCRYPT_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_MAC_CAP;
	read_responder_public_certificate_chain(m_use_hash_algo,
						m_use_asym_algo, &data,
						&data_size, &hash, &hash_size);
	spdm_reset_message_a(spdm_context);
	spdm_context->connection_info.algorithm.base_hash_algo =
		m_use_hash_algo;
	spdm_context->connection_info.algorithm.base_asym_algo =
		m_use_asym_algo;
	spdm_context->connection_info.algorithm.dhe_named_group =
		m_use_dhe_algo;
	spdm_context->connection_info.algorithm.aead_cipher_suite =
		m_use_aead_algo;
	spdm_context->connection_info.peer_used_cert_chain_buffer_size =
		data_size;
	copy_mem(spdm_context->connection_info.peer_used_cert_chain_buffer,
		 data, data_size);
	zero_mem(m_local_psk_hint, 32);
	copy_mem(&m_local_psk_hint[0], TEST_PSK_HINT_STRING,
		 sizeof(TEST_PSK_HINT_STRING));
	spdm_context->local_context.psk_hint_size =
		sizeof(TEST_PSK_HINT_STRING);
	spdm_context->local_context.psk_hint = m_local_psk_hint;

	session_id = 0xFFFFFFFF;
	session_info = &spdm_context->session_info[0];
	spdm_session_info_init(spdm_context, session_info, session_id, TRUE);
	spdm_secured_message_set_session_state(
		session_info->secured_message_context,
		SPDM_SESSION_STATE_HANDSHAKING);
	set_mem(m_dummy_key_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_key_size,
		(uint8)(0xFF));
	spdm_secured_message_set_response_handshake_encryption_key(
		session_info->secured_message_context, m_dummy_key_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_key_size);
	set_mem(m_dummy_salt_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_iv_size,
		(uint8)(0xFF));
	spdm_secured_message_set_response_handshake_salt(
		session_info->secured_message_context, m_dummy_salt_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_iv_size);
	((spdm_secured_message_context_t *)(session_info
						    ->secured_message_context))
		->handshake_secret.response_handshake_sequence_number = 0;
	spdm_secured_message_set_dummy_finished_key (session_info->secured_message_context);

	status = spdm_send_receive_psk_finish(spdm_context, session_id);
	assert_int_equal(status, RETURN_DEVICE_ERROR);
	free(data);
}

/**
  Test 5: the requester is setup correctly, but receives an ERROR message
  indicating the Busy status of the responder.
  Expected behavior: client returns a Status of RETURN_DEVICE_ERROR.
**/
void test_spdm_requester_psk_finish_case5(void **state)
{
	return_status status;
	spdm_test_context_t *spdm_test_context;
	spdm_context_t *spdm_context;
	uint32 session_id;
	void *data;
	uintn data_size;
	void *hash;
	uintn hash_size;
	spdm_session_info_t *session_info;

	spdm_test_context = *state;
	spdm_context = spdm_test_context->spdm_context;
	spdm_test_context->case_id = 0x5;
	spdm_context->connection_info.connection_state =
		SPDM_CONNECTION_STATE_NEGOTIATED;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_PSK_CAP;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_ENCRYPT_CAP;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_MAC_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_PSK_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_ENCRYPT_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_MAC_CAP;
	read_responder_public_certificate_chain(m_use_hash_algo,
						m_use_asym_algo, &data,
						&data_size, &hash, &hash_size);
	spdm_reset_message_a(spdm_context);
	spdm_context->connection_info.algorithm.base_hash_algo =
		m_use_hash_algo;
	spdm_context->connection_info.algorithm.base_asym_algo =
		m_use_asym_algo;
	spdm_context->connection_info.algorithm.dhe_named_group =
		m_use_dhe_algo;
	spdm_context->connection_info.algorithm.aead_cipher_suite =
		m_use_aead_algo;
	spdm_context->connection_info.peer_used_cert_chain_buffer_size =
		data_size;
	copy_mem(spdm_context->connection_info.peer_used_cert_chain_buffer,
		 data, data_size);
	zero_mem(m_local_psk_hint, 32);
	copy_mem(&m_local_psk_hint[0], TEST_PSK_HINT_STRING,
		 sizeof(TEST_PSK_HINT_STRING));
	spdm_context->local_context.psk_hint_size =
		sizeof(TEST_PSK_HINT_STRING);
	spdm_context->local_context.psk_hint = m_local_psk_hint;

	session_id = 0xFFFFFFFF;
	session_info = &spdm_context->session_info[0];
	spdm_session_info_init(spdm_context, session_info, session_id, TRUE);
	spdm_secured_message_set_session_state(
		session_info->secured_message_context,
		SPDM_SESSION_STATE_HANDSHAKING);
	set_mem(m_dummy_key_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_key_size,
		(uint8)(0xFF));
	spdm_secured_message_set_response_handshake_encryption_key(
		session_info->secured_message_context, m_dummy_key_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_key_size);
	set_mem(m_dummy_salt_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_iv_size,
		(uint8)(0xFF));
	spdm_secured_message_set_response_handshake_salt(
		session_info->secured_message_context, m_dummy_salt_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_iv_size);
	((spdm_secured_message_context_t *)(session_info
						    ->secured_message_context))
		->handshake_secret.response_handshake_sequence_number = 0;
	spdm_secured_message_set_dummy_finished_key (session_info->secured_message_context);

	status = spdm_send_receive_psk_finish(spdm_context, session_id);
	assert_int_equal(status, RETURN_NO_RESPONSE);
	free(data);
}

/**
  Test 6: the requester is setup correctly, but, on the first try, receiving
  a Busy ERROR message, and, on retry, receiving a correct PSK_FINISH_RSP
  message.
  Expected behavior: client returns a Status of RETURN_SUCCESS and session
  is established.
**/
void test_spdm_requester_psk_finish_case6(void **state)
{
	return_status status;
	spdm_test_context_t *spdm_test_context;
	spdm_context_t *spdm_context;
	uint32 session_id;
	void *data;
	uintn data_size;
	void *hash;
	uintn hash_size;
	spdm_session_info_t *session_info;

	spdm_test_context = *state;
	spdm_context = spdm_test_context->spdm_context;
	spdm_test_context->case_id = 0x6;
	spdm_context->connection_info.connection_state =
		SPDM_CONNECTION_STATE_NEGOTIATED;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_PSK_CAP;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_ENCRYPT_CAP;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_MAC_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_PSK_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_ENCRYPT_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_MAC_CAP;
	read_responder_public_certificate_chain(m_use_hash_algo,
						m_use_asym_algo, &data,
						&data_size, &hash, &hash_size);
	spdm_reset_message_a(spdm_context);
	spdm_context->connection_info.algorithm.base_hash_algo =
		m_use_hash_algo;
	spdm_context->connection_info.algorithm.base_asym_algo =
		m_use_asym_algo;
	spdm_context->connection_info.algorithm.dhe_named_group =
		m_use_dhe_algo;
	spdm_context->connection_info.algorithm.aead_cipher_suite =
		m_use_aead_algo;
	spdm_context->connection_info.peer_used_cert_chain_buffer_size =
		data_size;
	copy_mem(spdm_context->connection_info.peer_used_cert_chain_buffer,
		 data, data_size);
	zero_mem(m_local_psk_hint, 32);
	copy_mem(&m_local_psk_hint[0], TEST_PSK_HINT_STRING,
		 sizeof(TEST_PSK_HINT_STRING));
	spdm_context->local_context.psk_hint_size =
		sizeof(TEST_PSK_HINT_STRING);
	spdm_context->local_context.psk_hint = m_local_psk_hint;

	session_id = 0xFFFFFFFF;
	session_info = &spdm_context->session_info[0];
	spdm_session_info_init(spdm_context, session_info, session_id, TRUE);
	spdm_secured_message_set_session_state(
		session_info->secured_message_context,
		SPDM_SESSION_STATE_HANDSHAKING);
	set_mem(m_dummy_key_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_key_size,
		(uint8)(0xFF));
	spdm_secured_message_set_response_handshake_encryption_key(
		session_info->secured_message_context, m_dummy_key_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_key_size);
	set_mem(m_dummy_salt_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_iv_size,
		(uint8)(0xFF));
	spdm_secured_message_set_response_handshake_salt(
		session_info->secured_message_context, m_dummy_salt_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_iv_size);
	((spdm_secured_message_context_t *)(session_info
						    ->secured_message_context))
		->handshake_secret.response_handshake_sequence_number = 0;
	spdm_secured_message_set_dummy_finished_key (session_info->secured_message_context);

	status = spdm_send_receive_psk_finish(spdm_context, session_id);
	assert_int_equal(status, RETURN_SUCCESS);
	assert_int_equal(
		spdm_secured_message_get_session_state(
			spdm_context->session_info[0].secured_message_context),
		SPDM_SESSION_STATE_ESTABLISHED);
	free(data);
}

/**
  Test 7: the requester is setup correctly, but receives an ERROR message
  indicating the RequestResynch status of the responder.
  Expected behavior: client returns a Status of RETURN_DEVICE_ERROR, and the 
  communication is reset to expect a new GET_VERSION message.
**/
void test_spdm_requester_psk_finish_case7(void **state)
{
	return_status status;
	spdm_test_context_t *spdm_test_context;
	spdm_context_t *spdm_context;
	uint32 session_id;
	void *data;
	uintn data_size;
	void *hash;
	uintn hash_size;
	spdm_session_info_t *session_info;

	spdm_test_context = *state;
	spdm_context = spdm_test_context->spdm_context;
	spdm_test_context->case_id = 0x7;
	spdm_context->connection_info.connection_state =
		SPDM_CONNECTION_STATE_NEGOTIATED;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_PSK_CAP;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_ENCRYPT_CAP;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_MAC_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_PSK_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_ENCRYPT_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_MAC_CAP;
	read_responder_public_certificate_chain(m_use_hash_algo,
						m_use_asym_algo, &data,
						&data_size, &hash, &hash_size);
	spdm_reset_message_a(spdm_context);
	spdm_context->connection_info.algorithm.base_hash_algo =
		m_use_hash_algo;
	spdm_context->connection_info.algorithm.base_asym_algo =
		m_use_asym_algo;
	spdm_context->connection_info.algorithm.dhe_named_group =
		m_use_dhe_algo;
	spdm_context->connection_info.algorithm.aead_cipher_suite =
		m_use_aead_algo;
	spdm_context->connection_info.peer_used_cert_chain_buffer_size =
		data_size;
	copy_mem(spdm_context->connection_info.peer_used_cert_chain_buffer,
		 data, data_size);
	zero_mem(m_local_psk_hint, 32);
	copy_mem(&m_local_psk_hint[0], TEST_PSK_HINT_STRING,
		 sizeof(TEST_PSK_HINT_STRING));
	spdm_context->local_context.psk_hint_size =
		sizeof(TEST_PSK_HINT_STRING);
	spdm_context->local_context.psk_hint = m_local_psk_hint;

	session_id = 0xFFFFFFFF;
	session_info = &spdm_context->session_info[0];
	spdm_session_info_init(spdm_context, session_info, session_id, TRUE);
	spdm_secured_message_set_session_state(
		session_info->secured_message_context,
		SPDM_SESSION_STATE_HANDSHAKING);
	set_mem(m_dummy_key_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_key_size,
		(uint8)(0xFF));
	spdm_secured_message_set_response_handshake_encryption_key(
		session_info->secured_message_context, m_dummy_key_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_key_size);
	set_mem(m_dummy_salt_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_iv_size,
		(uint8)(0xFF));
	spdm_secured_message_set_response_handshake_salt(
		session_info->secured_message_context, m_dummy_salt_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_iv_size);
	((spdm_secured_message_context_t *)(session_info
						    ->secured_message_context))
		->handshake_secret.response_handshake_sequence_number = 0;
	spdm_secured_message_set_dummy_finished_key (session_info->secured_message_context);

	status = spdm_send_receive_psk_finish(spdm_context, session_id);
	assert_int_equal(status, RETURN_DEVICE_ERROR);
	assert_int_equal(spdm_context->connection_info.connection_state,
			 SPDM_CONNECTION_STATE_NOT_STARTED);
	free(data);
}

/**
  Test 8: the requester is setup correctly, but receives an ERROR message
  indicating the ResponseNotReady status of the responder.
  Expected behavior: client returns a Status of RETURN_DEVICE_ERROR.
**/
void test_spdm_requester_psk_finish_case8(void **state)
{
	return_status status;
	spdm_test_context_t *spdm_test_context;
	spdm_context_t *spdm_context;
	uint32 session_id;
	void *data;
	uintn data_size;
	void *hash;
	uintn hash_size;
	spdm_session_info_t *session_info;

	spdm_test_context = *state;
	spdm_context = spdm_test_context->spdm_context;
	spdm_test_context->case_id = 0x8;
	spdm_context->connection_info.connection_state =
		SPDM_CONNECTION_STATE_NEGOTIATED;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_PSK_CAP;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_ENCRYPT_CAP;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_MAC_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_PSK_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_ENCRYPT_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_MAC_CAP;
	read_responder_public_certificate_chain(m_use_hash_algo,
						m_use_asym_algo, &data,
						&data_size, &hash, &hash_size);
	spdm_reset_message_a(spdm_context);
	spdm_context->connection_info.algorithm.base_hash_algo =
		m_use_hash_algo;
	spdm_context->connection_info.algorithm.base_asym_algo =
		m_use_asym_algo;
	spdm_context->connection_info.algorithm.dhe_named_group =
		m_use_dhe_algo;
	spdm_context->connection_info.algorithm.aead_cipher_suite =
		m_use_aead_algo;
	spdm_context->connection_info.peer_used_cert_chain_buffer_size =
		data_size;
	copy_mem(spdm_context->connection_info.peer_used_cert_chain_buffer,
		 data, data_size);
	zero_mem(m_local_psk_hint, 32);
	copy_mem(&m_local_psk_hint[0], TEST_PSK_HINT_STRING,
		 sizeof(TEST_PSK_HINT_STRING));
	spdm_context->local_context.psk_hint_size =
		sizeof(TEST_PSK_HINT_STRING);
	spdm_context->local_context.psk_hint = m_local_psk_hint;

	session_id = 0xFFFFFFFF;
	session_info = &spdm_context->session_info[0];
	spdm_session_info_init(spdm_context, session_info, session_id, TRUE);
	spdm_secured_message_set_session_state(
		session_info->secured_message_context,
		SPDM_SESSION_STATE_HANDSHAKING);
	set_mem(m_dummy_key_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_key_size,
		(uint8)(0xFF));
	spdm_secured_message_set_response_handshake_encryption_key(
		session_info->secured_message_context, m_dummy_key_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_key_size);
	set_mem(m_dummy_salt_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_iv_size,
		(uint8)(0xFF));
	spdm_secured_message_set_response_handshake_salt(
		session_info->secured_message_context, m_dummy_salt_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_iv_size);
	((spdm_secured_message_context_t *)(session_info
						    ->secured_message_context))
		->handshake_secret.response_handshake_sequence_number = 0;
	spdm_secured_message_set_dummy_finished_key (session_info->secured_message_context);

	status = spdm_send_receive_psk_finish(spdm_context, session_id);
	assert_int_equal(status, RETURN_DEVICE_ERROR);
	free(data);
}

/**
  Test 9: the requester is setup correctly, but, on the first try, receiving
  a ResponseNotReady ERROR message, and, on retry, receiving a correct
  PSK_FINISH_RSP message.
  Expected behavior: client returns a Status of RETURN_SUCCESS and session
  is established.
**/
void test_spdm_requester_psk_finish_case9(void **state)
{
	return_status status;
	spdm_test_context_t *spdm_test_context;
	spdm_context_t *spdm_context;
	uint32 session_id;
	void *data;
	uintn data_size;
	void *hash;
	uintn hash_size;
	spdm_session_info_t *session_info;

	spdm_test_context = *state;
	spdm_context = spdm_test_context->spdm_context;
	spdm_test_context->case_id = 0x9;
	spdm_context->connection_info.connection_state =
		SPDM_CONNECTION_STATE_NEGOTIATED;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_PSK_CAP;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_ENCRYPT_CAP;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_MAC_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_PSK_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_ENCRYPT_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_MAC_CAP;
	read_responder_public_certificate_chain(m_use_hash_algo,
						m_use_asym_algo, &data,
						&data_size, &hash, &hash_size);
	spdm_reset_message_a(spdm_context);
	spdm_context->connection_info.algorithm.base_hash_algo =
		m_use_hash_algo;
	spdm_context->connection_info.algorithm.base_asym_algo =
		m_use_asym_algo;
	spdm_context->connection_info.algorithm.dhe_named_group =
		m_use_dhe_algo;
	spdm_context->connection_info.algorithm.aead_cipher_suite =
		m_use_aead_algo;
	spdm_context->connection_info.peer_used_cert_chain_buffer_size =
		data_size;
	copy_mem(spdm_context->connection_info.peer_used_cert_chain_buffer,
		 data, data_size);
	zero_mem(m_local_psk_hint, 32);
	copy_mem(&m_local_psk_hint[0], TEST_PSK_HINT_STRING,
		 sizeof(TEST_PSK_HINT_STRING));
	spdm_context->local_context.psk_hint_size =
		sizeof(TEST_PSK_HINT_STRING);
	spdm_context->local_context.psk_hint = m_local_psk_hint;

	session_id = 0xFFFFFFFF;
	session_info = &spdm_context->session_info[0];
	spdm_session_info_init(spdm_context, session_info, session_id, TRUE);
	spdm_secured_message_set_session_state(
		session_info->secured_message_context,
		SPDM_SESSION_STATE_HANDSHAKING);
	set_mem(m_dummy_key_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_key_size,
		(uint8)(0xFF));
	spdm_secured_message_set_response_handshake_encryption_key(
		session_info->secured_message_context, m_dummy_key_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_key_size);
	set_mem(m_dummy_salt_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_iv_size,
		(uint8)(0xFF));
	spdm_secured_message_set_response_handshake_salt(
		session_info->secured_message_context, m_dummy_salt_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_iv_size);
	((spdm_secured_message_context_t *)(session_info
						    ->secured_message_context))
		->handshake_secret.response_handshake_sequence_number = 0;
	spdm_secured_message_set_dummy_finished_key (session_info->secured_message_context);

	status = spdm_send_receive_psk_finish(spdm_context, session_id);
	assert_int_equal(status, RETURN_SUCCESS);
	assert_int_equal(
		spdm_secured_message_get_session_state(
			spdm_context->session_info[0].secured_message_context),
		SPDM_SESSION_STATE_ESTABLISHED);
	free(data);
}

/**
  Test 10: receiving an unexpected ERROR message from the responder.
  There are tests for all named codes, including some reserved ones
  (namely, 0x00, 0x0b, 0x0c, 0x3f, 0xfd, 0xfe).
  However, for having specific test cases, it is excluded from this case:
  Busy (0x03), ResponseNotReady (0x42), and RequestResync (0x43).
  Expected behavior: client returns a status of RETURN_DEVICE_ERROR.
**/
void test_spdm_requester_psk_finish_case10(void **state) {
  return_status        status;
  spdm_test_context_t    *spdm_test_context;
  spdm_context_t  *spdm_context;
  uint32               session_id;
  void                 *data;
  uintn                data_size;
  void                 *hash;
  uintn                hash_size;
  spdm_session_info_t    *session_info;
  uint16               error_code;

  spdm_test_context = *state;
  spdm_context = spdm_test_context->spdm_context;
  spdm_test_context->case_id = 0xA;
  spdm_context->connection_info.capability.flags |= SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_PSK_CAP;
  spdm_context->connection_info.capability.flags |= SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_ENCRYPT_CAP;
  spdm_context->connection_info.capability.flags |= SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_MAC_CAP;
  spdm_context->local_context.capability.flags |= SPDM_GET_CAPABILITIES_REQUEST_FLAGS_PSK_CAP;
  spdm_context->local_context.capability.flags |= SPDM_GET_CAPABILITIES_REQUEST_FLAGS_ENCRYPT_CAP;
  spdm_context->local_context.capability.flags |= SPDM_GET_CAPABILITIES_REQUEST_FLAGS_MAC_CAP;
  read_responder_public_certificate_chain (m_use_hash_algo, m_use_asym_algo, &data, &data_size, &hash, &hash_size);
  spdm_context->connection_info.algorithm.base_hash_algo = m_use_hash_algo;
  spdm_context->connection_info.algorithm.base_asym_algo = m_use_asym_algo;
  spdm_context->connection_info.algorithm.dhe_named_group = m_use_dhe_algo; 
  spdm_context->connection_info.algorithm.aead_cipher_suite = m_use_aead_algo;
  spdm_context->connection_info.peer_used_cert_chain_buffer_size = data_size;
  copy_mem (spdm_context->connection_info.peer_used_cert_chain_buffer, data, data_size);
  zero_mem (m_local_psk_hint, 32);
  copy_mem (&m_local_psk_hint[0], TEST_PSK_HINT_STRING, sizeof(TEST_PSK_HINT_STRING));
  spdm_context->local_context.psk_hint_size = sizeof(TEST_PSK_HINT_STRING);
  spdm_context->local_context.psk_hint = m_local_psk_hint;

  error_code = SPDM_ERROR_CODE_RESERVED_00;
  while(error_code <= 0xff) {
    spdm_context->connection_info.connection_state = SPDM_CONNECTION_STATE_NEGOTIATED;
	spdm_reset_message_a(spdm_context);

    session_id = 0xFFFFFFFF;
    session_info = &spdm_context->session_info[0];
    spdm_session_info_init (spdm_context, session_info, session_id, TRUE);
    spdm_secured_message_set_session_state (session_info->secured_message_context, SPDM_SESSION_STATE_HANDSHAKING);  
    set_mem (m_dummy_key_buffer, ((spdm_secured_message_context_t*)(session_info->secured_message_context))->aead_key_size, (uint8)(0xFF));
    spdm_secured_message_set_response_handshake_encryption_key (session_info->secured_message_context, m_dummy_key_buffer, ((spdm_secured_message_context_t*)(session_info->secured_message_context))->aead_key_size);
    set_mem (m_dummy_salt_buffer, ((spdm_secured_message_context_t*)(session_info->secured_message_context))->aead_iv_size, (uint8)(0xFF));
    spdm_secured_message_set_response_handshake_salt (session_info->secured_message_context, m_dummy_salt_buffer, ((spdm_secured_message_context_t*)(session_info->secured_message_context))->aead_iv_size);
    ((spdm_secured_message_context_t*)(session_info->secured_message_context))->handshake_secret.response_handshake_sequence_number = 0;
	spdm_secured_message_set_dummy_finished_key (session_info->secured_message_context);

    status = spdm_send_receive_psk_finish (spdm_context, session_id); 
    // assert_int_equal (status, RETURN_DEVICE_ERROR);
    ASSERT_INT_EQUAL_CASE (status, RETURN_DEVICE_ERROR, error_code);

    error_code++;
    if(error_code == SPDM_ERROR_CODE_BUSY) { //busy is treated in cases 5 and 6
      error_code = SPDM_ERROR_CODE_UNEXPECTED_REQUEST;
    }
    if(error_code == SPDM_ERROR_CODE_RESERVED_0D) { //skip some reserved error codes (0d to 3e)
      error_code = SPDM_ERROR_CODE_RESERVED_3F;
    }
    if(error_code == SPDM_ERROR_CODE_RESPONSE_NOT_READY) { //skip response not ready, request resync, and some reserved codes (44 to fc)
      error_code = SPDM_ERROR_CODE_RESERVED_FD;
    }
  }

  free(data);
}

void test_spdm_requester_psk_finish_case11(void **state)
{
	return_status status;
	spdm_test_context_t *spdm_test_context;
	spdm_context_t *spdm_context;
	uint32 session_id;
	void *data;
	uintn data_size;
	void *hash;
	uintn hash_size;
	spdm_session_info_t *session_info;

	spdm_test_context = *state;
	spdm_context = spdm_test_context->spdm_context;
	spdm_test_context->case_id = 0xb;
	spdm_context->connection_info.connection_state =
		SPDM_CONNECTION_STATE_NEGOTIATED;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_PSK_CAP;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_ENCRYPT_CAP;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_MAC_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_PSK_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_ENCRYPT_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_MAC_CAP;
	read_responder_public_certificate_chain(m_use_hash_algo,
						m_use_asym_algo, &data,
						&data_size, &hash, &hash_size);
	spdm_reset_message_a(spdm_context);

	spdm_context->connection_info.algorithm.base_hash_algo =
		m_use_hash_algo;
	spdm_context->connection_info.algorithm.base_asym_algo =
		m_use_asym_algo;
	spdm_context->connection_info.algorithm.dhe_named_group =
		m_use_dhe_algo;
	spdm_context->connection_info.algorithm.aead_cipher_suite =
		m_use_aead_algo;
	spdm_context->connection_info.peer_used_cert_chain_buffer_size =
		data_size;
	copy_mem(spdm_context->connection_info.peer_used_cert_chain_buffer,
		 data, data_size);
	zero_mem(m_local_psk_hint, 32);
	copy_mem(&m_local_psk_hint[0], TEST_PSK_HINT_STRING,
		 sizeof(TEST_PSK_HINT_STRING));
	spdm_context->local_context.psk_hint_size =
		sizeof(TEST_PSK_HINT_STRING);
	spdm_context->local_context.psk_hint = m_local_psk_hint;

	session_id = 0xFFFFFFFF;
	session_info = &spdm_context->session_info[0];
	spdm_session_info_init(spdm_context, session_info, session_id, TRUE);
	spdm_secured_message_set_session_state(
		session_info->secured_message_context,
		SPDM_SESSION_STATE_HANDSHAKING);
	set_mem(m_dummy_key_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_key_size,
		(uint8)(0xFF));
	spdm_secured_message_set_response_handshake_encryption_key(
		session_info->secured_message_context, m_dummy_key_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_key_size);
	set_mem(m_dummy_salt_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_iv_size,
		(uint8)(0xFF));
	spdm_secured_message_set_response_handshake_salt(
		session_info->secured_message_context, m_dummy_salt_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_iv_size);
	((spdm_secured_message_context_t *)(session_info
						    ->secured_message_context))
		->handshake_secret.response_handshake_sequence_number = 0;
	spdm_secured_message_set_dummy_finished_key (session_info->secured_message_context);

#if LIBSPDM_RECORD_TRANSCRIPT_DATA_SUPPORT
	session_info->session_transcript.message_m.buffer_size =
							session_info->session_transcript.message_m.max_buffer_size;
	spdm_context->transcript.message_b.buffer_size =
							spdm_context->transcript.message_b.max_buffer_size;
	spdm_context->transcript.message_c.buffer_size =
							spdm_context->transcript.message_c.max_buffer_size;
	spdm_context->transcript.message_mut_b.buffer_size =
							spdm_context->transcript.message_mut_b.max_buffer_size;
	spdm_context->transcript.message_mut_c.buffer_size =
							spdm_context->transcript.message_mut_c.max_buffer_size;
#endif

	status = spdm_send_receive_psk_finish(spdm_context, session_id);
	assert_int_equal(status, RETURN_SUCCESS);
	assert_int_equal(
		spdm_secured_message_get_session_state(
			spdm_context->session_info[0].secured_message_context),
		SPDM_SESSION_STATE_ESTABLISHED);
#if LIBSPDM_RECORD_TRANSCRIPT_DATA_SUPPORT
	assert_int_equal(session_info->session_transcript.message_m.buffer_size, 0);
	assert_int_equal(spdm_context->transcript.message_b.buffer_size, 0);
	assert_int_equal(spdm_context->transcript.message_c.buffer_size, 0);
	assert_int_equal(spdm_context->transcript.message_mut_b.buffer_size, 0);
	assert_int_equal(spdm_context->transcript.message_mut_c.buffer_size, 0);
#endif
	free(data);
}

/**
  Test 12: requester is not setup correctly to support pre-shared keys
  (no capabilities). The responder would attempt to return a correct
  PSK_FINISH_RSP message.
  Expected behavior: client returns a Status of RETURN_UNSUPPORTED.
**/
void test_spdm_requester_psk_finish_case12(void **state)
{
	return_status status;
	spdm_test_context_t *spdm_test_context;
	spdm_context_t *spdm_context;
	uint32 session_id;
	void *data;
	uintn data_size;
	void *hash;
	uintn hash_size;
	spdm_session_info_t *session_info;

	spdm_test_context = *state;
	spdm_context = spdm_test_context->spdm_context;
	spdm_test_context->case_id = 0xC;
	spdm_context->connection_info.connection_state =
		SPDM_CONNECTION_STATE_NEGOTIATED;
	//no PSK capabilities
	spdm_context->connection_info.capability.flags &=
		~(SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_PSK_CAP);
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_ENCRYPT_CAP;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_MAC_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_PSK_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_ENCRYPT_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_MAC_CAP;
	read_responder_public_certificate_chain(m_use_hash_algo,
						m_use_asym_algo, &data,
						&data_size, &hash, &hash_size);
	spdm_context->transcript.message_a.buffer_size = 0;
	spdm_context->connection_info.algorithm.base_hash_algo =
		m_use_hash_algo;
	spdm_context->connection_info.algorithm.base_asym_algo =
		m_use_asym_algo;
	spdm_context->connection_info.algorithm.dhe_named_group =
		m_use_dhe_algo;
	spdm_context->connection_info.algorithm.aead_cipher_suite =
		m_use_aead_algo;
	spdm_context->connection_info.peer_used_cert_chain_buffer_size =
		data_size;
	copy_mem(spdm_context->connection_info.peer_used_cert_chain_buffer,
		 data, data_size);
	zero_mem(m_local_psk_hint, 32);
	copy_mem(&m_local_psk_hint[0], TEST_PSK_HINT_STRING,
		 sizeof(TEST_PSK_HINT_STRING));
	spdm_context->local_context.psk_hint_size =
		sizeof(TEST_PSK_HINT_STRING);
	spdm_context->local_context.psk_hint = m_local_psk_hint;

	session_id = 0xFFFFFFFF;
	session_info = &spdm_context->session_info[0];
	spdm_session_info_init(spdm_context, session_info, session_id, TRUE);
	spdm_secured_message_set_session_state(
		session_info->secured_message_context,
		SPDM_SESSION_STATE_HANDSHAKING);
	set_mem(m_dummy_key_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_key_size,
		(uint8)(0xFF));
	spdm_secured_message_set_response_handshake_encryption_key(
		session_info->secured_message_context, m_dummy_key_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_key_size);
	set_mem(m_dummy_salt_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_iv_size,
		(uint8)(0xFF));
	spdm_secured_message_set_response_handshake_salt(
		session_info->secured_message_context, m_dummy_salt_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_iv_size);
	((spdm_secured_message_context_t *)(session_info
						    ->secured_message_context))
		->handshake_secret.response_handshake_sequence_number = 0;
	spdm_secured_message_set_dummy_finished_key (session_info->secured_message_context);

	status = spdm_send_receive_psk_finish(spdm_context, session_id);
	assert_int_equal(status, RETURN_UNSUPPORTED);
	free(data);
}

/**
  Test 13: receiving an incorrect FINISH_RSP message, with wrong response
  code, but all other field correct.
  Expected behavior: client returns a Status of RETURN_DEVICE_ERROR.
**/
void test_spdm_requester_psk_finish_case13(void **state)
{
	return_status status;
	spdm_test_context_t *spdm_test_context;
	spdm_context_t *spdm_context;
	uint32 session_id;
	void *data;
	uintn data_size;
	void *hash;
	uintn hash_size;
	spdm_session_info_t *session_info;

	spdm_test_context = *state;
	spdm_context = spdm_test_context->spdm_context;
	spdm_test_context->case_id = 0xD;
	spdm_context->connection_info.connection_state =
		SPDM_CONNECTION_STATE_NEGOTIATED;
	//no PSK capabilities
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_PSK_CAP;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_ENCRYPT_CAP;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_MAC_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_PSK_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_ENCRYPT_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_MAC_CAP;
	read_responder_public_certificate_chain(m_use_hash_algo,
						m_use_asym_algo, &data,
						&data_size, &hash, &hash_size);
	spdm_context->transcript.message_a.buffer_size = 0;
	spdm_context->connection_info.algorithm.base_hash_algo =
		m_use_hash_algo;
	spdm_context->connection_info.algorithm.base_asym_algo =
		m_use_asym_algo;
	spdm_context->connection_info.algorithm.dhe_named_group =
		m_use_dhe_algo;
	spdm_context->connection_info.algorithm.aead_cipher_suite =
		m_use_aead_algo;
	spdm_context->connection_info.peer_used_cert_chain_buffer_size =
		data_size;
	copy_mem(spdm_context->connection_info.peer_used_cert_chain_buffer,
		 data, data_size);
	zero_mem(m_local_psk_hint, 32);
	copy_mem(&m_local_psk_hint[0], TEST_PSK_HINT_STRING,
		 sizeof(TEST_PSK_HINT_STRING));
	spdm_context->local_context.psk_hint_size =
		sizeof(TEST_PSK_HINT_STRING);
	spdm_context->local_context.psk_hint = m_local_psk_hint;

	session_id = 0xFFFFFFFF;
	session_info = &spdm_context->session_info[0];
	spdm_session_info_init(spdm_context, session_info, session_id, TRUE);
	spdm_secured_message_set_session_state(
		session_info->secured_message_context,
		SPDM_SESSION_STATE_HANDSHAKING);
	set_mem(m_dummy_key_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_key_size,
		(uint8)(0xFF));
	spdm_secured_message_set_response_handshake_encryption_key(
		session_info->secured_message_context, m_dummy_key_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_key_size);
	set_mem(m_dummy_salt_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_iv_size,
		(uint8)(0xFF));
	spdm_secured_message_set_response_handshake_salt(
		session_info->secured_message_context, m_dummy_salt_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_iv_size);
	((spdm_secured_message_context_t *)(session_info
						    ->secured_message_context))
		->handshake_secret.response_handshake_sequence_number = 0;
	spdm_secured_message_set_dummy_finished_key (session_info->secured_message_context);

	status = spdm_send_receive_psk_finish(spdm_context, session_id);
	assert_int_equal(status, RETURN_DEVICE_ERROR);
	free(data);
}

/**
  Test 14: requester is not setup correctly by not initializing a
  session during PSK_EXCHANGE. The responder would attempt to 
  return a correct PSK_FINISH_RSP message.
  Expected behavior: client returns a Status of RETURN_UNSUPPORTED.
**/
void test_spdm_requester_psk_finish_case14(void **state)
{
	return_status status;
	spdm_test_context_t *spdm_test_context;
	spdm_context_t *spdm_context;
	uint32 session_id;
	void *data;
	uintn data_size;
	void *hash;
	uintn hash_size;
	spdm_session_info_t *session_info;

	spdm_test_context = *state;
	spdm_context = spdm_test_context->spdm_context;
	spdm_test_context->case_id = 0xE;
	spdm_context->connection_info.connection_state =
		SPDM_CONNECTION_STATE_NEGOTIATED;
	//no PSK capabilities
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_PSK_CAP;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_ENCRYPT_CAP;
	spdm_context->connection_info.capability.flags |=
		SPDM_GET_CAPABILITIES_RESPONSE_FLAGS_MAC_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_PSK_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_ENCRYPT_CAP;
	spdm_context->local_context.capability.flags |=
		SPDM_GET_CAPABILITIES_REQUEST_FLAGS_MAC_CAP;
	read_responder_public_certificate_chain(m_use_hash_algo,
						m_use_asym_algo, &data,
						&data_size, &hash, &hash_size);
	spdm_context->transcript.message_a.buffer_size = 0;
	spdm_context->connection_info.algorithm.base_hash_algo =
		m_use_hash_algo;
	spdm_context->connection_info.algorithm.base_asym_algo =
		m_use_asym_algo;
	spdm_context->connection_info.algorithm.dhe_named_group =
		m_use_dhe_algo;
	spdm_context->connection_info.algorithm.aead_cipher_suite =
		m_use_aead_algo;
	spdm_context->connection_info.peer_used_cert_chain_buffer_size =
		data_size;
	copy_mem(spdm_context->connection_info.peer_used_cert_chain_buffer,
		 data, data_size);
	zero_mem(m_local_psk_hint, 32);
	copy_mem(&m_local_psk_hint[0], TEST_PSK_HINT_STRING,
		 sizeof(TEST_PSK_HINT_STRING));
	spdm_context->local_context.psk_hint_size =
		sizeof(TEST_PSK_HINT_STRING);
	spdm_context->local_context.psk_hint = m_local_psk_hint;

	session_id = 0xFFFFFFFF;
	session_info = &spdm_context->session_info[0];
	spdm_session_info_init(spdm_context, session_info, session_id, TRUE);
	spdm_secured_message_set_session_state(
		session_info->secured_message_context,
		SPDM_SESSION_STATE_NOT_STARTED);
	set_mem(m_dummy_key_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_key_size,
		(uint8)(0xFF));
	spdm_secured_message_set_response_handshake_encryption_key(
		session_info->secured_message_context, m_dummy_key_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_key_size);
	set_mem(m_dummy_salt_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_iv_size,
		(uint8)(0xFF));
	spdm_secured_message_set_response_handshake_salt(
		session_info->secured_message_context, m_dummy_salt_buffer,
		((spdm_secured_message_context_t
			  *)(session_info->secured_message_context))
			->aead_iv_size);
	((spdm_secured_message_context_t *)(session_info
						    ->secured_message_context))
		->handshake_secret.response_handshake_sequence_number = 0;
	spdm_secured_message_set_dummy_finished_key (session_info->secured_message_context);

	status = spdm_send_receive_psk_finish(spdm_context, session_id);
	assert_int_equal(status, RETURN_UNSUPPORTED);
	free(data);
}

spdm_test_context_t m_spdm_requester_psk_finish_test_context = {
	SPDM_TEST_CONTEXT_SIGNATURE,
	TRUE,
	spdm_requester_psk_finish_test_send_message,
	spdm_requester_psk_finish_test_receive_message,
};

int spdm_requester_psk_finish_test_main(void)
{
	const struct CMUnitTest spdm_requester_psk_finish_tests[] = {
		// SendRequest failed
		cmocka_unit_test(test_spdm_requester_psk_finish_case1),
		// Successful response
		cmocka_unit_test(test_spdm_requester_psk_finish_case2),
		// connection_state check failed
		cmocka_unit_test(test_spdm_requester_psk_finish_case3),
		// Error response: SPDM_ERROR_CODE_INVALID_REQUEST
		cmocka_unit_test(test_spdm_requester_psk_finish_case4),
		// Always SPDM_ERROR_CODE_BUSY
		cmocka_unit_test(test_spdm_requester_psk_finish_case5),
		// SPDM_ERROR_CODE_BUSY + Successful response
		cmocka_unit_test(test_spdm_requester_psk_finish_case6),
		// Error response: SPDM_ERROR_CODE_REQUEST_RESYNCH
		cmocka_unit_test(test_spdm_requester_psk_finish_case7),
		// Always SPDM_ERROR_CODE_RESPONSE_NOT_READY
		cmocka_unit_test(test_spdm_requester_psk_finish_case8),
		// SPDM_ERROR_CODE_RESPONSE_NOT_READY + Successful response
		cmocka_unit_test(test_spdm_requester_psk_finish_case9),
		// Unexpected errors
		cmocka_unit_test(test_spdm_requester_psk_finish_case10),
		// Buffer reset
		cmocka_unit_test(test_spdm_requester_psk_finish_case11),
		// No correct setup
		cmocka_unit_test(test_spdm_requester_psk_finish_case12),
		// Wrong response code
		cmocka_unit_test(test_spdm_requester_psk_finish_case13),
		// Uninitialized session
		cmocka_unit_test(test_spdm_requester_psk_finish_case14),
	};

	setup_spdm_test_context(&m_spdm_requester_psk_finish_test_context);

	return cmocka_run_group_tests(spdm_requester_psk_finish_tests,
				      spdm_unit_test_group_setup,
				      spdm_unit_test_group_teardown);
}
