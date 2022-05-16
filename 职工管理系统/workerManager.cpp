#include "workerManager.h"

WorkerManager::WorkerManager() {

	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open()) {
		//cout << "文件不存在" << endl;
		//初始化属性
		this->m_EmpNum = 0; //初始化记录人数
		this->m_EmpArray = NULL; //初始化数组指针
		this->m_FileIsEmpty = true; //初始化文件是否为空
	}
	else {
		char ch;
		ifs >> ch;
		//文件存在，数据为空
		if (ifs.eof()) {
			//cout << "文件为空" << endl;
			//初始化属性
			this->m_EmpNum = 0; //初始化记录人数
			this->m_EmpArray = NULL; //初始化数组指针
			this->m_FileIsEmpty = true; //初始化文件是否为空
		}
		//文件存在且数据不为空
		else {
			int num = this->GetFileEmpNum();
			//cout << "职工人数为：" << num << endl;
			this->m_EmpNum = num;
			//开辟空间
			this->m_EmpArray = new Worker * [this->m_EmpNum];
			//将文件的数据存到数组中
			this->InitEmp();

			/*for (int i = 0; i < this->m_EmpNum; i++) {
				cout << "职工编号：" << this->m_EmpArray[i]->m_Id
					<< " 姓名：" << this->m_EmpArray[i]->m_Name
					<< " 部门编号：" << this->m_EmpArray[i]->m_DeptId << endl;
			}*/
		}
		ifs.close();
	}
}

//私有成员变量的get、set方法
int WorkerManager::getEmpNum() {
	return m_EmpNum;
}
void WorkerManager::setEmpNum(int empNum) {
	this->m_EmpNum = empNum;
}
Worker** WorkerManager::getEmpArray() {
	return m_EmpArray;
}
void WorkerManager::setEmpArray(Worker** empArray) {
	this->m_EmpArray = empArray;
}
bool WorkerManager::getFileIsEmpty(){
	return m_FileIsEmpty;
}
void WorkerManager::setFileIsEmpty(bool isEmpty) {
	this->m_FileIsEmpty = isEmpty;
}

