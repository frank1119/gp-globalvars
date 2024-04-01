#pragma once

#include "GlobalVarsMapArray.h"
#include "gigperformer/sdk/GPMidiMessages.h"
#include "gigperformer/sdk/GPUtils.h"
#include "gigperformer/sdk/GigPerformerAPI.h"
#include "gigperformer/sdk/types.h"

class LibMain : public gigperformer::sdk::GigPerformerAPI
{
  protected:
  public:
    // These must be here but no need to do anything unless you want extra behavior
    LibMain(LibraryHandle handle);

    ~LibMain() override;

    void OnStatusChanged(GPStatusType status) override;

    void Initialization() override;

    int RequestGPScriptFunctionSignatureList(GPScript_AllowedLocations location,
                                             ExternalAPI_GPScriptFunctionDefinition **list) override;


    void OnRackspaceActivated() override;

    // This MUST be defined in your class
    string GetProductDescription() override;

};
