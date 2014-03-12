/*
 * Copyright (c) 2012 Israel Jacquez
 * See LICENSE for details.
 *
 * Israel Jacquez <mrkotfw@gmail.com>
 */

#include <smpc/peripheral.h>

#include "smpc-internal.h"

struct smpc_peripheral_analog *
smpc_peripheral_analog_port(uint8_t port)
{
        struct smpc_peripheral_analog *port_1;
        struct smpc_peripheral_analog *port_2;

        port_1 = (struct smpc_peripheral_analog *)smpc_peripheral_port_1.peripheral;
        port_2 = (struct smpc_peripheral_analog *)smpc_peripheral_port_2.peripheral;

        switch (port) {
        case 1:
                return port_1;
        case 2:
                return port_2;
        default:
                return NULL;
        }
}
