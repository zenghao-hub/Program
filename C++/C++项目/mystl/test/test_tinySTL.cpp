#include <stdio.h>
#include<iostream>
#include <vector>
#include<algorithm>
#include <numeric>
#include"color.h"
#include"test.h"
//#include"test_tinySTL.h"
#define PRINT(x) std::cout<<redbud::io::state::manual << redbud::io::hfg::green<<x<<'\n'<<"---------------------------------------\n"
//#define green redbud::io::state::manual << redbud::io::hfg::green
#define XX(i) i##"1"
#define SPACE std::cout<<'\n'

template<typename Ta> 
Ta sum(Ta& t1,Ta& t2)
{
	return t1 + t2;
}

class TestCase
{
public:
	// 构造函数，接受一个字符串代表案例名称
	TestCase(const char* case_name) : testcase_name(case_name) { std::cout << "testCase构造"; }

	// 一个纯虚函数，用于测试案例
	virtual void Run() = 0;

public:
	const char* testcase_name;  // 测试案例的名称
	int         nTestResult;    // 测试案例的执行结果 
	double      nFailed;        // 测试失败的案例数
	double      nPassed;        // 测试通过的案例数
};

class UnitTest
{
public:
	// 获取一个案例
	static UnitTest* GetInstance();

	// 将案例依次加入 vector
	TestCase* RegisterTestCase(TestCase* testcase);

	void Run();

public:
	TestCase* CurrentTestCase;          // 当前执行的测试案例
	double    nPassed;                  // 通过案例数
	double    nFailed;                  // 失败案例数

protected:
	std::vector<TestCase*> testcases_;  // 保存案例集合
};

UnitTest* UnitTest::GetInstance() // 目的是获取UnitTest的对象啦，这样才能通过对象调用RegisterTestCase()
{
	static UnitTest instance;
	return &instance;
}

TestCase* UnitTest::RegisterTestCase(TestCase* testcase)
{
	testcases_.push_back(testcase);// 测试实例集合(vector) testcases_为保护变量
	return testcase;
}

void UnitTest::Run() {
	std::cout << "run?";
	for (auto it : testcases_)
	{
		std::cout << it->testcase_name;
	}
}

class copy_test_TEST : public TestCase {
public:                                                       
	copy_test_TEST(const char* case_name) : TestCase(case_name) { std::cout << "copy_test_TEST构造\n"; };
	virtual void Run();                                       
private:                                                      
	static TestCase* const testcase_;                        
};                                                            

//TestCase* const copy_test_TEST::testcase_ = UnitTest::GetInstance()->RegisterTestCase(
//	new copy_test_TEST("copy_test"));
void copy_test_TEST::Run() {
	// 定义RUN中的参数呀
	std::cout << XX("sss");
}

