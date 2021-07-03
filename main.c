#include "header.h"
void main()
{
	Tables** arr;
	Kitchen k;
	FILE* instr, * manot, * out;
	int temp,numoftables,i,tablecount=0,*ptablecount=&tablecount, tablenumber, quantity;
	char productname[51];
	instr = fopen("Instructions.txt", "r");//open the files
	if (instr == NULL)
		exit(1);
	manot = fopen("Manot.txt", "r");
	if (manot == NULL)
		exit(1);
	out = fopen("Output.txt", "w");
	if (out == NULL)
		exit(1);
	fscanf(instr, "%d", &numoftables);//scan from 'intr' file the number of tables
	arr = (Tables*)malloc(sizeof(Tables) * numoftables);//allocte memory for the array of tables
	if (arr == NULL)
		exit(1);
	for (i = 0; i < numoftables; i++)//intial all the tables lists
		intialt(&arr[i]);
	intialk(&k);//intial kitchen
	while (fscanf(instr, "%d", &temp) != EOF)//scan the wanted number of function
	{
		switch (temp)//scan and call the function by the scaned value
		{
		case 1:
			CreateProducts(&k,manot,out);
			break;
		case 2:
			fscanf(instr, "%s%d", productname, &quantity);
			AddItems(productname, quantity,&k,out);
			break;
		case 3:
			fscanf(instr, "%d%s%d",&tablenumber, productname, &quantity);
			OrderItem(tablenumber, productname, quantity,&k,arr,out, numoftables, ptablecount);
			break;
		case 4:
			fscanf(instr, "%d%s%d", &tablenumber, productname, &quantity);
		    RemoveItem(tablenumber, productname, quantity, &k, arr, out, numoftables);
			break;
		case 5:
			fscanf(instr, "%d", &tablenumber);
			tablecount=RemoveTable(tablenumber, &k, arr, out, tablecount);
			break;
		default:
			break;
		}
	}
	free(arr);//free the array
	fclose(manot);//close the files
	fclose(out);
	fclose(instr);
	return;
}