//
//  MockLogger.cpp
//  SkyRewards
//
//  Created by David Crooks on 24/03/2019.
//  Copyright © 2019 David Crooks. All rights reserved.
//

#include "MockLogger.hpp"
#import "ILogger.hpp"

LogSeverity MockLogger::getLastSeverity(){
    return lastSeverity;
}

std::string MockLogger::getLastMessage(){
    return lastMessage;
}

void MockLogger::log(LogSeverity severity,std::string message){
    lastMessage = message;
    lastSeverity = severity;
}
