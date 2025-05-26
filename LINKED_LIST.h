#ifndef LINKED_LIST
#define LINKED_LIST

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#define MAX_SYMBOLS_IN_NUM 20

enum check_number { NUM_IS_GOOD = 0, NUM_IS_BAD = -1 };

struct linked_list
{
    int data;
    struct linked_list* next_node;
};
typedef struct linked_list node;    // структура, содаржащая узел списка

// Проверка на правильность ввода значений
int IsTrueNumber(char* number);

// Вывод всего списка
void PrintList(node* head);

// Функция поиска одинаковых элементов списка
void FindSameNodes(node* head);

// Созданеие списка с заданным количеством элементов и вводимыми значениями элементов
node* CreateList(node* head, int num_of_nodes);

// Получение количества элементов списка
int GetNumOfNodes(node* head);

// Сортировка списка (перенос всех отрицательных значений в начало списка)
int SortAllNegatives(node* head);

// Удаление всего списка
node* DeleteList(node* head);

// Вставка элемента по номеру
node* InsertToPos(node* head, int pos_to_insert, int data_to_insert);

// Удаление элемента по номеру
node* DeleteInPos(node* head, int pos_to_delete_from);

// Вывод данных об элементе
void ReadDataFromNode(node* head, int needed_pos);

#endif //LINKED_LIST
