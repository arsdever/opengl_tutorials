#include <iostream>
#include <string>
#include <string_view>

std::string a() { return std::string("hello"); }

int main(int argc, char** argv)
{
    std::string_view view = a();
    std::cout << view << std::endl;
    return 0;
}