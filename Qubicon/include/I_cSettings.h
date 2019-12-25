#pragma once
#include <sdl.h>
#include <stdafx.h>
#include <string>


using namespace std;

class I_cSettings
{
 public:
        I_cSettings();
       ~I_cSettings();
       
       
        void LoadSettings(void);
        void SaveSettings(void);

 public:
        void SetRotSpeed(float rot_speed);
        float GetRotSpeed(void);
        void SetRowsCols(int rows, int cols);
        void SetRows(int row);
        int GetCols(void);
        int GetRows(void);       
        void SetStartxy(float x, float y);
        float GetStartx(void);
        float GetStarty(void);
        void SetStartz(float startz);
        float GetStartz(void);
        void SetDistance(float dis);
        float GetDistance(void);


 private:
         float rotSpeed_;
         int rows_,cols_;
         float startx_,starty_,startz_;
         float distance_;
         
 private:
         int decode_character_string(uint8_t *buffer, string *char_string);
         int encode_character_string(uint8_t *buffer, string str);
		 int encode_Unsigned32(uint8_t *buffer,uint32_t value);
		 int decode_Unsigned32(uint8_t *buffer ,uint32_t * value);      
		 int encode_float(float value, uint8_t * apdu);
		 int decode_float(uint8_t * apdu, float *real_value);

       
};


extern I_cSettings *gSettings;