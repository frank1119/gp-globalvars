#pragma once
#include <unordered_map>
#include "GlobalVar.h"
using namespace std;

/// <summary>
/// API for creating of, assigning to, gettting value of, destruct global variables
/// This might be a single value or an array.
/// All calls need at least string containing the variable-name
///
/// Supported single value types:
///		String, Integer, Double
/// Supported array types: 
///		String, Integer, Double
/// </summary>
class GlobalVarsMap
{
private:
	/// <summary>
	/// The map holding all varaiables
	/// </summary>
	unordered_map<string, GlobalVar*> dict;

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
	/// Create a variable array, type string
	/// </summary>
	/// <param name="name">Name</param>
	/// <param name="length">Number of elements</param>
	/// <returns>True on success, False when the variable name already exists</returns>
	bool CreateString(const string name, int length);

	/// <summary>
	/// Create a variable array, type integer
	/// </summary>
	/// <param name="name">Name</param>
	/// <param name="length">Number of elements</param>
	/// <returns>True on success, False when the variable name already exists</returns>
	bool CreateInt(const string name, int length);

	/// <summary>
	/// Create a variable array, type double
	/// </summary>
	/// <param name="name">Name</param>
	/// <param name="length">Number of elements</param>
	/// <returns>True on success, False when the variable name already exists</returns>
	bool CreateDouble(const string name, int length);

	/// <summary>
    /// Create a variable array, type boolean
    /// </summary>
    /// <param name="name">Name</param>
    /// <param name="length">Number of elements</param>
    /// <returns>True on success, False when the variable name already exists</returns>
    bool CreateBool(const string name, int length);

	/// <summary>
	/// Checks whether a give variable already exists
	/// </summary>
	/// <param name="name">Name</param>
	/// <returns>The variable type. 0 -> No such variabele</returns>
	int GetVariableType(const string name);

	/// <summary>
	/// Returns the size of an array
	/// </summary>
	/// <param name="name">Name</param>
	/// <returns>Number of elements. -1 -> No such variable or variable not an array</returns>
	int GetArraySize(const string name);

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
	/// Assign a value to a string variable array
	/// </summary>
	/// <param name="name">Name</param>
	/// <param name="index">Array index</param>
	/// <param name="value">Value</param>
	/// <returns>True on success, false when the variable does not exist, index is out of bounds or variable is of a different type</returns>
	bool SetString(const string name, int index, const string value);

	/// <summary>
	/// Assign a value to a integer variable array
	/// </summary>
	/// <param name="name">Name</param>
	/// <param name="index">Array index</param>
	/// <param name="value">Value</param>
	/// <returns>True on success, false when the variable does not exist, index is out of bounds or variable is of a different type</returns>
	bool SetInt(const string name, int index, int value);


	/// <summary>
	/// Assign a value to a double variable array
	/// </summary>
	/// <param name="name">Name</param>
	/// <param name="index">Array index</param>
	/// <param name="value">Value</param>
	/// <returns>True on success, false when the variable does not exist, index is out of bounds or variable is of a different type</returns>	
	bool SetDouble(const string name, int index, double value);

    /// <summary>
    /// Assign a value to a boolean variable array
    /// </summary>
    /// <param name="name">Name</param>
    /// <param name="index">Array index</param>
    /// <param name="value">Value</param>
    /// <returns>True on success, false when the variable does not exist, index is out of bounds or variable is of a
    /// different type</returns>
    bool SetBool(const string name, int index, bool value);

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
	/// Returns the value of a string array variable, or an empty string when it does not exist, index is out of bounds or variable is of a different type
	/// </summary>
	/// <param name="name">Name</param>
	/// <param name="index">Array index</param>
	/// <returns>Value of the variable or an empty string when the variable does not exist, index is out of bounds or variable is of a different type</returns>
	string GetStringValue(const string name, int index);

	/// <summary>
	/// Returns the value of a integer array variable, or 0 when it does not exist, index is out of bounds or variable is of a different type
	/// </summary>
	/// <param name="name">Name</param>
	/// <param name="index">Array index</param>
	/// <returns>Value of the variable or an 0 when the variable does not exist, index is out of bounds or variable is of a different type</returns>
	int GetIntValue(const string name, int index);

	/// <summary>
	/// Returns the value of a double array variable, or 0 when it does not exist, index is out of bounds or variable is of a different type
	/// </summary>
	/// <param name="name">Name</param>
	/// <param name="index">Array index</param>
	/// <returns>Value of the variable or an 0 when the variable does not exist, index is out of bounds or variable is of a different type</returns>
	double GetDoubleValue(const string name, int index);

	/// <summary>
    /// Returns the value of a boolean array variable, or 0 when it does not exist, index is out of bounds or variable is
    /// of a different type
    /// </summary>
    /// <param name="name">Name</param>
    /// <param name="index">Array index</param>
    /// <returns>Value of the variable or an 0 when the variable does not exist, index is out of bounds or variable is
    /// of a different type</returns>
    bool GetBoolValue(const string name, int index);

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

	~GlobalVarsMap();

};

