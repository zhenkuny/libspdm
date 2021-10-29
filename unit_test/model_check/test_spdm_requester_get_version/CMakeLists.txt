cmake_minimum_required(VERSION 2.6)
INCLUDE_DIRECTORIES(${LIBSPDM_DIR}/unit_test/model_check/test_spdm_requester_get_version
                    ${LIBSPDM_DIR}/include
                    ${LIBSPDM_DIR}/include/hal
                    ${LIBSPDM_DIR}/include/hal/${ARCH}
                    ${LIBSPDM_DIR}/library/spdm_common_lib
                    ${LIBSPDM_DIR}/library/spdm_requester_lib
                    ${LIBSPDM_DIR}/library/spdm_secured_message_lib
                    ${LIBSPDM_DIR}/unit_test/include
)
SET(src_test_spdm_requester_get_version
    get_version.c
)
SET(test_spdm_requester_get_version_LIBRARY
    memlib
    debuglib
    spdm_requester_lib
    spdm_common_lib
    ${CRYPTO_LIB_PATHS}
    rnglib
    cryptlib_${CRYPTO}
    malloclib
    spdm_crypt_lib
    spdm_secured_message_lib
    spdm_transport_test_lib
    spdm_device_secret_lib_null
)
ADD_EXECUTABLE(mc_test_spdm_requester_get_version ${src_test_spdm_requester_get_version})
TARGET_LINK_LIBRARIES(mc_test_spdm_requester_get_version ${test_spdm_requester_get_version_LIBRARY})
