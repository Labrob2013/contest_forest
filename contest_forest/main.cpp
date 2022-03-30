#include <cstdlib>
#include <ctime>
#include "m_test.h"

int main()
{
    //- Задаем сид для генератора
    srand(static_cast<unsigned int>(time(nullptr)));

    //- Объявляем менеджер тестов
    test tester;

    LOG("[Create test 1, turns=" << 1000 << "]");
    tester.create(1000);

    LOG("[Create test 2, turns=" << 500 << "]");
    tester.create(500);

    LOG("[Create test 3, turns=" << 250 << "]");
    tester.create(250);

    //- Выводим результаты
    tester.info();

    system("pause");

    return 0;
}
