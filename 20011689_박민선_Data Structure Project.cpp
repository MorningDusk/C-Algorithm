#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//Visitor node structure
typedef struct visitor {
	char name[20];	//visitor name
	int code;	//visitor's code given at random
	int date;	//date visited
	int phone_num;	//visitor's phone number
	int city;	//city they live in
	char pet[20];	//pet name
	float weight;	//pet's weight
	int flag;	//special case animal check
	struct visitor *prev;		//all node pointer
	struct visitor *next;		//next node pointer
	struct visitor *hash_next;	//hashtable next node pointer
}V;

//Visitor list structure
typedef struct list {
	V *Header, *Tail;	//doubly linked list so head and tail
	int length;		//number of visitors
}List;

typedef struct HashTable {	
	char name[10];		//name of city
	V *hash_header;		//visitor node structure pointer
}hashTable;

//Introduction menu
void introduction() {
	printf("\n------------------------------------------------------------------------------\n");
	printf("\t\tGreetings, welcome to Seoul National Vet in Korea\n");
	printf("\tBefore you make an entry, you must enter your personal information.\n");
	printf("\t\t\tPlease enter your information\n");
	printf("\n------------------------------------------------------------------------------\n\n");
}

//Select whether you are a visitor or administrator
void modeMenu() {
	printf("\n--------Select MODE---------\n");
	printf("\t1. Visitor\n");
	printf("\t2. Manager\n");
	printf("----------------------------\n\n");
}

//Selection menu for visitors
void visitorMenu() {
	printf("\n---------------Visitor Menu---------------\n");
	printf("\t1. Enter my information\n");
	printf("\t2. Modify my information\n");
	printf("------------------------------------------\n\n");
}

//Selection menu for administrator
void managerMenu() {
	printf("\n----------------------Manager menu-----------------------\n");
	printf("\t0. Log-out\n");
	printf("\t1. Registration of visitors\n");
	printf("\t2. Modify visitor information\n");
	printf("\t3. Delete visitor information\n");
	printf("\t4. View all visitor information\n");
	printf("\t5. Search Visitor Information\n");
	printf("---------------------------------------------------------\n\n");
}

//Selection menu for city residence
void cityMenu(char city[][10]) {
	int i;
	printf("\n\t*********Code of Administrative divisions of Seoul*********\n");
	for (i = 0; i < 7; i++)
		printf("\t\t\t\t%d. %s\n", i, city[i]);
	printf("\t************************************************************\n\n");
}

//Check information before continue
void showInformation(visitor *v, char city[][10]) {
	printf("\n*********************Visitor Information************************\n");
	printf("\tVisitor : %s\n", v->name);
	printf("\tVisitor code : %d\n", v->code);
	printf("\t==>Please remember this code to modify your info.\n");
	printf("\tVisited date : %d\n", v->date);
	printf("\tPhone number : %d\n", v->phone_num);
	printf("\tResidence : %s\n", city[v->city]);
	printf("\tPet name : %s\n", v->pet);
	printf("\tPet weight : %.2f\n", v->weight);
	printf("\tSpecial case animal status: NO\n");
	printf("**************************************************************\n\n");
}

//Outro
void bye() {
	printf("\n\n------------------------------------------------------------------------------------------------\n");
	printf("\t\tThank you for visiting Seoul National Vet\n");
	printf("\t** The information you filled in will be deleted in two weeks!!! **\n");
	printf("\t\t\t\tHave a nice day\n");
	printf("------------------------------------------------------------------------------------------------\n\n");
}

//Initialize visitor information node
void initVisitor(V **visitor) {
	srand((unsigned int)time(NULL));	//random number generator
	(*visitor) = (V*)malloc(sizeof(V));	//visitor node dynamic allocatioon
	(*visitor)->code = (rand() % 100) + 1;	//assign random code
	(*visitor)->date = 0;	//reset date
	(*visitor)->phone_num = 0;	//reset phone number
	(*visitor)->weight = 0.0;	//reset weight
	(*visitor)->flag = 0;	//reset special case animal status
	(*visitor)->prev = NULL;	//set previous pointer to null	
	(*visitor)->next = NULL;	//set next pointer to null
	(*visitor)->hash_next = NULL;	//set hash pointer to null
}

