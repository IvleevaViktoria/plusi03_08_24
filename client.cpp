#include <stdio.h>
#include <string.h>

struct Client {
    int id;
    char name[100];
    char city[100];
    int rating;
    int manager_id;
};

// Функция инициализации клиента
void initClient(Client* c, int id, const char* name, const char* city, int rating, int manager_id) {
    c->id = id;
    strncpy(c->name, name, sizeof(c->name) - 1);
    c->name[sizeof(c->name) - 1] = '\0';
    strncpy(c->city, city, sizeof(c->city) - 1);
    c->city[sizeof(c->city) - 1] = '\0';
    c->rating = rating;
    c->manager_id = manager_id;
}

// Функция для печати информации о клиенте
void printClient(const Client* c) {
    printf("ID: %d, Имя: %s, Город: %s, Рейтинг: %d, ID Менеджера: %d", 
           c->id, c->name, c->city, c->rating, c->manager_id);
}

int main() {
    Client client;
    initClient(&client, 1, "Бектенова Диана", "Москва", 5, 10);
    printClient(&client);
    
    return 0; // Завершение программы
}
