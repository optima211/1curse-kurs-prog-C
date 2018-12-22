#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>
#include <memory.h>
#include <new.h>
struct spis {char surname[20]; char middlename[20]; char name [20];
    int bal1, bal2, bal3, bal4; struct spis *v1; struct spis *v2;};
void create (void);
void list (struct spis *);
void add (void);
void find (void);
void del (void);
void save (void);
void load (void);
struct spis *head, *tail;
int main()
{char c;
    while (1)
    {
//        clrscr();
        puts("1 - new file");
        puts("2 - print file");
        puts("3 - add to file");
        puts("4 - find and correct information");
        puts("5 - delete information about students with bad marks");
        puts("6 - save list to file");
        puts("7 - load list from file");
        puts("0 - exit");
//            c=_getch();
        scanf_s("%c", &c);
        switch(c)
        {case '1':create();break;
            case '2':list(head); break;
            case '3':add(); break;
            case '4':find(); break;
            case '5':del();break;
            case '6':save();break;
            case '7':load();break;
            case '0':return 0;
            default: puts("incorrect mode");
        }
    }
//free(head);
}
void create (void)
{
//    clrscr();
   struct spis *p, *pred;
    pred=NULL;
    printf("\n Insert information about students \n");
    do
    {p=(struct spis *)malloc(sizeof(struct spis));
        printf ("\n Surname: "); scanf_s ("%s", &p->surname);
        printf (" Name: "); scanf_s ("%s", &p->name);
        printf(" Middle name: "); scanf_s("%s", &p->middlename);
        printf(" Maths: "); scanf_s("%d", &p->bal1);
        printf(" English: "); scanf_s("%d", &p->bal2);
        printf(" Programming: "); scanf_s("%d", &p->bal3);
        printf(" Physics: "); scanf_s("%d", &p->bal4);
        p->v1=pred;
        if (pred!=NULL)
            pred->v2=p;
        else
            head=p;
        pred=p;
        puts (" Finish - <esc>");
    }
    while (_getch()!=27);
    tail=p;
    tail->v2=NULL;
}

void list (struct spis *p)
{
//    clrscr();
    printf("Surname\t|   Name   |    M.name   | Maths | English | Programming | Physics \n");
    printf("---------------------------------------------------------------------------");
    if (p==head)
        while (p!=NULL)
        {printf("\n%s\t| %s\t   | %s\t |   %d   |    %d    |      %d      |    %d   ", p->surname, p->name, p->middlename,
                p->bal1, p-> bal2, p->bal3, p->bal4);
            p=p->v2;
        }
    else if (p==tail)
        while (p!=NULL)
        {puts (p->surname);
            p=p->v1;
        }
    else
        puts ("Incorrect input:");
    _getch();
}

void add(void)
{struct spis *p, *pn;
//    clrscr();
    printf("\n\n\n");
    do
    {pn=(struct spis *)malloc(sizeof(struct spis));
        printf ("\n Surname: "); scanf_s ("%s", &pn->surname);
        printf (" Name: "); scanf_s ("%s", &pn->name);
        printf(" Middle name: "); scanf_s("%s", &pn->middlename);
        printf(" Maths: "); scanf_s("%d", &pn->bal1);
        printf(" English: "); scanf_s("%d", &pn->bal2);
        printf(" Programming: "); scanf_s("%d", &pn->bal3);
        printf(" Physics: "); scanf_s("%d", &pn->bal4);
        p=head;
        pn->v1=NULL;
        pn->v2=p;
        p->v1=pn;
        head=pn;
        puts ("Finish - <esc>");
    }
    while (_getch()!=27);
}

void find (void)
{
    printf("\n\n\n");
 struct   spis *p, *z;
    int x=0;
    char y[20], c;
    printf("\n Insert student's surname for searching: ");
    scanf_s ("%s",&y);
    p=head;
    while (p!=NULL)
    {if (strcmp(p->surname,y)==0)
        {x++;
            printf("\n Results: ");
            printf("\n %s \t| %s | %s | %d | %d | %d | %d ", p->surname, p->name, p->middlename,
                   p->bal1, p->bal2, p->bal3, p->bal4);
            printf("\n Correct this record? - Y/N");
//            c=_getch();
            scanf_s("%c", &c);
            if (c=='y')
            {printf("\n Maths: "); scanf_s("%d", &p->bal1);
                printf(" English: "); scanf_s("%d", &p->bal2);
                printf(" Programming: "); scanf_s("%d", &p->bal3);
                printf(" Physics: "); scanf_s("%d", &p->bal4);
                printf("\n Correction finished");
                _getch ();
            }
        }
        p=p->v2;
    }
    if(x==0)
    {printf("\n Not found");
        _getch();
    }
}

void del(void)
{//clrscr();
    printf("\n\n\n");
    struct spis *p, *temp;
    int j=0;
    char c;
    printf ("\n Students with bad marks:");
    p=head;
    while (p!=NULL)
    {
        if(p->bal1+p->bal2+p->bal3<=6 || p->bal1+p->bal3+p->bal4<=6 || p->bal1+p->bal2+p->bal4<=6 || p->bal2+p->bal3+p->bal4<=6)
        {j++;
            printf("\n Results: ");
            printf("\n %s \t| %s | %s | %d | %d | %d | %d ", p->surname, p->name, p->middlename,
                   p->bal1, p->bal2, p->bal3, p->bal4);
            printf("Delete? - Y/N");
//            c=_getch();
            scanf_s("%c", &c);
            if (c=='y')
            {if (p==head)
                {head=p->v2;
                    head->v1=NULL;
                    free(p);
                    p=head;
                }
                else if (p==tail)
                {tail=p->v1;
                    tail->v2=NULL;
                    free(p);
                    p=tail;
                }
                else
                {p->v2->v1=p->v1;
                    p->v1->v2=p->v2;
                    temp=p;
                    free(temp);
                }
                printf("\n\n Deleted \n");
                _getch();
            }

        }
        p=p->v2;
    }
    if(j==0)
    {printf("\n Not found");
        _getch();
    }
}

void save()
{//clrscr();
    printf("\n\n\n");
  struct  spis *p=head;
    FILE *output;
    if(head==NULL)
    {
        printf("\n The list is empty");

    }
    else
    {output=fopen("Output.txt","wb");
        if(output!=NULL)
        {while(p!=NULL)
            {fwrite(p, sizeof(struct spis),1,output);
                p=p->v2;
            }
            printf("\n Information succesfuly saved");
            fclose (output);

        }
        else
            printf("\n Information was not saved");

    }
    _getch();
}

void load()
{//clrscr();
    struct spis *p,*r;
    FILE *input;
    r=NULL;
    p=head;
    input=fopen("Output.txt","rb");
    if(input!=NULL)
    {do
        {p=new spis;
            fread (p, sizeof(struct spis), 1, input);
            p->v1=NULL;
            p->v2=NULL;
            p->v1=r;
            if (r!=NULL)
                r->v2=p;
            else
                head=p;
            r=p;
        }
        while (!feof(input));
    }
    tail=p->v1;

    tail->v2=NULL;
    p=tail;
    fclose(input);
    printf("\n Load complete");
    _getch();
}