#include <iostream>
#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
using namespace std;

//测试代码
void Test() {
	Worker* worker = NULL;
	worker = new Employee(1, "张三", 111);
	worker->ShowInfo();
	delete worker;

	worker = new Manager(2, "李四", 222);
	worker->ShowInfo();
	delete worker;

	worker = new Boss(3, "王五", 333);
	worker->ShowInfo();
	delete worker;
}

int main() {

	//Test
	//Test();

	//实例化一个管理者对象
	WorkerManager workerManager;

	int choice = 0;
	while (true) {
		workerManager.ShowMenu();
		cout << "请输入您的选择：" << endl;
		cin >> choice;
		switch (choice) {
		case 0: //退出系统
			workerManager.ExitSystem();
			break;
		case 1: //增加职工
			workerManager.AddEmp();
			break;
		case 2: //显示职工
			workerManager.ShowEmp();
			break;
		case 3: //删除职工
			workerManager.DeleteEmp();
			break;
		case 4: //修改职工
			workerManager.ModifyEmp();
			break;
		case 5: //查找职工
			workerManager.FindEmp();
			break;
		case 6: //职工排序
			workerManager.SortEmp();
			break;
		case 7: //清空文档
			workerManager.ClearFile();
			break;
		default:
			cout << "无此选项，输入错误，请重新输入！" << endl;
		}
		system("pause");
		system("cls");
	}

	system("pause");

	return 0;
}