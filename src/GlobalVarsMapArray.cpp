#include "GlobalVarsMapArray.h"
#define reg regex("^[A-Za-z_][A-Za-z0-9_]{0,39}$")

// fake array notation: ^[A-Za-z_][A-Za-z0-9_]{0,39}([(][0-9]{1,3}[)]){0,1}$  -> Var(1) == OK


bool GlobalVarsMapArray::CreateString(const string handle, const string name)
{
    if (std::regex_match(name.c_str(), reg))
    {
        if (dicts.count(handle) == 0)
            AddRackspaceByUuid(handle);

        GlobalVarsMap *v = dicts[handle].get();
        return v->CreateString(name);
    }
    return false;
}

bool GlobalVarsMapArray::CreateInt(const string handle, const string name)
{
    if (std::regex_match(name.c_str(), reg))
    {
        if (dicts.count(handle) == 0)
            AddRackspaceByUuid(handle);

        GlobalVarsMap *v = dicts[handle].get();
        return v->CreateInt(name);
    }
    return false;
}

bool GlobalVarsMapArray::CreateDouble(const string handle, const string name)
{
    if (std::regex_match(name.c_str(), reg))
    {
        if (dicts.count(handle) == 0)
            AddRackspaceByUuid(handle);

        GlobalVarsMap *v = dicts[handle].get();
        return v->CreateDouble(name);
    }
    return false;
}

bool GlobalVarsMapArray::CreateBool(const string handle, const string name)
{
    if (std::regex_match(name.c_str(), reg))
    {
        if (dicts.count(handle) == 0)
            AddRackspaceByUuid(handle);

        GlobalVarsMap *v = dicts[handle].get();
        return v->CreateBool(name);
    }
    return false;
}

int GlobalVarsMapArray::GetVariableType(const string handle, const string name)
{
    if (std::regex_match(name.c_str(), reg))
    {
        if (dicts.count(handle) == 1)
        {
            GlobalVarsMap *v = dicts[handle].get();
            return v->GetVariableType(name);
        }
    }
    return 0;
}

bool GlobalVarsMapArray::SetString(const string handle, const string name, const string value)
{
    if (dicts.count(handle) == 1)
    {
        GlobalVarsMap *v = dicts[handle].get();
        return v->SetString(name, value);
    }

    return false;
}

bool GlobalVarsMapArray::SetInt(const string handle, const string name, int value)
{
    if (dicts.count(handle) == 1)
    {
        GlobalVarsMap *v = dicts[handle].get();
        return v->SetInt(name, value);
    }

    return false;
}

bool GlobalVarsMapArray::SetDouble(const string handle, const string name, double value)
{
    if (dicts.count(handle) == 1)
    {
        GlobalVarsMap *v = dicts[handle].get();
        return v->SetDouble(name, value);
    }

    return false;
}

bool GlobalVarsMapArray::SetBool(const string handle, const string name, bool value)
{
    if (dicts.count(handle) == 1)
    {
        GlobalVarsMap *v = dicts[handle].get();
        return v->SetBool(name, value);
    }

    return false;
}

string GlobalVarsMapArray::GetStringValue(const string handle, const string name)
{
    if (dicts.count(handle) == 1)
    {
        GlobalVarsMap *v = dicts[handle].get();
        return v->GetStringValue(name);
    }

    return "";
}

int GlobalVarsMapArray::GetIntValue(const string handle, const string name)
{
    if (dicts.count(handle) == 1)
    {
        GlobalVarsMap *v = dicts[handle].get();
        return v->GetIntValue(name);
    }

    return 0;
}

double GlobalVarsMapArray::GetDoubleValue(const string handle, const string name)
{
    if (dicts.count(handle) == 1)
    {
        GlobalVarsMap *v = dicts[handle].get();
        return v->GetDoubleValue(name);
    }
    return 0;
}

bool GlobalVarsMapArray::GetBoolValue(const string handle, const string name)
{
    if (dicts.count(handle) == 1)
    {
        GlobalVarsMap *v = dicts[handle].get();
        return v->GetBoolValue(name);
    }
    return 0;
}

bool GlobalVarsMapArray::DestroyVariable(const string handle, const string name)
{
    if (dicts.count(handle) == 1)
    {
        GlobalVarsMap *v = dicts[handle].get();
        return v->DestroyVariable(name);
    }
    return false;
}

void GlobalVarsMapArray::RemoveAll()
{
    //lck.lock();
    for (auto i = begin(dicts); i != end(dicts); i++)
    {
        i->second->RemoveAll();
    }
    //lck.unlock();
}

void GlobalVarsMapArray::RemoveAllOnLoad()
{
    //lck.lock();
    for (auto i = begin(dicts); i != end(dicts); i++)
    {
        try
        {
            i->second->RemoveAll();
        }
        catch (...)
        {
            cout << "Shit" << endl;
        }
    }
    dicts.clear();
    //lck.unlock();
}

void GlobalVarsMapArray::AddRackspaceByUuid(string handle)
{
    // lck.lock();
    if (dicts.count(handle) == 0)
    {
        dicts[handle].reset(new GlobalVarsMap());
    }
    // lck.unlock();
}

void GlobalVarsMapArray::RemoveAllPerRack(string rackspaceUuid)
{
    //lck.lock();
    for (auto i = begin(dicts); i != end(dicts); i++)
    {
        string uuid = i->first;

        if (uuid.compare(rackspaceUuid) == 0)
        {
            i->second->RemoveAll();
        }
    }
    //lck.unlock();
}

std::string GlobalVarsMapArray::getAllState(string rackspaceUuid)
{
    //lck.lock();
    for (auto i = begin(dicts); i != end(dicts); i++)
    {
        string uuid = i->first;

        if (uuid.compare(rackspaceUuid) == 0)
        {
            string s = i->second->getAllState().dump();
    //        lck.unlock();
            return s;
        }
    }
    //lck.unlock();
    return "";
}

void GlobalVarsMapArray::setAllState(string rackspaceUuid, string state)
{
    //lck.lock();
    AddRackspaceByUuid(rackspaceUuid);
    for (auto i = begin(dicts); i != end(dicts); i++)
    {
        string uuid = i->first;

        if (uuid.compare(rackspaceUuid) == 0)
            i->second->setAllState(state);
    }
    //lck.unlock();
}

void GlobalVarsMapArray::dumpAllState(string rackspaceUuid, LibMain *lib, string rackspaceName)
{
    //lck.lock();
    for (auto i = begin(dicts); i != end(dicts); i++)
    {
        string uuid = i->first;

        if (uuid.compare(rackspaceUuid) == 0)
            i->second->dumpAllState(lib, rackspaceName);
    }
    //lck.unlock();
}
