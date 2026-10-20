#pragma once
#include "ParkingFacility.h"
#include "ParkingTicket.h"
#include "Vehicle.h"
#include "ParkingFeeCalculator.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <chrono>

class ParkingManager
{
private:
    ParkingFacility facility;
    std::vector<ParkingTicket> tickets;
    int nextTicketId{1};
    ParkingFeeCalculator feeCalculator;

public:
    ParkingManager(const ParkingFacility &facility)
    {
        this->facility = facility;
    }

    bool isVehicleParked(const std::string &registrationNumber) const
    {
        for (int i = 0; i < tickets.size(); i++)
        {
            if (tickets[i].getRegistrationNumber() == registrationNumber && tickets[i].getTicketStatus() == TicketStatus::ACTIVE)
            {
                return true;
            }
        }

        return false;
    }

    int registerVehicleEntry(const Vehicle &vehicle)
    {
        if (isVehicleParked(vehicle.getRegistrationNumber()))
        {
            throw std::runtime_error("The vehicle is already parked in the facility");
        }

        int minimumFloorNumber = facility.findAvailableFloorNumber(vehicle.getCategory());

        if (minimumFloorNumber == -1)
        {
            throw std::runtime_error("There is no space available");
        }

        int minimumSpaceId = facility.findAvailableSpaceOnFloor(vehicle.getCategory(), minimumFloorNumber);

        std::chrono::system_clock::time_point currenttime = std::chrono::system_clock::now();

        ParkingTicket ticket(nextTicketId, vehicle, minimumFloorNumber, minimumSpaceId, currenttime);

        tickets.push_back(ticket);

        try
        {
            facility.parkVehicleAtSpace(vehicle, minimumFloorNumber, minimumSpaceId);
        }
        catch (...)
        {
            tickets.pop_back();
            throw;
        }

        nextTicketId++;

        return ticket.getTicketId();
    }

    ParkingTicket getTicketById(int ticketId) const
    {
        for (int i = 0; i < tickets.size(); i++)
        {
            if (tickets[i].getTicketId() == ticketId)
            {
                return tickets[i];
            }
        }

        throw std::invalid_argument("The ticket id does not exist");
    }

    int calculateFeeForTicket(int ticketId, std::chrono::system_clock::time_point exitTime) const
    {
        ParkingTicket ticket = getTicketById(ticketId);

        if (ticket.getTicketStatus() == TicketStatus::CLOSED)
        {
            throw std::runtime_error("The ticket is already closed");
        }

        return feeCalculator.calculateFees(ticket.getVehicleCategory(), ticket.getEntryTime(), exitTime);
    }
};