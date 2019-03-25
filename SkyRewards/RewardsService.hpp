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

    std::function<void(int)> invalidAcoountIdCallback;
    ILogger& logger;
    IEligibilityService& eligibilityService;
    std::vector<Reward> getRewardsForChannels( std::vector<ChannelSubscription> portfolio );
    
public:
    
    /*
     RewardsService is initialised with an eligibility service, logger, and a callback:
     - invalidAcoountIdCallback: this callback will be called if getRewards is called with an invalid customer, passing in the invalid id,
     and should be used to notify of invalid ids.
    */
    RewardsService(IEligibilityService& service, ILogger& logger, std::function<void(int)> invalidAcoountIdCallback);
    
    /*
     Given a customer with an id and a portfolio it will call the callback with a vector of rewards to which the customer is entitled to, depending on their eligibility and portfolio.
     side effects:
     - invalidAcoountIdCallback will be called if the customer id is invalid.
     - logs error to logger in the event of service failure.
    */
    void getRewards(Customer customer, std::function<void(std::vector<Reward>)> callback);
};

#endif /* RewardsService_hpp */
