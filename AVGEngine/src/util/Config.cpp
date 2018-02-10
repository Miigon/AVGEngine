#include "Config.h"
#include <fstream>
#include <sstream>
#include <list>

ConfigPtr Config::getAsConfig(const std::string& key) const
{
	std::stringstream stream(get(key));

	return loadConfig(stream);
}

std::string Config::readValue(std::stringstream& stream)
{
	//读取值
	std::string value;

	auto braceCount = 0;
	while (true)
	{
		char buffer;

		stream.read(&buffer, 1);

		//判断是否读完变量的值
		if ((!braceCount && buffer == '\n' && !value.empty()) || stream.eof())
			break;

		//跳过开始的空行和空格
		if ((buffer == ' ' || buffer == '\n') && value.empty())
			continue;

		//由引号括起来时单独处理
		if (value.empty() && buffer == '\"')
		{
			//直接读到结尾并跳出读取变量值的循环
			while (true)
			{
				stream.read(&buffer, 1);

				if (stream.eof())
					break;

				//是否读取到引号
				if (buffer == '\"')
				{
					//不包含转义符
					if ((value.empty() || value.back() != '\\'))
						break;

					//就是转义符
					value.pop_back();
				}
				value += buffer;
			}
			//跳出读值循环
			break;
		}

		//数据为空（第一个字符为大括号）或者使用大括号时处理有关大括号的东西
		if (value.empty() || braceCount != 0)
		{
			if (buffer == '{')
			{
				//丢掉第一个大括号
				if (++braceCount == 1)
					continue;
			}
			if (buffer == '}')
				//是否没有大括号了
				if (--braceCount == 0)
					break;
		}

		//丢弃非法字符（\r为windows下换行符）
		if (buffer != '\t' && buffer != '\r' && (braceCount || buffer != '\n'))
			value += buffer;
	}

	return value;
}

ConfigPtr Config::loadConfig(std::stringstream& configStr)
{
	ConfigPtr config(new Config());
	std::string valueName;

	while (true)
	{
		char buffer;
		configStr.read(&buffer, 1);

		if (configStr.eof())
			break;

		//抛弃大括号
		if ((buffer == '{' || buffer == '}') && valueName.empty())
			continue;

		//抛弃注释行
		if (buffer == '#')
		{
			if (!valueName.empty())
				throw(std::invalid_argument(std::string("Wrong note at ") + std::to_string(configStr.tellg())));

			while(buffer != '\n' && !configStr.eof())
				configStr.read(&buffer, 1);

			continue;
		}
		
		//警告字符
		if (buffer == ' ' || buffer == '\t' || buffer == '\r' || buffer == '\n')
			continue;

		//变量名和值的分割符
		if (buffer == '=')
		{
			if (valueName.empty())
				throw(std::invalid_argument(std::string("Failed to read file at ") + std::to_string(configStr.tellg())));

			//add to map
			config->mValueMap[valueName] = readValue(configStr);
			valueName = "";

			continue;
		}

		//非法字符(a-z A-Z 0-9 [ ] .)
		if (!((buffer < 123 && buffer > 96) || //a-z
			(buffer < 91 && buffer > 64) || //A-Z
			(buffer < 58 && buffer > 47) || //0-9
			(buffer == '[' || buffer == ']') || //[ and ]
			(buffer == '.')				   //.
			))
			throw(std::invalid_argument(std::string("Wrong data at ") + std::to_string(configStr.tellg())));

		//更改变量名
		valueName += buffer;
	}

	return config;
}

ConfigPtr Config::loadConfig(const char* fileName, const int offset)
{
	auto file = std::ifstream(fileName, std::ios::binary);
	std::stringstream stream;
	stream << file.rdbuf();
	return loadConfig(stream);
}

double Config::getExpressionResult(const std::string& expressionStr)
{
	enum ExpressionOperator
	{
		Number, Plus, Minus, Multiply, Divided
	};

	auto bracketCount = 0;
	std::string subExpression;
	std::string readNumber;
	std::list<std::pair<ExpressionOperator, double>> expression;

	//解析整个表达式
	for (auto& c : expressionStr)
	{
		if (bracketCount > 0)
			subExpression += c;

		switch (c)
		{
		case '(':
			bracketCount++;
			break;
		case ')':
			if (--bracketCount == 0)
			{
				readNumber = std::to_string(getExpressionResult(subExpression.substr(0, subExpression.length() - 1)));
				subExpression = "";
			}
			break;
		case '+':
		case '-':
		case '*':
		case '/':
			//是否是子表达式中的内容
			if (bracketCount)
				break;
			
			//是读到了数字
			if (readNumber.empty())
				throw (std::invalid_argument(std::string("can't find the number before thr operator: ") + c));

			//加入表达式
			expression.emplace_back(std::make_pair(Number, std::stod(readNumber)));
			readNumber = "";
			switch (c)
			{
			case '+':
				expression.emplace_back(std::make_pair(Plus, 0.0));
				break;
			case '-':
				expression.emplace_back(std::make_pair(Minus, 0.0));
				break;
			case '*':
				expression.emplace_back(std::make_pair(Multiply, 0.0));
				break;
			case '/':
				expression.emplace_back(std::make_pair(Divided, 0.0));
				break;
			default:
				break;
			}
			break;
		default:
			readNumber += c;
		}
	}

	//最后一个数字（因为后边没有运算符所以单独处理
	if (readNumber.empty())
		throw (std::invalid_argument(std::string("can't find the last number")));

	expression.emplace_back(std::make_pair(Number, std::stod(readNumber)));

	//计算乘法和除法
	for (auto item = expression.begin(); ;)
	{
		const auto number1 = item;
		const auto expressOperator = ++item;

		//是不是最后一个数字（最后一个数字后边无运算符)
		if (expressOperator == expression.end())
			break;
		const auto number2 = ++item;

		if (expressOperator->first == Multiply)
			number1->second *= number2->second;
		else if (expressOperator->first == Divided)
			number1->second /= number2->second;
		else
			continue;

		//定位到number 1
		item = number1;
		expression.erase(expressOperator);
		expression.erase(number2);
	}

	//计算加法和减法
	for (auto item = expression.begin(); ;)
	{
		const auto number1 = item;
		const auto expressOperator = ++item;

		//是不是最后一个数字（最后一个数字后边无运算符)
		if (expressOperator == expression.end())
			break;
		const auto number2 = ++item;

		if (expressOperator->first == Plus)
			number1->second += number2->second;
		else if (expressOperator->first == Minus)
			number1->second -= number2->second;
		else
			continue;

		//定位到number 1
		item = number1;
		expression.erase(expressOperator);
		expression.erase(number2);
	}

	if (expression.size() != 1)
		throw (std::runtime_error("failed to read expression :" + expressionStr));

	return expression.begin()->second;
}

double Config::getAsExpression(const std::string& key) const
{
	return getExpressionResult(get(key));
}