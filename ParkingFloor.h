#pragma once
#include <stdexcept>
#include "ParkingSpace.h"
#include <vector>
#include <cstddef>

class ParkingFloor
{
private:
    int floorNumber;
    std::vector<ParkingSpace> parkingSpaces{};

public:
    ParkingFloor(int floorNumber)
    {
        if (floorNumber <= 0)
        {
            throw std::invalid_argument("The floor number cannot be zero or negative");
        }

        this->floorNumber = floorNumber;
    }

    void addParkingSpace(const ParkingSpace &space)
    {
        for (int i = 0; i < parkingSpaces.size(); i++)
        {
            if (parkingSpaces[i].getSpaceId() == space.getSpaceId())
            {
                throw std::invalid_argument("The parking space already exists");
            }
        }

        parkingSpaces.push_back(space);
    }

    std::size_t getSpaceCount() const
    {
        return this->parkingSpaces.size();
    }

    int getAvailableSpaceCount(const VehicleCategory &category) const
    {
        int count = 0;
        for (int i = 0; i < parkingSpaces.size(); i++)
        {
            if (parkingSpaces[i].getCategory() == category && parkingSpaces[i].getStatus() == ParkingSpaceStatus::FREE)
            {
                count++;
            }
        }

        return count;
    }

    int findAvailableSpaceId(const VehicleCategory &category) const
    {
        int spaceId = -1;

        for (int i = 0; i < parkingSpaces.size(); i++)
        {
            if (parkingSpaces[i].getCategory() == category && parkingSpaces[i].getStatus() == ParkingSpaceStatus::FREE)
            {
                if (spaceId == -1)
                {
                    spaceId = parkingSpaces[i].getSpaceId();
                }
                else
                {
                    if (spaceId > parkingSpaces[i].getSpaceId())
                    {
                        spaceId = parkingSpaces[i].getSpaceId();
                    }
                }
            }
        }

        return spaceId;
    }

    void parkVehicleInSpace(const Vehicle &vehicle, int spaceId)
    {
        for (int i = 0; i < parkingSpaces.size(); i++)
        {
            if (parkingSpaces[i].getSpaceId() == spaceId)
            {

                parkingSpaces[i].parkVehicle(vehicle);
                return;
            }
        }

        throw std::invalid_argument("The space id does not exist on the floor");
    }

    void releaseSpaceById(int spaceId)
    {
        for (int i = 0; i < parkingSpaces.size(); i++)
        {
            if (parkingSpaces[i].getSpaceId() == spaceId)
            {

                parkingSpaces[i].releaseSpace();
                return;
            }
        }

        throw std::invalid_argument("The space id does not exist on the floor");
    }

    int getFloor() const
    {
        return this->floorNumber;
    }
};