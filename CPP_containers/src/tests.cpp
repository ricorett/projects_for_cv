#include <gtest/gtest.h>

#include <array>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#include "s21_containers.h"
#include "s21_containersplus.h"

TEST(S21ListTest, ConstructorWithSize) {
  s21::list<int> myList(5);
  EXPECT_EQ(myList.size(), 5);
}

TEST(S21ListTest, PushBack) {
  s21::list<int> myList;
  myList.push_back(10);
  myList.push_back(20);

  EXPECT_EQ(myList.size(), 2);

  auto it = myList.begin();
  EXPECT_EQ(*it, 10);
  ++it;
  EXPECT_EQ(*it, 20);
}

TEST(S21ListTest, PushFront) {
  s21::list<int> myList;
  myList.push_front(10);
  myList.push_front(20);

  EXPECT_EQ(myList.size(), 2);

  auto it = myList.begin();
  EXPECT_EQ(*it, 20);
  ++it;
  EXPECT_EQ(*it, 10);
}

TEST(S21ListTest, PopBack) {
  s21::list<int> myList;
  myList.push_back(10);
  myList.push_back(20);
  myList.pop_back();

  EXPECT_EQ(myList.size(), 1);

  auto it = myList.begin();
  EXPECT_EQ(*it, 10);
}

TEST(S21ListTest, PopFront) {
  s21::list<int> myList;
  myList.push_front(10);
  myList.push_front(20);
  myList.pop_front();

  EXPECT_EQ(myList.size(), 1);

  auto it = myList.begin();
  EXPECT_EQ(*it, 10);
}

TEST(S21ListTest, Clear) {
  s21::list<int> myList;
  myList.push_back(10);
  myList.push_back(20);
  myList.push_back(30);

  myList.clear();

  EXPECT_EQ(myList.size(), 0);
  EXPECT_EQ(myList.begin(), myList.end());
}

TEST(ListTest, CopyAssignmentOperator_Simple) {
  s21::list<int> list1;
  list1.push_back(1);
  list1.push_back(2);

  s21::list<int> list2;
  list2 = list1;

  EXPECT_EQ(list2.size(), 2);
  EXPECT_EQ(list2.front(), 1);
  EXPECT_EQ(list2.back(), 2);
}

TEST(ListTest, CopyAssignmentOperator_EmptyList) {
  s21::list<int> list1;

  s21::list<int> list2;
  list2.push_back(5);
  list2 = list1;

  EXPECT_TRUE(list2.empty());
}

TEST(ListTest, CopyAssignmentOperator_SelfAssignment) {
  s21::list<int> list;
  list.push_back(1);
  list.push_back(2);

  list = list;

  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 2);
}
TEST(ListTest, MoveAssignmentOperator_Simple) {
  s21::list<int> list1;
  list1.push_back(1);
  list1.push_back(2);

  s21::list<int> list2;
  list2 = std::move(list1);

  EXPECT_EQ(list2.size(), 2);
  EXPECT_EQ(list2.front(), 1);
  EXPECT_EQ(list2.back(), 2);
  EXPECT_TRUE(list1.empty());
}

TEST(ListTest, MoveAssignmentOperator_EmptyList) {
  s21::list<int> list1;

  s21::list<int> list2;
  list2.push_back(5);
  list2 = std::move(list1);

  EXPECT_TRUE(list2.empty());
  EXPECT_TRUE(list1.empty());
}

TEST(ListTest, Remove_ElementExists) {
  s21::list<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  list.remove(2);

  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 3);
}

TEST(ListTest, Remove_MultipleElements) {
  s21::list<int> list;
  list.push_back(2);
  list.push_back(2);
  list.push_back(3);

  list.remove(2);

  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.front(), 3);
  EXPECT_EQ(list.back(), 3);
}

TEST(ListTest, Remove_ElementNotExists) {
  s21::list<int> list;
  list.push_back(1);
  list.push_back(3);

  list.remove(2);

  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 3);
}

TEST(ListTest, Copy_Simple) {
  s21::list<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  s21::list<int> copied_list = list.copy();

  EXPECT_EQ(copied_list.size(), 3);
  EXPECT_EQ(copied_list.front(), 1);
  EXPECT_EQ(copied_list.back(), 3);
}

TEST(ListTest, Copy_EmptyList) {
  s21::list<int> list;

  s21::list<int> copied_list = list.copy();

  EXPECT_TRUE(copied_list.empty());
}

TEST(ListTest, Copy_Independent) {
  s21::list<int> list;
  list.push_back(1);
  list.push_back(2);

  s21::list<int> copied_list = list.copy();
  list.push_back(3);

  EXPECT_EQ(copied_list.size(), 2);
  EXPECT_EQ(list.size(), 3);
}

TEST(ListTest, Merge_TwoNonEmptyLists) {
  s21::list<int> list1;
  list1.push_back(1);
  list1.push_back(3);

  s21::list<int> list2;
  list2.push_back(2);
  list2.push_back(4);

  list1.merge(list2);

  EXPECT_EQ(list1.size(), 4);
  EXPECT_EQ(list1.front(), 1);
  EXPECT_EQ(list1.back(), 4);
  EXPECT_TRUE(list2.empty());
}

TEST(ListTest, Merge_EmptyWithNonEmpty) {
  s21::list<int> list1;

  s21::list<int> list2;
  list2.push_back(1);
  list2.push_back(2);

  list1.merge(list2);

  EXPECT_EQ(list1.size(), 2);
  EXPECT_EQ(list1.front(), 1);
  EXPECT_EQ(list1.back(), 2);
  EXPECT_TRUE(list2.empty());
}

TEST(ListTest, Merge_EmptyWithEmpty) {
  s21::list<int> list1;
  s21::list<int> list2;

  list1.merge(list2);

  EXPECT_TRUE(list1.empty());
  EXPECT_TRUE(list2.empty());
}

TEST(ListTest, Swap_TwoNonEmptyLists) {
  s21::list<int> list1;
  list1.push_back(1);
  list1.push_back(2);

  s21::list<int> list2;
  list2.push_back(3);
  list2.push_back(4);

  list1.swap(list2);

  EXPECT_EQ(list1.size(), 2);
  EXPECT_EQ(list1.front(), 3);
  EXPECT_EQ(list1.back(), 4);

  EXPECT_EQ(list2.size(), 2);
  EXPECT_EQ(list2.front(), 1);
  EXPECT_EQ(list2.back(), 2);
}

TEST(ListTest, Swap_EmptyWithNonEmpty) {
  s21::list<int> list1;

  s21::list<int> list2;
  list2.push_back(1);
  list2.push_back(2);

  list1.swap(list2);

  EXPECT_EQ(list1.size(), 2);
  EXPECT_EQ(list1.front(), 1);
  EXPECT_EQ(list1.back(), 2);

  EXPECT_TRUE(list2.empty());
}

TEST(ListTest, Swap_TwoEmptyLists) {
  s21::list<int> list1;
  s21::list<int> list2;

  list1.swap(list2);

  EXPECT_TRUE(list1.empty());
  EXPECT_TRUE(list2.empty());
}

TEST(ListTest, Splice_InsertAtBegin) {
  s21::list<int> list1;
  list1.push_back(3);
  list1.push_back(4);

  s21::list<int> list2;
  list2.push_back(1);
  list2.push_back(2);

  list1.splice(list1.cbegin(), list2);

  EXPECT_EQ(list1.size(), 4);
  EXPECT_EQ(list1.front(), 1);
  EXPECT_EQ(list1.back(), 4);
  EXPECT_TRUE(list2.empty());
}

TEST(ListTest, Splice_InsertAtEnd) {
  s21::list<int> list1;
  list1.push_back(1);
  list1.push_back(2);

  s21::list<int> list2;
  list2.push_back(3);
  list2.push_back(4);

  list1.splice(list1.cend(), list2);

  EXPECT_EQ(list1.size(), 4);
  EXPECT_EQ(list1.front(), 1);
  EXPECT_EQ(list1.back(), 4);
  EXPECT_TRUE(list2.empty());
}

TEST(ListTest, Splice_InsertInMiddle) {
  s21::list<int> list1;
  list1.push_back(1);
  list1.push_back(4);

  s21::list<int> list2;
  list2.push_back(2);
  list2.push_back(3);

  auto it = list1.cbegin();
  ++it;
  list1.splice(it, list2);

  EXPECT_EQ(list1.size(), 4);
  EXPECT_EQ(list1.front(), 1);
  EXPECT_EQ(list1.back(), 4);
  EXPECT_TRUE(list2.empty());
}

TEST(ListTest, Reverse_SimpleList) {
  s21::list<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  list.reverse();

  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.front(), 3);
  EXPECT_EQ(list.back(), 1);
}

TEST(ListTest, Reverse_EmptyList) {
  s21::list<int> list;

  list.reverse();

  EXPECT_TRUE(list.empty());
}

TEST(ListTest, Reverse_SingleElement) {
  s21::list<int> list;
  list.push_back(1);

  list.reverse();

  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.front(), 1);
}

TEST(ListTest, MaxSize_NotEmptyList) {
  s21::list<int> list;
  list.push_back(1);
  EXPECT_GT(list.max_size(), 0);
}

TEST(ListTest, MaxSize_EmptyList) {
  s21::list<int> list;
  EXPECT_GT(list.max_size(), 0);
}

TEST(ListTest, MaxSize_LargeList) {
  s21::list<int> list;
  for (int i = 0; i < 10000; ++i) {
    list.push_back(i);
  }
  EXPECT_GT(list.max_size(), list.size());
}

TEST(ListTest, CreateEmptyList) {
  s21::list<int> l(0);
  EXPECT_EQ(l.size(), 0);
}

TEST(ListTest, CreateListWithDefaultValues) {
  s21::list<int> l(5);
  EXPECT_EQ(l.size(), 5);

  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(l.front(), 0);
    l.pop_front();
  }
}

TEST(ListTest, CreateListFromEmptyInitializerList) {
  s21::list<int> l{};
  EXPECT_EQ(l.size(), 0);
}

TEST(ListTest, CreateListFromInitializerList) {
  s21::list<int> l{1, 2, 3, 4, 5};
  EXPECT_EQ(l.size(), 5);

  for (int i = 1; i < 6; ++i) {
    EXPECT_EQ(l.front(), i);
    l.pop_front();
  }
}

struct TestStruct {
  int x;
  TestStruct(int value) : x(value) {}
  bool operator==(const TestStruct &other) const { return x == other.x; }
};

TEST(ListTest, ConstructorWithStrings) {
  s21::list<std::string> l(3);
  EXPECT_EQ(l.size(), 3);

  for (auto it = l.begin(); it != l.end(); ++it) {
    EXPECT_EQ(*it, "");
  }
}

TEST(ListTest, CreateListFromInitializerListWithCustomType) {
  s21::list<TestStruct> l{{10}, {20}, {30}};
  EXPECT_EQ(l.size(), 3);

  EXPECT_EQ(l.front().x, 10);
  l.pop_front();
  EXPECT_EQ(l.front().x, 20);
  l.pop_front();
  EXPECT_EQ(l.front().x, 30);
}

TEST(ListTest, CopyEmptyList) {
  s21::list<int> original;
  s21::list<int> copy(original);

  EXPECT_EQ(copy.size(), 0);
}

TEST(ListTest, CopyListWithElements) {
  s21::list<int> original{1, 2, 3, 4, 5};
  s21::list<int> copy(original);

  EXPECT_EQ(copy.size(), original.size());
  auto orig_iter = original.begin();
  auto copy_iter = copy.begin();
  for (size_t i = 0; i < original.size(); ++i, ++orig_iter, ++copy_iter) {
    EXPECT_EQ(*orig_iter, *copy_iter);
  }
}

TEST(ListTest, DeepCopyList) {
  s21::list<int> original{10, 20, 30};
  s21::list<int> copy(original);

  original.push_back(40);
  EXPECT_EQ(original.size(), 4);
  EXPECT_EQ(copy.size(), 3);

  EXPECT_EQ(copy.front(), 10);
  copy.pop_front();
  EXPECT_EQ(copy.front(), 20);
  copy.pop_front();
  EXPECT_EQ(copy.front(), 30);
}

TEST(ListTest, MoveEmptyList) {
  s21::list<int> original;
  s21::list<int> moved(std::move(original));

  EXPECT_EQ(moved.size(), 0);
  EXPECT_EQ(original.size(), 0);
}

TEST(ListTest, MoveListWithElements) {
  s21::list<int> original{1, 2, 3, 4, 5};
  s21::list<int> moved(std::move(original));

  EXPECT_EQ(moved.size(), 5);

  auto moved_iter = moved.begin();

  for (int i = 1; i < 6; ++i, ++moved_iter) {
    EXPECT_EQ(*moved_iter, i);
  }

  EXPECT_EQ(original.size(), 0);
}

TEST(ListTest, MoveListWithCustomObjects) {
  struct TestStruct {
    int value;
    TestStruct(int v) : value(v) {}
  };

  s21::list<TestStruct> original{{1}, {2}, {3}};
  s21::list<TestStruct> moved(std::move(original));

  EXPECT_EQ(moved.size(), 3);

  EXPECT_EQ(moved.front().value, 1);
  moved.pop_front();
  EXPECT_EQ(moved.front().value, 2);
  moved.pop_front();
  EXPECT_EQ(moved.front().value, 3);

  EXPECT_EQ(original.size(), 0);
}

TEST(ListTest, UniqueOnListWithoutDuplicates) {
  s21::list<int> l{1, 2, 3, 4, 5};
  l.unique();
  EXPECT_EQ(l.size(), 5);
  auto iter = l.begin();
  for (int i = 1; i < 6; ++i, ++iter) {
    EXPECT_EQ(*iter, i);
  }
}

TEST(ListTest, UniqueOnListWithConsecutiveDuplicates) {
  s21::list<int> l{1, 2, 2, 3, 4, 4, 4, 5};
  l.unique();
  EXPECT_EQ(l.size(), 5);

  auto iter = l.begin();
  for (int i = 1; i < 6; ++i, ++iter) {
    EXPECT_EQ(*iter, i);
  }
}

TEST(ListTest, UniqueOnListWithAllDuplicates) {
  s21::list<int> l{7, 7, 7, 7, 7};
  l.unique();
  EXPECT_EQ(l.size(), 1);
  EXPECT_EQ(l.front(), 7);
}

TEST(ListTest, SortAlreadySorted) {
  s21::list<int> l{1, 2, 3, 4, 5};
  l.sort();
  EXPECT_EQ(l.size(), 5);
  auto iter = l.begin();
  for (int i = 1; i < 6; ++i, ++iter) {
    EXPECT_EQ(*iter, i);
  }
}

TEST(ListTest, SortReverseOrder) {
  s21::list<int> l{5, 4, 3, 2, 1};
  l.sort();
  EXPECT_EQ(l.size(), 5);
  auto iter = l.begin();
  for (int i = 1; i < 6; ++i, ++iter) {
    EXPECT_EQ(*iter, i);
  }
}

TEST(ListTest, SortWithDuplicates) {
  s21::list<int> l{3, 1, 2, 3, 2};
  l.sort();
  EXPECT_EQ(l.size(), 5);
  EXPECT_EQ(l.front(), 1);
  l.pop_front();
  EXPECT_EQ(l.front(), 2);
  l.pop_front();
  EXPECT_EQ(l.front(), 2);
  l.pop_front();
  EXPECT_EQ(l.front(), 3);
  l.pop_front();
  EXPECT_EQ(l.front(), 3);
}

TEST(ListTest, InsertIntoEmptyList) {
  s21::list<int> l;
  auto it = l.insert(l.begin(), 42);

  EXPECT_EQ(l.size(), 1);
  EXPECT_EQ(*it, 42);
  EXPECT_EQ(l.begin(), it);
  EXPECT_EQ(l.end(), ++it);
}

TEST(ListTest, InsertAtBeginning) {
  s21::list<int> l{1, 2, 3};
  auto it = l.insert(l.begin(), 0);

  EXPECT_EQ(l.size(), 4);
  EXPECT_EQ(*it, 0);

  EXPECT_EQ(l.front(), 0);
  l.pop_front();
  EXPECT_EQ(l.front(), 1);
  l.pop_front();
  EXPECT_EQ(l.front(), 2);
  l.pop_front();
  EXPECT_EQ(l.front(), 3);
}

TEST(ListTest, InsertInMiddle) {
  s21::list<int> l{1, 3, 4};
  auto it = l.insert(++l.begin(), 2);

  EXPECT_EQ(l.size(), 4);
  EXPECT_EQ(*it, 2);
  auto iter = l.begin();
  for (int i = 1; i < 5; ++i, ++iter) {
    EXPECT_EQ(*iter, i);
  }
}

TEST(ListTest, EraseSingleElement) {
  s21::list<int> l{42};
  auto it = l.begin();
  l.erase(it);

  EXPECT_EQ(l.size(), 0);
  EXPECT_EQ(l.begin(), l.end());
}

TEST(ListTest, EraseFirstElement) {
  s21::list<int> l{1, 2, 3, 4};
  l.erase(l.begin());

  EXPECT_EQ(l.size(), 3);
  EXPECT_EQ(l.front(), 2);
  l.pop_front();
  EXPECT_EQ(l.front(), 3);
  l.pop_front();
  EXPECT_EQ(l.front(), 4);
}

