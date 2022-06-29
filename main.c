#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

struct emp {
	char name[50];
	float salary;
	int age;
};

struct emp e;

long int size = sizeof(e);

FILE *fp, *ft;

void addrecord()
{
	system("cls");
	fseek(fp, 0, SEEK_END);
	char another = 'y';

	while (another == 'y') {
		printf("\nEnter Name : ");
		scanf("%s", e.name);

		printf("\nEnter Age : ");
		scanf("%d", &e.age);

		printf("\nEnter Salary : ");
		scanf("%f", &e.salary);

		fwrite(&e, size, 1, fp);

		printf("\nWant to add another record (Y/N) : ");
		fflush(stdin);

		scanf("%c", &another);
	}
}

void deleterecord()
{
	system("cls");
	char empname[50];
	char another = 'y';

	while (another == 'y') {
		printf("\nEnter employee name to delete : ");
		scanf("%s", empname);

		ft = fopen("temp.txt", "wb");
		rewind(fp);

		while (fread(&e, size, 1, fp) == 1) {
			if (strcmp(e.name, empname) != 0)
				fwrite(&e, size, 1, ft);
		}

		fclose(fp);
		fclose(ft);
		remove("data.txt");
		rename("temp.txt", "data.txt");
		fp = fopen("data.txt", "rb+");

		printf("\nWant to delete another record (Y/N) :");
		fflush(stdin);
		scanf("%c", &another);
	}
}

void displayrecord()
{
	system("cls");

	rewind(fp);

	printf("\n==========================================================");
	printf("\nNAME\t\t\tAGE\t\t\tSALARY", e.name, e.age, e.salary);
	printf("\n==========================================================\n");

	while (fread(&e, size, 1, fp) == 1)
	    printf("\n%s\t\t\t%d\t\t\t%.2f", e.name, e.age, e.salary);

	printf("\n\n\n\t");
	system("pause");
}

void modifyrecord()
{
	system("cls");
	char empname[50];
	char another = 'y';

	while (another == 'y') {
		printf("\nEnter employee name to modify : ");
		scanf("%s", empname);

		rewind(fp);

		while (fread(&e, size, 1, fp) == 1) {
			
			if (strcmp(e.name, empname) == 0) {
				printf("\nEnter new name:");
				scanf("%s", e.name);
				printf("\nEnter new age :");
				scanf("%d", &e.age);
				printf("\nEnter new salary :");
				scanf("%f", &e.salary);

				fseek(fp, -size, SEEK_CUR);
				fwrite(&e, size, 1, fp);
				break;
			}
		}

		printf("\nWant to modify another record (Y/N) :");
		fflush(stdin);
		scanf("%c", &another);
	}
}

int main()
{
	int choice;

	fp = fopen("data.txt", "rb+");

	if (fp == NULL) {
		fp = fopen("data.txt", "wb+");
		if (fp == NULL) {
			printf("\nCannot open file...");
			exit(1);
		}
	}

	while (1) {
		
		system("cls");
		printf("\n1. ADD RECORD\n");
		printf("\n2. DELETE RECORD\n");
		printf("\n3. DISPLAY RECORDS\n");
		printf("\n4. MODIFY RECORD\n");
		printf("\n5. EXIT\n");
		printf("\nENTER YOUR CHOICE...\n");
		fflush(stdin);
		scanf("%d", &choice);

		switch (choice) {
		case 1:

			addrecord();
			break;

		case 2:

			deleterecord();
			break;

		case 3:

			displayrecord();
			break;

		case 4:

			modifyrecord();
			break;

		case 5:
			fclose(fp);
			exit(0);
			break;

		default:
			printf("\nINVALID CHOICE...\n");
		}
	}

	return 0;
}
