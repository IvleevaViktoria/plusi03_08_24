#include <stdio.h>
#include <fstream>
#include <vector>
#include <iomanip>

#define MAX_MANAGERS 100
#define MAX_NAME_LENGTH 100

struct Manager {
    int id;
    char name[MAX_NAME_LENGTH];
    char city[MAX_NAME_LENGTH];
    float salary;
};

struct Trade {
    Manager list[MAX_MANAGERS];
    int count = 0; // Начинаем с нуля
};

void add_manager(Trade *trade, const Manager &manager) {
    if (trade->count < MAX_MANAGERS) {
        trade->list[trade->count++] = manager; // Добавляем менеджера в список
    }
}

void read_managers(Trade *trade, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Не удалось открыть файл!\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Manager m;
        char salary[20];

        sscanf(line, "%d;%[^;];%[^;];%s", &m.id, m.name, m.city, salary);
        m.salary = atof(salary);
        add_manager(trade, m);
    }
    fclose(file);
}

void print_kovrov_managers(const Trade &trade) {
    printf("Ковровские менеджеры:\n");
    for (int i = 0; i < trade.count; i++) {
        if (strcmp(trade.list[i].city, "КОВРОВ") == 0) {
            printf("%d %s %s %.2f", trade.list[i].id, trade.list[i].name, trade.list[i].city, trade.list[i].salary);
        }
    }
}

int main() {
    Trade trade;
    read_managers(&trade, "manager.txt");
    print_kovrov_managers(trade);
    return 0; // Завершение программы
}