TEST(ListTest, EraseMiddleElement) {
  s21::list<int> l{1, 2, 3, 4};
  auto it = ++l.begin();
  l.erase(it);

  EXPECT_EQ(l.size(), 3);

  EXPECT_EQ(l.front(), 1);
  l.pop_front();
  EXPECT_EQ(l.front(), 3);
  l.pop_front();
  EXPECT_EQ(l.front(), 4);
}

TEST(ListTest, EmptyOnEmptyList) {
  s21::list<int> l;
  EXPECT_TRUE(l.empty());
}

TEST(ListTest, EmptyOnNonEmptyList) {
  s21::list<int> l{1, 2, 3};
  EXPECT_FALSE(l.empty());
}

TEST(ListTest, EmptyAfterClearingList) {
  s21::list<int> l{1, 2, 3};
  l.erase(l.begin());
  l.erase(l.begin());
  l.erase(l.begin());
  EXPECT_TRUE(l.empty());
}

TEST(ListTest, InsertMany) {
  s21::list<int> l{1, 2, 3};
  l.insert_many(++l.cbegin(), 7, 8, 9);
  EXPECT_EQ(l.front(), 1);
  l.pop_front();
  EXPECT_EQ(l.front(), 7);
  l.pop_front();
  EXPECT_EQ(l.front(), 8);
  l.pop_front();
  EXPECT_EQ(l.front(), 9);
  l.pop_front();
  EXPECT_EQ(l.front(), 2);
  l.pop_front();
  EXPECT_EQ(l.front(), 3);
}

TEST(ListTest, InsertManyFront) {
  s21::list<int> l{1, 2, 3};
  l.insert_many_front(7, 8, 9);
  EXPECT_EQ(l.front(), 7);
  l.pop_front();
  EXPECT_EQ(l.front(), 8);
  l.pop_front();
  EXPECT_EQ(l.front(), 9);
  l.pop_front();
  EXPECT_EQ(l.front(), 1);
  l.pop_front();
  EXPECT_EQ(l.front(), 2);
  l.pop_front();
  EXPECT_EQ(l.front(), 3);
}

TEST(ListTest, InsertManyBack) {
  s21::list<int> l{1, 2, 3};
  l.insert_many_back(7, 8, 9);
  EXPECT_EQ(l.front(), 1);
  l.pop_front();
  EXPECT_EQ(l.front(), 2);
  l.pop_front();
  EXPECT_EQ(l.front(), 3);
  l.pop_front();
  EXPECT_EQ(l.front(), 7);
  l.pop_front();
  EXPECT_EQ(l.front(), 8);
  l.pop_front();
  EXPECT_EQ(l.front(), 9);
}

/*--------------------------VECTOR TESTS------------------------------*/

TEST(VectorTest, IntConstructorDefault) {
  s21::vector<int> vec;
  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec.capacity(), 0);
}

TEST(VectorTest, IntConstructorWithSize) {
  s21::vector<int> vec(5);
  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec.capacity(), 5);
}

TEST(VectorTest, IntInitializerListConstructor) {
  s21::vector<int> vec = {1, 2, 3, 4};
  EXPECT_EQ(vec.size(), 4);
  EXPECT_EQ(vec.capacity(), 8);
}

TEST(VectorTest, IntCopyConstructor) {
  s21::vector<int> vec1 = {1, 2, 3};
  s21::vector<int> vec2 = vec1;
  EXPECT_EQ(vec2.size(), 3);
  EXPECT_EQ(vec2.capacity(), 6);
  EXPECT_EQ(vec2[0], 1);
  EXPECT_EQ(vec2[1], 2);
  EXPECT_EQ(vec2[2], 3);
}

TEST(VectorTest, DoubleConstructorDefault) {
  s21::vector<double> vec;
  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec.capacity(), 0);
}

TEST(VectorTest, DoubleConstructorWithSize) {
  s21::vector<double> vec(3);
  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec.capacity(), 3);
}

TEST(VectorTest, DoubleInitializerListConstructor) {
  s21::vector<double> vec = {1.1, 2.2, 3.3};
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec.capacity(), 6);
}

TEST(VectorTest, DoubleMoveConstructor) {
  s21::vector<double> vec1 = {1.1, 2.2};
  s21::vector<double> vec2 = std::move(vec1);
  EXPECT_EQ(vec2.size(), 2);
  EXPECT_EQ(vec2.capacity(), 4);
  EXPECT_EQ(vec1.size(), 0);
}

TEST(VectorTest, StringConstructorDefault) {
  s21::vector<std::string> vec;
  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec.capacity(), 0);
}

TEST(VectorTest, StringConstructorWithSize) {
  s21::vector<std::string> vec(4);
  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec.capacity(), 4);
}

TEST(VectorTest, StringInitializerListConstructor) {
  s21::vector<std::string> vec = {"hello", "world"};
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec.capacity(), 4);
}

TEST(VectorTest, StringCopyConstructor) {
  s21::vector<std::string> vec1 = {"foo", "bar"};
  s21::vector<std::string> vec2 = vec1;
  EXPECT_EQ(vec2.size(), 2);
  EXPECT_EQ(vec2.capacity(), 4);
  EXPECT_EQ(vec2[0], "foo");
  EXPECT_EQ(vec2[1], "bar");
}

TEST(VectorTest, MoveAssignmentOperator) {
  s21::vector<int> vec1 = {1, 2, 3, 4};
  s21::vector<int> vec2;

  vec2 = std::move(vec1);

  EXPECT_EQ(vec2.size(), 4);
  EXPECT_EQ(vec2.capacity(), 8);
  EXPECT_EQ(vec2[0], 1);
  EXPECT_EQ(vec2[1], 2);
  EXPECT_EQ(vec2[2], 3);
  EXPECT_EQ(vec2[3], 4);

  EXPECT_EQ(vec1.size(), 0);
  EXPECT_EQ(vec1.capacity(), 0);
}

TEST(VectorTest, AtMethodValidIndex) {
  s21::vector<int> vec = {10, 20, 30};

  EXPECT_EQ(vec.at(0), 10);
  EXPECT_EQ(vec.at(1), 20);
  EXPECT_EQ(vec.at(2), 30);
}

TEST(VectorTest, AtMethodOutOfRange) {
  s21::vector<int> vec = {10, 20, 30};

  EXPECT_THROW(vec.at(3), std::out_of_range);
  EXPECT_THROW(vec.at(100), std::out_of_range);
}

TEST(VectorTest, SubscriptOperator) {
  s21::vector<std::string> vec = {"apple", "banana", "cherry"};

  EXPECT_EQ(vec[0], "apple");
  EXPECT_EQ(vec[1], "banana");
  EXPECT_EQ(vec[2], "cherry");

  vec[1] = "orange";
  EXPECT_EQ(vec[1], "orange");
}

TEST(VectorTest, FrontNonConst) {
  s21::vector<int> vec = {1, 2, 3};
  EXPECT_EQ(vec.front(), 1);
}

TEST(VectorTest, FrontNonConstModify) {
  s21::vector<int> vec = {10, 20, 30};
  vec.front() = 100;
  EXPECT_EQ(vec.front(), 100);
}

TEST(VectorTest, FrontSingleElement) {
  s21::vector<int> vec = {42};
  EXPECT_EQ(vec.front(), 42);
}

TEST(VectorTest, FrontConst) {
  const s21::vector<int> vec = {4, 5, 6};
  EXPECT_EQ(vec.front(), 4);
}

TEST(VectorTest, FrontConstSingleElement) {
  const s21::vector<int> vec = {99};
  EXPECT_EQ(vec.front(), 99);
}

TEST(VectorTest, FrontConstPreservesValue) {
  const s21::vector<int> vec = {7, 8, 9};
  EXPECT_EQ(vec.front(), 7);
}

TEST(VectorTest, BackNonConst) {
  s21::vector<int> vec = {1, 2, 3};
  EXPECT_EQ(vec.back(), 3);
}

TEST(VectorTest, BackNonConstModify) {
  s21::vector<int> vec = {10, 20, 30};
  vec.back() = 100;
  EXPECT_EQ(vec.back(), 100);
}

TEST(VectorTest, BackSingleElement) {
  s21::vector<int> vec = {42};
  EXPECT_EQ(vec.back(), 42);
}

TEST(VectorTest, BackConst) {
  const s21::vector<int> vec = {4, 5, 6};
  EXPECT_EQ(vec.back(), 6);
}

TEST(VectorTest, BackConstSingleElement) {
  const s21::vector<int> vec = {99};
  EXPECT_EQ(vec.back(), 99);
}

TEST(VectorTest, BackConstPreservesValue) {
  const s21::vector<int> vec = {7, 8, 9};
  EXPECT_EQ(vec.back(), 9);
}

TEST(VectorTest, DataNonConst) {
  s21::vector<int> vec = {10, 20, 30};
  int *dataPtr = vec.data();
  EXPECT_EQ(dataPtr[0], 10);
  EXPECT_EQ(dataPtr[1], 20);
  EXPECT_EQ(dataPtr[2], 30);
}

TEST(VectorTest, DataNonConstModify) {
  s21::vector<int> vec = {1, 2, 3};
  int *dataPtr = vec.data();
  dataPtr[1] = 100;
  EXPECT_EQ(vec[1], 100);
}

TEST(VectorTest, DataEmptyVector) {
  s21::vector<int> vec;
  EXPECT_EQ(vec.data(), nullptr);
}

TEST(VectorTest, DataNonNullForNonEmpty) {
  s21::vector<int> vec = {1};
  EXPECT_NE(vec.data(), nullptr);
}

TEST(VectorTest, DataConst) {
  const s21::vector<int> vec = {10, 20, 30};
  const int *dataPtr = vec.data();
  EXPECT_EQ(dataPtr[0], 10);
  EXPECT_EQ(dataPtr[1], 20);
  EXPECT_EQ(dataPtr[2], 30);
}

TEST(VectorTest, DataConstEmptyVector) {
  const s21::vector<int> vec;
  EXPECT_EQ(vec.data(), nullptr);
}

TEST(VectorTest, DataConstNonNullForNonEmpty) {
  const s21::vector<int> vec = {1};
  EXPECT_NE(vec.data(), nullptr);
}

TEST(VectorTest, DataConstPreservesValues) {
  const s21::vector<int> vec = {1, 2, 3};
  const int *dataPtr = vec.data();
  EXPECT_EQ(dataPtr[0], 1);
  EXPECT_EQ(dataPtr[1], 2);
  EXPECT_EQ(dataPtr[2], 3);
}

TEST(VectorTest, BeginIteratorNonConst) {
  s21::vector<int> vec = {10, 20, 30};
  auto it = vec.begin();
  EXPECT_EQ(*it, 10);
}

TEST(VectorTest, BeginIteratorModify) {
  s21::vector<int> vec = {10, 20, 30};
  auto it = vec.begin();
  *it = 100;
  EXPECT_EQ(*it, 100);
}

TEST(VectorTest, BeginEqualsEndOnEmptyVector) {
  s21::vector<int> vec;
  EXPECT_EQ(vec.begin(), vec.end());
}

TEST(VectorTest, BeginIteratorTraversal) {
  s21::vector<int> vec = {1, 2, 3, 4};
  auto it = vec.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it, 4);
}

TEST(VectorTest, EndIteratorNonConst) {
  s21::vector<int> vec = {10, 20, 30};
  auto it = vec.end();
  --it;
  EXPECT_EQ(*it, 30);
}

TEST(VectorTest, EndIteratorTraversalBackwards) {
  s21::vector<int> vec = {1, 2, 3};
  auto it = vec.end();
  --it;
  EXPECT_EQ(*it--, 3);
  EXPECT_EQ(*it--, 2);
  EXPECT_EQ(*it, 1);
}

TEST(VectorTest, EndIteratorComparison) {
  s21::vector<int> vec = {1, 2, 3};
  auto it = vec.begin();
  while (it != vec.end()) {
    ++it;
  }
  EXPECT_EQ(it, vec.end());
}

TEST(VectorTest, EndEqualsBeginOnEmptyVector) {
  s21::vector<int> vec;
  EXPECT_EQ(vec.end(), vec.begin());
}

TEST(VectorTest, CBeginConstIterator) {
  const s21::vector<int> vec = {1, 2, 3};
  auto it = vec.cbegin();
  EXPECT_EQ(*it, 1);
}

TEST(VectorTest, CEndConstIterator) {
  const s21::vector<int> vec = {1, 2, 3};
  auto it = vec.cend();
  --it;
  EXPECT_EQ(*it, 3);
}

TEST(VectorTest, CBeginCEndTraversal) {
  const s21::vector<int> vec = {5, 10, 15};
  auto it = vec.cbegin();
  EXPECT_EQ(*it++, 5);
  EXPECT_EQ(*it++, 10);
  EXPECT_EQ(*it, 15);
}

TEST(VectorTest, CEndEqualsCBeginOnEmptyVector) {
  const s21::vector<int> vec;
  EXPECT_EQ(vec.cend(), vec.cbegin());
}

TEST(VectorTest, EmptyOnEmptyVector) {
  s21::vector<int> vec;
  EXPECT_TRUE(vec.empty());
}

TEST(VectorTest, EmptyOnNonEmptyVector) {
  s21::vector<int> vec = {1, 2, 3};
  EXPECT_FALSE(vec.empty());
}

TEST(VectorTest, EmptyAfterPushBack) {
  s21::vector<int> vec;
  vec.push_back(1);
  EXPECT_FALSE(vec.empty());
}

TEST(VectorTest, EmptyAfterClear) {
  s21::vector<int> vec = {1, 2, 3};
  vec.clear();
  EXPECT_TRUE(vec.empty());
}

TEST(VectorTest, SizeEmptyVector) {
  s21::vector<int> vec;
  EXPECT_EQ(vec.size(), 0);
}

TEST(VectorTest, SizeAfterPushBack) {
  s21::vector<int> vec;
  vec.push_back(10);
  vec.push_back(20);
  EXPECT_EQ(vec.size(), 2);
}

TEST(VectorTest, SizeAfterClear) {
  s21::vector<int> vec = {1, 2, 3};
  vec.clear();
  EXPECT_EQ(vec.size(), 0);
}

TEST(VectorTest, SizeAfterReserve) {
  s21::vector<int> vec = {1, 2, 3};
  vec.reserve(100);
  EXPECT_EQ(vec.size(), 3);
}

TEST(VectorTest, MaxSize) {
  s21::vector<int> vec;
  EXPECT_GT(vec.max_size(), 0);
}

TEST(VectorTest, MaxSizeDifferentTypes) {
  s21::vector<int> vec_int;
  s21::vector<double> vec_double;
  EXPECT_GT(vec_int.max_size(), 0);
  EXPECT_GT(vec_double.max_size(), 0);
}

TEST(VectorTest, MaxSizeIsConstant) {
  s21::vector<int> vec = {1, 2, 3};
  std::size_t max_size_before = vec.max_size();
  vec.push_back(4);
  std::size_t max_size_after = vec.max_size();
  EXPECT_EQ(max_size_before, max_size_after);
}

TEST(VectorTest, MaxSizeLargeVector) {
  s21::vector<char> vec;
  EXPECT_GT(vec.max_size(), vec.size());
}

TEST(VectorTest, ReserveIncreaseCapacity) {
  s21::vector<int> vec;
  vec.reserve(10);
  EXPECT_GE(vec.capacity(), 10);
}

TEST(VectorTest, ReserveDoesNotDecreaseCapacity) {
  s21::vector<int> vec;
  vec.reserve(10);
  std::size_t capacity_before = vec.capacity();
  vec.reserve(5);
  EXPECT_EQ(vec.capacity(), capacity_before);
}

TEST(VectorTest, ReserveRetainsElements) {
  s21::vector<int> vec = {1, 2, 3};
  vec.reserve(10);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
}

TEST(VectorTest, ReserveDoesNotChangeSize) {
  s21::vector<int> vec = {1, 2, 3};
  vec.reserve(10);
  EXPECT_EQ(vec.size(), 3);
}

TEST(VectorTest, InitialCapacityEmptyVector) {
  s21::vector<int> vec;
  EXPECT_EQ(vec.capacity(), 0);
}

TEST(VectorTest, CapacityAfterPushBack) {
  s21::vector<int> vec;
  vec.push_back(10);
  vec.push_back(20);
  EXPECT_GE(vec.capacity(), 2);
}

TEST(VectorTest, CapacityAfterReserve) {
  s21::vector<int> vec;
  vec.reserve(100);
  EXPECT_GE(vec.capacity(), 100);
}

TEST(VectorTest, CapacityAfterClear) {
  s21::vector<int> vec = {1, 2, 3};
  vec.reserve(50);
  std::size_t capacity_before = vec.capacity();
  vec.clear();
  EXPECT_EQ(vec.capacity(), capacity_before);
}

TEST(VectorTest, ShrinkToFitReducesCapacity) {
  s21::vector<int> vec = {1, 2, 3};
  vec.reserve(10);
  vec.shrink_to_fit();
  EXPECT_EQ(vec.capacity(), vec.size());
}

TEST(VectorTest, ShrinkToFitRetainsElements) {
  s21::vector<int> vec = {1, 2, 3};
  vec.reserve(10);
  vec.shrink_to_fit();
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
}

TEST(VectorTest, ShrinkToFitEmptyVector) {
  s21::vector<int> vec;
  vec.shrink_to_fit();
  EXPECT_EQ(vec.capacity(), 0);
}

TEST(VectorTest, ShrinkToFitDoesNotIncreaseCapacity) {
  s21::vector<int> vec = {1, 2, 3};
  vec.shrink_to_fit();
  EXPECT_EQ(vec.capacity(), vec.size());
}

