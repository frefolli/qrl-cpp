#ifndef QRL_RANDOM
#define QRL_RANDOM
#include <cmath>
#include <cstdlib>
namespace qrl {
  inline double_t random_double_t() {
    return (double_t)(rand()) / (double_t)(RAND_MAX);
  }
}
#endif//QRL_RANDOM
