
#include "LibMain.h"
#include "string"
#include <malloc.h>

using GPUtils = gigperformer::sdk::GPUtils;
using namespace std;


#pragma region Global definitions
/// <summary>
/// Object holding all global vars
/// </summary>
std::unique_ptr<GlobalVarsMapArray> gv;

/// <summary>
/// Cache for the uuid of the Global Rackspace
/// </summary>
string GRSUuid = "";

/// <summary>
/// Holds the constructed object.
/// Provides a way to execute GP_Functions like consoleLog(..)
/// </summary>
LibMain *thisObj = nullptr;

/// Ignore a given value
/// details this is a dummy function to suppress compiler warnings about unused parameters
template <typename T>
void Ignore(T const &) noexcept
{
}

// define an XML string describing your product
const string XMLProductDescription =
    // Replace with your information
    "<Library>"
    "  <Product"
    "    Name=\"StateFullness\""
    "    Version=\"1.0\""
    "    BuildDate=\"07/31/2023\">"
    "  </Product> "
    "  <Description>Support for saving state. (c) 2023 F. den Blaauwen</Description>"
    "  <ImagePath>/Path/To/ImageFile/foo.jpg</ImagePath>"
    "</Library>";

string pathToMe; // This needs to be initialized from the initialization
                 // section of the LibMain class so it can be used in the
                 // standalone functions directly below

LibMain::LibMain(LibraryHandle handle)
    : GigPerformerAPI(handle)
{
    gv.reset(new GlobalVarsMapArray());
}

LibMain::~LibMain()
{
    thisObj = nullptr;
}
#pragma endregion


#pragma region Helper functions

string getRackspaceNameFromUuid(LibMain *gpi, string uuid)
{
    if (gpi == nullptr)
        return "";

    int rsnCnt = gpi->getRackspaceCount();

    if (uuid.compare(gpi->getRackspaceUuid(-1)) == 0)
        return "GLOBAL RACKSPACE";

    for (int i = 0; i < rsnCnt; i++)
    {
        if (gpi->getRackspaceUuid(i).compare(uuid) == 0)
        {
            return gpi->getRackspaceName(i);
        }
    }
    return "";
}

string getRackspaceUuidFromName(LibMain *gpi, string rsn)
{
    if (gpi == nullptr)
        return "";

    int rsnCnt = gpi->getRackspaceCount();

    if (rsn.compare("GLOBAL RACKSPACE") == 0)
        return gpi->getRackspaceUuid(-1);

    for (int i = 0; i < rsnCnt; i++)
    {
        if (gpi->getRackspaceName(i).compare(rsn) == 0)
        {
            return gpi->getRackspaceUuid(i);
        }
    }
    return "";
}

extern "C" void GetRackHandle(GPRuntimeEngine *vm)
{
    char rsn[100];
    GP_VM_PopString(vm, rsn, 100);

    string res = getRackspaceUuidFromName(thisObj, rsn);
    GP_VM_PushString(vm, res.c_str());
}

#pragma endregion

#pragma region Plugin calls
extern "C" void __declspec(dllexport) _stdcall ApplyState(std::string rackspaceUuid, std::string state)
{
    gv->setAllState(rackspaceUuid, state);
}

extern "C" void __declspec(dllexport) _stdcall getAllState(std::string rackspaceUuid, std::string &s)
{
    s.assign(gv->getAllState(rackspaceUuid));
}

extern "C" void __declspec(dllexport) _stdcall getRSUuid(std::string &s)
{
    if (thisObj != nullptr)
    {
        s.assign(thisObj->getRackspaceUuid(thisObj->getCurrentRackspaceIndex()));
    }
    else
        s.assign("");
}

extern "C" void __declspec(dllexport) _stdcall getRSName(std::string uuid, std::string &s)
{
    if (thisObj != nullptr)
    {
        s.assign(getRackspaceNameFromUuid(thisObj, uuid));
    }
    else
        s.assign("");
}

extern "C" void __declspec(dllexport) _stdcall getGRSUuid(std::string &s)
{
    if (thisObj != nullptr)
        s.assign(thisObj->getRackspaceUuid(-1));
    else
        s.assign("");

    GRSUuid = s;
}

#pragma endregion

