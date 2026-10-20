#pragma once
#include "Vehicle.h"
#include <stdexcept>
#include <chrono>

class ParkingFeeCalculator
{
private:
public:
    int getHourlyRate(VehicleCategory category) const
    {
        switch (category)
        {
        case (VehicleCategory::BIKE):
            return 10;
        case (VehicleCategory::CAR):
            return 20;
        case (VehicleCategory::TRUCK):
            return 30;

        default:
            throw std::invalid_argument("The category does not exists");
        }
    }

    int getBillableHours(std::chrono::system_clock::time_point entryTime, std::chrono::system_clock::time_point exitTime) const
    {
        if (exitTime < entryTime)
        {
            throw std::invalid_argument("Exit time cannot be before entry time");
        }

        auto timeElapsed = exitTime - entryTime;
        auto roundedHours = std::chrono::ceil<std::chrono::hours>(timeElapsed);
        auto hoursElapsed = roundedHours.count();

        if (hoursElapsed == 0)
        {
            return 1;
        }

        return static_cast<int>(hoursElapsed);
    }

    int calculateFees(const VehicleCategory &category, std::chrono::system_clock::time_point entryTime, std::chrono::system_clock::time_point exitTime) const
    {
        return getHourlyRate(category) * getBillableHours(entryTime, exitTime);
    }
};