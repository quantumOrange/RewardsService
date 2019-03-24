//
//  FailingEligibilityService.hpp
//  Sky
//
//  Created by David Crooks on 24/03/2019.
//  Copyright © 2019 David Crooks. All rights reserved.
//

#ifndef FailingEligibilityService_hpp
#define FailingEligibilityService_hpp

#include <stdio.h>
#include "IEligibilityService.hpp"

class FailingEligibilityService: public IEligibilityService {
public:
    virtual void isEligible(int id,std::function<void(CustomerEligible)> callback);
};
#endif /* FailingEligibilityService_hpp */
