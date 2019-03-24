//
//  EligibilityService.hpp
//  Sky
//
//  Created by David Crooks on 24/03/2019.
//  Copyright © 2019 David Crooks. All rights reserved.
//

#ifndef EligibilityService_hpp
#define EligibilityService_hpp

#include <stdio.h>
#include "enums.hpp"
#include <functional>

class IEligibilityService {
public:
    virtual void isEligible(int id,  std::function<void(CustomerEligible)> callback) = 0;
};



#endif /* EligibilityService_hpp */