TEST(VectorTest, ClearEmptiesVector) {
  s21::vector<int> vec = {1, 2, 3};
  vec.clear();
  EXPECT_EQ(vec.size(), 0);
  EXPECT_TRUE(vec.empty());
}

TEST(VectorTest, ClearDoesNotChangeCapacity) {
  s21::vector<int> vec = {1, 2, 3};
  std::size_t capacity_before = vec.capacity();
  vec.clear();
  EXPECT_EQ(vec.capacity(), capacity_before);
}

TEST(VectorTest, ClearAndInsertAfterClear) {
  s21::vector<int> vec = {1, 2, 3};
  vec.clear();
  vec.push_back(4);
  vec.push_back(5);
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec[0], 4);
  EXPECT_EQ(vec[1], 5);
}

TEST(VectorTest, ClearOnEmptyVector) {
  s21::vector<int> vec;
  vec.clear();
  EXPECT_EQ(vec.size(), 0);
  EXPECT_TRUE(vec.empty());
}

TEST(VectorTest, InsertAtBegin) {
  s21::vector<int> vec = {2, 3, 4};
  vec.insert(vec.begin(), 1);
  EXPECT_EQ(vec.size(), 4);
  EXPECT_EQ(vec[0], 1);
}

TEST(VectorTest, InsertAtMiddle) {
  s21::vector<int> vec = {1, 2, 4, 5};
  vec.insert(vec.begin() + 2, 3);
  EXPECT_EQ(vec.size(), 5);
  EXPECT_EQ(vec[2], 3);
}

TEST(VectorTest, InsertAtEnd) {
  s21::vector<int> vec = {1, 2, 3};
  vec.insert(vec.end(), 4);
  EXPECT_EQ(vec.size(), 4);
  EXPECT_EQ(vec[3], 4);
}

TEST(VectorTest, InsertIncreasesCapacity) {
  s21::vector<int> vec = {1, 2, 3};
  vec.reserve(3);
  vec.insert(vec.end(), 4);
  EXPECT_GE(vec.capacity(), 6);
}

TEST(VectorTest, EraseFromMiddle) {
  s21::vector<int> vec = {1, 2, 3, 4, 5};
  vec.erase(vec.begin() + 2);
  EXPECT_EQ(vec.size(), 4);
  EXPECT_EQ(vec[2], 4);
}

TEST(VectorTest, EraseFromBegin) {
  s21::vector<int> vec = {1, 2, 3, 4};
  vec.erase(vec.begin());
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec[0], 2);
}

TEST(VectorTest, EraseFromEnd) {
  s21::vector<int> vec = {1, 2, 3, 4};
  vec.erase(vec.end() - 1);
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec[2], 3);
}

TEST(VectorTest, EraseOnEmptyVector) {
  s21::vector<int> vec;
  vec.erase(vec.begin());
  EXPECT_EQ(vec.size(), 0);
}

TEST(VectorTest, PushBackToEmptyVector) {
  s21::vector<int> vec;
  vec.push_back(1);
  EXPECT_EQ(vec.size(), 1);
  EXPECT_EQ(vec[0], 1);
}

TEST(VectorTest, PushBackIncreasesCapacity) {
  s21::vector<int> vec;
  vec.reserve(2);
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  EXPECT_GE(vec.capacity(), 4);
  EXPECT_EQ(vec.size(), 3);
}

TEST(VectorTest, PushBackMultipleElements) {
  s21::vector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
}

TEST(VectorTest, PushBackWithComplexObjects) {
  s21::vector<std::string> vec;
  vec.push_back("Hello");
  vec.push_back("World");
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec[0], "Hello");
  EXPECT_EQ(vec[1], "World");
}

TEST(VectorTest, PopBackFromVector) {
  s21::vector<int> vec = {1, 2, 3};
  vec.pop_back();
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec[1], 2);
}

TEST(VectorTest, PopBackSingleElement) {
  s21::vector<int> vec = {1};
  vec.pop_back();
  EXPECT_EQ(vec.size(), 0);
  EXPECT_TRUE(vec.empty());
}

TEST(VectorTest, PopBackFromEmptyVector) {
  s21::vector<int> vec;
  vec.pop_back();
  EXPECT_EQ(vec.size(), 0);
}

TEST(VectorTest, PopBackComplexObjects) {
  s21::vector<std::string> vec = {"Hello", "World"};
  vec.pop_back();
  EXPECT_EQ(vec.size(), 1);
  EXPECT_EQ(vec[0], "Hello");
}

TEST(VectorTest, SwapSameSize) {
  s21::vector<int> vec1 = {1, 2, 3};
  s21::vector<int> vec2 = {4, 5, 6};
  vec1.swap(vec2);
  EXPECT_EQ(vec1[0], 4);
  EXPECT_EQ(vec1[1], 5);
  EXPECT_EQ(vec1[2], 6);
  EXPECT_EQ(vec2[0], 1);
  EXPECT_EQ(vec2[1], 2);
  EXPECT_EQ(vec2[2], 3);
}

TEST(VectorTest, SwapDifferentSize) {
  s21::vector<int> vec1 = {1, 2, 3, 4};
  s21::vector<int> vec2 = {5, 6};
  vec1.swap(vec2);
  EXPECT_EQ(vec1.size(), 2);
  EXPECT_EQ(vec2.size(), 4);
  EXPECT_EQ(vec1[0], 5);
  EXPECT_EQ(vec2[0], 1);
}

TEST(VectorTest, SwapWithEmptyVector) {
  s21::vector<int> vec1 = {1, 2, 3};
  s21::vector<int> vec2;
  vec1.swap(vec2);
  EXPECT_TRUE(vec1.empty());
  EXPECT_EQ(vec2.size(), 3);
  EXPECT_EQ(vec2[0], 1);
}

TEST(VectorTest, SwapSelf) {
  s21::vector<int> vec = {1, 2, 3};
  vec.swap(vec);
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
}

TEST(VectorTest, InsertManyAtBegin) {
  s21::vector<int> vec = {3, 4};
  vec.insert_many(vec.cbegin(), 1, 2);
  EXPECT_EQ(vec.size(), 4);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
}

TEST(VectorTest, InsertManyInMiddle) {
  s21::vector<int> vec = {1, 2, 5, 6};
  vec.insert_many(vec.cbegin() + 2, 3, 4);
  EXPECT_EQ(vec.size(), 6);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
}

TEST(VectorTest, InsertManyAtEnd) {
  s21::vector<int> vec = {1, 2};
  vec.insert_many(vec.cend(), 3, 4);
  EXPECT_EQ(vec.size(), 4);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
}

TEST(VectorTest, InsertManyIntoEmptyVector) {
  s21::vector<int> vec;
  vec.insert_many(vec.cbegin(), 1, 2, 3);
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
}

TEST(VectorTest, InsertManyBack) {
  s21::vector<int> vec = {1, 2};
  vec.insert_many_back(3, 4, 5);
  EXPECT_EQ(vec.size(), 5);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 5);
}

TEST(VectorTest, InsertManyBackIntoEmptyVector) {
  s21::vector<int> vec;
  vec.insert_many_back(1, 2, 3);
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
}

TEST(VectorTest, InsertManyBackIncreasesCapacity) {
  s21::vector<int> vec = {1, 2};
  vec.reserve(3);
  vec.insert_many_back(3, 4);
  EXPECT_GE(vec.capacity(), 4);
  EXPECT_EQ(vec.size(), 4);
}

TEST(VectorTest, InsertManyBackComplexObjects) {
  s21::vector<std::string> vec;
  vec.insert_many_back("Hello", "World", "Test");
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec[0], "Hello");
  EXPECT_EQ(vec[1], "World");
  EXPECT_EQ(vec[2], "Test");
}

TEST(Stack, default_constructor) {
  std::stack<std::string> std_stack;
  s21::stack<std::string> s21_stack;
  EXPECT_EQ(std_stack.size(), s21_stack.size());
  EXPECT_EQ(std_stack.empty(), s21_stack.empty());
}

TEST(Stack, initializer_list_constructor) {
  std::stack<int> std_stack;
  for (auto i : {1, 54, 654654, 423, 42, 453, 654, 21, 0, -232, 4324, -432}) {
    std_stack.push(i);
  }
  s21::stack<int> s21_stack{1,   54, 654654, 423,  42,   453,
                            654, 21, 0,      -232, 4324, -432};

  EXPECT_EQ(std_stack.top(), s21_stack.top());
  EXPECT_EQ(std_stack.size(), s21_stack.size());
}

TEST(Stack, copy_constructor) {
  std::stack<int> std_stack;
  s21::stack<int> s21_stack;
  for (auto i : {1, 0, -232, 4324, -432}) {
    std_stack.push(i);
    s21_stack.push(i);
  }
  s21::stack<int> s21_stack_copy(s21_stack);
  std::stack<int> std_stack_copy(std_stack);
  EXPECT_EQ(std_stack_copy.top(), s21_stack_copy.top());
  EXPECT_EQ(std_stack_copy.size(), s21_stack_copy.size());
}

TEST(Stack, copy_operator) {
  std::stack<int> std_stack;
  s21::stack<int> s21_stack;
  for (auto i : {1, 0, -232, 4324, -432}) {
    std_stack.push(i);
    s21_stack.push(i);
  }
  s21::stack<int> s21_stack_copy{1, 2, 3};
  s21_stack_copy = s21_stack;
  std::stack<int> std_stack_copy;
  std_stack_copy = std_stack;
  EXPECT_EQ(std_stack_copy.top(), s21_stack_copy.top());
  EXPECT_EQ(std_stack_copy.size(), s21_stack_copy.size());
}

TEST(Stack, move_constructor) {
  std::stack<int> std_stack;
  s21::stack<int> s21_stack;
  for (auto i : {1, 0, -232, 4324, -432}) {
    std_stack.push(i);
    s21_stack.push(i);
  }
  s21::stack<int> s21_stack_moved(std::move(s21_stack));
  std::stack<int> std_stack_moved(std::move(std_stack));
  EXPECT_EQ(std_stack.empty(), s21_stack.empty());
  EXPECT_EQ(std_stack_moved.top(), s21_stack_moved.top());
  EXPECT_EQ(std_stack_moved.size(), s21_stack_moved.size());
}

TEST(Stack, move_operator) {
  std::stack<int> std_stack;
  s21::stack<int> s21_stack;
  for (auto i : {1, 0, -232, 4324, -432}) {
    std_stack.push(i);
    s21_stack.push(i);
  }
  s21::stack<int> s21_stack_moved{1, 2, 3};
  s21_stack_moved = std::move(s21_stack);
  std::stack<int> std_stack_moved;
  std_stack_moved = std::move(std_stack);
  EXPECT_EQ(std_stack.empty(), s21_stack.empty());
  EXPECT_EQ(std_stack_moved.top(), s21_stack_moved.top());
  EXPECT_EQ(std_stack_moved.size(), s21_stack_moved.size());
}

TEST(Stack, data_without_default_constructor) {
  struct data {
    int x_;
    data() = delete;
    data(int x) : x_(x) {}
  };

  std::stack<data> std_stack;
  s21::stack<data> s21_stack;

  for (auto i : {1, 0, -232, 4324, -432}) {
    std_stack.push(i);
    s21_stack.push(i);
  }

  EXPECT_EQ(std_stack.top().x_, s21_stack.top().x_);
  EXPECT_EQ(std_stack.size(), s21_stack.size());
}

TEST(Stack, top) {
  std::stack<int> std_stack_int;
  s21::stack<int> s21_stack_int;
  for (auto i : {1, 54, 654654, 423, 42, 453, 654, 21, 0, -232, 4324, -432}) {
    std_stack_int.push(i);
    s21_stack_int.push(i);
    EXPECT_EQ(std_stack_int.top(), s21_stack_int.top());
    EXPECT_EQ(std_stack_int.size(), s21_stack_int.size());
  }

  std::stack<std::string> std_stack_str;
  s21::stack<std::string> s21_stack_str;
  for (auto i : {"abc", "fdsaf", "eqwe23d", "!eq32-+2312", "0_0"}) {
    std_stack_str.push(i);
    s21_stack_str.push(i);
    EXPECT_EQ(std_stack_str.top(), s21_stack_str.top());
    EXPECT_EQ(std_stack_str.size(), s21_stack_str.size());
  }

  std::vector<int> a{1, 2, 3};
  std::vector<int> b{32, 213, 43};
  std::vector<int> c{432423, 213, -321312};
  std::stack<std::vector<int>> std_stack_vector;
  s21::stack<std::vector<int>> s21_stack_vector;
  for (auto i : {a, b, c}) {
    std_stack_vector.push(i);
    s21_stack_vector.push(i);
    EXPECT_EQ(*(std_stack_vector.top().end() - 1),
              *(s21_stack_vector.top().end() - 1));
    EXPECT_EQ(std_stack_vector.size(), s21_stack_vector.size());
  }
}

TEST(Stack, empty) {
  std::stack<int> std_stack_int;
  s21::stack<int> s21_stack_int;
  for (auto i : {1, 54, 654654, 423, 42, 453, 654, 21, 0, -232, 4324, -432}) {
    std_stack_int.push(i);
    s21_stack_int.push(i);
    std_stack_int.pop();
    s21_stack_int.pop();
    EXPECT_EQ(std_stack_int.empty(), s21_stack_int.empty());
    EXPECT_EQ(std_stack_int.size(), s21_stack_int.size());
  }

  std::stack<std::string> std_stack_str;
  s21::stack<std::string> s21_stack_str;
  for (auto i : {"abc", "fdsaf", "eqwe23d", "!eq32-+2312", "0_0"}) {
    std_stack_str.push(i);
    s21_stack_str.push(i);
    std_stack_str.pop();
    s21_stack_str.pop();
    EXPECT_EQ(std_stack_str.empty(), s21_stack_str.empty());
    EXPECT_EQ(std_stack_str.size(), s21_stack_str.size());
  }

  std::vector<int> a{1, 2, 3};
  std::vector<int> b{32, 213, 43};
  std::vector<int> c{432423, 213, -321312};
  std::stack<std::vector<int>> std_stack_vector;
  s21::stack<std::vector<int>> s21_stack_vector;
  for (auto i : {a, b, c}) {
    std_stack_vector.push(i);
    s21_stack_vector.push(i);
    std_stack_vector.pop();
    s21_stack_vector.pop();
    EXPECT_EQ(std_stack_vector.empty(), s21_stack_vector.empty());
    EXPECT_EQ(std_stack_vector.size(), s21_stack_vector.size());
  }
}

TEST(Stack, pop) {
  std::stack<int> std_stack_int;
  s21::stack<int> s21_stack_int;
  for (auto i : {1, 54, 654654, 423, 42, 453, 654, 21, 0, -232, 4324, -432}) {
    std_stack_int.push(i);
    s21_stack_int.push(i);
    EXPECT_EQ(std_stack_int.size(), s21_stack_int.size());
  }

  std::stack<std::string> std_stack_str;
  s21::stack<std::string> s21_stack_str;
  for (auto i : {"abc", "fdsaf", "eqwe23d", "!eq32-+2312", "0_0"}) {
    std_stack_str.push(i);
    s21_stack_str.push(i);
    EXPECT_EQ(std_stack_str.size(), s21_stack_str.size());
  }

  std::vector<int> a{1, 2, 3};
  std::vector<int> b{32, 213, 43};
  std::vector<int> c{432423, 213, -321312};
  std::stack<std::vector<int>> std_stack_vector;
  s21::stack<std::vector<int>> s21_stack_vector;
  for (auto i : {a, b, c}) {
    std_stack_vector.push(i);
    s21_stack_vector.push(i);
    EXPECT_EQ(std_stack_vector.size(), s21_stack_vector.size());
  }

  for (auto i = 0; i < 2; ++i) {
    std_stack_int.pop();
    s21_stack_int.pop();
    std_stack_str.pop();
    s21_stack_str.pop();
    std_stack_vector.pop();
    s21_stack_vector.pop();
  }

  EXPECT_EQ(std_stack_int.top(), s21_stack_int.top());
  EXPECT_EQ(std_stack_int.size(), s21_stack_int.size());
  EXPECT_EQ(std_stack_int.top(), s21_stack_int.top());
  EXPECT_EQ(std_stack_int.size(), s21_stack_int.size());
  EXPECT_EQ(*(std_stack_vector.top().end() - 1),
            *(s21_stack_vector.top().end() - 1));
  EXPECT_EQ(std_stack_vector.size(), s21_stack_vector.size());
}

TEST(Stack, huge_num_of_elems) {
  std::stack<int> std_stack;
  s21::stack<int> s21_stack;
  for (int i = 0; i < 3000; ++i) {
    std_stack.push(i);
    s21_stack.push(i);
  }

  for (int i = 0; i < 1500; ++i) {
    std_stack.pop();
    s21_stack.pop();
  }

  EXPECT_EQ(std_stack.top(), s21_stack.top());
  EXPECT_EQ(std_stack.size(), s21_stack.size());
}

TEST(Stack, swap) {
  std::stack<int> std_stack;
  s21::stack<int> s21_stack;
  s21::stack<int> s21_stack2 = {1, 2, 4324, 432};
  for (auto i : {1, 54, 654654, 423, 42, 453, 654, 21, 0, -232, 4324, -432}) {
    std_stack.push(i);
    s21_stack.push(i);
  }
  s21_stack2.swap(s21_stack);

  EXPECT_EQ(std_stack.top(), s21_stack2.top());
  EXPECT_EQ(std_stack.size(), s21_stack2.size());
}

