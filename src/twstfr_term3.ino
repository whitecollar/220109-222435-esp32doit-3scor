#include <Preferences.h>
#include <ArduinoJson.h>
#include "WiFi.h" 
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
#include <HTTPClient.h>
#include <Keypad.h>
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"

#define ROW_NUM     6
#define COLUMN_NUM  6




char keys[ROW_NUM][COLUMN_NUM] = {
  {'0','5','2','8','B','{'},
  {'.','6','3','9','C','}'},
  {'l','D','n','^','p','['},
  {'q','*','E','F','u',']'},
  {'v','4','1','7','A','/'},
  {'!','@','#','$','%','?'}
};



byte pin_rows[ROW_NUM] =  {14,12,26,13,27,25}; //{12,13,14,25,26,27};
byte pin_column[COLUMN_NUM] = {2,32,15,33,23,5}; //{2,4,5,15,32,33};
String ABC;
bool connected = false;
Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );
LiquidCrystal_PCF8574 lcd(0x27);
Preferences preferences;
TaskHandle_t Task1;
TaskHandle_t Task2;
TaskHandle_t Task3;
String ssid;
String password;
int tr = 0;
String setmenu = "222";
byte error, address;
int devicecount;
String Sync, DispScor;
String DispScorLong;
String DispScorTemp;
String DispScor_1 = "";
String DispScor_2 = "";
String DispScor_3 = "";

String ServAddr= "http://192.168.123.1";
//String ServAddr= "http://192.168.88.45";
//String ServAddr= "http://79.104.192.118:8080/";
String iddev ="4";
int approve = 0;
int keyr = 1;
String memeber_id, post_json, bipm,namem, temp1,oneline, currentbip;
int chcom = 1;

//print to lcd
int printdisp (String p){
  lcd.setCursor(0, tr); 
  lcd.print(p);
  if (tr == 0){
    tr = 1;
  } else if (tr == 1){
    tr = 0;
  }
 return 1;         
}

void feedthedog () {
      TIMERG0.wdt_wprotect = TIMG_WDT_WKEY_VALUE;
      TIMERG0.wdt_feed = 1;
      TIMERG0.wdt_wprotect = 0;
}
//wifi connect function
//if (preferences.getString("ssid1name", "")){WFConnect (preferences.getString("ssid1name", ""),preferences.getString("ssid1pass", ""));}
//
int WFConnect (String s, String p){
   while (WiFi.status() != WL_CONNECTED) {
 //   for (int i = 1; i <= 5; i++) {
      Serial.println("Соединяемся с Wi-Fi");
      //printdisp ("connecting wifi_"+(String)i);
    
    //  String ss = "ssid"+String(i,DEC)+"name";
    //  String sp = "ssid"+String(i,DEC)+"pass";
    //  unsigned char* buf = new unsigned char[100]; 
    //  ss.getBytes(buf, 100, 0);
    //  char *Name = ( char*)buf;
    //  String s = preferences.getString(Name, ""); 
    //  sp.getBytes(buf, 100, 0);
    //  char *Pass = ( char*)buf;
    //  String p = preferences.getString(Pass, "");
       


      WiFi.begin(s.c_str(), p.c_str());
      if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Соединение с Wi-Fi установлено");
        printdisp ("conected wifi!");
        

        return 1;
        break;
      }
   // }
   }
  return 0;
}


//approve function 
int f_approve (){
  if (approve == 1) {
    approve=0;
    DispScor="";
    }
 return 1;
}
//ABC function
 



