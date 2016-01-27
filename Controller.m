/*
   KOSX
   Controller.m

   Copyright (C)2005 Dan Potter
*/


// Most of this really ought to be moved into KOSX itself...

#import "Controller.h"

#import <OpenGL/OpenGL.h>
#import <OpenGL/gl.h>
#import <OpenGL/glu.h>
#import <OpenGL/glext.h>

#include <unistd.h>
#include <maple/MapleEventReceiver.h>

@interface Controller (PrivateAPI)
- (NSOpenGLPixelFormat *) _createPixelFormat;
- (void)glThread;
+ (void)glThreadStatic: (id)obj;
@end

#include <plx/port.h>
#include <unistd.h>
#include <sys/time.h>

void plx_main();
void plx_wait_ready();

static volatile NSOpenGLContext * g_view = NULL;
static NSWindow * g_wnd = NULL;
static int frames = 0;

void waitgview() {
	while (!g_view) {
		NSLog(@"waiting for view...");
		usleep(1000*1000);
	}
}

void plx_scene_begin_hook() {
	waitgview();
	[g_view makeCurrentContext];
}

void plx_scene_finish_hook() {
	waitgview();
	[g_view flushBuffer];
}

static struct timeval lastFrame = { 0,0 };

// This makes sure we have a GL visual available and frame limits it to 60fps
// if needed.
void plx_wait_ready() {
	waitgview();

	if (lastFrame.tv_sec == 0) {
		gettimeofday(&lastFrame, NULL);
		return;
	}

	struct timeval now;
	gettimeofday(&now, NULL);
	long long nowu = ((long long)now.tv_sec) * 1000 * 1000 + now.tv_usec;
	long long lastu = ((long long)lastFrame.tv_sec) * 1000 * 1000 + lastFrame.tv_usec;
	long long diffu = nowu - lastu;
	if (diffu < (1000*1000 / 60)) {
		usleep((1000*1000 / 60) - diffu);
	}
	gettimeofday(&lastFrame, NULL);

	frames++;
}

@implementation Controller

- (void) applicationDidFinishLaunching: (NSNotification *) note
{
	// Put your desired width/height here.
	width = 640;
	height = 480;

	// You can query the display for its current depth and use that, but I
	// find that you get better results by just bumping it up to 32/32
	// right away.
	/*
	NSDictionary * originalDisplayMode = (NSDictionary *)
		CGDisplayCurrentMode(kCGDirectMainDisplay);
	depthBits = colorBits = [[originalDisplayMode objectForKey: (id)kCGDisplayBitsPerPixel] intValue];
	NSDictionary * displayMode = (NSDictionary *)CGDisplayBestModeForParameters(
		kCGDirectMainDisplay, colorBits, width, height, NULL);
	*/
	depthBits = colorBits = 32;

	NSOpenGLPixelFormat * pixelFormat = [self _createPixelFormat];
	NSOpenGLContext * context = [[NSOpenGLContext alloc]
		initWithFormat: pixelFormat shareContext: nil];
	[pixelFormat release];

	NSRect rect = NSMakeRect(0, 0, width, height);
	NSWindow * window = [[NSWindow alloc]
		initWithContentRect:rect
		styleMask:NSTitledWindowMask
			| NSTexturedBackgroundWindowMask	// Not compatible with Jaguar 10.2.x
			| NSClosableWindowMask
			| NSMiniaturizableWindowMask
			| NSResizableWindowMask
		backing:NSBackingStoreRetained
		defer:NO];
	[window setTitle: @"KOSX Test Program"];
	[window makeKeyAndOrderFront:nil];
	[window setHasShadow:YES];
	g_wnd = window;
	g_view = context;
        
	// Attach the GL context to the content of the window
	[context setView: [window contentView]];

	// Make the context we created be the current GL context
	[context makeCurrentContext];

	// Set the refresh sync on the context (or not)
	{
		// Get the underlying CGL context
		CGLContextObj cglContext = CGLGetCurrentContext();
    		long param = 0;
		CGLSetParameter(cglContext, kCGLCPSwapInterval, &param);
	}

	plx_set_scene_hooks(plx_scene_begin_hook, plx_scene_finish_hook);

	[MapleEventReceiver init];

	[NSThread detachNewThreadSelector:@selector(glThreadStatic:)
		toTarget:[Controller class] withObject:self];
	
	NSDate * distantPast = [[NSDate distantPast] retain];
	NSDate * distantFuture = [[NSDate distantFuture] retain];
	BOOL done = NO;
	NSAutoreleasePool * pool = nil;
	unsigned int kbNewFlags, kbPreviousFlags = 0, kbChanged, down;

	// Process events
	while (!done) {
		NSEvent * event;
		NSEventType type;
        
		pool = [[NSAutoreleasePool alloc] init];
        
		// This polls for an event.  If there isn't an event read immediately, it will return nil.  In a real game, we would loop until we had processed all pending events and would then go about our normal game processing
		event = [NSApp nextEventMatchingMask:NSAnyEventMask untilDate:distantFuture inMode:NSDefaultRunLoopMode dequeue:YES];
		if (!event) {
			[pool release];
			pool = nil;

			// We'd break out of this loop instead of continuing in a real game (as mentioned above).
			continue;
		}
        
		// Handle the event we got
		type = [event type];
		switch (type) {
		case NSKeyDown:
		case NSKeyUp:
			// Ignore key repeats (we don't turn them off because doing
			// so is risky in case of a program crash).
			if ([event isARepeat])
				break;
				
			// If Command or Ctrl is down, pass this on to NSApp.
			if (([event modifierFlags] & NSCommandKeyMask) ||
				([event modifierFlags] & NSControlKeyMask))
			{
				[NSApp sendEvent: event];
				break;
			}
			[MapleEventReceiver processEvent: event];
			// NSLog([NSString stringWithFormat: @"%@", event]);
			break;

		case NSFlagsChanged:
			kbNewFlags = [event modifierFlags];
			kbChanged = kbNewFlags ^ kbPreviousFlags;
                
			/* if (kbChanged & NSControlKeyMask) {
				down = kbNewFlags & NSControlKeyMask;
			}
                
			if (kbChanged & NSCommandKeyMask) {
				down = kbNewFlags & NSCommandKeyMask;
			} */
                
			kbPreviousFlags = kbNewFlags;
                
			break;
		}
	}
	[MapleEventReceiver shutdown];
	if (pool)
		[pool release];
}


@end

@implementation Controller (PrivateAPI)

- (void)glThread
{
	// We need our own autorelease pool for Cocoa.
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];

	NSLog(@"glThread started");

	// Make sure we've selected our context and have a view.
	plx_wait_ready();
	plx_scene_begin_hook();
	plx_scene_finish_hook();

	plx_main();

	NSLog(@"glThread exiting");

	[pool release];
}

+ (void)glThreadStatic:(id)anObject
{
	Controller * us = (Controller *)anObject;
	[us glThread];
}

- (NSOpenGLPixelFormat *) _createPixelFormat;
{
	NSOpenGLPixelFormatAttribute attributes[] = {
		NSOpenGLPFAColorSize, colorBits,
		NSOpenGLPFADepthSize, depthBits,
		NSOpenGLPFADoubleBuffer,
		NSOpenGLPFAAccelerated,
		NSOpenGLPFAScreenMask, CGDisplayIDToOpenGLDisplayMask(kCGDirectMainDisplay),
		// NSOpenGLPFAFullScreen,
		0
	};

	return [[NSOpenGLPixelFormat alloc] initWithAttributes: attributes];
}

@end





