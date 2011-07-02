
class report_writer {
  std::ostream& out;
public:
  typedef std::vector<std::pair<std::string, int> > pair_vector;

  report_writer(std::ostream& out);

  void write(std::map<std::string, int>& change_counts);

  void write_header(int count);

  void write_results(pair_vector& v, int count);
};
