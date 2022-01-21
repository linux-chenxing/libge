// SPDX-License-Identifier:	LGPL-2.1+
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#include "libge.h"

int libge_open(struct ge_cntx *ge)
{
	int fd;

	fd = open("/dev/mstar-ge", O_RDWR);
	if (fd < 0)
		return errno;

	ge->fd = fd;

	return 0;
}

int libge_close(struct ge_cntx *ge)
{
	close(ge->fd);

	return 0;
}
