# 一个基于 C++ 与 SDL 实现的 2D 动作游戏框架，用于探索游戏客户端常见系统设计，包括角色控制、AI 行为以及场景动态加载等功能。

---

# 框架架构

游戏框架整体结构参考 **UE 的 World-Scene-Entity-Component 架构**。

World  
负责管理所有 Entity 的生命周期，包括：

- 更新
- 创建
- 删除

Scene  
Scene 更类似 **配置文件**，用于描述当前场景需要加载哪些 Entity。

Entity  
Entity 是游戏对象的主体，游戏逻辑主要围绕 Entity 的生成和 Component 的修改。

Component  
Component 表示 Entity 的能力。

Component 分为两类：

数据型 Component  

例如：

JumpComponent

用于描述：

- 最大跳跃次数
- 是否支持蓄力
- 蓄力时间
- 跳跃高度

逻辑型 Component  

例如：

AnimationComponent

负责：

- 播放动画
- 管理动画状态参数

---

# 工作流

开发流程如下：

1. 在 **PrefabManager** 中编写 Entity 模板
2. 在 **SceneManager** 中配置 Scene 需要加载的 Entity
3. Scene 通过 Prefab 实例化 Entity
4. World 负责统一更新 Entity

---

# AI 系统

AI 逻辑结构与玩家逻辑保持一致：InputComponent+ControllerComponent+其他 Component
区别在于 Input 来源不同：

玩家 Input：键盘输入  
AI Input：AI 决策状态机

Controller 使用 **状态机（FSM）** 实现。

玩家由于行为复杂，使用 **双状态机结构**：这样可以组合出复杂行为，例如：MoveStateMachine ActionStateMachine

- 移动 + 攻击
- 跳跃 + 攻击

---

## AI 决策

AI 决策也采用状态机实现。

优点：

- 状态权限稳定
- 逻辑清晰

缺点：

- 状态复用性较低

因此 AI 只维护少量决策状态：

- Idle
- Patrol
- Chase
- Attack

复杂行为通过 **环境感知** 实现。

AI 使用 **传感器子实体** 模拟感官，例如：

- 视觉检测
- 地面检测
- 攻击范围检测

不同 AI 通过调整：

- 传感器类型
- 传感器范围

实现不同的行为模式。

AI 的具体行为通过 **Timeline + 委托函数** 实现。

---

# 实现难点

### 1. Entity 生命周期管理

游戏对象在运行时会频繁创建和删除，并且存在：

- 父子关系
- Timeline 行为

解决方案：

- 删除采用 **延迟删除**
- Entity 仅标记 Destroy
- 帧末统一删除

父子关系：

- 每帧展开父子层级缓存
- 删除父节点时递归删除子节点

Timeline：

- 按 Entity 绑定
- Entity 析构时自动清理 Timeline

---

### 2. Scene Streaming 状态问题

Scene 动态加载会导致：

- Entity 状态丢失
- Entity 跨 Scene 移动

当前解决方案：

World 维护 Scene Entity 状态表：

- Scene 首次加载记录 ID
- Entity 被销毁时更新状态

Scene 再次加载时：

- Dead Entity 不再生成

目前只实现 **死亡状态记录**。

复杂组件状态快照仍在探索。

---

### 3. AI 代码复用

解决方案：

保持：

- 决策状态稳定
- 行为状态稳定

通过：

- 传感器配置
- Timeline 行为实现

实现不同 AI。

---

### 4. Player 行为复杂

问题：

Player 存在大量打断式动作，例如：

- 移动中攻击
- 跳跃中攻击

解决：

- Move / Action 双状态机
- 动画状态机 Layer

实现：

上层动画覆盖下层动画。

---

### 5. 物理信息不足

碰撞体本身无法判断：

- 是否在地面

解决方案：

- 物理层增加 **Layer 标识**
- 逻辑层使用 **TagComponent**

用于识别：

- 地面
- 玩家
- 敌人

---

# 项目展示
(https://www.bilibili.com/video/BV1LewazME8Q/?spm_id_from=333.1387.homepage.video_card.click&vd_source=fa2133aac5f1c74a4709b5b3e6d25be2)
