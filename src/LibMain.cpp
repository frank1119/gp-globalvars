#include "LibMain.h"
#include "string"
#include <malloc.h>

using GPUtils = gigperformer::sdk::GPUtils;
using namespace std;

/// <summary>
/// Object holding all global vars
/// </summary>
GlobalVarsMap gv;

bool eraseOnReload = false;


/// <summary>
/// Holds the constructed object.
/// Provides a way to execute GP_Functions like consoleLog(..)
/// </summary>
LibMain *thisObj = nullptr;

/// Ignore a given value
/// \details this is a dummy function to suppress compiler warnings about unused parameters
template <typename T>
void Ignore(T const &) noexcept
{
}

// define an XML string describing your product
const string XMLProductDescription =
    // Replace with your information
    "<Library>"
    "  <Product"
    "    Name=\"GlobalVars\""
    "    Version=\"1.0\""
    "    BuildDate=\"06/13/2024\">"
    "  </Product> "
    "  <Description>Support for sharing variables between all scripts. (c) 2022 F. den Blaauwen</Description>"
    "  <ImagePath>/Path/To/ImageFile/foo.jpg</ImagePath>"
    "</Library>";

string pathToMe; // This needs to be initialized from the initialization
                 // section of the LibMain class so it can be used in the
                 // standalone functions directly below

LibMain::~LibMain()
{
    thisObj = nullptr;
}

#pragma region Events and housekeeping
void LibMain::OnStatusChanged(GPStatusType status)
{
    if (status == GPStatusType::GPStatus_GigStartedLoading && eraseOnReload)
        gv.RemoveAll();
}

void LibMain::Initialization()
{
    // Dirty way to make some instance methods, like consoleLog() available for
    // library-defined script functions
    thisObj = this;
    // Do any initialization that you need

    // .... your code here

    // Finally, register all the methods that you are going to actually use,
    // i.e, the ones you declared above as override
    registerCallback("OnStatusChanged");

    pathToMe = getPathToMe();
    consoleLog("path to library " + pathToMe);
}

string LibMain::GetProductDescription()
{
    // Generally don't touch this - simply define the constant
    // 'XMLProductDescription' at the top of this file with an XML description of
    // your product
    return XMLProductDescription;
}
#pragma endregion

#pragma region Declaring variables
extern "C" void CreateString(GPRuntimeEngine *vm)
{
    char buffer[100];
    GP_VM_PopString(vm, buffer, 100);

    bool res = gv.CreateString(buffer);

    GP_VM_PushBoolean(vm, res);

    //string rsn = thisObj->getRackspaceName(thisObj->getCurrentRackspaceIndex());
    
    //thisObj->consoleLog ("Testje " + rsn);
}

extern "C" void CreateInt(GPRuntimeEngine *vm)
{
    char buffer[100];
    GP_VM_PopString(vm, buffer, 100);

    bool res = gv.CreateInt(buffer);

    GP_VM_PushBoolean(vm, res);
}

extern "C" void CreateDouble(GPRuntimeEngine *vm)
{
    char buffer[100];

    GP_VM_PopString(vm, buffer, 100);

    bool res = gv.CreateDouble(buffer);
    GP_VM_PushBoolean(vm, res);
}

extern "C" void CreateBool(GPRuntimeEngine *vm)
{
    char buffer[100];

    GP_VM_PopString(vm, buffer, 100);

    bool res = gv.CreateBool(buffer);
    GP_VM_PushBoolean(vm, res);
}

extern "C" void CreateStringArray(GPRuntimeEngine *vm)
{
    char buffer[100];
    int size = GP_VM_PopInteger(vm);

    GP_VM_PopString(vm, buffer, 100);

    bool res = gv.CreateString(buffer, size);
    GP_VM_PushBoolean(vm, res);
}

extern "C" void CreateIntArray(GPRuntimeEngine *vm)
{
    char buffer[100];
    int size = GP_VM_PopInteger(vm);

    GP_VM_PopString(vm, buffer, 100);

    bool res = gv.CreateInt(buffer, size);
    GP_VM_PushBoolean(vm, res);
}