TEST(Stack, insert_many_front) {
  std::stack<int> std_stack;
  s21::stack<int> s21_stack;

  for (auto i : {1, 54, 654654, 423, 42, 453, 654, 21, 0, -232, 4324, -432}) {
    std_stack.push(i);
    s21_stack.push(i);
  }

  s21_stack.insert_many_front(2);
  std_stack.push(2);
  EXPECT_EQ(std_stack.top(), s21_stack.top());
  EXPECT_EQ(std_stack.size(), s21_stack.size());

  s21_stack.insert_many_front(10, 2, 4, 5, 21, 3, 4, 5);
  EXPECT_EQ(5, s21_stack.top());
  EXPECT_EQ(std_stack.size() + 8, s21_stack.size());
}

TEST(Queue, default_constructor) {
  std::queue<std::string> std_queue;
  s21::queue<std::string> s21_queue;
  EXPECT_EQ(std_queue.size(), s21_queue.size());
  EXPECT_EQ(std_queue.empty(), s21_queue.empty());
}

TEST(Queue, initializer_list_constructor) {
  std::queue<int> std_queue;
  for (auto i : {1, 54, 654654, 423, 42, 453, 654, 21, 0, -232, 4324, -432}) {
    std_queue.push(i);
  }
  s21::queue<int> s21_queue{1,   54, 654654, 423,  42,   453,
                            654, 21, 0,      -232, 4324, -432};

  EXPECT_EQ(std_queue.front(), s21_queue.front());
  EXPECT_EQ(std_queue.back(), s21_queue.back());
  EXPECT_EQ(std_queue.size(), s21_queue.size());
}

TEST(Queue, copy_constructor) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  for (auto i : {1, 0, -232, 4324, -432}) {
    std_queue.push(i);
    s21_queue.push(i);
  }
  s21::queue<int> s21_queue_copy(s21_queue);
  std::queue<int> std_queue_copy(std_queue);
  EXPECT_EQ(std_queue_copy.front(), s21_queue_copy.front());
  EXPECT_EQ(std_queue_copy.back(), s21_queue_copy.back());
  EXPECT_EQ(std_queue_copy.size(), s21_queue_copy.size());
}

TEST(Queue, copy_operator) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  for (auto i : {1, 0, -232, 4324, -432}) {
    std_queue.push(i);
    s21_queue.push(i);
  }
  s21::queue<int> s21_queue_copy{1, 2, 3};
  s21_queue_copy = s21_queue;
  std::queue<int> std_queue_copy;
  std_queue_copy = std_queue;
  EXPECT_EQ(std_queue_copy.front(), s21_queue_copy.front());
  EXPECT_EQ(std_queue_copy.back(), s21_queue_copy.back());
  EXPECT_EQ(std_queue_copy.size(), s21_queue_copy.size());
}

TEST(Queue, move_constructor) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  for (auto i : {1, 0, -232, 4324, -432}) {
    std_queue.push(i);
    s21_queue.push(i);
  }
  s21::queue<int> s21_queue_moved(std::move(s21_queue));
  std::queue<int> std_queue_moved(std::move(std_queue));
  EXPECT_EQ(std_queue_moved.front(), s21_queue_moved.front());
  EXPECT_EQ(std_queue_moved.back(), s21_queue_moved.back());
  EXPECT_EQ(std_queue_moved.size(), s21_queue_moved.size());
  EXPECT_EQ(std_queue.size(), s21_queue.size());
}

TEST(Queue, move_operator) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  for (auto i : {1, 0, -232, 4324, -432}) {
    std_queue.push(i);
    s21_queue.push(i);
  }
  s21::queue<int> s21_queue_moved{1, 2, 3};
  s21_queue_moved = std::move(s21_queue);
  std::queue<int> std_queue_moved;
  std_queue_moved = std::move(std_queue);
  EXPECT_EQ(std_queue_moved.front(), s21_queue_moved.front());
  EXPECT_EQ(std_queue_moved.back(), s21_queue_moved.back());
  EXPECT_EQ(std_queue_moved.size(), s21_queue_moved.size());
  EXPECT_EQ(std_queue.size(), s21_queue.size());
}

TEST(Queue, data_without_default_constructor) {
  struct data {
    int x_;
    data() = delete;
    data(int x) : x_(x) {}
  };

  std::queue<data> std_queue;
  s21::queue<data> s21_queue;

  for (auto i : {1, 0, -232, 4324, -432}) {
    std_queue.push(i);
    s21_queue.push(i);
  }

  EXPECT_EQ(std_queue.front().x_, s21_queue.front().x_);
  EXPECT_EQ(std_queue.back().x_, s21_queue.back().x_);
  EXPECT_EQ(std_queue.size(), s21_queue.size());
}

TEST(Queue, front_back) {
  std::queue<int> std_queue_int;
  s21::queue<int> s21_queue_int;
  for (auto i : {1, 54, 654654, 423, 42, 453, 654, 21, 0, -232, 4324, -432}) {
    std_queue_int.push(i);
    s21_queue_int.push(i);
    EXPECT_EQ(std_queue_int.front(), s21_queue_int.front());
    EXPECT_EQ(std_queue_int.back(), s21_queue_int.back());
    EXPECT_EQ(std_queue_int.size(), s21_queue_int.size());
  }

  std::queue<std::string> std_queue_str;
  s21::queue<std::string> s21_queue_str;
  for (auto i : {"abc", "fdsaf", "eqwe23d", "!eq32-+2312", "0_0"}) {
    std_queue_str.push(i);
    s21_queue_str.push(i);
    EXPECT_EQ(std_queue_str.front(), s21_queue_str.front());
    EXPECT_EQ(std_queue_str.back(), s21_queue_str.back());
    EXPECT_EQ(std_queue_str.size(), s21_queue_str.size());
  }

  std::vector<int> a{1, 2, 3};
  std::vector<int> b{32, 213, 43};
  std::vector<int> c{432423, 213, -321312};
  std::queue<std::vector<int>> std_queue_vector;
  s21::queue<std::vector<int>> s21_queue_vector;
  for (auto i : {a, b, c}) {
    std_queue_vector.push(i);
    s21_queue_vector.push(i);
    EXPECT_EQ(*(std_queue_vector.front().end() - 1),
              *(s21_queue_vector.front().end() - 1));
    EXPECT_EQ(*(std_queue_vector.back().end() - 1),
              *(s21_queue_vector.back().end() - 1));
    EXPECT_EQ(std_queue_vector.size(), s21_queue_vector.size());
  }
}

TEST(Queue, empty) {
  std::queue<int> std_queue_int;
  s21::queue<int> s21_queue_int;
  for (auto i : {1, 54, 654654, 423, 42, 453, 654, 21, 0, -232, 4324, -432}) {
    std_queue_int.push(i);
    s21_queue_int.push(i);
    std_queue_int.pop();
    s21_queue_int.pop();
    EXPECT_EQ(std_queue_int.empty(), s21_queue_int.empty());
    EXPECT_EQ(std_queue_int.size(), s21_queue_int.size());
  }

  std::queue<std::string> std_queue_str;
  s21::queue<std::string> s21_queue_str;
  for (auto i : {"abc", "fdsaf", "eqwe23d", "!eq32-+2312", "0_0"}) {
    std_queue_str.push(i);
    s21_queue_str.push(i);
    std_queue_str.pop();
    s21_queue_str.pop();
    EXPECT_EQ(std_queue_str.empty(), s21_queue_str.empty());
    EXPECT_EQ(std_queue_str.size(), s21_queue_str.size());
  }

  std::vector<int> a{1, 2, 3};
  std::vector<int> b{32, 213, 43};
  std::vector<int> c{432423, 213, -321312};
  std::queue<std::vector<int>> std_queue_vector;
  s21::queue<std::vector<int>> s21_queue_vector;
  for (auto i : {a, b, c}) {
    std_queue_vector.push(i);
    s21_queue_vector.push(i);
    std_queue_vector.pop();
    s21_queue_vector.pop();
    EXPECT_EQ(std_queue_vector.empty(), s21_queue_vector.empty());
    EXPECT_EQ(std_queue_vector.size(), s21_queue_vector.size());
  }
}

TEST(Queue, pop) {
  std::queue<int> std_queue_int;
  s21::queue<int> s21_queue_int;
  for (auto i : {1, 54, 654654, 423, 42, 453, 654, 21, 0, -232, 4324, -432}) {
    std_queue_int.push(i);
    s21_queue_int.push(i);
    EXPECT_EQ(std_queue_int.size(), s21_queue_int.size());
  }

  std::queue<std::string> std_queue_str;
  s21::queue<std::string> s21_queue_str;
  for (auto i : {"abc", "fdsaf", "eqwe23d", "!eq32-+2312", "0_0"}) {
    std_queue_str.push(i);
    s21_queue_str.push(i);
    EXPECT_EQ(std_queue_str.size(), s21_queue_str.size());
  }

  std::vector<int> a{1, 2, 3};
  std::vector<int> b{32, 213, 43};
  std::vector<int> c{432423, 213, -321312};
  std::queue<std::vector<int>> std_queue_vector;
  s21::queue<std::vector<int>> s21_queue_vector;
  for (auto i : {a, b, c}) {
    std_queue_vector.push(i);
    s21_queue_vector.push(i);
    EXPECT_EQ(std_queue_vector.size(), s21_queue_vector.size());
  }
  for (auto i = 0; i < 2; ++i) {
    std_queue_int.pop();
    s21_queue_int.pop();
    std_queue_str.pop();
    s21_queue_str.pop();
    std_queue_vector.pop();
    s21_queue_vector.pop();
  }

  EXPECT_EQ(std_queue_int.front(), s21_queue_int.front());
  EXPECT_EQ(std_queue_int.back(), s21_queue_int.back());
  EXPECT_EQ(std_queue_str.front(), s21_queue_str.front());
  EXPECT_EQ(std_queue_str.back(), s21_queue_str.back());
  EXPECT_EQ(*(std_queue_vector.front().end() - 1),
            *(s21_queue_vector.front().end() - 1));
  EXPECT_EQ(*(std_queue_vector.back().end() - 1),
            *(s21_queue_vector.back().end() - 1));
}

TEST(Queue, swap) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  s21::queue<int> s21_queue2 = {1, 2, 4324, 432};
  for (auto i : {1, 54, 654654, 423, 42, 453, 654, 21, 0, -232, 4324, -432}) {
    std_queue.push(i);
    s21_queue.push(i);
  }
  s21_queue2.swap(s21_queue);

  EXPECT_EQ(std_queue.front(), s21_queue2.front());
  EXPECT_EQ(std_queue.back(), s21_queue2.back());
  EXPECT_EQ(std_queue.size(), s21_queue2.size());
}

TEST(Queue, huge_num_of_elems) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  for (int i = 0; i < 3000; ++i) {
    std_queue.push(i);
    s21_queue.push(i);
  }

  for (int i = 0; i < 1500; ++i) {
    std_queue.pop();
    s21_queue.pop();
  }

  EXPECT_EQ(std_queue.front(), s21_queue.front());
  EXPECT_EQ(std_queue.back(), s21_queue.back());
  EXPECT_EQ(std_queue.size(), s21_queue.size());
}

TEST(Queue, insert_many_back) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;

  for (auto i : {1, 54, 654654, 423, 42, 453, 654, 21, 0, -232, 4324, -432}) {
    std_queue.push(i);
    s21_queue.push(i);
  }

  s21_queue.insert_many_back(2);
  std_queue.push(2);
  EXPECT_EQ(std_queue.front(), s21_queue.front());
  EXPECT_EQ(std_queue.back(), s21_queue.back());
  EXPECT_EQ(std_queue.size(), s21_queue.size());

  s21_queue.insert_many_back(10, 2, 4, 5, 21, 3, 4, 5);
  EXPECT_EQ(5, s21_queue.back());
  EXPECT_EQ(std_queue.size() + 8, s21_queue.size());
}

TEST(Set, default_constructor) {
  s21::set<int> s21_set;
  std::set<int> std_set;

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
  EXPECT_EQ(s21_set.begin(), s21_set.end());
}

TEST(Set, initializer_list_constructor) {
  s21::set<int> s21_set = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                           4, 423, 4, 32, 5, 345623, 4, 12, 3};
  std::set<int> std_set = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                           4, 423, 4, 32, 5, 345623, 4, 12, 3};

  auto std_it = std_set.begin();

  for (auto i : s21_set) {
    EXPECT_EQ(*(std_it++), i);
  }

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
}

TEST(Set, copy_constructor) {
  s21::set<int> s21_set = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                           4, 423, 4, 32, 5, 345623, 4, 12, 3};
  std::set<int> std_set = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                           4, 423, 4, 32, 5, 345623, 4, 12, 3};

  s21::set<int> s21_set_copy(s21_set);
  std::set<int> std_set_copy(std_set);

  auto std_it = std_set_copy.begin();

  for (auto i : s21_set_copy) {
    EXPECT_EQ(*(std_it++), i);
  }

  EXPECT_EQ(s21_set_copy.size(), std_set_copy.size());
  EXPECT_EQ(s21_set_copy.size(), s21_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
}

TEST(Set, copy_operator) {
  s21::set<int> s21_set = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                           4, 423, 4, 32, 5, 345623, 4, 12, 3};
  std::set<int> std_set = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                           4, 423, 4, 32, 5, 345623, 4, 12, 3};

  s21::set<int> s21_set_copy = {12, 9432, 432, 432};
  std::set<int> std_set_copy = {12, 9432, 432, 432};

  s21_set_copy = s21_set;
  std_set_copy = std_set;

  auto std_it = std_set_copy.begin();

  for (auto i : s21_set_copy) {
    EXPECT_EQ(*(std_it++), i);
  }

  EXPECT_EQ(s21_set_copy.size(), std_set_copy.size());
  EXPECT_EQ(s21_set_copy.size(), s21_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
}

TEST(Set, move_constructor) {
  s21::set<int> s21_set = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                           4, 423, 4, 32, 5, 345623, 4, 12, 3};
  std::set<int> std_set = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                           4, 423, 4, 32, 5, 345623, 4, 12, 3};

  s21::set<int> s21_set_copy(std::move(s21_set));
  std::set<int> std_set_copy(std::move(std_set));

  auto std_it = std_set_copy.begin();

  for (auto i : s21_set_copy) {
    EXPECT_EQ(*(std_it++), i);
  }

  EXPECT_EQ(s21_set_copy.size(), std_set_copy.size());
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
}

TEST(Set, move_operator) {
  s21::set<int> s21_set = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                           4, 423, 4, 32, 5, 345623, 4, 12, 3};
  std::set<int> std_set = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                           4, 423, 4, 32, 5, 345623, 4, 12, 3};

  s21::set<int> s21_set_copy = {12, 9432, 432, 432};
  std::set<int> std_set_copy = {12, 9432, 432, 432};

  s21_set_copy = std::move(s21_set);
  std_set_copy = std::move(std_set);

  auto std_it = std_set_copy.begin();

  for (auto i : s21_set_copy) {
    EXPECT_EQ(*(std_it++), i);
  }

  EXPECT_EQ(s21_set_copy.size(), std_set_copy.size());
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
}

TEST(Set, iterator) {
  s21::set<int> s21_set = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                           4, 423, 4, 32, 5, 345623, 4, 12, 3};
  std::set<int> std_set = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                           4, 423, 4, 32, 5, 345623, 4, 12, 3};

  const s21::set<int> s21_set_const = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                       4, 423, 4, 32, 5, 345623, 4, 12, 3};
  const std::set<int> std_set_const = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                       4, 423, 4, 32, 5, 345623, 4, 12, 3};

  auto std_it_beg = std_set.begin();
  auto std_it_end = --std_set.end();

  for (s21::set<int>::set_iterator i = s21_set.begin(); i != s21_set.end();
       i++) {
    EXPECT_EQ(*(std_it_beg++), (*i));
  }

  for (s21::set<int>::set_iterator i = --s21_set.end(); i != s21_set.begin();
       i--) {
    EXPECT_EQ(*(std_it_end--), (*i));
  }

  auto std_it_beg_const = std_set_const.begin();
  auto std_it_end_const = --std_set_const.end();

  for (s21::set<int>::const_set_iterator i = s21_set_const.begin();
       i != s21_set_const.end(); i++) {
    EXPECT_EQ(*(std_it_beg_const++), (*i));
  }

  for (s21::set<int>::const_set_iterator i = --s21_set_const.end();
       i != s21_set_const.begin(); i--) {
    EXPECT_EQ(*(std_it_end_const--), (*i));
  }
}

TEST(Set, empty) {
  s21::set<int> s21_set;
  std::set<int> std_set;

  EXPECT_EQ(s21_set.empty(), std_set.empty());

  s21_set.insert(234);
  std_set.insert(234);

  EXPECT_EQ(s21_set.empty(), std_set.empty());
}

TEST(Set, size) {
  s21::set<int> s21_set;
  std::set<int> std_set;

  EXPECT_EQ(s21_set.size(), std_set.size());

  s21_set.insert(234);
  std_set.insert(234);

  EXPECT_EQ(s21_set.size(), std_set.size());

  s21_set.insert(234);
  std_set.insert(234);
  s21_set.insert(2314);
  std_set.insert(2314);

  EXPECT_EQ(s21_set.size(), std_set.size());
}

TEST(Set, max_size) {
  s21::set<int> s21_set;
  std::set<int> std_set;
  EXPECT_EQ(s21_set.max_size(), std_set.max_size());
}

