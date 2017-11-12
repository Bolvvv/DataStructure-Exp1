// wordControl.cpp : �������̨Ӧ�ó������ڵ㡣
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
		if ((operation == 0) && (position != 0)) { //��ʾĳһλ������
			current = head;
			for (int i = 1; i < position; i++) {
				current = current->next;
			}
			cout << current->data << endl;
		}

		else if ((operation == 1) && (position == 0)) { //��ʾ��������
			current = head;
			while (current) {
				cout << current->data << endl;
				current = current->next;
			}
		}
		else if ((operation == 2) && (position == 0)) { //��ʾ��һ������
			cout << head->data << endl;
			current = head;
		}
		else if ((operation == 3) && (position == 0)) { //��ʾ���һ������
			cout << tail->data << endl;
			current = tail;
		}
		else if ((operation == 5) && ((position == 0))) { //��ʾ��ǰ�е�ǰһ������
			if (current->prev == NULL) {
				cout << "the line is the top" << endl;
			}
			else {
				cout << current->prev->data << endl;
				current = current->prev;
			}
		}
		else if ((operation == 6 && (position == 0)))
		{ //��ʾ��ǰ�еĺ�һ������
			if (current->next == NULL) {
				cout << "the line is the bottom" << endl;
			}
			else {
				cout << current->next->data << endl;
				current = current->next;
			}
		}
		else if ((operation == 4) && (position == 0)) { //��ʾ��ǰ�е�����
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
			cout << i << "��:" << current->data << endl;
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
		cout << length << "��:" << current->data << endl;

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
	wordControl list;  //��������
	fstream memoryFile;  //���ڴ��н����ļ�
	string inName;  //�����ļ���
	string quit; //�˳�ָ��
	string str; //�����ļ����м��ַ�
	cout << "please write down the import file name:" << endl;
	cin >> inName;
	memoryFile.open(inName.c_str(), ios::in);
	//�ж��Ƿ��������
	while (memoryFile.fail()) {
		cout << "we can't open the file, please re-enter the name:";
		cin >> inName;
		memoryFile.open(inName.c_str(), ios::in);
	}
	//��������
	while (!memoryFile.eof()) {
		char temp[100];
		memoryFile.getline(temp, 100);
		str = temp;
		list.wordAddToTail(str);
	}
	//�ر��ļ�
	memoryFile.close();
	//����ָ��
	while (quit != "q") {
		string instruction;//ָ��
		cout << "please enter instruction(enter h for help): ";
		cin >> instruction;
		if (instruction == "h") {
			cout << "sa(showall:��ʾ��������)" << endl;
			cout << "sf(showfirst:��ʾ��һ������)" << endl;
			cout << "sl(showlast:��ʾ���һ������)" << endl;
			cout << "sp(showpresent:��ʾ��ǰ������)" << endl;
			cout << "spp(showpresentprev:��ʾ��ǰ��ǰһ������)" << endl;
			cout << "spn(showpresentnext:��ʾ��ǰ�к�һ������)" << endl;
			cout << "ins(insert:��ָ��λ�ò����ַ���)" << endl;
			cout << "sea(search:�����ִ�)" << endl;
			cout << "del(delete:ɾ��ĳһ��)" << endl;
			cout << "rep(replace:�ı�ĳһ��)" << endl;
			cout << "add(add:��ĩβ���һ��)" << endl;
			cout << "savef(savefile:�洢�ļ�" << endl;
			cout << "len(length:��ȡ�ļ���������������)" << endl;
			cout << "q(quit:�˳�����)" << endl;
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
			cin.ignore(); //����������Ļ��з�����ֹcin¼��"/n"ʹ���޷�¼������
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
