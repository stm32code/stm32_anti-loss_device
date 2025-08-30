package com.example.anti_lossdevice.utils;

import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

import com.example.anti_lossdevice.Bluetooth.BlueTooth;
import com.itfitness.mqttlibrary.MQTTHelper;

import java.io.IOException;
import java.io.InputStream;

public class Common {
    public static String Port = "1883";
    public static String Sever = "tcp://iot-06z00axdhgfk24n.mqtt.iothub.aliyuncs.com" + ":" + Port;
//    public static String Port = "6002";
//    public static String Sever = "tcp://192.168.101.77" + ":" + Port;

    public static String ReceiveTopic = "/broadcast/h9sj0Mj5CyC/test2";
    public static String PushTopic = "/broadcast/h9sj0Mj5CyC/test1";
    public static String DriveID = "h9sj0Mj5CyC.smartapp|securemode=2,signmethod=hmacsha256,timestamp=1710895918379|";
    public static String DriveName = "smartapp&h9sj0Mj5CyC";
    public static String DrivePassword = "b0a90bff5a8686c95aae4db2b5d60b9c8b4496dbfb734b75ab59a83675d9575d";
    public static String Drive2ID = "1181073148";
    public static String api_key = "zVkyyNRjo4lk0BqXx9zxibg5uI0=";
    public static boolean DeviceOnline = false;
    public static String LatestOnlineDate = "离线";
    public static MQTTHelper mqttHelper = null;
    public static String MY_UUID = "00001101-0000-1000-8000-00805F9B34FB";  //要连接通信，此id必须和对方设备保持一致
    public static final int MSG_GET_DATA = 101; //获取到数据
    public static final int MSG_ERROR = 55;   // 错误
    public static final int MSG_CONNET = 200; // 连接到服务器
    public static final int SEND_OK = 201; //发送成功
    public static final int SEND_ERROR = 202;//发送失败
    public static final int SCAN_START = 52; //扫描蓝牙
    public static String CONNET_NAME = ""; //连接的蓝牙名称
    public static boolean ISBTCONNECT = false;  //蓝牙是否连接
    public static BlueTooth blueTooth;

}