TEST(Set, clear) {
  s21::set<int> s21_set = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                           4, 423, 4, 32, 5, 345623, 4, 12, 3};
  std::set<int> std_set = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                           4, 423, 4, 32, 5, 345623, 4, 12, 3};
  s21_set.clear();
  std_set.clear();
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.begin(), s21_set.end());
}

TEST(Set, insert) {
  s21::set<int> s21_set;
  std::set<int> std_set;
  auto s21_result = s21_set.insert(9);
  auto std_result = std_set.insert(9);
  EXPECT_EQ(s21_result.second, std_result.second);
  EXPECT_EQ(*s21_result.first, *std_result.first);

  s21_result = s21_set.insert(500);
  std_result = std_set.insert(500);
  EXPECT_EQ(s21_result.second, std_result.second);
  EXPECT_EQ(*s21_result.first, *std_result.first);

  s21_result = s21_set.insert(97988984);
  std_result = std_set.insert(97988984);
  EXPECT_EQ(s21_result.second, std_result.second);
  EXPECT_EQ(*s21_result.first, *std_result.first);
  EXPECT_EQ(s21_set.size(), std_set.size());
}

TEST(Set, erase) {
  s21::set<int> s21_set = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                           4, 423, 4, 32, 5, 345623, 4, 12, 3};
  std::set<int> std_set = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                           4, 423, 4, 32, 5, 345623, 4, 12, 3};

  for (int i = 0; i < 10; ++i) {
    if (i % 2 == 0) {
      s21_set.erase(s21_set.begin());
      std_set.erase(std_set.begin());
    } else if (i % 3 == 0) {
      s21_set.erase(--s21_set.end());
      std_set.erase(--std_set.end());
    }
  }

  auto std_iter = std_set.begin();
  for (auto i : s21_set) {
    EXPECT_EQ(*(std_iter++), i);
  }
  EXPECT_EQ(s21_set.size(), std_set.size());
}

TEST(Set, swap) {
  s21::set<int> s21_set = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                           4, 423, 4, 32, 5, 345623, 4, 12, 3};
  std::set<int> std_set = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                           4, 423, 4, 32, 5, 345623, 4, 12, 3};

  s21::set<int> s21_set_other = {9,  8, 1, 4, 1337, 12, 15648,
                                 54, 1, 2, 5, 8489, 4};
  std::set<int> std_set_other = {9,  8, 1, 4, 1337, 12, 15648,
                                 54, 1, 2, 5, 8489, 4};

  s21_set.swap(s21_set_other);
  std_set.swap(std_set_other);

  auto std_iter = std_set.begin();
  for (auto i : s21_set) {
    EXPECT_EQ(*(std_iter++), i);
  }

  auto std_iter_other = std_set_other.begin();
  for (auto i : s21_set_other) {
    EXPECT_EQ(*(std_iter_other++), i);
  }

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set_other.size(), std_set_other.size());
}

TEST(Set, merge) {
  s21::set<int> s21_set = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                           4, 423, 4, 32, 5, 345623, 4, 12, 3};
  std::set<int> std_set = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                           4, 423, 4, 32, 5, 345623, 4, 12, 3};

  s21::set<int> s21_set_other = {9,  8, 1, 4, 1337, 12, 15648,
                                 54, 1, 2, 5, 8489, 4};
  std::set<int> std_set_other = {9,  8, 1, 4, 1337, 12, 15648,
                                 54, 1, 2, 5, 8489, 4};

  s21_set.merge(s21_set_other);
  std_set.merge(std_set_other);

  auto std_iter = std_set.begin();
  for (auto i : s21_set) {
    EXPECT_EQ(*(std_iter++), i);
  }

  auto std_iter_other = std_set_other.begin();
  for (auto i : s21_set_other) {
    EXPECT_EQ(*(std_iter_other++), i);
  }

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set_other.size(), std_set_other.size());
}

TEST(Set, find) {
  s21::set<int> s21_set = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                           4, 423, 4, 32, 5, 345623, 4, 12, 3};
  std::set<int> std_set = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                           4, 423, 4, 32, 5, 345623, 4, 12, 3};

  EXPECT_EQ((*s21_set.find(743)) == 743, (*std_set.find(743)) == 743);
  EXPECT_EQ(s21_set.find(894519) == s21_set.end(),
            std_set.find(894519) == std_set.end());
}

TEST(Set, contains) {
  s21::set<int> s21_set = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                           4, 423, 4, 32, 5, 345623, 4, 12, 3};

  EXPECT_EQ(s21_set.contains(743), true);
  EXPECT_EQ(s21_set.contains(1), true);
  EXPECT_EQ(s21_set.contains(9871415), false);
}

TEST(Set, insert_many) {
  std::set<int> std_set = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                           4, 423, 4, 32, 5, 345623, 4, 12, 3};
  s21::set<int> s21_set;
  auto result = s21_set.insert_many(1, 1, 1, 1, 2, 3, 4, 5, 6, 743, 4, 423, 4,
                                    32, 5, 345623, 4, 12, 3);

  auto std_iter = std_set.begin();
  for (auto i : s21_set) {
    EXPECT_EQ(*(std_iter++), i);
  }
  int check_count = 0;
  for (auto pair : result) {
    if (pair.second == true) {
      check_count++;
    }
  }
  EXPECT_EQ(check_count, s21_set.size());
  EXPECT_EQ(check_count, std_set.size());
}

TEST(Map, default_constructor) {
  s21::map<int, int> s21_map;
  std::map<int, int> std_map;

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());
  EXPECT_EQ(s21_map.begin(), s21_map.end());
}

TEST(Map, initializer_list_constructor) {
  s21::map<int, std::string> s21_map{
      {32, "tridsat dva"}, {1, "odin"}, {40, "sorok"}, {13, "trinadsat"}};
  std::map<int, std::string> std_map{
      {32, "tridsat dva"}, {1, "odin"}, {40, "sorok"}, {13, "trinadsat"}};

  auto s21_it = s21_map.begin();
  auto std_it = std_map.begin();

  for (; s21_it != s21_map.end(); ++s21_it, ++std_it) {
    EXPECT_EQ(s21_it->first, std_it->first);
    EXPECT_EQ(s21_it->second, std_it->second);
  }

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());
}

TEST(Map, copy_constructor) {
  s21::map<int, std::string> s21_map{
      {32, "tridsat dva"}, {1, "odin"}, {40, "sorok"}, {13, "trinadsat"}};
  std::map<int, std::string> std_map{
      {32, "tridsat dva"}, {1, "odin"}, {40, "sorok"}, {13, "trinadsat"}};

  s21::map<int, std::string> s21_map_copy(s21_map);
  std::map<int, std::string> std_map_copy(std_map);

  auto s21_it = s21_map_copy.begin();
  auto std_it = std_map_copy.begin();

  for (; s21_it != s21_map_copy.end(); ++s21_it, ++std_it) {
    EXPECT_EQ(s21_it->first, std_it->first);
    EXPECT_EQ(s21_it->second, std_it->second);
  }

  EXPECT_EQ(s21_map_copy.size(), std_map_copy.size());
  EXPECT_EQ(s21_map_copy.empty(), std_map_copy.empty());
}

TEST(Map, copy_operator) {
  s21::map<int, std::string> s21_map{
      {32, "tridsat dva"}, {1, "odin"}, {40, "sorok"}, {13, "trinadsat"}};
  std::map<int, std::string> std_map{
      {32, "tridsat dva"}, {1, "odin"}, {40, "sorok"}, {13, "trinadsat"}};

  s21::map<int, std::string> s21_map_copy{{1, "random data"}, {3213, "ohhhh"}};
  std::map<int, std::string> std_map_copy{{1, "random data"}, {3213, "ohhhh"}};

  s21_map_copy = s21_map;
  std_map_copy = std_map;

  auto s21_it = s21_map_copy.begin();
  auto std_it = std_map_copy.begin();

  for (; s21_it != s21_map_copy.end(); ++s21_it, ++std_it) {
    EXPECT_EQ(s21_it->first, std_it->first);
    EXPECT_EQ(s21_it->second, std_it->second);
  }

  EXPECT_EQ(s21_map_copy.size(), std_map_copy.size());
  EXPECT_EQ(s21_map_copy.empty(), std_map_copy.empty());
}

TEST(Map, move_constructor) {
  s21::map<int, std::string> s21_map{
      {32, "tridsat dva"}, {1, "odin"}, {40, "sorok"}, {13, "trinadsat"}};
  std::map<int, std::string> std_map{
      {32, "tridsat dva"}, {1, "odin"}, {40, "sorok"}, {13, "trinadsat"}};

  s21::map<int, std::string> s21_map_copy(std::move(s21_map));
  std::map<int, std::string> std_map_copy(std::move(std_map));

  auto s21_it = s21_map_copy.begin();
  auto std_it = std_map_copy.begin();

  for (; s21_it != s21_map_copy.end(); ++s21_it, ++std_it) {
    EXPECT_EQ(s21_it->first, std_it->first);
    EXPECT_EQ(s21_it->second, std_it->second);
  }

  EXPECT_EQ(s21_map_copy.size(), std_map_copy.size());
  EXPECT_EQ(s21_map.size(), std_map.size());
}

TEST(Map, move_operator) {
  s21::map<int, std::string> s21_map{
      {32, "tridsat dva"}, {1, "odin"}, {40, "sorok"}, {13, "trinadsat"}};
  std::map<int, std::string> std_map{
      {32, "tridsat dva"}, {1, "odin"}, {40, "sorok"}, {13, "trinadsat"}};

  s21::map<int, std::string> s21_map_copy{{1, "random data"}, {3213, "ohhhh"}};
  std::map<int, std::string> std_map_copy{{1, "random data"}, {3213, "ohhhh"}};

  s21_map_copy = std::move(s21_map);
  std_map_copy = std::move(std_map);

  auto s21_it = s21_map_copy.begin();
  auto std_it = std_map_copy.begin();

  for (; s21_it != s21_map_copy.end(); ++s21_it, ++std_it) {
    EXPECT_EQ(s21_it->first, std_it->first);
    EXPECT_EQ(s21_it->second, std_it->second);
  }

  EXPECT_EQ(s21_map_copy.size(), std_map_copy.size());
  EXPECT_EQ(s21_map.size(), std_map.size());
}

TEST(Map, iterator) {
  s21::map<int, std::string> s21_map{
      {32, "tridsat dva"}, {1, "odin"}, {40, "sorok"}, {13, "trinadsat"}};
  std::map<int, std::string> std_map{
      {32, "tridsat dva"}, {1, "odin"}, {40, "sorok"}, {13, "trinadsat"}};

  const s21::map<int, std::string> s21_map_const{
      {32, "tridsat dva"}, {1, "odin"}, {40, "sorok"}, {13, "trinadsat"}};
  const std::map<int, std::string> std_map_const{
      {32, "tridsat dva"}, {1, "odin"}, {40, "sorok"}, {13, "trinadsat"}};

  auto std_it_beg = std_map.begin();
  auto std_it_end = --std_map.end();

  for (auto i = s21_map.begin(); i != s21_map.end(); i++) {
    EXPECT_EQ((std_it_beg)->first, (i)->first);
    EXPECT_EQ((std_it_beg++)->second, (i)->second);
  }

  for (auto i = --s21_map.end(); i != s21_map.begin(); i--) {
    EXPECT_EQ((std_it_end)->first, (i)->first);
    EXPECT_EQ((std_it_end--)->second, (i)->second);
  }

  auto std_it_beg_const = std_map_const.begin();
  auto std_it_end_const = --std_map_const.end();

  for (auto i = s21_map_const.begin(); i != s21_map_const.end(); i++) {
    EXPECT_EQ((std_it_beg_const)->first, (i)->first);
    EXPECT_EQ((std_it_beg_const++)->second, (i)->second);
  }

  for (auto i = --s21_map_const.end(); i != s21_map_const.begin(); i--) {
    EXPECT_EQ((std_it_end_const)->first, (i)->first);
    EXPECT_EQ((std_it_end_const--)->second, (i)->second);
  }
}

TEST(Map, at) {
  s21::map<int, std::string> s21_map{
      {32, "tridsat dva"}, {1, "odin"}, {40, "sorok"}, {13, "trinadsat"}};
  std::map<int, std::string> std_map{
      {32, "tridsat dva"}, {1, "odin"}, {40, "sorok"}, {13, "trinadsat"}};

  s21_map.at(1) = "ne odin";
  s21_map.at(13) = "ne trinadsat";
  s21_map.at(40) = "*-*";

  std_map.at(1) = "ne odin";
  std_map.at(13) = "ne trinadsat";

  EXPECT_TRUE(s21_map.at(1) == std_map.at(1));
  EXPECT_TRUE(s21_map.at(13) == std_map.at(13));
  EXPECT_FALSE(s21_map.at(40) == std_map.at(40));
  EXPECT_THROW(s21_map.at(1337), std::out_of_range);
}

TEST(Map, operator_sq_brackets) {
  s21::map<int, std::string> s21_map{
      {32, "tridsat dva"}, {1, "odin"}, {40, "sorok"}, {13, "trinadsat"}};
  std::map<int, std::string> std_map{
      {32, "tridsat dva"}, {1, "odin"}, {40, "sorok"}, {13, "trinadsat"}};

  s21_map[1] = "ne odin";
  s21_map[13] = "ne trinadsat";
  s21_map[40] = "*-*";

  std_map[1] = "ne odin";
  std_map[13] = "ne trinadsat";

  EXPECT_TRUE(s21_map[1] == std_map[1]);
  EXPECT_TRUE(s21_map[13] == std_map[13]);
  EXPECT_FALSE(s21_map[40] == std_map[40]);
  EXPECT_NO_THROW(s21_map[1337]);
  size_t tmp_size = s21_map.size();
  s21_map[35];
  EXPECT_EQ(tmp_size + 1, s21_map.size());
}

TEST(Map, empty) {
  s21::map<int, std::string> s21_map;
  std::map<int, std::string> std_map;

  EXPECT_EQ(s21_map.empty(), std_map.empty());

  s21_map.insert(234, "privet");
  std_map.insert({234, "privet"});

  EXPECT_EQ(s21_map.empty(), std_map.empty());
}

TEST(Map, size) {
  s21::map<int, std::string> s21_map;
  std::map<int, std::string> std_map;

  EXPECT_EQ(s21_map.size(), std_map.size());

  s21_map.insert(234, "privet");
  std_map.insert({234, "privet"});

  EXPECT_EQ(s21_map.size(), std_map.size());

  s21_map.insert(234, "privet");
  std_map.insert({234, "privet"});
  s21_map.insert(987, ":)");
  std_map.insert({987, ":)"});

  EXPECT_EQ(s21_map.size(), std_map.size());
}

TEST(Map, max_size) {
  s21::map<int, int> s21_map;
  std::map<int, int> std_map;
  EXPECT_EQ(s21_map.max_size(), std_map.max_size());
}

TEST(Map, clear) {
  s21::map<int, std::string> s21_map{
      {32, "tridsat dva"}, {1, "odin"}, {40, "sorok"}, {13, "trinadsat"}};
  std::map<int, std::string> std_map{
      {32, "tridsat dva"}, {1, "odin"}, {40, "sorok"}, {13, "trinadsat"}};

  s21_map.clear();
  std_map.clear();

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.begin(), s21_map.end());
}

TEST(Map, insert_pair) {
  s21::map<int, std::string> s21_map;
  std::map<int, std::string> std_map;

  auto s21_result = s21_map.insert({23, "UwU"});
  auto std_result = std_map.insert({23, "UwU"});

  EXPECT_EQ(s21_result.second, std_result.second);
  EXPECT_EQ(s21_result.first->first, s21_result.first->first);
  EXPECT_EQ(s21_result.first->second, s21_result.first->second);

  s21_result = s21_map.insert({23, "UwU"});
  std_result = std_map.insert({23, "UwU"});

  EXPECT_EQ(s21_result.second, std_result.second);
  EXPECT_EQ(s21_result.first->first, s21_result.first->first);
  EXPECT_EQ(s21_result.first->second, s21_result.first->second);

  s21_result = s21_map.insert({897, "all my homies code in c"});
  std_result = std_map.insert({897, "all my homies code in c"});

  EXPECT_EQ(s21_result.second, std_result.second);
  EXPECT_EQ(s21_result.first->first, s21_result.first->first);
  EXPECT_EQ(s21_result.first->second, s21_result.first->second);
}

TEST(Map, insert_key_value) {
  s21::map<int, std::string> s21_map;
  std::map<int, std::string> std_map;

  auto s21_result = s21_map.insert(23, "UwU");
  auto std_result = std_map.insert({23, "UwU"});

  EXPECT_EQ(s21_result.second, std_result.second);
  EXPECT_EQ(s21_result.first->first, s21_result.first->first);
  EXPECT_EQ(s21_result.first->second, s21_result.first->second);

  s21_result = s21_map.insert(23, "UwU");
  std_result = std_map.insert({23, "UwU"});

  EXPECT_EQ(s21_result.second, std_result.second);
  EXPECT_EQ(s21_result.first->first, s21_result.first->first);
  EXPECT_EQ(s21_result.first->second, s21_result.first->second);

  s21_result = s21_map.insert(897, "all my homies code in c");
  std_result = std_map.insert({897, "all my homies code in c"});

  EXPECT_EQ(s21_result.second, std_result.second);
  EXPECT_EQ(s21_result.first->first, s21_result.first->first);
  EXPECT_EQ(s21_result.first->second, s21_result.first->second);
}

