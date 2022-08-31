# C++ Gig Performer Extension GlobalVars 
Gig Performer is a live performance VST-host with lots of features. See [Gig Performer](https://gigperformer.com/) for details.  
This extension uses the [Gig Performer SDK](https://github.com/gigperformer/gp-sdk) and is based on the gp-extension-cpp example.  

## Purpose
Provides global variables accessible between the several script types, like gig-script, rackspace-scrips, scriptlets and song-scripts. GPscript lacks this.  
You might call this extension 'headless', because it has no menus or panels. It only adds some scripting functions.
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

## How to use

### Declare a variable

-   Integer declaration
    
    ```gpscript
    var
        b : boolean
        
        b = GlobalVars_CreateInt("NumberOfSongparts")
        Print(b)
    ```

-   String declaration
    
    ```gpscript
    var
        b : boolean
        
        b = GlobalVars_CreateString("Author")
        Print(b)
    ```
    
-   Declaration with an error
    
    ```gpscript
    var
        b : boolean
        
        b = GlobalVars_CreateString("global_1")
        
        b = GlobalVars_CreateInt("global_1") // Will return false: global_1 already exists
        Print(b)
    ```
    
-   Integer array declaration

    ```gpscript
    var
        b : boolean
        
        b = GlobalVars_CreateIntArray("PowersOfTwo", 10)
        Print(b)
    ```
    
### Assigning a value

-   Assigning an integer
    
    ```gpscript
    var
        b : boolean
        
        b = GlobalVars_SetInt("NumberOfSongparts", 100)
        Print(b)
    ```
    
-   Assigning an integer in an array

    ```gpscript
    var
        b : boolean
        
        b = GlobalVars_SetIntInArray("PowersOfTwo", 0, 1)
        Print(b)
        b = GlobalVars_SetIntInArray("PowersOfTwo", 1, 2)
        Print(b)
        b = GlobalVars_SetIntInArray("PowersOfTwo", 2, 4)
        Print(b)
        b = GlobalVars_SetIntInArray("PowersOfTwo", 3, 8)
        Print(b)
    ```

-   Assigning a string
    
    ```gpscript
    var
        b : boolean
        author : string
        
        author = "Frank"
        
        b = GlobalVars_SetString("Author", author, Length(author))
        Print(b)
    ```

-   Assigning a string in an array
    
    ```gpscript
    var
        b : boolean
        contributor : string
        
        contributor = "Frank"
        b = GlobalVars_SetStringInArray("Contributors", 0, contributor, Length(contributor))
        Print(b)
        
        contributor = "Tom"
        b = GlobalVars_SetStringInArray("Contributors", 1, contributor, Length(contributor))
        Print(b)
    ```

### Getting values

-   Getting an integer

    ```gpscript
    Print (GlobalVars_GetInt("NumberOfSongparts"))
    ```

-   Getting a string

    ```gpscript
    Print (GlobalVars_GetString("Author"))
    ```

-   Getting an integer from an array

    ```gpscript
    Print (GlobalVars_GetIntFromArray("PowersOfTwo", 2))
    Print (GlobalVars_GetIntFromArray("PowersOfTwo", 3))
    ```

-   Getting a string from an array

    ```gpscript
    Print (GlobalVars_GetStringFromArray("Contributors", 0))
    Print (GlobalVars_GetStringFromArray("Contributors", 1))
    ```

### Removing variables

-   Removing specific variables

    ```gpscript
    Print (GlobalVars_DestroyVariable("Contributors"))
    Print (GlobalVars_DestroyVariable("NumberOfSongparts"))
    ```

-   Erase all

    ```gpscript
    GlobalVars_RemoveAll()
    ```

### Enabling auto Removing variables when loading a new Gig
By default, variables created in one Gig will not be erased when a new Gig
is loaded.

-   Enable:

    ```gpscript
    Print (GlobalVars_RemoveAllOnLoad(True))
    ```

-   Disable:

    ```gpscript
    Print (GlobalVars_RemoveAllOnLoad(False))
    ```

    The returnvalue is the previous state. 


### Informational

-   Variable type

    ```gpscript
    var
        tp : integer
    
        tp = GlobalVars_GetVariableType("PowersOfTwo")
        Print (tp)
        
        // 0 -> Does not exist
        // 1 -> String value
        // 2 -> Integer value
        // 3 -> Double value
        // 4 -> Boolean value

        // 17 -> String array
        // 18 -> Integer array
        // 19 -> Double array
        // 20 -> Boolean array
    ```

-   Array size

    ```gpscript
    Print (GlobalVars_GetArraySize("PowersOfTwo"))
    // -1 -> Not an array or variable does not exist
    // >= 0 -> Size (although an array with a size of 0 cannot be created)
    ```
    
