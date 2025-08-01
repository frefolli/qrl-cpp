#ifndef QRL_AGENTS_QL_AGENT
#define QRL_AGENTS_QL_AGENT
#include <qrl/random.hh>
#include <qrl/ostream.hh>
#include <qrl/agent.hh>
#include <map>
#include <vector>

namespace qrl {
  template <typename State, typename Action, typename Reward, uintmax_t NUMBER_OF_ACTIONS>
  struct QLAgent : public Agent<State, Action, Reward, NUMBER_OF_ACTIONS> {
    std::map<State, std::vector<Reward>> table;
    std::map<State, std::pair<uintmax_t, Reward>> policy;

    Reward alpha;
    Reward gamma;
    double_t epsilon;
    double_t decay;

    Action act(const State& state) {
      auto record_it = policy.find(state);
      if (record_it == policy.end()) {
        policy[state] = {0, 0.0};
        table[state] = std::vector<Reward>(NUMBER_OF_ACTIONS, 0.0);
      }
      if (epsilon > 0) {
        if (random_double_t() <= epsilon) {
          epsilon *= decay;
          return std::rand() % NUMBER_OF_ACTIONS;
        } else {
          epsilon *= decay;
        }
      }
      return policy[state].first;
    }

    void learn(const State& old_state, const Action& action, const State& new_state, const Reward& reward) {
      auto record_it = policy.find(new_state);
      Reward new_state_reward = 0.0;
      if (record_it == policy.end()) {
        policy[new_state] = {0, 0.0};
        table[new_state] = std::vector<Reward>(NUMBER_OF_ACTIONS, 0.0);
      } else {
        new_state_reward = record_it->second.second;
      }

      std::vector<Reward>& action_rewards = this->table[old_state];
      Reward old_state_reward = action_rewards[action];
      Reward updated_old_state_reward = (1.0f - this->alpha) * old_state_reward + this->alpha * (reward + this->gamma * new_state_reward);
      action_rewards[action] = updated_old_state_reward;
      auto reward_it = std::max_element(action_rewards.begin(), action_rewards.end());

      uintmax_t max_idx = std::distance(action_rewards.begin(), reward_it);
      Reward max_rew = *reward_it;
      policy[old_state] = {max_idx, max_rew};
    }

    static QLAgent New() {
      QLAgent agent; 
      agent.table = {};
      agent.policy = {};
      agent.alpha = 0.5f;
      agent.gamma = 0.95f;
      agent.epsilon = 1.0;
      agent.decay = 0.9999f;
      return agent;
    }
  };

  template <typename State, typename Action, typename Reward, uintmax_t NUMBER_OF_ACTIONS>
  std::ostream& operator<<(std::ostream& out, const QLAgent<State, Action, Reward, NUMBER_OF_ACTIONS>& agent) {
    for (auto record : agent.table) {
      out << record.first << " -> " << record.second << std::endl;
    }
    return out;
  }
}
#endif//QRL_AGENTS_QL_AGENT