#pragma region Events and housekeeping
void LibMain::OnStatusChanged(GPStatusType status)
{
    if (status == GPStatusType::GPStatus_GigStartedLoading)
        gv->RemoveAllOnLoad();

    string s;
    switch (status)
    {
    case GPStatusType::GPStatus_GigCanceledLoading:
        s = "GPStatus_GigCanceledLoading";
        break;
    case GPStatusType::GPStatus_GigFailedLoading:
        s = "GPStatus_GigFailedLoading";
        break;
    case GPStatusType::GPStatus_GigFinishedLoading:
        s = "GPStatus_GigFinishedLoading";
        break;
    case GPStatusType::GPStatus_GigStartedLoading:
        s = "GPStatus_GigStartedLoading";
        break;
    case GPStatusType::GPStatus_MetronomeStateChanged:
        s = "GPStatus_MetronomeStateChanged";
        break;
    case GPStatusType::GPStatus_RackspaceListModified:
        gv->AddRackspaceByUuid(getRackspaceUuid(getCurrentRackspaceIndex()));
        s = "GPStatus_RackspaceListModified";
        break;
    case GPStatusType::GPStatus_SaveRequest:
        s = "GPStatus_SaveRequest";
        break;
    case GPStatusType::GPStatus_SongListModifed:
        s = "GPStatus_SongListModifed";
        break;
    case GPStatusType::GPStatus_SongPartListModified:
        s = "GPStatus_SongPartListModified";
        break;
    case GPStatusType::GPStatus_VariationListModified:
        s = "GPStatus_VariationListModified";
        break;
    }
}

void LibMain::OnRackspaceActivated()
{
    gv->AddRackspaceByUuid(getRackspaceUuid(getCurrentRackspaceIndex()));
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
    registerCallback("OnRackspaceActivated");
    // pathToMe = getPathToMe();
    // consoleLog("path to library " + pathToMe);
}

string LibMain::GetProductDescription()
{
    // Generally don't touch this - simply define the constant
    // 'XMLProductDescription' at the top of this file with an XML description of
    // your product
    return XMLProductDescription;
}

#pragma endregion

#pragma region Local Rackspace
#pragma region Declaring variables
extern "C" void CreateString(GPRuntimeEngine *vm)
{
    char buffer[100];
    GP_VM_PopString(vm, buffer, 100);

    char buffer2[100];
    GP_VM_PopString(vm, buffer2, 100);

    bool res = gv->CreateString(buffer2, buffer);
    GP_VM_PushBoolean(vm, res);
}

extern "C" void CreateInt(GPRuntimeEngine *vm)
{
    char buffer[100];
    GP_VM_PopString(vm, buffer, 100);
    char buffer2[100];
    GP_VM_PopString(vm, buffer2, 100);

    bool res = gv->CreateInt(buffer2, buffer);

    GP_VM_PushBoolean(vm, res);
}

extern "C" void CreateDouble(GPRuntimeEngine *vm)
{
    char buffer[100];
    GP_VM_PopString(vm, buffer, 100);

    char buffer2[100];
    GP_VM_PopString(vm, buffer2, 100);

    bool res = gv->CreateDouble(buffer2, buffer);
    GP_VM_PushBoolean(vm, res);
}

extern "C" void CreateBool(GPRuntimeEngine *vm)
{
    char buffer[100];
    GP_VM_PopString(vm, buffer, 100);

    char buffer2[100];
    GP_VM_PopString(vm, buffer2, 100);

    bool res = gv->CreateBool(buffer2, buffer);
    GP_VM_PushBoolean(vm, res);
}
#pragma endregion

#pragma region Delete variables
extern "C" void DestroyVariable(GPRuntimeEngine *vm)
{
    char name[100];
    GP_VM_PopString(vm, name, 100);

    char buffer2[100];
    GP_VM_PopString(vm, buffer2, 100);

    bool res = gv->DestroyVariable(buffer2, name);

    GP_VM_PushBoolean(vm, res);
}

extern "C" void RemoveAllFromRack(GPRuntimeEngine *vm)
{
    char buffer2[100];
    GP_VM_PopString(vm, buffer2, 100);
    gv->RemoveAllPerRack(buffer2);
}
#pragma endregion

#pragma region Assigning values
extern "C" void SetString(GPRuntimeEngine *vm)
{
    int len = GP_VM_TopStringLength(vm);
    char name[100];
    char handle[100];
    if (len < 0)
    {
        // Just pop and push the stack
        char dummy[5];
        GP_VM_PopString(vm, dummy, 1);
        GP_VM_PopString(vm, name, 100);
        GP_VM_PopString(vm, handle, 100);
        GP_VM_PushBoolean(vm, false);
        return;
    }
    else
    {
        char *value = (char *)malloc(len + 1);

        GP_VM_PopString(vm, value, len + 1);
        GP_VM_PopString(vm, name, 100);
        GP_VM_PopString(vm, handle, 100);

        bool res = false;
        if (value != nullptr)
            res = gv->SetString(handle, name, string(value, len));

        GP_VM_PushBoolean(vm, res);
        free(value);
    }
}

