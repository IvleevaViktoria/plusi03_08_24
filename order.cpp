#include <stdio.h>   // Для работы с функциями ввода-вывода
#include <fstream>   // Для работы с файлами
#include <vector>    // Для работы с динамическими массивами
#include <algorithm> // Для сортировки
#include <sstream>   // Для обработки строк
#include <iomanip>   // Для форматирования вывода

struct Order {
    int order_id;
    int manager_id;
    int client_id;
    char order_date[11]; // Дата формата "YYYY-MM-DD"
    float amount;
};

bool compareOrders(const Order &a, const Order &b) {
    return a.amount > b.amount; // Сравниваем заказы по сумме: больше - выше
}

int main() {
    FILE *input_file = fopen("order.txt", "r");
    if (!input_file) {
        printf("Не удалось открыть файл order.txt");
        return 1; // 1 - ошибка
    }

    std::vector<Order> orders;
    char line[256];

    // Считываем данные из файла
    while (fgets(line, sizeof(line), input_file)) {
        std::istringstream ss(line);
        Order order;
        char amount[20];

        ss.getline(amount, sizeof(amount), ';'); order.order_id = atoi(amount);
        ss.getline(amount, sizeof(amount), ';'); order.manager_id = atoi(amount);
        ss.getline(amount, sizeof(amount), ';'); order.client_id = atoi(amount);
        ss.getline(order.order_date, sizeof(order.order_date), ';');
        ss.getline(amount, sizeof(amount)); order.amount = atof(amount);
        
        orders.push_back(order);
    }
    fclose(input_file);

    // Сортируем заказы
    std::sort(orders.begin(), orders.end(), compareOrders);

    FILE *output_file = fopen("orders_sorted.txt", "w");
    if (!output_file) {
        printf("Не удалось открыть файл orders_sorted.txt");
        return 1;
    }

    // Записываем отсортированные заказы в файл
    fprintf(output_file, "order_id;manager_id;client_id;order_date;amount");
    for (const auto &order : orders) {
        fprintf(output_file, "%d;%d;%d;%s;%.2f", order.order_id, order.manager_id, order.client_id, order.order_date, order.amount);
    }
    fclose(output_file);

    printf("Обработка заказов завершена");
    return 0; // 0 - успешно
}
