野火鲁班猫2S，安装最简系统，纯命令框控制

1、开wifi
	sudo nmcli radio wifi off			
	sudo nmcli radio wifi on			
	nmcli dev wifi list			
	sudo nmcli device wifi connect "bbzt" password "8888888888" ifname wlan0 
2、ros一键安装
	wget http://fishros.com/install -O fishros && . fishros
3、创建工作区
	mkdir -p ~/catkin_ws/src
	cd ~/catkin_ws/src
	catkin_init_workspace
	cd ~/catkin_ws/
	catkin_make
	source devel/setup.bash
4、打开串口3和5	//两个串口分别连接雷达和飞控
	/boot/uEnv/board.txt （board 是你所用的板子的名称）
	重启		#在终端上输入“sync”再拔电关机
	ls /dev/tty* 	#检查是否使能成功，例如/dev/ttyS3
5、测试雷达读取数据
	将lsn10p包放入src工作区
	/*根据雷达文档操作*/	
	catkin_make -DCATKIN_WHITELIST_PACKAGES=lslidar_msgs
	catkin_make -DCATKIN_WHITELIST_PACKAGES=lslidar_driver
	roslaunch lslidar_driver lslidar_serial.launch	//串口打印数据
	安装时会缺各种包，因为是简版ros，根据报错csdn！
	
6、去GitHub下载对应的hector-mapping包放入src中
	catkin_make工作区。
7、测试
6、sudo apt install ros-noetic-LIBARIES	//主要ros的版本必须为noetic
