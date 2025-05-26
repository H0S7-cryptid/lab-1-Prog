#include "LINKED_LIST.h"

int IsTrueNumber(char* number)
{
	const char* special_symbols = "\\|~`!@#$%^&*()_+=?:%;№";
	if (strpbrk(number, special_symbols) != NULL) return NUM_IS_BAD;              // Проверка на наличие в строке специальных символов
	if (number[0] == '\0' || number[0] == '\n' || number[0] == '/') return NUM_IS_BAD;          // Проверка на пустой ввод
	int is_negative = (number[0] == '-') ? 1 : 0;
	size_t start_idx = is_negative ? 1 : 0, len = strlen(number);        // Просчитывание индекса начала числа, вычисление длины без учёта "\0" и "-"
	if (number[len] == '\n') number[len] = '\0';                // Удаление знака \n из конца строки
	if (len == 0 && is_negative == 1) return NUM_IS_BAD;            // Отсечение одиночного '-'
	for (size_t i = start_idx; i < len; i++) if (isalpha(number[i])) return NUM_IS_BAD;      // Проверка на цифры
	return NUM_IS_GOOD;
}

int GetNumOfNodes(node* head)
{
	int num_of_nodes = 0;			// Переменная для записи количества узлов

	if (head == NULL) return 0;

	node* checker = head;			// Временный указатель для "пробежки" по списку
	while (checker != NULL)			// Перебор до конца списка
	{
		checker = checker->next_node;
		num_of_nodes++;
	}
	return num_of_nodes;
}

void PrintList(node* head)
{
	node* ptr = head;

	if (head == NULL)
	{
		printf("Списка не существует\\не создан");
		return;
	}

	while (ptr != NULL)
	{
		const char* form_str = ptr->next_node == NULL ? "%d" : "%d -> ";
		printf(form_str, ptr->data);
		ptr = ptr->next_node;
	}
	printf("\n");
}

node* DeleteList(node* head)
{
	if (head == NULL) return NULL;		// Проверка на существование списка

	for (node* ptr = head; head != NULL; ptr = head)	// Пробежка по всему списку
	{													// Удаление каждого найденного элемента.
		head = head->next_node;
		free(ptr);
	}
	return NULL;
}

void ReadDataFromNode(node* head, int needed_pos)
{
	node* search = head;
	int pos_to_read = 1;

	if (head == NULL || needed_pos > GetNumOfNodes(head) || needed_pos <= 0) return;		// Проверка на наличие списка
																							// Проверка на правильность задание читаемой позиции в списке
	while (pos_to_read < needed_pos)		// "Пробежка" по списку и поиск нужного элемента.
	{
		search = search->next_node;
		pos_to_read++;
	}

	printf("Значение выбранного элемента(номер %d): %d\n", pos_to_read, search->data);
	printf("Адресс выбранного элемента(номер %d): %p\n", pos_to_read, search);
}

node* CreateList(node* head, int num_of_nodes)
{
	char buffer[MAX_SYMBOLS_IN_NUM];
	int number = 0;
	int i = 0;

	if (head != NULL) head = DeleteList(head);

	if (num_of_nodes <= 0) return NULL;

	while (i < num_of_nodes)
	{
		printf("Введите значение: ");
		fgets(buffer, MAX_SYMBOLS_IN_NUM, stdin);
		if (IsTrueNumber(buffer) == NUM_IS_BAD)
		{
			printf("Число введено неверно\n");
			continue;
		}
		number = atoi(buffer);

		node* node_to_insert = (node*)malloc(sizeof(node));
		if (!node_to_insert) exit(1);
		node_to_insert->data = number;
		
		node_to_insert->next_node = head;
		head = node_to_insert;
		i++;
	}
	return head;
}

