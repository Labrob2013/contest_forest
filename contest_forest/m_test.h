#pragma once
#include <chrono>
#include <thread>
#include <vector>
#include <string>

//- 
#include "fairy_tail.hpp"


#define LOG(x) std::cout << x << std::endl;
#define T_MATSZ 10

typedef std::pair<int, int> T_POS;
typedef std::vector<T_POS> T_MAP;

//- ��������
struct T_Character {
	Character character{};
	Direction direction{};
	T_POS pos;
};

//- ����� ������
struct T_DATA {
	int turns = 0;
	T_MAP actor1, actor2;
};

class test
{
public:
	test();
	~test();

	//- ���������� �������� � ������ (�� ��������� = ��������� ���������)
	void create(int turns = 1000);

	//- ����� �����
	void draw(int id);

	//- ������� ���������� � ������
	void info();

private:
	Fairyland *world = NULL;

	//- ������� ������������
	std::vector<T_DATA> tests;

	//- ����������� ������
	bool move(T_Character& object, T_Character& object2);

	//- ������� ����������
	void moveCalc(Direction direction, T_POS &pos);
};