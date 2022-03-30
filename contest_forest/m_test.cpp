#include "m_test.h"

//- Создание объекта
test::test() {
    world = new Fairyland();
}

//- Уничтожение
test::~test() { 
    tests.clear(); delete world;
}

//- Создаем задание с условиями
void test::create(int turns)
{
    //- Если мир не создан, то создаем
    if (world == NULL)
        world = new Fairyland();

    T_Character Ivan, Elena;
    T_DATA data;
    int d = 0;

    for (int i = 0; i < turns; ++i)
    {
        //- Обозначаем героев
        Ivan.character = Character::Ivan;
        Elena.character = Character::Elena;

        //- Задаем направление, идем
        move(Ivan, Elena);

        //- Заносим значения в таблицу
        data.actor1.push_back({ Ivan.pos.first, Ivan.pos.second });
        data.actor2.push_back({ Elena.pos.first, Elena.pos.second });
        data.turns = world->getTurnCount();
    }

    //- Добавляем тесты в массив
    tests.push_back(data);

    //- Удаляем текущий мир
    world = NULL;
}

//- Показ карты
void test::draw(int id)
{
    //- Выводим количество ходов
    LOG("[View test " << (id+1) << "]: " << tests[id].turns << " turns");

    char arr[T_MATSZ][T_MATSZ] = {
        //- X
        {'#','#','#','#','#','#','#','#','#','#'}, //- Y
        {'#','#','#','#','#','#','#','#','#','#'},
        {'#','#','#','#','#','#','#','#','#','#'},
        {'#','#','#','#','#','#','#','#','#','#'},
        {'#','#','#','#','#','#','#','#','#','#'},
        {'#','#','#','#','#','#','#','#','#','#'},
        {'#','#','#','#','#','#','#','#','#','#'},
        {'#','#','#','#','#','#','#','#','#','#'},
        {'#','#','#','#','#','#','#','#','#','#'},
        {'#','#','#','#','#','#','#','#','#','#'}
    };
    //- y, x

    T_MAP ac1 = tests[id].actor1;
    T_MAP ac2 = tests[id].actor2;

    //- Заносим значения в таблицу
    //- Расчет пути Ивана
    for (int i = 0; i < ac1.size(); i++)
    {
        int x = ac1[i].second, y = ac1[i].first;
        if (y < T_MATSZ && x < T_MATSZ) arr[y][x] = (i != ac1.size() - 1) ? '.' : '@';
    }
    //- Расчет пути Елены (Не уверен в правильности)
    for (int i = 0; i < ac2.size(); i++)
    {
        if((i == ac2.size() - 1)) 
            arr[ac2[i].first][ac2[i].second] = '&';
    }

    //- Вывод карты маршрута
    for (int i = 0; i < T_MATSZ; i++)
    {
        for (int j = 0; j < T_MATSZ; j++) std::cout << arr[i][j];
        LOG("");
    }

    LOG("");
}

//- Перемещение героев
bool test::move(T_Character& object, T_Character& object2)
{
    bool
        //- Общий результат поиска ходов
        result = false,
     
        //- Готовы ли герои?
        ready1 = false,
        ready2 = false;
    while (!result)
    {
        //- Если первый герой не готов
        if (ready1 == false)
        {
            switch (rand() % 4)
            {
            case 0:
                object.direction = Direction::Up;
                break;
            case 1:
                object.direction = Direction::Down;
                break;
            case 2:
                object.direction = Direction::Left;
                break;
            default:
                object.direction = Direction::Right;
                break;
            }

            //- Может ли идти герой?
            if (world->canGo(object.character, object.direction))
            {
                moveCalc(object.direction, object.pos);
                ready1 = true;
            }
        }
        //- Если второй герой не готов
        if (ready2 == false)
        {
            switch (rand() % 4)
            {
            case 0:
                object2.direction = Direction::Up;
                break;
            case 1:
                object2.direction = Direction::Down;
                break;
            case 2:
                object2.direction = Direction::Left;
                break;
            default:
                object2.direction = Direction::Right;
                break;
            }

            //- Может ли идти герой?
            if (world->canGo(object2.character, object2.direction))
            {
                moveCalc(object2.direction, object2.pos);
                ready2 = true;
            }
        }
        
        //- Проверяем если двое готовы!
        if (ready1 && ready2)
        {
            //- Передвигаем
            world->go(object.direction, object2.direction);

            result = true;
            return true;
        }
        else
        {
            if (ready1 && !ready2)
                world->go(object.direction, Direction::Pass);

            else if (!ready1 && ready2)
                world->go(Direction::Pass, object2.direction);

            result = true;
            return true;
        }
    }

    return false;
}

//- Считаем координаты
void test::moveCalc(Direction direction, T_POS& pos)
{
    switch (direction)
    {
    case Direction::Pass:
        break;
    case Direction::Up:
        if (pos.first <= 0) {}
        else pos.first -= 1;
        break;
    case Direction::Down:
        if (pos.first >= T_MATSZ) {}
        else pos.first += 1;
        break;
    case Direction::Left:
        if (pos.second <= 0) {}
        else pos.second -= 1;
        break;
    case Direction::Right:
        if (pos.second >= T_MATSZ) {}
        else pos.second += 1;
        break;
    default:
        break;
    }
}

//- Запускаем тест
void test::info()
{
    if (tests.size() == 0)
    {
        LOG("There are no created tasks.");
    }
    else
    {
        for (int i = 0; i < tests.size(); i++)
        {
            draw(i);
        }
    }
}