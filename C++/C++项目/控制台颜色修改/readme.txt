1. main函数所在cpp中引用color.h
2. color.h中引用platform.h

test.cpp内容如下
#include <stdio.h>
#include<iostream>
#include"color.h"
#define green redbud::io::state::manual << redbud::io::hfg::green
template<typename Ta> 
Ta sum(Ta& t1,Ta& t2)
{
	return t1 + t2;
}

int main() {
	std::cout << green << "这是绿色吗？\n";
}