// SPDX-License-Identifier:     GPL-3.0+

#include <stdio.h>
#include "libge.h"

int main (int argv, char** argc)
{
	int ret = 0;
	struct ge_cntx ge;

	printf("Opening GE..");
	ret = libge_open(&ge);
	if (ret){
		printf("failed\n");
		return ret;
	}
	else
		printf("done\n");

	ret = libge_close(&ge);

	return ret;
}
