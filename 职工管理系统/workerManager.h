#pragma once //��ֹͷ�ļ��ظ�����
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
	//��¼ְ������
	int m_EmpNum;
	//ְ������ָ��
	Worker** m_EmpArray;
	//�ж��ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;

public :
	WorkerManager();
	int getEmpNum();
	void setEmpNum(int empNum);
	Worker** getEmpArray();
	void setEmpArray(Worker** empArray);
	bool getFileIsEmpty();
	void setFileIsEmpty(bool isEmpty);

	//չʾ�˵�
	void ShowMenu();
	//�˳�
	void ExitSystem();
	//���ְ��
	void AddEmp();
	//���浽�ļ�
	void SaveToFile();
	//ͳ���ļ��е�����
	int GetFileEmpNum();
	//��ʼ��Ա��
	void InitEmp();
	//��ʾ����Ա��
	void ShowEmp();
	//��ѯԱ���Ƿ����
	int IsExist(int id);
	//ɾ��ְ��
	void DeleteEmp();
	//�޸�ְ����Ϣ
	void ModifyEmp();
	//����ְ��
	void FindEmp();
	//���ձ������
	void SortEmp();
	//����ļ�
	void ClearFile();

	~WorkerManager();
};