#pragma once
#include "ParkingFloor.h"
#include "ParkingSpace.h"
#include <vector>
#include <stdexcept>

class ParkingFacility
{
private:
    std::vector<ParkingFloor> floors;

public:
    void addFloor(const ParkingFloor &floor)
    {
        for (int i = 0; i < floors.size(); i++)
        {
            if (floors[i].getFloorNumber() == floor.getFloorNumber())
            {
                throw std::invalid_argument("The floor number already exist in the facility");
            }
        }

        if (floor.getSpaceCount() == 0)
        {
            throw std::invalid_argument("Cannot add a floor with no parking spaces");
        }

        for (int i = 0; i < floors.size(); i++){
            if (floors[i].hasCommonSpaceId(floor)){
                throw std::invalid_argument("Some duplicate parking space ID are present");
            }
        }

        floors.push_back(floor);
    }

    int findAvailableFloorNumber(const VehicleCategory &category) const {
        int floorNumber = -1;

        for (int i = 0; i < floors.size(); i++){
            int availableSpaces = floors[i].getCategorySpaceAvailableCount(category);
            if (availableSpaces > 0){
                if (floorNumber == -1){
                    floorNumber = floors[i].getFloorNumber();
                }
                else if (floorNumber > floors[i].getFloorNumber()){
                    floorNumber = floors[i].getFloorNumber();
                }
            }
        }

        return floorNumber;
    }

};