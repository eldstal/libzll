#pragma once

#include "zll_packets.h"
#include "zll_aes.h"
#include "zll_key_exchange.h"

#include <inttypes.h>
#include <stddef.h>



#ifdef DEBUG
#include <stdio.h>
#define ZLL_PRINTF(fmt,...) printf(fmt, ##__VA_ARGS__)
#else
#define ZLL_PRINTF(fmt,...) /* */
#endif


typedef struct {
  uint8_t data[16];
  size_t length;
} zll_zigbee_packet;


typedef struct zll_zigbee_driver zll_zigbee_driver_t;


typedef struct {

  struct {
    uint16_t pan;
    uint8_t extended[8];
  } id;
  
  struct {
    uint8_t master[16];     // ZLL Master or Certification key
    uint8_t transport[16];  // Temporary transport key
    uint8_t network[16];    // Zigbee network key
  } key;

  zll_zigbee_driver_t* driver;

  void* user; 

} zll_network_t;



/**
 * Glue between an existing Zigbee system and the ZLL library.
 * Implement these functions and pass the pointers into zll_network_init.
 */
struct zll_zigbee_driver {
  void (*send_packet)(zll_network_t* net, zll_zigbee_packet* packet);
  void (*parse_packet)(zll_network_t* net, zll_zigbee_packet* parsed, void* packet);
  
};


/**
 * Initialize a zigbee network that this device should be part of.
 * @param net the structure to initialize
 * @param driver a driver structure giving us access to a zigbee stack.
 * @param user Opaque reference. Will be available as net->user in all calls to your driver.
 */
void zll_network_init(zll_network_t* net, zll_zigbee_driver_t* driver, void* user);
