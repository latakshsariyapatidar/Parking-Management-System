#pragma once
#include <string>
#include "Vehicle.h"
#include <stdexcept>
#include <chrono>

enum class TicketStatus
{
    ACTIVE,
    CLOSED
};

class ParkingTicket
{
private:
    int ticketId;
    int floorNumber;
    int spaceId;
    std::chrono::system_clock::time_point entryTime;
    std::string registrationNumber;
    VehicleCategory category;
    TicketStatus ticketStatus;

public:
    ParkingTicket(int ticketId, const Vehicle &vehicle, int floorNumber, int spaceId, std::chrono::system_clock::time_point entryTime)
    {

        if (ticketId <= 0)
        {
            throw std::invalid_argument("Ticket id must be positive");
        }

        if (floorNumber <= 0)
        {
            throw std::invalid_argument("The floor number must be positive");
        }

        if (spaceId <= 0)
        {
            throw std::invalid_argument("The space Id must be positive");
        }

        this->ticketId = ticketId;
        this->registrationNumber = vehicle.getRegistrationNumber();
        this->category = vehicle.getCategory();
        this->floorNumber = floorNumber;
        this->spaceId = spaceId;
        this->ticketStatus = TicketStatus::ACTIVE;
        this->entryTime = entryTime;
    }

    int getTicketId() const
    {
        return this->ticketId;
    }

    std::string getRegistrationNumber() const
    {
        return this->registrationNumber;
    }

    VehicleCategory getVehicleCategory() const
    {
        return this->category;
    }

    int getFloorNumber() const
    {
        return this->floorNumber;
    }

    int getSpaceId() const
    {
        return this->spaceId;
    }

    TicketStatus getTicketStatus() const
    {
        return this->ticketStatus;
    }

    std::chrono::system_clock::time_point getEntryTime() const
    {
        return this->entryTime;
    }

    void closeTicket(){
        if (this -> ticketStatus == TicketStatus::CLOSED){
            throw std::runtime_error("The ticket is already closed");
        }

        this -> ticketStatus = TicketStatus::CLOSED;
    }
};