//Initialize list information node
void initList(List **L) {
	(*L) = (List*)malloc(sizeof(List));		//list node dynamic allocation
	(*L)->Header = (V*)malloc(sizeof(V));	//header pointer dynamic allocation
	(*L)->Tail = (V*)malloc(sizeof(V));		//tail pointer dynamic allocation
	(*L)->Header->prev = NULL;		//set previous pointer to null
	(*L)->Tail->next = NULL;		//set next pointer to null
	(*L)->Header->next = (*L)->Tail;		//connect header pointer to tail pointer
	(*L)->Tail->prev = (*L)->Header;		//connect tail pointer to header pointer
	(*L)->length = 0;		//reset number of visitors
}

//Initialize hash table node
void initHashTable(hashTable *h, char city[][10]) {
	int i;
	for (i = 0; i < 7; i++) {		
		h[i].hash_header = (V*)malloc(sizeof(V));		//visitor node on hashtable dynamic allocation
		h[i].hash_header->hash_next = NULL;		//set hashtable next pointer to null
		strcpy(h[i].name, city[i]);		//copy city name to the hashtable
	}
}

//Split structure for merge sort function
void mergePartition(V *header, visitor **list1, visitor **list2, int n) {
	int i;
	visitor *p = header;		//copy header pointer to new pointer
	*list1 = header;		//copy list1 to the beginning of header
	for (i = 0; i < (n / 2) - 1; i++)
		p = p->next;		//move header node to n/2-1
	*list2 = p->next;		//set list2 to moved node of p
	p->next = NULL;		//set next pointer to null or there is no ending
}

//Sort by visited date
visitor *merge1(List *L, visitor **list1, visitor **list2) {
	visitor *sortedHeader, *p, *L1 = *list1, *L2 = *list2;
	//determine header
	if (L1->date <= L2->date) {		
		sortedHeader = L1;
		L1 = L1->next;
		p = sortedHeader;
	}
	else {
		sortedHeader = L2;
		L2 = L2->next;
		p = sortedHeader;
	}
	//sort to ascending order in sorted list
	while ((L1 != NULL) && (L2 != NULL)) {
		if (L1 == L->Tail || L2 == L->Tail)
			break;
		if (L1->date <= L2->date) {
			p->next = L1;
			if (L1->next != L->Tail)
				L1 = L1->next;
			p = p->next;
		}
		else {
			p->next = L2;
			if (L2->next != L->Tail)
				L2 = L2->next;
			p = p->next;
		}
	}
	//insert remaining unaligned nodes into sorted list
	while (L1 != NULL) {
		if (L1 == L->Tail)
			break;		//prevent tail of list
		p->next = L1;
		p = L1;
		L1 = L1->next;
	}
	while (L2 != NULL) {
		if (L2 == L->Tail)
			break;
		p->next = L2;
		p = L2;
		L2 = L2->next;
	}
	return sortedHeader;
}

void mergeSort1(List *L, visitor **header, int n) {
	visitor *L1, *L2, *p = (*header);
	//1 is the minimum number of list
	if (n >= 2) {
		mergePartition(p, &L1, &L2, n);		//split list
		if (n % 2 == 0) {		//number of visitors is even
			mergeSort1(L, &L1, n / 2);
			mergeSort1(L, &L2, n / 2);
		}
		else {		//number of visitors is odd
			mergeSort1(L, &L1, n / 2);
			mergeSort1(L, &L2, n / 2 + 1);
		}
		(*header) = merge1(L, &L1, &L2);		//merge by date
	}
}

//Sort by name
visitor *merge2(List *L, visitor **list1, visitor **list2) {
	visitor *sortedHeader, *p, *L1 = *list1, *L2 = *list2;
	//header determination
	if (strcmp(L1->name, L2->name) == -1) {
		sortedHeader = L1;
		L1 = L1->next;
		p = sortedHeader;
	}
	else {
		sortedHeader = L2;
		L2 = L2->next;
		p = sortedHeader;
	}
	//sort to ascending order in sorted list
	while ((L1 != NULL) && (L2 != NULL)) {
		if (L1 == L->Tail || L2 == L->Tail)
			break;
		if (strcmp(L1->name, L2->name) == 1 || strcmp(L1->name, L2->name) == 0) {
			p->next = L1;
			if (L1->next != L->Tail)
				L1 = L1->next;
			p = p->next;
		}
		else {
			p->next = L2;
			if (L2->next != L->Tail)
				L2 = L2->next;
			p = p->next;
		}
	}
	//insert remaining unaligned nodes into sorted list
	while (L1 != NULL) {
		if (L1 == L->Tail)
			break;		//prevent tail of list
		p->next = L1;
		p = L1;
		L1 = L1->next;
	}
	while (L2 != NULL) {
		if (L2 == L->Tail)
			break;
		p->next = L2;
		p = L2;
		L2 = L2->next;
	}
	return sortedHeader;
}

