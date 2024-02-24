//Attendance Management System

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Global variable declarations
int r1=0,r2=0,r3=0;

//Structure definition
struct sll
{
	char name[70];
	int roll_no;
	int present,absent,course;
    struct sll *next;

};
typedef struct sll node;
node * start=NULL;

//Student structure definition
struct student
{
	char date[20];
	int absent[1000];
	int ab;
  struct student *next;

};
typedef struct student node2;
node2 *start2=NULL;

//Function to allocate roll number
int roll(int c)
{
    if(c==1)
        return((c*1000)+(++r1));
    else if(c==2)
        return((c*1000)+(++r2));
    else
        return((c*1000)+(++r3));
}

node *fcreate()
{
    node *temp;
    temp=(node*)malloc(sizeof(node));
    temp->next=NULL;
	return temp;
}
//Function to create a student node
node* create()
{
	node *temp;
	temp=(node*)malloc(sizeof(node));
	printf("Enter the student name: ");
	scanf("%s",temp->name);
	printf("1.ISE\n2.CSE\n3.ECE\nEnter your choice:");
	scanf("%d",&temp->course);
	temp->present=temp->absent=0;
	temp->roll_no=roll(temp->course);
	printf("\nThe roll no issued is %d\n",temp->roll_no);
	temp->next=NULL;
	return temp;
}

void put_data()
{
    node *cur;
    FILE *file=fopen("list1.txt","w");
    if(file==NULL)
        exit(1);
    for(cur=start;cur!=NULL;cur=cur->next)
    {
        fprintf(file,"%s %d %d %d %d\n",cur->name,cur->roll_no,cur->course,cur->present,cur->absent);
    }
    fclose(file);
}
void get_data()
{
    FILE *file=fopen("list1.txt","r");
    if(file==NULL)
    {
        printf("File fetch failed");
        exit(0);
    }
    int r,c,p,a;
    char n[100],line[1000];
    while(fgets(line,sizeof(line),file)!=NULL)
    {
        if(sscanf(line,"%s %d %d %d %d",n,&r,&c,&p,&a)==5)
        {
            node *cur=fcreate();
            strcpy(cur->name,n);
            cur->roll_no=r;
            cur->course=c;
            cur->present=p;
            cur->absent=a;
            if(start==NULL)
            {
                start=cur;
            }
            else
            {
                node *t=start;
                while(t->next!=NULL)
                    t=t->next;
                t->next=cur;
            }
        }
    }


    fclose(file);
}

//Function to add a new student
void insert_student()
{
	node *temp=start;
	node *newnode=create();
	if(start==NULL)
	{
		start=newnode;
		printf("New student registration successful!\n");
		put_data();
		return;
	}
	if(start->next==NULL)
    {
        if(start->roll_no>newnode->roll_no)
        {
            newnode->next=start;
            start=newnode;
            printf("New student registration successful!\n");
            put_data();
            return;
        }
        else
        {
            start->next=newnode;
            printf("New student registration successful!\n");
            put_data();
            return;
        }
    }
    int a=0;
	while(temp->next!=NULL)
	{
	    if(newnode->roll_no<start->roll_no)
        {
            newnode->next=start;
            start=newnode;
            a++;
            printf("New student registration successful!\n");
            put_data();
            return;
        }
		if(temp->next->roll_no > newnode->roll_no)
        {
            newnode->next=temp->next;
            temp->next=newnode;
            a++;
            printf("New student registration successful!\n");
            put_data();
            return;
        }
        temp=temp->next;
	}
	if(a==0)
    {
        temp->next=newnode;
        printf("New student registration successful!\n");
        put_data();
    }

}