//显示菜单
void WorkerManager::ShowMenu() {
	cout << "************************************************" << endl;
	cout << "*************欢迎使用职工管理系统！*************" << endl;
	cout << "***************  0.退出管理程序  ***************" << endl;
	cout << "***************  1.增加职工信息  ***************" << endl;
	cout << "***************  2.显示职工信息  ***************" << endl;
	cout << "***************  3.删除离职职工  ***************" << endl;
	cout << "***************  4.修改职工信息  ***************" << endl;
	cout << "***************  5.查找职工信息  ***************" << endl;
	cout << "***************  6.按照编号排序  ***************" << endl;
	cout << "***************  7.清空所有文档  ***************" << endl;
	cout << "************************************************" << endl;
	cout << endl;
}
//退出程序
void WorkerManager::ExitSystem() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0); //退出程序
}
//添加职工
void WorkerManager::AddEmp() {
	cout << "请输入添加职工的数量：" << endl;
	int addNum = 0;
	cin >> addNum;

	if (addNum) {
		//计算新添加的空间的大小。原来的职工数量+新添加的职工数量
		int newSize = this->m_EmpNum + addNum;
		//开辟新空间
		Worker** newSpace = new Worker* [newSize];

		//如果原来的空间有数据，则将原来空间的数据拷贝到新空间
		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		//批量添加新数据
		for (int i = 0; i < addNum; i++) {
			int id; //部门编号
			string name; //职工姓名
			int depSelect; //部门选择

			cout << "请输入第 " << i + 1 << " 个新职工编号: " << endl;
			cin >> id;
			cout << "请输入第 " << i + 1 << " 个新职工姓名: " << endl;
			cin >> name;
			cout << "请选择该职工的岗位：" << endl;
			cout << "** 1.普通职工" << endl;
			cout << "** 2.经理" << endl;
			cout << "** 3.老板" << endl;
			cin >> depSelect;

			Worker* worker = NULL;
			switch (depSelect) {
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				cout << "岗位选择有误，添加失败" << endl;
				break;
			}
			//将创建的职工职责，保存到数组
			//原来的空间数量加上新添加的第i个职工才是当前空间的最后一个下标
			newSpace[this->m_EmpNum + i] = worker;
		}
		//释放原来的空间
		delete[] this->m_EmpArray;

		//更改新空间的指向
		this->m_EmpArray = newSpace;

		//更新新的职工人数
		this->m_EmpNum = newSize;

		//更新文件不为空
		this->m_FileIsEmpty = false;

		//将数据添加到文件
		this->SaveToFile();

		//提示添加成功
		cout << "成功添加" << addNum << "名新职工" << endl;
	}
	else {
		cout << "输入数据有误！" << endl;
	}
	//system("pause");
	//system("cls");
}
//保存到文件
void WorkerManager::SaveToFile() {
	ofstream ofs;
	//用输出的方式打开文件——写文件
	ofs.open(FILENAME, ios::out);
	//将每个人的数据写入到数据中
	for (int i = 0; i < this->m_EmpNum; i++) {
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	//关闭文件
	ofs.close();
}
//统计文件中的人数
int WorkerManager::GetFileEmpNum() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int deptId;
	int num = 0; //统计人数的变量
	while (ifs >> id && ifs >> name && ifs >> deptId) {
		++num;
	}
	ifs.close();

	return num;
}
//初始化员工
void WorkerManager::InitEmp() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dempId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dempId) {

		Worker* worker = NULL;
		cout << dempId << endl;
		switch (dempId) {
		case 1 :
			worker = new Employee(id, name, dempId);
			break;
		case 2:
			worker = new Manager(id, name, dempId);
			break;
		case 3:
			worker = new Boss(id, name, dempId);
			break;
		default:
			cout << "读取文件员工编号错误" << endl;
			return;
		}

		this->m_EmpArray[index++] = worker;
	}

	ifs.close();
}
//显示所有员工
void WorkerManager::ShowEmp() {
	//判断文件是否为空
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空！" << endl;
	}
	else {
		for (int i = 0; i < m_EmpNum; i++) {
			//利用多态调用程序接口
			this->m_EmpArray[i]->ShowInfo();
		}
	}
	//system("pause");
	//system("cls");
}
//查询员工是否存在
int WorkerManager::IsExist(int id) {
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++) {
		if (this->m_EmpArray[i]->m_Id == id) {
			index = i;
			break;
		}
	}
	return index;
}
//删除职工
void WorkerManager::DeleteEmp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空！" << endl;
	}
	else {
		this->ShowEmp();
		cout << "请输入想要删除职工的编号：" << endl;
		int id = 0;
		cin >> id;

		int index = this->IsExist(id);
		if (index != -1) { //存在
			//数据前移
			for (int i = index; i < this->m_EmpNum - 1; i++) {
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			--this->m_EmpNum;
			//数据同步更新到文件
			this->SaveToFile();
			cout << "删除成功！" << endl;
		}
		else {
			cout << "删除失败，未找到该职工！" << endl;
		}
	}
	//system("pause");
	//system("cls");
}
//修改职工信息
void WorkerManager::ModifyEmp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空" << endl;
	}
	else {
		this->ShowEmp();

		cout << "请输入要修改的职工编号：" << endl;
		int id;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret != -1) {
			delete this->m_EmpArray[ret];
			int newId = 0;
			string newName = "";
			int deptSelect = 0;
			cout << "查到：" << id << "号职工，请输入新的职工号：" << endl;
			cin >> newId;
			cout << "请输入新的姓名：" << endl;
			cin >> newName;
			cout << "请输入岗位：" << endl;
			cout << "** 1.普通职工" << endl;
			cout << "** 2.经理" << endl;
			cout << "** 3.老板" << endl;
			cin >> deptSelect;

			Worker* worker = NULL;
			switch (deptSelect) {
			case 1:
				worker = new Employee(newId, newName, deptSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, deptSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, deptSelect);
				break;
			default:
				cout << "部门编号填写错误！修改失败！" << endl;
				//然后做相关处理，添加成功和失败的标记等
				break;
			}
			this->m_EmpArray[ret] = worker;
			this->SaveToFile();

			cout << "修改成功！" << endl;
		}
		else {
			cout << "修改失败，查无此人！" << endl;
		}
	}
}
//查找职工
void WorkerManager::FindEmp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空" << endl;
	}
	else {
		cout << "请输入查找的方式：" << endl;
		cout << "** 1.按照职工编号查找" << endl;
		cout << "** 2.按照职工姓名查找" << endl;
		int select = 0;
		cin >> select;
		if (select == 1) {
			int id;
			cout << "请输入查找的职工编号：" << endl;
			cin >> id;

			int ret = IsExist(id);
			if (ret != -1) {
				cout << "查找成功！职工信息如下：" << endl;
				this->m_EmpArray[ret]->ShowInfo();
			}
			else {
				cout << "查找失败！不存在这个职工编号！" << endl;
			}
		}
		else if (select == 2) {
			string name;
			cout << "请输入查找的姓名：" << endl;
			cin >> name;

			bool flag = false; //默认未找到职工

			for (int i = 0; i < this->m_EmpNum; i++) {
				if (this->m_EmpArray[i]->m_Name == name) {
					cout << "查找成功，职工信息如下：" << endl;
					this->m_EmpArray[i]->ShowInfo();
					flag = true;
				}
			}
			if (!flag) {
				cout << "查找失败，查无此人！" << endl;
			}
		}
		else {
			cout << "输入选项有误！" << endl;
		}
	}
}
//按照编号排序
void WorkerManager::SortEmp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空！" << endl;
	}
	else {
		cout << "请选择排序方式：" << endl;
		cout << "1.按照职工号进行升序排序" << endl;
		cout << "2.按照职工号进行降序排序" << endl;

		int select = 0;
		cin >> select;

		for (int i = 0; i < this->m_EmpNum; i++) {
			int minOrMax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++) {
				if (select == 1) { //升序
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id) {
						minOrMax = j;
					}
				}
				else { //降序
					if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id) {
						minOrMax = j;
					}
				}
			}
			//如果最开始的最大值或最小值不是计算后的最大值或最小值，交换数据
			if (i != minOrMax) {
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}

		cout << "排序成功！排序后的结果为：" << endl;
		this->SaveToFile();
		this->ShowEmp();
	}
}
//清空文件
void WorkerManager::ClearFile() {
	cout << "是否确认清空？" << endl;
	cout << "** 1.是" << endl;
	cout << "** 2.否" << endl;

	int select = 0;
	cin >> select;

	if (select == 1) {
		ofstream ofs;
		ofs.open(FILENAME, ios::trunc); //删除文件后重新创建
		ofs.close();

		if (this->m_EmpArray != NULL) {
			//删除堆区的每个职工对象
			for (int i = 0; i < this->m_EmpNum; i++) {
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			//删除堆区数组指针
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功！" << endl;
	}
	return;
}

WorkerManager::~WorkerManager() {
	if (this->m_EmpArray != NULL) {
		/*delete m_EmpArray;
		m_EmpArray = NULL;*/
		for (int i = 0; i < this->m_EmpNum; i++) {
			if (this->m_EmpArray[i] != NULL) {
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}