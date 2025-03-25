/*
 * SPDX-FileCopyrightText: 2024 Roland Rusch, easy-smart solution GmbH <roland.rusch@easy-smart.ch>
 * SPDX-License-Identifier: AGPL-3.0-only
 */

#ifndef LIBSMART_STM32RTC_DATETYPE_HPP
#define LIBSMART_STM32RTC_DATETYPE_HPP

#include <main.h>
#include <utility>

namespace Stm32Rtc {
    namespace HAL {
        using RTC_DateTypeDef = ::RTC_DateTypeDef;
    }

    class DateType : public HAL::RTC_DateTypeDef {
    public:
        /*
        using WEEKDAY = enum WEEKDAY: uint8_t {
            WEEKDAY_MONDAY = 1,
            WEEKDAY_TUESDAY = 2,
            WEEKDAY_WEDNESDAY = 3,
            WEEKDAY_THURSDAY = 4,
            WEEKDAY_FRIDAY = 5,
            WEEKDAY_SATURDAY = 6,
            WEEKDAY_SUNDAY = 7
        };

        using MONTH = enum MONTH: uint8_t {
            MONTH_JANUARY = 1,
            MONTH_FEBRUARY = 2,
            MONTH_MARCH = 3,
            MONTH_APRIL = 4,
            MONTH_MAY = 5,
            MONTH_JUNE = 6,
            MONTH_JULI = 7,
            MONTH_AUGUST = 8,
            MONTH_SEPTEMBER = 9,
            MONTH_OCTOBER = 10,
            MONTH_NOVEMBER = 11,
            MONTH_DECEMBER = 12
        };
*/

        DateType() : HAL::RTC_DateTypeDef{0} { ; }

        DateType(const DateType &other) = default;

        DateType(DateType &&other) noexcept
            : HAL::RTC_DateTypeDef(std::move(other)) {
        }

        DateType &operator=(const DateType &other) {
            if (this == &other)
                return *this;
            HAL::RTC_DateTypeDef::operator =(other);
            return *this;
        }

        DateType &operator=(DateType &&other) noexcept {
            if (this == &other)
                return *this;
            HAL::RTC_DateTypeDef::operator =(std::move(other));
            return *this;
        }

        void reset() { *static_cast<HAL::RTC_DateTypeDef *>(this) = {0}; }

        [[nodiscard]] bool isValid() const { return Month >= 1 && Month <= 12; };
    };
}
#endif
