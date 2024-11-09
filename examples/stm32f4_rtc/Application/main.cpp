/*
 * SPDX-FileCopyrightText: 2024 Roland Rusch, easy-smart solution GmbH <roland.rusch@easy-smart.ch>
 * SPDX-License-Identifier: AGPL-3.0-only
 */

/**
 * This file holds the main setup() and loop() functions for C++ code.
 * If a RTOS is used, loop() is called in the main task and setup() is called before RTOS initialization.
 * @see App_ThreadX_Init() in Core/Src/app_threadx.c
 */

#include "main.hpp"
#include "globals.hpp"
#include "Helper.hpp"
#include "rtc.h"
#include "RunEvery.hpp"
#include "Stm32ItmLogger.hpp"
#include "Stm32Rtc.hpp"


/**
 * @brief Setup function.
 * This function is called once at the beginning of the program before ThreadX is initialized.
 * @see main() in Core/Src/main.c
 */
void setup() {
    Stm32ItmLogger::logger.setSeverity(Stm32ItmLogger::LoggerInterface::Severity::INFORMATIONAL)
            ->println("::setup()");

    dummyCpp = 0;
    dummyCandCpp = 0;

    Serial1.begin();
    Serial1.print('\0');


    // newlocale(LC_ALL, "de_CH");


    Serial1.printf("setlocale: %s\r\n", setlocale(LC_TIME, "de_DE"));

    Stm32Rtc::TimeType time;
    time.Hours = 18;
    time.Minutes = 45;
    time.Seconds = 0;
    time.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    time.StoreOperation = RTC_STOREOPERATION_RESET;
    // if (HAL_RTC_SetTime(&hrtc, &time, RTC_FORMAT_BIN) != HAL_OK) {
    // Error_Handler();
    // }

    Stm32Rtc::DateType date;
    date.WeekDay = RTC_WEEKDAY_FRIDAY;
    date.Month = RTC_MONTH_NOVEMBER;
    date.Date = 8;
    date.Year = 24;
    // if (HAL_RTC_SetDate(&hrtc, &date, RTC_FORMAT_BIN) != HAL_OK) {
    // Error_Handler();
    // }
}


/**
 * @brief This function is the main loop that executes continuously.
 * The function is called inside the mainLoopThread().
 * @see mainLoopThread() in AZURE_RTOS/App/app_azure_rtos.c
 */
void loop() {
    Serial1.loop();

    dummyCpp++;
    dummyCandCpp++;

    static Stm32Common::RunEvery re1;
    if (re1.loop(1000)) {
        // Stm32Rtc::TimeType time;
        // Stm32Rtc::DateType date;
        Stm32Rtc::DateTimeType dateTime;

        // HAL_RTC_GetTime(&hrtc, &dateTime, RTC_FORMAT_BIN);
        // HAL_RTC_GetDate(&hrtc, &dateTime, RTC_FORMAT_BIN);

        rtc.getDateTime(&dateTime);

        Serial1.printf("-> RTC Value: %04d-%02d-%02d %02d:%02d:%02d\r\n",
                       2000 + dateTime.Year, dateTime.Month, dateTime.Date,
                       dateTime.Hours, dateTime.Minutes, dateTime.Seconds);
        Serial1.printf("timestamp: %d\r\n", dateTime.getTimestamp());
        char str[100]{0};
        dateTime.strftime(str, sizeof(str), "%Y-%m-%d %H:%M:%S");
        Serial1.printf("strftime: %s\r\n", str);

        std::memset(str, 0, sizeof(str));
        dateTime.strftime(str, sizeof(str), "%H:%M:%S, %e. %B %Y");
        Serial1.printf("strftime: %s\r\n", str);

        std::memset(str, 0, sizeof(str));
        dateTime.strftime(str, sizeof(str), "%X, %x");
        Serial1.printf("strftime: %s\r\n", str);

        tm timeinfo{0};
        dateTime.getStructTm(&timeinfo);
        Serial1.printf("asctime: %s\r\n", asctime(&timeinfo));

        Serial1.println();
    }

    static Stm32Common::RunEvery blinker;
    if (blinker.loop(300)) {
        HAL_GPIO_TogglePin(LED1_GRN_GPIO_Port, LED1_GRN_Pin);
    }
}


/**
 * @brief This function handles fatal errors.
 * @see Error_Handler() in Core/Src/main.c
 */
void errorHandler() {
    HAL_GPIO_WritePin(LED1_GRN_GPIO_Port, LED1_GRN_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED2_ORG_GPIO_Port, LED2_ORG_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED3_RED_GPIO_Port, LED3_RED_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED4_BLU_GPIO_Port, LED4_BLU_Pin, GPIO_PIN_RESET);

    while (true) {
        for (uint32_t i = (SystemCoreClock / 10); i > 0; i--) { UNUSED(i); }
        HAL_GPIO_TogglePin(LED1_GRN_GPIO_Port, LED1_GRN_Pin);
        HAL_GPIO_TogglePin(LED2_ORG_GPIO_Port, LED2_ORG_Pin);
        HAL_GPIO_TogglePin(LED3_RED_GPIO_Port, LED3_RED_Pin);
        HAL_GPIO_TogglePin(LED4_BLU_GPIO_Port, LED4_BLU_Pin);
    }
}
