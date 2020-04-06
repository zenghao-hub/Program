#include<ctime>
#include"util.h"
#include"iterator.h"
#include"memory.h"
#include"functional.h"
clock_t start,end;
#define EX_CNT 10000
int cnt = 0;

#define OUT_TIME_P2(fun,a,b)	cnt=EX_CNT;		\
srand((int)time(0));							\
start = clock();								\
while(cnt--){fun(a,b);							\
}												\
end=clock();									\
std::cout<<#fun<<":"<<(end-start)<<"ms\n";		

#define OUT_TIME_P3(fun,a,b,c)	cnt=EX_CNT;		\
srand((int)time(0));							\
start = clock();								\
while(cnt--){fun(a,b,c);						\
}												\
end=clock();									\
std::cout<<#fun<<":"<<(end-start)<<"ms\n";		

#define OUT_TIME_P4(fun,a,b,c,d) cnt=EX_CNT;	\
srand((int)time(0));							\
start = clock();								\
while(cnt--){fun(a,b,c,d);}						\
end=clock();									\
std::cout<<#fun<<":"<<(end-start)<<"ms\n";		

#define OUT_TIME_P5(fun,a,b,c,d,e) cnt=EX_CNT;	\
srand((int)time(0));							\
start = clock();								\
while(cnt--){fun(a,b,c,d,e);}					\
end=clock();									\
std::cout<<#fun<<":"<<(end-start)<<"ms\n";		

#define OUT_TIME_P6(fun,a,b,c,d,e,f) cnt=EX_CNT;\
srand((int)time(0));							\
start = clock();								\
while(cnt--){fun(a,b,c,d,e,f);}					\
end=clock();									\
std::cout<<#fun<<":"<<(end-start)<<"ms\n";		

int  gen() { return 5; }
int  r(int i) { return (i * 5 + 1) % 9; }
bool is_odd(int i) { return i & 1; }
int  binary_op(const int& x, const int& y) { return x + y; }
bool is_even(int i) { return !(i & 1); }
int  for_each_sum = 0;
void arr_sum(int i) { for_each_sum += i; }
bool cmp(const int& a, const int& b) { return b < a; }
int  unary_op(const int& x) { return x + 1; }

namespace mystl{

	/**************************************************
	@brief   : copy
	@author  : zenghao
	@input   ：first,last,result
	@output  ：result
	**************************************************/

	template <class Tp, class Up>
	Up* unchecked_copy(Tp* first, Tp* last, Up* result)
	{
		const auto n = static_cast<size_t>(last - first);
		if (n != 0)
			std::memmove(result, first, n * sizeof(Up));
		return result + n - 1;
	}
	template <class InputIter, class OutputIter>
	OutputIter copy(InputIter first, InputIter last, OutputIter result)
	{
		return unchecked_copy(first, last, result);
	}

	/**************************************************
	@brief   : copy_backward
	@author  : zenghao
	@input   ：first,last,result
	@output  ：result
	**************************************************/
	template <class Tp, class Up>
	Up* unchecked_copy_backward(Tp* first, Tp* last, Up* result)
	{
		const auto n = static_cast<size_t>(last - first);
		if (n != 0)
		{
			result -= n;
			std::memmove(result, first, n * sizeof(Up));
		}
		return result;
	}

	template <class BidirectionalIter1, class BidirectionalIter2>
	BidirectionalIter2
		copy_backward(BidirectionalIter1 first, BidirectionalIter1 last, BidirectionalIter2 result)
	{
		return unchecked_copy_backward(first, last, result);
	}


	/**************************************************
	@brief   : copy_if
	@author  : zenghao
	@input   ：first,last,result,unary_pred(条件)
	@output  ：result
	**************************************************/
	template <class InputIter, class OutputIter, class UnaryPredicate>
	OutputIter
		copy_if(InputIter first, InputIter last, OutputIter result, UnaryPredicate unary_pred)
	{
		for (; first != last; ++first)
		{
			if (unary_pred(*first))
				*result++ = *first;
		}
		return result;
	}


	/**************************************************
	@brief   : copy_n 把 [first, first + n)区间上的元素拷贝到 [result, result + n)上
	@author  : zenghao
	@input   ：first,n,result
	@output  ：pair<InputIter, OutputIter>
	**************************************************/
	template <class InputIter, class Size, class OutputIter>
	mystl::pair<InputIter, OutputIter>
		unchecked_copy_n(InputIter first, Size n, OutputIter result, mystl::input_iterator_tag)
	{
		for (; n > 0; --n, ++first, ++result)
		{
			*result = *first;
		}
		return mystl::pair<InputIter, OutputIter>(first, result);
	}

	template <class RandomIter, class Size, class OutputIter>
	mystl::pair<RandomIter, OutputIter>
		unchecked_copy_n(RandomIter first, Size n, OutputIter result,
			mystl::random_access_iterator_tag)
	{
		auto last = first + n;
		return mystl::pair<RandomIter, OutputIter>(last, mystl::copy(first, last, result));
	}

	template <class InputIter, class Size, class OutputIter>
	mystl::pair<InputIter, OutputIter>
		copy_n(InputIter first, Size n, OutputIter result)
	{
		return unchecked_copy_n(first, n, result, iterator_category(first));
	}


	/**************************************************
	@brief   : move 把 [first, last)区间内的元素移动到 [result, result + (last - first))内
	@author  : zenghao
	@input   ：first,last,result
	@output  ：Up*
	**************************************************/
	template <class Tp, class Up>
	Up* unchecked_move(Tp* first, Tp* last, Up* result)
	{
		const size_t n = static_cast<size_t>(last - first);
		if (n != 0)
			std::memmove(result, first, n * sizeof(Up));
		return result + n;
	}
	template <class InputIter, class OutputIter>
	OutputIter move(InputIter first, InputIter last, OutputIter result)
	{
		return unchecked_move(first, last, result);
	}

	/**************************************************
	@brief   : move_backward 将 [first, last)区间内的元素移动到 [result - (last - first), result)
	@author  : zenghao
	@input   ：first,last,result
	@output  ：Up*
	**************************************************/
	template <class Tp, class Up>
	Up* unchecked_move_backward(Tp* first, Tp* last, Up* result)
	{
		const size_t n = static_cast<size_t>(last - first);
		if (n != 0)
		{
			result -= n;
			std::memmove(result, first, n * sizeof(Up));
		}
		return result;
	}
	template <class BidirectionalIter1, class BidirectionalIter2>
	BidirectionalIter2
		move_backward(BidirectionalIter1 first, BidirectionalIter1 last, BidirectionalIter2 result)
	{
		return unchecked_move_backward(first, last, result);
	}


