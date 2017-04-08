#include "logger.h"

namespace util {

logger::logger(bool should_log, std::ostream& os) :
  should_log_(should_log),
  out_(os) {
  // No op.
}

void logger::log(std::string message) {
  if (should_log_) {
    out_ << message << std::endl;
    out_.flush();
  }
}

void logger::should_log(bool should_log) {
  should_log_ = should_log;
}

}  // util