//key to disp and send to http 2 number scor
int DispScorT2 (String d){
     f_approve();
         if (DispScor.length() < 3) {
                    if (d == "1"){
                     DispScor=DispScor+'1';
                     //DispScorTemp=DispScorTemp+'1';
                     if (keyr==1) { DispScor_1=DispScor_1+'1';}
                     if (keyr==2) { DispScor_2=DispScor_2+'1';}
                     
                    // Serial.println (DispScor_3); 
                     Sync ="";   }
                  else if (d == "2"){
                     DispScor=DispScor+'2';
                     if (keyr==1) { DispScor_1=DispScor_1+'2';}
                     if (keyr==2) { DispScor_2=DispScor_2+'2';}
                     
                     DispScorTemp='2';
                     Sync ="";}
                  else if (d == "3"){
                     DispScor=DispScor+'3';
                     if (keyr==1) { DispScor_1=DispScor_1+'3';}
                     if (keyr==2) { DispScor_2=DispScor_2+'3';}
                     
                     DispScorTemp='3';
                     Sync ="";}
                  else if (d == "4"){
                     DispScor=DispScor+'4';
                     if (keyr==1) { DispScor_1=DispScor_1+'4';}
                     if (keyr==2) { DispScor_2=DispScor_2+'4';}
                     
                     DispScorTemp='4';
                     Sync ="";}
                  else if (d == "5"){
                     DispScor=DispScor+'5';
                     if (keyr==1) { DispScor_1=DispScor_1+'5';}
                     if (keyr==2) { DispScor_2=DispScor_2+'5';}
                     
                     DispScorTemp='5';
                     Sync ="";}
                  else if (d == "6"){
                     DispScor=DispScor+'6';
                     if (keyr==1) { DispScor_1=DispScor_1+'6';}
                     if (keyr==2) { DispScor_2=DispScor_2+'6';}
                     
                     DispScorTemp='6';
                     Sync ="";}
                  else if (d == "7"){
                     DispScor=DispScor+'7';
                     if (keyr==1) { DispScor_1=DispScor_1+'7';}
                     if (keyr==2) { DispScor_2=DispScor_2+'7';}
                     
                     DispScorTemp='7';
                     Sync ="";}
                  else if (d == "8"){
                     DispScor=DispScor+'8';
                     if (keyr==1) { DispScor_1=DispScor_1+'8';}
                     if (keyr==2) { DispScor_2=DispScor_2+'8';}
                     
                     DispScorTemp='8';
                     Sync ="";}
                  else if (d == "9"){
                     DispScor=DispScor+'9';
                     if (keyr==1) { DispScor_1=DispScor_1+'9';}
                     if (keyr==2) { DispScor_2=DispScor_2+'9';}
                     
                     DispScorTemp='9';
                     Sync ="";}
                  else if (d == "0"){
                     DispScor=DispScor+'0';
                     if (keyr==1) { DispScor_1=DispScor_1+'0';}
                     if (keyr==2) { DispScor_2=DispScor_2+'0';}
                     
                     DispScorTemp='0';
                     Sync ="";}
                  else  if (d == "E" and keyr!=2){          
                        
                    keyr=keyr+1;
                    DispScorLong = DispScorLong +"|" +DispScor+"|";  
                    DispScor="";
                    Serial.println(keyr);
                    Serial.println (DispScorLong);
                    Serial.println (DispScor);
                  }  
                  else  if (d == "E" and keyr==2){
                    DispScorLong = DispScorLong +"|" +DispScor+"|";  
                     keyr = 1;
                     Sync ="";
                     post_json = "{\"temp2\":\""+ABC+"\",\"temp1\":\""+temp1+"\",\"bip\":\""+bipm+"\",\"id_judge\":\""+iddev+"\",\"id_member\":\""+memeber_id+"\",\"scor\":\""+DispScorLong+"\",\"status\":\"1\"}";
                     DispScor=DispScor+" OK";
                     DispScor="";
                     DispScor_1="";
                     DispScor_2="";
                     DispScor_3="";
                     DispScorLong="";
                     ABC=" ";
                     Sync ="";
                     approve =1;
                          if (chcom==1){
                             if(WiFi.status()== WL_CONNECTED){
                                  WiFiClient client;
                                  HTTPClient http;
                                  http.begin(client, ServAddr+"/scs");
                                  http.addHeader("Content-Type", "application/json");
                                  int httpResponseCode = http.POST(post_json);
                                  Serial.print("HTTP Response code: ");
                                  Serial.println(httpResponseCode);
                                  http.end();
                                }
                                else {
                                  printdisp ("Error HTTP request");
                                }
                          }
                                                      
                  }
                  else if (d == "D"){
                     DispScor="";
                     DispScorLong="";
                     keyr = 1;
                     DispScor_1="";
                     DispScor_2="";
                     DispScor_3="";
                     ABC=" ";
                     Sync ="";}
                  else if (d == "."){
                     DispScor=DispScor+'.';
                     Sync ="";}
                  else {}
     }else{DispScor="";DispScorTemp="";} 
return 1;
}


