//
//  Util.hpp
//  SonicRunway
//
//  Created by Rob Jensen on 4/6/16.
//
//

#ifndef SR_UTIL_HPP
#define SR_UTIL_HPP

#include <stdio.h>
#include <string>

// Set the current working directory to the location of resources
// so we can load text files, images, etc.
void
SrUtil_ChangeToResourceDirectory();

std::string
SrUtil_GetAbsolutePathForResource(const std::string & localPath);

#endif /* Util_hpp */
