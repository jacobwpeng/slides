/*
 * ==================================================================
 *
 *       Filename:  boost_smart_ptr.cc
 *         Author:  Peng Wang
 *          Email:  pw2191195@gmail.com
 *        Created:  05/30/18 09:47:43
 *    Description:  boost::shared_ptr, boost::scoped_ptr, boost::weak_ptr示例
 *                  std::auto_ptr默认支持拷贝, 但是拷贝转移了所有权
 *                  taf::TC_AutoPtr则依赖于保存的对象继承于taf::TC_HandleBase
 *                  MJRoomServer中的CSmartPointer依赖于保存的对象实现IncRef&DecRef
 *                  以上几个智能指针都缺失了打破循环依赖的指针(weak_ptr)
 *
 *
 * ==================================================================
 */

#include <iostream>
#include <boost/smart_ptr.hpp>

class Foo;
class Bar;
class Baz;

typedef boost::shared_ptr<Foo> FooPtr;

typedef boost::shared_ptr<Bar> BarPtr;
typedef boost::weak_ptr<Bar> BarWeakPtr;

typedef boost::shared_ptr<Baz> BazPtr;
typedef boost::weak_ptr<Baz> BazWeakPtr;
typedef boost::scoped_ptr<Baz> BazScopedPtr;

class Foo {
 public:
  explicit Foo(BarPtr ptr) : bar_(ptr) {}

  explicit Foo(BarWeakPtr weakPtr) : weakBar_(weakPtr) {}

  void doSomethingWithWeakPtr() {
    // 持有的是弱引用, 要先lock确认对方没有被释放
    if (weakBar_.expired()) {
      return;
    }
    // 并临时获得一个强引用
    BarPtr bar = weakBar_.lock();
    // 由于expire和lock之间存在时间窗口, 要确认bar是否已经被释放
    if (bar == NULL) {
      return;
    }
    // 现在可以安全的使用bar指针了

    // 或者可以这样
    if (BarPtr bar2 = weakBar_.lock()) {
      // 表示该对象仍然存活, 可以安全使用
    }
  }

  ~Foo() { std::cout << "Destory Foo\n"; }

 private:
  BarPtr bar_;
  BarWeakPtr weakBar_;
};

class Bar {
 public:
  ~Bar() { std::cout << "Destory Bar\n"; }

  void SetFoo(const FooPtr& ptr) { foo_ = ptr; }

 private:
  FooPtr foo_;
};

class Baz : public boost::enable_shared_from_this<Baz> {
 public:
  Baz() : val_(0) {}

  // 错误的实现!!!
  BazPtr GetSharedBuggly() { return BazPtr(this); }

  // 正确的实现
  BazPtr GetShared() { return shared_from_this(); }

 private:
  int val_;
};

int main() {
  {
    // Foo和Bar互相持有各自的强引用
    // 导致两个对象都无法被释放, 造成资源泄漏
    BarPtr bar = boost::make_shared<Bar>();
    FooPtr foo = boost::make_shared<Foo>(bar);
    bar->SetFoo(foo);
  }

  {
    // 使用WeakPtr打破循环依赖, 正常释放资源
    BarPtr bar = boost::make_shared<Bar>();
    FooPtr foo = boost::make_shared<Foo>(BarWeakPtr(bar));
    bar->SetFoo(foo);
    foo->doSomethingWithWeakPtr();
  }

  {
    Baz* p = new Baz();
    BazPtr baz = BazPtr(p);
    boost::weak_ptr<Baz> weakBaz = baz->weak_from_this();

    // 使用shared_from_this获取shared_ptr, 保证增加的是同一份引用计数
    assert(weakBaz.use_count() == 1);
    {
      BazPtr newBaz = baz->GetShared();
      assert(weakBaz.use_count() == 2);
    }
    assert(weakBaz.use_count() == 1);

    // 如果直接返回BazPtr(this), 则会产生一个全新的shared_ptr
    // 那么会导致new出来的指针p会被两个不同的智能指针管理, 造成double free
    BazPtr buggly = baz->GetSharedBuggly();
    BazWeakPtr bugglyWeak(buggly);
    assert(weakBaz.use_count() == 1);
    assert(bugglyWeak.use_count() == 1);
  }

  boost::scoped_ptr<Bar> out;
  {
    // boost::scoped_ptr则无法被拷贝, 保证资源一定释放(除非显示转移所有权)
    boost::scoped_ptr<Bar> bar(new Bar);
    // 无法编译
    // boost::scoped_ptr<Bar> newBar = bar;
    // 可以通过swap将所有权转出去
    out.swap(bar);
    assert(bar == NULL);
  }
  assert(out != NULL);
}
