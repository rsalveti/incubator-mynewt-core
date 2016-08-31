/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
#include <stdint.h>
#include <stddef.h>

#include "bsp/bsp.h"
#include <hal/hal_bsp.h>
#include "mcu/nrf52_hal.h"

static const struct nrf52_uart_cfg uart_cfg = {
    .suc_pin_tx = 13,
    .suc_pin_rx = 15,
    .suc_pin_rts = 14,
    .suc_pin_cts = 12
};

/*
 * What memory to include in coredump.
 */
static const struct bsp_mem_dump dump_cfg[] = {
    [0] = {
	.bmd_start = &_ram_start,
        .bmd_size = RAM_SIZE
    }
};

const struct nrf52_uart_cfg *
bsp_uart_config(void)
{
    return &uart_cfg;
}

const struct hal_flash *
bsp_flash_dev(uint8_t id)
{
    /*
     * Internal flash mapped to id 0.
     */
    if (id != 0) {
        return NULL;
    }
    return &nrf52k_flash_dev;
}

const struct bsp_mem_dump *
bsp_core_dump(int *area_cnt)
{
    *area_cnt = sizeof(dump_cfg) / sizeof(dump_cfg[0]);
    return dump_cfg;
}
