#ifndef QRL_ENV
#define QRL_ENV
#include <qrl/agent.hh>
#include <cstdint>
#include <cmath>
#include <vector>

namespace qrl {
  template <typename State, typename Action, typename Reward, uintmax_t NUMBER_OF_OPTIONS>
  struct Environment {
    State state;

    virtual State reset() = 0;
    virtual std::tuple<State, Reward, bool> step(Action action) = 0;
  };

  template<typename State, typename Action, typename Reward, uintmax_t NUMBER_OF_OPTIONS>
  inline double_t training_episode(Environment<State, Action, Reward, NUMBER_OF_OPTIONS>& environment, Agent<State, Action, Reward, NUMBER_OF_OPTIONS>& agent) {
    double_t cumulative_reward = 0.0;
    std::vector<intmax_t> state = environment.reset();
    bool terminated = false;
    while (!terminated) {
      uintmax_t action = agent.act(state);
      auto update = environment.step(action);
      agent.learn(state, action, std::get<0>(update), std::get<1>(update));
      state = std::get<0>(update);
      cumulative_reward += std::get<1>(update);
      terminated = std::get<2>(update);
    }
    return cumulative_reward;
  }

  template<typename State, typename Action, typename Reward, uintmax_t NUMBER_OF_OPTIONS>
  inline double_t evaluation_episode(Environment<State, Action, Reward, NUMBER_OF_OPTIONS>& environment, Agent<State, Action, Reward, NUMBER_OF_OPTIONS>& agent) {
    double_t cumulative_reward = 0.0;
    std::vector<intmax_t> state = environment.reset();
    bool terminated = false;
    while (!terminated) {
      uintmax_t action = agent.act(state);
      auto update = environment.step(action);
      state = std::get<0>(update);
      cumulative_reward += std::get<1>(update);
      terminated = std::get<2>(update);
    }
    return cumulative_reward;
  }
}
#endif//QRL_ENV
