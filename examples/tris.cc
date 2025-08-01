#include <qrl/envs/tris.hh>
#include <qrl/agents/ql_agent.hh>
#include <fstream>

using namespace qrl;

int main() {
  Tris environment;
  QLAgent<std::vector<intmax_t>, uintmax_t, double_t, 9> agent;

  std::ofstream training ("./builddir/training.csv");
  training << "Episode,CumulativeReward" << std::endl;
  for (uintmax_t episode = 0; episode < 10000; ++episode) {
    double_t cumulative_reward = training_episode(environment, agent);
    training << episode << "," << cumulative_reward << std::endl;
    std::cout << "training: " << episode << " | " << cumulative_reward << '\r';
  }
  std::cout << std::endl;
  training.close();

  std::ofstream evaluation ("./builddir/evaluation.csv");
  evaluation << "Episode,CumulativeReward" << std::endl;
  for (uintmax_t episode = 0; episode < 100; ++episode) {
    double_t cumulative_reward = evaluation_episode(environment, agent);
    evaluation << episode << "," << cumulative_reward << std::endl;
    std::cout << "evaluation: " << episode << " | " << cumulative_reward << '\r';
  }
  std::cout << std::endl;
  evaluation.close();
  std::cout << agent << std::endl;
  return 0;
}
