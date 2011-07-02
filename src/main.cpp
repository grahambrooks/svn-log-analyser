#include <iostream>
#include <string>
#include <boost/regex.hpp>
#include <map>

#include "utils.hpp"

int main (int argc, const char * argv[])
{
  std::map<std::string, int> change_counts;


  boost::regex break_regex("^[-]+$", boost::match_default);
  boost::regex change_regex("   ([AMD]) ([^$]+)", boost::match_default);
  boost::regex summary_regex("^r(\\d+)"					\
			     "\\s\\|\\s"				\
			     "([^|]+)"					\
			     "\\s\\|\\s"				\
			     "(\\d+)-(\\d+)-(\\d+)\\s(\\d+):(\\d+):(\\d+)\\s[-+](\\d+)" \
			     "\\s\\((\\w+),\\s(\\d+)\\s(\\w+)\\s(\\d+)\\)"					\
			     "\\s\\|\\s"				\
			     "(\\d+)\\sline"				\
			     ".*", boost::match_default | boost::regex_constants::icase);


  std::string line;
  
  while (getline(std::cin, line)) {
    boost::match_results<std::string::const_iterator> what;

    if (regex_match(line, what, summary_regex)) {

      std::string revision(what[1].first, what[1].second);
      //      cout << "Revision " << revision << std::endl;
      //      cout << "Author " << std::string(what[2].first, what[2].second) << std::endl;

    } else if (boost::regex_match(line, break_regex)) {
      std::cerr << ".";

      //      cout << "-- BREAK LINE " << std::endl;

    } else if(regex_match(line, what, change_regex)) {
      std::string change_type(what[1].first, what[1].second);
      std::string file_path(what[2].first, what[2].second);

      if (change_counts.find(file_path) == change_counts.end()) {
	change_counts[file_path] = 1;
      } else {
	change_counts[file_path] += 1;
      }

      //      cout << "File " << file_path << " " << change_type << std::endl;
    } else {
      //      cout << line << std::endl;
    }
  }
  std::cerr << std::endl;

  std::vector<std::pair<std::string, int> > myvec(change_counts.begin(), change_counts.end());  
  std::sort(myvec.begin(), myvec.end(), sort::descending<std::pair<std::string, int> >());

  std::cout << "Top 50 most frequently changed files" << std::endl;
  std::cout << "# Changes\tFile" << std::endl;
  
  for (int i = 0; i < std::min(50, (int)myvec.size()); ++i) {
    if (myvec[i].second <= 1)
      break;
    std::cout << myvec[i].second << "\t" << myvec[i].first << std::endl;
  }


  return 0;
}

