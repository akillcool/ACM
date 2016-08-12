////1325: 算法2 - 3~2 - 6：Big Bang Example

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef int SizeType;

#ifdef DEBUG
#define debug printf
// for memory leak detect.
typedef struct MemBlock {
	void* next;
	long id;
	long size;
}MemBlock;

MemBlock gMallocFake = { 0, 0 };

long gIdCounter = 0;
long gMallocCounter = 0;

void* MallocWrapper(unsigned size) {
	char* cp = NULL;
	MemBlock* p = (MemBlock*)malloc(size + sizeof(MemBlock));
	assert(p);

	++gMallocCounter;
	p->id = ++gIdCounter;
	p->size = size;
	p->next = gMallocFake.next;
	gMallocFake.next = p;

	cp = sizeof(MemBlock) + (char*)p;
	debug("Malloc %d bytes at %p, id: %ld, counter: %ld\n", size, cp, p->id, gMallocCounter);
	return cp;
}

void FreeWrapper(void* mem) {
	MemBlock* p = gMallocFake.next;
	MemBlock* prev = &gMallocFake;
	while (p) {
		if (mem == sizeof(MemBlock) + (char*)p) {
			debug("Free %ld bytes at %p, id: %ld, counter: %ld\n", p->size, mem, p->id, gMallocCounter);
			--gMallocCounter;
			prev->next = p->next;
			free(p);
			return;
		}
		prev = p;
		p = p->next;
	}
	debug("Untracked block %p\n", mem);
}

char* Strdup(char* str) {
	int len = strlen(str) + 1;
	char* dst = (char*)MallocWrapper(len * sizeof(char));
	strcpy(dst, str);
	return dst;
}

#define malloc MallocWrapper
#define free   FreeWrapper
#define strdup Strdup
#else // DEBUG
void nop(char* fmt, ...) {}
#define debug nop
#endif // DEBUG

// begin ItemType:
typedef char* ItemType;

void ItemPrint(ItemType item) {
	printf("%s ", item);
}

int ItemMatch(ItemType a, ItemType b) {
	return !strcmp(a, b);
}

void ItemDestroy(ItemType item) {
	debug("destroy %p %s\n", item, item);
	free(item);
}
// end ItemType

typedef struct ArrayListSt {
	ItemType* data;
	SizeType  size;
	SizeType  capacity;
}ArrayList;

void ArrayListInfo(ArrayList* list) {
	printf("list: %p, size: %d, capacity: %d\n", list, list->size, list->capacity);
}

ArrayList* ArrayListCreate(int hint) {
	ArrayList* list = (ArrayList*)malloc(sizeof(ArrayList));
	assert(list);
	list->size = 0;

	int capacity = 16;
	while (capacity < hint) capacity *= 2;
	list->capacity = capacity;

	list->data = (ItemType*)malloc(capacity * sizeof(ItemType));
	assert(list->data);

	return list;
}

#define ArrayListForeach(list, visitor) do { \
    int i; \
    for(i = 0; i < list->size; ++i) { \
        visitor(list->data[i]); \
    } \
}while(0)

void ArrayListDestroy(ArrayList* list) {
	ArrayListForeach(list, ItemDestroy);
	free(list->data);
	free(list);
}

void ArrayListInsert(ArrayList* list, SizeType num, ItemType val) {
	int idx = num - 1;
	assert(0 <= idx && idx <= list->size);

	debug(">insert %d %s\n", num, val);
	if (idx < list->size) {
		int i;
		for (i = list->size - 1; i >= idx; --i) {
			list->data[i + 1] = list->data[i];
		}
	}

	list->data[idx] = val;
	list->size++;
	// ArrayListForeach(list, ItemPrint); printf("\n\n");
}

void ArrayListDelete(ArrayList* list, ItemType val) {
	int i, target = -1;

	debug(">delete %s\n", val);
	for (i = 0; i < list->size; ++i) {
		if (ItemMatch(list->data[i], val)) {
			target = i;
			ItemDestroy(list->data[i]);
			break;
		}
	}

	if (target < 0) return;

	for (i = target + 1; i < list->size; ++i) {
		list->data[i - 1] = list->data[i];
	}
	list->size--;
	// ArrayListForeach(list, ItemPrint); printf("\n\n");
}

int ArrayListSearch(ArrayList* list, ItemType val) {
	int i;

	debug(">search %s\n", val);
	for (i = 0; i < list->size; ++i) {
		if (ItemMatch(list->data[i], val)) return i + 1;
	}
	return 0;
}

int main()
{
	char buffer[32]; // 每个名字不超过30个字符。

	ArrayList *list = ArrayListCreate(10);
	assert(list);

	while (scanf("%s", buffer) == 1) {
		if (!strcmp(buffer, "insert")) {
			int num = 0;
			scanf("%d%s", &num, buffer);
			ArrayListInsert(list, num, strdup(buffer));
		}
		else if (!strcmp(buffer, "delete")) {
			scanf("%s", buffer);
			ArrayListDelete(list, buffer);
		}
		else if (!strcmp(buffer, "show")) {
			ArrayListForeach(list, ItemPrint);
			printf("\n");
		}
		else if (!strcmp(buffer, "search")) {
			scanf("%s", buffer);
			int num = ArrayListSearch(list, buffer);
			printf("%d\n", num);
		}
		else {
			// unknow.
		}
	}

	// ArrayListForeach(list, ItemPrint); printf("\n");
	ArrayListDestroy(list);

	return 0;
}
