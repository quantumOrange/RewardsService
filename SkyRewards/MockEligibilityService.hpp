//
//  MockEligibilityService.hpp
//  Sky
//
//  Created by David Crooks on 24/03/2019.
//  Copyright © 2019 David Crooks. All rights reserved.
//

#ifndef MockEligibilityService_hpp
#define MockEligibilityService_hpp

#include <stdio.h>
#include "IEligibilityService.hpp"
#include  <unordered_map>

class MockEligibilityService: public IEligibilityService {
    std::unordered_map<int,CustomerEligible> customers;
public:
    MockEligibilityService(std::unordered_map<int,CustomerEligible> customers);
        virtual void isEligible(int id, std::function<void(CustomerEligible)> callback);
};

#endif /* MockEligibilityService_hpp */
