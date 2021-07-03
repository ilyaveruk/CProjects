#include "header.h"

void intialt(Tables* t)
/*This function intialze the "Tables" list*/
{
	t->head = NULL;
	t->tail = NULL;
	t->bill = 0;
}
void intialk(Kitchen* k)
/*This function intialze the "kitchen" list*/
{
	k->head = NULL;
	k->tail = NULL;
}
void CreateProducts(Kitchen* k,FILE *manot, FILE* out)
/*This function create the list of the products in the kitchen using file 'manot', the function also allocet memory for the name of the product*/
{
	int i=0;
	char temp[51];
	Dishes* temp1,*temp2;
	temp1 = (Dishes*)malloc(sizeof(Dishes));
	if(temp1==NULL)
	{
		fprintf(out, "Not enogh memory\n");
		exit(1);
	}
	temp2 = temp1;
	while (fscanf(manot, "%s%d%d", temp, &temp1->quantity, &temp1->price) != EOF)
	{
		temp1->name = (char*)malloc(sizeof(char)*(strlen(temp) + 1));
		if (temp1->name == NULL)
		{
			fprintf(out, "Not enogh memory\n");
			exit(1);
		}
		strcpy(temp1->name, temp);
		temp1->orders = 0;
		i++;
		if(i==1)
			k->head = temp1;
		temp1->next = (Dishes*)malloc(sizeof(Dishes));
		if (temp1->next == NULL)
		{
			fprintf(out, "Not enogh memory\n");
			exit(1);
		}
		temp2 = temp1;
		temp1 = temp1->next;
	}
	temp2->next = NULL;
	k->tail = temp2;
	free(temp1);
    fprintf(out,"The kitchen was created\n");

}
void AddItems(char* productname, int quantity, Kitchen* k, FILE* out)
{
	Dishes* temp;
	if (quantity < 0)
		fprintf(out, "The number of products to add have to be positive number\n");
	else 
	{
		temp = k->head;
		while (strcmp(productname, temp->name) != 0)
			temp = temp->next;
		if (temp == NULL)
			fprintf(out, "This product doesn't exist\n");
		else
		{
			temp->quantity = temp->quantity + quantity;
			fprintf(out, "%d %s were added to the kitchen\n", quantity, temp->name);
		}

	}
}
void OrderItem(int tablenumber, char* productname, int quantity, Kitchen* k, Tables* arr[],FILE* out,int numoftables,int* tablecount)
/*This function order to the table in 'tablenumber' the wanted product, if this product not ordered yet to this table this function
allocet new memory for the node in the list of the dishes in the table, and print to file'out' massage for how much of this product is added to the table,
if there is any problem with the data(table number, quantity...) the function print to the file 'out' and exit the function*/
{
	int i;
	Dishes* tempk;
	DishesInTable* tempd, *tempd1;
	Tables* templist;
	templist = &arr[tablenumber];
	tempk = k->head;
	tempd1 = &arr[tablenumber]->head;
	if (numoftables < tablenumber)
		fprintf(out, "This table number is not exist\n");
	else if (quantity < 0)
		fprintf(out, "The number of products to add have to be positive number\n");
	else {
		while (strcmp(productname, tempk->name) != 0)
		{
			tempk = tempk->next;
			if (tempk == NULL)
			{
				fprintf(out, "This product doesn't exist\n");
				return;
			}
		}
	    if (quantity > tempk->quantity)
			fprintf(out,"There is not enough quantity from this product\n");
		else
		{
			templist->bill = templist->bill + ((tempk->price) * quantity);
			tempk->quantity = tempk->quantity - quantity;
			tempk->orders = tempk->orders + quantity;
			if (templist->head == NULL)
			{
				tempd = (DishesInTable*)malloc(sizeof(DishesInTable));
				if (tempd == NULL)
					exit(1);
				tempd->next = NULL;
				tempd->productname = (char*)malloc(sizeof(char) * (strlen(productname) + 1));
				if (tempd->productname == NULL)
					exit(1);
				strcpy(tempd->productname, productname);
				tempd->quantity = quantity;
				templist->head = tempd;
				templist->tail = tempd;
				*tablecount=*tablecount+1;
			}
			else {
				while (strcmp(tempd1->productname, productname) != 0)
					tempd1 = tempd1->next;
				if (tempd1 != NULL)
				{
					tempd1->quantity = tempd1->quantity + quantity;
				}
				else {
					tempd = (DishesInTable*)malloc(sizeof(DishesInTable));
					if (tempd == NULL)
						exit(1);
					tempd->next = NULL;
					tempd->prev = tempd1->prev;
					tempd->productname = (char*)malloc(sizeof(char) * (strlen(productname) + 1));
					if (tempd->productname == NULL)
						exit(1);
					strcpy(tempd->productname, productname);
					tempd->quantity = tempd->quantity + quantity;
					tempd1 = tempd;
				}
			}
			fprintf(out, "%d %s were added to the table number %d\n", quantity, productname, tablenumber);
		}
	}
}
void RemoveItem(int tablenumber, char* productname, int quantity, Kitchen* k, Tables* arr[], FILE* out, int numoftables)
/*This function remove the wanted quantity from the wanted dish and lower the bill for the table,
if there is any problem with the data(table number, quantity...) the function print to the file 'out' and exit the function*/
{
	int i;
	DishesInTable* tempd;
	Dishes* tempk;
	Tables* templist;
	templist = &arr[tablenumber];
	tempk = k->head;
	tempd = &arr[tablenumber]->head;
	if (numoftables < tablenumber)
		fprintf(out, "This table number is not exist\n");
	else if(tempd==NULL)
		fprintf(out, "This product doesn't exist\n");
	else {
		while (strcmp(productname, tempk->name) != 0)
			tempk = tempk->next;
		while (strcmp(productname, tempd->productname) != 0)
		{
			tempd = tempd->next;
			if (tempd == NULL)
			{
				fprintf(out, "This product doesn't exist\n");
				return;
			}
		}
		if (quantity > tempd->quantity)
			fprintf(out, "In the table there is less quantity then you want to remove\n");
		else {
			tempd->quantity = tempd->quantity - quantity;
			templist->bill = templist->bill - (quantity * tempk->price);
			fprintf(out, "%d %s was returned to the kitchen from table number %d\n", quantity, productname, tablenumber);
		}
	}
}
int RemoveTable(int tablenumber, Kitchen* k, Tables* arr[], FILE* out, int tablecount)
/*This function remove the table in tablenumber and print to the file 'out' how much dishes the table order and print the bill return the tablecount
if the tablecount is 0 the function "close" the resturant and print the most popular dish*/
{
	DishesInTable* tempd,*tempd1;
	Dishes* tempk;
	Tables* templist;
	templist = &arr[tablenumber];
	int maxorders = 0, index = 0, i = 0;
	char productnametemp[51];
	tempk = k->head;
	tempd = &arr[tablenumber]->head;
	if (tempd == NULL)
	{
		fprintf(out, "The table namber %d is not ordered yet\n",tablenumber);
		return (tablecount);
	}
	while (tempd != NULL)
	{
		fprintf(out, "%d %s.", tempd->quantity, tempd->productname);
		tempd = tempd->next;
	}
	fprintf(out, "%d nis please\n", templist->bill);
	tempd = arr[tablenumber]->head;
	while (tempd != NULL)
	{
		tempd1 = tempd->next;
		free(tempd->productname);
		free(tempd);
		tempd = tempd1;
	}
	tablecount--;
	if (tablecount == 0)
	{
		while (tempk != NULL)
		{
			if (tempk->orders > maxorders)
			{
				maxorders = tempk->orders;
				strcpy(productnametemp, tempk->name);
			}
			tempk = tempk->next;
		}
		fprintf(out, "The most popular dish today is %s! (was ordered %d times)\n", productnametemp, maxorders);
	}
	return (tablecount);
}