# MCSDK

### 功能指标

![image-20230221124727184](https://pic-1256068477.cos.ap-shanghai.myqcloud.com/img/image-20230221124727184.png)



### 电机参数修改

* 电机参数：Inc\pmsm_motor_parameters.h
* 电源参数：Inc\power_stage_parameters.h



### 工程问题记录

* TM1650上电不显示：TM1650芯片内部初始化并未完成，所以Delay一段时间，等TM1650内部启动完成。
