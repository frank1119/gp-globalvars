#include "GlobalVar.h"

#pragma region Assignations
bool GlobalVar::assignString(string newVal)
{
    if (valueType == valueTypes::typeString)
    {
        if (s != nullptr)
            delete s;
        s = new string(newVal);
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

bool GlobalVar::assignString(int index, string newVal)
{
    if (sa != nullptr && index >= 0 && index < length)
    {
        if ((sa[index]) != nullptr)
        {
            delete (sa)[index];
        }
        (sa)[index] = new string(newVal);

        return true;
    }
    return false;
}

bool GlobalVar::assignDouble(int index, double newVal)
{
    if (da != nullptr && index >= 0 && index < length)
    {
        da[index] = newVal;
        return true;
    }
    return false;
}

bool GlobalVar::assignInt(int index, int newVal)
{
    if (ia != nullptr && index >= 0 && index < length)
    {
        ia[index] = newVal;
        return true;
    }
    return false;
}

bool GlobalVar::assignBool(int index, bool newVal)
{
    if (ba != nullptr && index >= 0 && index < length)
    {
        ba[index] = newVal;
        return true;
    }
    return false;
}

#pragma endregion

#pragma region Getters
string GlobalVar::getStringValue()
{
    return (valueType == valueTypes::typeString && s != nullptr) ? *s : "";
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

string GlobalVar::getStringValue(int index)
{
    if (sa != nullptr)
    {
        if (index >= 0 && index < length)
        {
            if ((sa)[index] != nullptr)
                return string(*(sa)[index]);
        }
    }
    return "";
}

int GlobalVar::getIntValue(int index)
{
    if (ia != nullptr)
    {
        if (index >= 0 && index < length)
        {
            return ia[index];
        }
    }
    return 0;
}

double GlobalVar::getDoubleValue(int index)
{
    if (da != nullptr)
    {
        if (index >= 0 && index < length)
        {
            return da[index];
        }
    }
    return 0;
}

bool GlobalVar::getBoolValue(int index)
{
    if (ba != nullptr)
    {
        if (index >= 0 && index < length)
        {
            return ba[index];
        }
    }
    return 0;
}

int GlobalVar::getType()
{
    return valueType;
}

int GlobalVar::getSize()
{
    return length;
}
#pragma endregion

#pragma region Constructor / Destructor

/// <summary>
/// Construct a single ValueItem
/// </summary>
/// <param name="type">String, Int or Double</param>
GlobalVar::GlobalVar(valueTypes type)
{
    valueType = type;
}

/// <summary>
/// Construct an array - ValueItem
/// </summary>
/// <param name="type">String, Int or Double</param>
/// <param name="size">Number of elements</param>
GlobalVar::GlobalVar(arrayTypes type, int size)
{
    valueType = type;
    switch (valueType)
    {
    case arrayTypes::arrayString:
        sa = new string *[size];
        for (int i = 0; i < size; i++)
            sa[i] = nullptr;
        length = size;
        break;

    case arrayTypes::arrayInt:
        ia = new int[size];
        length = size;
        break;

    case arrayTypes::arrayDouble:
        da = new double[size];
        length = size;
        break;

    case arrayTypes::arrayBoolean:
        ba = new bool[size];
        length = size;
        break;
    }
}

GlobalVar::~GlobalVar()
{
    switch (valueType)
    {
    case arrayTypes::arrayString:
        if (sa != nullptr)
        {
            for (int i = 0; i < length; i++)
            {
                if ((sa)[i] != nullptr)
                    delete (sa)[i];
            }
            delete[] * sa;
            sa = nullptr;
        }
        break;

    case arrayTypes::arrayInt:
        if (ia != nullptr)
        {
            delete[] ia;
            ia = nullptr;
        }
        break;

    case arrayTypes::arrayDouble:
        if (da != nullptr)
        {
            delete[] da;
            da = nullptr;
        }
        break;

    case arrayTypes::arrayBoolean:
        if (ba != nullptr)
        {
            delete[] ba;
            ba = nullptr;
        }
        break;

    case valueTypes::typeString:
        if (s != nullptr)
        {
            delete s;
            s = nullptr;
        }
        break;
    }
}
#pragma endregion
