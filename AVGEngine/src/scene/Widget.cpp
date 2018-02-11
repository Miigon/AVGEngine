#include "Widget.h"

void Widget::init(const Config& config)
{
	for (const auto& conf : config.getConfigsConst())
	{
		if (hasField(conf.first))
		{
			switch (getType(conf.first))
			{
			case FieldString:
				setField(conf.first, conf.second);
				break;
			case FieldInt:
				try
				{
					setField(conf.first, static_cast<int>(Config::getExpressionResult(conf.second)));
				}
				catch (std::exception& e)
				{
					throw(std::runtime_error(std::string("Excepted Int but get ") + conf.second + "." + e.what()));
				}
				break;
			case FieldBool:
			{
				auto str = conf.second;
				for (auto& c : str)
				{
					if (c > 96 && c < 123)
						c -= 32;
				}
				setField(conf.first, str == "TRUE");
				break;
			}
			case FieldDouble:
				try
				{
					setField(conf.first, Config::getExpressionResult(conf.second));
				}
				catch(std::exception& e)
				{
					throw(std::runtime_error(std::string("Excepted Double but get ") + conf.second + "." + e.what()));
				}
				break;
			default:
				break;
			}
		}
		else
			throw(std::runtime_error(std::string("Opition doesn't exist:") + conf.first));
	}
}

Widget::Widget()
{
	addField("pos.x", FieldDouble);
	addField("pos.y", FieldDouble);

	addField("size.height", FieldDouble);
	addField("size.width", FieldDouble);

	addField("background.r", FieldDouble);
	addField("background.g", FieldDouble);
	addField("background.b", FieldDouble);
	addField("background.a", FieldDouble);
}
