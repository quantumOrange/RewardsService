//
//  RewardsService.hpp
//  Sky
//
//  Created by David Crooks on 24/03/2019.
//  Copyright © 2019 David Crooks. All rights reserved.
//

#ifndef RewardsService_hpp
#define RewardsService_hpp

#include <stdio.h>
#include "Customer.hpp"
#include "IEligibilityService.hpp"
#include "enums.hpp"
#include <vector>
#include <functional>
#include "ILogger.hpp"

class RewardsService {
    
    std::function<void(void)> invalidAcoountIdCallback;
    ILogger& logger;
    IEligibilityService& eligibilityService;
    std::vector<Reward> getRewardsForChannels( std::vector<Channel> channels );
    
public:
    RewardsService(IEligibilityService& service, ILogger& logger, std::function<void(void)> invalidAcoountIdCallback);
    void getRewards(Customer customer, std::function<void(std::vector<Reward>)> callback);
};

#endif /* RewardsService_hpp */
