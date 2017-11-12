// wordControl.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "wordControl.h"
#include<stdlib.h>
#include <iostream>
using namespace std;

wordControl::wordControl() {
	head = NULL;
	tail = NULL;
	current = NULL;
	length = 0;
	count = 0;
}

void wordControl::wordAddToTail(string variableData) {
	if (head == NULL) {
		head = new doubleLink(variableData);
		length++;
		count += variableData.length();
		tail = head;
		current = head;
	}
	else {
		doubleLink* pVariable1 = new doubleLink(variableData);
		length++;
		count += variableData.length();
		tail->next = pVariable1;
		pVariable1->prev = tail;
		tail = pVariable1;
		current = pVariable1;
	}
}

void wordControl::replaceCurrentLine(string replace) {
	count -= current->data.length();
	current->data = replace;
	count += replace.length();
}

void wordControl::deleteLine(int position) {
	if (position > length) {
		cout << "it surpass the length" << endl;
	}
	if (position == 1) {
		count -= head->data.length();
		doubleLink* variableP = head;
		head = head->next;
		head->prev = NULL;
		delete variableP;
		length--;
	}
	else if (position == length) {
		count -= tail->data.length();
		doubleLink* variableP = tail;
		tail = tail->prev;
		tail->next = NULL;
		delete variableP;
		length--;
	}
	else {
		doubleLink* variableP = head;
		for (int i = 1; i < (position - 1); i++) {
			variableP = variableP->next;
		}
		count -= variableP->data.length();
		doubleLink* variablePP = variableP->next;
		variableP->next = variablePP->next;
		variablePP->next->prev = variableP;
		delete variablePP;
		length--;
	}
}

void wordControl::printList(int operation, int position) {
	if (length == 0)
	{
		cout << "There is no data" << endl;
	}
	else if (length < position)
	{
		cout << "The postion surpass the length" << endl;
	}
	else
	{
		if ((operation == 0) && (position != 0)) { //显示某一位置文字
			current = head;
			for (int i = 1; i < position; i++) {
				current = current->next;
			}
			cout << current->data << endl;
		}

		else if ((operation == 1) && (position == 0)) { //显示所有文字
			current = head;
			while (current) {
				cout << current->data << endl;
				current = current->next;
			}
		}
		else if ((operation == 2) && (position == 0)) { //显示第一行文字
			cout << head->data << endl;
			current = head;
		}
		else if ((operation == 3) && (position == 0)) { //显示最后一行文字
			cout << tail->data << endl;
			current = tail;
		}
		else if ((operation == 5) && ((position == 0))) { //显示当前行的前一行文字
			if (current->prev == NULL) {
				cout << "the line is the top" << endl;
			}
			else {
				cout << current->prev->data << endl;
				current = current->prev;
			}
		}
		else if ((operation == 6 && (position == 0)))
		{ //显示当前行的后一行文字
			if (current->next == NULL) {
				cout << "the line is the bottom" << endl;
			}
			else {
				cout << current->next->data << endl;
				current = current->next;
			}
		}
		else if ((operation == 4) && (position == 0)) { //显示当前行的文字
			cout << current->data << endl;
		}
	}
}

void wordControl::searchSubString(string substr) {
	current = head;
	int substrlength = substr.length();
	for (int i = 0; i < length; i++) {
		int substrJ = 0, strI = 0, times = 0, currentdatalength = current->data.length();
		while (substrJ<substrlength && strI < currentdatalength) {
			if ((current->data)[strI] == substr[substrJ]) {
				substrJ++;
				strI++;
			}
			else {
				substrJ = 0;
				times++;
				strI = times;
			}
		}
		if (substrJ == substr.length())
			cout << i << "行:" << current->data << endl;
		if (i != length - 1)
			current = current->next;
	}
	current = tail;
	int substrJ = 0, strI = 0, times = 0, currentdatalength = current->data.length();
	while (substrJ<substrlength && strI < currentdatalength) {
		if ((current->data)[strI] == substr[substrJ]) {
			substrJ++;
			strI++;
		}
		else {
			substrJ = 0;
			times++;
			strI = times;
		}
	}
	if (substrJ == substr.length())
		cout << length << "行:" << current->data << endl;

}
void wordControl::moveCurrentPointer(int position) {
	current = head;
	if (length < position) {
		cout << "The postion surpass the length" << endl;
	}
	else {
		for (int i = 1; i < position; i++) {
			current = current->next;
		}
	}

}

void wordControl::outStrToFile(fstream *outfile)
{
	current = head;
	string s;
	for (int i = 0; i<(length - 1); i++)
	{
		string str;
		str = current->data;
		*outfile << str << endl;
		current = current->next;
	}
	s = current->data;
	*outfile << s << endl;
}

