#include <iostream>
#include <string>
#include <boost/regex.hpp>
#include <map>

#include "utils.hpp"
#include "svn_log_parser.hpp"

class count_changes: public subversion::log::parser_actions {
public:
	std::map<std::string, int> change_counts;
	void on_break() {
	}
	void on_change(const std::string& change_type, const std::string& filename) {
		if (change_counts.find(filename) == change_counts.end()) {
			change_counts[filename] = 1;
		} else {
			change_counts[filename] += 1;
		}
	}
	void on_summary(const subversion::log::change_summary& summary) {
	}
};

class report_writer {
	std::ostream& out;
public:

	report_writer(std::ostream& out) :
		out(out) {
	}

	void write(std::map<std::string, int>& change_counts) {
		std::vector<std::pair<std::string, int> > myvec(change_counts.begin(), change_counts.end());
		std::sort(myvec.begin(), myvec.end(), sort::descending<std::pair<std::string, int> >());
		const int & count = std::min(50, (int) ((myvec.size())));
		out << "Top " << count << " most frequently changed files" << std::endl;
		out << "# Changes\tFile" << std::endl;
		for (int i = 0; i < count; ++i) {
			if (myvec[i].second <= 1)
				break;

			out << myvec[i].second << "\t" << myvec[i].first << std::endl;
		}
	}
};

int main(int argc, const char * argv[]) {

	count_changes actions;

	subversion::log::parser parser(actions);

	parser.parse(std::cin);

	report_writer writer(std::cout);

	writer.write(actions.change_counts);

	return 0;
}
