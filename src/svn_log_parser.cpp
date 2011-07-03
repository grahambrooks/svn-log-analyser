#include <iostream>
#include "svn_log_parser.hpp"
#include "options_parser.hpp"

namespace subversion {
  namespace log {

    boost::regex parser::break_regex("^[-]+$", boost::match_default);
    boost::regex parser::change_regex("   ([AMD]) ([^$]+)", boost::match_default);
    boost::regex parser::summary_regex("^r(\\d+)"
				       "\\s\\|\\s"
				       "([^|]+)"
				       "\\s\\|\\s"
				       "(\\d+)-(\\d+)-(\\d+)\\s(\\d+):(\\d+):(\\d+)\\s[-+](\\d+)"
				       "\\s\\((\\w+),\\s(\\d+)\\s(\\w+)\\s(\\d+)\\)"
				       "\\s\\|\\s"
				       "(\\d+)\\sline"
				       ".*", boost::match_default | boost::regex_constants::icase);

    parser::parser(parser_actions& actions, const  command_options& options) :
      actions(actions), options(options) {

    }

    void parser::parse(std::istream& input) {
      std::string line;

      while (getline(input, line)) {
	boost::match_results<std::string::const_iterator> what;

	if (boost::regex_match(line, break_regex)) {
	  actions.on_break();
	} else if (boost::regex_match(line, what, change_regex)) {
	  std::string change_type(what[1].first, what[1].second);
	  std::string file_path(what[2].first, what[2].second);

	  if (options.filter.match(file_path)) {
	    actions.on_change(change_type, file_path);
	  }
	} else if (boost::regex_match(line, what, summary_regex)) {
	  change_summary summary;
	  std::string revision(what[1].first, what[1].second);
	  summary.revision = atoi(revision.c_str());

	  summary.author = std::string(what[2].first, what[2].second);

	  summary.lines = atoi(
			       std::string(what[14].first, what[14].second).c_str());

	  actions.on_summary(summary);
	}
      }
    }
  }
}