void wordControl::insertWord(int position, string str)
{
	if (position > length)
	{
		cout << "it surpass the length of the list" << endl;
	}
	else if(position <= 0)
	{
		cout << "wrong input" << endl;
	}
	else
	{
		if (position == 1)
		{
			doubleLink* headNode = new doubleLink(str);
			headNode->next = head;
			head->prev = headNode;
			headNode->prev = NULL;
			current = headNode;
			head = headNode;
			count += str.length();
			length++;
		}
		else if(position = length)
		{
			doubleLink* tailNode = new doubleLink(str);
			tailNode->prev = tail;
			tailNode->next = NULL;
			tail->next = tailNode;
			tail = tailNode;
			current = tailNode;
			count += str.length();
			length++;
		}
		else
		{
			doubleLink* middleNode = new doubleLink(str);
			current = head;
			for (int i = 1; i < (length - 1); i++)
			{
				current = current->next;
			}
			current->next->prev = middleNode;
			middleNode->next = current->next;
			current->next = middleNode;
			middleNode->prev = current;
			current = middleNode;
			length++;
			count += str.length();
		}
	}
}

void wordControl::getLength() {
	cout << "the count of line:" << length << endl;
	cout << "the count of word:" << count << endl;
}


int main() {
	wordControl list;  //建立链表
	fstream memoryFile;  //在内存中建立文件
	string inName;  //输入文件名
	string quit; //退出指令
	string str; //读入文件的中间字符
	cout << "please write down the import file name:" << endl;
	cin >> inName;
	memoryFile.open(inName.c_str(), ios::in);
	//判断是否输入错误
	while (memoryFile.fail()) {
		cout << "we can't open the file, please re-enter the name:";
		cin >> inName;
		memoryFile.open(inName.c_str(), ios::in);
	}
	//读入数据
	while (!memoryFile.eof()) {
		char temp[100];
		memoryFile.getline(temp, 100);
		str = temp;
		list.wordAddToTail(str);
	}
	//关闭文件
	memoryFile.close();
	//输入指令
	while (quit != "q") {
		string instruction;//指令
		cout << "please enter instruction(enter h for help): ";
		cin >> instruction;
		if (instruction == "h") {
			cout << "sa(showall:显示所有内容)" << endl;
			cout << "sf(showfirst:显示第一行文字)" << endl;
			cout << "sl(showlast:显示最后一行文字)" << endl;
			cout << "sp(showpresent:显示当前行文字)" << endl;
			cout << "spp(showpresentprev:显示当前行前一行文字)" << endl;
			cout << "spn(showpresentnext:显示当前行后一行文字)" << endl;
			cout << "ins(insert:在指定位置插入字符串)" << endl;
			cout << "sea(search:搜索字串)" << endl;
			cout << "del(delete:删除某一行)" << endl;
			cout << "rep(replace:改变某一行)" << endl;
			cout << "add(add:在末尾添加一行)" << endl;
			cout << "savef(savefile:存储文件" << endl;
			cout << "len(length:获取文件行数和文字数量)" << endl;
			cout << "q(quit:退出程序)" << endl;
		}
		else if (instruction == "sa") {
			list.printList(1, 0);
		}
		else if (instruction == "sf") {
			list.printList(2, 0);
		}
		else if (instruction == "sl") {
			list.printList(3, 0);
		}
		else if (instruction == "sp") {
			list.printList(4, 0);
		}
		else if (instruction == "spp") {
			list.printList(5, 0);
		}
		else if (instruction == "spn") {
			list.printList(6, 0);
		}
		else if (instruction == "sea") {
			cout << "please input substring:";
			string ss;
			cin >> ss;
			list.searchSubString(ss);
		}
		else if (instruction == "del") {
			cout << "please input line number:";
			int ln;
			cin >> ln;
			list.deleteLine(ln);
		}
		else if (instruction == "rep") {
			cout << "please input change line number:";
			int ln;
			cin >> ln;
			list.moveCurrentPointer(ln);
			cout << "please input the replace word:";
			string rep;
			cin.ignore();
			getline(cin, rep);
			list.replaceCurrentLine(rep);
		}
		else if (instruction == "add") {
			cout << "please input the word" << endl;
			string str;
			cin.ignore(); //清除缓存区的换行符，防止cin录入"/n"使得无法录入文字
			getline(cin, str);
			list.wordAddToTail(str);
		}
		else if (instruction == "q") {
			quit = "q";
		}
		else if (instruction == "savef")
		{
			cout << "please input the out-file name:";
			string outf;
			cin >> outf;
			fstream outfile;
			fstream *pf = &outfile;
			outfile.open(outf.c_str(), ios::out);
			list.outStrToFile(pf);
			cout << "outfile successfule!" << endl;
		}
		else if (instruction == "len")
		{
			list.getLength();
		}
		else if (instruction == "ins")
		{
			cout << "please input the insert word of position:";
			int pos;
			cin >> pos;
			cout << "please input the word:";
			string ins;
			cin.ignore();
			getline(cin, ins);
			list.insertWord(pos, ins);
		}
		else
		{
			cout << "wrong instruction!" << endl;
		}
	}
	return 0;
}