void mergeSort2(List *L, visitor **header, int n) {
	visitor *L1, *L2, *p = *header;
	//1 is the minimum number of list
	if (n >= 2) {
		mergePartition(p, &L1, &L2, n);		//split list
		if (n % 2 == 0) {		//number of visitors is even
			mergeSort2(L, &L1, n / 2);
			mergeSort2(L, &L2, n / 2);
		}
		else {		//number of visitors is odd
			mergeSort2(L, &L1, n / 2);
			mergeSort2(L, &L2, n / 2 + 1);
		}
		(*header) = merge2(L, &L1, &L2);		//merge by name
	}
}

//Print all visitor information
void printAll(List *L, char city[][10]) {
	int cnt = 1;
	visitor *p = L->Header;
	p = p->next;
	while (p != L->Tail) {
		printf("\ninfo %d", cnt);
		showInformation(p, city);
		cnt++;
		p = p->next;
	}
}

//Print all visitor information by name
void printByName(List *L, char city[][10]) {
	visitor *p = L->Header->next;
	mergeSort2(L, &(L->Header->next), L->length);		//sort by name
	while (p->next!= NULL)
		p = p->next;
	L->Tail->prev = p;
	p->next = L->Tail;
	printAll(L, city);
}

//Print all visitor information by date
void printByDate(List *L, char city[][10]) {
	visitor *p = L->Header->next;
	mergeSort1(L, &(L->Header->next), L->length);		//sort by date
	while (p->next != NULL)
		p = p->next;
	L->Tail->prev = p;
	p->next = L->Tail;
	printAll(L, city);
}

//Print all visitor information by City
void printByCity(hashTable *h, char city[][10]) {
	int i;
	visitor *tmp, *p;
	for (i = 0; i < 7; i++) {
		tmp = h[i].hash_header;
		printf("\n\n%s\n", h[i].name);
		if (tmp->hash_next == NULL) {
			printf("No Visitors!\n\n");
			continue;
		}
		p = tmp->hash_next;		//print information for cities with visitor information
		while (p != NULL) {
			showInformation(p, city);
			p = p->hash_next;
		}
	}
}

//Find visitor information by visitor code
visitor *searchByCode(List *L, int codeN) {
	visitor *p = L->Header;
	//when modifying, compare visitor code with original code
	while (p != L->Tail) {
		if (codeN == p->code)		//if the code name is same as original code
			return p;		//return visitor structure address
		p = p->next;
	}
	p = L->Header;		//set to header pointer if code information is missing
	return p;
}

//Find visitor information by visitor name
void searchByName(List *L, char *searchName, char city[][10]) {
	int cnt = 1;
	visitor *p = L->Header;
	if (p->next == L->Tail) {		//visitor list is empty
		printf("\n\n\tNo Visitors!\n\n");
		return;
	}
	while (p != L->Tail) {		//visitors available
		if (strcmp(p->name, searchName) == 0) {		//found visitor
			printf("info %d", cnt);
			showInformation(p, city);		//print information
			cnt++;
		}
		p = p->next;
	}
	if (cnt == 0)
		printf("\tNo visitors with the name has entered!!\n\n");
}

//Find visitor information by visited date
void searchByDay(List *L, int searchDate, char city[][10]) {
	int cnt = 1;
	visitor *p = L->Header;
	if (p->next == L->Tail) {		//visitor list is empty
		printf("\n\n\tNo Visitors!\n\n");
		return;
	}
	while (p != L->Tail) {		//visitors available
		if (p->date == searchDate) {		//found date
			printf("info %d", cnt);
			showInformation(p, city);		//print information
			cnt++;
		}
		p = p->next;
	}
	if (cnt == 0)
		printf("\tNo visitors with the name has entered!!\n\n");
}

