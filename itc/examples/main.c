#include "../lib/Config/DEV_Config.h"
#include "example.h"
#include "../lib/GUI/GUI_BMPfile.h"

#include <math.h>

#include <stdlib.h>     //exit()
#include <signal.h>     //signal()

#define Enhance false

#define USE_Factory_Test false

#define USE_Normal_Demo true

#define USE_Touch_Panel false

UWORD VCOM = 1550;

IT8951_Dev_Info Dev_Info;
UWORD Panel_Width;
UWORD Panel_Height;
UDOUBLE Init_Target_Memory_Addr;

void  Handler(int signo){
    Debug("\r\nHandler:exit\r\n");
    if(Refresh_Frame_Buf != NULL){
        free(Refresh_Frame_Buf);
        Debug("free Refresh_Frame_Buf\r\n");
        Refresh_Frame_Buf = NULL;
    }
    if(Panel_Frame_Buf != NULL){
        free(Panel_Frame_Buf);
        Debug("free Panel_Frame_Buf\r\n");
        Panel_Frame_Buf = NULL;
    }
    if(Panel_Area_Frame_Buf != NULL){
        free(Panel_Area_Frame_Buf);
        Debug("free Panel_Area_Frame_Buf\r\n");
        Panel_Area_Frame_Buf = NULL;
    }
    if(bmp_src_buf != NULL){
        free(bmp_src_buf);
        Debug("free bmp_src_buf\r\n");
        bmp_src_buf = NULL;
    }
    if(bmp_dst_buf != NULL){
        free(bmp_dst_buf);
        Debug("free bmp_dst_buf\r\n");
        bmp_dst_buf = NULL;
    }
    Debug("Going to sleep\r\n");
    EPD_IT8951_Sleep();
    DEV_Module_Exit();
    exit(0);
}


int main(int argc, char *argv[])
{
    //Exception handling:ctrl + c
    signal(SIGINT, Handler);

    if (argc != 2){
        Debug("bleh\r\n");
        exit(1);
    }

    //Init the BCM2835 Device
    if(DEV_Module_Init()!=0){
        return -1;
    }

    double temp;
    // sscanf(argv[1],"%lf",&temp);
    VCOM = (UWORD)1550;
    Debug("VCOM value:%d\r\n", VCOM);
    Dev_Info = EPD_IT8951_Init(VCOM);

#if(Enhance)
    Debug("Attention! Enhanced driving ability, only used when the screen is blurred\r\n");
    Enhance_Driving_Capability();
#endif

    //get some important info from Dev_Info structure
    Panel_Width = Dev_Info.Panel_W;
    Panel_Height = Dev_Info.Panel_H;
    Init_Target_Memory_Addr = Dev_Info.Memory_Addr_L | (Dev_Info.Memory_Addr_H << 16);
    char* LUT_Version = (char*)Dev_Info.LUT_Version;
    if( strcmp(LUT_Version, "M641") == 0 ){
        //6inch e-Paper HAT(800,600), 6inch HD e-Paper HAT(1448,1072), 6inch HD touch e-Paper HAT(1448,1072)
        A2_Mode = 4;
        Four_Byte_Align = true;
    }else if( strcmp(LUT_Version, "M841_TFAB512") == 0 ){
        //Another firmware version for 6inch HD e-Paper HAT(1448,1072), 6inch HD touch e-Paper HAT(1448,1072)
        A2_Mode = 6;
        Four_Byte_Align = true;
    }else if( strcmp(LUT_Version, "M841") == 0 ){
        //9.7inch e-Paper HAT(1200,825)
        A2_Mode = 6;
    }else if( strcmp(LUT_Version, "M841_TFA2812") == 0 ){
        //7.8inch e-Paper HAT(1872,1404)
        A2_Mode = 6;
    }else if( strcmp(LUT_Version, "M841_TFA5210") == 0 ){
        //10.3inch e-Paper HAT(1872,1404)
        A2_Mode = 6;
    }else{
        //default set to 6 as A2 Mode
        A2_Mode = 6;
    }
    Debug("A2 Mode:%d\r\n", A2_Mode);


#if(USE_Factory_Test)
    Factory_Test_Only(Dev_Info, Init_Target_Memory_Addr);
#endif

#if(USE_Normal_Demo)
    //Show 16 grayscale
    // EPD_IT8951_Init_Refresh(Dev_Info, Init_Target_Memory_Addr);
    // Display_ColorPalette_Example(Panel_Width, Panel_Height, Init_Target_Memory_Addr);

    //Show some character and pattern
    // EPD_IT8951_Init_Refresh(Dev_Info, Init_Target_Memory_Addr);
    // Display_CharacterPattern_Example(Panel_Width, Panel_Height, Init_Target_Memory_Addr, BitsPerPixel_4);

    //Show a bmp file
    EPD_IT8951_Init_Refresh(Dev_Info, Init_Target_Memory_Addr);
    //1bp use A2 mode by default, before used it, refresh the screen with INIT_Mode
    // Display_BMP_Example(Panel_Width, Panel_Height, Init_Target_Memory_Addr, BitsPerPixel_1);
    // Display_BMP_Example(Panel_Width, Panel_Height, Init_Target_Memory_Addr, BitsPerPixel_2);
    Display_BMP_Example(Panel_Width, Panel_Height, Init_Target_Memory_Addr, BitsPerPixel_4, argv[1]);
    
    //Show A2 mode refresh effect
    // EPD_IT8951_Init_Refresh(Dev_Info, Init_Target_Memory_Addr);
    // Dynamic_Refresh_Example(Dev_Info,Init_Target_Memory_Addr);

    //Show how to display a gif, not works well on 6inch e-Paper HAT, 9.7inch e-Paper HAT, others work well
    // EPD_IT8951_Init_Refresh(Dev_Info, Init_Target_Memory_Addr);
    // Dynamic_GIF_Example(Panel_Width, Panel_Height, Init_Target_Memory_Addr);

    //Show how to test frame rate, test it individually,which is related to refresh area size and refresh mode
    // EPD_IT8951_Init_Refresh(Dev_Info, Init_Target_Memory_Addr);
    // Check_FrameRate_Example(800, 600, Init_Target_Memory_Addr, BitsPerPixel_1);
#endif
    
#if(USE_Touch_Panel)
    //show a simple demo for hand-painted tablet, only support for <6inch HD touch e-Paper> at present
    // EPD_IT8951_Init_Refresh(Dev_Info, Init_Target_Memory_Addr);
    // TouchPanel_ePaper_Example(Panel_Width, Panel_Height, Init_Target_Memory_Addr);
#endif

    //We recommended refresh the panel to white color before storing in the warehouse.
    // EPD_IT8951_Init_Refresh(Dev_Info, Init_Target_Memory_Addr);

    //EPD_IT8951_Standby();
    EPD_IT8951_Sleep();

    //In case RPI is transmitting image in no hold mode, which requires at most 10s
    DEV_Delay_ms(5000);

    DEV_Module_Exit();
    return 0;
}
