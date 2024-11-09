/*
 * SPDX-FileCopyrightText: 2024 Roland Rusch, easy-smart solution GmbH <roland.rusch@easy-smart.ch>
 * SPDX-License-Identifier: AGPL-3.0-only
 */

#ifndef LIBSMART_STM32RTC_DATETIMETYPE_HPP
#define LIBSMART_STM32RTC_DATETIMETYPE_HPP

#include "TimeType.hpp"
#include "DateType.hpp"
#include <ctime>

namespace Stm32Rtc {
    class DateTimeType : public TimeType, public DateType {
    public:
        using timestamp_t = time_t;

        DateTimeType() = default;


        void reset();

        bool isValid();

        void getStructTm(struct tm *tp);

        timestamp_t getTimestamp();

        size_t strftime(char *str, size_t count, const char *format);
    };

    inline void DateTimeType::reset() {
        DateType::reset();
        TimeType::reset();
    }

    inline bool DateTimeType::isValid() {
        return DateType::isValid() && TimeType::isValid();
    }

    inline void DateTimeType::getStructTm(struct tm *tp) {
        tp->tm_sec = this->Seconds;
        tp->tm_min = this->Minutes;
        tp->tm_hour = this->Hours;
        tp->tm_mday = this->Date;
        tp->tm_mon = this->Month - 1;
        tp->tm_year = this->Year + 2000 - 1900;
        tp->tm_wday = this->WeekDay;
        tp->tm_yday = 0;
        tp->tm_isdst = -1;
    }

    inline DateTimeType::timestamp_t DateTimeType::getTimestamp() {
        tm timeinfo{0};
        getStructTm(&timeinfo);
        return ::mktime(&timeinfo);
    }

    inline size_t DateTimeType::strftime(char *str, size_t count, const char *format) {
        tm timeinfo{0};
        getStructTm(&timeinfo);
        timeinfo.tm_mon++;
        return ::strftime(str, count, format, &timeinfo);
    }
}

#endif