	/**************************************************
	@brief   : equal 比较第一序列在 [first, last)区间上的元素值是否和第二序列相等
	@author  : zenghao
	@input   ：first1,last1,first2
	@output  ：bool
	**************************************************/
	template <class InputIter1, class InputIter2>
	bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (*first1 != *first2)
				return false;
		}
		return true;
	}
	// 重载版本使用函数对象 comp 代替比较操作
	template <class InputIter1, class InputIter2, class Compared>
	bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2, Compared comp)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!comp(*first1, *first2))
				return false;
		}
		return true;
	}

	/**************************************************
	@brief   : fill 为 [first, last)区间内的所有元素填充新值
	@author  : zenghao
	@input   ：first,last,value
	@output  ：none
	**************************************************/
	template <class ForwardIter, class T>
	void fill_cat(ForwardIter first, ForwardIter last, const T& value)
	{
		for (; first != last; ++first)
		{
			*first = value;
		}
	}
	template <class RandomIter, class T>
	void fill_cat(RandomIter first, RandomIter last, const T& value,
		mystl::random_access_iterator_tag)
	{
		fill_n(first, last - first, value);
	}
	template <class ForwardIter, class T>
	void fill(ForwardIter first, ForwardIter last, const T& value)
	{
		fill_cat(first, last, value);//修改
	}

	/**************************************************
	@brief   : fill_n 从 first 位置开始填充 n 个值
	@author  : zenghao
	@input   ：first,n,value
	@output  ：OutputIter
	**************************************************/
	template <class OutputIter, class Size, class T>
	OutputIter unchecked_fill_n(OutputIter first, Size n, const T& value)
	{
		for (; n > 0; --n, ++first)
		{
			*first = value;
		}
		return first;
	}
	template <class OutputIter, class Size, class T>
	OutputIter fill_n(OutputIter first, Size n, const T& value)
	{
		return unchecked_fill_n(first, n, value);
	}

	/**************************************************
	@brief   : iter_swap  将两个迭代器所指对象对调
	@author  : zenghao
	@input   ：lhs,rhs
	@output  ：none
	**************************************************/
	template <class FIter1, class FIter2>
	void iter_swap(FIter1 lhs, FIter2 rhs)
	{
		mystl::swap(*lhs, *rhs);
	}


	/**************************************************
	@brief   : lexicographical_compare 
	以字典序排列对两个序列进行比较，当在某个位置发现第一组不相等元素时，有下列几种情况：
	 (1)如果第一序列的元素较小，返回 true ，否则返回 false
	 (2)如果到达 last1 而尚未到达 last2 返回 true
	 (3)如果到达 last2 而尚未到达 last1 返回 false
	 (4)如果同时到达 last1 和 last2 返回 false
	@author  : zenghao
	@input   ：first1,last1,first2,last2
	@output  ：none
	**************************************************/
	template <class InputIter1, class InputIter2>
	bool lexicographical_compare(InputIter1 first1, InputIter1 last1,
		InputIter2 first2, InputIter2 last2)
	{
		for (; first1 != last1 && first2 != last2; ++first1, ++first2)
		{
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
		}
		return first1 == last1 && first2 != last2;
	}

	/**************************************************
	@brief   : max 两者中的最大值
	@author  : zenghao
	@input   ：lhs，rhs
	@output  ：
	**************************************************/
	template <class T>
	const T& max(const T& lhs, const T& rhs)
	{
		return lhs < rhs ? rhs : lhs;
	}
	// 重载版本使用函数对象 comp 代替比较操作
	template <class T, class Compare>
	const T& max(const T& lhs, const T& rhs, Compare comp)
	{
		return comp(lhs, rhs) ? rhs : lhs;
	}

	/**************************************************
	@brief   : min
	@author  : zenghao
	@input   ：lhs,rhs
	@output  ：T
	**************************************************/
	template <class T>
		const T& min(const T& lhs, const T& rhs)
	{
		return rhs < lhs ? rhs : lhs;
	}

	// 重载版本使用函数对象 comp 代替比较操作
	template <class T, class Compare>
	const T& min(const T& lhs, const T& rhs, Compare comp)
	{
		return comp(rhs, lhs) ? rhs : lhs;
	}


	/**************************************************
	@brief   : mismatch 平行比较两个序列，找到第一处失配的元素，返回一对迭代器，分别指向两个序列中失配的元素
	@author  : zenghao
	@input   ：first1,last1,first2
	@output  ：pair
	**************************************************/
	template <class InputIter1, class InputIter2>
	mystl::pair<InputIter1, InputIter2>
		mismatch(InputIter1 first1, InputIter1 last1, InputIter2 first2)
	{
		while (first1 != last1 && *first1 == *first2)
		{
			++first1;
			++first2;
		}
		return mystl::pair<InputIter1, InputIter2>(first1, first2);
	}

	// 重载版本使用函数对象 comp 代替比较操作
	template <class InputIter1, class InputIter2, class Compred>
	mystl::pair<InputIter1, InputIter2>
		mismatch(InputIter1 first1, InputIter1 last1, InputIter2 first2, Compred comp)
	{
		while (first1 != last1 && comp(*first1, *first2))
		{
			++first1;
			++first2;
		}
		return mystl::pair<InputIter1, InputIter2>(first1, first2);
	}

	/**************************************************
	@brief   : make_heap 该函数接受两个迭代器，表示 heap 容器的首尾，把容器内的数据变为一个 heap
	@author  : zenghao
	@input   ：none
	@output  ：none
	**************************************************/
	// 该函数接受两个迭代器，表示一个 heap 容器的首尾，并且新元素已经插入到底部容器的最尾端，调整 heap
	template <class RandomIter, class Distance, class T>
	void push_heap_aux(RandomIter first, Distance holeIndex, Distance topIndex, T value)
	{
		auto parent = (holeIndex - 1) / 2;
		while (holeIndex > topIndex && *(first + parent) < value)
		{
			// 使用 operator<，所以 heap 为 max-heap
			*(first + holeIndex) = *(first + parent);
			holeIndex = parent;
			parent = (holeIndex - 1) / 2;
		}
		*(first + holeIndex) = value;
	}
	// 重载版本使用函数对象 comp 代替比较操作
	template <class RandomIter, class Distance, class T, class Compared>
	void push_heap_aux(RandomIter first, Distance holeIndex, Distance topIndex, T value,
		Compared comp)
	{
		auto parent = (holeIndex - 1) / 2;
		while (holeIndex > topIndex && comp(*(first + parent), value))
		{
			*(first + holeIndex) = *(first + parent);
			holeIndex = parent;
			parent = (holeIndex - 1) / 2;
		}
		*(first + holeIndex) = value;
	}

	template <class RandomIter, class T, class Distance>
	// 该函数接受两个迭代器，表示 heap 容器的首尾，将 heap 的根节点取出放到容器尾部，调整 heap
	void adjust_heap(RandomIter first, Distance holeIndex, Distance len, T value)
	{
		// 先进行下溯(percolate down)过程
		auto topIndex = holeIndex;
		auto rchild = 2 * holeIndex + 2;
		while (rchild < len)
		{
			if (*(first + rchild) < *(first + rchild - 1))
				--rchild;
			*(first + holeIndex) = *(first + rchild);
			holeIndex = rchild;
			rchild = 2 * (rchild + 1);
		}
		if (rchild == len)
		{  // 如果没有右子节点
			*(first + holeIndex) = *(first + (rchild - 1));
			holeIndex = rchild - 1;
		}
		// 再执行一次上溯(percolate up)过程
		mystl::push_heap_aux(first, holeIndex, topIndex, value);
	}
	// 重载版本使用函数对象 comp 代替比较操作
	template <class RandomIter, class T, class Distance, class Compared>
	void adjust_heap(RandomIter first, Distance holeIndex, Distance len, T value,
		Compared comp)
	{
		// 先进行下溯(percolate down)过程
		auto topIndex = holeIndex;
		auto rchild = 2 * holeIndex + 2;
		while (rchild < len)
		{
			if (comp(*(first + rchild), *(first + rchild - 1)))  --rchild;
			*(first + holeIndex) = *(first + rchild);
			holeIndex = rchild;
			rchild = 2 * (rchild + 1);
		}
		if (rchild == len)
		{
			*(first + holeIndex) = *(first + (rchild - 1));
			holeIndex = rchild - 1;
		}
		// 再执行一次上溯(percolate up)过程
		mystl::push_heap_aux(first, holeIndex, topIndex, value, comp);
	}
	template <class RandomIter, class Distance>
	void make_heap_aux(RandomIter first, RandomIter last, Distance*)
	{
		if (last - first < 2)
			return;
		auto len = last - first;
		auto holeIndex = (len - 2) / 2;
		while (true)
		{
			// 重排以 holeIndex 为首的子树
			mystl::adjust_heap(first, holeIndex, len, *(first + holeIndex));
			if (holeIndex == 0)
				return;
			holeIndex--;
		}
	}
	// 重载版本使用函数对象 comp 代替比较操作
	template <class RandomIter, class Distance, class Compared>
	void make_heap_aux(RandomIter first, RandomIter last, Distance*, Compared comp)
	{
		if (last - first < 2)
			return;
		auto len = last - first;
		auto holeIndex = (len - 2) / 2;
		while (true)
		{
			// 重排以 holeIndex 为首的子树
			mystl::adjust_heap(first, holeIndex, len, *(first + holeIndex), comp);
			if (holeIndex == 0)
				return;
			holeIndex--;
		}
	}
	template <class RandomIter>
	void make_heap(RandomIter first, RandomIter last)
	{
		mystl::make_heap_aux(first, last, distance_type(first));;
	}
	// 重载版本使用函数对象 comp 代替比较操作
	template <class RandomIter, class Compared>
	void make_heap(RandomIter first, RandomIter last, Compared comp)
	{
		mystl::make_heap_aux(first, last, distance_type(first), comp);
	}
	/**************************************************
	@brief   : pop_heap
	@author  : zenghao
	@input   ：first,last
	@output  ：none
	**************************************************/
	template <class RandomIter, class T, class Distance>
	void pop_heap_aux(RandomIter first, RandomIter last, RandomIter result, T value,
		Distance*)
	{
		// 先将首值调至尾节点，然后调整[first, last - 1)使之重新成为一个 max-heap
		*result = *first;
		mystl::adjust_heap(first, static_cast<Distance>(0), last - first, value);
	}
	template <class RandomIter, class T, class Distance, class Compared>
	// 重载版本使用函数对象 comp 代替比较操作
	void pop_heap_aux(RandomIter first, RandomIter last, RandomIter result,
		T value, Distance*, Compared comp)
	{
		*result = *first;  // 先将尾指设置成首值，即尾指为欲求结果
		mystl::adjust_heap(first, static_cast<Distance>(0), last - first, value, comp);
	}
	template <class RandomIter>
	void pop_heap(RandomIter first, RandomIter last)
	{
		mystl::pop_heap_aux(first, last - 1, last - 1, *(last - 1), distance_type(first));
	}
	// 重载版本使用函数对象 comp 代替比较操作
	template <class RandomIter, class Compared>
	void pop_heap(RandomIter first, RandomIter last, Compared comp)
	{
		mystl::pop_heap_aux(first, last - 1, last - 1, *(last - 1),
			distance_type(first), comp);
	}
	/**************************************************
	@brief   : push_heap push_heap_aux前文已经定义
	@author  : zenghao
	@input   ：first，last
	@output  ：none
	**************************************************/
	template <class RandomIter, class Distance>
	void push_heap_d(RandomIter first, RandomIter last, Distance*)
	{
		mystl::push_heap_aux(first, (last - first) - 1, static_cast<Distance>(0), *(last - 1));
	}

	template <class RandomIter>
	void push_heap(RandomIter first, RandomIter last)
	{ // 新元素应该已置于底部容器的最尾端
		mystl::push_heap_d(first, last, distance_type(first));
	}
	// 重载版本使用函数对象 comp 代替比较操作
	template <class RandomIter, class Compared, class Distance>
	void push_heap_d(RandomIter first, RandomIter last, Distance*, Compared comp)
	{
		mystl::push_heap_aux(first, (last - first) - 1, static_cast<Distance>(0),
			*(last - 1), comp);
	}

	template <class RandomIter, class Compared>
	void push_heap(RandomIter first, RandomIter last, Compared comp)
	{
		mystl::push_heap_d(first, last, distance_type(first), comp);
	}
	/**************************************************
	@brief   : sort_heap 该函数接受两个迭代器，表示 heap 容器的首尾，不断执行 pop_heap 操作，直到首尾最多相差1
	@author  : zenghao
	@input   ：first,last
	@output  ：none
	**************************************************/
	template <class RandomIter>
	void sort_heap(RandomIter first, RandomIter last)
	{
		// 每执行一次 pop_heap，最大的元素都被放到尾部，直到容器最多只有一个元素，完成排序
		while (last - first > 1)
		{
			mystl::pop_heap(first, last--);
		}
	}

	// 重载版本使用函数对象 comp 代替比较操作
	template <class RandomIter, class Compared>
	void sort_heap(RandomIter first, RandomIter last, Compared comp)
	{
		while (last - first > 1)
		{
			mystl::pop_heap(first, last--, comp);
		}
	}


	/**************************************************
	@brief   : set_difference  计算 S1-S2 的结果并保存到 result 中，返回一个迭代器指向输出结果的尾部
	@author  : zenghao
	@input   ：first1,last1,first2,last2
	@output  ：none
	**************************************************/
	template <class InputIter1, class InputIter2, class OutputIter>
	OutputIter set_difference(InputIter1 first1, InputIter1 last1,
		InputIter2 first2, InputIter2 last2,
		OutputIter result)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first1 < *first2)
			{
				*result = *first1;
				++first1;
				++result;
			}
			else if (*first2 < *first1)
			{
				++first2;
			}
			else
			{
				++first1;
				++first2;
			}
		}
		return mystl::copy(first1, last1, result);
	}

	// 重载版本使用函数对象 comp 代替比较操作
	template <class InputIter1, class InputIter2, class OutputIter, class Compared>
	OutputIter set_difference(InputIter1 first1, InputIter1 last1,
		InputIter2 first2, InputIter2 last2,
		OutputIter result, Compared comp)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (comp(*first1, *first2))
			{
				*result = *first1;
				++first1;
				++result;
			}
			else if (comp(*first2, *first1))
			{
				++first2;
			}
			else
			{
				++first1;
				++first2;
			}
		}
		return mystl::copy(first1, last1, result);
	}


	/**************************************************
	@brief   : set_intersection 计算 S1∩S2 的结果并保存到 result 中，返回一个迭代器指向输出结果的尾部
	@author  : zenghao
	@input   ：first1,last1,first2,last2  
	@output  ：none
	**************************************************/
	template <class InputIter1, class InputIter2, class OutputIter>
	OutputIter set_intersection(InputIter1 first1, InputIter1 last1,
		InputIter2 first2, InputIter2 last2,
		OutputIter result)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first1 < *first2)
			{
				++first1;
			}
			else if (*first2 < *first1)
			{
				++first2;
			}
			else
			{
				*result = *first1;
				++first1;
				++first2;
				++result;
			}
		}
		return result;
	}

	// 重载版本使用函数对象 comp 代替比较操作
	template <class InputIter1, class InputIter2, class OutputIter, class Compared>
	OutputIter set_intersection(InputIter1 first1, InputIter1 last1,
		InputIter2 first2, InputIter2 last2,
		OutputIter result, Compared comp)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (comp(*first1, *first2))
			{
				++first1;
			}
			else if (comp(*first2, *first1))
			{
				++first2;
			}
			else
			{
				*result = *first1;
				++first1;
				++first2;
				++result;
			}
		}
		return result;
	}

	/**************************************************
	@brief   : set_symmetric_difference 计算 (S1-S2)∪(S2-S1) 的结果并保存到 result 中，返回一个迭代器指向输出结果的尾部
	@author  : zenghao
	@input   ：first1,last1,first2,last2  
	@output  ：none
	**************************************************/
	template <class InputIter1, class InputIter2, class OutputIter>
	OutputIter set_symmetric_difference(InputIter1 first1, InputIter1 last1,
		InputIter2 first2, InputIter2 last2,
		OutputIter result)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first1 < *first2)
			{
				*result = *first1;
				++first1;
				++result;
			}
			else if (*first2 < *first1)
			{
				*result = *first2;
				++first2;
				++result;
			}
			else
			{
				++first1;
				++first2;
			}
		}
		return mystl::copy(first2, last2, mystl::copy(first1, last1, result));
	}

	// 重载版本使用函数对象 comp 代替比较操作
	template <class InputIter1, class InputIter2, class OutputIter, class Compared>
	OutputIter set_symmetric_difference(InputIter1 first1, InputIter1 last1,
		InputIter2 first2, InputIter2 last2,
		OutputIter result, Compared comp)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (comp(*first1, *first2))
			{
				*result = *first1;
				++first1;
				++result;
			}
			else if (comp(*first2, *first1))
			{
				*result = *first2;
				++first2;
				++result;
			}
			else
			{
				++first1;
				++first2;
			}
		}
		return mystl::copy(first2, last2, mystl::copy(first1, last1, result));
	}

	/**************************************************
	@brief   : set_union 计算 S1∪S2 的结果并保存到 result 中，返回一个迭代器指向输出结果的尾部
	@author  : zenghao
	@input   ：first1,last1,first2,last2  
	@output  ：none
	**************************************************/
	template <class InputIter1, class InputIter2, class OutputIter>
	OutputIter set_union(InputIter1 first1, InputIter1 last1,
		InputIter2 first2, InputIter2 last2,
		OutputIter result)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first1 < *first2)
			{
				*result = *first1;
				++first1;
			}
			else if (*first2 < *first1)
			{
				*result = *first2;
				++first2;
			}
			else
			{
				*result = *first1;
				++first1;
				++first2;
			}
			++result;
		}
		// 将剩余元素拷贝到 result
		return mystl::copy(first2, last2, mystl::copy(first1, last1, result));
	}

	// 重载版本使用函数对象 comp 代替比较操作
	template <class InputIter1, class InputIter2, class OutputIter, class Compared>
	OutputIter set_union(InputIter1 first1, InputIter1 last1,
		InputIter2 first2, InputIter2 last2,
		OutputIter result, Compared comp)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (comp(*first1, *first2))
			{
				*result = *first1;
				++first1;
			}
			else if (comp(*first2, *first1))
			{
				*result = *first2;
				++first2;
			}
			else
			{
				*result = *first1;
				++first1;
				++first2;
			}
			++result;
		}
		// 将剩余元素拷贝到 result
		return mystl::copy(first2, last2, mystl::copy(first1, last1, result));
	}
	/**************************************************
	@brief   : accumulate first至last求和
	版本1：以初值 init 对每个元素进行累加
	版本2：以初值 init 对每个元素进行二元操作
	@author  : zenghao
	@input   ：first,last,init
	@output  ：T
	**************************************************/
	// 版本1
	template <class InputIter, class T>
	T accumulate(InputIter first, InputIter last, T init)
	{
		for (; first != last; ++first)
		{
			init += *first;
		}
		return init;
	}

	// 版本2
	template <class InputIter, class T, class BinaryOp>
	T accumulate(InputIter first, InputIter last, T init, BinaryOp binary_op)
	{
		for (; first != last; ++first)
		{
			init = binary_op(init, *first);
		}
		return init;
	}
	/**************************************************
	@brief   : adjacent_difference 
	版本1：计算相邻元素的差值，结果保存到以 result 为起始的区间上
	版本2：自定义相邻元素的二元操作
	@author  : zenghao
	@input   ：first,last,result
	@output  ：none
	**************************************************/
	template <class InputIter, class OutputIter>
	OutputIter adjacent_difference(InputIter first, InputIter last, OutputIter result)
	{
		if (first == last)  return result;
		*result = *first;  // 记录第一个元素
		auto value = *first;
		while (++first != last)
		{
			auto tmp = *first;
			*++result = tmp - value;
			value = tmp;
		}
		return ++result;
	}

	// 版本2
	template <class InputIter, class OutputIter, class BinaryOp>
	OutputIter adjacent_difference(InputIter first, InputIter last, OutputIter result,
		BinaryOp binary_op)
	{
		if (first == last)  return result;
		*result = *first;  // 记录第一个元素
		auto value = *first;
		while (++first != last)
		{
			auto tmp = *first;
			*++result = binary_op(tmp, value);
			value = tmp;
		}
		return ++result;
	}
	/**************************************************
	@brief   : inner_product
	版本1：以 init 为初值，计算两个区间的内积
	版本2：自定义 operator+ 和 operator*
	@author  : zenghao
	@input   ：first1,last1,first2,init
	@output  ：none
	**************************************************/
	template <class InputIter1, class InputIter2, class T>
	T inner_product(InputIter1 first1, InputIter1 last1, InputIter2 first2, T init)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			init = init + (*first1 * *first2);
		}
		return init;
	}

	// 版本2
	template <class InputIter1, class InputIter2, class T, class BinaryOp1, class BinaryOp2>
	T inner_product(InputIter1 first1, InputIter1 last1, InputIter2 first2, T init,
		BinaryOp1 binary_op1, BinaryOp2 binary_op2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			init = binary_op1(init, binary_op2(*first1, *first2));
		}
		return init;
	}
	/**************************************************
	@brief   : iota 填充[first, last)，以 value++ 为初值开始递增
	@author  : zenghao
	@input   ：first,last,value
	@output  ：none
	**************************************************/
	template <class ForwardIter, class T>
	void iota(ForwardIter first, ForwardIter last, T value)
	{
		while (first != last)
		{
			*first++ = value;
			++value;
		}
	}
	/**************************************************
	@brief   : partial_sum
	版本1：计算局部累计求和，结果保存到以 result 为起始的区间上
	版本2：进行局部进行自定义二元操作
	@author  : zenghao
	@input   ：first,last,result
	@output  ：OutputIter
	**************************************************/
	template <class InputIter, class OutputIter>
	OutputIter partial_sum(InputIter first, InputIter last, OutputIter result)
	{
		if (first == last)  return result;
		*result = *first;  // 记录第一个元素
		auto value = *first;
		while (++first != last)
		{
			value = value + *first;
			*++result = value;
		}
		return ++result;
	}

	// 版本2
	template <class InputIter, class OutputIter, class BinaryOp>
	OutputIter partial_sum(InputIter first, InputIter last, OutputIter result,
		BinaryOp binary_op)
	{
		if (first == last)  return result;
		*result = *first;  //记录第一个元素
		auto value = *first;
		while (++first != last)
		{
			value = binary_op(value, *first);
			*++result = value;
		}
		return ++result;
	}
	/**************************************************
	@brief   : adjacent_find 找出第一对相等的相邻元素，指向这对元素的第一个元素
	@author  : zenghao
	@input   ：first,last
	@output  ：none
	**************************************************/
	template <class ForwardIter>
	ForwardIter adjacent_find(ForwardIter first, ForwardIter last)
	{
		if (first == last)  return last;
		auto next = first;
		while (++next != last)
		{
			if (*first == *next)  return first;
			first = next;
		}
		return last;
	}
	/**************************************************
	@brief   : all_of 检查[first, last)内是否全部元素都满足一元操作 unary_pred 为 true 的情况，满足则返回 true
	@author  : zenghao
	@input   ：first,last,unary_pred
	@output  ：none
	**************************************************/
	template <class InputIter, class UnaryPredicate>
	bool all_of(InputIter first, InputIter last, UnaryPredicate unary_pred)
	{
		for (; first != last; ++first)
		{
			if (!unary_pred(*first))
				return false;
		}
		return true;
	}
	/**************************************************
	@brief   : any_of 检查[first, last)内是否存在某个元素满足一元操作 unary_pred 为 true 的情况，满足则返回 true
	@author  : zenghao
	@input   ：first,last,unary_pred
	@output  ：none
	**************************************************/
	template <class InputIter, class UnaryPredicate>
	bool any_of(InputIter first, InputIter last, UnaryPredicate unary_pred)
	{
		for (; first != last; ++first)
		{
			if (unary_pred(*first))
				return true;
		}
		return false;
	}
	/**************************************************
	@brief   : binary_search 二分查找 
	@brief	 : lower_bound 在[first, last)中查找第一个不小于 value 的元素，并返回指向它的迭代器，若没有则返回 last
	@author  : zenghao
	@input   ：first，last，value
	@output  ：none
	**************************************************/
	template <class ForwardIter, class T>
	ForwardIter lbound_dispatch(ForwardIter first, ForwardIter last,
		const T& value, forward_iterator_tag)
	{
		auto len = mystl::distance(first, last);
		auto half = len;
		ForwardIter middle;
		while (len > 0)
		{
			half = len >> 1;
			middle = first;
			mystl::advance(middle, half);
			if (*middle < value)
			{
				first = middle;
				++first;
				len = len - half - 1;
			}
			else
			{
				len = half;
			}
		}
		return first;
	}
	// 重载版本使用函数对象 comp 代替比较操作
	template <class ForwardIter, class T, class Compared>
	ForwardIter lbound_dispatch(ForwardIter first, ForwardIter last,
		const T& value, forward_iterator_tag, Compared comp)
	{
		auto len = mystl::distance(first, last);
		auto half = len;
		ForwardIter middle;
		while (len > 0)
		{
			half = len >> 1;
			middle = first;
			mystl::advance(middle, half);
			if (comp(*middle, value))
			{
				first = middle;
				++first;
				len = len - half - 1;
			}
			else
			{
				len = half;
			}
		}
		return first;
	}
	template <class ForwardIter, class T>
	ForwardIter lower_bound(ForwardIter first, ForwardIter last, const T& value)
	{
		return mystl::lbound_dispatch(first, last, value, iterator_category(first));
	}
	// 重载版本使用函数对象 comp 代替比较操作
	template <class ForwardIter, class T, class Compared>
	ForwardIter lower_bound(ForwardIter first, ForwardIter last, const T& value, Compared comp)
	{
		return mystl::lbound_dispatch(first, last, value, iterator_category(first), comp);
	}

	template <class ForwardIter, class T>
	bool binary_search(ForwardIter first, ForwardIter last, const T& value)
	{
		auto i = mystl::lower_bound(first, last, value);
		return i != last && !(value < *i);
	}

	/**************************************************
	@brief   : count 数组等于value的计数
	@author  : zenghao
	@input   ：first,last,value
	@output  ：int
	**************************************************/
	template <class InputIter, class T>
	size_t count(InputIter first, InputIter last, const T& value)
	{
		size_t n = 0;
		for (; first != last; ++first)
		{
			if (*first == value)
				++n;
		}
		return n;
	}
	/**************************************************
	@brief   : count_if 对[first, last)区间内的每个元素都进行一元 unary_pred 操作，返回结果为 true 的个数
	@author  : zenghao
	@input   ：first,last,unary_pred
	@output  ：n
	**************************************************/
	template <class InputIter, class UnaryPredicate>
	size_t count_if(InputIter first, InputIter last, UnaryPredicate unary_pred)
	{
		size_t n = 0;
		for (; first != last; ++first)
		{
			if (unary_pred(*first))
				++n;
		}
		return n;
	}
	/**************************************************
	@brief   : upper_bound 在[first, last)中查找第一个大于value 的元素，并返回指向它的迭代器，若没有则返回 last
	@author  : zenghao
	@input   ：first,last,value
	@output  ：
	**************************************************/
	template <class ForwardIter, class T>
	ForwardIter ubound_dispatch(ForwardIter first, ForwardIter last,
		const T& value, forward_iterator_tag)
	{
		auto len = mystl::distance(first, last);
		auto half = len;
		ForwardIter middle;
		while (len > 0)
		{
			half = len >> 1;
			middle = first;
			mystl::advance(middle, half);
			if (value < *middle)
			{
				len = half;
			}
			else
			{
				first = middle;
				++first;
				len = len - half - 1;
			}
		}
		return first;
	}
	template <class ForwardIter, class T>
	ForwardIter
		upper_bound(ForwardIter first, ForwardIter last, const T& value)
	{
		return mystl::ubound_dispatch(first, last, value, iterator_category(first));
	}
	/**************************************************
	@brief   : equal_range 查找[first,last)区间中与 value 相等的元素所形成的区间，返回一对迭代器指向区间首尾
	第一个迭代器指向第一个不小于 value 的元素，第二个迭代器指向第一个大于 value 的元素
	@author  : zenghao
	@input   ：none
	@output  ：none
	**************************************************/
	template <class ForwardIter, class T>
	mystl::pair<ForwardIter, ForwardIter> erange_dispatch(ForwardIter first, ForwardIter last,
			const T& value, forward_iterator_tag)
	{
		auto len = mystl::distance(first, last);
		auto half = len;
		ForwardIter middle, left, right;
		while (len > 0)
		{
			half = len >> 1;
			middle = first;
			mystl::advance(middle, half);
			if (*middle < value)
			{
				first = middle;
				++first;
				len = len - half - 1;
			}
			else if (value < *middle)
			{
				len = half;
			}
			else
			{
				left = mystl::lower_bound(first, last, value);
				mystl::advance(first, len);
				right = mystl::upper_bound(++middle, first, value);
				return mystl::pair<ForwardIter, ForwardIter>(left, right);
			}
		}
		return mystl::pair<ForwardIter, ForwardIter>(last, last);
	}

	template <class ForwardIter, class T>
	mystl::pair<ForwardIter, ForwardIter>
		equal_range(ForwardIter first, ForwardIter last, const T& value)
	{
		return mystl::erange_dispatch(first, last, value, iterator_category(first));
	}

	/**************************************************
	@brief   : find 在[first, last)区间内找到等于 value 的元素，返回指向该元素的迭代器
	@author  : zenghao
	@input   ：first,last,value
	@output  ：InputIter
	**************************************************/
	template <class InputIter, class T>
	InputIter
		find(InputIter first, InputIter last, const T& value)
	{
		while (first != last && *first != value)
			++first;
		return first;
	}
	/**************************************************
	@brief   : search 在[first1, last1)中查找[first2, last2)的首次出现点
	@author  : zenghao
	@input   ：none
	@output  ：none
	**************************************************/
	template <class ForwardIter1, class ForwardIter2>
	ForwardIter1
		search(ForwardIter1 first1, ForwardIter1 last1,
			ForwardIter2 first2, ForwardIter2 last2)
	{
		auto d1 = mystl::distance(first1, last1);
		auto d2 = mystl::distance(first2, last2);
		if (d1 < d2)
			return last1;
		auto current1 = first1;
		auto current2 = first2;
		while (current2 != last2)
		{
			if (*current1 == *current2)
			{
				++current1;
				++current2;
			}
			else
			{
				if (d1 == d2)
				{
					return last1;
				}
				else
				{
					current1 = ++first1;
					current2 = first2;
					--d1;
				}
			}
		}
		return first1;
	}
	/**************************************************
	@brief   : find_end 在[first1, last1)区间中查找[first2, last2)最后一次出现的地方，若不存在返回 last1
	@author  : zenghao
	@input   ：none
	@output  ：none
	**************************************************/
	// find_end_dispatch 的 forward_iterator_tag 版本
	template <class ForwardIter1, class ForwardIter2>
	ForwardIter1
		find_end_dispatch(ForwardIter1 first1, ForwardIter1 last1,
			ForwardIter2 first2, ForwardIter2 last2,
			forward_iterator_tag, forward_iterator_tag)
	{
		if (first2 == last2)
		{
			return last1;
		}
		else
		{
			auto result = last1;
			while (true)
			{
				// 利用 search 查找某个子序列的首次出现点，找不到则返回 last1
				auto new_result = mystl::search(first1, last1, first2, last2);
				if (new_result == last1)
				{
					return result;
				}
				else
				{
					result = new_result;
					first1 = new_result;
					++first1;
				}
			}
		}
	}

	// find_end_dispatch 的 bidirectional_iterator_tag 版本
	template <class BidirectionalIter1, class BidirectionalIter2>
	BidirectionalIter1
		find_end_dispatch(BidirectionalIter1 first1, BidirectionalIter1 last1,
			BidirectionalIter2 first2, BidirectionalIter2 last2,
			bidirectional_iterator_tag, bidirectional_iterator_tag)
	{
		typedef reverse_iterator<BidirectionalIter1> reviter1;
		typedef reverse_iterator<BidirectionalIter2> reviter2;
		reviter1 rlast1(first1);
		reviter2 rlast2(first2);
		reviter1 rresult = mystl::search(reviter1(last1), rlast1, reviter2(last2), rlast2);
		if (rresult == rlast1)
		{
			return last1;
		}
		else
		{
			auto result = rresult.base();
			mystl::advance(result, -mystl::distance(first2, last2));
			return result;
		}
	}

	template <class ForwardIter1, class ForwardIter2>
	ForwardIter1
		find_end(ForwardIter1 first1, ForwardIter1 last1,
			ForwardIter2 first2, ForwardIter2 last2)
	{
		typedef typename iterator_traits<ForwardIter1>::iterator_category Category1;
		typedef typename iterator_traits<ForwardIter2>::iterator_category Category2;
		return mystl::find_end_dispatch(first1, last1, first2, last2, Category1(), Category2());
	}

	/**************************************************
	@brief   : find_first_of 在[first1, last1)中查找[first2, last2)中的某些元素，返回指向第一次出现的元素的迭代器
	@author  : zenghao
	@input   ：first1,last1,first2,last2
	@output  ：none
	**************************************************/
	template <class InputIter, class ForwardIter>
	InputIter
		find_first_of(InputIter first1, InputIter last1,
			ForwardIter first2, ForwardIter last2)
	{
		for (; first1 != last1; ++first1)
		{
			for (auto iter = first2; iter != last2; ++iter)
			{
				if (*first1 == *iter)
					return first1;
			}
		}
		return last1;
	}

	/**************************************************
	@brief   : find_if 在[first, last)区间内找到第一个令一元操作 unary_pred 为 true 的元素并返回指向该元素的迭代器
	@author  : zenghao
	@input   ：first,last,unary_pred
	@output  ：InputIter
	**************************************************/
	template <class InputIter, class UnaryPredicate>
	InputIter
		find_if(InputIter first, InputIter last, UnaryPredicate unary_pred)
	{
		while (first != last && !unary_pred(*first))
			++first;
		return first;
	}
	/**************************************************
	@brief   : find_if_not
	@author  : zenghao
	@input   ：first,last,unary_pred
	@output  ：InputIter
	**************************************************/
	template <class InputIter, class UnaryPredicate>
	InputIter
		find_if_not(InputIter first, InputIter last, UnaryPredicate unary_pred)
	{
		while (first != last && unary_pred(*first))
			++first;
		return first;
	}
	/**************************************************
	@brief   : for_each 使用一个函数对象 f 对[first, last)区间内的每个元素执行一个 operator() 操作，但不能改变元素内容
	@author  : zenghao
	@input   ：first, last, Function f
	@output  ：Function
	**************************************************/
	template <class InputIter, class Function>
	Function for_each(InputIter first, InputIter last, Function f)
	{
		for (; first != last; ++first)
		{
			f(*first);
		}
		return f;
	}
	/**************************************************
	@brief   : generate 将函数对象 gen 的运算结果对[first, last)内的每个元素赋值
	@author  : zenghao
	@input   ：ForwardIter first, ForwardIter last, Generator gen
	@output  ：none
	**************************************************/
	template <class ForwardIter, class Generator>
	void generate(ForwardIter first, ForwardIter last, Generator gen)
	{
		for (; first != last; ++first)
		{
			*first = gen();
		}
	}
	/**************************************************
	@brief   : generate_n 用函数对象 gen 连续对 n 个元素赋值
	@author  : zenghao
	@input   ：ForwardIter first, Size n, Generator gen
	@output  ：none
	**************************************************/
	template <class ForwardIter, class Size, class Generator>
	void generate_n(ForwardIter first, Size n, Generator gen)
	{
		for (; n > 0; --n, ++first)
		{
			*first = gen();
		}
	}
	/**************************************************
	@brief   : includes 判断序列一 S1 传入的元素是否小于序列二 S2 传入的元素
	@author  : zenghao
	@input   ：InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2
	@output  ：bool
	**************************************************/
	template <class InputIter1, class InputIter2>
	bool includes(InputIter1 first1, InputIter1 last1,
		InputIter2 first2, InputIter2 last2)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first2 < *first1)
			{
				return false;
			}
			else if (*first1 < *first2)
			{
				++first1;
			}
			else
			{
				++first1, ++first2;
			}
		}
		return first2 == last2;
	}
	/**************************************************
	@brief   : rotate 将[first, middle)内的元素和 [middle, last)内的元素互换，可以交换两个长度不同的区间
	@author  : zenghao
	@input   ：none
	@output  ：返回交换后 middle 的位置
	**************************************************/
	template <class ForwardIter>
	ForwardIter
		rotate_dispatch(ForwardIter first, ForwardIter middle,
			ForwardIter last, forward_iterator_tag)
	{
		auto first2 = middle;
		do
		{
			mystl::swap(*first++, *first2++);
			if (first == middle)
				middle = first2;
		} while (first2 != last);  // 后半段移到前面

		auto new_middle = first;   // 迭代器返回的位置
		first2 = middle;
		while (first2 != last)
		{   // 调整剩余元素
			mystl::swap(*first++, *first2++);
			if (first == middle)
			{
				middle = first2;
			}
			else if (first2 == last)
			{
				first2 = middle;
			}
		}
		return new_middle;
	}
	template <class ForwardIter>
	ForwardIter
		rotate(ForwardIter first, ForwardIter middle, ForwardIter last)
	{
		if (first == middle)
			return last;
		if (middle == last)
			return first;
		return mystl::rotate_dispatch(first, middle, last, iterator_category(first));
	}
	/**************************************************
	@brief   : inplace_merge 把连接在一起的两个有序序列结合成单一序列并保持有序
	@author  : zenghao
	@input   ：BidirectionalIter first, BidirectionalIter middle,BidirectionalIter last
	@output  ：none
	**************************************************/
	template <class BidirectionalIter, class Distance>
	void merge_without_buffer(BidirectionalIter first, BidirectionalIter middle,
		BidirectionalIter last, Distance len1, Distance len2)
	{
		if (len1 == 0 || len2 == 0)
			return;
		if (len1 + len2 == 2)
		{
			if (*middle < *first)
				mystl::iter_swap(first, middle);
			return;
		}
		auto first_cut = first;
		auto second_cut = middle;
		Distance len11 = 0;
		Distance len22 = 0;
		if (len1 > len2)
		{  // 序列一较长，找到序列一的中点
			len11 = len1 >> 1;
			mystl::advance(first_cut, len11);
			second_cut = mystl::lower_bound(middle, last, *first_cut);
			len22 = mystl::distance(middle, second_cut);
		}
		else
		{              // 序列二较长，找到序列二的中点
			len22 = len2 >> 1;
			mystl::advance(second_cut, len22);
			first_cut = mystl::upper_bound(first, middle, *second_cut);
			len11 = mystl::distance(first, first_cut);
		}
		auto new_middle = mystl::rotate(first_cut, middle, second_cut);
		mystl::merge_without_buffer(first, first_cut, new_middle, len11, len22);
		mystl::merge_without_buffer(new_middle, second_cut, last, len1 - len11, len2 - len22);
	}
	template <class BidirectionalIter1, class BidirectionalIter2>
	BidirectionalIter1
		merge_backward(BidirectionalIter1 first1, BidirectionalIter1 last1,
			BidirectionalIter2 first2, BidirectionalIter2 last2,
			BidirectionalIter1 result)
	{
		if (first1 == last1)
			return mystl::copy_backward(first2, last2, result);
		if (first2 == last2)
			return mystl::copy_backward(first1, last1, result);
		--last1;
		--last2;
		while (true)
		{
			if (*last2 < *last1)
			{
				*--result = *last1;
				if (first1 == last1)
					return mystl::copy_backward(first2, ++last2, result);
				--last1;
			}
			else
			{
				*--result = *last2;
				if (first2 == last2)
					return mystl::copy_backward(first1, ++last1, result);
				--last2;
			}
		}
	}
	template <class BidirectionalIter1, class BidirectionalIter2, class Distance>
	BidirectionalIter1
		rotate_adaptive(BidirectionalIter1 first, BidirectionalIter1 middle,
			BidirectionalIter1 last, Distance len1, Distance len2,
			BidirectionalIter2 buffer, Distance buffer_size)
	{
		BidirectionalIter2 buffer_end;
		if (len1 > len2 && len2 <= buffer_size)
		{
			buffer_end = mystl::copy(middle, last, buffer);
			mystl::copy_backward(first, middle, last);
			return mystl::copy(buffer, buffer_end, first);
		}
		else if (len1 <= buffer_size)
		{
			buffer_end = mystl::copy(first, middle, buffer);
			mystl::copy(middle, last, first);
			return mystl::copy_backward(buffer, buffer_end, last);
		}
		else
		{
			return mystl::rotate(first, middle, last);
		}
	}

	// 有缓冲区的情况下合并
	template <class BidirectionalIter, class Distance, class Pointer>
	void merge_adaptive(BidirectionalIter first, BidirectionalIter middle,
		BidirectionalIter last, Distance len1, Distance len2,
		Pointer buffer, Distance buffer_size)
	{
		// 区间长度足够放进缓冲区
		if (len1 <= len2 && len1 <= buffer_size)
		{
			Pointer buffer_end = mystl::copy(first, middle, buffer);
			mystl::merge(buffer, buffer_end, middle, last, first);
		}
		else if (len2 <= buffer_size)
		{
			Pointer buffer_end = mystl::copy(middle, last, buffer);
			mystl::merge_backward(first, middle, buffer, buffer_end, last);
		}
		else
		{  // 区间长度太长，分割递归处理
			auto first_cut = first;
			auto second_cut = middle;
			Distance len11 = 0;
			Distance len22 = 0;
			if (len1 > len2)
			{
				len11 = len1 >> 1;
				mystl::advance(first_cut, len11);
				second_cut = mystl::lower_bound(middle, last, *first_cut);
				len22 = mystl::distance(middle, second_cut);
			}
			else
			{
				len22 = len2 >> 1;
				mystl::advance(second_cut, len22);
				first_cut = mystl::upper_bound(first, middle, *second_cut);
				len11 = mystl::distance(first, first_cut);
			}
			auto new_middle = mystl::rotate_adaptive(first_cut, middle, second_cut,
				len1 - len11, len22, buffer, buffer_size);
			mystl::merge_adaptive(first, first_cut, new_middle, len11, len22, buffer, buffer_size);
			mystl::merge_adaptive(new_middle, second_cut, last, len1 - len11,
				len2 - len22, buffer, buffer_size);
		}
	}

	template <class BidirectionalIter, class T>
	void
		inplace_merge_aux(BidirectionalIter first, BidirectionalIter middle,
			BidirectionalIter last, T*)
	{
		auto len1 = mystl::distance(first, middle);
		auto len2 = mystl::distance(middle, last);
		temporary_buffer<BidirectionalIter, T> buf(first, last);
		if (!buf.begin())
		{
			mystl::merge_without_buffer(first, middle, last, len1, len2);
		}
		else
		{
			mystl::merge_adaptive(first, middle, last, len1, len2, buf.begin(), buf.size());
		}
	}

	template <class BidirectionalIter>
	void
		inplace_merge(BidirectionalIter first, BidirectionalIter middle,
			BidirectionalIter last)
	{
		if (first == middle || middle == last)
			return;
		mystl::inplace_merge_aux(first, middle, last, value_type(first));
	}
	/**************************************************
	@brief   : merge 将两个经过排序的集合 S1 和 S2 合并起来置于另一段空间，返回一个迭代器指向最后一个元素的下一位置
	@author  : zenghao
	@input   ：InputIter1 first1, InputIter1 last1,InputIter2 first2, InputIter2 last2,OutputIter result
	@output  ：none
	**************************************************/
	template <class InputIter1, class InputIter2, class OutputIter>
	OutputIter
		merge(InputIter1 first1, InputIter1 last1,
			InputIter2 first2, InputIter2 last2,
			OutputIter result)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first2 < *first1)
			{
				*result = *first2;
				++first2;
			}
			else
			{
				*result = *first1;
				++first1;
			}
			++result;
		}
		return mystl::copy(first2, last2, mystl::copy(first1, last1, result));
	}
	/**************************************************
	@brief   : is_heap 检查[first, last)内的元素是否为一个堆，如果是，则返回 true
	@author  : zenghao
	@input   ：RandomIter first, RandomIter last
	@output  ：bool
	**************************************************/
	template <class RandomIter>
	bool is_heap(RandomIter first, RandomIter last)
	{
		auto n = mystl::distance(first, last);
		auto parent = 0;
		for (auto child = 1; child < n; ++child)
		{
			if (first[parent] < first[child])
				return false;
			if ((child & 1) == 0)
				++parent;
		}
		return true;
	}
	/**************************************************
	@brief   : is_sorted 检查[first, last)内的元素是否升序，如果是升序，则返回 true
	@author  : zenghao
	@input   ：ForwardIter first, ForwardIter last
	@output  ：bool
	**************************************************/
	template <class ForwardIter>
	bool is_sorted(ForwardIter first, ForwardIter last)
	{
		if (first == last)
			return true;
		auto next = first;
		++next;
		for (; next != last; first = next, ++next)
		{
			if (*next < *first)
				return false;
		}
		return true;
	}
	/**************************************************
	@brief   : max_element 返回一个迭代器，指向序列中最大的元素
	@author  : zenghao
	@input   ：ForwardIter first, ForwardIter last
	@output  ：ForwardIter
	**************************************************/
	template <class ForwardIter>
	ForwardIter max_element(ForwardIter first, ForwardIter last)
	{
		if (first == last)
			return first;
		auto result = first;
		while (++first != last)
		{
			if (*result < *first)
				result = first;
		}
		return result;
	}
	/**************************************************
	@brief   : median 找出三个值的中间值
	@author  : zenghao
	@input   ：const T& left, const T& mid, const T& right
	@output  ：T&
	**************************************************/
	template <class T>
	const T& median(const T& left, const T& mid, const T& right)
	{
		if (left < mid)
			if (mid < right)        // left < mid < right
				return mid;
			else if (left < right)  // left < right <= mid
				return right;
			else                    // right <= left < mid
				return left;
		else if (left < right)      // mid <= left < right
			return left;
		else if (mid < right)       // mid < right <= left
			return right;
		else                        // right <= mid <= left
			return mid;
	}
	/**************************************************
	@brief   : min_element 返回一个迭代器，指向序列中最小的元素
	@author  : zenghao
	@input   ：ForwardIter first, ForwardIter last 
	@output  ：ForwardIter
	**************************************************/
	template <class ForwardIter>
	ForwardIter min_elememt(ForwardIter first, ForwardIter last)
	{
		if (first == last)
			return first;
		auto result = first;
		while (++first != last)
		{
			if (*first < *result)
				result = first;
		}
		return result;
	}
	/**************************************************
	@brief   : is_permutation 判断[first1,last1)是否为[first2, last2)的排列组合
	@author  : zenghao
	@input   ：ForwardIter1 first1, ForwardIter1 last1,
		ForwardIter2 first2, ForwardIter2 last2
	@output  ：bool
	**************************************************/
	template <class ForwardIter1, class ForwardIter2, class BinaryPred>
	bool is_permutation_aux(ForwardIter1 first1, ForwardIter1 last1,
		ForwardIter2 first2, ForwardIter2 last2,
		BinaryPred pred)
	{
		constexpr bool is_ra_it = mystl::is_random_access_iterator<ForwardIter1>::value
			&& mystl::is_random_access_iterator<ForwardIter2>::value;
		if (is_ra_it)
		{
			auto len1 = last1 - first1;
			auto len2 = last2 - first2;
			if (len1 != len2)
				return false;
		}

		// 先找出相同的前缀段
		for (; first1 != last1 && first2 != last2; ++first1, (void) ++first2)
		{
			if (!pred(*first1, *first2))
				break;
		}
		if (is_ra_it)
		{
			if (first1 == last1)
				return true;
		}
		else
		{
			auto len1 = mystl::distance(first1, last1);
			auto len2 = mystl::distance(first2, last2);
			if (len1 == 0 && len2 == 0)
				return true;
			if (len1 != len2)
				return false;
		}

		// 判断剩余部分
		for (auto i = first1; i != last1; ++i)
		{
			bool is_repeated = false;
			for (auto j = first1; j != i; ++j)
			{
				if (pred(*j, *i))
				{
					is_repeated = true;
					break;
				}
			}

			if (!is_repeated)
			{
				// 计算 *i 在 [first2, last2) 的数目
				auto c2 = 0;
				for (auto j = first2; j != last2; ++j)
				{
					if (pred(*i, *j))
						++c2;
				}
				if (c2 == 0)
					return false;

				// 计算 *i 在 [first1, last1) 的数目
				auto c1 = 1;
				auto j = i;
				for (++j; j != last1; ++j)
				{
					if (pred(*i, *j))
						++c1;
				}
				if (c1 != c2)
					return false;
			}
		}
		return true;
	}
	template <class ForwardIter1, class ForwardIter2, class BinaryPred>
	bool is_permutation(ForwardIter1 first1, ForwardIter1 last1,
		ForwardIter2 first2, ForwardIter2 last2,
		BinaryPred pred)
	{
		return is_permutation_aux(first1, last1, first2, last2, pred);
	}
	template <class ForwardIter1, class ForwardIter2>
	bool is_permutation(ForwardIter1 first1, ForwardIter1 last1,
		ForwardIter2 first2, ForwardIter2 last2)
	{
		typedef typename iterator_traits<ForwardIter1>::value_type v1;
		typedef typename iterator_traits<ForwardIter2>::value_type v2;
		static_assert(std::is_same<v1, v2>::value,
			"the type should be same in mystl::is_permutation");
		return is_permutation_aux(first1, last1, first2, last2,
			mystl::equal_to<v1>());
	}
	/**************************************************
	@brief   : next_permutation 取得[first, last)所标示序列的下一个排列组合，如果没有下一个排序组合，返回 false，否则返回 true
	@author  : zenghao
	@input   ：BidirectionalIter first, BidirectionalIter last
	@output  ：bool
	**************************************************/
	template <class BidirectionalIter>
	bool next_permutation(BidirectionalIter first, BidirectionalIter last)
	{
		auto i = last;
		if (first == last || first == --i)
			return false;
		for (;;)
		{
			auto ii = i;
			if (*--i < *ii)
			{                 // 找到第一对小于关系的元素
				auto j = last;
				while (!(*i < *--j)) {}
				mystl::iter_swap(i, j);       // 交换 i，j 所指元素
				mystl::reverse(ii, last);     // 将 ii 之后的所有元素反转
				return true;
			}
			if (i == first)
			{
				mystl::reverse(first, last);
				return false;
			}
		}
	}
	/**************************************************
	@brief   : reverse 将[first, last)区间内的元素反转
	@author  : zenghao
	@input   ：BidirectionalIter first, BidirectionalIter last
	@output  ：none
	**************************************************/
	// reverse_dispatch 的 bidirectional_iterator_tag 版本
	template <class BidirectionalIter>
	void reverse_dispatch(BidirectionalIter first, BidirectionalIter last,
		bidirectional_iterator_tag)
	{
		while (true)
		{
			if (first == last || first == --last)
				return;
			mystl::iter_swap(first++, last);
		}
	}

	// reverse_dispatch 的 random_access_iterator_tag 版本
	template <class RandomIter>
	void reverse_dispatch(RandomIter first, RandomIter last,
		random_access_iterator_tag)
	{
		while (first < last)
			mystl::iter_swap(first++, --last);
	}

	template <class BidirectionalIter>
	void reverse(BidirectionalIter first, BidirectionalIter last)
	{
		mystl::reverse_dispatch(first, last, iterator_category(first));
	}
	/**************************************************
	@brief   : none_of 检查[first, last)内是否全部元素都不满足一元操作 unary_pred 为 true 的情况，满足则返回 true
	@author  : zenghao
	@input   ：InputIter first, InputIter last, UnaryPredicate unary_pred
	@output  ：bool
	**************************************************/
	template <class InputIter, class UnaryPredicate>
	bool none_of(InputIter first, InputIter last, UnaryPredicate unary_pred)
	{
		for (; first != last; ++first)
		{
			if (unary_pred(*first))
				return false;
		}
		return true;
	}
	/**************************************************
	@brief   : nth_element 对序列重排，使得所有小于第 n 个元素的元素出现在它的前面，大于它的出现在它的后面
	@author  : zenghao
	@input   ：RandomIter first, RandomIter nth,
		RandomIter last
	@output  ：none
	**************************************************/
	template <class RandomIter>
	void nth_element(RandomIter first, RandomIter nth,
		RandomIter last)
	{
		if (nth == last)
			return;
		while (last - first > 3)
		{
			auto cut = mystl::unchecked_partition(first, last, mystl::median(*first,
				*(first + (last - first) / 2),
				*(last - 1)));
			if (cut <= nth)  // 如果 nth 位于右段
				first = cut;   // 对右段进行分割
			else
				last = cut;    // 对左段进行分割
		}
		mystl::insertion_sort(first, last);
	}
	// 插入排序函数 insertion_sort
	template <class RandomIter>
	void insertion_sort(RandomIter first, RandomIter last)
	{
		if (first == last)
			return;
		for (auto i = first + 1; i != last; ++i)
		{
			auto value = *i;
			if (value < *first)
			{
				mystl::copy_backward(first, i, i + 1);
				*first = value;
			}
			else
			{
				mystl::unchecked_linear_insert(i, value);
			}
		}
	}
	// 插入排序辅助函数 unchecked_linear_insert
	template <class RandomIter, class T>
	void unchecked_linear_insert(RandomIter last, const T& value)
	{
		auto next = last;
		--next;
		while (value < *next)
		{
			*last = *next;
			last = next;
			--next;
		}
		*last = value;
	}
	// 分割函数 unchecked_partition
	template <class RandomIter, class T>
	RandomIter
		unchecked_partition(RandomIter first, RandomIter last, const T& pivot)
	{
		while (true)
		{
			while (*first < pivot)
				++first;
			--last;
			while (pivot < *last)
				--last;
			if (!(first < last))
				return first;
			mystl::iter_swap(first, last);
			++first;
		}
	}
	/**************************************************
	@brief   : partial_sort 对整个序列做部分排序，保证较小的 N 个元素以递增顺序置于[first, first + N)中
	@author  : zenghao
	@input   ：RandomIter first, RandomIter middle,
		RandomIter last
	@output  ：none
	**************************************************/
	template <class RandomIter>
	void partial_sort(RandomIter first, RandomIter middle,
		RandomIter last)
	{
		mystl::make_heap(first, middle);
		for (auto i = middle; i < last; ++i)
		{
			if (*i < *first)
			{
				mystl::pop_heap_aux(first, middle, i, *i, distance_type(first));
			}
		}
		mystl::sort_heap(first, middle);
	}
	/**************************************************
	@brief   : partial_sort_copy  行为与 partial_sort 类似，不同的是把排序结果复制到 result 容器中
	@author  : zenghao
	@input   ：InputIter first, InputIter last,
			RandomIter result_first, RandomIter result_last
	@output  ：RandomIter
	**************************************************/
	template <class InputIter, class RandomIter>
	RandomIter
		partial_sort_copy(InputIter first, InputIter last,
			RandomIter result_first, RandomIter result_last)
	{
		return mystl::psort_copy_aux(first, last, result_first, result_last,
			distance_type(result_first));
	}
	template <class InputIter, class RandomIter, class Distance>
	RandomIter
		psort_copy_aux(InputIter first, InputIter last,
			RandomIter result_first, RandomIter result_last,
			Distance*)
	{
		if (result_first == result_last)
			return result_last;
		auto result_iter = result_first;
		while (first != last && result_iter != result_last)
		{
			*result_iter = *first;
			++result_iter;
			++first;
		}
		mystl::make_heap(result_first, result_iter);
		while (first != last)
		{
			if (*first < *result_first)
			{
				mystl::adjust_heap(result_first, static_cast<Distance>(0),
					result_iter - result_first, *first);
			}
			++first;
		}
		mystl::sort_heap(result_first, result_iter);
		return result_iter;
	}
	/**************************************************
	@brief   : partition 对区间内的元素重排，被一元条件运算判定为 true 的元素会放到区间的前段
	@author  : zenghao
	@input   ：BidirectionalIter first, BidirectionalIter last,
			UnaryPredicate unary_pred
	@output  ：none
	**************************************************/
	template <class BidirectionalIter, class UnaryPredicate>
	BidirectionalIter
		partition(BidirectionalIter first, BidirectionalIter last,
			UnaryPredicate unary_pred)
	{
		while (true)
		{
			while (first != last && unary_pred(*first))
			{
				++first;
			}
			if (first == last)
				break;
			--last;
			while (first != last && !unary_pred(*last))
			{
				--last;
			}
			if (first == last)
				break;
			mystl::iter_swap(first, last);
			++first;
		}
		return first;
	}
	/**************************************************
	@brief   : partition_copy 行为与 partition 类似，不同的是，将被一元操作符判定为 true 的放到 result_true 的输出区间
	其余放到 result_false 的输出区间，并返回一个 mystl::pair 指向这两个区间的尾部
	@author  : zenghao
	@input   ：InputIter first, InputIter last,
			OutputIter1 result_true, OutputIter2 result_false,
			UnaryPredicate unary_pred
	@output  ：patr
	**************************************************/
	template <class InputIter, class OutputIter1, class OutputIter2, class UnaryPredicate>
	mystl::pair<OutputIter1, OutputIter2>
		partition_copy(InputIter first, InputIter last,
			OutputIter1 result_true, OutputIter2 result_false,
			UnaryPredicate unary_pred)
	{
		for (; first != last; ++first)
		{
			if (unary_pred(*first))
			{
				*result_true++ = *first;
			}
			else
			{
				*result_false++ = *first;
			}
		}
		return mystl::pair<OutputIter1, OutputIter2>(result_true, result_false);
	}
	/**************************************************
	@brief   : prev_permutation 取得[first, last)所标示序列的上一个排列组合，如果没有上一个排序组合，返回 false，否则返回 true
	@author  : zenghao
	@input   ：BidirectionalIter first, BidirectionalIter last
	@output  ：bool
	**************************************************/
	template <class BidirectionalIter>
	bool prev_permutation(BidirectionalIter first, BidirectionalIter last)
	{
		auto i = last;
		if (first == last || first == --i)
			return false;
		for (;;)
		{
			auto ii = i;
			if (*ii < *--i)
			{                 // 找到第一对大于关系的元素
				auto j = last;
				while (!(*--j < *i)) {}
				mystl::iter_swap(i, j);       // 交换i，j
				mystl::reverse(ii, last);     // 将 ii 之后的所有元素反转
				return true;
			}
			if (i == first)
			{
				mystl::reverse(first, last);
				return false;
			}
		}
	}
	/**************************************************
	@brief   : random_shuffle 将[first, last)内的元素次序随机重排
	@author  : zenghao
	@input   ：RandomIter first, RandomIter last
	@output  ：none
	**************************************************/
	template <class RandomIter>
	void random_shuffle(RandomIter first, RandomIter last)
	{
		if (first == last)
			return;
		srand((unsigned)time(0));
		for (auto i = first + 1; i != last; ++i)
		{
			mystl::iter_swap(i, first + (rand() % (i - first + 1)));
		}
	}
	// 重载版本使用一个产生随机数的函数对象 rand
	template <class RandomIter, class RandomNumberGenerator>
	void random_shuffle(RandomIter first, RandomIter last,
		RandomNumberGenerator& rand)
	{
		if (first == last)
			return;
		auto len = mystl::distance(first, last);
		for (auto i = first + 1; i != last; ++i)
		{
			mystl::iter_swap(i, first + (rand(i - first + 1) % len));
		}
	}
	/**************************************************
	@brief   : remove 移除所有与指定 value 相等的元素
	@author  : zenghao
	@input   ：ForwardIter first, ForwardIter last, const T& value
	@output  ：ForwardIter
	**************************************************/
	// 移除区间内与指定 value 相等的元素，并将结果复制到以 result 标示起始位置的容器上
	template <class InputIter, class OutputIter, class T>
	OutputIter
		remove_copy(InputIter first, InputIter last, OutputIter result, const T& value)
	{
		for (; first != last; ++first)
		{
			if (*first != value)
			{
				*result++ = *first;
			}
		}
		return result;
	}
	template <class ForwardIter, class T>
	ForwardIter remove(ForwardIter first, ForwardIter last, const T& value)
	{
		first = mystl::find(first, last, value);  // 利用 find 找出第一个匹配的地方
		auto next = first;
		return first == last ? first : mystl::remove_copy(++next, last, first, value);
	}
	/**************************************************
	@brief   : remove_copy_if 移除区间内所有令一元操作 unary_pred 为 true 的元素，并将结果复制到以 result 为起始位置的容器上
	@author  : zenghao
	@input   ：InputIter first, InputIter last,
			OutputIter result, UnaryPredicate unary_pred
	@output  ：OutputIter
	**************************************************/
	template <class InputIter, class OutputIter, class UnaryPredicate>
	OutputIter
		remove_copy_if(InputIter first, InputIter last,
			OutputIter result, UnaryPredicate unary_pred)
	{
		for (; first != last; ++first)
		{
			if (!unary_pred(*first))
			{
				*result = *first;
				++result;
			}
		}
		return result;
	}
	/**************************************************
	@brief   : remove_if 移除区间内所有令一元操作 unary_pred 为 true 的元素
	@author  : zenghao 
	@input   ：ForwardIter first, ForwardIter last, UnaryPredicate unary_pred
	@output  ：ForwardIter
	**************************************************/
	template <class ForwardIter, class UnaryPredicate>
	ForwardIter
		remove_if(ForwardIter first, ForwardIter last, UnaryPredicate unary_pred)
	{
		first = mystl::find_if(first, last, unary_pred);  // 利用 find_if 找出第一个匹配的地方
		auto next = first;
		return first == last ? first : mystl::remove_copy_if(++next, last, first, unary_pred);
	}
	/**************************************************
	@brief   : replace 将区间内所有的 old_value 都以 new_value 替代
	@author  : zenghao
	@input   ：ForwardIter first, ForwardIter last,
		const T& old_value, const T& new_value
	@output  ：none
	**************************************************/
	template <class ForwardIter, class T>
	void replace(ForwardIter first, ForwardIter last,
		const T& old_value, const T& new_value)
	{
		for (; first != last; ++first)
		{
			if (*first == old_value)
				*first = new_value;
		}
	}
	/**************************************************
	@brief   : replace_copy 行为与 replace 类似，不同的是将结果复制到 result 所指的容器中，原序列没有改变
	@author  : zenghao
	@input   ：InputIter first, InputIter last,
			OutputIter result, const T& old_value, const T& new_value
	@output  ：none
	**************************************************/
	template <class InputIter, class OutputIter, class T>
	OutputIter
		replace_copy(InputIter first, InputIter last,
			OutputIter result, const T& old_value, const T& new_value)
	{
		for (; first != last; ++first, ++result)
		{
			*result = *first == old_value ? new_value : *first;
		}
		return result;
	}
	/**************************************************
	@brief   : replace_copy_if 行为与 replace_if 类似，不同的是将结果复制到 result 所指的容器中，原序列没有改变
	@author  : zenghao
	@input   ：InputIter first, InputIter last,
			OutputIter result, UnaryPredicate unary_pred, const T& new_valu
	@output  ：OutputIter
	**************************************************/	
	template <class InputIter, class OutputIter, class UnaryPredicate, class T>
	OutputIter
		replace_copy_if(InputIter first, InputIter last,
			OutputIter result, UnaryPredicate unary_pred, const T& new_value)
	{
		for (; first != last; ++first, ++result)
		{
			*result = unary_pred(*first) ? new_value : *first;
		}
		return result;
	}
	/**************************************************
	@brief   : replace_if 将区间内所有令一元操作 unary_pred 为 true 的元素都用 new_value 替代
	@author  : zenghao
	@input   ：ForwardIter first, ForwardIter last,
		UnaryPredicate unary_pred, const T& new_value
	@output  ：none
	**************************************************/
	template <class ForwardIter, class UnaryPredicate, class T>
	void replace_if(ForwardIter first, ForwardIter last,
		UnaryPredicate unary_pred, const T& new_value)
	{
		for (; first != last; ++first)
		{
			if (unary_pred(*first))
				*first = new_value;
		}
	}
	/**************************************************
	@brief   : reverse_copy 行为与 reverse 类似，不同的是将结果复制到 result 所指容器中
	@author  : zenghao
	@input   ：BidirectionalIter first, BidirectionalIter last,
			OutputIter result
	@output  ：OutputIter
	**************************************************/
	template <class BidirectionalIter, class OutputIter>
	OutputIter
		reverse_copy(BidirectionalIter first, BidirectionalIter last,
			OutputIter result)
	{
		while (first != last)
		{
			--last;
			*result = *last;
			++result;
		}
		return result;
	}
	/**************************************************
	@brief   : rotate_copy 行为与 rotate 类似，不同的是将结果复制到 result 所指的容器中
	@author  : zenghao
	@input   ：orwardIter first, ForwardIter middle,
			ForwardIter last, OutputIter result
	@output  ：ForwardIter
	**************************************************/	
	template <class ForwardIter, class OutputIter>
	ForwardIter
		rotate_copy(ForwardIter first, ForwardIter middle,
			ForwardIter last, OutputIter result)
	{
		return mystl::copy(first, middle, mystl::copy(middle, last, result));
	}
	/**************************************************
	@brief   : search_n  在[first, last)中查找连续 n 个 value 所形成的子序列，返回一个迭代器指向该子序列的起始处
	@author  : zenghao
	@input   ：ForwardIter first, ForwardIter last, Size n, const T& value
	@output  ：ForwardIter
	**************************************************/
	template <class ForwardIter, class Size, class T>
	ForwardIter
		search_n(ForwardIter first, ForwardIter last, Size n, const T& value)
	{
		if (n <= 0)
		{
			return first;
		}
		else
		{
			first = mystl::find(first, last, value);
			while (first != last)
			{
				auto m = n - 1;
				auto i = first;
				++i;
				while (i != last && m != 0 && *i == value)
				{
					++i;
					--m;
				}
				if (m == 0)
				{
					return first;
				}
				else
				{
					first = mystl::find(i, last, value);
				}
			}
			return last;
		}
	}
	/**************************************************
	@brief   : sort 将[first, last)内的元素以递增的方式排序
	@author  : zenghao
	@input   ：RandomIter first, RandomIter last
	@output  ：none
	**************************************************/
	constexpr static size_t kSmallSectionSize = 128;
	template <class Size>
	Size slg2(Size n)
	{ // 找出 lgk <= n 的 k 的最大值
		Size k = 0;
		for (; n > 1; n >>= 1)
			++k;
		return k;
	}
	template <class RandomIter>
	void sort(RandomIter first, RandomIter last)
	{
		if (first != last)
		{
			// 内省式排序，将区间分为一个个小区间，然后对整体进行插入排序
			mystl::intro_sort(first, last, slg2(last - first) * 2);
			mystl::final_insertion_sort(first, last);
		}
	}
	template <class RandomIter, class Compared>
	void sort(RandomIter first, RandomIter last, Compared comp)
	{
		if (first != last)
		{
			// 内省式排序，将区间分为一个个小区间，然后对整体进行插入排序
			mystl::intro_sort(first, last, slg2(last - first) * 2, comp);
			mystl::final_insertion_sort(first, last, comp);
		}
	}
	// 内省式排序，先进行 quick sort，当分割行为有恶化倾向时，改用 heap sort
	template <class RandomIter, class Size>
	void intro_sort(RandomIter first, RandomIter last, Size depth_limit)
	{
		while (static_cast<size_t>(last - first) > kSmallSectionSize)
		{
			if (depth_limit == 0)
			{                      // 到达最大分割深度限制
				mystl::partial_sort(first, last, last);  // 改用 heap_sort
				return;
			}
			--depth_limit;
			auto mid = mystl::median(*(first), *(first + (last - first) / 2), *(last - 1));
			auto cut = mystl::unchecked_partition(first, last, mid);
			mystl::intro_sort(cut, last, depth_limit);
			last = cut;
		}
	}
	// 内省式排序，先进行 quick sort，当分割行为有恶化倾向时，改用 heap sort
	template <class RandomIter, class Size, class Compared>
	void intro_sort(RandomIter first, RandomIter last,
		Size depth_limit, Compared comp)
	{
		while (static_cast<size_t>(last - first) > kSmallSectionSize)
		{
			if (depth_limit == 0)
			{                            // 到达最大分割深度限制
				mystl::partial_sort(first, last, last, comp);  // 改用 heap_sort
				return;
			}
			--depth_limit;
			auto mid = mystl::median(*(first), *(first + (last - first) / 2), *(last - 1));
			auto cut = mystl::unchecked_partition(first, last, mid, comp);
			mystl::intro_sort(cut, last, depth_limit, comp);
			last = cut;
		}
	}
	// 最终插入排序函数 final_insertion_sort
	template <class RandomIter>
	void final_insertion_sort(RandomIter first, RandomIter last)
	{
		if (static_cast<size_t>(last - first) > kSmallSectionSize)
		{
			mystl::insertion_sort(first, first + kSmallSectionSize);
			mystl::unchecked_insertion_sort(first + kSmallSectionSize, last);
		}
		else
		{
			mystl::insertion_sort(first, last);
		}
	}
	// 最终插入排序函数 final_insertion_sort
	template <class RandomIter, class Compared>
	void final_insertion_sort(RandomIter first, RandomIter last, Compared comp)
	{
		if (static_cast<size_t>(last - first) > kSmallSectionSize)
		{
			mystl::insertion_sort(first, first + kSmallSectionSize, comp);
			mystl::unchecked_insertion_sort(first + kSmallSectionSize, last, comp);
		}
		else
		{
			mystl::insertion_sort(first, last, comp);
		}
	}
	// 插入排序函数 unchecked_insertion_sort
	template <class RandomIter>
	void unchecked_insertion_sort(RandomIter first, RandomIter last)
	{
		for (auto i = first; i != last; ++i)
		{
			mystl::unchecked_linear_insert(i, *i);
		}
	}
	// 插入排序函数 unchecked_insertion_sort
	template <class RandomIter, class Compared>
	void unchecked_insertion_sort(RandomIter first, RandomIter last,
		Compared comp)
	{
		for (auto i = first; i != last; ++i)
		{
			mystl::unchecked_linear_insert(i, *i, comp);
		}
	}
	/**************************************************
	@brief   : swap_ranges
	将[first1, last1)从 first2 开始，交换相同个数元素
	交换的区间长度必须相同，两个序列不能互相重叠，返回一个迭代器指向序列二最后一个被交换元素的下一位置
	@author  : zenghao
	@input   ：ForwardIter1 first1, ForwardIter1 last1,
			ForwardIter2 first2
	@output  ：ForwardIter2
	**************************************************/	
	template <class ForwardIter1, class ForwardIter2>
	ForwardIter2
		swap_ranges(ForwardIter1 first1, ForwardIter1 last1,
			ForwardIter2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			mystl::iter_swap(first1, first2);
		}
		return first2;
	}
	/**************************************************
	@brief   : transform 
	第一个版本以函数对象 unary_op 作用于[first, last)中的每个元素并将结果保存至 result 中
	第二个版本以函数对象 binary_op 作用于两个序列[first1, last1)、[first2, last2)的相同位置
	@author  : zenghao
	@input   ：
	@output  ：OutputIter
	**************************************************/
	template <class InputIter, class OutputIter, class UnaryOperation>
	OutputIter
		transform(InputIter first, InputIter last,
			OutputIter result, UnaryOperation unary_op)
	{
		for (; first != last; ++first, ++result)
		{
			*result = unary_op(*first);
		}
		return result;
	}

	template <class InputIter1, class InputIter2, class OutputIter, class BinaryOperation>
	OutputIter
		transform(InputIter1 first1, InputIter1 last1,
			InputIter2 first2, OutputIter result, BinaryOperation binary_op)
	{
		for (; first1 != last1; ++first1, ++first2, ++result)
		{
			*result = binary_op(*first1, *first2);
		}
		return result;
	}
	/**************************************************
	@brief   : unique 移除[first, last)内重复的元素，序列必须有序，和 remove 类似，它也不能真正的删除重复元素
	@author  : zenghao
	@input   ：ForwardIter first, ForwardIter last
	@output  ：ForwardIter
	**************************************************/
	template <class ForwardIter>
	ForwardIter unique(ForwardIter first, ForwardIter last)
	{
		first = mystl::adjacent_find(first, last);
		return mystl::unique_copy(first, last, first);
	}

	// 重载版本使用函数对象 comp 代替比较操作
	template <class ForwardIter, class Compared>
	ForwardIter unique(ForwardIter first, ForwardIter last, Compared comp)
	{
		first = mystl::adjacent_find(first, last, comp);
		return mystl::unique_copy(first, last, first, comp);
	}
	/**************************************************
	@brief   : unique_copy 从[first, last)中将元素复制到 result 上，序列必须有序，如果有重复的元素，只会复制一次
	@author  : zenghao
	@input   ：InputIter first, InputIter last, OutputIter result
	@output  ：OutputIter
	**************************************************/	
	template <class InputIter, class OutputIter>
	OutputIter
		unique_copy(InputIter first, InputIter last, OutputIter result)
	{
		if (first == last)
			return result;
		return mystl::unique_copy_dispatch(first, last, result, iterator_category(result));
	}
	// unique_copy_dispatch 的 forward_iterator_tag 版本
	template <class InputIter, class ForwardIter>
	ForwardIter
		unique_copy_dispatch(InputIter first, InputIter last,
			ForwardIter result, forward_iterator_tag)
	{
		*result = *first;
		while (++first != last)
		{
			if (*result != *first)
				*++result = *first;
		}
		return ++result;
	}
	// 重载版本使用函数对象 comp 代替比较操作
