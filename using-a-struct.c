//	 ▄   ▄   ▄▄▄   ▄▄▄    ▄ ▄▄    ▄▄▄▄          ▄▄▄  
//	 █   █  █   ▀    █    █▀  █  █▀ ▀█         ▀   █ 
//	 █   █   ▀▀▀▄    █    █   █  █   █         ▄▀▀▀█ 
//	 ▀▄▄▀█  ▀▄▄▄▀  ▄▄█▄▄  █   █  ▀█▄▀█         ▀▄▄▀█ 
//	                              ▄  █               
//	                               ▀▀                
//	                                          
//	          ▄                           ▄   
//	  ▄▄▄   ▄▄█▄▄   ▄ ▄▄  ▄   ▄   ▄▄▄   ▄▄█▄▄ 
//	 █   ▀    █     █▀  ▀ █   █  █▀  ▀    █   
//	  ▀▀▀▄    █     █     █   █  █        █   
//	 ▀▄▄▄▀    ▀▄▄   █     ▀▄▄▀█  ▀█▄▄▀    ▀▄▄ 
//
//
//
// BY ROHAN MOLLOY
//
//

#include <stdio.h>

//
// Create our structure containing attributes of the person.
// Define a new type of "Person"
//

typedef struct person {
	char *name;
	char gender;
	double weight;
	double height;
	unsigned int birthdate[3];
} Person;

//
// Delcare our functions 
// 
void printPersion(Person);
Person makeExamplePerson(void); 

int main(int argc, char *argv[])
{
	Person johnsmith =  makeExamplePerson(); 
	printPerson(johnsmith);
	return 0; 
}


Person makeExamplePerson()
{
	Person p;
	p.name = "John Smith";
	p.gender = 'M';
	p.weight = 75.7;
	p.height = 1.75;
	p.birthdate[0] = 10;
	p.birthdate[1] = 12;
	p.birthdate[2] = 1993;
	return p;	
}

void printPerson(Person p)
{
	printf(
	"Name:%s\nSex:%c\nWeight:%.2f\nHeight:%.2f\nDOB:%d-%d-%d\n",
	       p.name,p.gender,p.weight,p.height,p.birthdate[0],
	       p.birthdate[1],p.birthdate[2]
	);
}
