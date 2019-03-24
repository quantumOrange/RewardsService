//
//  RewardsService.cpp
//  Sky
//
//  Created by David Crooks on 24/03/2019.
//  Copyright © 2019 David Crooks. All rights reserved.
//

#include "RewardsService.hpp"
#include <iostream>

RewardsService::RewardsService(IEligibilityService& service, std::function<void(void)> callback):
                                                                invalidAcoountIdCallback(callback),
                                                                eligibilityService(service)
{
    
}


void RewardsService::getRewards(Customer customer, std::function<void(std::vector<Reward>)> callback){
    
}
