#pragma once

#include <memory>
#include "WidgetContainer.h"
#include "../util/Config.h"

class Scene :public WidgetContainer
{
public:
	Scene(const Scene&) = delete;
	Scene(const Scene&&) = delete;
	Scene& operator=(const Scene&&) = delete;
	Scene& operator=(const Scene&) = delete;

	void draw() override;

	Scene() = default;
	virtual ~Scene() = default;

	//��config��ʼ��Scene
	void init(const Config& sceneConfig) override;
};

using ScenePtr = std::shared_ptr<Scene>;