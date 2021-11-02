# ShootPractice
A UE4 game project of Shooting target
## 功能
实现了射击打靶、切换武器的功能，用UMG实现了手机操作界面，和分数显示。<br/>
射击采用射线检测，达到10分时用移动靶代替静止靶。
## 遇到问题
用高版本SDK生成时，虚幻默认的grandle版本过低，需要修改依赖。<br/>
蓝图获取游戏模式转化为继承自c++的蓝图类后调用BluePrintCallable方法会导致虚幻引擎的Bug，无法启动编辑器。<br/>
input interface和UMG的触摸不能同时使用，UMG不支持同时按两个按钮。<br/>
在其他类使用GameMode类时修改GameMode类可能导致安卓端闪退。
