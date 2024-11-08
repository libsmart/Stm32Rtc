/*
 * SPDX-FileCopyrightText: 2024 Roland Rusch, easy-smart solution GmbH <roland.rusch@easy-smart.ch>
 * SPDX-License-Identifier: AGPL-3.0-only
 */

/**
 * This file holds global macro defines. It can be imported in C and C++ files.
 * Do not put global variables in this file.
 * @see globals.cpp
 * @see globals.c
 */

#ifndef EASY_SMART_STM32_skeleton_DEFINES_H
#define EASY_SMART_STM32_skeleton_DEFINES_H

/** Name of the firmware. */
#define FIRMWARE_NAME "stm32f4_rtc"

/** Copyright of the firmware */
#define FIRMWARE_COPY "(c) 2024 easy-smart solution GmbH"

/** Build time of the firmware */
#define FIRMWARE_BUILDTIME BUILD_TIME

/** Version of the firmware. */
#ifndef FIRMWARE_VERSION
#ifdef VER_NEXT_ALPHA
#define FIRMWARE_VERSION VER_NEXT_ALPHA
#else
#define FIRMWARE_VERSION "0.0.0-alpha+UNKNOWN"
#endif
#endif




/* Some useful defines */
//#define min(a, b) ((a)<(b)?(a):(b))
//#define max(a, b) ((a)>(b)?(a):(b))
//#define millis HAL_GetTick



#endif //EASY_SMART_STM32_skeleton_DEFINES_H
