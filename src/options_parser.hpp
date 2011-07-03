#ifndef OPTIONS_PARSER_INCLUDED
#define OPTIONS_PARSER_INCLUDED

#include <boost/program_options.hpp>
#include <boost/regex.hpp>
#include "file_filter.hpp"

typedef std::vector<std::string> string_vector;

struct command_options {
  command_options() : format("csv"), filter("*") {
  }
  string_vector input_files;
  std::string format;
  file_filter filter;
};

class options_parser {
  std::ostream& output;
public:
  options_parser();
  options_parser(std::ostream& output);
  
  void parse(int argc, const char * argv[], command_options& options);

private:
  void add_visible_options(boost::program_options::options_description& opts);
  void add_hidden_options(boost::program_options::options_description& opts);
};

#endif
