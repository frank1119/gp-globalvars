#pragma once
#include "GlobalVarsMap.h"
#include <mutex>
using namespace std;

class GlobalVarsMapArray
{
  private:
    /// <summary>
    /// The map holding all variables
    /// </summary>
    unordered_map<string, std::unique_ptr<GlobalVarsMap>> dicts;
    // std::recursive_mutex lck;

  public:
    /// <summary>
    /// Adds an GlobalVarsMap for a particular rackspace
    /// </summary>
    /// <param name="handle">RackspaceUuid</param>

    /// <summary>
    /// Create a variable, type string
    /// </summary>
    /// <param name="handle">RackspaceUuid</param>
    /// <param name="name">Name</param>
    /// <returns>True on success, False if the variable name already exists</returns>
    bool CreateString(const string handle, const string name);

    /// <summary>
    /// Create a variable, type integer
    /// </summary>
    /// <param name="handle">RackspaceUuid</param>
    /// <param name="name">Name</param>
    /// <returns>True on success, False if the variable name already exists</returns>
    bool CreateInt(const string handle, const string name);

    /// <summary>
    /// Create a variable, type double
    /// </summary>
    /// <param name="handle">RackspaceUuid</param>
    /// <param name="name">Name</param>
    /// <returns>True on success, False if the variable name already exists</returns>
    bool CreateDouble(const string handle, const string name);

    /// <summary>
    /// Create a variable, type boolean
    /// </summary>
    /// <param name="handle">RackspaceUuid</param>
    /// <param name="name">Name</param>
    /// <returns>True on success, False if the variable name already exists</returns>
    bool CreateBool(const string handle, const string name);

    /// <summary>
    /// Checks whether a give variable already exists
    /// </summary>
    /// <param name="handle">RackspaceUuid</param>
    /// <param name="name">Name</param>
    /// <returns>The variable type. 0 -> No such variabele</returns>
    int GetVariableType(const string handle, const string name);

    /// <summary>
    /// Assign a value to a string variable
    /// </summary>
    /// <param name="handle">RackspaceUuid</param>
    /// <param name="name">Name</param>
    /// <param name="value">Value</param>
    /// <returns>True on success, false if the variable does not exist or variable is of a different type</returns>
    bool SetString(const string handle, const string name, const string value);

    /// <summary>
    /// Assign a value to a integer variable
    /// </summary>
    /// <param name="handle">RackspaceUuid</param>
    /// <param name="name">Name</param>
    /// <param name="value">Value</param>
    /// <returns>True on success, false if the variable does not exist or variable is of a different type</returns>
    bool SetInt(const string handle, const string name, int value);

    /// <summary>
    /// Assign a value to a double variable
    /// </summary>
    /// <param name="handle">RackspaceUuid</param>
    /// <param name="name">Name</param>
    /// <param name="value">Value</param>
    /// <returns>True on success, false if the variable does not exist or variable is of a different type</returns>
    bool SetDouble(const string handle, const string name, double value);

    /// <summary>
    /// Assign a value to a boolean variable
    /// </summary>
    /// <param name="handle">RackspaceUuid</param>
    /// <param name="name">Name</param>
    /// <param name="value">Value</param>
    /// <returns>True on success, false if the variable does not exist or variable is of a different type</returns>
    bool SetBool(const string handle, const string name, bool value);

    /// <summary>
    /// Returns the value of a string variable, or an empty string if it does not exist or variable is of a different type
    /// </summary>
    /// <param name="handle">RackspaceUuid</param>
    /// <param name="name">Name</param>
    /// <returns>Value of the variable or an empty string if it does not exist or variable is of a different type</returns>
    string GetStringValue(const string handle, const string name);

    /// <summary>
    /// Returns the value of an integer variable, or 0 if it does not exist or variable is of a different type
    /// </summary>
    /// <param name="handle">RackspaceUuid</param>
    /// <param name="name">Name</param>
    /// <returns>Value of the variable or 0 if it does not exist or is variable of a different type</returns>
    int GetIntValue(const string handle, const string name);

    /// <summary>
    /// Returns the value of an double variable, or 0 if it does not exist or variable is of a different type
    /// </summary>
    /// <param name="handle">RackspaceUuid</param>
    /// <param name="name">Name</param>
    /// <returns>Value of the variable or 0 if it does not exist or is variable of a different type</returns>
    double GetDoubleValue(const string handle, const string name);

    /// <summary>
    /// Returns the value of an boolean variable, or 0 if it does not exist or variable is of a different type
    /// </summary>
    /// <param name="handle">RackspaceUuid</param>
    /// <param name="name">Name</param>
    /// <returns>Value of the variable or 0 if it does not exist or is variable of a different type</returns>
    bool GetBoolValue(const string handle, const string name);

    /// <summary>
    /// Remove a variable from the map
    /// </summary>
    /// <param name="handle">RackspaceUuid</param>
    /// <param name="name">Name of the variable to remove</param>
    /// <returns>True on success, False if the variable does not exist</returns>
    bool DestroyVariable(const string handle, const string name);

    /// <summary>
    /// Removes all variables from all maps
    /// </summary>
    void RemoveAll();

    void AddRackspaceByUuid(string handle);

    void RemoveAllOnLoad();

    /// <summary>
    /// Remove all variables from the map of a particular Rackspace.
    /// <param name="rackspaceUuid">Then RackspaceUuid</param>
    /// </summary>
    void RemoveAllPerRack(string rackspaceUuid);
    
    /// <summary>
    /// Exports the state of a particular Rackspace
    /// </summary>
    /// <param name="rackspaceUuid">The RackspaceUuid</param>
    /// <returns>A json string with the state of this Rackspace</returns>
    string getAllState(string rackspaceUuid);

    /// <summary>
    /// Imports the state of a particular Rackspace
    /// </summary>
    /// <param name="rackspaceUuid">The RackspaceUuid</param>
    /// <param name="state">The json string to import</param>
    void setAllState(string rackspaceUuid, string state);

    /// <summary>
    /// Dumps the contents a the GlobalVarsMap of a particular Rackspace
    /// </summary>
    /// <param name="rackspaceUuid">The RackspaceUuid</param>
    /// <param name="lib">Reference to the Libmain object</param>
    /// <param name="rackspaceName">The RackspaceName (only for formatting purposes)</param>
    void dumpAllState(string rackspaceUuid, LibMain *lib, string rackspaceName);
};
