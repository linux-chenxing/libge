// SPDX-License-Identifier:     GPL-3.0+

#include <stdio.h>
#include <stdint.h>

#include "libge.h"

int main (int argv, char** argc)
{
	int ret = 0;
	struct ge_cntx ge;

	printf("Opening GE..");
	ret = libge_open(&ge);
	if (ret){
		printf("failed: %d\n", ret);
		return ret;
	}
	else
		printf("done\n");

	printf("caps %08x\n", ge.info.caps);

	ret = libge_close(&ge);

	return ret;
}
