#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AVGEngine/src/scene/Scene.h"
#include "../AVGEngine/src/util/Resource.h"
#include "../AVGEngine/src/scene/Label.h"
#include "../AVGEngine/src/scene/CustomWidget.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace avg_engine_tests
{
	class TestScene1 : protected Scene
	{
	public:
		TestScene1()
		{
			Scene::init(*Resource::getConfig("res.scene.TestScene1.cnf"));
		}

		void checkWidgetContainer()
		{
			for (const auto& w : widgets)
			{
				if (w->name == "label1")
				{
					Label& label = *reinterpret_cast<Label*>(w.get());
					if (label.caption != "Test Data [] {} =")
						Assert::Fail(L"Failed to load label1");
				}
				else if (w->name == "dialog1")
				{
					CustomWidget& customWidget = *reinterpret_cast<CustomWidget*>(w.get());

					for (const auto& w2 : customWidget.widgets)
					{
						Label& label = *reinterpret_cast<Label*>(w2.get());
						if (!(
							(label.caption != "Test!" && label.name != "label1") ||
							(label.caption != "Value 2" && label.name != "label2")
							))
							Assert::Fail(L"Failed to load label in dialog1");
					}
				}
			}
		}
	};
	class TestScene2 : protected Scene
	{
	public:
		TestScene2()
		{
			Scene::init(*Resource::getConfig("res.scene.TestScene2.cnf"));
		}

		void checkWidgetContainer()
		{
			for (const auto& w : widgets)
			{
				if (w->name == "label1")
				{
					Label& label = *reinterpret_cast<Label*>(w.get());
					if (label.caption != "Test Data [] {} =")
						Assert::Fail(L"Failed to load label1");
				}
				else if (w->name == "dialog1")
				{
					CustomWidget& customWidget = *reinterpret_cast<CustomWidget*>(w.get());

					Label& label1 = *reinterpret_cast<Label*>(widgets[0].get());
					CustomWidget& dialogDialog1 = *reinterpret_cast<CustomWidget*>(customWidget.widgets[1].get());

					Label& dialogDialog1Label1 = *reinterpret_cast<Label*>(dialogDialog1.widgets[0].get());
					Label& dialogDialog1Label2 = *reinterpret_cast<Label*>(dialogDialog1.widgets[1].get());

					if (!(
						(label1.caption == "Test Data [] {} =" && label1.name == "label1") &&
						(dialogDialog1Label1.caption == "Test!" && dialogDialog1Label1.name == "label1") &&
						(dialogDialog1Label2.caption == "Value 2" && dialogDialog1Label2.name == "label2")
						))
						Assert::Fail(L"Failed to check widget");
				}
			}
		}
	};

	TEST_CLASS(SceneTest)
	{
	public:
		
		TEST_METHOD(custonWidgetLoadTest)
		{
			Resource::init();
			TestScene1 testScene;
			testScene.checkWidgetContainer();
		}

		TEST_METHOD(complexCustonWidgetLoadTest)
		{
			Resource::init();
			TestScene2 testScene;
			testScene.checkWidgetContainer();
		}
	};
}