// unique_copy_dispatch 的 forward_iterator_tag 版本
	template <class InputIter, class ForwardIter, class Compared>
	ForwardIter
		unique_copy_dispatch(InputIter first, InputIter last,
			ForwardIter result, forward_iterator_tag, Compared comp)
	{
		*result = *first;
		while (++first != last)
		{
			if (!comp(*result, *first))
				*++result = *first;
		}
		return ++result;
	}
	template <class InputIter, class OutputIter, class Compared>
	OutputIter
		unique_copy(InputIter first, InputIter last, OutputIter result, Compared comp)
	{
		if (first == last)
			return result;
		return mystl::unique_copy_dispatch(first, last, result, iterator_category(result), comp);
	}
	/**************************************************
	@brief   : none
	@author  : zenghao
	@input   ：none
	@output  ：none
	**************************************************/
	/**************************************************
	@brief   : none
	@author  : zenghao
	@input   ：none
	@output  ：none
	**************************************************/
	/**************************************************
	@brief   : none
	@author  : zenghao
	@input   ：none
	@output  ：none
	**************************************************/	
	/**************************************************
	@brief   : none
	@author  : zenghao
	@input   ：none
	@output  ：none
	**************************************************/
	/**************************************************
	@brief   : none
	@author  : zenghao
	@input   ：none
	@output  ：none
	**************************************************/
	/**************************************************
	@brief   : none
	@author  : zenghao
	@input   ：none
	@output  ：none
	**************************************************/	
	/**************************************************
	@brief   : none
	@author  : zenghao
	@input   ：none
	@output  ：none
	**************************************************/
	/**************************************************
	@brief   : none
	@author  : zenghao
	@input   ：none
	@output  ：none
	**************************************************/
	/**************************************************
	@brief   : none
	@author  : zenghao
	@input   ：none
	@output  ：none
	**************************************************/	
	/**************************************************
	@brief   : none
	@author  : zenghao
	@input   ：none
	@output  ：none
	**************************************************/
	/**************************************************
	@brief   : none
	@author  : zenghao
	@input   ：none
	@output  ：none
	**************************************************/
	/**************************************************
	@brief   : none
	@author  : zenghao
	@input   ：none
	@output  ：none
	**************************************************/
}