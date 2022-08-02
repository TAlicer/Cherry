#include <stdio.h>
#include <signal.h>
#include <sys/time.h>

void send_property_changed(int signo)
{
	switch (signo)
	{
		case SIGALRM:
			printf("Caught the SIGALRM signal!\n");
			break;
	}
}

void arch_os_async_call(int value)
{
	signal(SIGALRM, send_property_changed);
	struct itimerval  new_value;
    new_value.it_value.tv_sec = 1;
    new_value.it_value.tv_usec = 0;
    new_value.it_interval.tv_sec = value;
    new_value.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &new_value, NULL);
}

int main(int argc, char *argv[])
{   
	int i = 0;
	
	for(i=0; i<3; i++)
	{
		arch_os_async_call(3);
	}
	
	printf("&&&&&&&&&&&&\n");
	
    for(;;);
     
    return 0;
}