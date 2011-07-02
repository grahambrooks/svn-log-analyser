#include <boost/test/unit_test.hpp>
#include "utils.hpp"

BOOST_AUTO_TEST_CASE(sort_descending_compares_the_second_value)
{
  sort::descending<std::pair<int, int> > descending_comparator;

  std::pair<int, int> lhs(10, 10);
  std::pair<int, int> rhs(10, 9);

  BOOST_CHECK(descending_comparator(lhs, rhs));
}

BOOST_AUTO_TEST_CASE(sort_descending_comparing_equal_second_values_is_false)
{
  sort::descending<std::pair<int, int> > descending_comparator;

  std::pair<int, int> lhs(10, 10);
  std::pair<int, int> rhs(10, 10);

  BOOST_CHECK(!descending_comparator(lhs, rhs));
}

BOOST_AUTO_TEST_CASE(can_call_sort_on_empty_vector)
{
  sort::descending<std::pair<int, int> > descending_comparator;

  std::vector<std::pair<int, int> > empty_vector;

  std::sort(empty_vector.begin(), empty_vector.end(), sort::descending<std::pair<int, int> >());
}
BOOST_AUTO_TEST_CASE(can_sort_a_vector_in_descending_order)
{
  sort::descending<std::pair<int, int> > descending_comparator;

  std::vector<std::pair<int, int> > v;
  v.insert(v.end(), std::pair<int, int>(0, 100));
  v.insert(v.end(), std::pair<int, int> (0, 200));

  std::sort(v.begin(), v.end(), sort::descending<std::pair<int, int> >());

  BOOST_CHECK(200 == v[0].second);
  BOOST_CHECK(100 == v[1].second);
}


