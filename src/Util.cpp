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

void SrUtil_ChangeToResourceDirectory()
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

    chdir(path);
    printf("current path: %s\n", path);
#endif
    
}