1. main��������cpp������color.h
2. color.h������platform.h

test.cpp��������
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
	std::cout << green << "������ɫ��\n";
}