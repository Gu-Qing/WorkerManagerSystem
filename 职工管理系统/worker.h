#pragma once
#include <iostream>
#include <string>
using namespace std;

class Worker {


public :
	int m_Id;
	string m_Name;
	int m_DeptId; //1.��ְͨ��; 2.����; 3.�ϰ�

	//��ʾ������Ϣ
	virtual void ShowInfo() = 0;
	//��ȡ��λ����
	virtual string GetDeptName() = 0;
};