EOSFramework
============

A Cocoa framework for controlling Canon DSLR cameras.

Visit http://henrybetts.co.uk/eosframework for more information and example code.

EOSFramework is for developers who wish to develop Mac applications that have the ability to interact with Canon DSLR cameras. It acts as a wrapper around Canon’s EDSDK framework, making it simpler to use and easier to fit into Cocoa applications. It can do (almost) everything that EDSDK can do, such as getting and setting properties of a camera, managing camera files and sending commands. The framework was initially designed to handle a large number of cameras at once, but it works just as well with a single camera.

#New for v0.2

* Added EOSBatteryQuality and EOSMeteringMode definitions
* New EOSCameraDelegate methods - camera:didModifyVolume:, camera:didFormatVolume: and camera:willShutdownAfterDelay:

#Requirements

EOSFramework requires Canon's EDSDK (64bit) framework which can be downloaded from:
* [Canon USA](http://www.usa.canon.com/cusa/consumer/standard_display/sdk_homepage)
* [Canon Europa](https://www.didp.canon-europa.com)

#Setup

There are a few steps that need to be taken in order to use EOSFramework in a project. First, ensure that you have downloaded the latest Canon EDSDK 64bit. EOSFramework currently relies on ARC which is only supported in 64bit. Therefore you must use the 64bit version of EDSDK. Also ensure that you have compiled or downloaded the latest version of EOSFramework as a .framework file.

####Preparing EDSDK

EOSFramework looks for the EDSDK header files inside of the EDSDK framework. This is generally the way that Cocoa frameworks are packaged, but EDSDK is not setup in this way. Navigate to the EDSDK.framework folder. Inside, create a folder named Headers. Copy the EDSDK header files (EDSDK.h, EDSDKTypes.h, EDSDKErrors.h) into the newly created folder. Done.

####Importing the frameworks

The easiest way is to drag EDSDK.framework and EOSFramework.framework into the sidebar of an Xcode project. A dialog window will appear in which you can ensure that the frameworks are being added to the target app. Next, go to the build phases of the target app. Add a Copy Files phase. Set the destination to Frameworks and drag both of the frameworks onto the file list.

####Code Signing

You may experience some issues regarding code signing, which causes building the app to fail. A quick (but not necessarily the best) way of fixing this is to disable code signing. Go to the Build Settings of the target app, and set Code Signing Identity to Don't Code Sign.

####Preprocessor Macros

The EDSDK header files contain some outdated preprocessor macros. Go to the Build Settings of the target app, and add \__MACOS__ to the list of Preprocessor Macros.