TEST(Map, insert_or_assign) {
  s21::map<int, std::string> s21_map;
  std::map<int, std::string> std_map;

  auto s21_result = s21_map.insert_or_assign(23, "UwU");
  auto std_result = std_map.insert_or_assign(23, "UwU");

  EXPECT_EQ(s21_result.second, std_result.second);
  EXPECT_EQ(s21_result.first->first, s21_result.first->first);
  EXPECT_EQ(s21_result.first->second, s21_result.first->second);

  s21_result = s21_map.insert_or_assign(23, "quit c++, code in c, my brother");
  std_result = std_map.insert_or_assign(23, "quit c++, code in c, my brother");

  EXPECT_EQ(s21_result.second, std_result.second);
  EXPECT_EQ(s21_result.first->first, s21_result.first->first);
  EXPECT_EQ(s21_result.first->second, s21_result.first->second);

  s21_result = s21_map.insert_or_assign(897, "all my homies code in c");
  std_result = std_map.insert_or_assign(897, "all my homies code in c");

  EXPECT_EQ(s21_result.second, std_result.second);
  EXPECT_EQ(s21_result.first->first, s21_result.first->first);
  EXPECT_EQ(s21_result.first->second, s21_result.first->second);
}

TEST(Map, erase) {
  s21::map<int, std::string> s21_map{
      {32, "tridsat dva"}, {1, "odin"}, {40, "sorok"}, {13, "trinadsat"}};
  std::map<int, std::string> std_map{
      {32, "tridsat dva"}, {1, "odin"}, {40, "sorok"}, {13, "trinadsat"}};

  for (int i = 0; i < 4; ++i) {
    if (i % 2 == 0) {
      s21_map.erase(s21_map.begin());
      std_map.erase(std_map.begin());
    } else if (i % 3 == 0) {
      s21_map.erase(--s21_map.end());
      std_map.erase(--std_map.end());
    }
  }

  auto std_iter = std_map.begin();
  for (auto i : s21_map) {
    EXPECT_EQ(*(std_iter++), i);
  }
  EXPECT_EQ(s21_map.size(), std_map.size());
}

TEST(Map, swap) {
  s21::map<int, std::string> s21_map{
      {32, "tridsat dva"}, {1, "odin"}, {40, "sorok"}, {13, "trinadsat"}};
  std::map<int, std::string> std_map{
      {32, "tridsat dva"}, {1, "odin"}, {40, "sorok"}, {13, "trinadsat"}};

  s21::map<int, std::string> s21_map_other{{1, "random data"}, {3213, "ohhhh"}};
  std::map<int, std::string> std_map_other{{1, "random data"}, {3213, "ohhhh"}};

  s21_map.swap(s21_map_other);
  std_map.swap(std_map_other);

  auto std_iter = std_map.begin();
  for (auto i : s21_map) {
    EXPECT_EQ(*(std_iter++), i);
  }

  auto std_iter_other = std_map_other.begin();
  for (auto i : s21_map_other) {
    EXPECT_EQ(*(std_iter_other++), i);
  }

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map_other.size(), std_map_other.size());
}

TEST(Map, merge) {
  s21::map<int, std::string> s21_map{{32, "tridsat dva"}, {1, "odin"},
                                     {40, "sorok"},       {13, "trinadsat"},
                                     {2, "dva"},          {1, "null"}};
  std::map<int, std::string> std_map{{32, "tridsat dva"}, {1, "odin"},
                                     {40, "sorok"},       {13, "trinadsat"},
                                     {2, "dva"},          {1, "null"}};

  s21::map<int, std::string> s21_map_other{
      {1, "random data"}, {1, "odin"}, {3213, "ohhhh"}, {13, "hello world"}};
  std::map<int, std::string> std_map_other{
      {1, "random data"}, {1, "odin"}, {3213, "ohhhh"}, {13, "hello world"}};

  s21_map.merge(s21_map_other);
  std_map.merge(std_map_other);

  auto std_iter = std_map.begin();
  for (auto i : s21_map) {
    EXPECT_EQ(*(std_iter++), i);
  }

  auto std_iter_other = std_map_other.begin();
  for (auto i : s21_map_other) {
    EXPECT_EQ(*(std_iter_other++), i);
  }

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map_other.size(), std_map_other.size());
}

TEST(Map, contains) {
  s21::map<int, std::string> s21_map{{32, "tridsat dva"}, {1, "odin"},
                                     {40, "sorok"},       {13, "trinadsat"},
                                     {2, "dva"},          {1, "null"}};

  EXPECT_EQ(s21_map.contains(32), true);
  EXPECT_EQ(s21_map.contains(13), true);
  EXPECT_EQ(s21_map.contains(9871415), false);
}

TEST(Map, insert_many) {
  std::map<int, std::string> std_map{{32, "tridsat dva"}, {1, "odin"},
                                     {40, "sorok"},       {13, "trinadsat"},
                                     {2, "dva"},          {1, "null"}};
  s21::map<int, std::string> s21_map;
  auto result = s21_map.insert_many(
      std::make_pair(32, "tridsat dva"), std::make_pair(1, "odin"),
      std::make_pair(40, "sorok"), std::make_pair(13, "trinadsat"),
      std::make_pair(2, "dva"), std::make_pair(1, "null"));
  auto std_iter = std_map.begin();
  for (auto i : s21_map) {
    EXPECT_EQ(*(std_iter++), i);
  }

  int check_count = 0;
  for (auto pair : result) {
    if (pair.second == true) {
      check_count++;
    }
  }
  EXPECT_EQ(check_count, s21_map.size());
  EXPECT_EQ(check_count, std_map.size());
  EXPECT_EQ(s21_map.size(), std_map.size());
}

TEST(Multiset, default_constructor) {
  s21::multiset<int> s21_mset;
  std::multiset<int> std_mset;

  EXPECT_EQ(s21_mset.size(), std_mset.size());
  EXPECT_EQ(s21_mset.empty(), std_mset.empty());
  EXPECT_EQ(s21_mset.begin(), s21_mset.end());
}

TEST(Multiset, initializer_list_constructor) {
  s21::multiset<int> s21_mset = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                 4, 423, 4, 32, 5, 345623, 4, 12, 3};
  std::multiset<int> std_mset = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                 4, 423, 4, 32, 5, 345623, 4, 12, 3};

  auto std_it = std_mset.begin();

  for (auto i : s21_mset) {
    EXPECT_EQ(*(std_it++), i);
  }

  EXPECT_EQ(s21_mset.size(), std_mset.size());
  EXPECT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(Multiset, copy_constructor) {
  s21::multiset<int> s21_mset = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                 4, 423, 4, 32, 5, 345623, 4, 12, 3};
  std::multiset<int> std_mset = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                 4, 423, 4, 32, 5, 345623, 4, 12, 3};

  s21::multiset<int> s21_mset_copy(s21_mset);
  std::multiset<int> std_mset_copy(std_mset);

  auto std_it = std_mset_copy.begin();

  for (auto i : s21_mset_copy) {
    EXPECT_EQ(*(std_it++), i);
  }

  EXPECT_EQ(s21_mset_copy.size(), std_mset_copy.size());
  EXPECT_EQ(s21_mset_copy.size(), s21_mset.size());
}

TEST(Multiset, copy_operator) {
  s21::multiset<int> s21_mset = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                 4, 423, 4, 32, 5, 345623, 4, 12, 3};
  std::multiset<int> std_mset = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                 4, 423, 4, 32, 5, 345623, 4, 12, 3};

  s21::multiset<int> s21_mset_copy = {12, 9432, 432, 432};
  std::multiset<int> std_mset_copy = {12, 9432, 432, 432};

  s21_mset_copy = s21_mset;
  std_mset_copy = std_mset;

  auto std_it = std_mset_copy.begin();

  for (auto i : s21_mset_copy) {
    EXPECT_EQ(*(std_it++), i);
  }

  EXPECT_EQ(s21_mset_copy.size(), std_mset_copy.size());
  EXPECT_EQ(s21_mset_copy.size(), s21_mset.size());
}

TEST(Multiset, move_constructor) {
  s21::multiset<int> s21_mset = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                 4, 423, 4, 32, 5, 345623, 4, 12, 3};
  std::multiset<int> std_mset = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                 4, 423, 4, 32, 5, 345623, 4, 12, 3};

  s21::multiset<int> s21_mset_copy(std::move(s21_mset));
  std::multiset<int> std_mset_copy(std::move(std_mset));

  auto std_it = std_mset_copy.begin();

  for (auto i : s21_mset_copy) {
    EXPECT_EQ(*(std_it++), i);
  }

  EXPECT_EQ(s21_mset_copy.size(), std_mset_copy.size());
  EXPECT_EQ(s21_mset.size(), std_mset.size());
  EXPECT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(Multiset, move_operator) {
  s21::multiset<int> s21_mset = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                 4, 423, 4, 32, 5, 345623, 4, 12, 3};
  std::multiset<int> std_mset = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                 4, 423, 4, 32, 5, 345623, 4, 12, 3};

  s21::multiset<int> s21_mset_copy = {12, 9432, 432, 432};
  std::multiset<int> std_mset_copy = {12, 9432, 432, 432};

  s21_mset_copy = std::move(s21_mset);
  std_mset_copy = std::move(std_mset);

  auto std_it = std_mset_copy.begin();

  for (auto i : s21_mset_copy) {
    EXPECT_EQ(*(std_it++), i);
  }

  EXPECT_EQ(s21_mset_copy.size(), std_mset_copy.size());
  EXPECT_EQ(s21_mset.size(), std_mset.size());
  EXPECT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(Multiset, iterator) {
  s21::multiset<int> s21_mset = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                 4, 423, 4, 32, 5, 345623, 4, 12, 3};
  std::multiset<int> std_mset = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                 4, 423, 4, 32, 5, 345623, 4, 12, 3};

  const s21::multiset<int> s21_mset_const = {
      1, 1, 1, 1, 2, 3, 4, 5, 6, 743, 4, 423, 4, 32, 5, 345623, 4, 12, 3};
  const std::multiset<int> std_mset_const = {
      1, 1, 1, 1, 2, 3, 4, 5, 6, 743, 4, 423, 4, 32, 5, 345623, 4, 12, 3};

  auto std_it_beg = std_mset.begin();
  auto std_it_end = --std_mset.end();

  for (s21::multiset<int>::multiset_iterator i = s21_mset.begin();
       i != s21_mset.end(); i++) {
    EXPECT_EQ(*(std_it_beg++), (*i));
  }

  for (s21::multiset<int>::multiset_iterator i = --s21_mset.end();
       i != s21_mset.begin(); i--) {
    EXPECT_EQ(*(std_it_end--), (*i));
  }

  auto std_it_beg_const = std_mset_const.begin();
  auto std_it_end_const = --std_mset_const.end();

  for (s21::multiset<int>::const_multiset_iterator i = s21_mset_const.begin();
       i != s21_mset_const.end(); i++) {
    EXPECT_EQ(*(std_it_beg_const++), (*i));
  }

  for (s21::multiset<int>::const_multiset_iterator i = --s21_mset_const.end();
       i != s21_mset_const.begin(); i--) {
    EXPECT_EQ(*(std_it_end_const--), (*i));
  }
}

TEST(Multiset, empty) {
  s21::multiset<int> s21_mset;
  std::multiset<int> std_mset;

  EXPECT_EQ(s21_mset.empty(), std_mset.empty());

  s21_mset.insert(234);
  std_mset.insert(234);

  EXPECT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(Multiset, size) {
  s21::multiset<int> s21_mset;
  std::multiset<int> std_mset;

  EXPECT_EQ(s21_mset.size(), std_mset.size());

  s21_mset.insert(234);
  std_mset.insert(234);

  EXPECT_EQ(s21_mset.size(), std_mset.size());

  s21_mset.insert(234);
  std_mset.insert(234);
  s21_mset.insert(2314);
  std_mset.insert(2314);

  EXPECT_EQ(s21_mset.size(), std_mset.size());
}

TEST(Multiset, max_size) {
  s21::multiset<int> s21_mset;
  std::multiset<int> std_mset;
  EXPECT_EQ(s21_mset.max_size(), std_mset.max_size());
}

TEST(Multiset, clear) {
  s21::multiset<int> s21_mset = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                 4, 423, 4, 32, 5, 345623, 4, 12, 3};
  std::multiset<int> std_mset = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                 4, 423, 4, 32, 5, 345623, 4, 12, 3};
  s21_mset.clear();
  std_mset.clear();
  EXPECT_EQ(s21_mset.size(), std_mset.size());
  EXPECT_EQ(s21_mset.begin(), s21_mset.end());
}

TEST(Multiset, insert) {
  s21::multiset<int> s21_mset;
  std::multiset<int> std_mset;
  auto s21_result = s21_mset.insert(9);
  auto std_result = std_mset.insert(9);

  EXPECT_EQ(*s21_result, *std_result);

  s21_result = s21_mset.insert(500);
  std_result = std_mset.insert(500);
  EXPECT_EQ(*s21_result, *std_result);

  s21_result = s21_mset.insert(500);
  std_result = std_mset.insert(500);
  EXPECT_EQ(*s21_result, *std_result);

  s21_result = s21_mset.insert(97988984);
  std_result = std_mset.insert(97988984);
  EXPECT_EQ(*s21_result, *std_result);
  EXPECT_EQ(s21_mset.size(), std_mset.size());
}

TEST(Multiset, erase) {
  s21::multiset<int> s21_mset = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                 4, 423, 4, 32, 5, 345623, 4, 12, 3};
  std::multiset<int> std_mset = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                 4, 423, 4, 32, 5, 345623, 4, 12, 3};

  for (int i = 0; i < 10; ++i) {
    if (i % 2 == 0) {
      s21_mset.erase(s21_mset.begin());
      std_mset.erase(std_mset.begin());
    } else if (i % 3 == 0) {
      s21_mset.erase(--s21_mset.end());
      std_mset.erase(--std_mset.end());
    }
  }

  auto std_iter = std_mset.begin();
  for (auto i : s21_mset) {
    EXPECT_EQ(*(std_iter++), i);
  }
  EXPECT_EQ(s21_mset.size(), std_mset.size());
}

TEST(Multiset, swap) {
  s21::multiset<int> s21_mset = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                 4, 423, 4, 32, 5, 345623, 4, 12, 3};
  std::multiset<int> std_mset = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                 4, 423, 4, 32, 5, 345623, 4, 12, 3};

  s21::multiset<int> s21_mset_other = {9,  8, 1, 4, 1337, 12, 15648,
                                       54, 1, 2, 5, 8489, 4};
  std::multiset<int> std_mset_other = {9,  8, 1, 4, 1337, 12, 15648,
                                       54, 1, 2, 5, 8489, 4};

  s21_mset.swap(s21_mset_other);
  std_mset.swap(std_mset_other);

  auto std_iter = std_mset.begin();
  for (auto i : s21_mset) {
    EXPECT_EQ(*(std_iter++), i);
  }

  auto std_iter_other = std_mset_other.begin();
  for (auto i : s21_mset_other) {
    EXPECT_EQ(*(std_iter_other++), i);
  }

  EXPECT_EQ(s21_mset.size(), std_mset.size());
  EXPECT_EQ(s21_mset_other.size(), std_mset_other.size());
}

TEST(Multiset, merge) {
  s21::multiset<int> s21_mset = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                 4, 423, 4, 32, 5, 345623, 4, 12, 3};
  std::multiset<int> std_mset = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                 4, 423, 4, 32, 5, 345623, 4, 12, 3};

  s21::multiset<int> s21_mset_other = {9,  8, 1, 4, 1337, 12, 15648,
                                       54, 1, 2, 5, 8489, 4};
  std::multiset<int> std_mset_other = {9,  8, 1, 4, 1337, 12, 15648,
                                       54, 1, 2, 5, 8489, 4};

  s21_mset.merge(s21_mset_other);
  std_mset.merge(std_mset_other);

  auto std_iter = std_mset.begin();
  for (auto i : s21_mset) {
    EXPECT_EQ(*(std_iter++), i);
  }

  EXPECT_EQ(s21_mset.size(), std_mset.size());
  EXPECT_EQ(s21_mset_other.empty(), std_mset_other.empty());
}

TEST(Multiset, count) {
  s21::multiset<int> s21_mset = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                 4, 423, 4, 32, 5, 345623, 4, 12, 3};
  std::multiset<int> std_mset = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                 4, 423, 4, 32, 5, 345623, 4, 12, 3};
  EXPECT_EQ(s21_mset.count(1), std_mset.count(1));
  EXPECT_EQ(s21_mset.count(345623), std_mset.count(345623));
  EXPECT_EQ(s21_mset.count(13333337), std_mset.count(13333337));
}

TEST(Multiset, find) {
  s21::multiset<int> s21_mset = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                 4, 423, 4, 32, 5, 345623, 4, 12, 3};
  std::multiset<int> std_mset = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                 4, 423, 4, 32, 5, 345623, 4, 12, 3};

  EXPECT_EQ((*s21_mset.find(743)) == 743, (*std_mset.find(743)) == 743);
  EXPECT_EQ(s21_mset.find(894519) == s21_mset.end(),
            std_mset.find(894519) == std_mset.end());
}

TEST(Multiset, contains) {
  s21::multiset<int> s21_mset = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                 4, 423, 4, 32, 5, 345623, 4, 12, 3};

  EXPECT_EQ(s21_mset.contains(743), true);
  EXPECT_EQ(s21_mset.contains(1), true);
  EXPECT_EQ(s21_mset.contains(9871415), false);
}

