# ChanneldUE Demos

This repository contains the UE project that demonstrates the features and how-tos of [ChanneldUE](https://github.com/metaworking/channeld-ue-plugin).

本UE项目用于展示[ChanneldUE插件](https://github.com/metaworking/channeld-ue-plugin)的特性和使用方法。

To clone the repo with all submodules, use the following command:

通过以下命令克隆代码仓库，可以自动克隆所有子模块：
```bash
git clone --recurse-submodules https://github.com/metaworking/channeld-ue-demos
```

## Contained maps and how to use them:
- TestReplication: single server test map. Used for basic single server replication test and performance benchmark.
  - Press `T` to create a `BP_TestRepActor`
  - Press `R` to toggle the latest created `BP_TestRepActor`'s movement and rotation
  - Press `C` to create a cube that can be pushed
  - Press `B` to trigger a multicast RPC on GameState
  - Press `N` to create an NPC that moves randomly
  - Use `Mouse Wheel` to zoom in/out the camera
- TestPhysics: physics replication test map.
  - Have the same controls as TestReplication
- TestLandscape: movement replication on Landscape test map.
  - Have the same controls as TestReplication
- TestAssetReplication: physics replication test map.
  - Have the same controls as TestReplication
  - Move onto the texts to trigger events
- TestMultiServer: multi server test map. Used for testing player switching and replication between offline level (TestMultiServer_SinglePlayer) and multiple online levels.
  - Press `Enter` to display the available online levels
  - Press `1-3` to enter the corresponding online level. If already in the coresspoding online levels, press again to return to offline level.
- TestSpatial_MxN: maps for testing MxN spatial channels. 
  - Based on `TestReplication`, the following controls are added:
  - Press `I` to toggle between default third-person AOI and full map AOI.
  - Press `L` to lock/unlock the pawn's spatial channel handover.
  - After pressing `Space` to jump, the GameState's Jumps property will be modified and synchronized to all spatial servers.
- ClientOnlyChatDemo: chat room demo in client-only mode.
- ServerAuthChatDemo: chat room demo in server-authoritative mode.

### The project and editor settings required to run the maps:
| Map | Channel Data View Class | Server Groups | Launch Channeld Parameters |
| ------ | ------ | ------ | ------ |
| TestReplication<br/>TestPhysics<br/>TestLandscape<br/>TestAssetReplication<br/> | SingleChannelDataView | Group 0: Server View Class = SingleChannelDataView, Num = 1 | (no change) |
| TestMultiServer | BP_MultiSubworldsView | Group 0: Server View Class = BP_MultiSubworldsView, Num = 3 | (no change) |
| TestSpatial_2x2 | BP_SpatialChannelView | Group 0: Server View Class = SpatialMasterServerView, Num = 1; Group 1: Server View Class = BP_SpatialChannelView, Num = 2 | -scc=config/spatial_static_2x2.json |
| TestSpatial_4x1 | BP_SpatialChannelView | Group 0: Server View Class = SpatialMasterServerView, Num = 1; Group 1: Server View Class = BP_SpatialChannelView, Num = 2 | -scc=config/spatial_static_4x1.json |
| TestSpatial_Benchmark | BP_SpatialChannelView | Group 0: Server View Class = SpatialMasterServerView, Num = 1; Group 1: Server View Class = BP_SpatialChannelView, Num = 9 | -scc=config/spatial_static_benchmark.json |

## 包含的地图及操作：
- TestReplication: 单服测试场景。用于基本的单服同步测试和性能基准测试。
  - 按`T`键创建一个`BP_TestRepActor`
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
- TestLandscape: 测试在Landscape上的移动同步
  - 操作同TestReplication
- TestAssetReplication：测试资产同步
  - 操作同TestReplication
  - 移动到对应的文字上触发事件
- TestSpatial_MxN：测试MxN空间频道。在`TestReplication`场景的基础上，增加了以下操作：
  - 按`I`键切换默认第三人称兴趣范围和全地图兴趣范围
  - 按`L`锁定/解锁玩家角色的空间频道迁移
  - 按`空格`键角色跳跃后，会修改主服务器GameState的Jumps属性，并同步到各个空间服务器
- ClientOnlyChatDemo：无服务器模式的聊天室示例
- ServerAuthChatDemo：服务器授权模式的聊天室示例\

### 各个地图运行需要的项目和编辑器设置：
| 地图 | Channel Data View Class | Server Groups | Launch Channeld Parameters |
| ------ | ------ | ------ | ------ |
| TestReplication<br/>TestPhysics<br/>TestLandscape<br/>TestAssetReplication<br/> | SingleChannelDataView | Group 0: Server View Class = SingleChannelDataView, Num = 1 | (无变化) |
| TestMultiServer | BP_MultiSubworldsView | Group 0: Server View Class = BP_MultiSubworldsView, Num = 3 | (无变化) |
| TestSpatial_2x2 | BP_SpatialChannelView | Group 0: Server View Class = SpatialMasterServerView, Num = 1; Group 1: Server View Class = BP_SpatialChannelView, Num = 2 | -scc=config/spatial_static_2x2.json |
| TestSpatial_4x1 | BP_SpatialChannelView | Group 0: Server View Class = SpatialMasterServerView, Num = 1; Group 1: Server View Class = BP_SpatialChannelView, Num = 2 | -scc=config/spatial_static_4x1.json |
| TestSpatial_Benchmark | BP_SpatialChannelView | Group 0: Server View Class = SpatialMasterServerView, Num = 1; Group 1: Server View Class = BP_SpatialChannelView, Num = 9 | -scc=config/spatial_static_benchmark.json |