extern "C" void CreateDoubleArray(GPRuntimeEngine *vm)
{
    char buffer[100];
    int size = GP_VM_PopInteger(vm);
    GP_VM_PopString(vm, buffer, 100);

    bool res = gv.CreateDouble(buffer, size);

    GP_VM_PushBoolean(vm, res);
}

extern "C" void CreateBoolArray(GPRuntimeEngine *vm)
{
    char buffer[100];
    int size = GP_VM_PopInteger(vm);
    GP_VM_PopString(vm, buffer, 100);

    bool res = gv.CreateBool(buffer, size);

    GP_VM_PushBoolean(vm, res);
}

#pragma endregion

#pragma region Delete variables
extern "C" void DestroyVariable(GPRuntimeEngine *vm)
{
    char name[100];
    GP_VM_PopString(vm, name, 100);

    bool res = gv.DestroyVariable(name);

    GP_VM_PushBoolean(vm, res);
}

extern "C" void RemoveAll(GPRuntimeEngine *vm)
{
    gv.RemoveAll();
}

extern "C" void RemoveAllOnLoad(GPRuntimeEngine *vm)
{
    bool state = eraseOnReload;
 
    eraseOnReload = GP_VM_PopBoolean(vm);
    
    GP_VM_PushBoolean(vm, state);
}
#pragma endregion

#pragma region Assigning values
extern "C" void SetString(GPRuntimeEngine *vm)
{
    int len = GP_VM_PopInteger(vm);
    char name[100];
    if (len < 0)
    {
        // Just pop and push the stack
        char dummy[5];
        GP_VM_PopString(vm, dummy, 1);
        GP_VM_PopString(vm, name, 100);
        GP_VM_PushBoolean(vm, false);
        return;
    }
    else
    {
        char *value = (char *)malloc(len + 1);
        GP_VM_PopString(vm, value, len + 1);
        GP_VM_PopString(vm, name, 100);

        bool res = gv.SetString(name, string(value));

        GP_VM_PushBoolean(vm, res);
        free(value);
    }
}

extern "C" void SetInt(GPRuntimeEngine *vm)
{
    char name[100];
    int value = GP_VM_PopInteger(vm);
    GP_VM_PopString(vm, name, 100);

    bool res = gv.SetInt(name, value);

    GP_VM_PushBoolean(vm, res);
}

extern "C" void SetDouble(GPRuntimeEngine *vm)
{
    char name[100];
    double value = GP_VM_PopDouble(vm);
    GP_VM_PopString(vm, name, 100);

    bool res = gv.SetDouble(name, value);

    GP_VM_PushBoolean(vm, res);
}

extern "C" void SetBool(GPRuntimeEngine *vm)
{
    char name[100];
    bool value = GP_VM_PopBoolean(vm);
    GP_VM_PopString(vm, name, 100);

    bool res = gv.SetBool(name, value);

    GP_VM_PushBoolean(vm, res);
}

extern "C" void SetStringInArray(GPRuntimeEngine *vm)
{
    int len = GP_VM_PopInteger(vm);

    char name[100];

    if (len < 0)
    {
        // Just pop and push the stack
        char dummy[5];
        GP_VM_PopString(vm, dummy, 1);
        GP_VM_PopString(vm, name, 100);
        int index = GP_VM_PopInteger(vm);
        GP_VM_PushBoolean(vm, false);
        return;
    }
    else
    {
        char *value = (char *)malloc(len + 1);
        GP_VM_PopString(vm, value, len + 1);
        int index = GP_VM_PopInteger(vm);
        GP_VM_PopString(vm, name, 100);

        bool res = gv.SetString(name, index, string(value));

        GP_VM_PushBoolean(vm, res);
        free(value);
    }
}

