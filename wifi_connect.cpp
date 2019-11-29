#include <iostream>
#include <fstream>

#define CMD "wpa_cli -i wlan0 reconfigure"

using namespace std;

void write_wpa_supplicant()
{
	ofstream wpa;
	wpa.open("/etc/wpa_supplicant/wpa_supplicant.conf");
	if(!wpa)
		cout << "Cannot open file\n";
	else
	{
		wpa << "country=GB" << endl;
		wpa << "ctrl_interface=/var/run/wpa_supplicant" << endl;
		wpa << "update_config=1" << endl;
		wpa << "network={" << endl;
		wpa << "\tssid=\"id\"" << endl;
		wpa << "\tpsk=\"password\"" << endl;
		wpa << "}";
		wpa.close();
	}
}

int main(void)
{
	write_wpa_supplicant();
	system(CMD);
	//restart wlan0 interface
	system("ifdown wlan0");
	system("ifup wlan0");
	system("ifconfig wlan0 up");
}
