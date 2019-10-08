#include <cassert>
#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <sstream>

using namespace std;

class Foo {
  struct {
    condition_variable cv;
    mutex m;
  } cv_m;

  int i = 0;

public:
  Foo() {}

  void first(function<void()> printFirst) {
    unique_lock l(cv_m.m);
    i = 1;

    // printFirst() outputs "first". Do not change or remove this line.
    printFirst();

    l.unlock();
    cv_m.cv.notify_one();
  }

  void second(function<void()> printSecond) {
    unique_lock l(cv_m.m);
    cv_m.cv.wait(l, [this] { return i == 1; });
    i = 2;

    // printSecond() outputs "second". Do not change or remove this line.
    printSecond();

    l.unlock();
    cv_m.cv.notify_one();
  }

  void third(function<void()> printThird) {
    unique_lock l(cv_m.m);
    cv_m.cv.wait(l, [this] { return i == 2; });
    i = 3;

    // printThird() outputs "third". Do not change or remove this line.
    printThird();

    l.unlock();
    cv_m.cv.notify_one();
  }
};

void test_funciton() {
  // ostringstream ss;
  // mutex ss_mutex;

  // auto printFirst = [&ss, &ss_mutex]() {
  //   unique_lock l(ss_mutex);
  //   ss << "first";
  // };
  // auto printSecond = [&ss, &ss_mutex]() {
  //   unique_lock l(ss_mutex);
  //   ss << "second";
  // };

  // auto printThird = [&ss, &ss_mutex]() {
  //   unique_lock l(ss_mutex);
  //   ss << "third";
  // };

  auto printFirst = [&]() {
    cout << "first";
  };

  auto printSecond = []() {
    cout << "second";
  };

  auto printThird = []() {
    cout << "third";
  };

  Foo foo{};

  auto first = thread([&foo, &printFirst]() { foo.first(printFirst); });
  auto second = thread([&foo, &printSecond]() { foo.first(printSecond); });
  auto third = thread([&foo, &printThird]() { foo.first(printThird); });

  first.join();
  second.join();
  third.join();

  // const auto result = ss.str();
  // const auto cpm_result = string{"firstsecondthird"} == result;
  // if (!cpm_result)
  //   cout << result << endl;
  // assert(cpm_result);
}

int main(int, char **) {
  for (auto i = 0; i < 100; ++i) {
    cout << endl;
    // cout << i << endl;
    test_funciton();
  }

  return 0;
}