extern "C" void SetIntInArray(GPRuntimeEngine *vm)
{
    int value = GP_VM_PopInteger(vm);
    char name[100];
    int index = GP_VM_PopInteger(vm);
    GP_VM_PopString(vm, name, 100);

    bool res = gv.SetInt(name, index, value);

    GP_VM_PushBoolean(vm, res);
}

extern "C" void SetDoubleInArray(GPRuntimeEngine *vm)
{
    double value = GP_VM_PopInteger(vm);
    char name[100];
    int index = GP_VM_PopInteger(vm);
    GP_VM_PopString(vm, name, 100);

    bool res = gv.SetDouble(name, index, value);

    GP_VM_PushBoolean(vm, res);
}

extern "C" void SetBoolInArray(GPRuntimeEngine *vm)
{
    bool value = GP_VM_PopBoolean(vm);
    char name[100];
    int index = GP_VM_PopInteger(vm);
    GP_VM_PopString(vm, name, 100);

    bool res = gv.SetBool(name, index, value);

    GP_VM_PushBoolean(vm, res);
}
#pragma endregion

#pragma region Get Values
extern "C" void GetStringValue(GPRuntimeEngine *vm)
{
    char name[100];
    GP_VM_PopString(vm, name, 100);

    string res = gv.GetStringValue(name);

    GP_VM_PushString(vm, res.c_str());
}

extern "C" void GetIntValue(GPRuntimeEngine *vm)
{
    char name[100];
    GP_VM_PopString(vm, name, 100);

    int value = gv.GetIntValue(name);

    GP_VM_PushInteger(vm, value);
}

extern "C" void GetDoubleValue(GPRuntimeEngine *vm)
{
    char name[100];
    GP_VM_PopString(vm, name, 100);
    double value = gv.GetDoubleValue(name);

    GP_VM_PushDouble(vm, value);
}

extern "C" void GetBoolValue(GPRuntimeEngine *vm)
{
    char name[100];
    GP_VM_PopString(vm, name, 100);
    bool value = gv.GetDoubleValue(name);

    GP_VM_PushBoolean(vm, value);
}

extern "C" void GetStringValueFromArray(GPRuntimeEngine *vm)
{
    char name[100];
    int index = GP_VM_PopInteger(vm);
    GP_VM_PopString(vm, name, 100);

    string res = gv.GetStringValue(name, index);

    GP_VM_PushString(vm, res.c_str());
}

extern "C" void GetIntValueFromArray(GPRuntimeEngine *vm)
{
    char name[100];
    int index = GP_VM_PopInteger(vm);
    GP_VM_PopString(vm, name, 100);

    int value = gv.GetIntValue(name, index);

    GP_VM_PushInteger(vm, value);
}

extern "C" void GetDoubleValueFromArray(GPRuntimeEngine *vm)
{
    char name[100];
    int index = GP_VM_PopInteger(vm);

    GP_VM_PopString(vm, name, 100);

    double value = gv.GetDoubleValue(name, index);

    GP_VM_PushDouble(vm, value);
}

extern "C" void GetBoolValueFromArray(GPRuntimeEngine *vm)
{
    char name[100];
    int index = GP_VM_PopInteger(vm);

    GP_VM_PopString(vm, name, 100);

    bool value = gv.GetBoolValue(name, index);

    GP_VM_PushBoolean(vm, value);
}

#pragma endregion

#pragma region Info
extern "C" void GetVariableType(GPRuntimeEngine *vm)
{
    char name[100];
    GP_VM_PopString(vm, name, 100);

    int res = gv.GetVariableType(name);

    GP_VM_PushInteger(vm, res);
}

extern "C" void GetArraySize(GPRuntimeEngine *vm)
{
    char name[100];
    GP_VM_PopString(vm, name, 100);

    int res = gv.GetArraySize(name);

    GP_VM_PushInteger(vm, res);
}
#pragma endregion

