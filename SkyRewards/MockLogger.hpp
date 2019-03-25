//
//  MockLogger.hpp
//  SkyRewards
//
//  Created by David Crooks on 24/03/2019.
//  Copyright © 2019 David Crooks. All rights reserved.
//

#ifndef MockLogger_hpp
#define MockLogger_hpp

#include <stdio.h>
#include "ILogger.hpp"



/*
 This mock logger doesn't really log anything.
 All it needs to do is keep track of the  last message so that we can test that the right errors are logged at the right time.
 */
class MockLogger: public ILogger {
    LogSeverity lastSeverity = INFO;
    std::string lastMessage = "";
public:
    void log(LogSeverity severity,std::string message);
    LogSeverity getLastSeverity();
    std::string getLastMessage();
};

#endif /* MockLogger_hpp */
