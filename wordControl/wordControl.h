#pragma once
#include "stdafx.h"
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

struct doubleLink   //�ڵ�
{
	string data;
	doubleLink* prev;
	doubleLink* next;
	doubleLink(string variableData)
	{
		data = variableData;
		prev = NULL;
		next = NULL;
	}
};

class wordControl  //���Ա�
{
private:
	doubleLink* head;  //ͷָ��
	doubleLink* tail;  //βָ��
	doubleLink* current;  //��ǰָ��
	int length;  //��������
	int count;  //��������
public:
	wordControl();
	void wordAddToTail(string variableData);  //����е�β��
	void printList(int operation, int position);  //��ӡ������
	void replaceCurrentLine(string replace);  //�滻��ǰ������
	void deleteLine(int postion);  //ɾ��ָ��������
	void searchSubString(string substr);  //�����ִ�
	void moveCurrentPointer(int position);  //�ƶ���ǰָ�뵽ָ��λ��
	void getLength();  //��������
	void outStrToFile(fstream* outfile);  //������ļ�
	void insertWord(int position, string str);  //������
};