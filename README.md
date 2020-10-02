# 驭远杯
## 模块一 运动：
    输入：控制指令，红外传感器信息
    param: 
    输出：行动状态指令
## 模块二 控制：
    输入：环境讯息（感知，循迹，碰撞） 
    输出：行动状态指令
## 模块三 感知：
    输入：摄像头信息（从硬件接口得到）
    输出：画面是否有灯光（bool）， 颜色（bool）
## 模块四 碰撞：
    输入：碰撞信息（从硬件接口中得到）
        param: ...
    输出：有无碰撞
    ```java
        @param bool touched 
        // 如果touched为真，则小车与灯塔已达到碰撞状态
    ```
## 附录：
    规则网页：https://mp.weixin.qq.com/s/D6dDW7oGuLzhpgyk5TNQ_A
    
