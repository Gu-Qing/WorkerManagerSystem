#pragma once
#include <iostream>
#include "worker.h"
using namespace std;

class Manager : public Worker {
public :
	Manager(int id, string name, int deptId);
	//��ʾ������Ϣ
	virtual void ShowInfo();
	//��ȡ��λ����
	virtual string GetDeptName();
};