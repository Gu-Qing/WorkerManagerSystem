#pragma once //防止头文件重复包含
#include <iostream>
#include <fstream>
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
using namespace std;

#define FILENAME "empFile.txt"

class WorkerManager {
private :
	//记录职工人数
	int m_EmpNum;
	//职工数组指针
	Worker** m_EmpArray;
	//判断文件是否为空
	bool m_FileIsEmpty;

public :
	WorkerManager();
	int getEmpNum();
	void setEmpNum(int empNum);
	Worker** getEmpArray();
	void setEmpArray(Worker** empArray);
	bool getFileIsEmpty();
	void setFileIsEmpty(bool isEmpty);

	//展示菜单
	void ShowMenu();
	//退出
	void ExitSystem();
	//添加职工
	void AddEmp();
	//保存到文件
	void SaveToFile();
	//统计文件中的人数
	int GetFileEmpNum();
	//初始化员工
	void InitEmp();
	//显示所有员工
	void ShowEmp();
	//查询员工是否存在
	int IsExist(int id);
	//删除职工
	void DeleteEmp();
	//修改职工信息
	void ModifyEmp();
	//查找职工
	void FindEmp();
	//按照编号排序
	void SortEmp();
	//清空文件
	void ClearFile();

	~WorkerManager();
};