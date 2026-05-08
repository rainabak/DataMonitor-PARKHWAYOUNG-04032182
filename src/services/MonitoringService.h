#pragma once
#include <vector>
#include "../models/OrderSummary.h"
#include "../models/Sample.h"
#include "../repositories/IOrderRepository.h"
#include "../repositories/ISampleRepository.h"

class MonitoringService
{
public:
    MonitoringService(IOrderRepository& orderRepo, ISampleRepository& sampleRepo);

    OrderSummary        getOrderSummary() const;
    std::vector<Sample> getSampleList()   const;

private:
    IOrderRepository&  m_orderRepo;
    ISampleRepository& m_sampleRepo;
};
