#include <iostream>
#include <string>
#include <boost/regex.hpp>
#include <map>

#include "utils.hpp"
#include "svn_log_parser.hpp"
#include "report_writer.hpp"
#include "count_changes.hpp"


int main(int argc, const char * argv[]) {

  count_changes actions;

  subversion::log::parser parser(actions);

  parser.parse(std::cin);

  report_writer writer(std::cout);

  writer.write(actions.change_counts);

  return 0;
}
