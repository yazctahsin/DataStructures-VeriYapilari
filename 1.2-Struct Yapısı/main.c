#include <stdio.h>
#include <stdlib.h>
typedef struct Person{
    char* Name;
    int age;
}person;
typedef struct Student{
    int sNo;
    struct Person p;
}student;
int main()
{
    person p1;
    p1.Name = "John";
    p1.age = 15;
    printf("Person's name : %s\n" , p1.Name);
    printf("Person's age  : %d\n" , p1.age);
    printf("------------------------ \n");
    displayPerson(p1);
    printf("------------------------ \n");
    student s1;
    s1.sNo = 2000;
    s1.p.Name = "Mustafa";
    s1.p.age = 22;
    displayStudent(s1);
    printf("------------------------ \n");
    person* ptr = &p1;
    printf("Person's name : %s\n" , ptr->Name);
    printf("Person's age  : %d\n" , ptr->age);
    printf("------------------------ \n");
    printf("Struct'in adresi : %p\n" , &p1);
    printf("Name'in adresi : %p\n" , &(p1.Name));
    printf("Age'in adresi : %p\n" , &(p1.age));
    printf("p.age'in adresi : %p\n" , &(ptr->age));



    return 0;
}
void displayPerson(person p1)
{
    printf("Person's name : %s\n" , p1.Name);
    printf("Person's age  : %d\n" , p1.age);
}
void displayStudent(student s1)
{
    printf("Student's name : %s\n" , s1.p.Name);
    printf("Student's age  : %d\n" , s1.p.age);
    printf("Student's School Number  : %d\n" , s1.sNo);
}

