/*
 * SPDX-FileCopyrightText: 2024 Roland Rusch, easy-smart solution GmbH <roland.rusch@easy-smart.ch>
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <main.h>

#include "../Lib/Stm32Common/src/libsmart_config.dist.hpp"
#include "../Lib/Stm32ItmLogger/src/libsmart_config.dist.hpp"
#include "../Lib/Stm32Serial/src/libsmart_config.dist.hpp"
#include "../Lib/Stm32Shell/src/libsmart_config.dist.hpp"

// #undef LIBSMART_ITM_LOGGER_OVER_UART
// #define LIBSMART_ITM_LOGGER_OVER_UART huart1
// #undef LIBSMART_ITM_LOGGER_OVER_ITM

#define LIBSMART_STM32SERIAL_ENABLE_HAL_UART_IT_DRIVER

