#pragma once 

#include <iostream>
#include <string>
#include <iomanip>
#include "bin.h"

using namespace std;

struct Element {
	int id = 0;
	int id_bin = 0;
	Element() {};
	Element(int id) {
		this->id = id;
	}
	Element(int id, int id_bin) {
		this->id = id;
		this->id_bin = id_bin;
	}
	bool openORclose = true;
	bool delORnot = false; 
};

struct HashTable {
	int table_size;
	int getSizee() { return table_size; };
	Element* T;
	void createHashTable(int table_size) {
		this->table_size = table_size;
		Element elem_x;
		T = new Element[table_size];
		for (int i = 0; i < table_size; i++) {
			T[i] = elem_x;
		}
	}
	int ins_count = 0; //кол-во вставленных ключей
	int del_count = 0; //кол-во удаленных ключей
};


Element errElement;

void rehashTable(HashTable& table);

int hashFunc1(int key, int table_size) {
	return key % table_size;
}

int hashFunc2(int key, int table_size) {
	return key / table_size;
}

void insertElement(Element elem, HashTable& table) { // Вставить ключ в таблицу
	if (table.ins_count + table.del_count == table.table_size -1) { // Проверка необходимости рехеширования
		rehashTable(table);
	}
	int index_1;
	int index = hashFunc1(elem.id, table.table_size);
	while (true) {
		if (table.T[index].openORclose) {
			table.T[index] = elem;
			if (table.T[index].delORnot) table.del_count--;
			break;
		}
		else {
			index_1 = (index + hashFunc2(elem.id, table.table_size)) % table.table_size;
			if (index_1 == index) index = (index + hashFunc2(elem.id, table.table_size) + 10) % table.table_size;
			else index = (index + hashFunc2(elem.id, table.table_size)) % table.table_size;
		}
	}
	table.ins_count++;
	table.T[index].openORclose = false;
	table.T[index].delORnot = false;
}

Element searchElement(int key, HashTable& table) { // Найти ключ в таблице
	Element errElement;
	int index_1;
	int index = hashFunc1(key, table.table_size);
	while (true) {
		if (table.T[index].openORclose && !table.T[index].delORnot) {
			return errElement;
		}
		if (table.T[index].id == key && !table.T[index].delORnot) {
			return table.T[index];
		}
		else {
			index_1 = (index + hashFunc2(key, table.table_size)) % table.table_size;
			if (index_1 == index) index = (index + hashFunc2(key, table.table_size) + 10) % table.table_size;
			else index = (index + hashFunc2(key, table.table_size)) % table.table_size;
		}
	}
}

int deleteElement(int key, HashTable& table) { // Удалить ключ
	int sizeTab = table.table_size;
	int index = hashFunc1(key, sizeTab);
	int index_1;
	Element nullElement;
	while (true) {
		if (table.T[index].openORclose && !table.T[index].delORnot) {
			return -3;
		}
		if (table.T[index].id == key) {
			table.T[index] = nullElement;
			break;
		}
		else {
			index_1 = (index + hashFunc2(key, sizeTab)) % sizeTab;
			if (index_1 == index) index = (index + hashFunc2(key, sizeTab) + 10) % sizeTab;
			else index = (index + hashFunc2(key, sizeTab)) % sizeTab;
		}
	}
	table.T[index].openORclose = true;
	table.T[index].delORnot = true;
	table.ins_count--;
	table.del_count++;
	return 1;
}

void rehashTable(HashTable& table) { // Рехешировать таблицу
	int old_size = table.table_size;
	Element* old_table = table.T;
	table.table_size = old_size * 2;
	table.del_count = 0;
	table.T = new Element[old_size * 2];
	for (int i = 0; i < old_size; i++) {
		if (!old_table[i].openORclose && !old_table[i].delORnot) {
			insertElement(old_table[i], table);
		}
	}
}

void printTable(HashTable& table) { // Вывод таблицы в консоль
	cout << endl << "==============" << endl << endl;
	cout << "key \tid \tid_bin" << endl;
	for (int i = 0; i < table.table_size; i++) {
		cout << i << "\t" << table.T[i].id << "\t" <<  setw(2) << right <<table.T[i].id_bin << endl;
	}
}

void test_hash() {
	setlocale(0, "");
	HashTable table;
	table.createHashTable(15);
	Element e1(456758);
	insertElement(e1, table); //456758 % 15 = 8
	printTable(table);
	Element e2(922868);
	insertElement(e2, table); //922868 % 15 = 8			(922868 + 922868 // 15) % 15 = 2
	printTable(table);


	HashTable table_1;
	table_1.createHashTable(4);
	insertElement(e1, table_1); 
	insertElement(e2, table_1);
	Element e3(657849);
	insertElement(e3, table_1);
	printTable(table_1);
	Element e4(357876);
	insertElement(e4, table_1);
	printTable(table_1);
	deleteElement(922868, table_1);
	printTable(table_1);
	Element e = searchElement(357876, table_1);
	if (e.id == 0) {
		cout << "Не найдено!";
	}
	else {
		cout << "\nИскомый элемент:\n";
		cout << e.id << endl;
	}

	HashTable table_2;
	table_2.createHashTable(6);
	insertElement(e1, table_2); //456758 % 15 = 8
	insertElement(e2, table_2); //922868 % 15 = 8
	insertElement(e3, table_1);
	insertElement(e4, table_1);
	printTable(table_2);
	deleteElement(456758, table_2);
	printTable(table_2);
	Element e_1 = searchElement(922868, table_2);
	if (e_1.id == 0) {
		cout << "Не найдено!";
	}
	else {
		cout << "\nИскомый элемент:\n";
		cout << e_1.id << endl;
	}
}