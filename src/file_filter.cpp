#include "file_filter.hpp"

file_filter::file_filter(std::string pattern) {
  boost::regex candidate_pattern("\\*");
  std::string replacement(".*");

  regex = boost::regex(boost::regex_replace(pattern, candidate_pattern, replacement));
}

bool file_filter::match(std::string path) {
  
  return boost::regex_match(path, regex);
}

void file_filter::operator=(const file_filter& f) {
  regex = f.regex;
}
