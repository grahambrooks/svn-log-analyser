#include <boost/test/unit_test.hpp>
#include "svn_log_parser.hpp"

namespace subversion {
  namespace log {

    class test_actions: public parser_actions {
    public:
      int break_calls;
      std::string change_type;
      std::string change_file;
      change_summary summary;

      test_actions() :
	break_calls(0) {
      }

      void on_break() {
	break_calls++;
      }

      void on_change(const std::string& change_type,
		     const std::string& change_file) {
	this->change_type = change_type;
	this->change_file = change_file;
      }

      void on_summary(const change_summary& summary) {
	this->summary = summary;
      }
    };

    void parse_input(parser_actions& a, const char* text) {
      command_options options;
      
      parser parser(a, options);
      
      std::istringstream input(text);

      parser.parse(input);
    }

    BOOST_AUTO_TEST_CASE(parser_accepts_empty_stream)
    {
      command_options options;
      test_actions actions;
      parser parser(actions, options);

      std::istringstream input;

      parser.parse(input);
    }

    BOOST_AUTO_TEST_CASE(parser_recognises_break_lines)
    {
      test_actions actions;

      parse_input(actions, "------------");

      BOOST_CHECK(actions.break_calls > 0);
    }

    BOOST_AUTO_TEST_CASE(parser_recognises_change_lines)
    {
      test_actions actions;

      parse_input(actions, "   A /some/path");

      BOOST_CHECK_EQUAL("A", actions.change_type);
      BOOST_CHECK_EQUAL("/some/path", actions.change_file);
    }

    BOOST_AUTO_TEST_CASE(parser_recognises_summary_lines)
    {
      test_actions actions;

      parse_input(actions,
		  "r1 | graham | 2009-07-17 17:25:54 -0400 (Fri, 17 Jul 2009) | 1 line");

      BOOST_CHECK_EQUAL(1, actions.summary.revision);
      BOOST_CHECK_EQUAL("graham", actions.summary.author);
      BOOST_CHECK_EQUAL(1, actions.summary.lines);
    }
  }
}

