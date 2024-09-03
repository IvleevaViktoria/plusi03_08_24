#include <stdio.h>

int main() {
    int manager_id = 1;
    const char* name = "Менеджер Иванов";
    const char* city = "Москва";
    float comm = 1500.50;

    printf("%d. %s из %s, Комиссия: %.2f", manager_id, name, city, comm);

    return 0; // Завершение программы
}
