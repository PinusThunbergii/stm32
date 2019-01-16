extern "C"
{
#include "clock.h"
}
#include <vector>
#include "test_class.hpp"

char * global_str = "I`m global!!!"; 
int integer_global = 0x30313233;
int none_init_int;
void foo()
{
    char str[40] = "Hello world!!!"; 
    str[12] = 'G';
}

TestClass global_class_with_static_item_0(5);
TestClass global_class_with_static_item_1(2);
TestClass global_class_with_static_item_2(6);
int main()
{
    enableHSE();
    foo();
    /*global_class_with_static_item.setI(55);
    std::vector<int> vec(0);
    vec.push_back(6);*/
    while(0) 
    {

    }
    return 0;
}