node* InsertToPos(node* head, int pos_to_insert, int data_to_insert)
{
	node* search_for_insert = head;
	int pos_check = 1;

	node* node_to_insert = (node*)malloc(sizeof(node));		// Создание узла списка
	if (!node_to_insert) exit(1);							// Проверка на выделение памяти	для узла
	node_to_insert->data = data_to_insert;
	node_to_insert->next_node = NULL;

	if (GetNumOfNodes(head) + 1 < pos_to_insert) return head;		// Проверка на правильность списка

	if (head == NULL || pos_to_insert == 1)			// Случай, когда надо вставить элемент в начало списка
	{
		node_to_insert->next_node = head;
		head = node_to_insert;
		return head;
	}

	if (GetNumOfNodes(head) + 1 == pos_to_insert)	// Случай, когда надо вставить элемент в конец списка
	{
		while (search_for_insert->next_node != NULL) search_for_insert = search_for_insert->next_node;
		node_to_insert->next_node = search_for_insert->next_node;
		search_for_insert->next_node = node_to_insert;
		return head;
	}

	while (pos_check < pos_to_insert - 1)			// Случай, когда надо вставить элемент в середину списка
	{
		search_for_insert = search_for_insert->next_node;
		pos_check++;
	}

	node_to_insert->next_node = search_for_insert->next_node;		// Вставка элемента в середину
	search_for_insert->next_node = node_to_insert;
	return  head;
}

node* DeleteInPos(node* head, int pos_to_delete_from)
{
	node* search_for_delete = head;
	node* item = NULL;
	int prev_pos = 1;

	if (head == NULL || GetNumOfNodes(head) < pos_to_delete_from) return head;		// Проверка на правильность списка

	if (pos_to_delete_from == 1)		// Случай, когда удаляется элемент из начала списка
	{
		item = head;
		head = head->next_node;
		free(item);
		return head;
	}

	if (GetNumOfNodes(head) == pos_to_delete_from)		// Случай, когда удаляется элемент из конца списка
	{
		while (search_for_delete->next_node->next_node != NULL) search_for_delete = search_for_delete->next_node;
		item = search_for_delete->next_node;
		search_for_delete->next_node = NULL;
		free(item);
		return head;
	}

	while (prev_pos < pos_to_delete_from - 1)			// Случай, когда удаляется элемент из середины списка
	{
		search_for_delete = search_for_delete->next_node;
		prev_pos++;
	}

	item = search_for_delete->next_node;				// Удаление узла из середины
	search_for_delete->next_node = search_for_delete->next_node->next_node;
	free(item);
	return head;
}

int SortAllNegatives(node* head)
{
	node* total_sort_check = head;
	node* cycle_for_check = head;
	int checked_num = 0;
	int pos = 1, is_negative_in_row = 1;
	int times_sorted = 0;

	while (cycle_for_check != NULL)
	{
		if (pos == is_negative_in_row && cycle_for_check->data < 0)
		{
			pos++;
			if (cycle_for_check->next_node != NULL)
				is_negative_in_row = cycle_for_check->next_node->data < 0 ? is_negative_in_row + 1 : is_negative_in_row;
			else
				break;
			cycle_for_check = cycle_for_check->next_node;
			total_sort_check = total_sort_check->next_node;
			continue;
		}
		else if (pos != is_negative_in_row && cycle_for_check->data < 0)
		{
			checked_num = total_sort_check->data;
			total_sort_check->data = cycle_for_check->data;
			cycle_for_check->data = checked_num;
			total_sort_check = total_sort_check->next_node;
			times_sorted++;
		}
		cycle_for_check = cycle_for_check->next_node;
		pos++;
	}
	if (times_sorted == 0) printf("Перестановки в списке не нужны.\n");
	return times_sorted;
}

void FindSameNodes(node* head)
{
	int exploring_element = 0, explored_pos = 1, found_pos = 2;
	const char* formatstr = NULL;
	node* total_search_ptr = head;
	node* sycle_search_ptr = NULL;

	exploring_element = total_search_ptr->data;

	while (total_search_ptr->next_node != NULL)
	{
		sycle_search_ptr = total_search_ptr;
		while (1)
		{
			if (sycle_search_ptr->next_node == NULL)
			{
				found_pos = 2 + explored_pos;
				break;
			}
			if (exploring_element == sycle_search_ptr->next_node->data)
			{
				formatstr = "Найдена пара равных чисел: %d(%d-ая позиция), %d(%d-ая позиция)\n";
				printf(formatstr, exploring_element, explored_pos, sycle_search_ptr->next_node->data, found_pos);
				found_pos = 2 + explored_pos;
				break;
			}
			found_pos++;
			sycle_search_ptr = sycle_search_ptr->next_node;
		}
		explored_pos++;
		total_search_ptr = total_search_ptr->next_node;
		exploring_element = total_search_ptr->data;
	}
	if (formatstr == NULL) printf("В списке нет пар одинаковых чисел.\n");
	return;
}
