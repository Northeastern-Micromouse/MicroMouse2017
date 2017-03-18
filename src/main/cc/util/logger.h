#ifndef MICROMOUSE_LOGGER_H
#define MICROMOUSE_LOGGER_H

#include <string>
#include <ostream>

namespace util {

class logger {
 public:
  logger(bool should_log, std::ostream& out);

  void log(std::string message);

 private:
  std::ostream& out_;
  bool should_log_;
};

}  // util


#endif //MICROMOUSE_LOGGER_H
