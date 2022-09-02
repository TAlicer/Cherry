#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static int  g_port;
static int  g_mode;
static char g_logwirte[32]; 

void parse_arg(int argc, char*argv[])
{
	int opt;
	const char *str = "p:l:m:";

	while ((opt = getopt(argc, argv, str)) != -1)
	{
		switch (opt)
		{
			case 'p':
			{
				g_port = atoi(optarg);
				printf("g_port = [%d]\n", g_port);
				break;
			}
			case 'l':
			{
				strncpy(g_logwirte, optarg, sizeof(g_logwirte));
				printf("g_logwirte = [%s]\n", g_logwirte);
				break;
			}
			case 'm':
			{
				g_mode = atoi(optarg);
				printf("g_mode = [%d]\n", g_mode);
				break;
			}
			default:
				break;
		}
	}
}



int main(int argc, char*argv[])
{
	parse_arg(argc, argv);
	
	return 0;
}