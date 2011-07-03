#ifndef OPTIONS_PARSER_INCLUDED
#define OPTIONS_PARSER_INCLUDED

#include <boost/program_options.hpp>

typedef std::vector<std::string> string_vector;

struct command_options {
  string_vector input_files;
  std::string format;
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
