#include "git.h"

Data_TypeDef Data_init;						  // �豸���ݽṹ��
Threshold_Value_TypeDef threshold_value_init; // �豸��ֵ���ýṹ��
Device_Satte_Typedef device_state_init;		  // �豸״̬
//DHT11_Data_TypeDef DHT11_Data;

void errorLog(U8 num)
{
	while (1)
	{
		printf("ERROR%d\r\n", num);
	}
}
// ��ȡGPS��λ��Ϣ
void parseGpsBuffer()
{
	char *subString;
	char *subStringNext;
	char i = 0;
	char usefullBuffer[2];
	if (Save_Data.isGetData)
	{
		Save_Data.isGetData = false;
		for (i = 0; i <= 6; i++)
		{
			if (i == 0)
			{
				if ((subString = strstr(Save_Data.GPS_Buffer, ",")) == NULL)
					errorLog(1); // ��������
			}
			else
			{
				subString++;
				if ((subStringNext = strstr(subString, ",")) != NULL)
				{
					switch (i)
					{
					case 1:
						memcpy(Save_Data.UTCTime, subString, subStringNext - subString);
						break; // ��ȡUTCʱ��
					case 2:
						memcpy(usefullBuffer, subString, subStringNext - subString);
						break; // ��ȡUTCʱ��
					case 3:
						memcpy(Save_Data.latitude, subString, subStringNext - subString);

						break; // ��ȡγ����Ϣ
					case 4:
						memcpy(Save_Data.N_S, subString, subStringNext - subString);
						break; // ��ȡN/S
					case 5:
						memcpy(Save_Data.longitude, subString, subStringNext - subString);
						break; // ��ȡ������Ϣ
					case 6:
						memcpy(Save_Data.E_W, subString, subStringNext - subString);
						break; // ��ȡE/W

					default:
						break;
					}

					subString = subStringNext;
					Save_Data.isParseData = true;
					if (usefullBuffer[0] == 'A')
					{
						device_state_init.location_state = 1;
						Save_Data.isUsefull = true;
					}

					else if (usefullBuffer[0] == 'V')
						Save_Data.isUsefull = false;

					// if (Save_Data.latitude > 0 && Save_Data.longitude > 0)
					// {
					// }
				}
				else
				{
					errorLog(2); // ��������
				}
			}
		}
	}
}
F32 longitude_sum, latitude_sum;
U8 longitude_int, latitude_int;
void printGpsBuffer()
{
	// ת��Ϊ����
	longitude_sum = atof(Save_Data.longitude);
	latitude_sum = atof(Save_Data.latitude);
	// printf("ά�� = %.5f %.5f\r\n",longitude_sum,latitude_sum);
	// ����
	longitude_int = longitude_sum / 100;
	latitude_int = latitude_sum / 100;

	// ת��Ϊ��γ��
	longitude_sum = longitude_int + ((longitude_sum / 100 - longitude_int) * 100) / 60;
	latitude_sum = latitude_int + ((latitude_sum / 100 - latitude_int) * 100) / 60;
	device_state_init.location_state = 1;
	if (Save_Data.isParseData)
	{
		Save_Data.isParseData = false;

		// printf("Save_Data.UTCTime = %s\r\n", Save_Data.UTCTime);
		if (Save_Data.isUsefull)
		{
			Save_Data.isUsefull = false;
		}
		else
		{
			// printf("GPS DATA is not usefull!\r\n");
		}
	}
}
// ��ȡ���ݲ���
mySta Read_Data(Data_TypeDef *Device_Data)
{

	// ��ȡ��γ��
	parseGpsBuffer();
	if (device_state_init.location_state == 1)
	{
		// ������γ��
		printGpsBuffer();
	}
	return MY_SUCCESSFUL;
}

// ��ʼ��
mySta Reset_Threshole_Value(Threshold_Value_TypeDef *Value, Device_Satte_Typedef *device_state)
{

	//Value->Distance_value = 100;
  // д
  //W_Test();
	// ��
	R_Test();
	// ״̬����
	device_state->close_link = 5;
//	longitude_sum = 110.1541548;
//	latitude_sum = 30.25415487;
//	W_Test();
	return MY_SUCCESSFUL;
}
// ����OLED��ʾ��������
mySta Update_oled_massage()
{
#if OLED // �Ƿ��
	char str[50];
	if(device_state_init.close_link){
		sprintf(str, " ��������: %02d  ",device_state_init.close_link);
	}else{
		sprintf(str, " ���ӶϿ�: %02d  ",device_state_init.close_link);
	}
	OLED_ShowCH(0, 0, (unsigned char *)str);
	// ��λ�ɹ� 
	if(device_state_init.location_state == 1){
		sprintf(str, " GPS Succeed  ");
	}else{
		sprintf(str, " GPS Error    ");
	}
	OLED_ShowCH(0, 2, (unsigned char *)str);
	sprintf(str, "����: %06f ",longitude_sum );
	OLED_ShowCH(0, 4, (unsigned char *)str);
	sprintf(str, "γ��: %06f ",latitude_sum);
	OLED_ShowCH(0, 6, (unsigned char *)str);
#endif

	return MY_SUCCESSFUL;
}

