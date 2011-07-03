#include <boost/test/unit_test.hpp>
#include "file_filter.hpp"

BOOST_AUTO_TEST_CASE(filter_returns_true_for_matching_filenames)
{
  file_filter filter("*.java");

  BOOST_CHECK(filter.match("somepath.java"));
}

BOOST_AUTO_TEST_CASE(filter_does_not_match_files_that_do_not_match_the_pattern)
{
  file_filter filter("*.java");

  BOOST_CHECK(!filter.match("wrongpath.c"));
}
