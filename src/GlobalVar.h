#pragma once


#include <iostream>
#include <unordered_map>
#include <string>

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
/// Array types that can be created
/// ArrayNone means invalid
/// </summary>
enum arrayTypes
{
	arrayNone = 0,
	arrayString = 16,
	arrayInt = 17,
	arrayDouble = 18,
	arrayBoolean = 19,
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

	// Array placeholders
	string** sa = nullptr;
	int* ia = nullptr;
	double* da = nullptr;
    bool* ba = nullptr;

	// Single value placeholders
	string* s = nullptr;
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

	/// <summary>
    /// Assign a value to a double array
    /// </summary>
    /// <param name="index">Index in the array</param>
    /// <param name="newVal">Double value to assign</param>
    /// <returns>True on success, False when the variable is not an array double value, or the index is out of
    /// bounds</returns>
    bool assignDouble(int index, double newVal);

	/// <summary>
    /// Assign a value to an integer array
    /// </summary>
    /// <param name="index">Index in the array</param>
    /// <param name="newVal">Integer value to assign</param>
    /// <returns>True on success, False when the variable is not an array integer value, or the index is out of
    /// bounds</returns>
    bool assignInt(int index, int newVal);

	/// <summary>
    /// Assign a value to a boolean array
    /// </summary>
    /// <param name="index">Index in the array</param>
    /// <param name="newVal">Boolean value to assign</param>
    /// <returns>True on success, False when the variable is not an array boolean value, or the index is out of
    /// bounds</returns>
    bool assignBool(int index, bool newVal);

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
    /// Get the a string value from the array
    /// </summary>
    /// <param name="index">Index of the value</param>
    /// <returns>The assigned string</returns>
    string getStringValue(int index);

	/// <summary>
    /// Get the a integer value from the array
    /// </summary>
    /// <param name="index">Index of the value</param>
    /// <returns>The assigned integer</returns>
    int getIntValue(int index);

	/// <summary>
    /// Get the a double value from the array
    /// </summary>
    /// <param name="index">Index of the value</param>
    /// <returns>The assigned double</returns>
    double getDoubleValue(int index);

    /// <summary>
    /// Get the a boolean value from the array
    /// </summary>
    /// <param name="index">Index of the value</param>
    /// <returns>The assigned boolean</returns>
    bool getBoolValue(int index);


	/// <summary>
    /// Get the type of a particular variable
    /// </summary>
    /// <returns>1 - String, 2 - Integer, 3 - Double. Arrays have 16 added</returns>
    int getType();

	/// <summary>
    /// Get the size of an array
    /// </summary>
    /// <returns>The size or -1 when the instance does not represent an array</returns>
    int getSize();
#pragma endregion

#pragma region Constructor/Destructor

	/// <summary>
	/// Construct a single ValueItem 
	/// </summary>
	/// <param name="type">String, Int or Double</param>
	GlobalVar(valueTypes type);

	/// <summary>
	/// Construct an array - ValueItem 
	/// </summary>
	/// <param name="type">String, Int or Double</param>
	/// <param name="size">Number of elements</param>
	GlobalVar(arrayTypes type, int size);

	~GlobalVar();
#pragma endregion

};
