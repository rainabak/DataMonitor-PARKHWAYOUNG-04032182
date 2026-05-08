#include "MonitoringService.h"

MonitoringService::MonitoringService(IOrderRepository& orderRepo, ISampleRepository& sampleRepo)
    : m_orderRepo(orderRepo)
    , m_sampleRepo(sampleRepo)
{
}

OrderSummary MonitoringService::getOrderSummary() const
{
    return OrderSummary{};
}

std::vector<Sample> MonitoringService::getSampleList() const
{
    return {};
}
