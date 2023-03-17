# ChanneldUE Demos
TEST
This repository contains the UE project that demonstrates the features and how-tos of [ChanneldUE](https://github.com/metaworking/channeld-ue-plugin).

本UE项目用于展示[ChanneldUE插件](https://github.com/metaworking/channeld-ue-plugin)的特性和使用方法。

To clone the repo with all submodules, use the following command:

通过以下命令克隆代码仓库，可以自动克隆所有子模块：
```bash
git clone --recurse-submodules https://github.com/metaworking/channeld-ue-demos
```

## Contained maps and how to use them:
- TestReplication: single server test map. Used for basic single server replication test and performance benchmark.
  - Press `T` to create a `BP_TestRepActor`. The actor will follow the player across servers (requires `BP_SingleChannelView` as the channel data view)
  - Press `R` to toggle the latest created `BP_TestRepActor`'s movement and rotation
  - Press `C` to create a cube that can be pushed
  - Press `B` to trigger a multicast RPC on GameState
  - Press `N` to create an NPC that moves randomly
  - Use `Mouse Wheel` to zoom in/out the camera
- TestMultiServer: multi server test map. Used for testing player switching and replication between offline level (TestMultiServer_SinglePlayer) and multiple online levels.
  - Press `Enter` to display the available online levels
  - Press `1-3` to enter the corresponding online level. If already in the coresspoding online levels, press again to return to offline level.
- TestPhysics: physics replication test map.
  - Have the same operations as TestReplication
- TestSpatial_NxN: maps for testing NxN spatial channels.
  - After pressing `Space` to jump, the GameState's Jumps property will be modified and synchronized to all spatial servers.
- ClientOnlyChatDemo: chat room demo in client-only mode.
- ServerAuthChatDemo: chat room demo in server-authoritative mode.

## 包含的地图及操作：
- TestReplication: 单服测试场景。用于基本的单服同步测试和性能基准测试。
  - 按`T`键创建一个`BP_TestRepActor`。该Actor会跟随创建的玩家跨服（需要使用`BP_SingleChannelView`作为频道数据视图）
  - 按`R`键开启/停止最近一次创建的`BP_TestRepActor`的位移和旋转
  - 按`C`键创建一个可以被推动的立方体
  - 按`B`键触发GameState的多播RPC
  - 按`N`键创建一个随机移动的NPC
  - `鼠标滚轮`拉远拉近摄像机
- TestMultiServer：多房间测试场景。用于测试玩家在离线的房间（TestMultiServer_SinglePlayer）和多个在线房间之间切换和同步。
  - 按`回车`键显示当前可以进入的房间列表
  - 按`1-3`键进入对应的房间。如果已经在对应的房间中，则退回到离线房间
- TestPhysics：测试物理同步
  - 操作同TestReplication
- TestSpatial_NxN：测试NxN空间频道
  - 按`空格`键角色跳跃后，会修改主服务器GameState的Jumps属性，并同步到各个空间服务器
- ClientOnlyChatDemo：无服务器模式的聊天室示例
- ServerAuthChatDemo：服务器授权模式的聊天室示例
