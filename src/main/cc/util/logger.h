#ifndef MICROMOUSE_LOGGER_H
#define MICROMOUSE_LOGGER_H

#include <string>
#include <ostream>

namespace util {

class logger {
 public:
  logger(bool should_log, std::ostream& out);

  void log(std::string message);

  void should_log(bool should_log);

 private:
  bool should_log_;
  std::ostream& out_;
};

}  // util


#endif //MICROMOUSE_LOGGER_H
