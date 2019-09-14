#include "zll_test.h"


int zll_test_key_exchange(void) {

  return 0;
}



int zll_test_run(void) {

  if (zll_test_key_exchange()) {
    return 1;
  }

  return 0;
}