//Find visitor information by city
void searchByCity(hashTable *h, int searchCity, char city[][10]) {
	visitor *tmp = h[searchCity].hash_header, *p;
	if (tmp->hash_next == NULL) {		//visitor list is empty
		printf("\n\n\tNo visitor in %s\n\n", city[searchCity]);
		return;
	}
	p = tmp->hash_next;
	while (p != NULL) {		//visitors available
		showInformation(p, city);		//print information
		p = p->next;
	}
}

//Add visitor information
void addVisitor(List *L, hashTable *h, char city[][10]) {
	int flag = 0, status = 0;
	visitor *tmp = L->Header, *v = (visitor*)malloc(sizeof(visitor));		//visitor node dynamic allocation
	initVisitor(&v);
	while (1) {
		printf("Enter your Name : ");		//visitor name
		scanf("%s", v->name);
		while (1) {
			printf("Please enter today's date : ");		//visited date
			scanf("%d", &(v->date));
			if (v->date < 20220101) {		//date is before 2022
				printf("\n\nEnter date in YYYYMMDD format.\n");
				printf("\tPlease enter date information after January 1st, 2022.\n\n\n");
				continue;
			}
			else
				break;
		}
		printf("Please enter your phone number : ");		//visitor's phone number
		scanf("%d", &(v->phone_num));
		while (1) {
			printf("Which city do you live in?\n");		//visitor's residence
			cityMenu(city);		//present cities of Korea
			printf("City code : ");		//input city code
			scanf("%d", &(v->city));		
			if (v->city < 0 || v->city>7) {		//if city code is out of range
				printf("\n\n\tThe code is out of range!!\n");
				printf("\tCode is a number from 0 to 26.\n");
				printf("\tPlease re-enter the number of region-code.\n\n\n");
				continue;
			}
			else
				break;
		}
		printf("Enter your pet's name : ");		//pet's name
		scanf("%s", v->pet);
		while (1) {
			printf("Please enter your pet's weight in kilograms : ");		//pet's weight
			scanf("%f", &(v->weight));
			if (v->weight > 1.0 && v->weight < 60.0)		//pet's weight is in range
				break;
			else if (v->weight > 70.0) {		//pet's weight is too high
				printf("\n\n\tYour pet's weight is too high for us to handle!\n");
				printf("\tWe will recommend you a special veterinarian to take care of it instead.\n");
				printf("\tYour information entered will be deleted now.\n");
				status = -1;
				break;
			}
			else {		//pet's weight is out of range
				printf("\n\n\tInput Error!\n");
				printf("\tThe number you put is beyond the range.\n");
				printf("\tPlease re-enter your pet's weight\n");
				continue;
			}
		}
		if (status == -1) {		//cannot enter if pet's weight is too high
			free(v);
			return;
		}
		while (1) {
			printf("Is your pet a special case animal that is besides a dog or a cat?\n");		//special case pet
			printf("\t0. yes \t\t1. no\n");
			scanf("%d", &(v->flag));
			if (v->flag == 0) {		//it is special case animal
				printf("\tWe will recommend you a special veterinarian to take care of it instead.\n");
				printf("\tYour information entered will be deleted now.\n");
				free(v);
				return;
			}
			else if (v->flag == 1)
				break;
			else {
				printf("\n\n\tInput Error!\n");
				printf("\tPlease re-enter your pet's type\n");
				continue;
			}
		}
		showInformation(v, city);		//show entered information
		printf("Is the information correct?\n");		//determine whether correct
		printf("If correct, press 1 and if not, press 0.\n");
		scanf("%d", &flag);
		printf("\n");
		if (flag == 0)
			continue;
		else {		//add if information is correct
			while (tmp != L->Tail)
				tmp = tmp->next;
			v->next = tmp;
			v->prev = tmp->prev;
			tmp->prev->next = v;
			tmp->prev = v;
			L->length++;
			visitor *temp = h[v->city].hash_header;		//add to hashtable
			if (temp->hash_next == NULL)
				temp->hash_next = v;
			else {
				v->hash_next = temp->hash_next;
				temp->hash_next = v;
			}
			break;
		}		
	}
	printf("\n\n\tResistration completed!!\n");
}

