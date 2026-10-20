#pragma once
#include <chrono>
#include <stdexcept>

enum class PaymentMethod
{
    CASH,
    UPI,
    CARD
};

class PaymentRecord
{
private:
    int transactionId;
    int ticketId;
    int amountPaid;
    PaymentMethod paymentMethod;
    std::chrono::system_clock::time_point paymentTime;

public:
    PaymentRecord(int transactionId, int ticketId, int amountPaid, PaymentMethod paymentMethod, std::chrono::system_clock::time_point paymentTime)
    {

        if (transactionId <= 0)
        {
            throw std::invalid_argument("Transaction id cannot be negative");
        }

        if (ticketId <= 0)
        {
            throw std::invalid_argument("Ticket id cannot be negative");
        }

        if (amountPaid <= 0)
        {
            throw std::invalid_argument("Amount paid must be strictly positive");
        }

        if (paymentMethod != PaymentMethod::CARD && paymentMethod != PaymentMethod::CASH && paymentMethod != PaymentMethod::UPI)
        {
            throw std::invalid_argument("Select a proper payment method");
        }

        this->transactionId = transactionId;
        this->ticketId = ticketId;
        this->amountPaid = amountPaid;
        this->paymentMethod = paymentMethod;
        this->paymentTime = paymentTime;
    }

    int getTransactionId() const
    {
        return this->transactionId;
    }

    int getTicketId() const
    {
        return this->ticketId;
    }

    int getAmountPaid() const
    {
        return this->amountPaid;
    }

    PaymentMethod getPaymentMethod() const
    {
        return this->paymentMethod;
    }

    std::chrono::system_clock::time_point getPaymentTime() const
    {
        return this->paymentTime;
    }
};