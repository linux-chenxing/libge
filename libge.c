// SPDX-License-Identifier:	LGPL-2.1+
#include <stdint.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

#include "libge.h"

int libge_open(struct ge_cntx *ge)
{
	int fd, ret;

	fd = open("/dev/mstar-ge", O_RDWR);
	if (fd < 0)
		return errno;

	ge->fd = fd;

	ret = ioctl(ge->fd, MSTAR_GE_IOCTL_INFO, &ge->info);
	if (ret)
		goto out;

out:
	return ret;
}

int libge_queue_job(struct ge_cntx *ge,
					struct mstar_ge_opdata *opdata,
					unsigned int num_ops,
					int src_fd,
					int src_w, int src_h, __u32 src_fourcc, unsigned int src_pitch,
					int dst_fd,
					int dst_w, int dst_h, __u32 dst_fourcc, unsigned int dst_pitch,
					unsigned long *tag)
{
	struct mstar_ge_job_request req;
	struct mstar_ge_buf bufs[2];
	int ret, num_buf = 0;

	if (src_fd > 0) {
		bufs[num_buf].fd = src_fd;
		bufs[num_buf].cfg.width = src_w;
		bufs[num_buf].cfg.height = src_h;
		bufs[num_buf].cfg.fourcc = src_fourcc;
		bufs[num_buf].cfg.pitch = src_pitch;
		num_buf++;
	}

	if (dst_fd > 0) {
		bufs[num_buf].fd = dst_fd;
		bufs[num_buf].cfg.width = dst_w;
		bufs[num_buf].cfg.height = dst_h;
		bufs[num_buf].cfg.fourcc = dst_fourcc;
		bufs[num_buf].cfg.pitch = dst_pitch;
		num_buf++;
	}

	if (num_buf == 0)
		return -EINVAL;

	req.tag = tag;
	req.ops = opdata;
	req.num_ops = num_ops;
	req.bufs = &bufs;
	req.num_bufs = num_buf;

	ret = ioctl(ge->fd, MSTAR_GE_IOCTL_QUEUE, &req);
	if (ret)
		goto out;

out:
	return ret;
}

int libge_query_job(struct ge_cntx *ge, unsigned long tag)
{
	int ret;

	ret = ioctl(ge->fd, MSTAR_GE_IOCTL_QUERY, &tag);
	if (ret)
		goto out;

out:
	return ret;
}

int libge_close(struct ge_cntx *ge)
{
	close(ge->fd);

	return 0;
}
