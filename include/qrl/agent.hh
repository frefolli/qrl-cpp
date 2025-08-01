#ifndef QRL_AGENTS_AGENT
#define QRL_AGENTS_AGENT
#include <cstdint>

namespace qrl {
  template <typename State, typename Action, typename Reward, uintmax_t NUMBER_OF_ACTIONS>
  struct Agent {
    virtual Action act(const State& state) = 0;
    virtual void learn(const State& old_state, const Action& action, const State& new_state, const Reward& reward) = 0;
  };
}
#endif//QRL_AGENTS_QL_AGENT