extern "C" void SetInt(GPRuntimeEngine *vm)
{
    char name[100];
    int value = GP_VM_PopInteger(vm);
    GP_VM_PopString(vm, name, 100);
    char buffer2[100];
    GP_VM_PopString(vm, buffer2, 100);

    bool res = gv->SetInt(buffer2, name, value);

    GP_VM_PushBoolean(vm, res);
}

extern "C" void SetDouble(GPRuntimeEngine *vm)
{
    char name[100];
    double value = GP_VM_PopDouble(vm);
    GP_VM_PopString(vm, name, 100);
    char buffer2[100];
    GP_VM_PopString(vm, buffer2, 100);

    bool res = gv->SetDouble(buffer2, name, value);

    GP_VM_PushBoolean(vm, res);
}

extern "C" void SetBool(GPRuntimeEngine *vm)
{
    char name[100];
    bool value = GP_VM_PopBoolean(vm);
    GP_VM_PopString(vm, name, 100);
    char buffer2[100];
    GP_VM_PopString(vm, buffer2, 100);

    bool res = gv->SetBool(buffer2, name, value);

    GP_VM_PushBoolean(vm, res);
}
#pragma endregion

#pragma region Get Values
extern "C" void GetStringValue(GPRuntimeEngine *vm)
{
    char name[100];
    GP_VM_PopString(vm, name, 100);
    char buffer2[100];
    GP_VM_PopString(vm, buffer2, 100);

    string res = gv->GetStringValue(buffer2, name);
    GP_VM_PushString(vm, res.c_str());
}

extern "C" void GetIntValue(GPRuntimeEngine *vm)
{
    char name[100];
    GP_VM_PopString(vm, name, 100);
    char buffer2[100];
    GP_VM_PopString(vm, buffer2, 100);

    int value = gv->GetIntValue(buffer2, name);

    GP_VM_PushInteger(vm, value);
}

extern "C" void GetDoubleValue(GPRuntimeEngine *vm)
{
    char name[100];
    GP_VM_PopString(vm, name, 100);
    char buffer2[100];
    GP_VM_PopString(vm, buffer2, 100);

    double value = gv->GetDoubleValue(buffer2, name);

    GP_VM_PushDouble(vm, value);
}

extern "C" void GetBoolValue(GPRuntimeEngine *vm)
{
    char name[100];
    GP_VM_PopString(vm, name, 100);
    char buffer2[100];
    GP_VM_PopString(vm, buffer2, 100);

    bool value = gv->GetDoubleValue(buffer2, name);

    GP_VM_PushBoolean(vm, value);
}

extern "C" void dumpAllVars(GPRuntimeEngine *vm)
{
    char uuid[100];
    GP_VM_PopString(vm, uuid, 100);

    string rsn = getRackspaceNameFromUuid(thisObj, uuid);

    gv->dumpAllState(uuid, thisObj, rsn);
}


#pragma endregion
#pragma endregion

#pragma region Global Rackspace
#pragma region Declaring variables
extern "C" void CreateStringG(GPRuntimeEngine *vm)
{
    char buffer[100];
    GP_VM_PopString(vm, buffer, 100);

    bool res = gv->CreateString(GRSUuid, buffer);
    GP_VM_PushBoolean(vm, res);
}

extern "C" void CreateIntG(GPRuntimeEngine *vm)
{
    char buffer[100];
    GP_VM_PopString(vm, buffer, 100);

    bool res = gv->CreateInt(GRSUuid, buffer);

    GP_VM_PushBoolean(vm, res);
}

extern "C" void CreateDoubleG(GPRuntimeEngine *vm)
{
    char buffer[100];
    GP_VM_PopString(vm, buffer, 100);

    bool res = gv->CreateDouble(GRSUuid, buffer);
    GP_VM_PushBoolean(vm, res);
}

extern "C" void CreateBoolG(GPRuntimeEngine *vm)
{
    char buffer[100];
    GP_VM_PopString(vm, buffer, 100);

    bool res = gv->CreateBool(GRSUuid, buffer);
    GP_VM_PushBoolean(vm, res);
}
#pragma endregion

