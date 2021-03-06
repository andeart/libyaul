/*
 * Copyright (c) 2012-2016 Israel Jacquez
 * See LICENSE for details.
 *
 * Israel Jacquez <mrkotfw@gmail.com>
 */

#ifndef _VDP1_CMDT_H_
#define _VDP1_CMDT_H_

#include <sys/cdefs.h>

#include <stdint.h>

#include <scu.h>

#include <vdp1/map.h>

#include <vdp2/sprite.h>

#include <color.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define VDP1_CMDT_DRAW_MODE_STRUCT_DECLARE(n)                                  \
        union {                                                                \
                struct {                                                       \
                        unsigned int msb:1;                       /* Bit 15 */ \
                        unsigned int :2;                                       \
                        unsigned int high_speed_shrink:1;         /* Bit 12 */ \
                        unsigned int pre_clipping:1;              /* Bit 11 */ \
                        unsigned int user_clipping:2;          /* Bits 10-9 */ \
                        unsigned int mesh:1;                       /* Bit 8 */ \
                        unsigned int end_code:1;                   /* Bit 7 */ \
                        unsigned int transparent_pixel:1;          /* Bit 6 */ \
                        unsigned int color_mode:3;              /* Bits 5-3 */ \
                        unsigned int cc_mode:3;                 /* Bits 2-0 */ \
                } __aligned(2);                                                \
                                                                               \
                uint16_t raw;                                                  \
        } __CONCAT(n, _mode)

#define VDP1_CMDT_SPRITE_TYPE_DECLARE(n)                                       \
        union {                                                                \
                struct vdp2_sprite_type_0 type_0;                              \
                struct vdp2_sprite_type_1 type_1;                              \
                struct vdp2_sprite_type_2 type_2;                              \
                struct vdp2_sprite_type_3 type_3;                              \
                struct vdp2_sprite_type_4 type_4;                              \
                struct vdp2_sprite_type_5 type_5;                              \
                struct vdp2_sprite_type_6 type_6;                              \
                struct vdp2_sprite_type_7 type_7;                              \
                struct vdp2_sprite_type_8 type_8;                              \
                struct vdp2_sprite_type_9 type_9;                              \
                struct vdp2_sprite_type_a type_a;                              \
                struct vdp2_sprite_type_b type_b;                              \
                struct vdp2_sprite_type_c type_c;                              \
                struct vdp2_sprite_type_d type_d;                              \
                struct vdp2_sprite_type_e type_e;                              \
                struct vdp2_sprite_type_f type_f;                              \
                                                                               \
                uint16_t raw;                                                  \
        } __CONCAT(n, _sprite_type)

struct vdp1_cmdt;

struct vdp1_cmdt_list {
        struct vdp1_cmdt *cmdts;
        struct vdp1_cmdt *cmdt;
        uint16_t count;
} __aligned(4);

struct vdp1_cmdt {
        uint16_t cmd_ctrl;
        uint16_t cmd_link;
        uint16_t cmd_pmod;
        uint16_t cmd_colr;
        uint16_t cmd_srca;
        uint16_t cmd_size;
        int16_t cmd_xa;
        int16_t cmd_ya;
        int16_t cmd_xb;
        int16_t cmd_yb;
        int16_t cmd_xc;
        int16_t cmd_yc;
        int16_t cmd_xd;
        int16_t cmd_yd;
        uint16_t cmd_grda;
        uint16_t reserved;
} __aligned(32);

struct vdp1_cmdt_sprite {
        union {
#define CMDT_ZOOM_POINT_UPPER_LEFT      0x0030
#define CMDT_ZOOM_POINT_UPPER_CENTER    0x0050
#define CMDT_ZOOM_POINT_UPPER_RIGHT     0x0090
#define CMDT_ZOOM_POINT_CENTER_LEFT     0x0210
#define CMDT_ZOOM_POINT_CENTER          0x0410
#define CMDT_ZOOM_POINT_CENTER_RIGHT    0x0810
#define CMDT_ZOOM_POINT_LOWER_LEFT      0x2010
#define CMDT_ZOOM_POINT_LOWER_CENTER    0x4010
#define CMDT_ZOOM_POINT_LOWER_RIGHT     0x8010

                struct {
                        unsigned int lower_right:1;
                        unsigned int lower_center:1;
                        unsigned int lower_left:1;
                        unsigned int :1;
                        unsigned int center_right:1;
                        unsigned int center:1;
                        unsigned int center_left:1;
                        unsigned int :1;
                        unsigned int upper_right:1;
                        unsigned int upper_center:1;
                        unsigned int upper_left:1;
                        unsigned int enable:1;
                } __aligned(2);

                uint16_t raw;
        } cs_zoom_point;

        VDP1_CMDT_DRAW_MODE_STRUCT_DECLARE(cs);

        union {
                /* Mode 0, 2, 3, and 4 */
                VDP1_CMDT_SPRITE_TYPE_DECLARE(cs);

