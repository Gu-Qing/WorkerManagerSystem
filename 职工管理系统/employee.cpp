#include "employee.h"

Employee::Employee(int id, string name, int deptId) {
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = deptId;
}

//��ʾ������Ϣ
void Employee::ShowInfo() {
	cout << "ְ����ţ�" << this->m_Id
		<< "\tְ��������" << this->m_Name
		<< "\tְ����λ��" << this->GetDeptName()
		<< "\t��λְ������ϼ����õ�����" << endl;
}

//��ȡ��λ����
string Employee::GetDeptName() {
	return string("��ͨԱ��");
}