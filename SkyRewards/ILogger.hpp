//
//  ILogger.hpp
//  SkyRewards
//
//  Created by David Crooks on 24/03/2019.
//  Copyright © 2019 David Crooks. All rights reserved.
//

#ifndef ILogger_h
#define ILogger_h

#include <string>

enum LogSeverity {
    INFO,
    WARNING,
    ERROR,
    FATAL
};

class ILogger {
public:
    virtual void log(LogSeverity severity,std::string message) = 0;
};

#endif /* ILogger_h */
