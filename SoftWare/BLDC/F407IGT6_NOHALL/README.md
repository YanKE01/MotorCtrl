# 基于正点原子开发版的BLDC 无感驱动



## 开发环境

* CUBEMX: 6.7.0
* KEIL: 5.28.0



## 测试硬件

* 务必将驱动板板载跳线由HALL<->H&Z 切换至 ==H&Z <-> ZERO==



## 开发记录

<img src="https://pic-1256068477.cos.ap-shanghai.myqcloud.com/img/image-20230208092629713.png" alt="image-20230208092629713" style="zoom:50%;" />

顺时针：HallLess的状态为 5 4 6 2 3 1

![image-20230208094506086](https://pic-1256068477.cos.ap-shanghai.myqcloud.com/img/image-20230208094506086.png)

逆时针：HallLess的状态为 5 1 3 2 6 4

<img src="https://pic-1256068477.cos.ap-shanghai.myqcloud.com/img/image-20230208095716516.png" alt="image-20230208095716516" style="zoom:50%;" />



## 实验效果

* 按下KEY0实现增速
* 按下KEY1实现减速
* 按下KEY2停止电机