#include "employee.h"

Employee::Employee(int id, string name, int deptId) {
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = deptId;
}

//显示个人信息
void Employee::ShowInfo() {
	cout << "职工编号：" << this->m_Id
		<< "\t职工姓名：" << this->m_Name
		<< "\t职工岗位：" << this->GetDeptName()
		<< "\t岗位职责：完成上级布置的任务" << endl;
}

//获取岗位名称
string Employee::GetDeptName() {
	return string("普通员工");
}