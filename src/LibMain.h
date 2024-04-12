#pragma once

#include "GlobalVarsMap.h"
#include "gigperformer/sdk/GPMidiMessages.h"
#include "gigperformer/sdk/GPUtils.h"
#include "gigperformer/sdk/GigPerformerAPI.h"
#include "gigperformer/sdk/types.h"
class LibMain;
class LibMain : public gigperformer::sdk::GigPerformerAPI
{
  protected:
  public:
    static LibMain *thisObj;
      // These must be here but no need to do anything unless you want extra behavior
    explicit LibMain(LibraryHandle handle)
        : GigPerformerAPI(handle)
    {
        thisObj = this;
    }

    ~LibMain() override;

    void OnStatusChanged(GPStatusType status) override;

    void Initialization() override;

    int RequestGPScriptFunctionSignatureList(GPScript_AllowedLocations location,
                                             ExternalAPI_GPScriptFunctionDefinition **list) override;

    // This MUST be defined in your class
    string GetProductDescription() override;
};