#pragma region Definitions
ExternalAPI_GPScriptFunctionDefinition functionList[] = {
    {"CreateString", "name:String", "Returns boolean", "Creates a global string ", CreateString},
    {"CreateInt", "name:String", "Returns boolean", "Creates a global integer", CreateInt},
    {"CreateDouble", "name:String", "Returns boolean", "Creates a global double", CreateDouble},
    {"CreateBoolean", "name:String", "Returns boolean", "Creates a global boolean", CreateBool},

    {"CreateStringArray", "name:String, size:integer", "Returns boolean", "Creates a global string array", CreateStringArray},
    {"CreateIntArray", "name:String, size:integer", "Returns boolean", "Creates a global integer array", CreateIntArray},
    {"CreateDoubleArray", "name:String, size:integer", "Returns boolean", "Creates a global double array", CreateDoubleArray},
    {"CreateBooleanArray", "name:String, size:integer", "Returns boolean", "Creates a global boolean array", CreateBoolArray},

    {"SetString", "name:String, value:String, len:integer", "Returns boolean", "Assigns a string value", SetString},
    {"SetInt", "name:String, value:integer", "Returns boolean", "Assigns an integer value", SetInt},
    {"SetDouble", "name:String, value:Double", "Returns boolean", "Assigns a double value", SetDouble},
    {"SetBoolean", "name:String, value:boolean", "Returns boolean", "Assigns a boolean value", SetBool},

    {"SetStringInArray", "name:String, index:integer, value:String, len:integer", "Returns boolean", "Assigns a string value", SetStringInArray},
    {"SetIntInArray", "name:String, index:integer, value:integer", "Returns boolean", "Assigns an integer value", SetIntInArray},
    {"SetDoubleInArray", "name:String, index:integer, value:Double", "Returns boolean", "Assigns a double value", SetDoubleInArray},
    {"SetBooleanInArray", "name:String, index:integer, value:boolean", "Returns boolean", "Assigns a boolean value", SetBoolInArray},

    {"GetStringValue", "name:String", "Returns string", "Retrieves the value of a global string", GetStringValue},
    {"GetIntValue", "name:String", "Returns integer", "Retrieves the value of a global integer", GetIntValue},
    {"GetDoubleValue", "name:String", "Returns Double", "Retrieves the value of a global double", GetDoubleValue},
    {"GetBooleanValue", "name:String", "Returns boolean", "Retrieves the value of a global boolean", GetBoolValue},

    {"GetStringValueFromArray", "name:String, index:integer", "Returns string", "Retrieves the value of a global string", GetStringValueFromArray},
    {"GetIntValueFromArray", "name:String, index:integer", "Returns integer", "Retrieves the value of a global integer", GetIntValueFromArray},
    {"GetDoubleValueFromArray", "name:String, index:integer", "Returns Double", "Retrieves the value of a global double", GetDoubleValueFromArray},
    {"GetBooleanValueFromArray", "name:String, index:integer", "Returns boolean", "Retrieves the value of a global boolean", GetBoolValueFromArray},

    {"DestroyVariable", "name:String", "Returns boolean", "Removes a global variable", DestroyVariable},
    {"GetVariableType", "name:String", "Returns integer", "Get the type of a variable or 0 if it does not exist", GetVariableType},
    {"GetArraySize", "name:String", "Returns integer", "Get the size of an array or -1 if there is no such array", GetArraySize},
    {"RemoveAll", "", "", "Erases all Variables", RemoveAll},

    {"RemoveAllOnLoad", "enable:boolean", "Returns boolean", "Erase all Variables on Gig load. Returns the previous state", RemoveAllOnLoad},

};

int LibMain::RequestGPScriptFunctionSignatureList(GPScript_AllowedLocations location,
                                                  ExternalAPI_GPScriptFunctionDefinition **list)
{
    Ignore(location);
    // Allow these in ANY script so no need to check the location field
    *list = functionList;
    int count = sizeof(functionList) / sizeof(ExternalAPI_GPScriptFunctionDefinition);
    return count;
}

#pragma endregion

namespace gigperformer
{
namespace sdk
{

GigPerformerAPI *CreateGPExtension(LibraryHandle handle)
{
    return new LibMain(handle);
}

} // namespace sdk
} // namespace gigperformer
