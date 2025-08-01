#include <qrl/ostream.hh>
#include <qrl/random.hh>
#include <qrl/agents/ql_agent.hh>
#include <qrl/envs/rock_paper_scissor_like.hh>
#include <qrl/env.hh>
#include <fstream>
#include <iostream>

using namespace qrl;

int main() {
  constexpr uintmax_t NUMBER_OF_OPTIONS = 10;
  auto environment = RockPaperScissorLike<NUMBER_OF_OPTIONS>::New();
  auto ql_agent = QLAgent<std::vector<intmax_t>, uintmax_t, double_t, NUMBER_OF_OPTIONS>::New();

  std::ofstream training ("./builddir/training.csv");
  training << "Episode,CumulativeReward" << std::endl;
  for (uintmax_t episode = 0; episode < 10000; ++episode) {
    double_t cumulative_reward = training_episode(environment, ql_agent);
    training << episode << "," << cumulative_reward << std::endl;
    std::cout << "training: " << episode << " | " << cumulative_reward << '\r';
  }
  std::cout << std::endl;
  training.close();

  std::ofstream evaluation ("./builddir/evaluation.csv");
  evaluation << "Episode,CumulativeReward" << std::endl;
  for (uintmax_t episode = 0; episode < 100; ++episode) {
    double_t cumulative_reward = evaluation_episode(environment, ql_agent);
    evaluation << episode << "," << cumulative_reward << std::endl;
    std::cout << "evaluation: " << episode << " | " << cumulative_reward << '\r';
  }
  std::cout << std::endl;
  evaluation.close();
  std::cout << ql_agent << std::endl;
  return 0;
}
