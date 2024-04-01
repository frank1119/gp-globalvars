#pragma once
#include "GlobalVar.h"
#include <unordered_map>
#include <regex>
#include "json.h"

class LibMain;

using json = nlohmann::json;

using namespace std;

/// <summary>
/// API for creating of, assigning to, gettting value of, destruct global variables
/// This might be a single value or an array.
/// All calls need at least string containing the variable-name
///
/// Supported single value types:
///        String, Integer, Double
/// Supported array types:
///        String, Integer, Double
/// </summary>
class GlobalVarsMap
{
  private:
    /// <summary>
    /// The map holding all variables
    /// </summary>
    unordered_map<string, std::unique_ptr<GlobalVar>> dict;
    //unordered_map<string, GlobalVar *> dict;

  public:
    /// <summary>
    /// Create a variable, type string
    /// </summary>
    /// <param name="name">Name</param>
    /// <returns>True on success, False when the variable name already exists</returns>
    bool CreateString(const string name);

    /// <summary>
    /// Create a variable, type integer
    /// </summary>
    /// <param name="name">Name</param>
    /// <returns>True on success, False when the variable name already exists</returns>
    bool CreateInt(const string name);

    /// <summary>
    /// Create a variable, type double
    /// </summary>
    /// <param name="name">Name</param>
    /// <returns>True on success, False when the variable name already exists</returns>
    bool CreateDouble(const string name);

    /// <summary>
    /// Create a variable, type boolean
    /// </summary>
    /// <param name="name">Name</param>
    /// <returns>True on success, False when the variable name already exists</returns>
    bool CreateBool(const string name);


    /// <summary>
    /// Checks whether a give variable already exists
    /// </summary>
    /// <param name="name">Name</param>
    /// <returns>The variable type. 0 -> No such variabele</returns>
    int GetVariableType(const string name);

    /// <summary>
    /// Assign a value to a string variable
    /// </summary>
    /// <param name="name">Name</param>
    /// <param name="value">Value</param>
    /// <returns>True on success, false when the variable does not exist or variable is of a different type</returns>
    bool SetString(const string name, const string value);

    /// <summary>
    /// Assign a value to a integer variable
    /// </summary>
    /// <param name="name">Name</param>
    /// <param name="value">Value</param>
    /// <returns>True on success, false when the variable does not exist or variable is of a different type</returns>
    bool SetInt(const string name, int value);

    /// <summary>
    /// Assign a value to a double variable
    /// </summary>
    /// <param name="name">Name</param>
    /// <param name="value">Value</param>
    /// <returns>True on success, false when the variable does not exist or variable is of a different type</returns>
    bool SetDouble(const string name, double value);

    /// <summary>
    /// Assign a value to a boolean variable
    /// </summary>
    /// <param name="name">Name</param>
    /// <param name="value">Value</param>
    /// <returns>True on success, false when the variable does not exist or variable is of a different type</returns>
    bool SetBool(const string name, bool value);

    /// <summary>
    /// Returns the value of a string variable, or an empty string when it does not exist or variable is of a different type
    /// </summary>
    /// <param name="name">Name</param>
    /// <returns>Value of the variable or an empty string if it does not exist or variable is of a different type</returns>
    string GetStringValue(const string name);

    /// <summary>
    /// Returns the value of an integer variable, or 0 when it does not exist or variable is of a different type
    /// </summary>
    /// <param name="name">Name</param>
    /// <returns>Value of the variable or 0 if it does not exist or is variable of a different type</returns>
    int GetIntValue(const string name);

    /// <summary>
    /// Returns the value of an double variable, or 0 when it does not exist or variable is of a different type
    /// </summary>
    /// <param name="name">Name</param>
    /// <returns>Value of the variable or 0 if it does not exist or is variable of a different type</returns>
    double GetDoubleValue(const string name);

    /// <summary>
    /// Returns the value of an boolean variable, or 0 when it does not exist or variable is of a different type
    /// </summary>
    /// <param name="name">Name</param>
    /// <returns>Value of the variable or 0 if it does not exist or is variable of a different type</returns>
    bool GetBoolValue(const string name);

    /// <summary>
    /// Remove a variable from the map
    /// </summary>
    /// <param name="name">Name of the variable to remove</param>
    /// <returns>True on success, False when the variable does not exist</returns>
    bool DestroyVariable(const string name);

    /// <summary>
    /// Remove all variables from the map.
    /// </summary>
    void RemoveAll();

    json getAllState();

    void ProcessRecord(json j);

    void setAllState(string jstate);

    void dumpAllState(LibMain *lib, string line);

    ~GlobalVarsMap();
};


