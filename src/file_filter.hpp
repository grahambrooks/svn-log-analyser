#ifndef FILE_FILTER
#define FILE_FILTER

#include <boost/regex.hpp>

class file_filter {
  boost::regex regex;
public:
  file_filter(std::string pattern);

  bool match(std::string path);
  void operator=(const file_filter& f);
};

#endif
