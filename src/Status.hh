#pragma once

enum class Status
{
    TERMINATED,
    ACTIVE,
    PENDING
};

inline const char *statusToString(Status status)
{
    switch (status)
    {
    case Status::TERMINATED:
        return "TERMINATED";
    case Status::ACTIVE:
        return "ACTIVE";
    case Status::PENDING:
        return "PENDING";
    default:
        return "UNKNOWN";
    }
}