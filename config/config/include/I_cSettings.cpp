#include "I_cSettings.h" 


I_cSettings *gSettings = NULL;
 
I_cSettings::I_cSettings()
{
 rotSpeed_ = 0.3;
 rows_ = cols_ = 4;
 startx_ = -4.0;
 starty_ = 4.0;
 startz_ = -15.0;
 distance_ = 2.5;
}


I_cSettings::~I_cSettings()
{
}



void I_cSettings::LoadSettings(void)
{
 int len = 0;
 
 FILE *f = fopen("sett.bin","rb");
 string s;
 
 if (f == NULL)
	{
	 char path[256];
	 GetCurrentDirectory(256,path);
	 string currentDirectory = path;
	 return;
	}
    
 fseek (f, 0, SEEK_END);   // non-portable
 size_t size = ftell (f);
 uint8_t *buffer = new uint8_t[size];
 rewind(f);
 //// copy;
 fread(buffer,1,size,f);
 fclose(f); 
 
 
 rows_ = (int)buffer[len++];
 cols_ = (int)buffer[len++];
 len += this->decode_float(&buffer[len],&rotSpeed_);
 len += this->decode_float(&buffer[len],&startx_);
 len += this->decode_float(&buffer[len],&starty_);
 len += this->decode_float(&buffer[len],&startz_);
 len += this->decode_float(&buffer[len],&distance_);

 return;
}


void I_cSettings::SaveSettings(void)
{
 int len = 0;

 uint8_t buffer[512];
 FILE *f = fopen("sett.bin","wb");
 
 if (f == NULL)
    {
     MessageBox(NULL,"Unable to open settings file.","SNMP XML Builder",MB_OK);
     return;
    }

 buffer[len++] = rows_;
 buffer[len++] = cols_;
 len += this->encode_float(rotSpeed_,&buffer[len]);
 len += this->encode_float(startx_,&buffer[len]);
 len += this->encode_float(starty_,&buffer[len]);
 len += this->encode_float(startz_,&buffer[len]);
 len += this->encode_float(distance_,&buffer[len]);

 fwrite(buffer,1,len,f); 
    
 fclose(f);
}
 
 
         float rotSpeed_;
         int rows_,cols_;
         float startx_,starty_,startz_; 


int encode_Unsigned32(uint8_t *buffer,uint32_t value)
{
    buffer[0] = (uint8_t) ((value & 0xff000000) >> 24);
    buffer[1] = (uint8_t) ((value & 0x00ff0000) >> 16);
    buffer[2] = (uint8_t) ((value & 0x0000ff00) >> 8);
    buffer[3] = (uint8_t) (value & 0x000000ff);

    return 4;
}




int decode_Unsigned32(uint8_t *buffer ,uint32_t * value)
{
    if (value) {
        *value = ((uint32_t) ((((uint32_t) buffer[0]) << 24) & 0xff000000));
        *value |= ((uint32_t) ((((uint32_t) buffer[1]) << 16) & 0x00ff0000));
        *value |= ((uint32_t) ((((uint32_t) buffer[2]) << 8) & 0x0000ff00));
        *value |= ((uint32_t) (((uint32_t) buffer[3]) & 0x000000ff));
    }

    return 4;
}





int I_cSettings::decode_character_string(uint8_t *buffer, string *char_string)
{
 int len = 0;
 uint8_t str_len = buffer[len++];
 for (int c=0;c<str_len;c++)
     {
      char_string->push_back(buffer[len++]);
     }
 return len;
}



int I_cSettings::encode_character_string(uint8_t *buffer, string str)   
{
 int len = 0;
 buffer[len++] = (uint8_t)str.size();
 memcpy(&buffer[len],str.c_str(),str.size());
 return len + str.size();
}



/* from clause 20.2.6 Encoding of a Real Number Value */
/* returns the number of apdu bytes consumed */
int I_cSettings::encode_float(float value, uint8_t * apdu)
{
    union {
        uint8_t byte[4];
        float real_value;
    } my_data;

    /* NOTE: assumes the compiler stores float as IEEE-754 float */
    my_data.real_value = value;
#if BIG_ENDIAN
    apdu[0] = my_data.byte[0];
    apdu[1] = my_data.byte[1];
    apdu[2] = my_data.byte[2];
    apdu[3] = my_data.byte[3];
#else
    apdu[0] = my_data.byte[3];
    apdu[1] = my_data.byte[2];
    apdu[2] = my_data.byte[1];
    apdu[3] = my_data.byte[0];
#endif

    return 4;
}


/* from clause 20.2.6 Encoding of a Real Number Value */
/* returns the number of apdu bytes consumed */
int I_cSettings::decode_float(uint8_t * apdu, float *real_value)
{
    union {
        uint8_t byte[4];
        float real_value;
    } my_data;

    /* NOTE: assumes the compiler stores float as IEEE-754 float */
#if BIG_ENDIAN
    my_data.byte[0] = apdu[0];
    my_data.byte[1] = apdu[1];
    my_data.byte[2] = apdu[2];
    my_data.byte[3] = apdu[3];
#else
    my_data.byte[0] = apdu[3];
    my_data.byte[1] = apdu[2];
    my_data.byte[2] = apdu[1];
    my_data.byte[3] = apdu[0];
#endif

    *real_value = my_data.real_value;

    return 4;
}





void I_cSettings::SetRotSpeed(float rot_speed)
{
 rotSpeed_ = rot_speed;
}
float I_cSettings::GetRotSpeed(void)
{
 return rotSpeed_;
}
void I_cSettings::SetRowsCols(int rows, int cols)
{
 rows_ = rows;
 cols_ = cols;
}
int I_cSettings::GetCols(void)
{
 return cols_;
}
int I_cSettings::GetRows(void)
{
 return rows_;
}
void I_cSettings::SetStartxy(float x, float y)
{
 startx_ = x;
 starty_ = y;
}
float I_cSettings::GetStartx(void)
{
 return startx_;
}
float I_cSettings::GetStarty(void)
{
 return starty_;
}
void I_cSettings::SetStartz(float startz)
{
 startz_ = startz;
}
float I_cSettings::GetStartz(void)
{
 return startz_;
}


void I_cSettings::SetDistance(float dis)
{
 distance_ = dis;
}

float I_cSettings::GetDistance(void)
{
 return distance_;
}






     