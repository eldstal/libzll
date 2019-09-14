#include "zll_key_exchange.h"
#include "zll_aes.h"

#include <string.h>


static void aes_encrypt(uint8_t cryptext[16], uint8_t plaintext[16], uint8_t key[16]) {
  memcpy(cryptext, plaintext, 16);

  struct AES_ctx ctx;
  AES_init_ctx(&ctx, key);
  AES_ECB_encrypt(&ctx, cryptext);
}


static void aes_decrypt(uint8_t plaintext[16], uint8_t cryptext[16], uint8_t key[16]) {
  memcpy(plaintext, cryptext, 16);

  struct AES_ctx ctx;
  AES_init_ctx(&ctx, key);
  AES_ECB_decrypt(&ctx, plaintext);
}





void zll_transport_key(uint8_t transport_key[16], uint32_t trans_id, uint32_t resp_id, uint8_t master_key[16]) {
  // Concatenate trans_id and resp_id into a 128-bit number
  union {
    uint32_t words[4];
    uint8_t bytes[16];
  } cat;
  cat.words[0] = trans_id;
  cat.words[1] = trans_id;
  cat.words[2] = resp_id;
  cat.words[3] = resp_id;

  aes_encrypt(transport_key, cat.bytes, master_key);
}

void zll_encrypt_network_key(uint8_t cryptext[16], uint8_t network_key[16], uint8_t transport_key[16]) {
  aes_encrypt(cryptext, network_key, transport_key);
}

void zll_decrypt_network_key(uint8_t network_key[16], uint8_t cryptext[16], uint8_t transport_key[16]) {
  aes_decrypt(network_key, cryptext, transport_key);
}