int algo_cnt = 0;
int main() {

	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5,6,7,8,9,10 };
		int exp[5];
		OUT_TIME_P3(std::copy, arr1, arr1 + 5, exp);
		OUT_TIME_P3(mystl::copy, arr1, arr1 + 5, exp);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5 };
		std::vector<int> exp{ 0,0,0,0,0,6,7,8,9,10 };
		int act[] = { 0,0,0,0,0,6,7,8,9,10 };
		OUT_TIME_P3(std::copy_backward,arr1, arr1 + 5, exp.begin() + 5);
		OUT_TIME_P3(mystl::copy_backward,arr1, arr1 + 5, act + 5);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5,6,7,8,9,10 };
		int exp[5], act[5];
		OUT_TIME_P4(std::copy_if,arr1, arr1 + 10, exp, is_odd);
		OUT_TIME_P4(mystl::copy_if,arr1, arr1 + 10, act, is_odd);
		//std::cout << act[0] << act[1] << act[2];
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5,6,7,8,9,10 };
		int exp[10], act[10];
		OUT_TIME_P3(std::copy_n,arr1, 10, exp);
		OUT_TIME_P3(mystl::copy_n,arr1, 10, act);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5 };
		int arr2[] = { 1,2,3,4,5 };
		int exp[5], act[5];
		OUT_TIME_P3(std::move,arr1, arr1 + 5, exp);
		OUT_TIME_P3(mystl::move,arr2, arr2 + 5, act);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5 };
		int arr2[] = { 1,2,3,4,5 };
		int exp[5], act[5];
		OUT_TIME_P3(std::move_backward,arr1, arr1 + 5, exp + 5);
		OUT_TIME_P3(mystl::move_backward,arr2, arr2 + 5, act + 5);
	}
	{
		PRINT(++algo_cnt);
		std::vector<int> v1{ 1,2,3,4,5 };
		std::vector<int> v2{ 1,2,3,4,5,6 };
		int arr1[] = { 1,2,3,4,5 };
		int arr2[] = { 1,2,3,4,6 };
		OUT_TIME_P3(std::equal, v1.begin(), v1.end(), v2.begin());
		OUT_TIME_P3(mystl::equal, v1.begin(), v1.end(), v2.begin());

		OUT_TIME_P4(std::equal, v1.begin(), v1.end(), arr2, std::equal_to<int>());
		OUT_TIME_P4(mystl::equal,v1.begin(), v1.end(), arr2, std::equal_to<int>());
	}
	{
		PRINT(++algo_cnt);
		int exp[10], act[10];
		std::vector<int> v1(10, 1);
		std::vector<int> v2(10, 2);
		OUT_TIME_P3(std::fill,exp, exp + 10, 1);
		OUT_TIME_P3(mystl::fill,act, act + 10, 1);

		OUT_TIME_P3(std::fill,v1.begin(), v1.end(), 3);
		OUT_TIME_P3(mystl::fill,v2.begin(), v2.end(), 3);
	}

	{
		PRINT(++algo_cnt);
		int arr1[5];
		int arr2[5];
		OUT_TIME_P3(std::fill_n,arr2, 5, 1);
		OUT_TIME_P3(mystl::fill_n,arr1, 5, 1);
	}
	{
		PRINT(++algo_cnt);
		int a = 1;
		int b = 2;
		int *p1 = &a;
		int *p2 = &b;
		int *p3 = &a;
		int *p4 = &b;
		OUT_TIME_P2(std::iter_swap,p1, p2);
		OUT_TIME_P2(mystl::iter_swap,p3, p4);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5 };
		int arr2[] = { 0,2,4,6,8 };
		int arr3[] = { 1,2,3,4,5 };
		int arr4[] = { 1,2,3,4,5,6 };
		int arr5[] = { 2,3,4 };
		OUT_TIME_P4(std::lexicographical_compare, arr1, arr1 + 5, arr2, arr2 + 5);
		OUT_TIME_P4(mystl::lexicographical_compare,arr1, arr1 + 5, arr2, arr2 + 5);
	}
	{
		PRINT(++algo_cnt);
		int i1 = 1, i2 = 2;
		double d1 = 1.1, d2 = 2.2;
		char c1 = 'a', c2 = 'b';
		OUT_TIME_P2(std::max, i1, i2);
		OUT_TIME_P2(mystl::max,i1, i2);
	}
	{
		PRINT(++algo_cnt);
		int i1 = 1, i2 = 2;
		double d1 = 1.1, d2 = 2.2;
		char c1 = 'a', c2 = 'b';
		OUT_TIME_P2(std::min, i1, i2);
		OUT_TIME_P2(mystl::min, i1, i2);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,1,2,2,3,4,5 };
		int arr2[] = { 1,1,2,2,3,3,3 };
		int arr3[] = { 0,1,2,2,3,4,5 };
		int arr4[] = { 1,1,2,2,3,4,5 };
		OUT_TIME_P3(std::mismatch,arr1, arr1 + 7, arr2);
		OUT_TIME_P3(mystl::mismatch,arr1, arr1 + 7, arr2);
	}
	// heap_algo test
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5,6,7,8,9 };
		int arr2[] = { 1,2,3,4,5,6,7,8,9 };
		OUT_TIME_P2(std::make_heap,arr1, arr1 + 9);
		OUT_TIME_P2(mystl::make_heap,arr2, arr2 + 9);
	}

	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5,6,7,8,9 };
		int arr2[] = { 1,2,3,4,5,6,7,8,9 };
		std::make_heap(arr1, arr1 + 9);
		std::make_heap(arr2, arr2 + 9);
		for (int i = 9; i > 0; --i)
		{
			OUT_TIME_P2(std::pop_heap,arr1, arr1 + i);
			OUT_TIME_P2(mystl::pop_heap,arr2, arr2 + i);
		}
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5,6,7,8,9 };
		int arr2[] = { 1,2,3,4,5,6,7,8,9 };
		std::make_heap(arr1, arr1 + 4);
		std::make_heap(arr2, arr2 + 4);
		for (int i = 4; i <= 9; ++i)
		{
			OUT_TIME_P2(std::push_heap,arr1, arr1 + i);
			OUT_TIME_P2(mystl::push_heap,arr2, arr2 + i);
		}
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5,6,7,8,9 };
		int arr2[] = { 1,2,3,4,5,6,7,8,9 };
		std::make_heap(arr1, arr1 + 9);
		std::make_heap(arr2, arr2 + 9);
		// 不能多次执行 
		srand((int)time(0));
		start = clock();
		std::sort_heap(arr1, arr1 + 9);
		end = clock();
		std::cout << "std::sort_heap" << ":" << (end - start) << "ms\n";
		
		srand((int)time(0));
		start = clock();
		mystl::sort_heap(arr2, arr2 + 9);
		end = clock();
		std::cout << "mystl::sort_heap" << ":" << (end - start) << "ms\n";
		//OUT_TIME_P2(std::sort_heap,arr1, arr1 + 9);
		//OUT_TIME_P2(mystl::sort_heap,arr2, arr2 + 9);
	}

	// set_algo test
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5,6,7,8,9 };
		int arr2[] = { 1,2,3,4,5,6 };
		int arr3[] = { 1,2,3 };
		int exp[6] = { 0 }, act[6] = { 0 };
		OUT_TIME_P5(std::set_difference,arr1, arr1 + 9, arr2, arr2 + 6, exp);
		OUT_TIME_P5(mystl::set_difference,arr1, arr1 + 9, arr2, arr2 + 6, act);
		OUT_TIME_P6(std::set_difference,arr1, arr1 + 9, arr3, arr3 + 3, exp, std::less<int>());
		OUT_TIME_P6(mystl::set_difference,arr1, arr1 + 9, arr3, arr3 + 3, act, std::less<int>());
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5,6,7,8,9 };
		int arr2[] = { 1,2,3,4,5,6 };
		int arr3[] = { 1,2,3 };
		int exp[9] = { 0 }, act[9] = { 0 };
		OUT_TIME_P5(std::set_intersection,arr1, arr1 + 9, arr2, arr2 + 6, exp);
		OUT_TIME_P5(mystl::set_intersection,arr1, arr1 + 9, arr2, arr2 + 6, act);
		OUT_TIME_P6(std::set_intersection,arr1, arr1 + 9, arr3, arr3 + 3, exp, std::less<int>());
		OUT_TIME_P6(mystl::set_intersection,arr1, arr1 + 9, arr3, arr3 + 3, act, std::less<int>());
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5 };
		int arr2[] = { 1,3,5,7,9 };
		int arr3[] = { 2,4,6,8,10 };
		int exp[10] = { 0 }, act[10] = { 0 };
		OUT_TIME_P5(std::set_symmetric_difference,arr1, arr1 + 5, arr2, arr2 + 5, exp);
		OUT_TIME_P5(mystl::set_symmetric_difference,arr1, arr1 + 5, arr2, arr2 + 5, act);
		OUT_TIME_P6(std::set_symmetric_difference,arr2, arr2 + 5, arr3, arr3 + 5, exp, std::less<int>());
		OUT_TIME_P6(mystl::set_symmetric_difference,arr2, arr2 + 5, arr3, arr3 + 5, act, std::less<int>());
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5 };
		int arr2[] = { 1,3,5,7,9 };
		int arr3[] = { 2,4,6,8,10 };
		int exp[10] = { 0 }, act[10] = { 0 };
		OUT_TIME_P5(std::set_union,arr1, arr1 + 5, arr2, arr2 + 5, exp);
		OUT_TIME_P5(mystl::set_union,arr1, arr1 + 5, arr2, arr2 + 5, act);
		OUT_TIME_P6(std::set_union,arr2, arr2 + 5, arr3, arr3 + 5, exp, std::less<int>());
		OUT_TIME_P6(mystl::set_union,arr2, arr2 + 5, arr3, arr3 + 5, act, std::less<int>());
	}
	// numeric test
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5 };
		OUT_TIME_P3(std::accumulate,arr1, arr1 + 5, 0);
		OUT_TIME_P3(mystl::accumulate,arr1, arr1 + 5, 0);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5 };
		int arr2[] = { 1,1,1,1,1 };
		int exp[5], act[5];
		OUT_TIME_P3(std::adjacent_difference,arr1, arr1 + 5, exp);
		OUT_TIME_P3(mystl::adjacent_difference,arr1, arr1 + 5, act);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,1,1,1,1 };
		int arr2[] = { 2,2,2,2,2 };
		int arr3[] = { 1,2,3,4,5 };
		OUT_TIME_P4(std::inner_product, arr1, arr1 + 5, arr3, 0);
		OUT_TIME_P4(mystl::inner_product,arr1, arr1 + 5, arr3, 0);
	}
	{
		PRINT(++algo_cnt);
		int arr1[10];
		int arr2[10];
		OUT_TIME_P3(std::iota,arr1, arr1 + 10, 1);
		OUT_TIME_P3(mystl::iota,arr2, arr2 + 10, 1);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5,6,7,8,9 };
		int exp1[5], act1[5];
		OUT_TIME_P3(std::partial_sum,arr1, arr1 + 5, exp1);
		OUT_TIME_P3(mystl::partial_sum,arr1, arr1 + 5, act1);
	}
	// algo test
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,3,4 };
		int arr2[] = { 1,2,3,4,5 };
		OUT_TIME_P2(std::adjacent_find,arr1, arr1 + 5);
		OUT_TIME_P2(mystl::adjacent_find,arr1, arr1 + 5);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,3,5,7,9 };
		int arr2[] = { 1,3,5,7,8 };
		OUT_TIME_P3(std::all_of, arr1, arr1 + 5, is_odd);
		OUT_TIME_P3(mystl::all_of,arr1, arr1 + 5, is_odd);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,4,6,8 };
		int arr2[] = { 2,4,6,8,10 };
		OUT_TIME_P3(std::any_of, arr1, arr1 + 5, is_odd);
		OUT_TIME_P3(mystl::any_of,arr1, arr1 + 5, is_odd);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5 };
		OUT_TIME_P3(std::binary_search, arr1, arr1 + 5, 1);
		OUT_TIME_P3(mystl::binary_search,arr1, arr1 + 5, 1);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,2,3,3,3,4,5,8 };
		OUT_TIME_P3(std::count, arr1, arr1 + 9, 2);
		OUT_TIME_P3(mystl::count,arr1, arr1 + 9, 2);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,2,3,3,3,4,5,8 };
		OUT_TIME_P3(std::count_if, arr1, arr1 + 9, is_odd);
		OUT_TIME_P3(mystl::count_if,arr1, arr1 + 9, is_odd);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,3,3,4,5 };
		OUT_TIME_P3(std::equal_range, arr1, arr1 + 7, 3);
		OUT_TIME_P3(mystl::equal_range,arr1, arr1 + 7, 3);
		
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5 };
		OUT_TIME_P3(std::find, arr1, arr1 + 5, 3);
		OUT_TIME_P3(mystl::find,arr1, arr1 + 5, 3);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,2,2,3,4,5 };
		int arr2[] = { 2,3 };
		OUT_TIME_P4(std::find_end, arr1, arr1 + 8, arr2, arr2 + 1);
		OUT_TIME_P4(mystl::find_end,arr1, arr1 + 8, arr2, arr2 + 1);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5 };
		int arr2[] = { 2,3,4 };
		int arr3[] = { 6,7,8 };
		OUT_TIME_P4(std::find_first_of, arr1, arr1 + 5, arr2, arr2 + 3);
		OUT_TIME_P4(mystl::find_first_of,arr1, arr1 + 5, arr2, arr2 + 3);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5 };
		OUT_TIME_P3(std::find_if, arr1, arr1 + 5, is_odd);
		OUT_TIME_P3(mystl::find_if,arr1, arr1 + 5, is_odd);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5 };
		OUT_TIME_P3(std::find_if_not, arr1, arr1 + 5, is_odd);
		OUT_TIME_P3(mystl::find_if_not,arr1, arr1 + 5, is_odd);
	}
	{
		PRINT(++algo_cnt);
		std::vector<int> v1{ 1,2,3,4,5 };
		OUT_TIME_P3(std::for_each,v1.begin(), v1.end(), arr_sum);
		OUT_TIME_P3(mystl::for_each,v1.begin(), v1.end(), arr_sum);
	}
	{
		PRINT(++algo_cnt);
		int arr1[5];
		int arr2[5];
		OUT_TIME_P3(std::generate,arr1, arr1 + 5, gen);
		OUT_TIME_P3(mystl::generate,arr2, arr2 + 5, gen);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,1,1,1,1,6,7,8,9,10 };
		int arr2[] = { 2,2,2,2,2,6,7,8,9,10 };
		OUT_TIME_P3(std::generate_n,arr1, 5, gen);
		OUT_TIME_P3(mystl::generate_n,arr2, 5, gen);
	}
	{
		PRINT(++algo_cnt);
		std::vector<int> v1{ 1,2,3,4,5,6,7,8,9 };
		std::vector<int> v2{ 2,3,5,6,9 };
		OUT_TIME_P4(std::includes, v1.begin(), v1.end(), v2.begin(), v2.end());
		OUT_TIME_P4(mystl::includes,v1.begin(), v1.end(), v2.begin(), v2.end());
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,3,5,7,9,2,4,6,8,10 };
		int arr2[] = { 1,3,5,7,9,2,4,6,8,10 };
		OUT_TIME_P3(std::inplace_merge,arr1, arr1 + 5, arr1 + 10);
		OUT_TIME_P3(mystl::inplace_merge,arr2, arr2 + 5, arr2 + 10);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5,6,7,8,9 };
		int arr2[] = { 9,8,7,6,5,4,3,2,1 };
		OUT_TIME_P2(std::is_heap, arr1, arr1 + 10);
		OUT_TIME_P2(mystl::is_heap,arr1, arr1 + 10);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5 };
		OUT_TIME_P2(std::is_sorted, arr1, arr1 + 5);
		OUT_TIME_P2(mystl::is_sorted,arr1, arr1 + 5);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,3,3,4,5 };
		OUT_TIME_P3(std::lower_bound,arr1, arr1 + 7, 3);
		OUT_TIME_P3(mystl::lower_bound,arr1, arr1 + 7, 3);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5,4,3,2,1 };
		OUT_TIME_P2(std::max_element, arr1, arr1 + 9);
		OUT_TIME_P2(mystl::max_element,arr1, arr1 + 9);
	}
	{
		PRINT(++algo_cnt);
		int ia = 2, ib = 1, ic = 3;
		OUT_TIME_P3(mystl::median,ia, ib, ic);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,5,9,10 };
		int arr2[] = { 3,7,8,8,9 };
		int arr3[] = { 1,2,5,9,10 };
		int arr4[] = { 3,7,8,8,9 };
		int exp[10], act[10];
		OUT_TIME_P5(std::merge,arr1, arr1 + 5, arr2, arr2 + 5, exp);
		OUT_TIME_P5(mystl::merge,arr3, arr3 + 5, arr4, arr4 + 5, act);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 2,4,8,1,6,5,8,9,3 };
		OUT_TIME_P2(std::min_element, arr1, arr1 + 9);
		OUT_TIME_P2(mystl::min_elememt,arr1, arr1 + 9);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5 };
		int arr2[] = { 3,4,5,2,1 };
		// 因为提供的是 C++11 的支持，std::is_permutation 可能没有 C++14 的接口
		OUT_TIME_P3(std::is_permutation, arr1, arr1 + 5, arr2);
		OUT_TIME_P4(mystl::is_permutation,arr1, arr1 + 5, arr2, arr2 + 5);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,3 };
		int arr2[] = { 1,2,3,3 };
		int n1 = 0, n2 = 0;
		OUT_TIME_P2(std::next_permutation,arr1, arr1 + 4);
		OUT_TIME_P2(mystl::next_permutation,arr1, arr1 + 4);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,3,5,7,9 };
		OUT_TIME_P3(std::none_of, arr1, arr1 + 5, is_even);
		OUT_TIME_P3(mystl::none_of,arr1, arr1 + 5, is_even);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 9,8,7,6,5,4,3,2,1 };
		int arr2[] = { 1,2,3,4,5,6,3,2,1 };
		OUT_TIME_P3(mystl::nth_element,arr1, arr1 + 4, arr1 + 9);
		OUT_TIME_P3(mystl::nth_element,arr2, arr2 + 2, arr2 + 9);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 3,2,1,9,8,7,6,5,4 };
		int arr2[] = { 3,2,1,9,8,7,6,5,4 };
		OUT_TIME_P3(std::partial_sort,arr1, arr1 + 2, arr1 + 9);
		OUT_TIME_P3(mystl::partial_sort,arr2, arr2 + 2, arr2 + 9);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 3,2,1,9,8,7,6,5,4 };
		int exp[5], act[5];
		OUT_TIME_P4(std::partial_sort_copy,arr1, arr1 + 9, exp, exp + 5);
		OUT_TIME_P4(mystl::partial_sort_copy,arr1, arr1 + 9, act, act + 5);

	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5,6,7,8,9 };
		int arr2[] = { 1,2,3,4,5,6,7,8,9 };
		OUT_TIME_P3(std::partition,arr1, arr1 + 9, is_odd);
		OUT_TIME_P3(mystl::partition,arr2, arr2 + 9, is_odd);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5,6,7,8,9,10 };
		int exp_true[5], exp_false[5];
		int act_true[5], act_false[5];
		OUT_TIME_P5(std::partition_copy,arr1, arr1 + 10, exp_true, exp_false, is_odd);
		OUT_TIME_P5(mystl::partition_copy,arr1, arr1 + 10, act_true, act_false, is_odd);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 3,2,1,1 };
		int arr2[] = { 3,2,1,1 };
		int n1 = 0, n2 = 0;
		OUT_TIME_P2(std::prev_permutation,arr1, arr1 + 4);
		OUT_TIME_P2(mystl::prev_permutation,arr1, arr1 + 4);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5,6,7,8,9 };
		int arr2[9];
		OUT_TIME_P3(std::copy,arr1, arr1 + 9, arr2);
		OUT_TIME_P2(mystl::random_shuffle,arr1, arr1 + 9);
	}
	{
		PRINT(++algo_cnt);
		std::vector<int> v1{ 1,2,3,4,5,6,6,6 };
		std::vector<int> v2(v1);
		OUT_TIME_P3(std::remove,v1.begin(), v1.end(), 3);
		OUT_TIME_P3(mystl::remove,v2.begin(), v2.end(), 3);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5,6,6,6 };
		int arr2[] = { 1,2,3,4,5,6,6,6 };
		int exp[5], act[5];
		OUT_TIME_P4(std::remove_copy,arr1, arr1 + 8, exp, 6);
		OUT_TIME_P4(mystl::remove_copy,arr2, arr2 + 8, act, 6);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5,6,7,8,9,10 };
		int exp[5], act[5];
		OUT_TIME_P4(std::remove_copy_if,arr1, arr1 + 10, exp, is_odd);
		OUT_TIME_P4(mystl::remove_copy_if,arr1, arr1 + 10, act, is_odd);
	}
	{
		PRINT(++algo_cnt);
		std::vector<int> v1{ 1,2,3,4,5,6,7,8,9,10 };
		std::vector<int> v2(v1);
		OUT_TIME_P3(std::remove_if,v1.begin(), v1.end(), is_odd);
		OUT_TIME_P3(mystl::remove_if,v2.begin(), v2.end(), is_odd);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,1,1,2,2,2,3,3,3 };
		int arr2[] = { 1,1,1,2,2,2,3,3,3 };
		OUT_TIME_P4(std::replace,arr1, arr1 + 9, 1, 4);
		OUT_TIME_P4(mystl::replace,arr2, arr2 + 9, 1, 4);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,1,1,2,2,2,3,3,3 };
		int exp[9], act[9];
		OUT_TIME_P5(std::replace_copy,arr1, arr1 + 9, exp, 1, 4);
		OUT_TIME_P5(mystl::replace_copy,arr1, arr1 + 9, act, 1, 4);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5,6,7,8,9,10 };
		int exp[10] = { 0 }, act[10] = { 0 };
		OUT_TIME_P5(std::replace_copy_if,arr1, arr1 + 10, exp, is_odd, 1);
		OUT_TIME_P5(mystl::replace_copy_if,arr1, arr1 + 10, act, is_odd, 1);
	}
	{
		PRINT(++algo_cnt);
		std::vector<int> v1{ 1,2,3,4,5,6,7,8,9,10 };
		std::vector<int> v2(v1);
		OUT_TIME_P4(std::replace_if,v1.begin(), v1.end(), is_odd, 1);
		OUT_TIME_P4(mystl::replace_if,v2.begin(), v2.end(), is_odd, 1);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5,6,7,8,9 };
		int arr2[] = { 1,2,3,4,5,6,7,8,9 };
		OUT_TIME_P2(std::reverse,arr1, arr1 + 9);
		OUT_TIME_P2(mystl::reverse,arr2, arr2 + 9);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5,6,7,8,9 };
		int exp[5], act[5];
		OUT_TIME_P3(std::reverse_copy,arr1, arr1 + 5, exp);
		OUT_TIME_P3(mystl::reverse_copy,arr1, arr1 + 5, act);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5,6,7,8,9 };
		int arr2[] = { 1,2,3,4,5,6,7,8,9 };
		OUT_TIME_P3(std::rotate,arr1, arr1 + 3, arr1 + 9);
		OUT_TIME_P3(mystl::rotate,arr2, arr2 + 3, arr2 + 9);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5,6,7,8,9 };
		int exp[9], act[9];
		OUT_TIME_P4(std::rotate_copy,arr1, arr1 + 5, arr1 + 9, exp);
		OUT_TIME_P4(mystl::rotate_copy,arr1, arr1 + 5, arr1 + 9, act);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,3,3,4,5,6,6, };
		int arr2[] = { 1 };
		int arr3[] = { 3,3 };
		int arr4[] = { 5,6,6,6 };
		OUT_TIME_P4(std::search,arr1, arr1 + 9, arr2, arr2 + 1);
		OUT_TIME_P4(mystl::search,arr1, arr1 + 9, arr2, arr2 + 1);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,2,3,3,3,6,6,9 };
		OUT_TIME_P4(std::search_n,arr1, arr1 + 9, 1, 0);
		OUT_TIME_P4(mystl::search_n,arr1, arr1 + 9, 1, 0);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 6,1,2,5,4,8,3,2,4,6,10,2,1,9 };
		int arr2[] = { 6,1,2,5,4,8,3,2,4,6,10,2,1,9 };
		OUT_TIME_P2(std::sort,arr1, arr1 + 14);
		OUT_TIME_P2(mystl::sort,arr2, arr2 + 14);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 4,5,6,1,2,3 };
		int arr2[] = { 4,5,6,1,2,3 };
		int arr3[] = { 1,2,3,4,5,6 };
		int arr4[] = { 1,2,3,4,5,6 };
		OUT_TIME_P3(std::swap_ranges,arr1, arr1 + 6, arr3);
		OUT_TIME_P3(mystl::swap_ranges,arr2, arr2 + 6, arr4);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,4,5,6,7,8,9 };
		int arr2[] = { 9,8,7,6,5,4,3,2,1 };
		int exp[9], act[9];
		OUT_TIME_P4(std::transform,arr1, arr1 + 9, exp, unary_op);
		OUT_TIME_P4(mystl::transform,arr1, arr1 + 9, act, unary_op);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,1,1,2,2,3,4,4,5,6 };
		int arr2[] = { 1,1,1,2,2,3,4,4,5,6 };
		OUT_TIME_P2(std::unique,arr1, arr1 + 10);
		OUT_TIME_P2(mystl::unique,arr2, arr2 + 10);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,1,1,2,2,3,4,4,5,6 };
		int exp[6], act[6];
		OUT_TIME_P3(std::unique_copy,arr1, arr1 + 10, exp);
		OUT_TIME_P3(mystl::unique_copy,arr1, arr1 + 10, act);
	}
	{
		PRINT(++algo_cnt);
		int arr1[] = { 1,2,3,3,3,4,5,6,6 };
		OUT_TIME_P3(std::upper_bound,arr1, arr1 + 9, 0);
		OUT_TIME_P3(mystl::upper_bound,arr1, arr1 + 9, 0);
	}
 }
