#include<Arduino.h>
#include<SAIOTDevice.h>

#define HOST "192.168.0.110"
#define PORT "3000"

SAIOTDevice hidrometro;

void setup(){
    hidrometro.startWifi();
    hidrometro.setDevice(accum);

    hidrometro.setSendingEvent("Status");
    hidrometro.serReceivingEvent("OnEvent")
    hidrometro.setReceivingConfigEvent("Config");
    hidrometro.setOnOffEvent("On_Off");

    hidrometro.startWSConnection(HOST,PORT);

}
void loop(){
    hidrometro.deviceHandle();
}