//key to disp and send to http 3 number scor
int DispScorT3 (String d){
     f_approve();
         if (DispScor.length() < 3) {
                    if (d == "1"){
                     DispScor=DispScor+'1';
                     //DispScorTemp=DispScorTemp+'1';
                     if (keyr==1) { DispScor_1=DispScor_1+'1';}
                     if (keyr==2) { DispScor_2=DispScor_2+'1';}
                     if (keyr==3) { DispScor_3=DispScor_3+'1';}
                    // Serial.println (DispScor_3); 
                     Sync ="";   }
                  else if (d == "2"){
                     DispScor=DispScor+'2';
                     if (keyr==1) { DispScor_1=DispScor_1+'2';}
                     if (keyr==2) { DispScor_2=DispScor_2+'2';}
                     if (keyr==3) { DispScor_3=DispScor_3+'2';}
                     DispScorTemp='2';
                     Sync ="";}
                  else if (d == "3"){
                     DispScor=DispScor+'3';
                     if (keyr==1) { DispScor_1=DispScor_1+'3';}
                     if (keyr==2) { DispScor_2=DispScor_2+'3';}
                     if (keyr==3) { DispScor_3=DispScor_3+'3';}
                     DispScorTemp='3';
                     Sync ="";}
                  else if (d == "4"){
                     DispScor=DispScor+'4';
                     if (keyr==1) { DispScor_1=DispScor_1+'4';}
                     if (keyr==2) { DispScor_2=DispScor_2+'4';}
                     if (keyr==3) { DispScor_3=DispScor_3+'4';}
                     DispScorTemp='4';
                     Sync ="";}
                  else if (d == "5"){
                     DispScor=DispScor+'5';
                     if (keyr==1) { DispScor_1=DispScor_1+'5';}
                     if (keyr==2) { DispScor_2=DispScor_2+'5';}
                     if (keyr==3) { DispScor_3=DispScor_3+'5';}
                     DispScorTemp='5';
                     Sync ="";}
                  else if (d == "6"){
                     DispScor=DispScor+'6';
                     if (keyr==1) { DispScor_1=DispScor_1+'6';}
                     if (keyr==2) { DispScor_2=DispScor_2+'6';}
                     if (keyr==3) { DispScor_3=DispScor_3+'6';}
                     DispScorTemp='6';
                     Sync ="";}
                  else if (d == "7"){
                     DispScor=DispScor+'7';
                     if (keyr==1) { DispScor_1=DispScor_1+'7';}
                     if (keyr==2) { DispScor_2=DispScor_2+'7';}
                     if (keyr==3) { DispScor_3=DispScor_3+'7';}
                     DispScorTemp='7';
                     Sync ="";}
                  else if (d == "8"){
                     DispScor=DispScor+'8';
                     if (keyr==1) { DispScor_1=DispScor_1+'8';}
                     if (keyr==2) { DispScor_2=DispScor_2+'8';}
                     if (keyr==3) { DispScor_3=DispScor_3+'8';}
                     DispScorTemp='8';
                     Sync ="";}
                  else if (d == "9"){
                     DispScor=DispScor+'9';
                     if (keyr==1) { DispScor_1=DispScor_1+'9';}
                     if (keyr==2) { DispScor_2=DispScor_2+'9';}
                     if (keyr==3) { DispScor_3=DispScor_3+'9';}
                     DispScorTemp='9';
                     Sync ="";}
                  else if (d == "0"){
                     DispScor=DispScor+'0';
                     if (keyr==1) { DispScor_1=DispScor_1+'0';}
                     if (keyr==2) { DispScor_2=DispScor_2+'0';}
                     if (keyr==3) { DispScor_3=DispScor_3+'0';}
                     DispScorTemp='0';
                     Sync ="";}
                  else  if (d == "E" and keyr!=3){          
                        
                    keyr=keyr+1;
                    DispScorLong = DispScorLong +"|" +DispScor+"|";  
                    DispScor="";
                    Serial.println(keyr);
                    Serial.println (DispScorLong);
                    Serial.println (DispScor);
                  }  
                  else  if (d == "E" and keyr==3){
                    DispScorLong = DispScorLong +"|" +DispScor+"|";  
                     keyr = 1;
                     Sync ="";
                     post_json = "{\"temp2\":\""+ABC+"\",\"temp1\":\""+temp1+"\",\"bip\":\""+bipm+"\",\"id_judge\":\""+iddev+"\",\"id_member\":\""+memeber_id+"\",\"scor\":\""+DispScorLong+"\",\"status\":\"1\"}";
                     DispScor=DispScor+" OK";
                     DispScor="";
                     DispScor_1="";
                     DispScor_2="";
                     DispScor_3="";
                     DispScorLong="";
                     ABC=" ";
                     Sync ="";
                     approve =1;
                          if (chcom==1){
                             if(WiFi.status()== WL_CONNECTED){
                                  WiFiClient client;
                                  HTTPClient http;
                                  http.begin(client, ServAddr+"/scs");
                                  http.addHeader("Content-Type", "application/json");
                                  int httpResponseCode = http.POST(post_json);
                                  Serial.print("HTTP Response code: ");
                                  Serial.println(httpResponseCode);
                                  http.end();
                                }
                                else {
                                  printdisp ("Error HTTP request");
                                }
                          }
                                                      
                  }
                  else if (d == "D"){
                     DispScor="";
                     DispScorLong="";
                     keyr = 1;
                     DispScor_1="";
                     DispScor_2="";
                     DispScor_3="";
                     ABC=" ";
                     Sync ="";}
                  else if (d == "."){
                     DispScor=DispScor+'.';
                     Sync ="";}
                  else {}
     }else{DispScor="";DispScorTemp="";} 
return 1;
}



