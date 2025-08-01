#ifndef QRL_OSTREAM
#define QRL_OSTREAM
#include <ostream>
#include <vector>
namespace qrl {
  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const std::vector<T>& vec) {
    bool first = true;
    out << "{ ";
    for (auto el : vec) {
      if (first) {
        first = false;
      } else {
        out << ", ";
      }
      out << el;
    }
    out << " }";
    return out;
  }
}
#endif//QRL_OSTREAM
