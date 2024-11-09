/*
 * SPDX-FileCopyrightText: 2024 Roland Rusch, easy-smart solution GmbH <roland.rusch@easy-smart.ch>
 * SPDX-License-Identifier: AGPL-3.0-only
 */

#include <main.h>
#include <utility>

#ifndef LIBSMART_STM32RTC_DATETYPE_HPP
#define LIBSMART_STM32RTC_DATETYPE_HPP

namespace Stm32Rtc {
    namespace HAL {
        using RTC_DateTypeDef = ::RTC_DateTypeDef;
    }

    class DateType : public HAL::RTC_DateTypeDef {
    public:
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

        bool isValid() { return Month >= 1 && Month <= 12; };


    };
}
#endif
