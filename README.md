# C++ Gig Performer Extension GlobalVars 
Gig Performer is a live performance VST-host with lots of features. See [Gig Performer](https://gigperformer.com/) for details
This is extension using the [Gig Performer SDK](https://github.com/gigperformer/gp-sdk).
It is based on the gp-extension-cpp example.

## Purpose
Provides global variables accessible between the several script types, like gig-script, rackspace-scrips, scriptlets and song-scripts. GPscript lacks this.  
**USE AT YOUR OWN RISK!**

## Some history
Some time ago I started exploring Gig Performer and stumbled upon its scripting feature. This feature is very useful, but lacks one thing: low weight communication between the several scripts. Of course there are way to accomplish collaboration between these scripts but sometimes they feel a bit heavy for the usage I have in mind. The easiest way IMHO could be variables accessible from all scripts. When I read about this extension API and its possibility to extend also the available script functions, I saw an opportunity to implement this myself.

I must admit till now every 'Gig' I created can do without it, so I'm not entirely sure of the usefulness of this extension. Furthermore, it is possible that this extension conflicts with the philosophy of Gig Performer.

## How to build...
These instructions are a copy of build instructions for the gp-extension-cpp example. The build on macOS I cannot try, because I don't own a Mac.

### ... on macOS

-   Make sure you have [CMake](https://cmake.org) installed.
    You might have to add the path to the cmake executable by adding this line to your bash profile:

    ```bash
    export PATH=/Applications/CMake.app/Contents/bin:$PATH
    ```

    Alternatively, you can install CMake via [Homebrew](https://brew.sh):

    ```bash
    brew install cmake
    ```

-   Build (and install) the project via CMake.
    For your convenience we have provided a `build.sh` which contains all necessary commands:

    ```bash
    ./build.sh
    ```

### ... on Windows

-   Make sure you have [CMake](https://cmake.org), [Git](https://git-scm.com) and a C(++) compiler installed.
    You can get that for example by installing [Visual Studio](https://visualstudio.microsoft.com) with the _Desktop development with C++_ workload and the _Git for Windows_ component.
-   Build (and install) the project via CMake.
    For your convenience we have provided a `build.cmd` which contains all necessary commands:

    ```powershell
    build.cmd
    ```

    **Make sure to run the script from the Visual Studio developer command prompt!**
