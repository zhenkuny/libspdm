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


// -Dmemcpy=optimized_memcpy
boolean esmbc_random_seed(const uint8 *seed OPTIONAL, uintn seed_size) {}

boolean is_member(spdm_version_number_t *ver_set, uintn ver_num, spdm_version_number_t ver) {
  for (int i=0; i<ver_num; i++) {
    if ((uint16)ver_set[i] == (uint16)ver)
      return TRUE;
  }
  return FALSE;
}
void test_spdm_version_number_sort(IN OUT spdm_version_number_t *ver_set, IN uintn ver_num) {
  const int ver_num = 5;
  spdm_version_number_t ver_set[ver_num] = __ESBMC_alloca(sizeof(spdm_version_number_t) * ver_num);
  for (int i=1; i<ver_num; i++) {
    __ESBMC_assert(spdm_version_number_compare(ver_set[i-1], ver_set[i]));
  }
}

void test_spdm_negotiate_connection_version() {
  const uintn req_ver_num = 5;
  const uintn res_ver_num = 6;
  spdm_context_t *context = __ESBMC_alloca(sizeof(spdm_context_t));
  spdm_version_number_t *req_ver_set = __ESBMC_alloca(sizeof(spdm_version_number_t) * req_ver_num);
  spdm_version_number_t *res_ver_set = __ESBMC_alloca(sizeof(spdm_version_number_t) * res_ver_num);

  boolean ret = spdm_negotiate_connection_version(context, req_ver_set, req_ver_num, res_ver_set, res_ver_num);
  spdm_version_number_t ver = context->connection_info.version;

  // ver must be in both req_ver_set and res_ver_set
  __ESBMC_assert(is_member(req_ver_set, req_ver_num, ver));
  __ESBMC_assert(is_member(res_ver_set, res_ver_num, ver));

  // any version in req_ver_set is higher than ver must not in res_ver_set
  for (int i=1; i<req_ver_num; i++) {
    if (spdm_version_number_compare(req_ver_set[i], ver))
      __ESBMC_assert(!is_member(res_ver_set, res_ver_num, req_ver_set[i]));
  }

  // any version in res_ver_set is higher than ver must not in req_ver_set
  for (int i=1; i<res_ver_num; i++) {
    if (spdm_version_number_compare(res_ver_set[i], ver))
      __ESBMC_assert(!is_member(req_ver_set, req_ver_num, req_ver_set[i]));
  }
}


int main()
{
  void *spdm_context = (void *)m_spdm_context_payload;
  spdm_init_context(spdm_context);
  spdm_register_device_io_func(spdm_context, spdm_device_send_message, spdm_device_receive_message);
  spdm_register_transport_layer_func(spdm_context, spdm_transport_test_encode_message, spdm_transport_test_decode_message);
  spdm_get_version(spdm_context);
  return 0;
}
