/*
   KOSX
   Controller.h

   Copyright (C)2005 Dan Potter
*/

#import <Cocoa/Cocoa.h>

@interface Controller : NSObject
{
    unsigned int  width, height;
    unsigned int  colorBits;
    unsigned int  depthBits;
    
    NSView	* mainView;
}

@end