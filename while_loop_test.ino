#include <Wire.h>

#define Addr 0x50 //  I2C address
int data;

void setup()
{
  // Initialise I2C communication as Master
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);

  REG_write(0x00,0x80); // 1.置能VCM
  REG_write(0x01,0x00); // 2.設定PGAC0   原始設定
  REG_write(0x02,0x00); // 3.設定PGAC1   原始設定
  REG_write(0x09,0x00); // 4.設定ADCS    原始設定
 // REG_write(0x07,0x80); // 5.設定ADCR0   原始設定 設定工作模式
  REG_write(0x08,0x00); // 5.設定ADCR1   原始設定 控制A/D數據狀態
  REG_write(0x03,0x00); // 6.設定PGACS   原始設定  
  REG_write(0x07,0x00); // 7.設定ADCR0   00000000 開啟工作模式
  
}

void loop()
{
  /*Serial.println("----0x07寫入ADRST置高-------");
  REG_write(0x07,0x80); // 將ADRST置高 , 進行A/D轉換
  REG_read(0x07);
  Serial.print("0x07=");
  Serial.println(data); // 確認0x07暫存器狀態數值 data應為128
  REG_read(0x08);
  Serial.print("0x08="); 
  Serial.println(data); 

  REG_read(0x04);
  Serial.print("0x04="); 
  Serial.println(data);
  REG_read(0x05);
  Serial.print("0x05="); 
  Serial.println(data);
  REG_read(0x06);
  Serial.print("0x06="); 
  Serial.println(data);
  
  delay(1000);*/
  
  Serial.println("----0x07寫入ADRST置低-------");
  REG_write(0x07,0x00); 
  REG_read(0x07); // 讀取ADCR0暫存器工作狀態 data應為0 工作模式
  Serial.print("0x07=");
  Serial.println(data);
  
  delay(1000);
  
  Serial.println("檢測EOC"); 
  do{
    
    REG_read(0x08);
    Serial.print("0x08="); 
    Serial.println(data); 
    
  }  while((data&2)==0);  // 檢測ADCR1中EOC位
  
  Serial.println("EOC為1"); 

  REG_read(0x04);
  Serial.print("0x04="); 
  Serial.println(data);
  REG_read(0x05);
  Serial.print("0x05="); 
  Serial.println(data);
  REG_read(0x06);
  Serial.print("0x06="); 
  Serial.println(data);
}

void REG_write(int a,int b){

  Wire.beginTransmission(Addr);
  Wire.write(a);  // 進入 暫存器
  Wire.write(b);  // 寫入控制內容
  //Serial.println("write sucess");

  Wire.endTransmission();  // Stop I2C Transmission

}

void REG_read(int a){
  
  Wire.beginTransmission(Addr);
  Wire.write(a);  // 進入 暫存器

  Wire.endTransmission();  // Stop I2C Transmission
  
  Wire.requestFrom(Addr, 1);

  if (Wire.available())
  {
    data = Wire.read();
  //  Serial.println(data);   //顯示暫存器的內部狀態
  }
 
  
}
