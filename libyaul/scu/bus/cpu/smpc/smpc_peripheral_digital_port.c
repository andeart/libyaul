/*
 * Copyright (c) 2012-2016 Israel Jacquez
 * See LICENSE for details.
 *
 * Israel Jacquez <mrkotfw@gmail.com>
 */

#include <assert.h>

#include <smpc/peripheral.h>

#include "smpc-internal.h"

void
smpc_peripheral_digital_port(uint8_t port, struct smpc_peripheral_digital * const peripheral)
{
        struct smpc_peripheral *port_peripheral;

        assert((port == 1) || (port == 2));

        switch (port) {
        case 1:
                port_peripheral = smpc_peripheral_port_1.peripheral;
                break;
        case 2:
                port_peripheral = smpc_peripheral_port_2.peripheral;
                break;
        }

        smpc_peripheral_digital_get(port_peripheral, peripheral);
}
