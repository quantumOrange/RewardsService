//
//  Customer.cpp
//  Sky
//
//  Created by David Crooks on 24/03/2019.
//  Copyright © 2019 David Crooks. All rights reserved.
//

#include "Customer.hpp"

Customer::Customer(int id, std::vector<ChannelSubscription> channels):
                                                        id(id),
                                                        portfolio(channels)
{
    
}
