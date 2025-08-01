#ifndef QRL_AGENTS_RANDOM_AGENT
#define QRL_AGENTS_RANDOM_AGENT
#include <cassert>
#include <qrl/random.hh>
#include <qrl/ostream.hh>
#include <qrl/agent.hh>
#include <random>

namespace qrl {
  template <typename State, typename Action, typename Reward, uintmax_t NUMBER_OF_ACTIONS>
  struct RandomAgent : public Agent<State, Action, Reward, NUMBER_OF_ACTIONS> {
    std::mt19937 gen;
    std::uniform_int_distribution<> dist = std::uniform_int_distribution<>(0, NUMBER_OF_ACTIONS - 1);

    Action act(const State& /*state*/) {
      return dist(gen);
    }

    void learn(const State& /*old_state*/, const Action& /*action*/, const State& /*new_state*/, const Reward& /*reward*/) {
      assert(false);
    }
  };
}
#endif//QRL_AGENTS_RANDOM_AGENT
