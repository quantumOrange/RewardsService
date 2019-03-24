//
//  RewardsService.cpp
//  Sky
//
//  Created by David Crooks on 24/03/2019.
//  Copyright © 2019 David Crooks. All rights reserved.
//

#include "RewardsService.hpp"
#include <iostream>

RewardsService::RewardsService(IEligibilityService& service, ILogger& logger, std::function<void(void)> callback):
                                                                invalidAcoountIdCallback(callback),
                                                                eligibilityService(service)
{
    
}

std::vector<Reward> RewardsService::getRewardsForChannels( std::vector<Channel> channels ) {
    std::vector<Reward> rewards = {};
    
    for(auto channel : channels){
        switch (channel) {
            case SPORTS:
                rewards.push_back(CHAMPIONS_LEAGUE_FINAL_TICKET);
                break;
            case MUSIC:
                rewards.push_back(KARAOKE_PRO_MICROPHONE);
                break;
            case MOVIES:
                rewards.push_back(PIRATES_OF_THE_CARIBBEAN_COLLECTION);
                break;
            default:
                break;
        }
    }
    return rewards;
}

void RewardsService::getRewards(Customer customer, std::function<void(std::vector<Reward>)> callback){
    auto rewards = this->getRewardsForChannels(customer.channels);
    eligibilityService.isEligible(customer.id, [customer,callback,rewards,this](CustomerEligible eligible) {
        switch (eligible) {
            case ELIGABLE:
                callback(rewards);
                break;
            case INVALID_ACCOUNT_ID:
                this->invalidAcoountIdCallback();
                callback({});
                break;
            case SERVICE_FAILURE:
                std::cout << "ERROR: SERVICE_FAILURE" << std::endl;
            default:
                callback({});
                break;
        }
    });
}