#pragma region Delete variables
extern "C" void DestroyVariableG(GPRuntimeEngine *vm)
{
    char name[100];
    GP_VM_PopString(vm, name, 100);

    bool res = gv->DestroyVariable(GRSUuid, name);

    GP_VM_PushBoolean(vm, res);
}

extern "C" void RemoveAllFromRackG(GPRuntimeEngine *vm)
{
    gv->RemoveAllPerRack(GRSUuid);
}

#pragma endregion

#pragma region Assigning values
extern "C" void SetStringG(GPRuntimeEngine *vm)
{
    int len = GP_VM_TopStringLength(vm);
    char name[100];
    char handle[100];
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

        bool res = false;
        if (value != nullptr)
            res = gv->SetString(GRSUuid, name, string(value, len));

        GP_VM_PushBoolean(vm, res);
        free(value);
    }
}

extern "C" void SetIntG(GPRuntimeEngine *vm)
{
    char name[100];
    int value = GP_VM_PopInteger(vm);
    GP_VM_PopString(vm, name, 100);

    bool res = gv->SetInt(GRSUuid, name, value);

    GP_VM_PushBoolean(vm, res);
}

extern "C" void SetDoubleG(GPRuntimeEngine *vm)
{
    char name[100];
    double value = GP_VM_PopDouble(vm);
    GP_VM_PopString(vm, name, 100);

    bool res = gv->SetDouble(GRSUuid, name, value);

    GP_VM_PushBoolean(vm, res);
}

extern "C" void SetBoolG(GPRuntimeEngine *vm)
{
    char name[100];
    bool value = GP_VM_PopBoolean(vm);
    GP_VM_PopString(vm, name, 100);

    bool res = gv->SetBool(GRSUuid, name, value);

    GP_VM_PushBoolean(vm, res);
}
#pragma endregion

#pragma region Get Values
extern "C" void GetStringValueG(GPRuntimeEngine *vm)
{
    char name[100];
    GP_VM_PopString(vm, name, 100);

    string res = gv->GetStringValue(GRSUuid, name);
    GP_VM_PushString(vm, res.c_str());
}

extern "C" void GetIntValueG(GPRuntimeEngine *vm)
{
    char name[100];
    GP_VM_PopString(vm, name, 100);

    int value = gv->GetIntValue(GRSUuid, name);

    GP_VM_PushInteger(vm, value);
}

extern "C" void GetDoubleValueG(GPRuntimeEngine *vm)
{
    char name[100];
    GP_VM_PopString(vm, name, 100);

    double value = gv->GetDoubleValue(GRSUuid, name);

    GP_VM_PushDouble(vm, value);
}

extern "C" void GetBoolValueG(GPRuntimeEngine *vm)
{
    char name[100];
    GP_VM_PopString(vm, name, 100);

    bool value = gv->GetDoubleValue(GRSUuid, name);

    GP_VM_PushBoolean(vm, value);
}

extern "C" void dumpAllVarsG(GPRuntimeEngine *vm)
{
    gv->dumpAllState(GRSUuid, thisObj, "GLOBAL RACKSPACE");
}

#pragma endregion

#pragma region VarInfo

extern "C" void GetVariableTypeG(GPRuntimeEngine *vm)
{
    char name[100];
    GP_VM_PopString(vm, name, 100);

    int res = gv->GetVariableType(GRSUuid, name);

    GP_VM_PushInteger(vm, res);
}


#pragma endregion
#pragma endregion

#pragma region All Rackspaces
extern "C" void GetVariableType(GPRuntimeEngine *vm)
{
    char name[100];
    GP_VM_PopString(vm, name, 100);
    char buffer2[100];
    GP_VM_PopString(vm, buffer2, 100);

    int res = gv->GetVariableType(buffer2, name);

    GP_VM_PushInteger(vm, res);
}

extern "C" void RemoveAll(GPRuntimeEngine *vm)
{
    gv->RemoveAll();
}

#pragma endregion

#pragma region Definitions

