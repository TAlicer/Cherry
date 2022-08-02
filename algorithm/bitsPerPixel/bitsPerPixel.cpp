#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> //close()
#include <string.h> //strcmp()等字符串操作函数
#include <stdlib.h> //atoi() 字符串转int
#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>

//检测jpg位深
int get_jpg_bitsPerPixel(const char *bytes)
{
	int i = 2;
	int bitsPerPixel=0;
	while (1) {
		int marker = (bytes[i] & 0xff) << 8 | (bytes[i + 1] & 0xff);
		int size = (bytes[i + 2] & 0xff) << 8 | (bytes[i + 3] & 0xff);
		if (marker >= 0xffc0 && marker <= 0xffcf && marker != 0xffc4
				&& marker != 0xffc8) {
			bitsPerPixel = (bytes[i + 4] & 0xff) * (bytes[i + 9] & 0xff);
			break;
		} else {
			i += size + 2;
		}
	}
	
	return bitsPerPixel;
}

//检测png位深
int get_png_bitsPerPixel(const char *bytes)
{
	int bitsPerPixel = bytes[24] & 0xff;
	if ((bytes[25] & 0xff) == 2) {
		bitsPerPixel *= 3;
	} else if ((bytes[25] & 0xff) == 6) {
		bitsPerPixel *= 4;
	}
	
	return bitsPerPixel;
}

int main()
{
	int bitsPerPixel_HP_jpg = 0 ;
	int bitsPerPixel_Lager_jpg = 0;
	
	std::ifstream ifs1("pc.jpg");
    std::string strOut1((std::istreambuf_iterator<char>(ifs1)), std::istreambuf_iterator<char>(0));
	bitsPerPixel_HP_jpg = get_jpg_bitsPerPixel(strOut1.c_str());
	
	std::ifstream ifs2("device.jpg");
    std::string strOut2((std::istreambuf_iterator<char>(ifs2)), std::istreambuf_iterator<char>(0));
	bitsPerPixel_Lager_jpg = get_jpg_bitsPerPixel(strOut2.c_str());
	
	
	std::cout << "bitsPerPixel_pc_jpg = " << bitsPerPixel_HP_jpg << std::endl;
	std::cout << "bitsPerPixel_device_jpg = " << bitsPerPixel_Lager_jpg << std::endl;
	
	return 0;
}