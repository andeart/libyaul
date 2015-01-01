/*
 * Copyright (c) 2012-2014 Israel Jacquez
 * See LICENSE for details.
 *
 * Israel Jacquez <mrkotfw@gmail.com>
 */

#include <yaul.h>
#include <fixmath.h>

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int32_t lut_cos[512];
int32_t lut_sin[512];

char *text = NULL;
size_t text_len = 0;

extern uint8_t root_romdisk[];

static void *romdisk = NULL;

void
init(void)
{
        static bool initialized = false;

#ifdef DEBUG
        static char angle_str[32];
        static char str[512];
#endif /* DEBUG */

        if (initialized) {
                return;
        }
        initialized = true;

        fix16_t brad_const;
        brad_const = fix16_from_float(360.0f / 512.0f);

        /* Build a sine wave table */
        uint32_t angle_idx;
        for (angle_idx = 0; angle_idx < 512; angle_idx++) {
                fix16_t angle_deg;
                angle_deg = fix16_from_int((int)angle_idx);

                fix16_t angle_brad;
                angle_brad = fix16_mul(angle_deg, brad_const);

                /*
                 * angle_brad = angle * (360.0 / 512.0)
                 * angle_rad = (angle_brad * pi) / 180.0 */
                fix16_t angle_rad;
                angle_rad = fix16_div(fix16_mul(angle_brad, fix16_pi),
                    fix16_from_int(180));

                lut_sin[angle_idx] = fix16_to_int(
                        fix16_mul(fix16_sin(angle_rad), fix16_from_int(4096)));
                lut_cos[angle_idx] = fix16_to_int(
                        fix16_mul(fix16_cos(angle_rad), fix16_from_int(4096)));

#ifdef DEBUG
                fix16_to_str(angle_rad, angle_str, 7);
                (void)sprintf(str, "Deg. %3i - %s\n", (int)angle_idx,
                    angle_str);

                cons_write(&cons, str);
                if (((angle_idx + 1) % 28) == 0) {
                        cons_write(&cons, "[H[2J");
                }
#endif /* DEBUG */
        }

        text_len = common_round_pow2(CONS_COLS * CONS_ROWS);
        text = (char *)malloc(text_len);
        assert(text != NULL);
        memset(text, '\0', text_len);

        romdisk_init();
        romdisk = romdisk_mount("/", root_romdisk);
        assert(romdisk != NULL);
}

void
sleep(fix16_t seconds)
{
        uint16_t frames;
        frames = fix16_to_int(fix16_mul(fix16_from_int(60), seconds));

        uint16_t t;
        for (t = 0; t < frames; t++) {
                vdp2_tvmd_vblank_out_wait();
                vdp2_tvmd_vblank_in_wait();
        }
}

void *
fs_open(const char *path)
{
        assert(romdisk != NULL);

        void *fh;

        fh = romdisk_open(romdisk, path, O_RDONLY);
        assert(fh != NULL);

        return fh;
}

void
fs_close(void *fh)
{
        assert(romdisk != NULL);
        assert(fh != NULL);

        romdisk_close(fh);
}

void
fs_read(void *fh, void *dst)
{
        assert(romdisk != NULL);
        assert(fh != NULL);

        size_t len;

        len = romdisk_read(fh, dst, romdisk_total(fh));
        assert(len == romdisk_total(fh));
}

size_t
fs_size(void *fh)
{
        assert(romdisk != NULL);
        assert(fh != NULL);

        return romdisk_total(fh);
}