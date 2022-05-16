#pragma once
#include <iostream>
#include "worker.h"
using namespace std;

class Boss : public Worker {
public:
	Boss(int id, string name, int deptId);
	//显示个人信息
	virtual void ShowInfo();
	//获取岗位名称
	virtual string GetDeptName();
};