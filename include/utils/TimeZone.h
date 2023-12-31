#pragma once

#include <memory>
#include <string>
#include <time.h>
#include <vector>

namespace utils {
namespace TimeZone {

struct Data;

// TimeZone for 1970~2030
class TimeZone {
public:
    explicit TimeZone(const char *zonefile);
    TimeZone(int eastOfUtc, const char *tzname); // a fixed timezone
    TimeZone() = default;                        // an invalid timezone

    // default copy ctor/assignment/dtor are Okay.

    bool valid() const {
        // 'explicit operator bool() const' in C++11
        return static_cast<bool>(data_);
    }

    struct tm toLocalTime_byChrono(time_t secondsSinceEpoch) const;
    struct tm toLocalTime(time_t secondsSinceEpoch) const;
    time_t fromLocalTime(const struct tm &) const;

    // gmtime(3)
    static struct tm toUtcTime(time_t secondsSinceEpoch, bool yday = false);
    // timegm(3)
    static time_t fromUtcTime(const struct tm &);
    // year in [1900..2500], month in [1..12], day in [1..31]
    static time_t fromUtcTime(int year, int month, int day, int hour, int minute, int seconds);

private:
    std::shared_ptr<Data> data_;
};

} // namespace TimeZone
} // namespace utils