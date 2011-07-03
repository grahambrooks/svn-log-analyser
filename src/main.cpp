#include <iostream>
#include <string>
#include <boost/regex.hpp>
#include <map>

#include "utils.hpp"
#include "svn_log_parser.hpp"
#include "report_writer.hpp"
#include "count_changes.hpp"
#include "options_parser.hpp"

int main(int argc, const char * argv[]) {
  options_parser options_parser;
  
  command_options options;
  options_parser.parse(argc, argv, options);

  count_changes actions;

  subversion::log::parser parser(actions);

  parser.parse(std::cin);

  report_writer writer(std::cout);

  writer.write(actions.change_counts);

  return 0;
}
