#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <pthread.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <sched.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <pwd.h>
#include <errno.h>
#include <sys/wait.h>
#define ll long long;
void countA()
{

    long long count = 0;
    for (int i = 0; i < UINT_MAX; i++)
    {
        count += 1;
    }
}

void countB()
{
    long long count = 0;
    for (int i = 0; i < UINT_MAX; i++)
    {
        count += 1;
    }
}
void countC()
{
    long long count = 0;
    for (int i = 0; i < UINT_MAX; i++)
    {
        count += 1;
    }
}

void timePrinter(double ptr, struct timespec s, struct timespec e,char c)
{
    ptr = (e.tv_sec - s.tv_sec) + (e.tv_nsec - s.tv_nsec) / 1000000000.0;
    printf("%c\n",c);
    printf("%f\n", ptr);
}

void clockMethod(struct timespec s, struct timespec e, int counter,char c)
{
    if (counter == 1)
    {
        clock_gettime(CLOCK_REALTIME, &s);
        countA();
        clock_gettime(CLOCK_REALTIME, &e);
        double ptr;
        timePrinter(ptr, s, e,c);
    }
    else if (counter == 2)
    {
        clock_gettime(CLOCK_REALTIME, &s);
        countB();
        clock_gettime(CLOCK_REALTIME, &e);
        double ptr;
        timePrinter(ptr, s, e,c);
    }
    else
    {
        clock_gettime(CLOCK_REALTIME, &s);
        countC();
        clock_gettime(CLOCK_REALTIME, &e);
        double ptr;
        timePrinter(ptr, s, e,c);
    }
}

void process1()
{
    struct timespec s1, e1,s2,e2,s3,e3;
    double ptr1,ptr2,ptr3;
    pid_t pid;
    int status;
    clock_gettime(CLOCK_REALTIME, &s1);
    if(pid = fork()== 0){
        execl("/bin/bash","sh","./kernelBash.sh",NULL);
    }else{
        clock_gettime(CLOCK_REALTIME, &s2);
        if(pid=fork() ==0){
            execl("/bin/bash","sh","./kernelBash2.sh",NULL);
        }else{
            clock_gettime(CLOCK_REALTIME, &s3);
            if(pid = fork()==0){
                execl("/bin/bash","sh","./kernelBash3.sh",NULL);
            }
            else{
                waitpid(pid,&status,WNOHANG);
                clock_gettime(CLOCK_REALTIME, &e1);
                double ptr;
                timePrinter(ptr1, s1, e1,'a');
            }
            waitpid(pid,&status,WNOHANG);
            clock_gettime(CLOCK_REALTIME, &e2);
            timePrinter(ptr2, s2, e2,'a');
        }
        waitpid(pid,&status,WNOHANG);
        clock_gettime(CLOCK_REALTIME, &e3);
        timePrinter(ptr3, s3, e3,'a');
    }
    timePrinter(ptr1, s1, e1,'a');
    timePrinter(ptr2, s2, e2,'a');
    timePrinter(ptr3, s3, e3,'a');

}


void forkCaller()
{
    
    process1();
    

}

struct sched_param paramA;
struct sched_param paramAmain;
struct sched_param paramB;
struct sched_param paramBmain;
struct sched_param paramC;
struct sched_param paramCmain;
void paramPrioritySetter(int c,int prio)
{
    if (c == 1)
        paramA.sched_priority = prio;
    else if (c == 2)
        paramB.sched_priority = prio;
    else
        paramC.sched_priority = prio;
}



void *threACaller()
{
    paramPrioritySetter(1,0);
    int y = pthread_setschedparam(pthread_self(), SCHED_OTHER, &paramA);
    int policy;
    pthread_getschedparam(pthread_self(), &policy, &paramAmain);

    printf("%d\n", y);
    struct timespec start, end;
    
    clockMethod(start, end, 1,'a');
}

void *threBCaller()
{
    paramPrioritySetter(2,6);
    int y = pthread_setschedparam(pthread_self(), SCHED_RR, &paramB);
    int policy;
    pthread_getschedparam(pthread_self(), &policy, &paramBmain);

    printf("%d\n", y);
    struct timespec start, end;
    
    clockMethod(start, end, 2,'b');
}

void *threCCaller()
{
    paramPrioritySetter(3,10);
    int y = pthread_setschedparam(pthread_self(), SCHED_FIFO, &paramC);
    int policy;
    pthread_getschedparam(pthread_self(), &policy, &paramCmain);

    printf("%d\n", y);
    struct timespec start, end;
    
    clockMethod(start, end, 3,'c');
}

pthread_t ThrA, ThrB, ThrC;

void threadCaller()
{
    pthread_create(&ThrA, NULL, &threACaller, NULL);
    pthread_create(&ThrB, NULL, &threBCaller, NULL);
    pthread_create(&ThrC, NULL, &threCCaller, NULL);
    pthread_join(ThrA, NULL);
    pthread_join(ThrB, NULL);
    pthread_join(ThrC, NULL);
}

int main()
{
    printf("----Press 1 for thread based processing-------\n");
    printf("----Press 2 for fork based processing-------\n");
    int t = 0;
    scanf("%d", &t);
    if (t == 1)
    {
        threadCaller();
    }
    else
    {
        forkCaller();
    }
}