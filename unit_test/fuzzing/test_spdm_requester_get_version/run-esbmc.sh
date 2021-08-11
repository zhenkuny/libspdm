
LIBSPDM="$(cd "$( dirname "${BASH_SOURCE[0]}" )"/../../.. &> /dev/null && pwd)"

esbmc \
 --force-malloc-success \
 --compact-trace \
 --memory-leak-check \
 --overflow-check \
 --k-step 7 --unlimited-k-steps \
 --k-induction --max-inductive-step 3 \
 --no-library \
  $LIBSPDM/unit_test/fuzzing/test_spdm_requester_get_version/main.c \
  $LIBSPDM/unit_test/fuzzing/test_spdm_requester_get_version/get_version.c \
  $LIBSPDM/library/spdm_requester_lib/get_version.c \
  $LIBSPDM/os_stub/memlib/zero_mem.c \
  $LIBSPDM/unit_test/fuzzing/spdm_unit_fuzzing_common/common.c \
  $LIBSPDM/library/spdm_common_lib/context_data.c \
  $LIBSPDM/library/spdm_secured_message_lib/context_data.c \
  -I $LIBSPDM/unit_test/fuzzing/spdm_unit_fuzzing_common \
  -I $LIBSPDM/include/hal/ \
  -I $LIBSPDM/include/hal/x64 \
  -I $LIBSPDM/include \
  -I $LIBSPDM/unit_test/include \
  -I $LIBSPDM/library/spdm_common_lib \
  -I $LIBSPDM/library/spdm_requester_lib \
  
