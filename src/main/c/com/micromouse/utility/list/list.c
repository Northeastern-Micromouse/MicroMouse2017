// TODO: Need add push and pop functionality for queue operations.
#include "list.h"

List* InitializeList(Cell *data) {
	// Create the List struct.
	List *new_list;

	// Request the memory from the heap.
	new_list = (List *)malloc(sizeof(List));

	// Check if the request was successful
	if (new_list == 0) {
		printf("Error creating the list node, out of memory\n");
		return NULL;
	}

	// Initialize the values
	new_list->prev_ = NULL;
	new_list->next_ = NULL;
	new_list->data_ = data;

	return new_list;
}

void ListDestructor(List** list) {
	// Check if you are at the end of the list.
	if (list == NULL) {
		return;
	}

	struct List* current = *list;
  struct List* next;
  while (current != NULL) {
    next = current->next_;
    // Frees the memory for the cell.
    CellDestructor(current->data_);
    // Free the memory for this node.
    free(current);
    // Go to next node.
    current = next;
  }
  current = NULL;
}

void PrintList(List* list) {
  if (list == NULL) {
    printf("List is empty\n");
  }
  List* head = list;
  while (head != NULL) {
    PrintCell(head->data_);
    head = head->next_;
  }
}

Cell* Front(List **list) {
	// TODO: Implement
	if (list == NULL) {
		printf("Invalid argument in Front");
		return NULL;
	}
	if (*list == NULL) {
		printf("List is null in Front");
		return NULL;
	}
	List *result = *list;
	*list = result->next_;
	result->prev_ = NULL;

	return result->data_;
}

Cell* back(List** list) {
	if (list == NULL) {
    printf("Invalid argument in back\n");
    return NULL;
  }
  if (*list == NULL) {
    return NULL;
  }
  List* iter = *list;
  while (iter->next_ != NULL) {
    iter = iter->next_;
  }
  iter->prev_->next_ = NULL;
	return iter->data_;
}

void PushBack(Cell* data, List* list) {
	if (list == NULL) {
		printf("Cannot PushBack onto an empty List. \n");
		return;
	}
	if (list->next_ == NULL) {
		list->next_ = InitializeList(data);
		list->next_->prev_ = list;
		return;
	}
	List* head = list->next_;
	while (head->next_ != NULL) {
		head = head->next_;
	}
	head->next_ = InitializeList(data);
	head->next_->prev_ = head;
}

void Append(Cell* data, List** list) {
	if ((*list) == NULL) {
		(*list) = InitializeList(data);
		return;
	}
	if ((*list)->prev_ == NULL) {
		(*list)->prev_ = InitializeList(data);
		(*list)->prev_->next_ = (*list);
		(*list) = (*list)->prev_;
		return;
	}

	List* head = (*list)->prev_;
	while (head->prev_ != NULL) {
		head = head->prev_;
	}
	head->prev_ = InitializeList(data);
	head->prev_->next_ = head;
	head = head->prev_;
}

Cell* get(int index, List* list) {
	// TODO: Implement
	return NULL;
}

bool in(Cell* data, List* list) {
	// TODO: Implement
	return false;
}

int length(List* list) {
	if (list == NULL) {
		return 0;
	}
	int count = 1;
	List* head = list;
	while (head->next_ != NULL) {
		count++;
		head = head->next_;
	}
	return count;
}

bool empty(List* list) {
	if (list == NULL) {
    return true;
  }
	return false;
}

void clear(List** list) {
	// TODO: Implement
}

void erase(Cell* data, List** list) {
	// TODO: Implement
}

List* reverse(List** list) {
	// TODO: Implement
	return NULL;
}

void resetList(List** list) {
	if ((*list) == NULL) {
		return;
	}
	if ((*list)->prev_ == NULL) {
		return;
	}
	List* head = (*list);
	while (head->prev_ != NULL) {
		head = head->prev_;
	}
	(*list) = head;
}