//key to disp and send to http original
int DispScorT (String d){
     f_approve();
         if (DispScor.length() < 6) {
                    if (d == "1"){
                     DispScor=DispScor+'1';
                     Sync ="";   }
                  else if (d == "2"){
                     DispScor=DispScor+'2';
                     Sync ="";}
                  else if (d == "3"){
                     DispScor=DispScor+'3';
                     Sync ="";}
                  else if (d == "4"){
                     DispScor=DispScor+'4';
                     Sync ="";}
                  else if (d == "5"){
                     DispScor=DispScor+'5';
                     Sync ="";}
                  else if (d == "6"){
                     DispScor=DispScor+'6';
                     Sync ="";}
                  else if (d == "7"){
                     DispScor=DispScor+'7';
                     Sync ="";}
                  else if (d == "8"){
                     DispScor=DispScor+'8';
                     Sync ="";}
                  else if (d == "9"){
                     DispScor=DispScor+'9';
                     Sync ="";}
                  else if (d == "0"){
                     DispScor=DispScor+'0';
                     Sync ="";}
                  else if (d == "A"){
                     ABC="A";
                     Sync ="";} 
                  else if (d == "B"){
                     ABC="B";
                     Sync ="";}
                  else if (d == "C"){
                     ABC="C";
                     Sync ="";}          
                  else  if (d == "E"){
                     Sync ="";
                     post_json = "{\"temp2\":\""+ABC+"\",\"temp1\":\""+temp1+"\",\"bip\":\""+bipm+"\",\"id_judge\":\""+iddev+"\",\"id_member\":\""+memeber_id+"\",\"scor\":\""+DispScor+"\",\"status\":\"1\"}";
                     DispScor=DispScor+" OK";
                     DispScor="";
                     ABC=" ";
                     Sync ="";
                     approve =1;
                          if (chcom==1){
                             if(WiFi.status()== WL_CONNECTED){
                                  WiFiClient client;
                                  HTTPClient http;
                                  http.begin(client, ServAddr+"/scs");
                                  http.addHeader("Content-Type", "application/json");
                                  int httpResponseCode = http.POST(post_json);
                                  Serial.print("HTTP Response code: ");
                                  Serial.println(httpResponseCode);
                                  http.end();
                                }
                                else {
                                  printdisp ("Error HTTP request");
                                }
                          }
                                                      
                  }
                  else if (d == "D"){
                     DispScor="";
                     ABC=" ";
                     Sync ="";}
                  else if (d == "."){
                     DispScor=DispScor+'.';
                     Sync ="";}
                  else {}
     }else{DispScor="";} 
return 1;
}

