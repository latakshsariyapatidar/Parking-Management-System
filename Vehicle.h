#pragma once
#include <string>
#include <stdexcept>

enum class VehicleCategory
{
    CAR,
    BIKE,
    TRUCK
};

class Vehicle
{
private:
    std::string registrationNumber;
    VehicleCategory category;

protected:
    Vehicle(VehicleCategory category, std::string registrationNumber)
    {

        if (registrationNumber == "")
        {
            throw std::invalid_argument("Registration number cannot be empty");
        }

        this->category = category;
        this->registrationNumber = registrationNumber;
    }

public:
    std::string getRegistrationNumber() const
    {
        return this->registrationNumber;
    }

    VehicleCategory getCategory() const
    {
        return this->category;
    }
};

class Car : public Vehicle
{
public:
    Car(std::string registrationNumber) : Vehicle(VehicleCategory::CAR, registrationNumber) {}
};

class Bike : public Vehicle
{
public:
    Bike(std::string registrationNumber) : Vehicle(VehicleCategory::BIKE, registrationNumber) {}
};

class Truck : public Vehicle
{
public:
    Truck(std::string registrationNumber) : Vehicle(VehicleCategory::TRUCK, registrationNumber) {};
};