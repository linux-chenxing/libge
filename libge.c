// SPDX-License-Identifier:	LGPL-2.1+
#include <stdint.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "libge.h"

int libge_open(struct ge_cntx *ge)
{
	int fd, ret;
	struct ge_info info;

	fd = open("/dev/mstar-ge", O_RDWR);
	if (fd < 0)
		return errno;

	ge->fd = fd;

	ret = ioctl(ge->fd, LIBGE_IOCTL_INFO, &info);
	if (ret)
		goto out;

	memcpy(&ge->info, &info, sizeof(info));

out:
	return ret;
}

int libge_close(struct ge_cntx *ge)
{
	close(ge->fd);

	return 0;
}
