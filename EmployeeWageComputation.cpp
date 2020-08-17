#include <iostream>
#include <time.h>

using namespace std;
bool isPresent();

int main(int argc, char const *argv[])
{
    cout << "Presenty status: " << isPresent();
    return 0;
}

bool isPresent()
{
    srand(time(0));
    int result = rand() % 2;
    if (result == 1)
        return true;
    return false;
}