//firmware update setting
//x = 1 read; x = 0 write; x = 9988 clear;
int firmware (int x) {
  if (x ==0) {
    while(true){
               if (Serial.available() > 0) {
                  String incomingString = Serial.readString();
                  DynamicJsonDocument doc(1024);
                  deserializeJson(doc, incomingString);
                  preferences.begin("credentials", false);   
                  //ssid
                  //preferences.remove("ssid1name");
                  ssid = preferences.putString("ssid1name", (const char*) doc["ssid1name"]); 
                  password = preferences.putString("ssid1pass", (const char*) doc["ssid1pass"]);
                  ssid = preferences.putString("ssid2name", (const char*) doc["ssid2name"]); 
                  password = preferences.putString("ssid2pass", (const char*) doc["ssid2pass"]);
                  ssid = preferences.putString("ssid3name", (const char*) doc["ssid3name"]); 
                  password = preferences.putString("ssid3pass", (const char*) doc["ssid3pass"]);
                  ssid = preferences.putString("ssid4name", (const char*) doc["ssid4name"]); 
                  password = preferences.putString("ssid4pass", (const char*) doc["ssid4pass"]);
                  ssid = preferences.putString("ssid5name", (const char*) doc["ssid5name"]); 
                  password = preferences.putString("ssid15ass", (const char*) doc["ssid5pass"]);
                  //gsm
                  ssid = preferences.putString("apnname", (const char*) doc["apnname"]); 
                  password = preferences.putString("apnuser", (const char*) doc["apnuser"]);
                  password = preferences.putString("apnpass", (const char*) doc["apnpass"]);
                  //rest
                  password = preferences.putString("serveraddr", (const char*) doc["serveraddr"]);
                  //rest
                  password = preferences.putString("chcom", (const char*) doc["chcom"]);
                  password = preferences.putString("monitoring", (const char*) doc["monitoring"]);
                  preferences.end();
                  return x;
                  break; 
               }
    }
  
  } else if (x==1) {
      preferences.begin("credentials", false);
      DynamicJsonDocument doc(1024);
      //ssid
      doc["ssid1name"] = preferences.getString("ssid1name", "");
      doc["ssid1pass"] = preferences.getString("ssid1pass", "");
      doc["ssid2name"] = preferences.getString("ssid2name", "");
      doc["ssid2pass"] = preferences.getString("ssid2pass", "");
      doc["ssid3name"] = preferences.getString("ssid3name", "");
      doc["ssid3pass"] = preferences.getString("ssid3pass", "");
      doc["ssid4name"] = preferences.getString("ssid4name", "");
      doc["ssid4pass"] = preferences.getString("ssid4pass", "");
      doc["ssid5name"] = preferences.getString("ssid5name", "");
      doc["ssid5pass"] = preferences.getString("ssid5pass", "");
      //gsm
      doc["apnname"] = preferences.getString("apnname", "");
      doc["apnuser"] = preferences.getString("apnuser", "");
      doc["apnpass"] = preferences.getString("apnpass", "");
      //rest
      doc["serveraddr"] = preferences.getString("serveraddr", "");
      //system
      doc["chcom"] = preferences.getString("chcom", "");
      doc["monitoring"] = preferences.getString("monitoring", "");
      serializeJson(doc, Serial);
      preferences.end();
      return x;
  } else if (x==9988) {
      preferences.begin("credentials", false);
      preferences.clear();
      preferences.end();
      return x;
  }  else {
      return x;  
  }
}


int status (int x){
  if (x == 0) {
          while(true){
          //wifi
          Serial.print("IP:");
          Serial.println(WiFi.localIP());  
          Serial.print("MAC:");
          Serial.println(WiFi.macAddress());
          long rssi = WiFi.RSSI();
          Serial.print("RSSI dbm:");
          Serial.println(rssi);
          Serial.print("RSSI %:");
          rssi = 2*(rssi+100);
          Serial.println(rssi);
          wifi_power_t tx_power;
          Serial.print("TxPower:");
          tx_power=WiFi.getTxPower();
          Serial.println(tx_power);
          byte mac[6];
          WiFi.macAddress(mac);
          String uniq =  String(mac[0],HEX) +String(mac[1],HEX) +String(mac[2],HEX) +String(mac[3],HEX) + String(mac[4],HEX) + String(mac[5],HEX);
          Serial.print("uniq:");
          Serial.println(uniq);
          delay (1000);
          if (Serial.available()) {char ser = Serial.read(); if (ser  == '0'){break;}} 
          }
   } else if (x == 1 ){
          while(true){
          //GSM
          if(!connected) {
           //   GPRSConnect(APN);
          }
          byte mac[6];
          WiFi.macAddress(mac);
          String uniq =  String(mac[0],HEX) +String(mac[1],HEX) +String(mac[2],HEX) +String(mac[3],HEX) + String(mac[4],HEX) + String(mac[5],HEX);
          Serial.print("uniq:");
          Serial.println(uniq);
          delay (1000);
          if (Serial.available()) {char ser = Serial.read(); if (ser  == '0'){break;}} 
          }
   }
    return x;
}


