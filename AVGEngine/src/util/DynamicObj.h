#pragma once

#include <string>
#include <map>
#include <vector>

class DynamicObj
{
public:
	enum FieldType
	{
		FieldInt,FieldDouble,FieldBool,FieldString
	};

private:
	//储存所有field
	std::map<std::string, std::pair<FieldType, void*>> mFields;

	//检查field是否存在
	std::pair<FieldType, void*>& ckeckField(const std::string &name, const FieldType type)
	{
		auto result = mFields.find(name);
		if (result == mFields.end())
			throw(std::invalid_argument(std::string("Field ") + name + " isn't existed"));

		if (result->second.first != type)
			throw(std::invalid_argument(
				std::string("Field ") + name + " type is " + std::to_string(result->second.first) + " but get " + 
				std::to_string(type)));
		return result->second;
	}

	//const版的check
	const std::pair<FieldType, void*>& ckeckFieldConst(const std::string &name, const FieldType type) const
	{
		const auto result = mFields.find(name);
		if (result == mFields.end())
			throw(std::invalid_argument(std::string("Field ") + name + " isn't existed"));

		if (result->second.first != type)
			throw(std::invalid_argument(
				std::string("Field ") + name + " type is " + std::to_string(result->second.first) + " but get " +
				std::to_string(type)));
		return result->second;
	}

public:
	/*!获取所有field
	 * @note 请不要轻易使用此方法
	 */
	std::map<std::string, std::pair<FieldType, void*>>& getFields() { return mFields; }

	void addField(const std::string& name, FieldType type, void* data = nullptr)
	{
		if (mFields.find(name) != mFields.end())
			throw(std::invalid_argument(std::string("Field ") + name + " is existed"));

		void* dataPtr;

		switch (type)
		{
		case FieldInt:
			if (data)
				dataPtr = new int(*reinterpret_cast<int*>(data));
			else
				dataPtr = new int(0);
			break;
		case FieldBool:
			if (data)
				dataPtr = new bool(*reinterpret_cast<bool*>(data));
			else
				dataPtr = new bool(false);
			break;
		case FieldDouble:
			if (data)
				dataPtr = new double(*reinterpret_cast<double*>(data));
			else
				dataPtr = new double(0);
			break;
		case FieldString:
			if (data)
				dataPtr = new std::string(*reinterpret_cast<std::string*>(data));
			else
				dataPtr = new std::string("");
			break;
		default:
			break;
		}
		mFields[name] = std::make_pair(type, dataPtr);
	}
	
	int getInt(const std::string& name) const
	{
		const auto& field = ckeckFieldConst(name, FieldInt);
		return *reinterpret_cast<int*>(field.second);
	}

	double getDouble(const std::string& name) const
	{
		const auto& field = ckeckFieldConst(name, FieldDouble);
		return *reinterpret_cast<double*>(field.second);
	}

	bool getBool(const std::string& name) const
	{
		const auto& field = ckeckFieldConst(name, FieldBool);
		return *reinterpret_cast<bool*>(field.second);
	}

	std::string getString(const std::string& name) const
	{
		const auto& field = ckeckFieldConst(name, FieldString);
		return *reinterpret_cast<std::string*>(field.second);
	}

	void setField(const std::string& name, const int value)
	{
		auto& field = ckeckField(name, FieldInt);
		delete reinterpret_cast<int*>(field.second);
		field.second = new int(value);
	}

	void setField(const std::string& name, const double value)
	{
		auto& field = ckeckField(name, FieldDouble);
		delete reinterpret_cast<double*>(field.second);
		field.second = new double(value);
	}

	void setField(const std::string& name, const bool value)
	{
		auto& field = ckeckField(name, FieldBool);
		delete reinterpret_cast<bool*>(field.second);
		field.second = new bool(value);
	}

	void setField(const std::string& name, const std::string& value)
	{
		auto& field = ckeckField(name, FieldString);
		delete reinterpret_cast<std::string*>(field.second);
		field.second = new std::string(value);
	}
};
