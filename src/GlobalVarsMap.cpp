#include "GlobalVarsMap.h"

bool GlobalVarsMap::CreateString(const string name)
{
    if (dict.count(name) == 0)
    {
        GlobalVar *v = new GlobalVar(valueTypes::typeString);
        dict[name] = v;
        return true;
    }
    return false;
}

bool GlobalVarsMap::CreateInt(const string name)
{
    if (dict.count(name) == 0)
    {
        GlobalVar *v = new GlobalVar(valueTypes::typeInt);
        dict[name] = v;
        return true;
    }
    return false;
}

bool GlobalVarsMap::CreateDouble(const string name)
{
    if (dict.count(name) == 0)
    {
        GlobalVar *v = new GlobalVar(valueTypes::typeDouble);
        dict[name] = v;
        return true;
    }
    return false;
}

bool GlobalVarsMap::CreateBool(const string name)
{
    if (dict.count(name) == 0)
    {
        GlobalVar *v = new GlobalVar(valueTypes::typeBoolean);
        dict[name] = v;
        return true;
    }
    return false;
}

bool GlobalVarsMap::CreateString(const string name, int length)
{
    if (dict.count(name) == 0 && length > 0 && length < INT_MAX)
    {
        GlobalVar *v = new GlobalVar(arrayTypes::arrayString, length);
        dict[name] = v;
        return true;
    }
    return false;
}

bool GlobalVarsMap::CreateInt(const string name, int length)
{
    if (dict.count(name) == 0 && length > 0 && length < INT_MAX)
    {
        GlobalVar *v = new GlobalVar(arrayTypes::arrayInt, length);
        dict[name] = v;
        return true;
    }
    return false;
}

bool GlobalVarsMap::CreateDouble(const string name, int length)
{
    if (dict.count(name) == 0 && length > 0 && length < INT_MAX)
    {
        GlobalVar *v = new GlobalVar(arrayTypes::arrayDouble, length);
        dict[name] = v;
        return true;
    }
    return false;
}

bool GlobalVarsMap::CreateBool(const string name, int length)
{
    if (dict.count(name) == 0 && length > 0 && length < INT_MAX)
    {
        GlobalVar *v = new GlobalVar(arrayTypes::arrayBoolean, length);
        dict[name] = v;
        return true;
    }
    return false;
}

int GlobalVarsMap::GetVariableType(const string name)
{
    return (dict.count(name) == 1) ? dict[name]->getType() : 0;
}

int GlobalVarsMap::GetArraySize(const string name)
{
    if (dict.count(name) == 1)
        return dict[name]->getSize();
    return -1;
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

bool GlobalVarsMap::SetString(const string name, int index, const string value)
{
    if (dict.count(name) == 1)
        return dict[name]->assignString(index, value);
    return false;
}

bool GlobalVarsMap::SetInt(const string name, int index, int value)
{
    if (dict.count(name) == 1)
        return dict[name]->assignInt(index, value);
    return false;
}

bool GlobalVarsMap::SetDouble(const string name, int index, double value)
{
    if (dict.count(name) == 1)
        return dict[name]->assignDouble(index, value);
    return false;
}

bool GlobalVarsMap::SetBool(const string name, int index, bool value)
{
    if (dict.count(name) == 1)
        return dict[name]->assignBool(index, value);
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

string GlobalVarsMap::GetStringValue(const string name, int index)
{
    if (dict.count(name) == 1)
        return dict[name]->getStringValue(index);
    return "";
}

int GlobalVarsMap::GetIntValue(const string name, int index)
{
    if (dict.count(name) == 1)
        return dict[name]->getIntValue(index);
    return 0;
}

double GlobalVarsMap::GetDoubleValue(const string name, int index)
{
    if (dict.count(name) == 1)
        return dict[name]->getDoubleValue(index);
    return 0;
}

bool GlobalVarsMap::GetBoolValue(const string name, int index)
{
    if (dict.count(name) == 1)
        return dict[name]->getBoolValue(index);
    return 0;
}

bool GlobalVarsMap::DestroyVariable(const string name)
{
    if (dict.count(name) == 1)
    {
        GlobalVar *v = dict[name];
        dict.erase(name);
        delete v;
        return true;
    }
    return false;
}

void GlobalVarsMap::RemoveAll()
{
    for (auto i = begin(dict); i != end(dict); i++)
        delete i->second;
    dict.clear();
}

GlobalVarsMap::~GlobalVarsMap()
{
    RemoveAll();
}
