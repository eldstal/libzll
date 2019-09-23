#pragma once

#include <inttypes.h>


/**
 * Generate the temporary transport key, used only during exchange of the network key.
 * @param transport_key destination
 * @param trans_id the transaction ID found during touch-linking procedure
 * @param resp_id the response ID found during touch-linking procedure
 */
 void zll_transport_key(uint8_t transport_key[16], uint32_t trans_id, uint32_t resp_id, uint8_t master_key[16]);


/**
 * Initiator: Encrypt the network key so it can be transmitted to a target
 * @param cryptext destination
 * @param network_key the payload to encrypt
 * @param transport_key the temporary transport key used to encrypt
 */
 void zll_encrypt_network_key(uint8_t cryptext[16], uint8_t network_key[16], uint8_t transport_key[16]);


/**
 * Target: Decrypt the network key received from the initiator
 * @param network_key destination
 * @param cryptext the payload received
 * @param transport_key the temporary transport key used to encrypt
 */
 void zll_decrypt_network_key(uint8_t network_key[16], uint8_t cryptext[16], uint8_t transport_key[16]);
