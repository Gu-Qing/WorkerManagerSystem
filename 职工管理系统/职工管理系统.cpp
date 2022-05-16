#include <iostream>
#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
using namespace std;

//���Դ���
void Test() {
	Worker* worker = NULL;
	worker = new Employee(1, "����", 111);
	worker->ShowInfo();
	delete worker;

	worker = new Manager(2, "����", 222);
	worker->ShowInfo();
	delete worker;

	worker = new Boss(3, "����", 333);
	worker->ShowInfo();
	delete worker;
}

int main() {

	//Test
	//Test();

	//ʵ����һ�������߶���
	WorkerManager workerManager;

	int choice = 0;
	while (true) {
		workerManager.ShowMenu();
		cout << "����������ѡ��" << endl;
		cin >> choice;
		switch (choice) {
		case 0: //�˳�ϵͳ
			workerManager.ExitSystem();
			break;
		case 1: //����ְ��
			workerManager.AddEmp();
			break;
		case 2: //��ʾְ��
			workerManager.ShowEmp();
			break;
		case 3: //ɾ��ְ��
			workerManager.DeleteEmp();
			break;
		case 4: //�޸�ְ��
			workerManager.ModifyEmp();
			break;
		case 5: //����ְ��
			workerManager.FindEmp();
			break;
		case 6: //ְ������
			workerManager.SortEmp();
			break;
		case 7: //����ĵ�
			workerManager.ClearFile();
			break;
		default:
			cout << "�޴�ѡ�����������������룡" << endl;
		}
		system("pause");
		system("cls");
	}

	system("pause");

	return 0;
}