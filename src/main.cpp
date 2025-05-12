#include <iostream>
#include <locale>
#include <codecvt>
#include <io.h>
#include <fcntl.h>


int main() {
    std::setlocale(LC_ALL, "en_US.UTF-8");
    std::wcout.imbue(std::locale("en_US.UTF-8"));

    return 0;
}
