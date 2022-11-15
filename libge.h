// SPDX-License-Identifier:	LGPL-2.1+

#define LIBGE_IOCTL_INFO	0

/* Probing */
struct ge_info {
	uint32_t caps;
};

struct ge_cntx {
	int fd;
	struct ge_info info;
};

/* The meat and potatoes */
enum ge_op {
	GE_OP_BITBLT,
};

#define GE_ROTATION_0	0
#define GE_ROTATION_90	1
#define GE_ROTATION_180	2
#define GE_ROTATION_270	3

struct ge_bitblt {
	unsigned int rotation;
};

struct ge_opdata {
	enum ge_op op;
	void *src, *dst;
	uint32_t src_width, src_height, dst_width, dst_height;
	uint32_t src_pitch, dst_pitch;
	uint32_t src_fourcc, dst_fourcc;
	union {
		struct ge_bitblt bitblt;
	};
};

int libge_open(struct ge_cntx *ge);
int libge_queue_job(struct ge_cntx *ge, struct ge_opdata *opdata, uint32_t *tag);
int libge_query_job(struct ge_cntx *ge, uint32_t tag);
int libge_close(struct ge_cntx *ge);
