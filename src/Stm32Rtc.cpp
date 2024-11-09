/*
 * SPDX-FileCopyrightText: 2024 Roland Rusch, easy-smart solution GmbH <roland.rusch@easy-smart.ch>
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "Stm32Rtc.hpp"
#include <stdexcept>

using namespace Stm32Rtc;

void Rtc::getTime(TimeType *time) {
    DateType tmpDate;
    auto retTime = getRtcTime(time);
    auto retDate = getRtcDate(&tmpDate);
    if (RTC_Handle->Instance == nullptr || retDate != HAL_OK || retTime != HAL_OK) {
        time->reset();
    }
}

void Rtc::getDate(DateType *date) {
    TimeType tmpTime;
    auto retTime = getRtcTime(&tmpTime);
    auto retDate = getRtcDate(date);
    if (RTC_Handle->Instance == nullptr || retDate != HAL_OK || retTime != HAL_OK) {
        date->reset();
    }
}

void Rtc::getDateTime(DateTimeType *dateTime) {
    auto retTime = getRtcTime(dateTime);
    auto retDate = getRtcDate(dateTime);
    if (RTC_Handle->Instance == nullptr || retDate != HAL_OK || retTime != HAL_OK) {
        dateTime->reset();
    }
}

HAL::HAL_StatusTypeDef Rtc::getRtcTime(HAL::RTC_TimeTypeDef *halTime) {
    return RTC_Handle->Instance == nullptr
               ? HAL_ERROR
               : HAL_RTC_GetTime(RTC_Handle, halTime, RTC_FORMAT_BIN);
}

HAL::HAL_StatusTypeDef Rtc::getRtcDate(HAL::RTC_DateTypeDef *halDate) {
    return RTC_Handle->Instance == nullptr
               ? HAL_ERROR
               : HAL_RTC_GetDate(RTC_Handle, halDate, RTC_FORMAT_BIN);
}
