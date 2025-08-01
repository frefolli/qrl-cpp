#ifndef QRL_ENVS_ROCK_PAPER_SCISSOR_LIKE
#define QRL_ENVS_ROCK_PAPER_SCISSOR_LIKE
#include <qrl/env.hh>
#include <cstdint>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <assert.h>

namespace qrl {
  template <uintmax_t NUMBER_OF_OPTIONS>
  struct RockPaperScissorLike : public Environment<std::vector<intmax_t>, uintmax_t, double_t, NUMBER_OF_OPTIONS> {
    std::vector<intmax_t> state;
    uintmax_t step_count;

    inline static RockPaperScissorLike New() {
      RockPaperScissorLike env;
       env.state = {0};
       env.step_count = 0;
       return env;
    }

    std::vector<intmax_t> reset(uintmax_t /*seed*/) {
      step_count = 0;
      state = {std::rand() % 3};
      return state;
    }

    std::tuple<std::vector<intmax_t>, double_t, bool> step(uintmax_t action) {
      uintmax_t left = state[0];
      assert (left < NUMBER_OF_OPTIONS);
      uintmax_t right = action;
      assert (right < NUMBER_OF_OPTIONS);

      double_t reward = 0.0f;
      if (left == right) {
        reward = 0.0;
      } else {
        if (right == 0) {
          reward = (left == NUMBER_OF_OPTIONS - 1) ? 1.0 : -1.0;
        } else {
          reward = (left == (right - 1)) ? 1.0 : -1.0;
        }
      }

      state = {std::rand() % (long)NUMBER_OF_OPTIONS};
      ++step_count;
      return {state, reward, step_count > 10};
    }
  };
}
#endif//QRL_ENVS_ROCK_PAPER_SCISSOR_LIKE
