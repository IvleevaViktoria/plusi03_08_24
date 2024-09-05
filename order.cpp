#include <stdio.h>   // Для работы с функциями ввода-вывода
#include <stdlib.h>  // Для функций преобразования
#include <string.h>  // Для работы со строками

struct Order {
    int order_id;
    int manager_id;
    int client_id;
    char order_date[11]; // Дата формата "YYYY-MM-DD"
    float amount;
};

int compareOrders(const void *a, const void *b) {
    float amountA = ((Order*)a)->amount;
    float amountB = ((Order*)b)->amount;
    return (amountA < amountB) - (amountA > amountB); // Сравниваем заказы по сумме
}

int main() {
    FILE *input_file = fopen("order.txt", "r");
    if (!input_file) {
        printf("Не удалось открыть файл order.txt");
        return 1; // 1 - ошибка
    }

    Order orders[100]; // Предполагая, что максимум 100 заказов
    int count = 0;
    char line[256];

    // Считываем данные из файла
    while (fgets(line, sizeof(line), input_file) && count < 100) {
        Order order;
        char amount[20];

        char *token = strtok(line, ";");
        order.order_id = atoi(token);
        
        token = strtok(NULL, ";");
        order.manager_id = atoi(token);
        
        token = strtok(NULL, ";");
        order.client_id = atoi(token);
        
        token = strtok(NULL, ";");
        strcpy(order.order_date, token);
        
        token = strtok(NULL, "\n");
        order.amount = atof(token);
        
        orders[count++] = order;
    }
    fclose(input_file);

    // Сортируем заказы
    qsort(orders, count, sizeof(Order), compareOrders);

    FILE *output_file = fopen("orders_sorted.txt", "w");
    if (!output_file) {
        printf("Не удалось открыть файл orders_sorted.txt");
        return 1;
    }

    // Записываем отсортированные заказы в файл
    fprintf(output_file, "order_id;manager_id;client_id;order_date;amount");
    for (int i = 0; i < count; i++) {
        fprintf(output_file, "%d;%d;%d;%s;%.2f", orders[i].order_id, orders[i].manager_id, orders[i].client_id, orders[i].order_date, orders[i].amount);
    }
    fclose(output_file);

    printf("Обработка заказов завершена");
    return 0; // 0 - успешно
}