                /* Mode 1 */
                uint32_t cs_clut;
        };

        uint32_t cs_char;
        uint16_t cs_width;
        uint16_t cs_height;

        union {
                struct {
                        int16_t x;
                        int16_t y;
                } cs_position;

                struct {
                        struct {
                                int16_t x;
                                int16_t y;
                        } point;

                        struct {
                                int16_t x;
                                int16_t y;
                        } display;
                } cs_zoom;

                struct {
                        struct {
                                int16_t x;
                                int16_t y;
                        } a, b, c, d;
                } cs_vertex;

                int16_t cs_vertices[8];
        };

        uint32_t cs_grad;
};

struct vdp1_cmdt_polygon {
        VDP1_CMDT_DRAW_MODE_STRUCT_DECLARE(cp);

        union {
                VDP1_CMDT_SPRITE_TYPE_DECLARE(cp);

                color_rgb555_t cp_color;
        };

        union {
                struct {
                        struct {
                                int16_t x;
                                int16_t y;
                        } a, b, c, d;
                } cp_vertex;

                int16_t cp_vertices[8];
        };

        uint32_t cp_grad;
};

struct vdp1_cmdt_polyline {
        VDP1_CMDT_DRAW_MODE_STRUCT_DECLARE(cl);

        union {
                VDP1_CMDT_SPRITE_TYPE_DECLARE(cl);

                color_rgb555_t cl_color;
        };

        union {
                struct {
                        struct {
                                int16_t x;
                                int16_t y;
                        } a, b, c, d;
                } cl_vertex;

                int16_t cl_vertices[8];
        };

        uint32_t cl_grad;
};

struct vdp1_cmdt_line {
        VDP1_CMDT_DRAW_MODE_STRUCT_DECLARE(cl);

        union {
                VDP1_CMDT_SPRITE_TYPE_DECLARE(cl);

                color_rgb555_t cl_color;
        };

        union {
                struct {
                        struct {
                                int16_t x;
                                int16_t y;
                        } a, b;
                } cl_vertex;

                int16_t cl_vertices[4];
        };

        uint32_t cl_grad;
};

struct vdp1_cmdt_local_coord {
        struct {
                int16_t x;
                int16_t y;
        } lc_coord;
};

struct vdp1_cmdt_system_clip_coord {
        struct {
                int16_t x;
                int16_t y;
        } scc_coord;
};

struct vdp1_cmdt_user_clip_coord {
        struct {
                int16_t x;
                int16_t y;
        } ucc_coords[2];
};

static inline uint16_t __always_inline
vdp1_cmdt_current_get(void)
{
        return MEMORY_READ(16, VDP1(COPR)) >> 2;
}

static inline uint16_t __always_inline
vdp1_cmdt_last_get(void)
{
        return MEMORY_READ(16, VDP1(LOPR)) >> 2;
}

extern struct vdp1_cmdt_list *vdp1_cmdt_list_alloc(uint16_t);
extern void vdp1_cmdt_list_free(struct vdp1_cmdt_list *);
extern void vdp1_cmdt_list_init(struct vdp1_cmdt_list *, struct vdp1_cmdt *, uint16_t);
extern void vdp1_cmdt_list_reset(struct vdp1_cmdt_list *);

extern struct vdp1_cmdt *vdp1_cmdt_base_get(void);

extern void vdp1_cmdt_normal_sprite_draw(struct vdp1_cmdt_list *, const struct vdp1_cmdt_sprite *);
extern void vdp1_cmdt_scaled_sprite_draw(struct vdp1_cmdt_list *, const struct vdp1_cmdt_sprite *);
extern void vdp1_cmdt_distorted_sprite_draw(struct vdp1_cmdt_list *, const struct vdp1_cmdt_sprite *);
extern void vdp1_cmdt_polygon_draw(struct vdp1_cmdt_list *, const struct vdp1_cmdt_polygon *);
extern void vdp1_cmdt_polyline_draw(struct vdp1_cmdt_list *, const struct vdp1_cmdt_polyline *);
extern void vdp1_cmdt_line_draw(struct vdp1_cmdt_list *, const struct vdp1_cmdt_line *);
extern void vdp1_cmdt_user_clip_coord_set(struct vdp1_cmdt_list *, const struct vdp1_cmdt_user_clip_coord *);
extern void vdp1_cmdt_system_clip_coord_set(struct vdp1_cmdt_list *, const struct vdp1_cmdt_system_clip_coord *);
extern void vdp1_cmdt_local_coord_set(struct vdp1_cmdt_list *, const struct vdp1_cmdt_local_coord *);
extern void vdp1_cmdt_end(struct vdp1_cmdt_list *);

#undef VDP1_CMDT_DRAW_MODE_STRUCT_DECLARE
#undef VDP1_CMDT_SPRITE_TYPE_DECLARE

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !_VDP1_CMDT_H_ */
