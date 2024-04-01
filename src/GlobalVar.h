#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

/// <summary>
/// Single value types that can be created.
/// TypeNone means invalid
/// </summary>
enum valueTypes
{
    typeNone = 0,
    typeString = 1,
    typeInt = 2,
    typeDouble = 3,
    typeBoolean = 4,
};


/// <summary>
/// This struct is an in-between element to make it possible to have one list of
/// global variables, but with different types. This makes it easier, to lookup
/// and to see whether a variable already exists
/// </summary>
struct GlobalVar
{
  private:
#pragma region Declarations
    int valueType;
    int length = -1;

     // Single value placeholders
    std::unique_ptr<string> s;
    int i = 0;
    double d = 0;
    bool b = false;
#pragma endregion

  public:
#pragma region Assignments
    /// <summary>
    /// Assign a value to a string
    /// </summary>
    /// <param name="newVal">String value to assign</param>
    /// <returns>True on success, False when the variable is not a single string value</returns>
    bool assignString(string newVal);

    /// <summary>
    /// Assign a value to an integer
    /// </summary>
    /// <param name="newVal">Integer value to assign</param>
    /// <returns>True on success, False when the variable is not a single integer value</returns>
    bool assignInt(int newVal);

    /// <summary>
    /// Assign a value to a double
    /// </summary>
    /// <param name="newVal">Double value to assign</param>
    /// <returns>True on success, False when the variable is not a single double value</returns>
    bool assignDouble(double newVal);

    /// <summary>
    /// Assign a value to a boolean
    /// </summary>
    /// <param name="newVal">Boolean value to assign</param>
    /// <returns>True on success, False when the variable is not a single booelan value</returns>
    bool assignBool(bool newVal);

    /// <summary>
    /// Assign a value to a string array
    /// </summary>
    /// <param name="index">Index in the array</param>
    /// <param name="newVal">String value to assign</param>
    /// <returns>True on success, False when the variable is not an array string value, or the index is out of bounds</returns>
    bool assignString(int index, string newVal);


#pragma endregion

#pragma region Getters
    /// <summary>
    /// Get the string value
    /// </summary>
    /// <returns>The assigned string</returns>
    string getStringValue();

    /// <summary>
    /// Get the integer value
    /// </summary>
    /// <returns>The assigned integer</returns>
    int getIntValue();

    /// <summary>
    /// Get the double value
    /// </summary>
    /// <returns>The assigned double</returns>
    double getDoubleValue();

    /// <summary>
    /// Get the boolean value
    /// </summary>
    /// <returns>The assigned boolean</returns>
    bool getBoolValue();

    /// <summary>
    /// Get the type of a particular variable
    /// </summary>
    /// <returns>1 - String, 2 - Integer, 3 - Double. Arrays have 16 added</returns>
    int getType();

#pragma endregion

#pragma region Constructor / Destructor

    /// <summary>
    /// Construct a single ValueItem
    /// </summary>
    /// <param name="type">String, Int or Double</param>
    GlobalVar(valueTypes type);

    ~GlobalVar();
#pragma endregion
};