ExternalAPI_GPScriptFunctionDefinition functionList[] = {
    {"CreateString", "handle:String, name:String", "Returns boolean", "Creates a global string ", CreateString},
    {"CreateInt", "handle:String, name:String", "Returns boolean", "Creates a global integer", CreateInt},
    {"CreateDouble", "handle:String, name:String", "Returns boolean", "Creates a global double", CreateDouble},
    {"CreateBoolean", "handle:String, name:String", "Returns boolean", "Creates a global boolean", CreateBool},

    {"SetString", "handle:String, name:String, value:String", "Returns boolean", "Assigns a string value", SetString},
    {"SetInt", "handle:String, name:String, value:integer", "Returns boolean", "Assigns an integer value", SetInt},
    {"SetDouble", "handle:String, name:String, value:Double", "Returns boolean", "Assigns a double value", SetDouble},
    {"SetBoolean", "handle:String, name:String, value:boolean", "Returns boolean", "Assigns a boolean value", SetBool},

    {"GetStringValue", "handle:String, name:String", "Returns string", "Retrieves the value of a global string", GetStringValue},
    {"GetIntValue", "handle:String, name:String", "Returns integer", "Retrieves the value of a global integer", GetIntValue},
    {"GetDoubleValue", "handle:String, name:String", "Returns Double", "Retrieves the value of a global double", GetDoubleValue},
    {"GetBooleanValue", "handle:String, name:String", "Returns boolean", "Retrieves the value of a global boolean", GetBoolValue},
    {"DumpAllVars", "handle:String", "", "Dumps all varaibles of this rackspace to the log", dumpAllVars},

    {"DestroyVariable", "handle:String, name:String", "Returns boolean", "Removes a global variable", DestroyVariable},
    {"GetVariableType", "handle:String, name:String", "Returns integer", "Get the type of a variable or 0 if it does not exist", GetVariableType},
    {"GetRackHandle", "name:String", "Returns string", "Gets the handle of to a rackspace", GetRackHandle},
    {"RemoveAllFromRack", "handle:String", "", "Erases all Variables from a rackspace", RemoveAllFromRack},
    {"RemoveAll", "", "", "Erases all Variables from all racks", RemoveAll},
};

ExternalAPI_GPScriptFunctionDefinition functionListGlobal[] = {
    {"CreateString", "name:String", "Returns boolean", "Creates a global string ", CreateStringG},
    {"CreateInt", "name:String", "Returns boolean", "Creates a global integer", CreateIntG},
    {"CreateDouble", "name:String", "Returns boolean", "Creates a global double", CreateDoubleG},
    {"CreateBoolean", "name:String", "Returns boolean", "Creates a global boolean", CreateBoolG},

    {"SetString", "name:String, value:String", "Returns boolean", "Assigns a string value", SetStringG},
    {"SetInt", "name:String, value:integer", "Returns boolean", "Assigns an integer value", SetIntG},
    {"SetDouble", "name:String, value:Double", "Returns boolean", "Assigns a double value", SetDoubleG},
    {"SetBoolean", "name:String, value:boolean", "Returns boolean", "Assigns a boolean value", SetBoolG},

    {"GetStringValue", "name:String", "Returns string", "Retrieves the value of a global string", GetStringValueG},
    {"GetIntValue", "name:String", "Returns integer", "Retrieves the value of a global integer", GetIntValueG},
    {"GetDoubleValue", "name:String", "Returns Double", "Retrieves the value of a global double", GetDoubleValueG},
    {"GetBooleanValue", "handle:String, name:String", "Returns boolean", "Retrieves the value of a global boolean", GetBoolValueG},
    {"DumpAllVars", "", "", "Dumps all varaibles of this rackspace to the log", dumpAllVarsG},

    {"DestroyVariable", "name:String", "Returns boolean", "Removes a global variable", DestroyVariableG},
    {"GetVariableType", "name:String", "Returns integer", "Get the type of a variable or 0 if it does not exist", GetVariableTypeG},
    {"GetRackHandle", "name:String", "Returns string", "Gets the handle of to a rackspace", GetRackHandle},
    {"RemoveAllFromRack", "", "", "Erases all Variablesfrom the Global Rackspace", RemoveAllFromRackG},
    {"RemoveAll", "", "", "Erases all Variables from all racks", RemoveAll},
};

int LibMain::RequestGPScriptFunctionSignatureList(GPScript_AllowedLocations location,
                                                  ExternalAPI_GPScriptFunctionDefinition **list)
{
    if (location == GPScript_AllowedLocations::GPScript_Rackspace)
    {
        *list = functionList;
        return sizeof(functionList) / sizeof(ExternalAPI_GPScriptFunctionDefinition);
    }

    if (location == GPScript_AllowedLocations::GPScript_GlobalRackspace)
    {
        *list = functionListGlobal;
        return sizeof(functionListGlobal) / sizeof(ExternalAPI_GPScriptFunctionDefinition);
    }

    return 0;
}

#pragma endregion

namespace gigperformer::sdk
{
GigPerformerAPI *CreateGPExtension(LibraryHandle handle)
{
    return new LibMain(handle);
}
} // namespace gigperformer::sdk
