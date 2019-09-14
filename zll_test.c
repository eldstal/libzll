#include "zll_test.h"

#include <string.h>




int zll_test_key_exchange(void) {
  // Test case outlined in the ZLL standards document
  uint32_t trans_id = 0x3EAA2009;
  uint32_t resp_id = 0x88762fb1;

  uint8_t cert_key[16] = { 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7,
                           0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf };

  uint8_t network_key[16] = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
                              0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00 };

  // Expected values
  uint8_t t_transport_key[16] = { 0x66, 0x9e, 0x08, 0xe4, 0x02, 0x77, 0xed, 0x9a,
                                  0xb3, 0x6b, 0x25, 0x80, 0x45, 0x6b, 0x41, 0x76 };

  uint8_t t_enc_network_key[16] = { 0x83, 0x22, 0x63, 0x68, 0x73, 0xa7, 0xbb, 0x2a,
                                    0x18, 0x9a, 0x53, 0x70, 0x8c, 0x60, 0x7b, 0xd0 };

  uint8_t transport_key[16];
  uint8_t enc_network_key[16];
  uint8_t dec_network_key[16];

  zll_transport_key(transport_key, trans_id, resp_id, cert_key);
  if (memcmp(transport_key, t_transport_key, 16)) {
    ZLL_PRINTF("Test failed: transport key\n");
    return 1;
  }

  zll_encrypt_network_key(enc_network_key, network_key, t_transport_key);
  if (memcmp(enc_network_key, t_enc_network_key, 16)) {
    ZLL_PRINTF("Test failed: network key encryption\n");
    return 1;
  }

  zll_decrypt_network_key(dec_network_key, enc_network_key, t_transport_key);
if (memcmp(dec_network_key, network_key, 16)) {
    ZLL_PRINTF("Test failed: network key decryption\n");
    return 1;
  }


  return 0;
}



int zll_test_run(void) {

  if (zll_test_key_exchange()) {
    return 1;
  }

  ZLL_PRINTF("Tests passed!\n");
  return 0;
}