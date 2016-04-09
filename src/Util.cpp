//
//  Util.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 4/6/16.
//
//

#include "Util.hpp"

#ifdef __APPLE__
#include "CoreFoundation/CoreFoundation.h"
#endif

static std::string
_GetResourcePath()
{
    // from http://stackoverflow.com/questions/516200/relative-paths-not-working-in-xcode-c
    // This makes relative paths work in C++ in Xcode by changing directory to the Resources folder inside the .app bundle
#ifdef __APPLE__
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
    char path[PATH_MAX];
    if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX))
    {
        // error!
    }
    CFRelease(resourcesURL);

    return std::string(path);
#endif
    
    printf("_GetResourcePath only understood for __APPLE__\n");
    return std::string("");
}

void
SrUtil_ChangeToResourceDirectory()
{
    std::string path = _GetResourcePath();
    chdir(path.c_str());
}

std::string
SrUtil_GetAbsolutePathForResource(const std::string & localPath)
{
    std::string resourcePath = _GetResourcePath();
    return resourcePath + '/' + localPath;
}