//
//  main.cpp
//  SkyRewards
//
//  Created by David Crooks on 24/03/2019.
//  Copyright © 2019 David Crooks. All rights reserved.
//

#define CATCH_CONFIG_MAIN

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <unordered_map>

#include "catch.hpp"

#include "RewardsService.hpp"
#include "FailingEligibilityService.hpp"
#include "MockEligibilityService.hpp"
#include "MockLogger.hpp"

template<typename T>
bool compare(std::vector<T>& v1, std::vector<T>& v2)
{
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
    
    return v1 == v2;
}

TEST_CASE( "Service failure returns empty rewards and logs error") {
    bool hasCalledCallbackFlag = false;
    
    auto failing_service = FailingEligibilityService();
    auto logger = MockLogger();
    auto rewardsService = RewardsService(failing_service,logger, [](){});
    
    Customer customer = Customer(1, {SPORTS,MOVIES});
    
    rewardsService.getRewards(customer, [&hasCalledCallbackFlag](std::vector<Reward> rewards){
        hasCalledCallbackFlag = true;
        REQUIRE(rewards.empty());
    } );
    
    REQUIRE(logger.getLastSeverity() == ERROR );
    REQUIRE(logger.getLastMessage() == "ERROR: SERVICE_FAILURE");
    
    REQUIRE(hasCalledCallbackFlag);
}

TEST_CASE( "Ineligible customer returns empty rewards") {
    bool hasCalledCallbackFlag = false;
    
    auto customerEligigble = Customer(1, {SPORTS,MOVIES});
    auto customerIneligible = Customer(2, {SPORTS,MOVIES});
    
    std::unordered_map<int, CustomerEligible> customers;
    customers[customerEligigble.id] = ELIGABLE;
    customers[customerIneligible.id] = INELIGABLE;
    
    auto mock_service = MockEligibilityService(customers);
    auto logger = MockLogger();
    
    auto rewardsService = RewardsService(mock_service,logger,[](){});
    
    rewardsService.getRewards(customerIneligible, [&hasCalledCallbackFlag](std::vector<Reward> rewards){
        hasCalledCallbackFlag = true;
        REQUIRE(rewards.empty());
    } );
    
    //We have to check that the callback has indeed been called, otherwise an empty implementation would pass the tests because the above REQUIRE would not even be hit.
    REQUIRE(hasCalledCallbackFlag);
}

TEST_CASE( "Invalid customer id returns empty rewards and notifies client") {
    bool hasNotifiedClientFlag = false;
    bool hasCalledCallbackFlag = false;
    
    auto customerValid = Customer(1, {SPORTS,MOVIES});
    
    auto customerInvalid = Customer(2, {SPORTS,MOVIES});
    
    std::unordered_map<int, CustomerEligible> customers;
    customers[customerValid.id] = ELIGABLE;
    auto mock_service = MockEligibilityService(customers);
    auto logger = MockLogger();
    
    auto rewardsService = RewardsService(mock_service,logger,[&hasNotifiedClientFlag](){
        hasNotifiedClientFlag = true;
    });
    
    rewardsService.getRewards(customerInvalid, [&hasNotifiedClientFlag, &hasCalledCallbackFlag](std::vector<Reward> rewards){
        hasCalledCallbackFlag = true;
        REQUIRE(rewards.empty());
    } );
    
    REQUIRE(hasNotifiedClientFlag);
    REQUIRE(hasCalledCallbackFlag);
}

TEST_CASE( "Eligbile customers get the right rewards") {
    bool hasCalledCallbackFlag = false;
    
    auto customerSPORTS     = Customer(1, {SPORTS});
    auto customerMOVIES     = Customer(2, {MOVIES});
    auto customerMUSIC      = Customer(3, {MUSIC});
    auto customerKIDS       = Customer(4, {KIDS});
    auto customerNEWS       = Customer(5, {NEWS});
    auto customerALL        = Customer(6, {SPORTS,MUSIC,MOVIES,KIDS,NEWS});
    auto customerINELIGIBLE = Customer(7, {SPORTS,MUSIC,MOVIES,KIDS,NEWS});
    
    std::unordered_map<int, CustomerEligible> customers;
    
    customers[customerSPORTS.id]        = ELIGABLE;
    customers[customerMOVIES.id]        = ELIGABLE;
    customers[customerMUSIC.id]         = ELIGABLE;
    customers[customerKIDS.id]          = ELIGABLE;
    customers[customerNEWS.id]          = ELIGABLE;
    customers[customerALL.id]           = ELIGABLE;
    customers[customerINELIGIBLE.id]    = INELIGABLE;
    
    auto mock_service = MockEligibilityService(customers);
    auto logger = MockLogger();
    
    auto rewardsService = RewardsService(mock_service,logger,[](){});
    
    rewardsService.getRewards(customerSPORTS, [&hasCalledCallbackFlag](std::vector<Reward> rewards){
        hasCalledCallbackFlag = true;
        std::vector<Reward> expected = {CHAMPIONS_LEAGUE_FINAL_TICKET};
        REQUIRE(compare(expected, rewards) );
    } );
    
    rewardsService.getRewards(customerMOVIES, [](std::vector<Reward> rewards){
        std::vector<Reward> expected = {PIRATES_OF_THE_CARIBBEAN_COLLECTION};
        REQUIRE(compare(expected, rewards) );
    } );
    
    rewardsService.getRewards(customerMUSIC, [](std::vector<Reward> rewards){
        std::vector<Reward> expected = {KARAOKE_PRO_MICROPHONE};
        REQUIRE(compare(expected, rewards) );
    } );
    
    rewardsService.getRewards(customerKIDS, [](std::vector<Reward> rewards){
        std::vector<Reward> expected = {};
        REQUIRE(compare(expected, rewards) );
    } );
    
    rewardsService.getRewards(customerNEWS, [](std::vector<Reward> rewards){
        std::vector<Reward> expected = {};
        REQUIRE(compare(expected, rewards) );
    } );
    
    rewardsService.getRewards(customerALL, [](std::vector<Reward> rewards){
        std::vector<Reward> expected = {CHAMPIONS_LEAGUE_FINAL_TICKET,KARAOKE_PRO_MICROPHONE,PIRATES_OF_THE_CARIBBEAN_COLLECTION};
        REQUIRE(compare(expected, rewards) );
    } );
    
    rewardsService.getRewards(customerINELIGIBLE, [](std::vector<Reward> rewards){
        std::vector<Reward> expected = {};
        REQUIRE(compare(expected, rewards) );
    } );
    
    REQUIRE(hasCalledCallbackFlag);
}
