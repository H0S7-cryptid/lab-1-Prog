#include "LINKED_LIST.h"

node* HeadTracker(node* head)
{
	char buffer[MAX_SYMBOLS_IN_NUM];
	char buf_to_choose[MAX_SYMBOLS_IN_NUM];

	int item;

	fgets(buf_to_choose, MAX_SYMBOLS_IN_NUM, stdin);
	item = atoi(buf_to_choose);

	switch (item)
	{
	case 1:
	{
		int num_of_nodes;
		printf("Введите число элементов: ");
		fgets(buffer, MAX_SYMBOLS_IN_NUM, stdin);
		if (IsTrueNumber(buffer) == NUM_IS_GOOD)
		{
			num_of_nodes = atoi(buffer);
			head = CreateList(head, num_of_nodes);
		}
		else break;

		printf("Количество узлов списка: %d\n", GetNumOfNodes(head));
		break;
	}
	case 12:
	{
		PrintList(head);
		break;
	}
	case 2:
	{
		int num_to_insert;
		int pos_to_insert;

		printf("Введите элемент для вставки: ");
		fgets(buffer, MAX_SYMBOLS_IN_NUM, stdin);
		if (IsTrueNumber(buffer) == NUM_IS_GOOD) num_to_insert = atoi(buffer);
		else break;
		
		printf("Введите позицию (номер) элемента для вставки: ");
		fgets(buffer, MAX_SYMBOLS_IN_NUM, stdin);
		if (IsTrueNumber(buffer) == NUM_IS_GOOD) pos_to_insert = atoi(buffer);
		else break;

		head = InsertToPos(head, pos_to_insert, num_to_insert);

		printf("Количество узлов списка: %d\n", GetNumOfNodes(head));
		break;
	}
	case 3:
	{
		int pos_to_delete = 0;

		printf("Введите позицию (номер) элемента для удаления: ");
		fgets(buffer, MAX_SYMBOLS_IN_NUM, stdin);
		if (IsTrueNumber(buffer) == NUM_IS_GOOD) pos_to_delete = atoi(buffer);
		else break;

		head = DeleteInPos(head, pos_to_delete);
		printf("Количество узлов списка: %d\n", GetNumOfNodes(head));
		break;
	}
	case 4:
	{
		int pos_to_check = 0;

		printf("Введите номер нужного элемента: ");
		fgets(buffer, MAX_SYMBOLS_IN_NUM, stdin);
		if (IsTrueNumber(buffer) == NUM_IS_GOOD) pos_to_check = atoi(buffer);
		else break;

		ReadDataFromNode(head, pos_to_check);

		break;
	}
	case 5:
	{
		DeleteList(head);
		break;
	}
	default: printf("Неверный ввод\n");
	}

	return head;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	node* head = NULL;

	char buffer_for_item[MAX_SYMBOLS_IN_NUM];
	int item;

	printf("Работа с односвязным списком\n");
	printf("Выберете действие:\n1. Создать список (Вывод списка - 12)\n2. Создать элемент списка (вставить его в список)\n3. Удалить элемент списка\n4. Вывести данные об элементе\n5. Удалить список\n\n");
	while (1)
	{
		head = HeadTracker(head);
		printf("Закончить работу со списком? (1 - Нет, 2\\Enter - Да)\n");
		fgets(buffer_for_item, MAX_SYMBOLS_IN_NUM, stdin);
		item = atoi(buffer_for_item);
		if (item == 1 && head != NULL) continue;
		else break;
	}

	if (head != NULL)
	{
		printf("\nВведённый список: ");
		PrintList(head);
		FindSameNodes(head);
		printf("Количество перестановок итогового списка: %d\n", SortAllNegatives(head));
		printf("Отсортированный список: ");
		PrintList(head);
	}
	else printf("Списка не существует\n");

	return 0;
}
