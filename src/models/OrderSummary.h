#pragma once

struct OrderSummary
{
    int countReceived   { 0 };
    int countInProgress { 0 };
    int countCompleted  { 0 };
    int countCancelled  { 0 };
    int total           { 0 };
};
