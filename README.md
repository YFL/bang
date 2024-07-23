# Build and run
To build the game you need to first build all the dependencies that are in the _external_ folder.

We used dlls where we could (mostly because of licencing).

We also used the CMake GUI (so that's our recommendation unless you are well versed with CMake and can use the command line and want to type a lot :D).

## JsonCpp
For JsonCpp we recommend the following CMake config:
* BUILD_OBJECT_LIBS OFF
* BUILD_SHARED_LIBS ON
* BUILD_STATIC_LIBS OFF
* BUILD_TESTING OFF
* CMAKE_INSTALL_PREFIX `<BangSourceDir>/vendor/jsoncpp`
* JSONCPP_STATIC_WINDOWS_RUNTIME OFF
* JSONCPP_WITH_CMAKE_PACKAGE ON
* JSONCPP_WITH_EXAMPLE OFF
* JSONCPP_WITH_PKGCONFIG_SUPPORT OFF
* JSONCPP_WITH_POST_BUILD_UNITTEST OFF
* JSONCPP_WITH_STRIC_ISO ON
* JSONCPP_WITH_TESTS OFF
* JSONCPP_WITH_WARNING_AS_ERROR OFF

The _CMAKE__ variables seemed to be usable without changing them.

Hit _Configure_ and _Generate_.  
With this configuration we then build jsoncpp by doing this in the command line:
```
$> cd <BangSourceDir>/external/jsoncpp/build
$> cmake --build . --config Release
$> cmake --install .
```

## SDL2
For SDL2 we recommend the following CMake config:
* CMAKE_INSTALL_PREFIX `<BangSourceDir>/vendor/SDL2`
* SDL2_DISABLE_INSTALL OFF
* SDL2_DISBALE_SDL2MAIN ON
* SDL2_DISABLE_UNINSTALL OFF
* SDL_STATIC OFF
* SDL_TEST OFF
* SDL_TESTS OFF

Hit _Configure_ and _Generate_.  
With this configuration we then build SDL2 by doing this in the command line:
```
$> cd <BangSourceDir>/external/SDL/build
$> cmake --build . --config Release
$> cmake --install .
```

## SDL2 Image
For SDL2 Image we recommend the following CMake config:
* BUILD_SHARED_LIBS ON
* CMAKE_INSTALL_PREFIX `<BangSourceDir>/vendor/SDL2_image`
* SDL2IMAGE_SAMPLES OFF
* SDL2IMAGE_TESTS OFF
* SDL2IMAGE_VENDORED ON

The first _configuration_ via CMake GUI will probably fail by saying that SDL couldn't be found. Now we should find SDL2_DIR among the configuration options and set it to `<BangSourceDir>/vendor/SDL2/cmake` and hit _Configure_ in the CMake GUI again.

If there's another problem regarding a missing NASM installation, something along the lines of `Missing CMAKE_ASM_NASM_COMPILER when compiling ...`, then you'll have to install NASM and add it's location to the PATH environment variable.  
NASM can be downloaded from [here](https://www.nasm.us/pub/nasm/releasebuilds/?C=M;O=D). We just installed it to `C:\Program Files\NASM\` and added that path to the PATH environment variable.

Hit _Configure_ and _Generate_.  
With this configuration we then build SDL2 by doing this in the command line:
```
$> cd <BangSourceDir>/external/SDL_image/build
$> cmake --build . --config Release
$> cmake --install .
```
After the install you should remove the build directory so that the SDL2_image submodule doesn't recognize it as changes. This might pose problems if you wanted to actually commit something into the Bang repo though, so if you just want to build it and play, this is probably not necessary.

## SDL2 TTF
For SDL2 TTF we recommend the following CMake config:
* BUILD_SHARED_LIBS ON
* CMAKE_INSTALL_PREFIX `<BangSourceDir>/vendor/SDL2_ttf`
* SDL2TTF_INSTALL ON
* SDL2TTF_SAMPLES OFF - without this the compilation fails.
* SDL2TTF_VENDORED ON

The same problem might arrise as with SDL2 Image regarding `SDL2_DIR`. The solution is the same, i.e.:
1. _Configure_
2. Set `SDL2_DIR` to `<BangSourceDir>/vendor/SDL2/cmake`
3. Hit _Configure_ again.

Hit _Generate_.  
With this configuration we then build SDL2 by doing this in the command line:
```
$> cd <BangSourceDir>/external/SDL_ttf/build
$> cmake --build . --config Release
$> cmake --install .
```
After the install you should remove the build directory so that the SDL2_ttf submodule doesn't recognize it as changes. This might pose problems if you wanted to actually commit something into the Bang repo though, so if you just want to build it and play, this is probably not necessary.

---

After the dependencies are built we are ready to build the game itself. We configure and generate the project via the CMake GUI by just clicking the _Configure_ and _Generate_ buttons, then we can open the project via the _Open Project_ button. Visual Studio should open. Now we can select the Release configuration and build the project inside VS by hittitng `Ctrl + Shift + B`.

When the project is built we can simply Run the game by clicking on `Local Windows Debugger |>` in VS.

If you want to run the game from the GUI of you operating system, you should have the card bundles, fonts and other assets placed into the working directory from where you want to start the game. The built executables and every required dll can be found in \<BangSourceDir\>/build/bin.