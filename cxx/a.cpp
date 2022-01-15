#include <iostream>

using namespace std;

int main()
{
    int i ;
    auto func = [&] () { cout << "Hello world << " << i << std::endl ; };
    func(); // now call the function
}