void Task2code( void * parameter) {
          
  for(;;) {
    feedthedog();
     StaticJsonDocument<2000> doc; 
  if ((WiFi.status() == WL_CONNECTED)) {
    HTTPClient http;
    http.begin(ServAddr+"/ags");
    int httpCode = http.GET();
    if (httpCode > 0) {
      String payload = http.getString();
        DeserializationError error = deserializeJson(doc, payload);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
      const char* name  = doc["short_name"];
      const char* bip  = doc["bip"];
       String mid = doc["id"];
       String tempp = doc["temp1"];
       temp1= tempp;
      memeber_id  = mid;  
      bipm=String(bip);
     oneline = String(bip)+" "+String(name);

    }
    else {
      printdisp ("Error HTTP-request");
      //WFConnect("MikroTik-CEDA03","lexroot1");
      WFConnect("tw1","12345678");
      //WFConnect_cred();
    //добавить новую функцию с перебором точек доступа
    }
    http.end();
  }
  

 if ((WiFi.status() == WL_CONNECTED)) {
    HTTPClient http;
    http.begin(ServAddr+"/des?id="+iddev);
    int httpCode = http.GET();
    if (httpCode > 0) {
      String payload = http.getString();
        DeserializationError error = deserializeJson(doc, payload);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
        String setmenu1 = doc["type_dev"];
        setmenu =setmenu1;
      /* const char* bip  = doc["bip"];
       String mid = doc["id"];
       String tempp = doc["temp1"];
       temp1= tempp;
      memeber_id  = mid;  
      bipm=String(bip);
     oneline = String(bip)+" "+String(name);*/
     //Serial.println (setmenu1);

    }
    else {
      printdisp ("Error HTTP-request");
      //WFConnect("MikroTik-CEDA03","lexroot1");
      WFConnect("tw1","12345678");
      //WFConnect_cred();
    //добавить новую функцию с перебором точек доступа
    }
    http.end();

   
    

  }


  // Serial.println (setmenu);
    vTaskDelay( 2000 / portTICK_PERIOD_MS);
  }
  vTaskDelete( NULL );
}



void Task1code( void * parameter) {
  for(;;) {
         
      feedthedog();
       // lcd.init(); 
       if (setmenu=="2")
       {
         /* code */
       
       
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print(oneline);
       lcd.setCursor(0, 1);
       //lcd.print("\x20""\x20""\x20""\x20""\x20""\x20""\x20""\x20""\x20""\x20""\x20""\x20""\x20""\x20""\x20""\x20");
      // lcd.print(iddev+"\xFF""\xFF""\xFF""\x20""\x20""\x20""\x20""\x20""\x20""\x20");
       lcd.print(iddev+"\xFF""\xFF""\xFF"" "+DispScor); 
       lcd.setCursor(12, 1);
       //lcd.print("\xFF""\xFF""\xFF""\xFF");
      lcd.print("\xFF""\x5F"+ABC);
      lcd.setCursor(15, 1);
      lcd.print("\x5F");
       //delay(200);

       } else if (setmenu=="5")
       {
         /* code */
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print(oneline);
       lcd.setCursor(0, 1);
       //lcd.print("\x20""\x20""\x20""\x20""\x20""\x20""\x20""\x20""\x20""\x20""\x20""\x20""\x20""\x20""\x20""\x20");
      // lcd.print(iddev+"\xFF""\xFF""\xFF""\x20""\x20""\x20""\x20""\x20""\x20""\x20");
       lcd.print(iddev+"\xFF |"+DispScor_1); 
       lcd.setCursor(6, 1);
       //lcd.print("\xFF""\xFF""\xFF""\xFF");
      lcd.print("||"+DispScor_2);
      lcd.setCursor(10, 1);
      lcd.print("||"+DispScor_3);
      lcd.setCursor(14, 1);
      lcd.print("|");
       } else if (setmenu=="6")
       {
          /* code */
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print(oneline);
       lcd.setCursor(0, 1);
       //lcd.print("\x20""\x20""\x20""\x20""\x20""\x20""\x20""\x20""\x20""\x20""\x20""\x20""\x20""\x20""\x20""\x20");
      // lcd.print(iddev+"\xFF""\xFF""\xFF""\x20""\x20""\x20""\x20""\x20""\x20""\x20");
       lcd.print(iddev+"\xFF |"+DispScor_1); 
       lcd.setCursor(8, 1);
       //lcd.print("\xFF""\xFF""\xFF""\xFF");
      lcd.print("||"+DispScor_2);
      lcd.setCursor(12, 1);
      
      lcd.setCursor(14, 1);
      lcd.print("|");
       }
       
       vTaskDelay( 200 / portTICK_PERIOD_MS); 
       
  }
  vTaskDelete( NULL );
}

