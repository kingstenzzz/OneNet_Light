本项目基于ardiuno接入onenet，请事先搭建好ardiuno开发环境。

 const char* ssid = "kingsten";//WIFI名
 const char* password = "23622033";//密码
 const char* mqtt_server = "183.230.40.39";//onenet服务器
 const char* DEV_ID = "583458957"; //设备ID
 const char* DEV_PRO_ID = "315799"; //产品ID
 const char* DEV_KEY = "IDePEtsFhX***6s="; //API KEY
 IPAddress staticIP(192,168,2,107);//固定IP地址
IPAddress gateway(192,168,2,1);//网关地址
IPAddress subnet(255,255,255,0);//子网掩码地址
根据个人情况修改以上内容
====================================
接入了siri通过声控控制开关
通过以下地址添加捷径。
https://www.icloud.com/shortcuts/c83d5df4dbd045edb560186a84174e68