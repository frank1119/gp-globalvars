#include "GlobalVar.h"

#pragma region Assignations
bool GlobalVar::assignString(string newVal)
{
    if (valueType == valueTypes::typeString)
    {
        s.reset (new string(newVal));
        return true;
    }
    return false;
}

bool GlobalVar::assignInt(int newVal)
{
    if (valueType == valueTypes::typeInt)
    {
        i = newVal;
        return true; 
    } 
    return false;
}

bool GlobalVar::assignDouble(double newVal)
{
    if (valueType == valueTypes::typeDouble)
    {
        d = newVal;
        return true;
    }
    return false;
}  

bool GlobalVar::assignBool(bool newVal)
{
    if (valueType == valueTypes::typeBoolean)
    {
        b = newVal;
        return true;
    }
    return false;
}


#pragma endregion

#pragma region Getters
string GlobalVar::getStringValue()
{
    return (valueType == valueTypes::typeString && s.get()) ? *s : "";
}

int GlobalVar::getIntValue()
{
    return (valueType == valueTypes::typeInt) ? i : 0;
}

double GlobalVar::getDoubleValue()
{
    return (valueType == valueTypes::typeDouble) ? d : 0;
}

bool GlobalVar::getBoolValue()
{
    return (valueType == valueTypes::typeBoolean) ? b : false;
}

int GlobalVar::getType()
{
    return valueType;
}

#pragma endregion

#pragma region Constructor / Destructor

/// <summary>
/// Construct a single ValueItem
/// </summary>
/// <param name="type">String, Int, Double or Boolean</param>
GlobalVar::GlobalVar(valueTypes type)
{
    valueType = type;
}


GlobalVar::~GlobalVar()
{
    switch (valueType)
    {
    case valueTypes::typeString:
        break;
    }
}
#pragma endregion
