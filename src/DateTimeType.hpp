/*
 * SPDX-FileCopyrightText: 2024 Roland Rusch, easy-smart solution GmbH <roland.rusch@easy-smart.ch>
 * SPDX-License-Identifier: AGPL-3.0-only
 */

#ifndef LIBSMART_STM32RTC_DATETIMETYPE_HPP
#define LIBSMART_STM32RTC_DATETIMETYPE_HPP

#include "TimeType.hpp"
#include "DateType.hpp"
#include <ctime>
#include <algorithm>
#include <climits>
#include <charconv>
#include "String/FixedString.hpp"

namespace Stm32Rtc {
    class DateTimeType : public TimeType, public DateType {
    public:
        using timestamp_t = time_t;

        DateTimeType() = default;

        explicit DateTimeType(timestamp_t timestamp) { setTimestamp(timestamp); }

        void reset();

        bool isValid();

        void getStructTm(struct tm *tp);

        void setFromStructTm(const struct tm *tp);

        timestamp_t getTimestamp();

        void setTimestamp(timestamp_t timestamp);

        size_t strftime(char *str, size_t count, const char *format);

        template<std::size_t N>
        size_t strftime(Stm32Common::String::FixedString<N> &fixedString, const char *format);

        static timestamp_t mktime(struct tm *tp);

        bool setFromIso8601(const char *datetimestring);
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
        tp->tm_mon = std::min(std::max(this->Month - 1, 0), 11);
        tp->tm_year = std::min(std::max(this->Year + 100, 0), INT_MAX);
        tp->tm_wday = this->WeekDay % 7;
        tp->tm_yday = -1;
        tp->tm_isdst = -1;
        mktime(tp);
    }

    inline void DateTimeType::setFromStructTm(const struct tm *tp) {
        this->reset();
        this->Seconds = tp->tm_sec;
        this->Minutes = tp->tm_min;
        this->Hours = tp->tm_hour;
        this->Date = tp->tm_mday;
        this->Month = std::min(std::max(tp->tm_mon + 1, 0), 12);
        this->Year = std::min(std::max(tp->tm_year - 100, 0), 99);
        this->WeekDay = (tp->tm_wday + 6) % 7 + 1;
    }

    inline DateTimeType::timestamp_t DateTimeType::getTimestamp() {
        tm timeinfo{0};
        getStructTm(&timeinfo);
        return ::mktime(&timeinfo);
    }

    inline void DateTimeType::setTimestamp(timestamp_t timestamp) {
        tm *timeinfo = localtime(&timestamp);
        setFromStructTm(timeinfo);
    }

    inline size_t DateTimeType::strftime(char *str, size_t count, const char *format) {
        tm timeinfo{0};
        getStructTm(&timeinfo);
        timeinfo.tm_mon++;
        return ::strftime(str, count, format, &timeinfo);
    }

    template<std::size_t N>
    size_t DateTimeType::strftime(Stm32Common::String::FixedString<N> &fixedString, const char *format) {
        // auto ret = strftime(nullptr, 0, format);
        size_t ret = 50;
        char tmpstr[ret]{};
        ret = strftime(tmpstr, sizeof(tmpstr), format);
        fixedString.set(tmpstr);
        return ret;
    }

    inline DateTimeType::timestamp_t DateTimeType::mktime(struct tm *tp) {
        return ::mktime(tp);
    }

    inline bool DateTimeType::setFromIso8601(const char *datetimestring) {
        int year = 0;
        int month = 0;
        int day = 0;
        int h = 0;
        int m = 0;
        int s = 0;

        std::from_chars_result result{};

        result = std::from_chars(datetimestring, datetimestring + 4, year);
        if (result.ec != std::errc() || *result.ptr != '-') {
            // throw std::runtime_error("resultObject.info.serverTime malformed");
            return false;
        }

        result = std::from_chars(datetimestring + 5, datetimestring + 7, month);
        if (result.ec != std::errc() || *result.ptr != '-') {
            // throw std::runtime_error("resultObject.info.serverTime malformed");
            return false;
        }

        result = std::from_chars(datetimestring + 8, datetimestring + 10, day);
        if (result.ec != std::errc() || *result.ptr != 'T') {
            // throw std::runtime_error("resultObject.info.serverTime malformed");
            return false;
        }

        result = std::from_chars(datetimestring + 11, datetimestring + 13, h);
        if (result.ec != std::errc() || *result.ptr != ':') {
            // throw std::runtime_error("resultObject.info.serverTime malformed");
            return false;
        }

        result = std::from_chars(datetimestring + 14, datetimestring + 16, m);
        if (result.ec != std::errc() || *result.ptr != ':') {
            // throw std::runtime_error("resultObject.info.serverTime malformed");
            return false;
        }

        result = std::from_chars(datetimestring + 17, datetimestring + 19, s);
        if (result.ec != std::errc()) {
            // throw std::runtime_error("resultObject.info.serverTime malformed");
            return false;
        }

        struct tm tmstruct{};
        tmstruct.tm_year = year - 1900;
        tmstruct.tm_mon = month - 1;
        tmstruct.tm_mday = day;
        tmstruct.tm_hour = h;
        tmstruct.tm_min = m;
        tmstruct.tm_sec = s;
        tmstruct.tm_isdst = -1;
        tmstruct.tm_wday = -1;
        tmstruct.tm_yday = -1;

        mktime(&tmstruct);
        setFromStructTm(&tmstruct);
        return true;
    }
}

#endif