// �����豸״̬
mySta Update_device_massage()
{
	// ��������
	if (device_state_init.close_link == 0 || device_state_init.open)
	{
		BEEP = ~BEEP;
	}
	else
	{	
		BEEP=0;
	}

	return MY_SUCCESSFUL;
}

// ��ʱ��
void Automation_Close(void)
{
	// ��������
	if(device_state_init.close_link ){
		device_state_init.close_link --;
	}
	
	if (Data_init.App)
	{
		switch (Data_init.App)
		{
		case 1:
			SendMqtt(1); // �������ݵ�APP
			break;
		case 2:
			SendData(); // �������ݵ���ƽ̨
			break;
		}
		Data_init.App = 0;
	}

}
// ��ⰴ���Ƿ���
static U8 num_on = 0;
static U8 key_old = 0;
void Check_Key_ON_OFF()
{
	U8 key;
	key = KEY_Scan(1);
	// ����һ�εļ�ֵ�Ƚ� �������ȣ������м�ֵ�ı仯����ʼ��ʱ
	if (key != 0 && num_on == 0)
	{
		key_old = key;
		num_on = 1;
	}
	if (key != 0 && num_on >= 1 && num_on <= Key_Scan_Time) // 25*10ms
	{
		num_on++; // ʱ���¼��
	}
	if (key == 0 && num_on > 0 && num_on < Key_Scan_Time) // �̰�
	{
		switch (key_old)
		{
		case KEY1_PRES:
			printf("Key1_Short\n");
			if(device_state_init.waning){
				device_state_init.waning = 0;
			}else{
				device_state_init.waning = 1;
			}
			if (Data_init.App == 0) {
       Data_init.App = 1;
			}
			break;
		case KEY2_PRES:
			printf("Key2_Short\n");

			break;
		case KEY3_PRES:
			printf("Key3_Short\n");

			break;

		default:
			break;
		}
		num_on = 0;
	}
	else if (key == 0 && num_on >= Key_Scan_Time) // ����
	{
		switch (key_old)
		{
		case KEY1_PRES:
			printf("Key1_Long\n");

			break;
		case KEY2_PRES:
			printf("Key2_Long\n");

			break;
		case KEY3_PRES:
			printf("Key3_Long\n");

			break;
		default:
			break;
		}
		num_on = 0;
	}
}
// ����json����
mySta massage_parse_json(char *message)
{

	cJSON *cjson_test = NULL; // ���json��ʽ
	//cJSON *cjson_data = NULL; // ����
	const char *massage;
	// ������������
	u8 cjson_cmd; // ָ��,����

	/* ��������JSO���� */
	cjson_test = cJSON_Parse(message);
	if (cjson_test == NULL)
	{
		// ����ʧ��
		printf("parse fail.\n");
		return MY_FAIL;
	}

	/* ���θ���������ȡJSON���ݣ���ֵ�ԣ� */
	cjson_cmd = cJSON_GetObjectItem(cjson_test, "cmd")->valueint;
	/* ����Ƕ��json���� */
	//cjson_data = cJSON_GetObjectItem(cjson_test, "data");

	switch (cjson_cmd)
	{
	case 0x01: // ��Ϣ��
		device_state_init.open = cJSON_GetObjectItem(cjson_test, "open")->valueint;
		break;
	case 0x02: // ��Ϣ��
		device_state_init.close_link = cJSON_GetObjectItem(cjson_test, "heart")->valueint;
		device_state_init.close_link = 5;
		break;
	case 0x03: // ���ݰ�

		break;
	case 0x04: // ���ݰ�
		Data_init.App = cjson_cmd + 1;

		break;
	default:
		break;
	}

	/* ���JSON����(��������)���������� */
	cJSON_Delete(cjson_test);

	return MY_SUCCESSFUL;
}