void Task3code( void * parameter) {
  
   //VTaskDelay(NULL);
  for(;;) {
    feedthedog();
    ///delay (5);
      char key = keypad.getKey();

  if (key) {
   // Serial.println(key);
    if (setmenu=="2")
       {
    DispScorT (String(key));
       } else if (setmenu=="5") {
    DispScorT3 (String(key));
       } else if (setmenu=="6") {
          DispScorT2 (String(key));
       }
  }
    vTaskDelay( 50 / portTICK_PERIOD_MS); 
  }
   vTaskDelete( NULL );
}
void setup() {
  //for rest only debug, remove or change to #define ifelse
  char key = keypad.getKey();
  if (key) {
      firmware (9988);
  }
  Serial.begin(115200);
  
  //Preferens for cred init
  preferences.begin("credentials", false);
    //add base env for pref to var example : server, gswm or wifi, budrate serial2, monitoring online(push metric (voltage signal an temperature ) to server over rest )
  //if (preferences.getString("chcom", "")){chcom = preferences.getString("chcom", "");}
    
  //Display init
  Wire.begin();
  Wire.beginTransmission(0x27);
  //error = Wire.endTransmission();
  Serial.print("Error: ");
  Serial.print(error);
  lcd.begin(16, 2);
  lcd.setBacklight(5000);
  lcd.home();
  //gprs init hw connect
  //Serial2.begin(57600);
  delay(1000);
  //I2C Diagnostic
  devicecount = 0; /*
  for (address = 1; address < 127; address++ )
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      printdisp ("Scanning...");
      if (address < 16)
          Serial.print("0");
          printdisp ("0");
          Serial.print(address, HEX);
          Serial.println("  !");
          devicecount++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
        Serial.println(address, HEX);
    }
  }
  if (devicecount == 0){
    Serial.println("No I2C devices found\n");
    printdisp ("No I2C devices found\n");
  }
  else{
    Serial.println("done\n"); 
  }  
  */
  delay(2000);
  //sim800l = new SIM800L((Stream *)&Serial2, SIM800_RST_PIN, 200, 512);
  //sim800l = new SIM800L((Stream *)&Serial2, SIM800_RST_PIN, 4000, 4096, (Stream *)&Serial);
  //sim800l = new SIM800L((Stream *)&Serial2, SIM800_RST_PIN, 4000, 4096);
  //wifi ini hw connect
  //Включать если есть параметр wifi
  WiFi.mode(WIFI_STA);
  WFConnect("tw1","12345678");
 




  xTaskCreatePinnedToCore(
        Task1code, /* Function to implement the task */
        "Task1", /* Name of the task */
        10000,  /* Stack size in words */
        NULL,  /* Task input parameter */
        5,  /* Priority of the task */
        &Task1,  /* Task handle. */
        1); /* Core where the task should run */

  //Task REST init
  xTaskCreatePinnedToCore(
        Task2code, /* Function to implement the task */
        "Task2", /* Name of the task */
        40000,  /* Stack size in words */
        NULL,  /* Task input parameter */
        10,  /* Priority of the task */
        &Task2,  /* Task handle. */
        0); /* Core where the task should run */  
    //Task keyboard
  xTaskCreatePinnedToCore(
        Task3code, /* Function to implement the task */
        "Task3", /* Name of the task */
        10000,  /* Stack size in words */
        NULL,  /* Task input parameter */
        5,  /* Priority of the task */
        &Task3,  /* Task handle. */
        1); /* Core where the task should run */        
  }

  

void loop() {

/*
  if (Serial.available()) {
    char ser = Serial.read();
    switch(ser){ 
      case '1':  firmware (0);; break;
      case '2':  firmware (1); break;
      case '3':  firmware (9988); break;
      case '4':  status (0); break;
      case '5':  status (1); break;
    }
  } */
  
 ///22 delay(2000);
    
}

