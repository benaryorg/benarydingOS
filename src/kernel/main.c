#include "header.h"

int main(void)
{
    puts("Main started");
//	cleardisplay();
	puts("benarydingOS Running!");
//	puts("Memorydump:");
//	memdump();
//	cleardisplay();

	puts("Awaiting Input!\n");

    puts("Tasks:");
    int i;
    for(i=0;i<TASKS_SIZE;i++)
    {
        if(task_func(i)->id>0)
        {
            printf("%d: cpu=%x\n",task_func(i)->id,task_func(i)->cpu);
        }
    }

//    exit(0);

	while(1);

	exit(0);
	return 0;
}
