//
//  Customer.hpp
//  Sky
//
//  Created by David Crooks on 24/03/2019.
//  Copyright © 2019 David Crooks. All rights reserved.
//

#ifndef Customer_hpp
#define Customer_hpp

#include <stdio.h>
#include "enums.hpp"
#include <vector>

struct Customer {
    Customer(int id, std::vector<Channel> channels);
    const int id;
    const std::vector<Channel> channels;
};

#endif /* Customer_hpp */
