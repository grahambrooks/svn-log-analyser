#ifndef SVN_LOG_PARSER
#define SVN_LOG_PARSER

#include <boost/regex.hpp>
#include "options_parser.hpp"

namespace subversion {
  namespace log {

    struct change_summary {
      int revision;
      std::string author;
      int lines;
    };

    class parser_actions {
    public:
      virtual void on_break() = 0;
      virtual void on_change(const std::string& change_type, const std::string& filename) = 0;
      virtual void on_summary(const change_summary& summary) = 0;
    };

    class parser {
      static boost::regex break_regex;
      static boost::regex change_regex;
      static boost::regex summary_regex;

      parser_actions& actions;
      command_options options;
    public:
      parser(parser_actions& actions, const  command_options& options);
      void parse(std::istream& input);
    };
  }
}
#endif
