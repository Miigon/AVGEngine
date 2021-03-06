#include <comdef.h> 
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AVGEngine/src/scene/Scene.h"
#include "../AVGEngine/src/util/Resource.h"
#include "../AVGEngine/src/scene/Label.h"
#include "../AVGEngine/src/scene/CustomWidget.h"

#define EPSINON 0.0001

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace avg_engine_tests
{
	class TestScene : protected Scene
	{
	public:
		TestScene()
		{
 			Scene::init(*Resource::getConfig("res.scene.TestScene.cnf"));
		}

		void checkWidgetContainer() const
		{
			const auto label1 = findWidget<CustomWidget>("label1");
			const auto label2 = findWidget<CustomWidget>("label2");
			const auto label3 = findWidget<CustomWidget>("label3");
			const auto label4 = findWidget<CustomWidget>("label4");
			const auto label5 = findWidget<CustomWidget>("label5");
			
			const auto c1 = label1->getString("caption");
			const auto c2 = label2->getString("caption");
			const auto c3 = label3->getString("caption");
			const auto c4 = label4->getString("caption");
			const auto c5 = label5->getString("caption");

			if (c1 != "Label 1" || label2->getDouble("pos.x") != 1.0f ||
				c2 != "Line 1\nLine 2" || c3 != "Line 1\nLine 2" ||
				c4 != "\"" || c5 != "\"Test\"")
				Assert::Fail(L"Failed to set label data");
		}
	};

	class TestScene1 : protected Scene
	{
	public:
		TestScene1()
		{
			Scene::init(*Resource::getConfig("res.scene.TestScene1.cnf"));
		}

		void checkWidgetContainer() const
		{
			const auto label1 = findWidget<CustomWidget>("label1");
			const auto label2 = findWidget<CustomWidget>("label2");

			if (label1->getString("caption") != "Test Data [] {} =" || label2->getString("caption") != "label 2")
				Assert::Fail(L"Failed to set label data");

			const auto dialog1 = findWidget<CustomWidget>("dialog1");

			const auto dialogLabel1 = dialog1->findWidget<Label>("dialogLabel1");
			const auto dialogLabel2 = dialog1->findWidget<Label>("dialogLabel2");

			if (dialogLabel1->getString("caption") != "Label 1" || dialogLabel2->getString("caption") != "Label 2")
				Assert::Fail(L"Failed to set dialog data");
		}
	};
	class TestScene2 : protected Scene
	{
	public:
		TestScene2()
		{
			Scene::init(*Resource::getConfig("res.scene.TestScene2.cnf"));
		}

		void checkWidgetContainer() const
		{
			const auto label1 = findWidget<Label>("label1");
			const auto dialog1 = findWidget<CustomWidget>("dialog1");

			if (label1->getString("caption") != "Label 1")
				Assert::Fail(L"Failed to set label data");

			if (dialog1->findWidget<CustomWidget>("dialog1")->findWidget<Label>("dialogLabel1")->getString("caption") != "Test!")
				Assert::Fail(L"Failed to set label data");

			if (dialog1->findWidget<CustomWidget>("dialog1")->findWidget<Label>("dialogLabel2")->getString("caption") != "Value 2")
				Assert::Fail(L"Failed to set label data");
		}
	};
	class TestScene3 : protected Scene
	{
	public:
		TestScene3()
		{
			Scene::init(*Resource::getConfig("res.scene.TestScene3.cnf"));
		}

		void checkWidgetContainer() const
		{
			const auto dialog1 = findWidget<CustomWidget>("dialog1");
			const auto height = dialog1->findWidget<Label>("label1")->getDouble("size.height");

			if (height != (1.0 + 2.0 + 3.0 * (1.0 + 2.0 + 3.0 / 3.0 - 10.0) / 10.0 - 1.0))
				Assert::Fail(L"Failed to set label data");
		}
	};

	TEST_CLASS(SceneTest)
	{
	public:
		
		TEST_METHOD(sceneConfigReadTest)
		{
			Resource::init();
			TestScene testScene;
			testScene.checkWidgetContainer();
		}

		TEST_METHOD(sceneBasedTest)
		{
			Resource::init();
			TestScene1 testScene;
			testScene.checkWidgetContainer();
		}

		TEST_METHOD(complexCustomWidgetLoadTest)
		{
			Resource::init();
			TestScene2 testScene;
			testScene.checkWidgetContainer();
		}

		TEST_METHOD(expressionTest)
		{
			//��Scene�����
			std::vector<std::pair<std::string, double>> testData
			{
				std::make_pair("1 + 1", 1.0 + 1.0),
				std::make_pair("1 + 3 * 8", 1.0 + 3.0 * 8.0),
				std::make_pair("1 + 3 * 8 / 4", 1.0 + 3.0 * 8.0 / 4.0),
				std::make_pair("1 + 3 * 8 / 4 - 1", 1.0 + 3.0 * 8.0 / 4.0 - 1.0),
				std::make_pair("1 + 3 * 8 / (4 - 1)", 1.0 + 3.0 * 8.0 / (4.0 - 1.0)),
				std::make_pair("1 + 3 * (8 / (4 - 1.2))", 1.0 + 3.0 * (8.0 / (4.0 - 1.2))),
				std::make_pair("1 + 3 - 1 * (8 / (4 - 1))", 1.0 + 3.0 - 1.0 * (8.0 / (4.0 - 1.0))),
				std::make_pair("1 + (3 - 1) * (8 / (4 - 1))", 1.0 + (3.0 - 1.0) * (8.0 / (4.0 - 1.0))),
				std::make_pair("1+(3-1)*(8/(4-1))", 1.0 + (3.0 - 1.0 )* (8.0 / (4.0 - 1.0))),
				std::make_pair("1  +(3  -  1  )  *  ( 8/  ( 4-1 )    )", 1.0 + (3.0 - 1.0) * (8.0 / (4.0 - 1.0))),
			};

			for (auto& data : testData)
			{
				const auto result = Config::getExpressionResult(data.first);
				if (abs(result - data.second) > EPSINON)
				{
					const _bstr_t t = data.first.c_str();
					const auto pwchar = static_cast<wchar_t*>(t);
					const std::wstring wStr = pwchar;
					Assert::Fail((std::wstring(L"Failed to calcuate ") + wStr).c_str());
				}
			}

			//��Scene�ڲ���
			Resource::init();
			TestScene3 testScene;
			testScene.checkWidgetContainer();
		}
	};
}