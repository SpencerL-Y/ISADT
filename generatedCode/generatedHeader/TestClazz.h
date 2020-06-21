#ifndef TestClazz_h
#define TestClazz_h
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <thread>
#include <uinstd.h>
#include <stdlib.h>

#include "UserType.h" 
class TestClazz {
	private: 
	
int testAttr2_;
	
int testAttr1_;
	public: 
	
int getTestAttr2_();
int setTestAttr2_(int testAttr2_);
	
int getTestAttr1_();
int setTestAttr1_(int testAttr1_);
};
#endif

