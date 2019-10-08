#include <cassert>
#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <sstream>
#include <atomic>

using namespace std;

class Foo {
  atomic_bool first_called = false;
  atomic_bool second_called = false;
public:
  Foo() {}

  void first(function<void()> printFirst) {
   
    // printFirst() outputs "first". Do not change or remove this line.
    printFirst();

    first_called = true;
  }

  void second(function<void()> printSecond) {
    while( ! first_called )
      ;

    // printSecond() outputs "second". Do not change or remove this line.
    printSecond();

    second_called = true;
  }

  void third(function<void()> printThird) {
    while (!second_called)
      ;

    // printThird() outputs "third". Do not change or remove this line.
    printThird();
  }
};

void test_funciton() {
  ostringstream ss;
  mutex ss_mutex;

  auto printFirst = [&ss, &ss_mutex]() {
    unique_lock l(ss_mutex);
    ss << "first";
  };
  auto printSecond = [&ss, &ss_mutex]() {
    unique_lock l(ss_mutex);
    ss << "second";
  };

  auto printThird = [&ss, &ss_mutex]() {
    unique_lock l(ss_mutex);
    ss << "third";
  };

  Foo foo{};

  const auto first =
      async(launch::async, [&foo, &printFirst]() { foo.first(printFirst); });
  const auto second =
      async(launch::async, [&foo, &printSecond]() { foo.second(printSecond); });
  const auto third =
      async(launch::async, [&foo, &printThird]() { foo.third(printThird); });

  first.wait();
  second.wait();
  third.wait();

  const auto result = ss.str();
  const auto cpm_result = string{"firstsecondthird"} == result;
  if (!cpm_result)
    cout << result << endl;
  assert(cpm_result);
}

int main(int, char **) {
  for (auto i = 0; i < static_cast<int>(1e4); ++i) {
    test_funciton();
  }

  return 0;
}
