#ifndef QRL_ENVS_TRIS
#define QRL_ENVS_TRIS
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <qrl/env.hh>
#include <random>
#include <vector>

namespace qrl {
  constexpr intmax_t E  = 0;
  constexpr intmax_t P1 = 1;
  constexpr intmax_t P2 = 2;
  struct Tris : Environment<std::vector<intmax_t>, uintmax_t, double_t, 9> {
    std::vector<intmax_t> state = {};
    uintmax_t turn = 0;
    uintmax_t action_count = 0;
    std::mt19937 gen;
    std::uniform_int_distribution<> distrib = std::uniform_int_distribution<>(0,9);

    std::vector<intmax_t> reset(uintmax_t seed = 0) {
      gen.seed(seed);
      state = {
        E, E, E,
        E, E, E,
        E, E, E
      };
      turn = 0;
      action_count = 0;
      return state;
    }

    uintmax_t random_action() {
      uintmax_t action = distrib(gen);
      uintmax_t safe_count = 0;
      constexpr uintmax_t threshold = 10;
      while (state[action] != E) {
        action = distrib(gen);
        ++safe_count;
        if (safe_count >= threshold) {
          for (uintmax_t i = 0; i < 9; ++i) {
            if (state[i] == E) {
              return i;
            }
          }
          assert(false);
        }
      }
      return action;
    }

    uintmax_t check_table() {
      // Returns:
      // * 0 if no one won
      // * 1 if P1 won
      // * 2 if P2 won

      bool p1_done_it = false;
      bool p2_done_it = false;

      for (uintmax_t j = 0; j < 9; j += 3) {
        if (state[j] == state[j + 1] && state[j] == state[j + 2]) {
          if (state[j] == P1) {
            p1_done_it = true;
          } else if (state[j] == P2) {
            p2_done_it = true;
          }
        }
      }

      for (uintmax_t j = 0; j < 3; ++j) {
        if (state[j] == state[j + 3] && state[j] == state[j + 6]) {
          if (state[j] == P1) {
            p1_done_it = true;
          } else if (state[j] == P2) {
            p2_done_it = true;
          }
        }
      }

      if (state[0] == state[4] && state[0] == state[8]) {
        if (state[0] == P1) {
          p1_done_it = true;
        } else if (state[0] == P2) {
          p2_done_it = true;
        }
      }

      if (state[2] == state[4] && state[2] == state[6]) {
        if (state[2] == P1) {
          p1_done_it = true;
        } else if (state[2] == P2) {
          p2_done_it = true;
        }
      }

      return (p1_done_it) ? 1 : (p2_done_it ? 2 : 0);
    }

    std::tuple<std::vector<intmax_t>, double_t, bool> step(uintmax_t action) {
      assert(action < 9);
      double_t reward = 0.0f;
      if (state[action] == E) {
        state[action] = P1;
        ++turn;
        if (turn < 9) {
          uintmax_t counter_action = random_action();
          assert(state[counter_action] == E);
          state[counter_action] = P2;
          ++turn;
        }
      } else {
        reward = -1.0f;
      }

      bool terminated = turn >= 9;
      uintmax_t checked = check_table();
      if (checked == P1) {
        reward = 1.0f;
        terminated = true;
      } else if (checked == P2) {
        reward = -1.0f;
        terminated = true;
      }

      ++action_count;
      if (action_count > 1000) {
        terminated = true;
        reward = -4.0f;
      }
      return {state, reward, terminated};
    }

    void render() {
      std::clog << "------" << std::endl;
      for (uintmax_t j = 0; j < 9; j += 3) {
        for (uintmax_t i = 0; i < 3; ++i) {
          intmax_t v = state[i + j];
          char c = (v == E) ? '+' : ((v == P1) ? 'X' : 'O');
          std::clog << c << ' ';
        }
        std::clog << std::endl;
      }
    }
  };
}
#endif//QRL_ENVS_TRIS
