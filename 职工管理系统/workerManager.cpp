#include "workerManager.h"

WorkerManager::WorkerManager() {

	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open()) {
		//cout << "�ļ�������" << endl;
		//��ʼ������
		this->m_EmpNum = 0; //��ʼ����¼����
		this->m_EmpArray = NULL; //��ʼ������ָ��
		this->m_FileIsEmpty = true; //��ʼ���ļ��Ƿ�Ϊ��
	}
	else {
		char ch;
		ifs >> ch;
		//�ļ����ڣ�����Ϊ��
		if (ifs.eof()) {
			//cout << "�ļ�Ϊ��" << endl;
			//��ʼ������
			this->m_EmpNum = 0; //��ʼ����¼����
			this->m_EmpArray = NULL; //��ʼ������ָ��
			this->m_FileIsEmpty = true; //��ʼ���ļ��Ƿ�Ϊ��
		}
		//�ļ����������ݲ�Ϊ��
		else {
			int num = this->GetFileEmpNum();
			//cout << "ְ������Ϊ��" << num << endl;
			this->m_EmpNum = num;
			//���ٿռ�
			this->m_EmpArray = new Worker * [this->m_EmpNum];
			//���ļ������ݴ浽������
			this->InitEmp();

			/*for (int i = 0; i < this->m_EmpNum; i++) {
				cout << "ְ����ţ�" << this->m_EmpArray[i]->m_Id
					<< " ������" << this->m_EmpArray[i]->m_Name
					<< " ���ű�ţ�" << this->m_EmpArray[i]->m_DeptId << endl;
			}*/
		}
		ifs.close();
	}
}

//˽�г�Ա������get��set����
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

