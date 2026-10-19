#pragma once
#include <stdexcept>
#include "Vehicle.h"

enum class ParkingSpaceStatus{
    OCCUPIED,
    FREE
};

class ParkingSpace{
private:
    int spaceId;
    VehicleCategory category;
    ParkingSpaceStatus status;
public:
    ParkingSpace(int spaceId, VehicleCategory category){
        if (spaceId <= 0 ){
            throw std::invalid_argument("Space ID must be greater than 0");
        }

        this -> spaceId = spaceId;
        this -> category = category;
        this -> status = ParkingSpaceStatus::FREE;
    }

    int getSpaceId() const {
        return this -> spaceId;
    }

    VehicleCategory getCategory() const{
        return this->category;
    }

    ParkingSpaceStatus getStatus() const{
        return this -> status;
    }

    void parkVehicle(const Vehicle& vehicle){
        if (vehicle.getCategory() != category){
            throw std::runtime_error("The vehicle category does not match the space category");
        }

        if (this -> status == ParkingSpaceStatus::OCCUPIED){
            throw std::runtime_error("The space is already occupied");
        }

        this->status = ParkingSpaceStatus::OCCUPIED;
    }

    void releaseSpace(){
        if (this -> status == ParkingSpaceStatus::FREE){
            throw std::runtime_error("The space is already empty");
        }

        this -> status = ParkingSpaceStatus::FREE;
    }
};