//Edit visitor information
void editVisitor(List *L, char city[][10]) {
	int codeN, flag, status = 0;
	visitor *tmp = L->Header;
	if (tmp->next == L->Tail) {
		printf("\n\n\tNo Visitors!\n\n");
		return;
	}
	while (1) {
		printf("\nEnter the visitor code : ");		//enter code information
		scanf("%d", &codeN);
		visitor *p = searchByCode(L, codeN);		//verify code
		if (p == L->Header) {		//incorrect code
			printf("\n\n\tThe code you entered does not exist.\n");
			printf("\tPlease try again later.\n");
		}
		else {
			while (1) {		
				printf("\n\tHello %s!\n", p->name);
				printf("\tYou can only modify your name, phone number, pet name, and pet weight.\n\n");
				printf("Please enter your name : ");		//re-enter name
				scanf("%s", p->name);
				printf("Please enter your phone number : ");		//re-enter phone number
				scanf("%d", &(p->phone_num));
				printf("Please enter your pet's name : ");		//re-enter pet name
				scanf("%s", p->pet);
				while (1) {
					printf("Please enter your pet's weight in kilograms : ");		//re-enter pet weight
					scanf("%f", &(p->weight));
					if (p->weight > 1.0 && p->weight < 60.0)		//pet's weight is in range
						break;
					else if (p->weight > 70.0) {		//pet's weight is too high
						printf("\n\n\tYour pet's weight is too high for us to handle!\n");
						printf("\tWe will recommend you a special veterinarian to take care of it instead.\n");
						printf("\tYour information entered will be deleted now.\n");
						status = -1;
						break;
					}
					else {		//pet's weight is out of range
						printf("\n\n\tInput Error!\n");
						printf("\tThe number you put is beyond the range.\n");
						printf("\tPlease re-enter your pet's weight\n");
						continue;
					}
				}
				if (status == -1) {		//cannot enter if pet's weight is too high
					free(p);
					return;
				}
				showInformation(p, city);		//show entered information
				printf("Is the information correct?\n");		//determine whether correct
				printf("If correct, press 1 and if not, press 0.\n");
				scanf("%d", &flag);
				printf("\n");
				if (flag == 0)
					continue;
				else
					break;
			}
			printf("\n\n\tThe information has been modified successfully.\n\n");
		}
		break;
	}
}

//Delete visitor information
void deleteVisitor(List *L, hashTable *h) {
	int deleteDate, cnt = 0, i;
	visitor *p=L->Header, *tmp;
	if (p->next == L->Tail) {		//no visitors
		printf("\n\n\tNo Visitors!\n");
		return;
	}
	printf("Please enter the date you want to delete : ");		//delete all information prior to the date entered
	scanf("%d", &deleteDate);
	p = p->next;
	while (p != L->Tail) {
		if (p->date <= deleteDate) {		//delete from list
			tmp = p;		//tmp will be deleted
			p = p->next;
			(tmp->prev)->next = tmp->next;
			(tmp->next)->prev = tmp->prev;
			i = tmp->city;		//delete from hashtable
			visitor *temp = h[i].hash_header;
			while (temp->hash_next != tmp)		//temp before tmp node
				temp = temp->next;
			if (tmp->hash_next == NULL)
				temp->hash_next = NULL;
			else
				temp->hash_next = tmp->hash_next;
			free(tmp);
			L->length--;		//reduce length of visitor list
			cnt++;
		}
		else
			p = p->next;
	}
	printf("\n\t%d piece(s) of information is/are deleted.\n", cnt);
}

