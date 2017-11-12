#pragma once
#include "stdafx.h"
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

struct doubleLink   //节点
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

class wordControl  //线性表
{
private:
	doubleLink* head;  //头指针
	doubleLink* tail;  //尾指针
	doubleLink* current;  //当前指针
	int length;  //链表行数
	int count;  //链表字数
public:
	wordControl();
	void wordAddToTail(string variableData);  //添加行到尾部
	void printList(int operation, int position);  //打印行文字
	void replaceCurrentLine(string replace);  //替换当前行文字
	void deleteLine(int postion);  //删除指定行文字
	void searchSubString(string substr);  //搜索字串
	void moveCurrentPointer(int position);  //移动当前指针到指定位置
	void getLength();  //链表行数
	void outStrToFile(fstream* outfile);  //输出到文件
	void insertWord(int position, string str);  //插入行
};