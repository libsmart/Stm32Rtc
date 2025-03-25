/*
 * SPDX-FileCopyrightText: 2024 Roland Rusch, easy-smart solution GmbH <roland.rusch@easy-smart.ch>
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef LIBSMART_STM32RTC_TIMETYPE_HPP
#define LIBSMART_STM32RTC_TIMETYPE_HPP

#include <main.h>
#include <utility>

namespace Stm32Rtc {
    namespace HAL {
        using RTC_TimeTypeDef = ::RTC_TimeTypeDef;
    }

    class TimeType : public HAL::RTC_TimeTypeDef {
    public:
        TimeType() : HAL::RTC_TimeTypeDef{0} { ; }

        TimeType(const TimeType &other) = default;

        TimeType(TimeType &&other) noexcept
            : HAL::RTC_TimeTypeDef(std::move(other)) {
        }

        TimeType &operator=(const TimeType &other) {
            if (this == &other)
                return *this;
            HAL::RTC_TimeTypeDef::operator =(other);
            return *this;
        }

        TimeType &operator=(TimeType &&other) noexcept {
            if (this == &other)
                return *this;
            HAL::RTC_TimeTypeDef::operator =(std::move(other));
            return *this;
        }

        void reset() { *static_cast<HAL::RTC_TimeTypeDef *>(this) = {0}; }

        static bool isValid() { return true; }
    };
}
#endif