int main() {
	
	char city[7][10] = { "Seoul", "Busan", "Daegu", "Incheon", "Gwangju", "Daejeon", "Ulsan" };		//city information
	char searchName[20] = "";
	char id[11] = "MinsunPark", pw[11] = "Min1234567";		//administrator id and password
	char enterID[10] = "", enterPW[10] = "";		//id and pw entered
	int mode, visitorN, ManageN, searchN, searchTime, searchCity;
	List *L;
	initList(&L);		//initialize visitor list
	visitor *tmp;
	hashTable hash[7];
	initHashTable(hash, city);	//initialize hashtable list
	while (1) {
		introduction();
		modeMenu();
		printf("Enter mode number : ");		//enter whether visitor or administrator
		scanf("%d", &mode);
		printf("\n");
		if (mode == 1) {		//visitor menu
			visitorMenu();
			printf("Select Menu: ");		//enter visitor menu
			scanf("%d", &visitorN);
			printf("\n");
			if (visitorN == 1)		//add visitor information
				addVisitor(L, hash, city);
			else if (visitorN == 2)		//edit visitor information
				editVisitor(L, city);
			else {		//incorrect mode input
				printf("\n\tInput Error!\n");
				printf("\tEnter correct mode number again.\n\n");
				continue;
			}
		}
		else if (mode == 2) {		//administrator menu
			printf("\nEnter administrator ID : ");
			scanf("%s", enterID);
			printf("\nEnter administrator Password : ");
			scanf("%s", enterPW);
			printf("\n");
			if (strcmp(id, enterID) == 0 && strcmp(pw, enterPW) == 0) {
				printf("\n\t\tYou are logged in!\n");
				while (1) {		//administrator mode
					managerMenu();		//administrator menu
					printf("Select Manager Menu : ");
					scanf("%d", &ManageN);
					if (ManageN == 1)		//add visitor information
						addVisitor(L, hash, city);
					else if (ManageN == 2)		//edit visitor information
						editVisitor(L, city);
					else if (ManageN == 3)		//delete visitor information
						deleteVisitor(L, hash);
					else if (ManageN == 4) {		//print visitor information
						tmp = L->Header;
						if (tmp->next == L->Tail) {
							printf("\n\n\tNo visitors!\n\n");
							continue;
						}
						printf("\n\t1. Sort by name\n");
						printf("\n\t2. Sort by date\n");
						printf("\n\t3. Sort by city\n");
						printf("Enter number : ");
						scanf("%d", &searchN);
						if (searchN == 1) {		//sort by name
							printByName(L, city);
							printf("\n");
						}
						else if (searchN == 2) {		//sort by date
							printByDate(L, city);
							printf("\n");
						}
						else if (searchN == 3) {		//sort by city
							printByCity(hash, city);
							printf("\n");
						}
						else {		//incorrect number input
							printf("\n\n\t\tInput Error!\n");
							printf("\t\tPlease re-enter menu number.\n\n");
							continue;
						}
					}
					else if (ManageN == 5) {		//search visitor information
						tmp = L->Header;
						if (tmp->next == L->Tail) {
							printf("\n\n\tNo visitors!\n\n");
							continue;
						}
						printf("\n\t1. By name\n");
						printf("\t2. By date\n");
						printf("\t3. By city code\n");
						printf("Enter number : ");		//select option
						scanf("%d", &searchN);
						if (searchN == 1) {
							printf("Enter the name of the visitor you want to find : ");		//search by name
							scanf("%s", searchName);		
							printf("\n");
							searchByName(L, searchName, city);
							printf("\n");
						}
						else if (searchN == 2) {
							printf("Enter the date you want to find : ");		//search by date
							scanf("%d", &searchTime);
							printf("\n");
							searchByDay(L, searchTime, city);
							printf("\n");
						}
						else if (searchN == 3) {
							cityMenu(city);
							printf("\nEnter the city code you want to find the information : ");		//search by city
							scanf("%d", &searchCity);
							searchByCity(hash, searchCity, city);
							printf("\n");
						}
						else {
							printf("\n\n\t\tInput Error!\n");
							printf("\t\tPlease re-enter menu number.\n\n");
							continue;
						}
					}
					else if (ManageN == 0) {		//log-out
						printf("\n\tLog-out complete!\n");
						break;
					}
					else {		//incorrect number input
						printf("\n\n\t\tInput Error!\n");
						printf("\t\tPlease re-enter mode number.\n\n");
						continue;
					}
				}
			}
			else {		//incorrect log-in information
				printf("\n\tThe administrator's ID and password are incorrect!\n");
				printf("\t\tReturn to Initial Page\n\n");
				continue;
			}
		}
		else if (mode==0)		//exit program
			break;
		else {
			printf("\n\n\t\tInput Error!\n");
			printf("\t\tPlease re-enter mode number.\n\n");
			continue;
        }
		bye();		//ending of program
	}

	printf("\n\tEnd of Program\n\n");

	return 0;
}