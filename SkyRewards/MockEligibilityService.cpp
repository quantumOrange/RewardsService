//
//  MockEligibilityService.cpp
//  Sky
//
//  Created by David Crooks on 24/03/2019.
//  Copyright © 2019 David Crooks. All rights reserved.
//

#include "MockEligibilityService.hpp"


MockEligibilityService::MockEligibilityService(std::unordered_map<int,CustomerEligible> customers):
                                                                                            customers(customers)
{
    
}

void MockEligibilityService::isEligible(int id, std::function<void(CustomerEligible)> callback) {
    
}
