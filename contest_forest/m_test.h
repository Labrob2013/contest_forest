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

//- Персонаж
struct T_Character {
	Character character{};
	Direction direction{};
	T_POS pos;
};

//- Пакет данных
struct T_DATA {
	int turns = 0;
	T_MAP actor1, actor2;
};

class test
{
public:
	test();
	~test();

	//- Записываем значение в список (по умолчанию = Провалено испытание)
	void create(int turns = 1000);

	//- Показ карты
	void draw(int id);

	//- Смотрим информацию о тестах
	void info();

private:
	Fairyland *world = NULL;

	//- Статусы тестирования
	std::vector<T_DATA> tests;

	//- Перемещение героев
	bool move(T_Character& object, T_Character& object2);

	//- Считаем координаты
	void moveCalc(Direction direction, T_POS &pos);
};