//��ʾ�˵�
void WorkerManager::ShowMenu() {
	cout << "************************************************" << endl;
	cout << "*************��ӭʹ��ְ������ϵͳ��*************" << endl;
	cout << "***************  0.�˳��������  ***************" << endl;
	cout << "***************  1.����ְ����Ϣ  ***************" << endl;
	cout << "***************  2.��ʾְ����Ϣ  ***************" << endl;
	cout << "***************  3.ɾ����ְְ��  ***************" << endl;
	cout << "***************  4.�޸�ְ����Ϣ  ***************" << endl;
	cout << "***************  5.����ְ����Ϣ  ***************" << endl;
	cout << "***************  6.���ձ������  ***************" << endl;
	cout << "***************  7.��������ĵ�  ***************" << endl;
	cout << "************************************************" << endl;
	cout << endl;
}
//�˳�����
void WorkerManager::ExitSystem() {
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0); //�˳�����
}
//���ְ��
void WorkerManager::AddEmp() {
	cout << "���������ְ����������" << endl;
	int addNum = 0;
	cin >> addNum;

	if (addNum) {
		//��������ӵĿռ�Ĵ�С��ԭ����ְ������+����ӵ�ְ������
		int newSize = this->m_EmpNum + addNum;
		//�����¿ռ�
		Worker** newSpace = new Worker* [newSize];

		//���ԭ���Ŀռ������ݣ���ԭ���ռ�����ݿ������¿ռ�
		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		//�������������
		for (int i = 0; i < addNum; i++) {
			int id; //���ű��
			string name; //ְ������
			int depSelect; //����ѡ��

			cout << "������� " << i + 1 << " ����ְ�����: " << endl;
			cin >> id;
			cout << "������� " << i + 1 << " ����ְ������: " << endl;
			cin >> name;
			cout << "��ѡ���ְ���ĸ�λ��" << endl;
			cout << "** 1.��ְͨ��" << endl;
			cout << "** 2.����" << endl;
			cout << "** 3.�ϰ�" << endl;
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
				cout << "��λѡ���������ʧ��" << endl;
				break;
			}
			//��������ְ��ְ�𣬱��浽����
			//ԭ���Ŀռ�������������ӵĵ�i��ְ�����ǵ�ǰ�ռ�����һ���±�
			newSpace[this->m_EmpNum + i] = worker;
		}
		//�ͷ�ԭ���Ŀռ�
		delete[] this->m_EmpArray;

		//�����¿ռ��ָ��
		this->m_EmpArray = newSpace;

		//�����µ�ְ������
		this->m_EmpNum = newSize;

		//�����ļ���Ϊ��
		this->m_FileIsEmpty = false;

		//��������ӵ��ļ�
		this->SaveToFile();

		//��ʾ��ӳɹ�
		cout << "�ɹ����" << addNum << "����ְ��" << endl;
	}
	else {
		cout << "������������" << endl;
	}
	//system("pause");
	//system("cls");
}
//���浽�ļ�
void WorkerManager::SaveToFile() {
	ofstream ofs;
	//������ķ�ʽ���ļ�����д�ļ�
	ofs.open(FILENAME, ios::out);
	//��ÿ���˵�����д�뵽������
	for (int i = 0; i < this->m_EmpNum; i++) {
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	//�ر��ļ�
	ofs.close();
}
//ͳ���ļ��е�����
int WorkerManager::GetFileEmpNum() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int deptId;
	int num = 0; //ͳ�������ı���
	while (ifs >> id && ifs >> name && ifs >> deptId) {
		++num;
	}
	ifs.close();

	return num;
}
//��ʼ��Ա��
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
			cout << "��ȡ�ļ�Ա����Ŵ���" << endl;
			return;
		}

		this->m_EmpArray[index++] = worker;
	}

	ifs.close();
}
//��ʾ����Ա��
void WorkerManager::ShowEmp() {
	//�ж��ļ��Ƿ�Ϊ��
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else {
		for (int i = 0; i < m_EmpNum; i++) {
			//���ö�̬���ó���ӿ�
			this->m_EmpArray[i]->ShowInfo();
		}
	}
	//system("pause");
	//system("cls");
}
//��ѯԱ���Ƿ����
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
//ɾ��ְ��
void WorkerManager::DeleteEmp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else {
		this->ShowEmp();
		cout << "��������Ҫɾ��ְ���ı�ţ�" << endl;
		int id = 0;
		cin >> id;

		int index = this->IsExist(id);
		if (index != -1) { //����
			//����ǰ��
			for (int i = index; i < this->m_EmpNum - 1; i++) {
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			--this->m_EmpNum;
			//����ͬ�����µ��ļ�
			this->SaveToFile();
			cout << "ɾ���ɹ���" << endl;
		}
		else {
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ����" << endl;
		}
	}
	//system("pause");
	//system("cls");
}
//�޸�ְ����Ϣ
void WorkerManager::ModifyEmp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else {
		this->ShowEmp();

		cout << "������Ҫ�޸ĵ�ְ����ţ�" << endl;
		int id;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret != -1) {
			delete this->m_EmpArray[ret];
			int newId = 0;
			string newName = "";
			int deptSelect = 0;
			cout << "�鵽��" << id << "��ְ�����������µ�ְ���ţ�" << endl;
			cin >> newId;
			cout << "�������µ�������" << endl;
			cin >> newName;
			cout << "�������λ��" << endl;
			cout << "** 1.��ְͨ��" << endl;
			cout << "** 2.����" << endl;
			cout << "** 3.�ϰ�" << endl;
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
				cout << "���ű����д�����޸�ʧ�ܣ�" << endl;
				//Ȼ������ش�����ӳɹ���ʧ�ܵı�ǵ�
				break;
			}
			this->m_EmpArray[ret] = worker;
			this->SaveToFile();

			cout << "�޸ĳɹ���" << endl;
		}
		else {
			cout << "�޸�ʧ�ܣ����޴��ˣ�" << endl;
		}
	}
}
//����ְ��
void WorkerManager::FindEmp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else {
		cout << "��������ҵķ�ʽ��" << endl;
		cout << "** 1.����ְ����Ų���" << endl;
		cout << "** 2.����ְ����������" << endl;
		int select = 0;
		cin >> select;
		if (select == 1) {
			int id;
			cout << "��������ҵ�ְ����ţ�" << endl;
			cin >> id;

			int ret = IsExist(id);
			if (ret != -1) {
				cout << "���ҳɹ���ְ����Ϣ���£�" << endl;
				this->m_EmpArray[ret]->ShowInfo();
			}
			else {
				cout << "����ʧ�ܣ����������ְ����ţ�" << endl;
			}
		}
		else if (select == 2) {
			string name;
			cout << "��������ҵ�������" << endl;
			cin >> name;

			bool flag = false; //Ĭ��δ�ҵ�ְ��

			for (int i = 0; i < this->m_EmpNum; i++) {
				if (this->m_EmpArray[i]->m_Name == name) {
					cout << "���ҳɹ���ְ����Ϣ���£�" << endl;
					this->m_EmpArray[i]->ShowInfo();
					flag = true;
				}
			}
			if (!flag) {
				cout << "����ʧ�ܣ����޴��ˣ�" << endl;
			}
		}
		else {
			cout << "����ѡ������" << endl;
		}
	}
}
//���ձ������
void WorkerManager::SortEmp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else {
		cout << "��ѡ������ʽ��" << endl;
		cout << "1.����ְ���Ž�����������" << endl;
		cout << "2.����ְ���Ž��н�������" << endl;

		int select = 0;
		cin >> select;

		for (int i = 0; i < this->m_EmpNum; i++) {
			int minOrMax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++) {
				if (select == 1) { //����
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id) {
						minOrMax = j;
					}
				}
				else { //����
					if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id) {
						minOrMax = j;
					}
				}
			}
			//����ʼ�����ֵ����Сֵ���Ǽ��������ֵ����Сֵ����������
			if (i != minOrMax) {
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}

		cout << "����ɹ��������Ľ��Ϊ��" << endl;
		this->SaveToFile();
		this->ShowEmp();
	}
}
//����ļ�
void WorkerManager::ClearFile() {
	cout << "�Ƿ�ȷ����գ�" << endl;
	cout << "** 1.��" << endl;
	cout << "** 2.��" << endl;

	int select = 0;
	cin >> select;

	if (select == 1) {
		ofstream ofs;
		ofs.open(FILENAME, ios::trunc); //ɾ���ļ������´���
		ofs.close();

		if (this->m_EmpArray != NULL) {
			//ɾ��������ÿ��ְ������
			for (int i = 0; i < this->m_EmpNum; i++) {
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			//ɾ����������ָ��
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "��ճɹ���" << endl;
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