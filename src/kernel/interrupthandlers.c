#include "header.h"

cpu_state_t *(**interrupt_handlers(int i))(cpu_state_t *)
{
    static cpu_state_t *(*ints[256])(cpu_state_t *)={};
    return ints+i;
}

cpu_state_t *(*getinterrupthandler(int i))(cpu_state_t *)
{
    return *interrupt_handlers(i);
}

void setinterrupthandler(int i,cpu_state_t *(*f)(cpu_state_t *))
{
    *interrupt_handlers(i)=f;
}

cpu_state_t *handler_exception(cpu_state_t *cpu)
{
    int intr=cpu->intr;
    switch(intr)
    {
        case 0x00:
            puts("#DE - Division by Zero");
            break;
        case 0x01:
            puts("#DB - Debug");
            break;
        case 0x02:
            puts("#NMI - Non Maskable Interrupt");
            break;
        case 0x03:
            puts("#BP - BreakPoint");
            break;
        case 0x04:
            puts("#OF - Overflow");
            break;
        case 0x05:
            puts("#BR - Bound Range Exception");
            break;
        case 0x06:
            puts("#UD - Invalid Opcode");
            break;
        case 0x07:
            puts("#NM - Device n/a");
            break;
        case 0x08:
            kernelpanic("#DF - Double Fault");
            break;
        case 0x09:
            kernelpanic("Coprocessor Segment Overrun");
            break;
        case 0x0a:
            puts("#TS - Invalid TSS");
            break;
        case 0x0b:
            puts("#NP - Segment not Present");
            break;
        case 0x0c:
            puts("#SS - Stack Fault");
            break;
        case 0x0d:
            resetcolor();
            printf("General Protection Fault\nError Code: %u\n",(unsigned int)cpu->error);
            kernelpanic("#GP");
            break;
        case 0x0e:
            resetcolor();
            unsigned int err=cpu->error;
            int i;
            printf("Page Fault\nError Code: %u\n",err);
            for(i=0;i<5;i++)
            {
                printf("Bit: %2d:\t",i);
                switch(i)
                {
                    case 0:
                        puts(((err>>i)&1)?"Active Page":"Not active Page");
                        break;
                    case 1:
                        puts(((err>>i)&1)?"Write Access":"Read Access");
                        break;
                    case 2:
                        puts(((err>>i)&1)?"User Mode":"Kernel Mode");
                        break;
                    case 3:
                        printf("Reserved was %d",((err>>i)&1));
                        break;
                    case 4:
                        puts(((err>>i)&1)?"Code Access":"Data Access");
                }
            }
            kernelpanic("#PF - Page Fault");
            break;
        case 0x10:
            puts("#MF - x87 Floating Point");
            break;
        case 0x11:
            kernelpanic("#AC - Alignment Check");
            break;
        case 0x12:
            puts("#MC - Machine Check");
            break;
        case 0x13:
            puts("#XF - SIMD Floating Point");
            break;
        case 0x0f:
        case 0x14:
        case 0x15:
        case 0x16:
        case 0x17:
        case 0x18:
        case 0x19:
        case 0x1a:
        case 0x1b:
        case 0x1c:
        case 0x1d:
        case 0x1f:
            kernelpanic("Reserved Exception");
            break;
        case 0x1e:
            kernelpanic("#SX - Security-sensitive event in Host");
        default:
            printf("Exception %d\n",intr);
            kernelpanic("It is impossible to get this Error!\nIf you have this Error, please kill yourself, you have no life and no friends!");
            break;
    }
    return cpu;
}

cpu_state_t *handler_hardware_int(cpu_state_t *cpu)
{
    int intr=cpu->intr;
    task_t *task;
    switch(intr-0x20)
    {
        case 0x00:
//            puts("Timer");
            task=task_next();
            tss_entry_set(1,(uint32_t)(task->cpu+1));
            cpu=task->cpu;
            break;
        default:
            printf("IRQ %3d\n",intr-0x20);
            break;
    }
    return cpu;
}

task_t *get_task_by_cpu(cpu_state_t *cpu)
{
    task_t *task=0;
    int i=0;
    do
    {
        task=task_func(i++);
    }
    while(task->cpu!=cpu&&i<TASKS_SIZE);
    return i<TASKS_SIZE?task:0;
}

cpu_state_t *int_handler(cpu_state_t *cpu)
{
    cpu_state_t *(*f)(cpu_state_t *)=getinterrupthandler(cpu->intr);
    task_t *task=get_task_by_cpu(cpu);
    task_t *old_task=task;
    if(!f)
    {
        kernelpanic("Unhandeled Interrupt!");
    }
    else
    {
        cpu=f(cpu);
    }
    if(task)
    {
        if(old_task->cpu->intr>=0x20&&old_task->cpu->intr<0x30)
        {
            if(old_task->cpu->intr<0x29)
            {
                outb(0x20,0x20);
            }
            outb(0xa0,0x20);
        }
    }
    if(old_task!=task)
    {
        page_activate_context(task->context);
    }
    return cpu;
}

task_t *task_next(void)
{
    return task_schedule(0);
}

cpu_state_t *cpu_new(page_context_t *c,void *ptr,char userspace)
{
    const int stackspace=4096;
    cpu_state_t cpu;
    cpu.eax=0;
    cpu.ebx=0;
    cpu.ecx=0;
    cpu.edx=0;
    cpu.esi=0;
    cpu.edi=0;
    cpu.ebp=0;
    cpu.eip=(uint32_t)ptr;
    cpu.cs=0x08;
    if(userspace)
    {
        cpu.cs=0x18|0x03;
        cpu.ss=0x20|0x03;
    }
    cpu.eflags=0x202;
    ptr=0;
    while(!ptr)
    {
        ptr=mallocblocks(c,1);
    }
    cpu.esp=(uint32_t)ptr+stackspace;
    cpu_state_t *state=(void *)(ptr+stackspace-sizeof(cpu));
//    printf("%x/%x\n",&cpu,state);
    memcpy(state,&cpu,sizeof(cpu));
    return state;
}

task_t *task_func(int i)
{
    static task_t tasks[TASKS_SIZE]={};
    return tasks+i;
}

task_t *task_schedule(task_t *task)
{
    static int last=0;
    int i;

    if(task)
    {
        for(i=0;task_func(i)->cpu&&i<TASKS_SIZE;i++);
        if(i<TASKS_SIZE)
        {
            *task_func(i)=*task;
        }
        return 0;
    }
    
    for(i=last;!task_func(i)->cpu;i++)
    {
        if(i>=TASKS_SIZE)
        {
            i=-1;
        }
    }
    return task_func(i);
}

void exit(int ret)
{
    while(1)
    {
        asm("int $0x30" : : "a" (SYSCALL_TASK_EXIT), "b" (ret));
    }
}

