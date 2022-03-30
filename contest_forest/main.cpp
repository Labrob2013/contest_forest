#include <cstdlib>
#include <ctime>
#include "m_test.h"

int main()
{
    //- ������ ��� ��� ����������
    srand(static_cast<unsigned int>(time(nullptr)));

    //- ��������� �������� ������
    test tester;

    LOG("[Create test 1, turns=" << 1000 << "]");
    tester.create(1000);

    LOG("[Create test 2, turns=" << 500 << "]");
    tester.create(500);

    LOG("[Create test 3, turns=" << 250 << "]");
    tester.create(250);

    //- ������� ����������
    tester.info();

    system("pause");

    return 0;
}
