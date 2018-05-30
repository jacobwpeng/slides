---?code=code/boost_optional_example.cc&title=boost::optional
@title[boost::optional]

@[17-20](1.使用不可能存在的值)
@[22-28](2.使用单独的boost值标记)
@[30-37](3.使用boost::optional)
@[39-46](boost::optional用法)

---?code=code/boost_foreach.cc&title=BOOST_AUTO/BOOST_FOREACH
@title[BOOST_AUTO/BOOST_FOREACH]

@[19-24](遍历std::vector)
@[26-36](遍历std::map)
@[38-48](统一的遍历方式)
@[50-61](BOOST_AUTO和BOOST_FOREACH结合)
@[63-69](C++11)

---?code=code/boost_local_function.cc&title=BOOST_LOCAL_FUNCTION
@title[BOOST_LOCAL_FUNCTION]

@[19-25](结构定义)
@[31-43](普通排序方式)
@[45-56](通过boost::bind绑定排序)
@[58-66](通过BOOST_LOCAL_FUNCTION排序)

---?code=code/boost_fusion.cc&title=boost::fusion
@title[boost::fusion]

@[18-21](结构定义)
@[23](生成元数据)
@[25-38](基础使用)
@[40-55](进阶用法)

---?code=code/boost_multi_index.cc&title=boost::multi_index
@title[boost::multi_index]

@[28-33](结构定义)
@[77-110](普通实现内部结构)
@[37-49](Add方法)
@[55-74](区间查找)
@[146-174](boost::multi_index实现)
@[146-150](tags)
@[152-154](ordered_unique)
@[156-158](hashed_unique)
@[160-162](hashed_unique)
@[117-120](Add方法)
@[122-130](区间查找)
@[133-143](排名查找)

---?code=code/boost_smart_ptr.cc&title=boost::smart_ptr
@title[boost::smart_ptr]

@[19, 25, 27-28, 30-32](智能指针定义)
@[30-32](boost::shared_ptr)
@[92-96](循环引用导致无法释放)
@[100-104](使用weak_ptr打破循环引用)
@[41-44](判断持有的对象是否已经析构)
@[45-50](从weak_ptr获得对象的shared_ptr)
@[53-56](更方便的使用方式)
@[108-110](测试对象)
@[120-125](错误的实现)
@[112-118](正确的实现)
@[80-81, 83-84](成员函数返回当前对象的智能指针)
@[128-138](scoped_ptr约束指针生命周期)

---?code=code/named_type.cc&title=NamedType
@title[NamedType]

@[36, 46-52](糟糕的参数传递)
@[54-57](更明确呃参数传递)
@[13-24](NamedType定义)
@[26-34](使用方式)
