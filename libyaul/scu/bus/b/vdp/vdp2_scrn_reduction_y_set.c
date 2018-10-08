/*
 * Copyright (c) 2012-2016 Israel Jacquez
 * See LICENSE for details.
 *
 * Israel Jacquez <mrkotfw@gmail.com>
 */

#include <vdp2/scrn.h>

#include <assert.h>

#include "vdp-internal.h"

void
vdp2_scrn_reduction_y_set(uint8_t scrn, q0_3_8_t scale)
{
#ifdef DEBUG
        /* Check if the background passed is valid */
        assert((scrn == SCRN_NBG0) ||
               (scrn == SCRN_NBG1));
#endif /* DEBUG */

        switch (scrn) {
        case SCRN_NBG0:
                _state_vdp2()->regs.zmyin0 = Q0_3_8_INT(scale);
                _state_vdp2()->regs.zmydn0 = Q0_3_8_FRAC(scale) << 8;
                break;
        case SCRN_NBG1:
                _state_vdp2()->regs.zmyin1 = Q0_3_8_INT(scale);
                _state_vdp2()->regs.zmydn1 = Q0_3_8_FRAC(scale) << 8;
                break;
        default:
                return;
        }
}