#include <iostream>
#include <locale>
#include <codecvt>
#include <io.h>
#include <fcntl.h>

int main() {
    std::locale::global(std::locale("en_US.UTF-8"));
    _setmode(_fileno(stdout), _O_U8TEXT); 

    std::wcout << L"Hello, тест!\n";
    std::system("pause");
    return 0;
}