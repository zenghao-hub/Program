#ifndef MYTINYSTL_ALGORITHM_TEST_H_
#define MYTINYSTL_ALGORITHM_TEST_H_
#include <iostream>
#include <vector>

class TestCase
{
public:
	// ���캯��������һ���ַ�������������
	TestCase(const char* case_name) : testcase_name(case_name) {}

	// һ�����麯�������ڲ��԰���
	virtual void Run() = 0;

public:
	const char* testcase_name;  // ���԰���������
	int         nTestResult;    // ���԰�����ִ�н�� 
	double      nFailed;        // ����ʧ�ܵİ�����
	double      nPassed;        // ����ͨ���İ�����
};

class UnitTest
{
public:
	// ��ȡһ������
	static UnitTest* GetInstance();

	// ���������μ��� vector
	TestCase* RegisterTestCase(TestCase* testcase);

	void Run();

public:
	TestCase* CurrentTestCase;          // ��ǰִ�еĲ��԰���
	double    nPassed;                  // ͨ��������
	double    nFailed;                  // ʧ�ܰ�����

protected:
	std::vector<TestCase*> testcases_;  // ���永������
};

UnitTest* UnitTest::GetInstance()
{
	static UnitTest instance;
	return &instance;
}

TestCase* UnitTest::RegisterTestCase(TestCase* testcase)
{
	testcases_.push_back(testcase);// ����ʵ������(vector) testcases_Ϊ��������
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

// �򵥲��Եĺ궨��
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