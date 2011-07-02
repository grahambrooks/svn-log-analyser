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