//Function to delete student details
void delete_student()
{
	node *temp=start,*temp2;
	int n;
	if(start==NULL)
	{
		printf("\nList empty\n");
		return;
	}
	printf("Enter the roll number to be deleted : ");
	scanf("%d",&n);
	int a=0;
	if(temp->next==NULL)
    {
        if(temp->roll_no==n)
        {
            free(temp);
            start=NULL;
            printf("\nStudent details with roll number %d deleted\n",n);
            return;
        }
        else
        {
            printf("Invalid roll_no\n");
            return;
        }
    }
    if(start->roll_no==n)
    {
        start=temp->next;
        free(temp);
        printf("\nStudent details with roll number %d deleted\n",n);
        return;
    }
	while(temp!=NULL)
    {
        if(temp->next->roll_no==n)
        {
            temp2=temp->next;
            temp->next=temp2->next;
            free(temp2);
            a++;
            printf("\nStudent details with roll number %d deleted\n",n);
            return;
        }
        temp=temp->next;
    }
    if(a==0)
        printf("\nRoll number not found\n");
}

//Function to display student details
void display_student()
{
	node *temp=start;
	if(start==NULL){
		printf("list empty\n\n");

		return;
	}
		printf("ROLL NO.\tNAME\tCOURSE\tPRESENT\tABSENT\n");
	while(temp!=NULL)
	{

		printf("%d\t",temp->roll_no);
		printf("\t%s\t",temp->name);
		switch(temp->course)
		{
			case 1:printf("ISE\t");
			break;
			case 2:printf("CSE\t");
			break;
			case 3:printf("ECE\t");
			break;

		}
		printf("%d\t",temp->present);
		printf("%d\t",temp->absent);
		temp=temp->next;
		printf("\n");
	}
}

//Function to enter attendance details
void attendance()
{
     int i;
     node2 *temp2=(node2 *)malloc(sizeof(node2));
  	 printf("\n Enter the date(DD/MM/YYYY): ");
	 scanf("%s",temp2->date);
	 printf("\nEnter number of students absent : ");
	 scanf("%d",&temp2->ab);
	 if(temp2->ab==0)
     {
         printf("\nNo student absent!\n");
     }
     else
     {
         printf("Enter the roll numbers of the students who are absent\n");
        for(i=0;i<temp2->ab;i++)
        {
            scanf("%d",&temp2->absent[i]);
        }
        node *temp=start;
        while(temp!=NULL)
        {
            temp->present++;
            temp=temp->next;
        }
        for(i=0;i<temp2->ab;i++)
        {
            node *temp=start;
            while(temp!=NULL)
            {
                if(temp->roll_no==temp2->absent[i])
                {
                    temp->absent++;
                    temp->present--;
                }
                temp=temp->next;
            }
        }
     }
     if(start2==NULL)
     {
         start2=temp2;
         printf("\nDetails updated!\n");
         return;
     }
     node2 *tem=start2;
     while(tem->next!=NULL)
     {
         tem=tem->next;
     }
     tem->next=temp2;
     printf("\nDetails updated!\n");
}
void display_attendance()
{
    node2 *temp=start2;
    int i;
    printf("\nDate\tAbsent roll nos\n");
    while(temp!=NULL)
    {
        printf("%s\t\t",temp->date);
        for(i=0;i<temp->ab;i++)
        {
            printf("%d, ",temp->absent[i]);
        }
        temp=temp->next;
        printf("\n");
    }
}

//Function to list attendance shortage
void attendance_shortage()
{
    int days,n=0;
    printf("\nEnter the minimum attendance required: ");
    scanf("%d",&days);
    node *temp=start;
    int a[1000],i=0;
    while(temp!=NULL)
    {
        if(temp->present<days)
        {
            n++;
            a[i]=temp->roll_no;
            i++;
        }
        temp=temp->next;
    }
    printf("There are %d students with attendance shortage\nThe roll numbers are: ",n);
    for(i=0;i<n;i++)
    {
        printf("%d, ",a[i]);
    }
    printf("\n");
}

//Main function
void main()
{
    int ch;
    get_data();
    for(;;)
    {
        printf("--------------------ATTENDANCE MANAGEMENT SYSTEM--------------------\n");
        printf("\n1.New student\n2.Delete student\n3.Display student details\n4.Attendance entry\n5.Display Attendance details\n6.Attendance Shortage List\n7.Exit\nEnter choice: ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:insert_student();break;
            case 2:delete_student();break;
            case 3:display_student();break;
            case 4:attendance();break;
            case 5:display_attendance();break;
            case 6:attendance_shortage();break;
            case 7:exit(0);
        }
    }
}
