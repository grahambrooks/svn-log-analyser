#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#include "utils.hpp"
#include "report_writer.hpp"


report_writer::report_writer(std::ostream& out) : out(out) {}

void report_writer::write(std::map<std::string, int>& change_counts) {
  pair_vector myvec(change_counts.begin(), change_counts.end());
  
  std::sort(myvec.begin(), myvec.end(), sort::descending<std::pair<std::string, int> >());

  const int & count = std::min(50, (int) ((myvec.size())));

  write_header(count);
  write_results(myvec, count);
}

void report_writer::write_header(int count) {
  out << "Top " << count << " most frequently changed files" << std::endl;
  out << "# Changes\tFile" << std::endl;
}

void report_writer::write_results(pair_vector& v, int count) {
  for (int i = 0; i < count; ++i) {
    if (v[i].second <= 1)
      break;

    out << v[i].second << "\t" << v[i].first << std::endl;
  }

}