TEST(Multiset, lower_bound) {
  s21::multiset<int> s21_mset = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                 4, 423, 4, 32, 5, 345623, 4, 12, 3};
  std::multiset<int> std_mset = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                 4, 423, 4, 32, 5, 345623, 4, 12, 3};
  EXPECT_EQ(*(s21_mset.lower_bound(1)), *(std_mset.lower_bound(1)));
  EXPECT_EQ(*(s21_mset.lower_bound(4)), *(std_mset.lower_bound(4)));
  EXPECT_EQ(*(s21_mset.lower_bound(345623)), *(std_mset.lower_bound(345623)));
  EXPECT_EQ(s21_mset.lower_bound(99988899) == s21_mset.end(),
            std_mset.lower_bound(99988899) == std_mset.end());
}

TEST(Multiset, upper_bound) {
  s21::multiset<int> s21_mset = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                 4, 423, 4, 32, 5, 345623, 4, 12, 3};
  std::multiset<int> std_mset = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                 4, 423, 4, 32, 5, 345623, 4, 12, 3};
  EXPECT_EQ(*(s21_mset.upper_bound(1)), *(std_mset.upper_bound(1)));
  EXPECT_EQ(*(s21_mset.upper_bound(4)), *(std_mset.upper_bound(4)));
  EXPECT_EQ(*(s21_mset.upper_bound(743)), *(std_mset.upper_bound(743)));
  EXPECT_EQ(s21_mset.upper_bound(99988899) == s21_mset.end(),
            std_mset.upper_bound(99988899) == std_mset.end());
}

TEST(Multiset, equal_range) {
  s21::multiset<int> s21_mset = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                 4, 423, 4, 32, 5, 345623, 4, 12, 3};
  std::multiset<int> std_mset = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                 4, 423, 4, 32, 5, 345623, 4, 12, 3};
  auto s21_range = s21_mset.equal_range(1);
  auto std_range = std_mset.equal_range(1);
  for (; s21_range.first != s21_range.second;
       ++s21_range.first, ++std_range.first) {
    EXPECT_EQ(*s21_range.first, *std_range.first);
  }

  s21_range = s21_mset.equal_range(4);
  std_range = std_mset.equal_range(4);
  for (; s21_range.first != s21_range.second;
       ++s21_range.first, ++std_range.first) {
    EXPECT_EQ(*s21_range.first, *std_range.first);
  }
  s21_range = s21_mset.equal_range(6232742);
  std_range = std_mset.equal_range(6232742);
  EXPECT_EQ(s21_range.first == s21_mset.end(),
            std_range.first == std_mset.end());
  EXPECT_EQ(s21_range.second == s21_mset.end(),
            std_range.second == std_mset.end());
}

TEST(Multiset, insert_many) {
  std::multiset<int> std_mset = {1, 1,   1, 1,  2, 3,      4, 5,  6, 743,
                                 4, 423, 4, 32, 5, 345623, 4, 12, 3};
  s21::multiset<int> s21_mset;
  auto result = s21_mset.insert_many(1, 1, 1, 1, 2, 3, 4, 5, 6, 743, 4, 423, 4,
                                     32, 5, 345623, 4, 12, 3);

  auto std_iter = std_mset.begin();
  for (auto i : s21_mset) {
    EXPECT_EQ(*(std_iter++), i);
  }

  EXPECT_EQ(result.size(), s21_mset.size());
  EXPECT_EQ(result.size(), std_mset.size());
}

TEST(Array, DefaultConstructor) {
  s21::array<int, 5> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.size(), 5);
}

TEST(Array, Constructor_1) {
  s21::array<int, 4> s21_arr_int;
  s21::array<double, 4> s21_arr_double;
  s21::array<std::string, 4> s21_arr_string;

  EXPECT_EQ(s21_arr_int.size(), 4U);
  EXPECT_EQ(s21_arr_double.size(), 4U);
  EXPECT_EQ(s21_arr_string.size(), 4U);
}

TEST(Array, Constructor_2) {
  s21::array<int, 5> s21_arr_int{1, 3, 5, 7, 9};
  s21::array<double, 5> s21_arr_double{1.1, 3.3, 5.5, 7.7, 9.1};
  s21::array<std::string, 5> s21_arr_string{"Hello", ",", "world", "!", "!!"};

  EXPECT_EQ(s21_arr_int.size(), 5U);
  EXPECT_EQ(s21_arr_int[0], 1);

  EXPECT_EQ(s21_arr_double.size(), 5U);
  EXPECT_EQ(s21_arr_double[0], 1.1);

  EXPECT_EQ(s21_arr_string.size(), 5U);
  EXPECT_EQ(s21_arr_string[0], "Hello");
}

TEST(Array, Constructor_3) {
  s21::array<int, 4> s21_arr_ref_int{1, 3, 5, 7};
  s21::array<int, 4> s21_arr_res_int(s21_arr_ref_int);

  s21::array<double, 4> s21_arr_ref_double{1.1, 3.3, 5.5, 7.7};
  s21::array<double, 4> s21_arr_res_double(s21_arr_ref_double);

  s21::array<std::string, 4> s21_arr_ref_string{"Hello", ",", "world", "!"};
  s21::array<std::string, 4> s21_arr_res_string(s21_arr_ref_string);

  EXPECT_EQ(s21_arr_ref_int.size(), s21_arr_res_int.size());
  EXPECT_EQ(s21_arr_ref_int[0], s21_arr_res_int[0]);
  EXPECT_EQ(s21_arr_ref_int[1], s21_arr_res_int[1]);
  EXPECT_EQ(s21_arr_ref_int[2], s21_arr_res_int[2]);
  EXPECT_EQ(s21_arr_ref_int[3], s21_arr_res_int[3]);

  EXPECT_EQ(s21_arr_ref_double.size(), s21_arr_res_double.size());
  EXPECT_EQ(s21_arr_ref_double[0], s21_arr_res_double[0]);
  EXPECT_EQ(s21_arr_ref_double[1], s21_arr_res_double[1]);
  EXPECT_EQ(s21_arr_ref_double[2], s21_arr_res_double[2]);
  EXPECT_EQ(s21_arr_ref_double[3], s21_arr_res_double[3]);

  EXPECT_EQ(s21_arr_ref_string.size(), s21_arr_res_string.size());
  EXPECT_EQ(s21_arr_ref_string[0], s21_arr_res_string[0]);
  EXPECT_EQ(s21_arr_ref_string[1], s21_arr_res_string[1]);
  EXPECT_EQ(s21_arr_ref_string[2], s21_arr_res_string[2]);
  EXPECT_EQ(s21_arr_ref_string[3], s21_arr_res_string[3]);
}

TEST(Array, at_1) {
  s21::array<int, 4> s21_arr_int{1, 3, 5, 7};
  s21::array<double, 4> s21_arr_double{1.1, 3.3, 5.5, 7.7};
  s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_arr_int.at(0), 1);
  EXPECT_EQ(s21_arr_double.at(0), 1.1);
  EXPECT_EQ(s21_arr_string.at(0), "Hello");
}

TEST(Array, at_2) {
  s21::array<int, 4> s21_arr_int{1, 3, 5, 7};
  s21::array<double, 4> s21_arr_double{1.1, 3.3, 5.5, 7.7};
  s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};

  EXPECT_THROW(s21_arr_int.at(5), std::out_of_range);
  EXPECT_THROW(s21_arr_double.at(5), std::out_of_range);
  EXPECT_THROW(s21_arr_string.at(5), std::out_of_range);
}

TEST(Array, square_braces) {
  s21::array<int, 4> s21_arr_int{1, 3, 5, 7};
  s21::array<double, 4> s21_arr_double{1.1, 3.3, 5.5, 7.7};
  s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_arr_int[1], 3);
  EXPECT_EQ(s21_arr_double[1], 3.3);
  EXPECT_EQ(s21_arr_string[0], "Hello");
}

TEST(Array, array_front) {
  s21::array<int, 4> s21_arr_int{1, 3, 5, 7};
  s21::array<double, 4> s21_arr_double{1.1, 3.3, 5.5, 7.7};
  s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_arr_int.front(), 1);
  EXPECT_EQ(s21_arr_double.front(), 1.1);
  EXPECT_EQ(s21_arr_string.front(), "Hello");
}

TEST(Array, array_back) {
  s21::array<int, 4> s21_arr_int{1, 3, 5, 7};
  s21::array<double, 4> s21_arr_double{1.1, 3.3, 5.5, 7.7};
  s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_arr_int.back(), 7);
  EXPECT_EQ(s21_arr_double.back(), 7.7);
  EXPECT_EQ(s21_arr_string.back(), "!");
}

TEST(Array, data) {
  s21::array<int, 4> s21_arr_int{1, 3, 5, 7};
  s21::array<double, 4> s21_arr_double{1.1, 3.3, 5.5, 7.7};
  s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_arr_int.data(), &s21_arr_int[0]);
  EXPECT_EQ(s21_arr_double.data(), &s21_arr_double[0]);
  EXPECT_EQ(s21_arr_string.data(), &s21_arr_string[0]);
}

TEST(Array, empty_true) {
  s21::array<int, 0> v;
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0);
}

TEST(Array, empty_false) {
  s21::array<int, 4> s21_arr_int{1, 3, 5, 7};
  s21::array<double, 4> s21_arr_double{1.1, 3.3, 5.5, 7.7};
  s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_arr_int.empty(), 0);
  EXPECT_EQ(s21_arr_double.empty(), 0);
  EXPECT_EQ(s21_arr_string.empty(), 0);
}

TEST(Array, begin) {
  s21::array<int, 4> s21_arr_int{1, 3, 5, 7};
  s21::array<double, 4> s21_arr_double{1.1, 3.3, 5.5, 7.7};
  s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_arr_int.begin(), &s21_arr_int[0]);
  EXPECT_EQ(s21_arr_double.begin(), &s21_arr_double[0]);
  EXPECT_EQ(s21_arr_string.begin(), &s21_arr_string[0]);
}
TEST(Array, end) {
  s21::array<int, 4> s21_arr_int{1, 3, 5, 7};
  s21::array<double, 4> s21_arr_double{1.1, 3.3, 5.5, 7.7};
  s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_arr_int.end(), &s21_arr_int[0] + 4);
  EXPECT_EQ(s21_arr_double.end(), &s21_arr_double[0] + 4);
  EXPECT_EQ(s21_arr_string.end(), &s21_arr_string[0] + 4);
}

TEST(array_size, case1) {
  s21::array<int, 4> s21_arr_int{1, 4, 8, 9};
  s21::array<double, 4> s21_arr_double{1.4, 4.8, 8.9, 9.1};
  s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_arr_int.size(), 4U);
  EXPECT_EQ(s21_arr_double.size(), 4U);
  EXPECT_EQ(s21_arr_string.size(), 4U);
}

TEST(array_max_size, case1) {
  s21::array<int, 4> s21_arr_int{1, 4, 8, 9};
  std::array<int, 4> std_arr_int{1, 4, 8, 9};

  s21::array<double, 4> s21_arr_double{1.4, 4.8, 8.9, 9.1};
  std::array<double, 4> std_arr_double{1.4, 4.8, 8.9, 9.1};

  s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};
  std::array<std::string, 4> std_arr_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_arr_int.max_size(), std_arr_int.max_size());
  EXPECT_EQ(s21_arr_double.max_size(), std_arr_double.max_size());
  EXPECT_EQ(s21_arr_string.max_size(), std_arr_string.max_size());
}

TEST(array_swap, case1) {
  s21::array<int, 4> s21_arr_ref_int{1, 4, 8, 9};
  s21::array<int, 4> s21_arr_res_int{21, 21, 21, 21};

  s21::array<double, 4> s21_arr_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::array<double, 4> s21_arr_res_double{21.0, 21.0, 21.0, 21.0};

  s21::array<std::string, 4> s21_arr_ref_string{"Hello", ",", "world", "!"};
  s21::array<std::string, 4> s21_arr_res_string{"21", "21", "21", "21"};

  s21_arr_ref_int.swap(s21_arr_res_int);
  s21_arr_ref_double.swap(s21_arr_res_double);
  s21_arr_ref_string.swap(s21_arr_res_string);

  EXPECT_EQ(s21_arr_ref_int[3], 21);
  EXPECT_EQ(s21_arr_res_int[0], 1);
  EXPECT_EQ(s21_arr_res_int[1], 4);
  EXPECT_EQ(s21_arr_res_int[2], 8);
  EXPECT_EQ(s21_arr_res_int[3], 9);

  EXPECT_EQ(s21_arr_ref_double[3], 21.0);
  EXPECT_EQ(s21_arr_res_double[0], 1.4);
  EXPECT_EQ(s21_arr_res_double[1], 4.8);
  EXPECT_EQ(s21_arr_res_double[2], 8.9);
  EXPECT_EQ(s21_arr_res_double[3], 9.1);

  EXPECT_EQ(s21_arr_ref_string[3], "21");
  EXPECT_EQ(s21_arr_res_string[0], "Hello");
  EXPECT_EQ(s21_arr_res_string[1], ",");
  EXPECT_EQ(s21_arr_res_string[2], "world");
  EXPECT_EQ(s21_arr_res_string[3], "!");
}
TEST(array_fill, case1) {
  s21::array<int, 4> s21_arr_int{1, 4, 8, 9};
  s21::array<double, 4> s21_arr_double{1.4, 4.8, 8.9, 9.1};
  s21::array<std::string, 4> s21_arr_string{"Hello", ",", "world", "!"};

  s21_arr_int.fill(21);
  s21_arr_double.fill(21.0);
  s21_arr_string.fill("21");

  EXPECT_EQ(s21_arr_int[0], 21);
  EXPECT_EQ(s21_arr_int[1], 21);
  EXPECT_EQ(s21_arr_int[2], 21);
  EXPECT_EQ(s21_arr_int[3], 21);

  EXPECT_EQ(s21_arr_double[0], 21.0);
  EXPECT_EQ(s21_arr_double[1], 21.0);
  EXPECT_EQ(s21_arr_double[2], 21.0);
  EXPECT_EQ(s21_arr_double[3], 21.0);

  EXPECT_EQ(s21_arr_string[0], "21");
  EXPECT_EQ(s21_arr_string[1], "21");
  EXPECT_EQ(s21_arr_string[2], "21");
  EXPECT_EQ(s21_arr_string[3], "21");
}

TEST(arrayTest, SizeConstructor_PositiveSize) {
  const size_t size = 5;
  s21::array<int, size> v;
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v.size(), size);
}

TEST(arrayTest, SizeConstructor_ZeroSize) {
  const size_t size = 0;
  s21::array<int, size> v;
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), size);
}

TEST(arrayTest, InitializerListConstructor_EmptyList) {
  s21::array<int, 0> v = {};
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0);
}

TEST(arrayTest, InitializerListConstructor_NonEmptyList) {
  s21::array<int, 5> v = {1, 2, 3, 4, 5};
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[4], 5);
}

TEST(arrayTest, CopyConstructor_Emptyarray) {
  s21::array<int, 0> v1;
  s21::array<int, 0> v2(v1);
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v2.size(), 0);
}

TEST(arrayTest, CopyConstructor_NonEmptyarray) {
  s21::array<int, 3> v1 = {1, 2, 3};
  s21::array<int, 3> v2(v1);
  EXPECT_EQ(v2.size(), v1.size());
  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v2[i], v1[i]);
  }
}

TEST(arrayTest, MoveConstructor_Emptyarray) {
  s21::array<int, 0> v1;
  s21::array<int, 0> v2(std::move(v1));
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v2.size(), 0);
}

TEST(arrayTest, MoveConstructor_NonEmptyarray) {
  s21::array<int, 3> v1 = {1, 2, 3};
  s21::array<int, 3> v2(std::move(v1));
  EXPECT_EQ(v2.size(), 3);
  EXPECT_FALSE(v1.empty());
}

TEST(arrayTest, Destructor_Emptyarray) {
  s21::array<int, 0> *v = new s21::array<int, 0>();
  delete v;
}

TEST(arrayTest, Destructor_NonEmptyarray) {
  s21::array<int, 3> *v = new s21::array<int, 3>{1, 2, 3};
  delete v;
}

TEST(arrayTest, MoveAssignmentOperator_EmptyToEmpty) {
  s21::array<int, 0> v1;
  s21::array<int, 0> v2;
  v2 = std::move(v1);
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v2.size(), 0);
}

TEST(arrayTest, MoveAssignmentOperator_NonEmptyToEmpty) {
  s21::array<int, 3> v1 = {1, 2, 3};
  s21::array<int, 3> v2;
  v2 = std::move(v1);
  EXPECT_EQ(v2.size(), 3);
  EXPECT_FALSE(v1.empty());
}

TEST(arrayTest, MoveAssignmentOperator_EmptyToNonEmpty) {
  s21::array<int, 3> v1;
  s21::array<int, 3> v2 = {4, 5, 6};
  v2 = std::move(v1);
  EXPECT_TRUE(!v2.empty());
  EXPECT_EQ(v2.size(), 3);
}

TEST(arrayTest, MoveAssignmentOperator_NonEmptyToNonEmpty) {
  s21::array<int, 3> v1 = {1, 2, 3};
  s21::array<int, 3> v2 = {4, 5, 6};
  v2 = std::move(v1);
  EXPECT_EQ(v2.size(), 3);
  EXPECT_FALSE(v1.empty());
}

TEST(arrayTest, At_ValidIndex) {
  s21::array<int, 5> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.at(0), 1);
  EXPECT_EQ(v.at(2), 3);
  EXPECT_EQ(v.at(4), 5);
}

