#include <iostream>


int main() {
    std::setlocale(LC_ALL, "en_US.UTF-8");
    std::wcout.imbue(std::locale("en_US.UTF-8"));

    printf("test\n");

    char a[256];
    std::cin >> a;

    printf("test %s\n", a);

    return 0;
}
