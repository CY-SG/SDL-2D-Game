#pragma once
#include"Component.h"
enum Tag {
	DefaultTag,
	PlayerTag,
	EnemyTag,
	WallTag,
	SensorTag
};
class TagComponent :public Component {
public:
	void Update()override;
	std::unique_ptr<Component>Clone(Entity* entity)override;
	TagComponent(Entity*entity,Tag tag=Tag::DefaultTag);
	Tag tag;
private:
};