#include "m_test.h"

//- �������� �������
test::test() {
    world = new Fairyland();
}

//- �����������
test::~test() { 
    tests.clear(); delete world;
}

//- ������� ������� � ���������
void test::create(int turns)
{
    //- ���� ��� �� ������, �� �������
    if (world == NULL)
        world = new Fairyland();

    T_Character Ivan, Elena;
    T_DATA data;
    int d = 0;

    for (int i = 0; i < turns; ++i)
    {
        //- ���������� ������
        Ivan.character = Character::Ivan;
        Elena.character = Character::Elena;

        //- ������ �����������, ����
        move(Ivan, Elena);

        //- ������� �������� � �������
        data.actor1.push_back({ Ivan.pos.first, Ivan.pos.second });
        data.actor2.push_back({ Elena.pos.first, Elena.pos.second });
        data.turns = world->getTurnCount();
    }

    //- ��������� ����� � ������
    tests.push_back(data);

    //- ������� ������� ���
    world = NULL;
}

//- ����� �����
void test::draw(int id)
{
    //- ������� ���������� �����
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

    //- ������� �������� � �������
    //- ������ ���� �����
    for (int i = 0; i < ac1.size(); i++)
    {
        int x = ac1[i].second, y = ac1[i].first;
        if (y < T_MATSZ && x < T_MATSZ) arr[y][x] = (i != ac1.size() - 1) ? '.' : '@';
    }
    //- ������ ���� ����� (�� ������ � ������������)
    for (int i = 0; i < ac2.size(); i++)
    {
        if((i == ac2.size() - 1)) 
            arr[ac2[i].first][ac2[i].second] = '&';
    }

    //- ����� ����� ��������
    for (int i = 0; i < T_MATSZ; i++)
    {
        for (int j = 0; j < T_MATSZ; j++) std::cout << arr[i][j];
        LOG("");
    }

    LOG("");
}

//- ����������� ������
bool test::move(T_Character& object, T_Character& object2)
{
    bool
        //- ����� ��������� ������ �����
        result = false,
     
        //- ������ �� �����?
        ready1 = false,
        ready2 = false;
    while (!result)
    {
        //- ���� ������ ����� �� �����
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

            //- ����� �� ���� �����?
            if (world->canGo(object.character, object.direction))
            {
                moveCalc(object.direction, object.pos);
                ready1 = true;
            }
        }
        //- ���� ������ ����� �� �����
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

            //- ����� �� ���� �����?
            if (world->canGo(object2.character, object2.direction))
            {
                moveCalc(object2.direction, object2.pos);
                ready2 = true;
            }
        }
        
        //- ��������� ���� ���� ������!
        if (ready1 && ready2)
        {
            //- �����������
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

//- ������� ����������
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

//- ��������� ����
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