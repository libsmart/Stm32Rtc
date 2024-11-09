/*
 * SPDX-FileCopyrightText: 2024 Roland Rusch, easy-smart solution GmbH <roland.rusch@easy-smart.ch>
 * SPDX-License-Identifier: AGPL-3.0-only
 */

/**
 * This file holds exports for the global variables, defined in globals.cpp.
 * @see globals.cpp
 */

#ifndef EASY_SMART_STM32_skeleton_GLOBALS_HPP
#define EASY_SMART_STM32_skeleton_GLOBALS_HPP

#include "globals.h"
#include <cstdint>
#include "Stm32ItmLogger.hpp"

#include "usart.h"
#include "Driver/Stm32HalUartItDriver.hpp"
#include "ezShell/Shell.hpp"

#include "rtc.h"
#include "Stm32Rtc.hpp"

#ifdef __cplusplus
extern "C" {
#endif

//    uint32_t micros();
extern uint32_t dummyCpp;

inline Stm32ItmLogger::Stm32ItmLogger &Logger = Stm32ItmLogger::logger;

inline Stm32Common::StreamSession::Manager<Stm32Shell::ezShell::Shell, 1> microrlStreamSessionManager(&Logger);
inline Stm32Serial::Stm32HalUartItDriver uart1Driver(&huart1, "uart1Driver");
inline Stm32Serial::Stm32Serial Serial1(&uart1Driver, &microrlStreamSessionManager);


inline Stm32Rtc::Rtc rtc(&hrtc, &Stm32ItmLogger::logger);

#ifdef __cplusplus
}
#endif

#endif //EASY_SMART_STM32_skeleton_GLOBALS_HPP
