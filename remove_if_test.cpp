#include <algorithm>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <vector>

struct base_t {
  base_t(): value(-1) {}
  base_t(const int &_value): value(_value) {}
  virtual ~base_t(){}


  int value;

  virtual void foo() const {
    std::cout << value << " ";
  }
};

struct derived_t : public base_t {
  derived_t(const int &_value)
    :base_t(_value)
    ,trash(123)
    ,qwe(123.123)
    ,asd(123.123)
  {}

  int trash;
  double qwe;
  float asd;
};

typedef boost::shared_ptr<base_t> base_ptr_t;

struct base_less_t {
  typedef base_ptr_t first_argument_type;
  typedef int second_argument_type;
  typedef bool result_type;

  bool operator()(const base_ptr_t &base, const int &value) const {
    return base->value < value;
  }
};


int main() {

  std::vector<base_ptr_t> data;
  for (int i = 0; i < 10; ++i) {
    data.push_back(base_ptr_t(new derived_t(i)));
  }

  for (size_t i = 0;i < data.size(); ++i) {
    data[i]->foo();
  }
  std::cout << std::endl;

  data.erase(
      std::remove_if(
        data.begin(),
        data.end(),
        std::bind2nd(base_less_t(), 5)
      ),
      data.end());

  for (size_t i = 0;i < data.size(); ++i) {
    data[i]->foo();
  }
  std::cout << std::endl;

  return 0;
}
