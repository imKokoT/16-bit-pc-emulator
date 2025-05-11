#include <iostream>
#include <locale>
#include <codecvt>
#include <io.h>
#include <fcntl.h>


int main() {
    std::setlocale(LC_ALL, "en_US.UTF-8");
    std::wcout.imbue(std::locale("en_US.UTF-8"));

    std::wcout << L"Hello, тест españel!\n";
    wprintf(L"Hello, тест españel!\n");

    std::cout << "Hello, тест españel!\n";
    printf("Hello, тест españel!\n");
    return 0;
}
