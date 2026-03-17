#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <TJpg_Decoder.h>
#include "esp_camera.h"
#include "FS.h"
#include "SD_MMC.h"

#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"
#define BOT_TOKEN "YOUR_BOT_TOKEN"
#define CHAT_ID "YOUR_CHAT_ID"

TFT_eSPI tft = TFT_eSPI();
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[240*10];
WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);
int photoCount = 0;

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p){
  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, area->x2-area->x1+1, area->y2-area->y1+1);
  tft.pushColors((uint16_t*)&color_p->full,(area->x2-area->x1+1)*(area->y2-area->y1+1),true);
  tft.endWrite();
  lv_disp_flush_ready(disp);
}

bool tft_output(int16_t x,int16_t y,uint16_t w,uint16_t h,uint16_t *bitmap){
  tft.pushImage(x,y,w,h,bitmap);
  return true;
}

void initCamera(){
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0; config.ledc_timer = LEDC_TIMER_0;
  config.pixel_format = PIXFORMAT_JPEG; config.frame_size = FRAMESIZE_QQVGA; config.jpeg_quality=12; config.fb_count=1;
  config.pin_d0=5; config.pin_d1=18; config.pin_d2=19; config.pin_d3=21;
  config.pin_d4=36; config.pin_d5=39; config.pin_d6=34; config.pin_d7=35;
  config.pin_xclk=0; config.pin_pclk=22; config.pin_vsync=25; config.pin_href=23;
  config.pin_sccb_sda=26; config.pin_sccb_scl=27; config.pin_pwdn=32; config.pin_reset=-1;
  esp_camera_init(&config);
}

void sendPhotoTelegram(String path){
  File photo = SD_MMC.open(path);
  if(photo){
    bot.sendPhotoByBinary(CHAT_ID, "image/jpeg", photo.size(), [](uint8_t *buf, size_t len){
      File f = SD_MMC.open("/temp.jpg");
      f.read(buf,len);
      f.close();
    });
    photo.close();
  }
}

void capturePhoto(lv_event_t *e){
  camera_fb_t *fb = esp_camera_fb_get();
  if(!fb) return;
  String path = "/photo"+String(photoCount++)+".jpg";
  File file = SD_MMC.open(path, FILE_WRITE);
  if(file){ file.write(fb->buf, fb->len); file.close(); }
  esp_camera_fb_return(fb);
  sendPhotoTelegram(path);
}

void setup(){
  Serial.begin(115200);
  tft.begin(); tft.setRotation(1);
  lv_init(); lv_disp_draw_buf_init(&draw_buf, buf, NULL, 240*10);
  static lv_disp_drv_t disp_drv; lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res=320; disp_drv.ver_res=240; disp_drv.flush_cb=my_disp_flush; disp_drv.draw_buf=&draw_buf;
  lv_disp_drv_register(&disp_drv);
  TJpgDec.setCallback(tft_output);
  initCamera();
  SD_MMC.begin();
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  while(WiFi.status()!=WL_CONNECTED){ delay(500); Serial.print("."); }
  client.setInsecure();
  lv_obj_t *btn=lv_btn_create(lv_scr_act()); lv_obj_center(btn); lv_obj_add_event_cb(btn,capturePhoto,LV_EVENT_CLICKED,NULL);
  lv_obj_t *label=lv_label_create(btn); lv_label_set_text(label,"Capture"); lv_obj_center(label);
}

void loop(){
  camera_fb_t *fb=esp_camera_fb_get();
  if(fb){ TJpgDec.drawJpg(0,0,fb->buf,fb->len); esp_camera_fb_return(fb); }
  lv_timer_handler();
  delay(30);
}s
