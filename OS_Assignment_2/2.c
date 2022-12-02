#include <stdio.h>
#include <sys/syscall.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <errno.h>
float arr2[5][4];

void printArr(){
	for(int i = 0; i < 5; i++){
			for(int j = 0; j < 4; j++){
				printf("%2f ", arr2[i][j]);
			}
		}
}
int main()
{
	float arr[5][4] = {{10, 22, 63,80}, {92, 36, 45,25.26}, {84, 15, 36,45.38}, {88, 65, 3.0,43},{84, 15, 36,45.3}};
	
	long sys_call_status = syscall(451, arr, arr2, 3, 3);
	if (sys_call_status != EFAULT)
	{
        printf("Successfully invoked system call 451\n");
		printArr();
		
	}else{
		printf("Not generated syscall");
	}
	return 0;
}