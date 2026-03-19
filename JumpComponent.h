#pragma once
#include"Component.h"
#include<vector>
struct JumpState {
	float Yspeed;//跳跃高度
	float maxHoldTime;//最大蓄力时间
	bool needHold;
};
class JumpComponent :public Component {
public:
	JumpComponent(Entity* entity, int jumpCount,std::vector<JumpState>&jumpState);
	JumpComponent(Entity* entity);
	void Update()override;
	std::unique_ptr<Component>Clone(Entity* entity)override;
	std::vector<JumpState>jumpStates;
	int jumpCount;//跳跃次数
};