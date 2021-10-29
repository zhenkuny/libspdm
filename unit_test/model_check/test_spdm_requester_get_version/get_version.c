#include <base.h>
#include <library/memlib.h>
#include <library/spdm_requester_lib.h>
#include <library/spdm_responder_lib.h>
#include <library/spdm_transport_test_lib.h>
#include <spdm_requester_lib_internal.h>
#include <spdm_common_lib_internal.h>
#include <library/spdm_secured_message_lib.h>
#include <spdm_secured_message_lib_internal.h>

#pragma pack(1)
typedef struct {
	spdm_message_header_t header;
	uint8 reserved;
	uint8 version_number_entry_count;
	spdm_version_number_t version_number_entry[MAX_SPDM_VERSION_COUNT];
} spdm_version_response_mine_t;
#pragma pack()

return_status spdm_device_send_message(IN void *spdm_context,
				       IN uintn request_size, IN void *request,
				       IN uint64 timeout)
{
	return RETURN_SUCCESS;
}

return_status spdm_device_receive_message(IN void *spdm_context,
					  IN OUT uintn *response_size,
					  IN OUT void *response,
					  IN uint64 timeout)
{
		spdm_version_response_mine_t spdm_response;

		zero_mem(&spdm_response, sizeof(spdm_response));
		spdm_response.header.spdm_version = SPDM_MESSAGE_VERSION_10;
		spdm_response.header.request_response_code = SPDM_VERSION;
		spdm_response.header.param1 = 0;
		spdm_response.header.param2 = 0;
		spdm_response.version_number_entry_count = 2;
		spdm_response.version_number_entry[0].major_version = 1;
		spdm_response.version_number_entry[0].minor_version = 0;
		spdm_response.version_number_entry[1].major_version = 1;
		spdm_response.version_number_entry[1].minor_version = 1;

		spdm_transport_test_encode_message(spdm_context, NULL, FALSE,
						   FALSE, sizeof(spdm_response),
						   &spdm_response,
						   response_size, response);
	return RETURN_SUCCESS;
}

#define SPDM_CONTEXT_SIZE (sizeof(spdm_context_t) + (sizeof(spdm_secured_message_context_t) * MAX_SPDM_SESSION_COUNT))
unsigned char m_spdm_context_payload[SPDM_CONTEXT_SIZE];

int main()
{
	void *spdm_context = (void *)m_spdm_context_payload;
  spdm_init_context(spdm_context);
	spdm_register_device_io_func(spdm_context, spdm_device_send_message, spdm_device_receive_message);
  spdm_register_transport_layer_func(spdm_context, spdm_transport_test_encode_message, spdm_transport_test_decode_message);
	spdm_get_version(spdm_context);
  return 0;
}