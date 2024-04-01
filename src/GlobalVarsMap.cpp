#include "GlobalVarsMap.h"
#include "GlobalVarsMapArray.h"
#include "LibMain.h"

#define reg regex("[A-Za-z][A-Za-z0-9_]{0,39}")

string getRackspaceNameFromUuid(LibMain *gpi, string uuid);

void addBoolJson(json &jarray, string name, bool value)
{
    json j;
    j[name] = {{"type", "bool"}, {"value", value}};
    jarray.push_back(j);
}

void addIntJson(json &jarray, string name, int value)
{
    json j;
    j[name] = {{"type", "int"}, {"value", value}};
    jarray.push_back(j);
}

void addDoubleJson(json &jarray, string name, double value)
{
    json j;
    j[name] = {{"type", "double"}, {"value", value}};
    jarray.push_back(j);
}

void addStringJson(json &jarray, string name, string value)
{
    json j;
    j[name] = {{"type", "string"}, {"value", value}};
    jarray.push_back(j);
}

bool GlobalVarsMap::CreateString(const string name)
{
    if (dict.count(name) == 0)
    {
        GlobalVar *v = new GlobalVar(valueTypes::typeString);
        dict[name].reset(v);
        return true;
    }
    return false;
}

bool GlobalVarsMap::CreateInt(const string name)
{
    if (dict.count(name) == 0)
    {
        GlobalVar *v = new GlobalVar(valueTypes::typeInt);
        dict[name].reset(v);
        return true;
    }
    return false;
}

bool GlobalVarsMap::CreateDouble(const string name)
{
    if (dict.count(name) == 0)
    {
        GlobalVar *v = new GlobalVar(valueTypes::typeDouble);
        dict[name].reset(v);
        return true;
    }
    return false;
}

bool GlobalVarsMap::CreateBool(const string name)
{
    if (dict.count(name) == 0)
    {
        GlobalVar *v = new GlobalVar(valueTypes::typeBoolean);
        dict[name].reset(v);
        return true;
    }
    return false;
}

int GlobalVarsMap::GetVariableType(const string name)
{
    return (dict.count(name) == 1) ? dict[name]->getType() : 0;
}

bool GlobalVarsMap::SetString(const string name, const string value)
{
    if (dict.count(name) == 1)
        return dict[name]->assignString(value);
    return false;
}

bool GlobalVarsMap::SetInt(const string name, int value)
{
    if (dict.count(name) == 1)
        return dict[name]->assignInt(value);
    return false;
}

bool GlobalVarsMap::SetDouble(const string name, double value)
{
    if (dict.count(name) == 1)
        return dict[name]->assignDouble(value);
    return false;
}

bool GlobalVarsMap::SetBool(const string name, bool value)
{
    if (dict.count(name) == 1)
        return dict[name]->assignBool(value);
    return false;
}

string GlobalVarsMap::GetStringValue(const string name)
{
    if (dict.count(name) == 1)
        return dict[name]->getStringValue();
    return "";
}

int GlobalVarsMap::GetIntValue(const string name)
{
    if (dict.count(name) == 1)
        return dict[name]->getIntValue();
    return 0;
}

double GlobalVarsMap::GetDoubleValue(const string name)
{
    if (dict.count(name) == 1)
        return dict[name]->getDoubleValue();
    return 0;
}

bool GlobalVarsMap::GetBoolValue(const string name)
{
    if (dict.count(name) == 1)
        return dict[name]->getBoolValue();
    return 0;
}

bool GlobalVarsMap::DestroyVariable(const string name)
{
    if (dict.count(name) == 1)
    {
        dict.erase(name);
        return true;
    }
    return false;
}

void GlobalVarsMap::RemoveAll()
{
    //for (auto j = begin(dict); j != end(dict); j++)
    //    delete j->second;
    dict.clear();
}

json GlobalVarsMap::getAllState()
{
    json j2;
    for (auto i = begin(dict); i != end(dict); i++)
    {
        string name = i->first;
        auto gv = i->second.get();

        switch (gv->getType())
        {
        case valueTypes::typeString:
            addStringJson(j2, name, gv->getStringValue());
            break;
        case valueTypes::typeDouble:
            addDoubleJson(j2, name, gv->getDoubleValue());
            break;
        case valueTypes::typeInt:
            addDoubleJson(j2, name, gv->getIntValue());
            break;
        case valueTypes::typeBoolean:
            addDoubleJson(j2, name, gv->getBoolValue());
            break;
        }
    }
    
    return j2;
}

void GlobalVarsMap::setAllState(string jstate)
{
    json j2;

    j2 = j2.parse(jstate);

    for (auto i = begin(j2); i != end(j2); i++)
    {
        ProcessRecord(i.value());
    }
}

void GlobalVarsMap::ProcessRecord(json j)
{
    json i = j.front();
    string varName = j.begin().key();

    if (i.contains("type"))
    {
        auto jv = i.at("type");
        if (jv.is_string())
        {
            string tp;
            jv.get_to(tp);
        }
    }
    else
        return;

    if (i.contains("value"))
    {
        auto jv = i.at("value");

        switch ((int)jv.front().type())
        {
        case 3: {
            string val;
            jv.get_to(val);
            CreateString(varName);
            SetString(varName, val);
            break;
        }
        case 4: {
            bool val;
            jv.get_to(val);
            CreateBool(varName);
            SetBool(varName, val);
            break;
        }
        case 7: {
            double val;
            jv.get_to(val);
            CreateDouble(varName);
            SetDouble(varName, val);
            break;
        }
        case 5: {
            int val;
            jv.get_to(val);
            CreateInt(varName);
            SetInt(varName, val);
            break;
        }
        }
    }
    else
        return;

}

void GlobalVarsMap::dumpAllState(LibMain *lib, string rackspaceName)
{
    //LibMain *lib2 = (LibMain*)lib;

    lib->consoleLog("+------------------------------------------------------------------");
    lib->consoleLog(string("| Dump StateFullness Variables Rackspace: ").append(rackspaceName));
    lib->consoleLog("+------------------------------------------------------------------");
    for (auto i = begin(dict); i != end(dict); i++)
    {
        string name = i->first;
        auto gv = i->second.get();
        string varLine;
        varLine.assign("|  Variable: ");
        switch (gv->getType())
        {
        case valueTypes::typeString:
            varLine.append(name).append(": ").append(gv->getStringValue());
            break;
        case valueTypes::typeDouble:
            varLine.append(name).append(": ").append(to_string(gv->getDoubleValue()));
            break;
        case valueTypes::typeInt:
            varLine.append(name).append(": ").append(to_string(gv->getIntValue()));
            break;
        case valueTypes::typeBoolean:
            varLine.append(name).append(": ").append(to_string(gv->getBoolValue()));
            break;
        }
        lib->consoleLog(varLine);
    }
    lib->consoleLog("+------------------------------------------------------------------");
}

GlobalVarsMap::~GlobalVarsMap()
{
    RemoveAll();
}
