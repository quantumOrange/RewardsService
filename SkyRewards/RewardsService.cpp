//
//  RewardsService.cpp
//  Sky
//
//  Created by David Crooks on 24/03/2019.
//  Copyright © 2019 David Crooks. All rights reserved.
//

#include "RewardsService.hpp"
#include <iostream>

RewardsService::RewardsService(IEligibilityService& service, ILogger& logger, std::function<void(int)> callback):
                                                                invalidAcoountIdCallback(callback),
                                                                eligibilityService(service),
                                                                logger(logger)
{
    
}

std::vector<Reward> RewardsService::getRewardsForChannels( std::vector<ChannelSubscription> portfolio ) {
    std::vector<Reward> rewards = {};
    
    for(auto subscription : portfolio){
        switch (subscription) {
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

void RewardsService::getRewards(Customer customer, std::function<void(std::vector<Reward>)> rewardsCallback){
    auto rewards = this->getRewardsForChannels(customer.portfolio);
    eligibilityService.isEligible(customer.id, [customer,rewardsCallback,rewards,this](CustomerEligible eligible) {
        switch (eligible) {
            case ELIGABLE:
                rewardsCallback(rewards);
                break;
            case INVALID_ACCOUNT_ID:
                this->invalidAcoountIdCallback(customer.id);
                rewardsCallback({});
                break;
            case SERVICE_FAILURE:
                this->logger.log(ERROR,"ERROR: SERVICE_FAILURE");
            default:
                rewardsCallback({});
                break;
        }
    });
}
