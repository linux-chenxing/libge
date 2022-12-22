// SPDX-License-Identifier:	LGPL-2.1+

#include <linux/types.h>
#include <drm/mstar_ge.h>
#include <stdbool.h>

struct ge_cntx {
	int fd;
	struct mstar_ge_info info;
};

int libge_open(struct ge_cntx *ge);
int libge_queue_job(struct ge_cntx *ge,
					struct mstar_ge_opdata *opdata,
					unsigned int num_ops,
					int src_fd,
					int src_w, int src_h, __u32 src_fourcc, unsigned int src_pitch,
					int dst_fd,
					int dst_w, int dst_h, __u32 dst_fourcc, unsigned int dst_pitch,
					unsigned long *tag);
int libge_query_job(struct ge_cntx *ge, unsigned long tag);
int libge_close(struct ge_cntx *ge);

static inline void libge_filljob_line(struct mstar_ge_opdata *opdata,
										  unsigned int x0,
										  unsigned int y0,
										  unsigned int x1,
										  unsigned int y1,
										  unsigned int a,
										  unsigned int r,
										  unsigned int g,
										  unsigned int b)
{
	opdata->op = MSTAR_GE_OP_LINE;

	opdata->line.x0 = x0;
	opdata->line.y0 = y0;
	opdata->line.x1 = x1;
	opdata->line.y1 = y1;

	opdata->line.start_color.a = a;
	opdata->line.start_color.r = r;
	opdata->line.start_color.g = g;
	opdata->line.start_color.b = b;
}

static inline void libge_filljob_fillrect(struct mstar_ge_opdata *opdata,
										  unsigned int x0,
										  unsigned int y0,
										  unsigned int x1,
										  unsigned int y1,
										  unsigned int a,
										  unsigned int r,
										  unsigned int g,
										  unsigned int b)
{
	opdata->op = MSTAR_GE_OP_RECTFILL;

	opdata->rectfill.x0 = x0;
	opdata->rectfill.y0 = y0;
	opdata->rectfill.x1 = x1;
	opdata->rectfill.y1 = y1;

	opdata->rectfill.start_color.a = a;
	opdata->rectfill.start_color.r = r;
	opdata->rectfill.start_color.g = g;
	opdata->rectfill.start_color.b = b;
}

static inline void libge_filljob_blit_fliprot(__u32 *flags,
											  bool src_v_flip,
											  bool dst_h_flip,
											  bool dst_v_flip,
											  unsigned int rotation)
{
	__u32 tmp = 0;

	if (src_v_flip)
		tmp |= MSTAR_GE_FLIP_SRC_V;
	if (dst_h_flip)
		tmp |= MSTAR_GE_FLIP_DST_H;
	if (dst_v_flip)
		tmp |= MSTAR_GE_FLIP_DST_V;

	tmp |= (rotation & MSTAR_GE_ROTATION_MASK);

	*flags = tmp;
}

static inline void libge_filljob_blit(struct mstar_ge_opdata *opdata,
								      unsigned int src_x0,
								      unsigned int src_y0,
									  unsigned int dst_x0,
									  unsigned int dst_y0,
								      unsigned int dst_x1,
								      unsigned int dst_y1,
									  bool src_v_flip,
									  bool dst_h_flip,
									  bool dst_v_flip,
									  unsigned int rotation)
{
	opdata->op = MSTAR_GE_OP_BITBLT;

	opdata->bitblt.src_x0 = src_x0;
	opdata->bitblt.src_y0 = src_y0;
	opdata->bitblt.dst_x0 = dst_x0;
	opdata->bitblt.dst_y0 = dst_y0;
	opdata->bitblt.dst_x1 = dst_x1;
	opdata->bitblt.dst_y1 = dst_y1;

	libge_filljob_blit_fliprot(&opdata->bitblt.fliprot,
							   src_v_flip,
							   dst_h_flip,
							   dst_v_flip,
							   rotation);
}

static inline void libge_filljob_strblit(struct mstar_ge_opdata *opdata,
								      unsigned int src_x0,
								      unsigned int src_y0,
									  unsigned int src_x1,
									  unsigned int src_y1,
									  unsigned int dst_x0,
									  unsigned int dst_y0,
								      unsigned int dst_x1,
								      unsigned int dst_y1,
									  bool src_v_flip,
									  bool dst_h_flip,
									  bool dst_v_flip,
									  enum mstar_ge_rotation rotation)
{
	opdata->op = MSTAR_GE_OP_STRBLT;

	opdata->strblt.src_x0 = src_x0;
	opdata->strblt.src_y0 = src_y0;
	opdata->strblt.src_x1 = src_x1;
	opdata->strblt.src_y1 = src_y1;

	opdata->strblt.dst_x0 = dst_x0;
	opdata->strblt.dst_y0 = dst_y0;
	opdata->strblt.dst_x1 = dst_x1;
	opdata->strblt.dst_y1 = dst_y1;

	libge_filljob_blit_fliprot(&opdata->strblt.fliprot,
							   src_v_flip,
							   dst_h_flip,
							   dst_v_flip,
							   rotation);
}
