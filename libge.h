// SPDX-License-Identifier:	LGPL-2.1+

#define LIBGE_IOCTL_INFO	0

struct ge_cntx {
	int fd;
};

int libge_open(struct ge_cntx *ge);
int libge_close(struct ge_cntx *ge);