TEST(arrayTest, At_InvalidIndex) {
  s21::array<int, 5> v = {1, 2, 3, 4, 5};
  EXPECT_THROW(v.at(5), std::out_of_range);
  EXPECT_THROW(v.at(10), std::out_of_range);
}

TEST(arrayTest, IndexOperator_ValidIndex) {
  s21::array<int, 5> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[4], 5);
}

TEST(arrayTest, IndexOperator_InvalidIndex) {
  s21::array<int, 5> v = {1, 2, 3, 4, 5};
  EXPECT_ANY_THROW(v[5]);
  EXPECT_ANY_THROW(v[10]);
}

TEST(arrayTest, ConstIndexOperator_ValidIndex) {
  const s21::array<int, 5> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[4], 5);
}

TEST(arrayTest, ConstIndexOperator_InvalidIndex) {
  const s21::array<int, 5> v = {1, 2, 3, 4, 5};
  EXPECT_ANY_THROW(v[5]);
  EXPECT_ANY_THROW(v[10]);
}

TEST(arrayTest, FrontConst_Validarray) {
  const s21::array<int, 5> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.front(), 1);
}

TEST(arrayTest, BackConst_Validarray) {
  const s21::array<int, 5> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.back(), 5);
}

TEST(arrayTest, Data_Validarray) {
  s21::array<int, 5> v = {1, 2, 3, 4, 5};
  int *dataPtr = v.data();
  EXPECT_EQ(*dataPtr, 1);
  *dataPtr = 10;
  EXPECT_EQ(v[0], 10);
}
TEST(arrayTest, Data_Emptyarray) {
  s21::array<int, 0> v;
  int *dataPtr = v.data();
  EXPECT_EQ(dataPtr, nullptr);
}
TEST(arrayTest, Begin_Validarray) {
  s21::array<int, 5> v = {1, 2, 3, 4, 5};
  auto it = v.begin();
  EXPECT_EQ(*it, 1);
  *it = 10;
  EXPECT_EQ(v[0], 10);
}

TEST(arrayTest, Begin_Emptyarray) {
  s21::array<int, 0> v;
  auto it = v.begin();
  EXPECT_EQ(it, v.end());
}

TEST(arrayTest, End_Validarray) {
  s21::array<int, 5> v = {1, 2, 3, 4, 5};
  auto it = v.end();
  auto beginIt = v.begin();
  EXPECT_NE(it, beginIt);
}

TEST(arrayTest, End_Emptyarray) {
  s21::array<int, 0> v;
  auto it = v.end();
  EXPECT_EQ(it, v.begin());
}

TEST(arrayTest, Empty_Emptyarray) {
  const s21::array<int, 0> v;
  EXPECT_TRUE(v.empty());
}

TEST(arrayTest, Empty_NonEmptyarray) {
  const s21::array<int, 3> v = {1, 2, 3};
  EXPECT_FALSE(v.empty());
}

TEST(arrayTest, Size_Emptyarray) {
  const s21::array<int, 0> v;
  EXPECT_EQ(v.size(), 0);
}

TEST(arrayTest, Size_NonEmptyarray) {
  const s21::array<int, 3> v = {1, 2, 3};
  EXPECT_EQ(v.size(), 3);
}

TEST(arrayTest, MaxSize) {
  s21::array<int, 0> v;
  std::array<int, 0> v1;

  EXPECT_EQ(v.max_size(), v1.max_size());
}

TEST(arrayTest, Swap_NonEmptyarrays) {
  s21::array<int, 3> v1 = {1, 2, 3};
  s21::array<int, 3> v2 = {4, 5, 6};

  v1.swap(v2);

  EXPECT_EQ(v1.size(), 3);
  EXPECT_EQ(v2.size(), 3);

  EXPECT_EQ(v1[0], 4);
  EXPECT_EQ(v1[2], 6);

  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[2], 3);
}

TEST(arrayTest, Swap_yarrays) {
  s21::array<int, 3> v1;
  s21::array<int, 3> v2 = {1, 2, 3};

  v1.swap(v2);

  EXPECT_EQ(v1.size(), 3);
  EXPECT_FALSE(v1.empty());
  EXPECT_EQ(v2.size(), 3);
  EXPECT_FALSE(v2.empty());
}

TEST(arrayConstructorTest, DefaultConstructor) {
  s21::array<int, 0> v;

  EXPECT_EQ(v.size(), 0);

  EXPECT_EQ(v.data(), nullptr);
}

TEST(arrayConstructorTest, SizeConstructor) {
  s21::array<int, 5> v;

  EXPECT_EQ(v.size(), 5);
}

TEST(arrayConstructorTest, InitializerListConstructor) {
  s21::array<int, 5> v = {1, 2, 3, 4, 5};

  EXPECT_EQ(v.size(), 5);

  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], i + 1);
  }
}

TEST(arrayConstructorTest, EmptyInitializerListConstructor) {
  s21::array<int, 0> v = {};

  EXPECT_EQ(v.size(), 0);
}

TEST(arrayConstructorTest, CopyConstructor) {
  s21::array<int, 5> v1 = {1, 2, 3, 4, 5};

  s21::array<int, 5> v2(v1);

  EXPECT_EQ(v2.size(), v1.size());

  for (size_t i = 0; i < v2.size(); ++i) {
    EXPECT_EQ(v2[i], v1[i]);
  }
}

TEST(arrayConstructorTest, EmptyCopyConstructor) {
  s21::array<int, 0> v1;

  s21::array<int, 0> v2(v1);

  EXPECT_EQ(v2.size(), 0);
}

TEST(arrayConstructorTest, MoveConstructor) {
  s21::array<int, 5> v1 = {1, 2, 3, 4, 5};

  s21::array<int, 5> v2(std::move(v1));

  EXPECT_EQ(v2.size(), 5);

  for (size_t i = 0; i < v2.size(); ++i) {
    EXPECT_EQ(v2[i], i + 1);
  }

  EXPECT_EQ(v1.size(), 5);
}

TEST(arrayConstructorTest, EmptyMoveConstructor) {
  s21::array<int, 0> v1;

  s21::array<int, 0> v2(std::move(v1));

  EXPECT_EQ(v2.size(), 0);

  EXPECT_EQ(v1.size(), 0);
  EXPECT_EQ(v1.data(), nullptr);
}

TEST(arrayDestructorTest, NonEmptyarray) {
  s21::array<int, 5> v = {1, 2, 3, 4, 5};

  EXPECT_NO_THROW({ v.~array(); });

  EXPECT_EQ(v.size(), 5);

  EXPECT_EQ(v.data(), v.begin());
}

TEST(arrayDestructorTest, Emptyarray) {
  s21::array<int, 0> v;

  EXPECT_NO_THROW({ v.~array(); });

  EXPECT_EQ(v.size(), 0);

  EXPECT_EQ(v.data(), nullptr);
}

TEST(arrayMoveAssignmentTest, MoveEmptyarray) {
  s21::array<int, 0> src;

  s21::array<int, 0> dest;
  dest = std::move(src);

  EXPECT_EQ(src.size(), 0);
  EXPECT_EQ(src.data(), nullptr);

  EXPECT_EQ(dest.size(), 0);
  EXPECT_EQ(dest.data(), nullptr);
}

TEST(arrayMoveAssignmentTest, MoveNonEmptyarray) {
  s21::array<int, 5> src = {1, 2, 3, 4, 5};

  s21::array<int, 5> dest;
  dest = std::move(src);

  EXPECT_EQ(src.size(), 5);

  EXPECT_EQ(dest.size(), 5);
  EXPECT_EQ(dest[0], 1);
  EXPECT_EQ(dest[1], 2);
  EXPECT_EQ(dest[2], 3);
  EXPECT_EQ(dest[3], 4);
  EXPECT_EQ(dest[4], 5);
}

TEST(arraySwapTest, SwapEmptyarrays) {
  s21::array<int, 0> v1;
  s21::array<int, 0> v2;

  v1.swap(v2);

  EXPECT_EQ(v1.size(), 0);
  EXPECT_EQ(v1.data(), nullptr);

  EXPECT_EQ(v2.size(), 0);
  EXPECT_EQ(v2.data(), nullptr);
}

TEST(arraySwapTest, SwapNonEmptyarrays) {
  s21::array<int, 3> v1 = {1, 2, 3};
  s21::array<int, 3> v2 = {4, 5, 6};

  v1.swap(v2);

  EXPECT_EQ(v1.size(), 3);
  EXPECT_NE(v1.data(), nullptr);
  EXPECT_EQ(v1[0], 4);
  EXPECT_EQ(v1[1], 5);
  EXPECT_EQ(v1[2], 6);

  EXPECT_EQ(v2.size(), 3);
  EXPECT_NE(v2.data(), nullptr);
  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[1], 2);
  EXPECT_EQ(v2[2], 3);
}

TEST(VectorTest, Swap_NonEmptyVectors) {
  s21::array<int, 3> v1 = {1, 2, 3};
  s21::array<int, 3> v2 = {4, 5, 6};

  v1.swap(v2);

  EXPECT_EQ(v1.size(), 3);
  EXPECT_EQ(v2.size(), 3);

  EXPECT_EQ(v1[0], 4);
  EXPECT_EQ(v1[2], 6);

  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[2], 3);
}

TEST(array_test, operator_eq) {
  s21::array<int, 7> vec1 = {1, 2, 3, 5, 6, 3, 4};
  s21::array<int, 7> vec2;
  vec2 = vec1;
  EXPECT_EQ(vec1.size(), vec2.size());
  auto it_2 = vec2.begin();
  for (auto it = vec1.begin(); it != vec1.end(); ++it) {
    EXPECT_EQ(*it, *it_2);
    ++it_2;
  }
}

TEST(array_test, operator_brackets) {
  s21::array<int, 5> vec1 = {1, 2, 3, 4, 5};
  std::array<int, 5> vec2 = {1, 2, 3, 4, 5};
  for (size_t i = 0; i < vec1.size(); i++) {
    EXPECT_EQ(vec1[i], vec2[i]);
  }
  EXPECT_EQ(vec1.size(), vec2.size());
}

TEST(array_test, front) {
  s21::array<int, 3> vec1 = {1, 2, 3};
  std::array<int, 3> vec2 = {1, 2, 3};
  EXPECT_EQ(vec1.front(), vec2.front());
  EXPECT_EQ(vec1.size(), vec2.size());
}
TEST(array_test, back) {
  s21::array<int, 3> vec1 = {1, 2, 3};
  std::array<int, 3> vec2 = {1, 2, 3};
  EXPECT_EQ(vec1.back(), vec2.back());
  EXPECT_EQ(vec1.size(), vec2.size());
}

TEST(array_test, data) {
  s21::array<int, 0> vec1;
  EXPECT_EQ(vec1.data(), nullptr);
  s21::array<int, 3> vec2 = {1, 2, 3};
  EXPECT_FALSE(vec2.data() == nullptr);
}

TEST(array_test, begin) {
  s21::array<int, 5> vec1 = {1, 2, 3, 4, 5};
  std::array<int, 5> vec2 = {1, 2, 3, 4, 5};
  auto iter1 = vec1.begin();
  auto iter2 = vec2.begin();
  EXPECT_EQ(*iter1, *iter2);
  EXPECT_EQ(vec1.size(), vec2.size());
}

TEST(array_test, end) {
  s21::array<int, 5> vec1 = {1, 2, 3, 4, 5};
  std::array<int, 5> vec2 = {1, 2, 3, 4, 5};
  auto iter1 = vec1.end();
  auto iter2 = vec2.end();
  EXPECT_EQ(*(iter1 - 1), *(iter2 - 1));
  EXPECT_EQ(vec1.size(), vec2.size());
}

TEST(array_test, size) {
  s21::array<int, 3> vec1;
  std::array<int, 3> vec2 = {1, 2, 3};
  EXPECT_EQ(vec1.size(), 3);
  vec1 = {1, 2, 3};
  EXPECT_EQ(vec1.size(), vec2.size());
  EXPECT_EQ(vec1.size(), vec2.size());
}
TEST(array_test, capacity) {
  s21::array<int, 3> vec1;
  std::array<int, 3> vec2;
  EXPECT_EQ(vec1.size(), vec2.size());

  vec1 = {1, 2, 3};
  vec2 = {1, 2, 3};
  EXPECT_EQ(vec1.size(), vec2.size());
}

TEST(array_test, swap) {
  s21::array<int, 3> vec1 = {1, 2, 3};
  s21::array<int, 3> vec1_1 = {3, 2, 1};
  vec1.swap(vec1_1);
  for (int i = 0, j = 3; i < 3; i++) {
    EXPECT_EQ(vec1_1[i], i + 1);
    EXPECT_EQ(vec1[i], j--);
  }
}

TEST(s21_array, front_back_test_1) {
  s21::array<int, 2> myarray{78, 16};
  std::array<int, 2> test_array{78, 16};
  ASSERT_EQ(myarray.front(), test_array.front());
  ASSERT_EQ(myarray.back(), test_array.back());
}

TEST(Array, copy_constructor_test) {
  std::array<int, 3> orig_array3{234, 21, 11};
  s21::array<int, 3> copy_array3{234, 21, 11};
  std::array<int, 3> orig_array4(orig_array3);
  s21::array<int, 3> copy_array4(copy_array3);
  for (int i{}; i < 3; i++) {
    ASSERT_EQ(orig_array3.at(i), copy_array3.at(i));
    ASSERT_EQ(orig_array4.at(i), copy_array4.at(i));
  }
  ASSERT_EQ(orig_array3.size(), copy_array3.size());
  ASSERT_EQ(orig_array3.max_size(), copy_array3.max_size());
  ASSERT_EQ(orig_array4.size(), copy_array4.size());
  ASSERT_EQ(orig_array4.max_size(), copy_array4.max_size());
  std::array<char, 0> orig_ar5;
  s21::array<char, 0> copy_ar5;
  std::array<char, 0> orig_ar6(orig_ar5);
  s21::array<char, 0> copy_ar6(copy_ar5);
  ASSERT_EQ(orig_ar5.empty(), copy_ar5.empty());
  ASSERT_EQ(orig_ar6.empty(), copy_ar6.empty());
}

TEST(Array, move_constructor_test) {
  std::array<int, 5> orig_array1{234, 21, 11, 34, 999};
  s21::array<int, 5> copy_array1{234, 21, 11, 34, 999};
  std::array<int, 5> orig_array2(std::move(orig_array1));
  s21::array<int, 5> copy_array2(std::move(copy_array1));
  for (size_t i{}; i < copy_array2.size(); i++) {
    ASSERT_EQ(orig_array2.at(i), copy_array2.at(i));
  }
  ASSERT_EQ(orig_array1.size(), copy_array1.size());
  ASSERT_EQ(orig_array1.max_size(), copy_array1.max_size());
  ASSERT_EQ(orig_array2.size(), copy_array2.size());
  ASSERT_EQ(orig_array2.max_size(), copy_array2.max_size());
  std::array<char, 0> orig_ar1;
  s21::array<char, 0> copy_ar1;
  ASSERT_EQ(orig_ar1.empty(), copy_ar1.empty());
}

TEST(Array, move_operator_test) {
  std::array<int, 5> orig_array1{234, 21, 11, 34, 999};
  s21::array<int, 5> copy_array1{234, 21, 11, 34, 999};
  std::array<int, 5> orig_array2{25};
  s21::array<int, 5> copy_array2{25};
  orig_array2 = std::move(orig_array1);
  copy_array2 = std::move(copy_array1);
  for (size_t i{}; i < copy_array2.size(); i++) {
    ASSERT_EQ(orig_array2.at(i), copy_array2.at(i));
  }
  ASSERT_EQ(orig_array1.size(), copy_array1.size());
  ASSERT_EQ(orig_array1.max_size(), copy_array1.max_size());
  ASSERT_EQ(orig_array2.size(), copy_array2.size());
  ASSERT_EQ(orig_array2.max_size(), copy_array2.max_size());
  std::array<char, 0> orig_ar1;
  s21::array<char, 0> copy_ar1;
  ASSERT_EQ(orig_ar1.empty(), copy_ar1.empty());
}

TEST(Array, iterator_test) {
  std::array<int, 5> orig_array1{234, 21, 11, 34, 999};
  s21::array<int, 5> copy_array1{234, 21, 11, 34, 999};
  int *orig_beg = orig_array1.begin();
  int *copy_beg = copy_array1.begin();
  int *orig_end = orig_array1.end();
  int *copy_end = copy_array1.end();
  while (orig_beg < orig_end && copy_beg < copy_end) {
    ASSERT_EQ(*orig_beg++, *copy_beg++);
  }
  ASSERT_EQ(orig_array1.size(), copy_array1.size());
  ASSERT_EQ(orig_array1.max_size(), copy_array1.max_size());
  s21::array<char, 0> copy_ar1;
  ASSERT_TRUE(copy_ar1.begin() == copy_ar1.end());
  s21::array<double, 3> my_arr{2.3, 4.5555, 6.1234};
  double *d = my_arr.data();
  ASSERT_DOUBLE_EQ(my_arr[0], *d);
}

TEST(Array, fill) {
  std::array<size_t, 10> arr;
  s21::array<size_t, 10> s21_arr;
  arr.fill(7);
  s21_arr.fill(7);
  for (size_t i = 0; i < arr.size(); i++) ASSERT_EQ(arr[i], s21_arr[i]);
  ASSERT_EQ(arr.size(), s21_arr.size());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}