namespace sort {
  template <typename P> struct descending {

    bool operator()(const P &lhs, const P &rhs) const {
      return lhs.second > rhs.second;
    }
  };
};
