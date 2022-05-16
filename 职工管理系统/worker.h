#pragma once
#include <iostream>
#include <string>
using namespace std;

class Worker {


public :
	int m_Id;
	string m_Name;
	int m_DeptId; //1.普通职工; 2.经理; 3.老板

	//显示个人信息
	virtual void ShowInfo() = 0;
	//获取岗位名称
	virtual string GetDeptName() = 0;
};