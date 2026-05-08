#pragma once
#include <string>
#include <vector>
#include "../models/OrderSummary.h"
#include "../models/Sample.h"

class MonitoringView
{
public:
    void showMenu()                                                const;
    int  getMenuChoice()                                           const;
    void showMessage(const std::string& msg)                       const;
    void showDashboard(const OrderSummary&        summary,
                       const std::vector<Sample>& samples)         const;
    void showOrderSummary(const OrderSummary& summary)             const;
    void showSampleList(const std::vector<Sample>& samples)        const;
};
