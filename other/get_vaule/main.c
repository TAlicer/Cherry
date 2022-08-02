#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>

uint64_t arch_get_did_ex(void)
{
	uint64_t did = 0;
	FILE * fp;
	char pBuf[256] = {0};

	fp = fopen ("./device.conf", "r");
	fread(pBuf, sizeof(pBuf), 1, fp);
	
	sscanf(pBuf, "%*[^did]did=%" PRId64 "[^\r]", &did);
	
	fclose(fp);
	return did;
}

int main()
{
	uint64_t did = 0;
	
	did = arch_get_did_ex();	
	printf("did = %" PRId64 "\n", did);
	
	return 0;
}