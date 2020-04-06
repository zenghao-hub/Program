#ifndef MYTINYSTL_ALGORITHM_TEST_H_
#define MYTINYSTL_ALGORITHM_TEST_H_
#include <iostream>
#include <vector>

class TestCase
{
public:
	// 构造函数，接受一个字符串代表案例名称
	TestCase(const char* case_name) : testcase_name(case_name) {}

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

UnitTest* UnitTest::GetInstance()
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

#define TESTCASE_NAME(testcase_name) \
    testcase_name##_TEST

// 简单测试的宏定义
// #define TEST(testcase_name) MYTINYSTL_TEST_(testcase_name)

#define TEST(testcase_name)                        \
class TESTCASE_NAME(testcase_name) : public TestCase {        \
public:                                                       \
    TESTCASE_NAME(testcase_name)(const char* case_name)       \
        : TestCase(case_name) {};                             \
    virtual void Run();                                       \
private:                                                      \
    static TestCase* const testcase_;                         \
};                                                            \
                                                              \
TestCase* const TESTCASE_NAME(testcase_name)                  \
    ::testcase_ = UnitTest::GetInstance()->RegisterTestCase(  \
        new TESTCASE_NAME(testcase_name)(#testcase_name));    \
void TESTCASE_NAME(testcase_name)::Run()


#endif // !MYTINYSTL_ALGORITHM_TEST_H_