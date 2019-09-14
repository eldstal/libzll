#pragma once

#include "zll_aes.h"
#include "zll_key_exchange.h"

#include <inttypes.h>



#ifdef DEBUG
#define ZLL_PRINTF(fmt,...) printf(fmt, ##__VA_ARGS__)
#else
#define ZLL_PRINTF(fmt,...) /* */
#endif



typedef struct {
  
  struct {
    uint8_t master[16];     // ZLL Master or Certification key
    uint8_t transport[16];  // Temporary transport key
    uint8_t network[16];    // Zigbee network key
  } key;

} zll_network_t;


void zll_network_init(zll_network_t* net);
