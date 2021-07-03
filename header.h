#ifndef header
#define header


#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Item1 {
	struct Dishes* next;
	char* name;
	int price;
	int quantity;
	int orders;
   
}Dishes;
typedef struct Listmanger1 {
	struct Dishes* head;
	struct Dishes* tail;
}Kitchen;

typedef struct Item2 {
	struct DishesInTable* next;
	struct DishesInTable* prev;
	char* productname;
	int quantity;
}DishesInTable;
typedef struct Listmanger2 {
	struct DishesInTable* head;
	struct DishesInTable* tail;
	int tablenumber;
	int bill;
}Tables;


void intialt(Tables* t);
void intialk(Kitchen* k);
void CreateProducts(Kitchen* k, FILE* manot, FILE* out);
void AddItems(char* productname, int quantity, Kitchen* k, FILE* out);
void OrderItem(int tablenumber, char* productname, int quantity, Kitchen* k, Tables* arr[], FILE* out,int numoftables,int* tablecount);
void RemoveItem(int tablenumber, char* productname, int quantity, Kitchen* k, Tables* arr[], FILE* out, int numoftables);
int RemoveTable(int tablenumber, Kitchen* k, Tables* arr[], FILE* out,int tablecount);

#endif