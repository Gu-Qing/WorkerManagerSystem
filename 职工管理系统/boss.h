#pragma once
#include <iostream>
#include "worker.h"
using namespace std;

class Boss : public Worker {
public:
	Boss(int id, string name, int deptId);
	//��ʾ������Ϣ
	virtual void ShowInfo();
	//��ȡ��λ����
	virtual string GetDeptName();
};