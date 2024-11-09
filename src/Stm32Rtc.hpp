/*
 * SPDX-FileCopyrightText: 2024 Roland Rusch, easy-smart solution GmbH <roland.rusch@easy-smart.ch>
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef LIBSMART_STM32RTC_STM32RTC_HPP
#define LIBSMART_STM32RTC_STM32RTC_HPP

#include "TimeType.hpp"
#include "DateType.hpp"
#include "DateTimeType.hpp"
#include "Loggable.hpp"

namespace Stm32Rtc {
    namespace HAL {
        using HAL_StatusTypeDef = ::HAL_StatusTypeDef;
        using RTC_HandleTypeDef = ::RTC_HandleTypeDef;
    }

    class Rtc : public Stm32ItmLogger::Loggable {
    public:
        Rtc() = delete;

        explicit Rtc(HAL::RTC_HandleTypeDef *RTC_Handle)
            : Rtc(RTC_Handle, &Stm32ItmLogger::emptyLogger) { ; }

        Rtc(HAL::RTC_HandleTypeDef *RTC_Handle, Stm32ItmLogger::LoggerInterface *logger)
            : Loggable(logger), RTC_Handle{RTC_Handle} { ; }


        /**
         * Retrieves the current time from the RTC and stores it in the provided TimeType structure.
         * If the RTC instance is not initialized, or there is an error retrieving the time or date,
         * the time structure is reset.
         *
         * @param time Pointer to a TimeType structure where the retrieved time will be stored.
         */
        void getTime(TimeType *time);

        /**
         * Retrieves the current date from the RTC and stores it in the provided DateType structure.
         * If the RTC instance is not initialized, or there is an error retrieving the date or time,
         * the date structure is reset.
         *
         * @param date Pointer to a DateType structure where the retrieved date will be stored.
         */
        void getDate(DateType *date);

        /**
         * Retrieves the current date and time from the RTC and stores it in the provided DateTimeType structure.
         * If the RTC instance is not initialized, or there is an error retrieving the date or time,
         * the dateTime structure is reset.
         *
         * @param dateTime Pointer to a DateTimeType structure where the retrieved date and time will be stored.
         */
        void getDateTime(DateTimeType *dateTime);




    private:
        /**
         * Acquires the current time from the RTC and populates the given HAL::RTC_TimeTypeDef structure.
         * If the RTC instance is uninitialized, the method returns an error status.
         *
         * @param halTime Pointer to a HAL::RTC_TimeTypeDef structure to be populated with the current time.
         * @return HAL::HAL_StatusTypeDef indicating the success or failure of the operation.
         */
        HAL::HAL_StatusTypeDef getRtcTime(HAL::RTC_TimeTypeDef *halTime);

        /**
         * Retrieves the current date from the RTC and stores it in the provided RTC_DateTypeDef structure.
         * If the RTC instance is not initialized, the function returns HAL_ERROR.
         *
         * @param halDate Pointer to an RTC_DateTypeDef structure where the retrieved date will be stored.
         * @return HAL_StatusTypeDef indicating the status of the operation: HAL_OK if successful, HAL_ERROR otherwise.
         */
        HAL::HAL_StatusTypeDef getRtcDate(HAL::RTC_DateTypeDef *halDate);

        /** The handle to the RTC */
        RTC_HandleTypeDef *RTC_Handle;
    };
}
#endif
