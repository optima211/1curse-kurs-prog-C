#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>
#include <memory.h>
#include<math.h>
#include <new.h>

struct zach {
    char prname[20];
    int prmark;
};
struct spis {
    char surname[20];
    char middlename[20];
    char name[20];
    struct zach spiszach[4];
    struct spis *prev;
    struct spis *next;
};

void createlist(void);
void viewlist(void);
void add(void);
void find(void);
void del(void);
void save(void);
void load(void);
int GetRecords();

struct spis *head, *tail;

#define FILE_NAME "output.txt"

int main() {
    load();
    char c;
    while (1) {
        puts("1 - new list");
        puts("2 - view list");
        puts("3 - add to head");
        puts("4 - find and correct");
        puts("5 - delete information about students with bad marks");
        puts("6 - save list to file");
        puts("0 - exit");
        c = _getch();
        switch(c) {
            case '1':createlist();break;
            case '2':viewlist(); break;
            case '3':add(); break;
            case '4':find(); break;
            case '5':del();break;
            case '6':save();break;
            case '0':return 0;
            default: printf("incorrect mode %d\n",c);
        }
        puts("");
    }
}

void createlist(void) {
    head = tail = NULL;
    printf ("\nRecords: %d\n",GetRecords());
}

void viewlist(void) {
    struct spis *p;
    int i;
    p = head;
    while(p != NULL){
        printf("\n%s %s %s\n",p->surname,p->name,p->middlename);
        for (i = 0;i < 4;i++)
            printf("%s:  %d\n",p->spiszach[i].prname,p->spiszach[i].prmark);
        printf("\n********************\n");
        p = p->next;
    }

}

void add(void) {
    struct spis *p;
    int i;
    p = (struct spis *) malloc(sizeof(struct spis));
    printf("\n Surname: ");    scanf_s("%s", p->surname,20);
    printf("\n Name: ");    scanf_s("%s", p->name,20);
    printf(" \n Last name: ");    scanf_s("%s", p->middlename,20);
    for(i = 0;i < 4;i++)
    {
        printf(" Subject %d: ", i);        scanf("%s", p->spiszach[i].prname);
        printf(" Mark %d: ", i);        scanf("%d", &p->spiszach[i].prmark);
    }
    p->prev = NULL;
    p->next = head;
    if (head != NULL)
        head->prev = p;
    head = p;
    printf ("\nRecords: %d\n",GetRecords());
}

void find(void) {
    struct spis *p;
    char s[20], c;
    int i;
    printf("\n Insert student's surname for searching: ");
    scanf_s("%s", &s,20);
    p = head;
    while (p != NULL) {
        if (strcmp(p->surname, s) == 0) {
            printf("\n %s  %s %s\n ",p->surname,p->name,p->middlename);
            for (i = 0;i < 4;i++)
                printf("%s:  %d\n ",p->spiszach[i].prname,p->spiszach[i].prmark);
            printf("\n Correct this record? - Y/N");
            c = _getch();
            if ((c == 'y') || (c == 'Y'))
                for(i = 0;i < 4;i++) {
                    printf("\n %s: ",p->spiszach[i].prname);
                    scanf_s("%d", &p->spiszach[i].prmark,1);
                }
        }
        p = p->next;
    }
    printf ("\nRecords: %d\n",GetRecords());
}

void del(void) {
    struct spis *p, *pn;
    char c;
    int i,n;
    printf("Are you sure? - Y/N\n");
    c = _getch();
    if ((c != 'y') && (c != 'Y'))
        return;
    p = head;
    while (p != NULL) {
        pn = p->next;
        n = 0;
        for(i = 0;i < 4;i++)
            if (p->spiszach[i].prmark < 3)
                n++;
        if (n > 2){
            if (p->prev != NULL)
                p->prev->next = p->next;
            if (p->next != NULL)
                p->next->prev = p->prev;
            free(p);
        }
        p = pn;
    }
    printf ("\nRecords: %d\n",GetRecords());
}

void save() {
    struct spis *p = head;
    FILE *output;
    if (head == NULL) {
        printf("\n The list is empty\n");

    } else {
        output = fopen(FILE_NAME, "wb");
        if (output != NULL) {
            while (p != NULL) {
                fwrite(p, sizeof(struct spis), 1, output);
                p = p->next;
            }
            printf("\n Information successfully saved\n");
            fclose(output);
        } else
            printf("\n Information was not saved\n");
    }
    printf ("\nRecords: %d\n",GetRecords());
}

void load() {
    FILE *input;
    struct spis *p;
    input = fopen(FILE_NAME, "r");
    head = tail = NULL;
    if (input != NULL) {
        while (!feof(input)) {
            p = (struct spis *)malloc(sizeof(struct spis));
            fread(p, sizeof(struct spis), 1, input);
            if (feof(input))
                break;
            p->next = NULL;
            p->prev = tail;
            if (tail != NULL)
                tail->next = p;
            if (head == NULL)
                head = p;
            tail = p;
        }
        fclose(input);
    }
    printf ("\nRecords: %d\n",GetRecords());
}

int GetRecords() {
    int n = 0;
    struct spis *p;
    p = head;
    while(p != NULL) {
        n++;
        p = p->next;
    }
    return(n);
}
