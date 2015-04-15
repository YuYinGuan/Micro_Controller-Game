/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <device.h>
#define Blue 1
#define myColor 1
#define Red 2
#define Nothing 0


/*variables used in program*/
uint8 opponID = 0x85;
uint8 ID = 0x12;
uint32 DelayTime = 2;
uint32 GRow = 8;
uint32 arrayLED[8][8];
uint8  setButton = 0;
uint8  currentSpot = 1;
uint8  setSpot = 0;
uint16 CSpot;
int8    selecting = 7;
uint8   setLocation;
uint8   Horizontal[8];
uint8   Vertical[8];
uint8   Flashing = 0;
uint8   Winner = 0;
uint8   twist = 0;
uint8   z =0;
uint8   flag;
uint8   home = 1;
uint8   playerTurn;
uint8   checkSum;
uint8   GT = 0;
uint8 Senting[13];
uint8 Received[13];



/*interrupt to flash after win*/
CY_ISR(fl) 
{
    /*if winning spot is lit, turn it off*/
    if(twist == 0){
        for(z=0; z<4; z++){
            arrayLED[Vertical[z]][Horizontal[z]] = Nothing;
        }
        twist = 1;
    }else{
        /*if winning spot is off, turn it on*/
        for(z=0; z<4; z++){
            arrayLED[Vertical[z]][Horizontal[z]] = Winner;
        }
        twist = 0;
    }
    /* # the flashes = Flashing/2*/
    Flashing++;
    Timer_ReadStatusRegister(); 
}


/*sleep timer interrupt for when the dics is dropping down*/
CY_ISR(sleep) 
{ 
    /* if the next LED on the panel is not taken, keep dropping*/
    if((selecting>0) && (arrayLED[selecting-1][setLocation] == Nothing)){
        arrayLED[selecting-1][setLocation] = arrayLED[selecting][setLocation];
        arrayLED[selecting][setLocation] = Nothing;
        selecting --;
    }else{
        setSpot = 1;
    }
    SleepTimer_GetStatus(); 
} 

/* resets the all the arrays to nothing*/
void resetArray(){
    uint8 h, t;
    for(h=0; h<8; h++){
        for(t=0; t<8; t++){
            arrayLED[h][t] = Nothing;
        }
    }
    for(h=0; h<4; h++){
        Horizontal[h] = Nothing;
        Vertical[h] = Nothing;
    }
}

/*prepares the reds on the next row to be displayed by ring counter*/ 
void PrepNextRowRed(){
    int8 i;
    for(i = 7; i>=0; i--){
        if(arrayLED[GRow][i]==Red){
            SER_Red_Write(0);
        }else{
            SER_Red_Write(1);
        }
        Control_Reg_Red_Write(1);
        Control_Reg_Red_Write(0);
    }
}

/*prepares the Blue on the next row to be displayed by ring counter*/
void PrepNextRowBlue(){
    int8 i;
    for(i = 7; i>=0; i--){
        if(arrayLED[GRow][i]==Blue){
            SER_Blue_Write(0);
        }else{
            SER_Blue_Write(1);
        }
        Control_Reg_Blue_Write(1);
        Control_Reg_Blue_Write(0);
    }
}

/*prints out the prepared Red and Blue LEDs*/
void DisplayDots(){
    Control_Reg_Red_Write(2);
    Control_Reg_Red_Write(0);
    Control_Reg_Blue_Write(2);
    Control_Reg_Blue_Write(0);
}

/*setting pins of given color to given row and column*/
void settingPin(int color, int row, int column){
    if(arrayLED[row-1][column-1] == Nothing){
        arrayLED[row-1][column-1] = color;
    }
}

/*renews the ring counter value from row 8 to 1*/
void checkRing(){
    if(GRow == 8){
            SER_Write(1);
            GRow = 0;
    }
}

/*ring counter which counts once each time called*/
void Control_Ring(){
    /*renew GRow and SER for ring counter for a new loop*/
    checkRing();
    /*clock in the next red and blue values*/
    PrepNextRowRed();
    PrepNextRowBlue();
    /*preparing row ring counter*/
    Control_Reg_Write(1);
    CyDelay(DelayTime/2);
    /*latches the value*/
    DisplayDots();
    /*hit the next row*/
    Control_Reg_Write(2);
    CyDelay(DelayTime/2);
    
    /*make ser 0 when its 1 so its high only once*/
    if(SER_Read() == 1){
        SER_Write(0);
    }
    /*count*/
    GRow++;
}

/*sets the values that are senting every halve a second*/
void setPacket(uint8 setID, uint8 setRow, uint8 setColumn){
    checkSum = 0;
    Senting[0] = 0x7E;
    Senting[1] = 0x00;
    Senting[2] = 0x09;
    Senting[3] = 0x01;
    Senting[4] = 0x00;
    Senting[5] = 0xFF;
    Senting[6] = 0xFF;
    Senting[7] = 0x01;  
    Senting[8] = setID;
    Senting[9] = 0x00;
    Senting[10] = setRow;
    Senting[11] = setColumn;
    uint8 i;
    /*do the checksum*/
    for(i=3; i<12; i++){
        checkSum += Senting[i]; 
        Control_Ring();
    }
    Senting[12] = 0xFF - checkSum;
}

/*checks the move that the enemy is senting*/
void receivePacket(){
    uint8 i, R;
    uint8 E = 1;
    checkSum = 0;
    /*if there is still stuff in buffer*/
    while(UART_GetRxBufferSize()!=0 && E==1){
        /*check for the starting of packet*/
        R = UART_GetChar();
        if(R == 0x7E){
            Received[0] = R;
            /*continue to receive the reset of packet until the end*/
            for(i = 1; i<13; i++){
                /*if the reset of the packet is not here yet, wait for it*/
                while(UART_GetRxBufferSize()==0){
                /*while waiting, keep refreshing*/
                Control_Ring();
                }
                Received[i] = UART_GetChar();
                Control_Ring();
                }
            E = 0;    
            }
            Control_Ring();
        }
    /*check if file is corrupted*/    
    for(i=3; i<12; i++){
        checkSum += Received[i]; 
        Control_Ring();
    }
    /*check for correct parameters*/
    if((Received[12] == 0xFF - checkSum)&&((Received[11]<=8)&&(Received[11]>0))&&((Received[10]<8)&&(Received[10]>0))&&(opponID==Received[8])){
        GT = 1;
        Control_Ring();
    }
}

/*check the homerow value*/
void ChangeHome(uint8 x){
    uint8 t;
    for(t=0; t<8; t++){
        arrayLED[7][t] = Nothing;
    }
    settingPin(myColor, 8, x);
}

/*make change of the home row if the senser is moved and at a new spot*/
void selectSpot(spot){
    /*the values was gotten from have FFFF/8, but the range was limited to halve
        so I divided my limite by have. So my values was gotten from experimentation*/
    if((1<=spot) && (spot <31/2.5) && (currentSpot != 1)){
        ChangeHome(1);
        currentSpot = 1;
    }
    if((31/2.5 <= spot) && (spot < 63/2.5) && (currentSpot != 2)){
        ChangeHome(2);
        currentSpot = 2;
    }
    if((63/2.5 <= spot) && (spot < 95/2.5) && (currentSpot != 3)){
        ChangeHome(3);
        currentSpot = 3;
    }
    if((95/2.5 <= spot) && (spot < 127/2.5) && (currentSpot != 4)){
        ChangeHome(4);
        currentSpot = 4;
    }
    if((127/2.5 <= spot) && (spot < 159/2.5) && (currentSpot != 5)){
        ChangeHome(5);
        currentSpot = 5;
    }
    if((159/2.5 <= spot) && (spot < 191/2.5) && (currentSpot != 6)){
        ChangeHome(6);
        currentSpot = 6;
    }
    if((191/2.5 <= spot) && (spot < 223/2.5) && (currentSpot != 7)){
        ChangeHome(7);
        currentSpot = 7;
    }
    if((223/2.5 <= spot) && (spot < 255/2.5) && (currentSpot != 8)){
        ChangeHome(8);
        currentSpot = 8;
    }
}

/*I put my values to show on the led here for testing*/
void test(){
    int8 t;
    for(t=1; t<=8;t++){
        settingPin(Blue, 2, t);
        settingPin(Red, 6, t);
    }
}

/*check if the given color have won the game*/
uint8 checkVictory(int8 color, int8 S, int8 L){
    uint8 f, t, v, h, n, d1, d2;
    v = h = f = 0;
    d2 = 1;
    
    /*horizontal check*/
    for(t = 0; t<8; t++){
        if(arrayLED[S][t] == color){
            Horizontal[f] = t;
            Vertical[f] = S;
            f++;
            h++;
        }else{
            h =0;
            f=0;
        }
        if(h>=4){
            Winner = color;
            return 1;
        }
    }
    /*vertical check*/
    f = 0;
    for(t = 0; t<7; t++){
        if(arrayLED[t][L] == color){
            Horizontal[f] = L;
            Vertical[f] = t;
            f++;
            v++;
        }else{
            f=0;
            v =0;
        }
        if(v>=4){
            Winner = color;
            return 1;
        }
    }
    
    /*diagonal / check*/
    f = 0;
    d1 = 1;
    n = 1;
    Horizontal[f] = L;
    Vertical[f] = S;
    f++;
    while(((S-n)>=0) && ((L-n)>=0)){
        if(arrayLED[S-n][L-n] == color){
            Horizontal[f] = L-n;
            Vertical[f] = S-n;
            f++;
            d1++;
        }else{
            break;
        }
        n++;
    }
    n=1;
    while(((S+n)<7) && ((L+n)<8)){
        if(arrayLED[S+n][L+n] == color){
            Horizontal[f] = L+n;
            Vertical[f] = S+n; 
            f++;
            d1++;
        }else{
            break;
        }
        n++;
    }
    if(d1>=4){
        Winner = color;
        return 1;
    }
    /*diagonal \ check*/
    f = 0;
    Horizontal[f] = L;
    Vertical[f] = S;
    f++;
    d2 = 1;
    n = 1;
    while(((S+n)<7) && ((L-n)>=0)){
        if(arrayLED[S+n][L-n] == color){
            Horizontal[f] = L-n;
            Vertical[f] = S+n; 
            f++;
            d2++;
        }else{
            break;
        }
        n++;
    }
    n=1;
    while(((S-n)>=0) && ((L+n)<8)){
        if(arrayLED[S-n][L+n] == color){
            Horizontal[f] = L+n;
            Vertical[f] = S-n; 
            f++;        
            d2++;
        }else{
            break;
        }
        n++;
    }
    if(d2>=4){
        Winner = color;    
        return 1;
    }
    return 0;
}

/*set up happy face on greeting page*/
void happyFace(){
    settingPin(Red, 5, 2);
    settingPin(Red, 5, 3);
    settingPin(Red, 5, 6);
    settingPin(Red, 5, 7);
    settingPin(Red, 6, 2);
    settingPin(Red, 6, 3);
    settingPin(Red, 6, 6);
    settingPin(Red, 6, 7);
    settingPin(Red, 7, 2);
    settingPin(Red, 7, 3);
    settingPin(Red, 7, 6);
    settingPin(Red, 7, 7);
    settingPin(Blue, 3, 2);
    settingPin(Blue, 3, 7);
    settingPin(Blue, 2, 6);
    settingPin(Blue, 2, 5);
    settingPin(Blue, 2, 4);
    settingPin(Blue, 2, 3);    
}

/*interrupt to sent a already set packet to xbee*/
CY_ISR(st) 
{
    UART_PutArray(Senting, 13);
    Timer_Sent_ReadStatusRegister(); 
}

void main()
{
    /*initialization/startup code here*/
    uint8 y;
    resetArray();
    CapSense_CSD_Start();
    LCD_Start();
    UART_Start();
    
    /*set up the isr*/
    CYGlobalIntDisable; 
    isr_sleep_Start(); 
    isr_sleep_SetVector(sleep);
    isr_flash_Start(); 
    isr_flash_SetVector(fl); 
    isr_Sent_Start(); 
    isr_Sent_SetVector(st);
    CYGlobalIntEnable;
    
    /* Initialize baselines */ 
    CapSense_CSD_InitializeAllBaselines();
    /*set the clear and output signal for transistor*/
    OE_Write(0);
    SRCLR_Write(1);
    
    /*initialize array for xbee*/
    for(y=0; y<13; y++){
        Received[y]=0;
        Senting[y] = 0;
    }
    
    /*set up xbee*/
    CyDelay(3000);
    UART_PutString("+++");
    CyDelay(2000);
    UART_PutString("ATAP1\r");
    UART_PutString("ATCH F\r");    
    UART_PutString("ATWR\r");
    UART_PutString("ATCN\r");
    
    /*Print choice of starting order*/
    LCD_Position(0,0);
    LCD_PrintString("Left: I am 1st");
    LCD_Position(1,0);
    LCD_PrintString("Right: I am 2nd");
    
            Timer_Sent_Start();
    /*program*/
    for(;;)
    {
        /*greeting page*/
        while(home == 1){
        /*update senser values*/
            CapSense_CSD_UpdateEnabledBaselines();
    	    CapSense_CSD_ScanEnabledWidgets();
            happyFace();
            /*when capsense not touched, just fresh leds*/
            while(CapSense_CSD_IsBusy() != 0){
                Control_Ring();
            }
            /*if button 0 is pressed, the player one is set to go first*/
            if (CapSense_CSD_CheckIsWidgetActive(CapSense_CSD_BUTTON0__BTN)){ 
                playerTurn = 1;
                home = 0;
                resetArray();
                CyDelay(500);
            }
            /*if button 1 is pressed, the player two is set to go first*/
            if (CapSense_CSD_CheckIsWidgetActive(CapSense_CSD_BUTTON1__BTN)){
                playerTurn = 2;
                home = 0;
                resetArray();
                CyDelay(500);
            }
            Control_Ring();
        }
        /*set the senser back to 0*/
        CapSense_CSD_InitializeAllBaselines();  
        
        /*if it is player 1's turn*/
        if(playerTurn == 1){
            /*set the inital spot for homerow*/
            ChangeHome(currentSpot);
            Control_Ring();
            
            /*set up printing of position on LCD*/
            LCD_ClearDisplay();
            LCD_Position(0,0);
            LCD_PrintString("Position:");
            
            /*choosing where to place disc*/
            while(setButton==0){
                /*update data*/
                CapSense_CSD_UpdateEnabledBaselines();
    	        CapSense_CSD_ScanEnabledWidgets();
                
                /*print current spot to LCD*/
                LCD_Position(0,9);
                LCD_PrintInt8(currentSpot);
                /* Wait for scanning to complete */
		        while(CapSense_CSD_IsBusy() != 0){
                Control_Ring();
                }
            
                /*check if button pushed*/
                if (CapSense_CSD_CheckIsWidgetActive(CapSense_CSD_BUTTON0__BTN)){ 
                    setButton = 1;
                }
                if (CapSense_CSD_CheckIsWidgetActive(CapSense_CSD_BUTTON1__BTN)){
                    setButton = 1;
                }
            
                /* adjust position */
                CSpot = CapSense_CSD_GetCentroidPos(CapSense_CSD_LINEARSLIDER0__LS);
            
                /*if not error change spot*/
                if(CSpot!= 0xFFFF){
                    selectSpot(CSpot);
                }
            
                Control_Ring();
            }
    
            CapSense_CSD_InitializeAllBaselines();  
        
            /*checks what spot play selected to drop disc*/
            for(y=0; y<8; y++){
                if(arrayLED[7][y] != Nothing){
                    setLocation = y;
                }
                Control_Ring();
            }
            

            /*start timer for droping th disc*/
            SleepTimer_Start();
            SleepTimer_Init();
            
            /*wait dropping the disc*/
            while(setSpot == 0){
                Control_Ring();
            }
            
            /*stop timer so it does not interrupt when dropping*/
            SleepTimer_Stop();
            
            
            setPacket(ID, selecting, setLocation);//Set packet ****************************************/
            
            /*check if Blue won after their move*/
            if(checkVictory(Blue, selecting, setLocation)){
                /*start timer for interrupt flashes*/
                Timer_Start();
                Timer_Init();
                /*flash for 5 times*/
                while(Flashing <10){
                    Control_Ring();
                }
                /*stop the timer to stop flashes*/
                Timer_Stop();
                CyDelay(1000);
                resetArray();
                home = 1;
            }
            
            playerTurn =2;
        }else{
            LCD_ClearDisplay();
            LCD_Position(0,0);
            LCD_PrintString("Turn: Red");
            LCD_Position(1,0);
            LCD_PrintString("Waiting...");
            GT = 0;
            while(GT == 0){
                receivePacket();
                if((arrayLED[Received[10]-1][Received[11]-1] != Nothing)){
                    GT = 0;
                }
                Control_Ring();
            }
            setLocation = Received[11]-1;
            settingPin(Red, 8, Received[11]); 
            SleepTimer_Start();
            SleepTimer_Init();
            
            /*wait dropping the disc*/
            while(setSpot == 0){
                Control_Ring();
            }
            
            /*stop timer so it does not interrupt when dropping*/
            SleepTimer_Stop();
            
            if(checkVictory(Red, selecting, setLocation)){
                /*start timer for interrupt flashes*/
                Timer_Start();
                Timer_Init();
                while(Flashing <10){
                    Control_Ring();
                }
                /*stop the timer to stop flashes*/
                Timer_Stop();
                CyDelay(1000);
                resetArray();
                home = 1;
            }
            playerTurn = 1;
        }
        
        /*resets value for next turn*/
        z =0;
        Winner = 0;
        twist = 0;
        Flashing =0;
        selecting = 7;
        setSpot = 0;
        setButton = 0;
    }
}

/* [] END OF FILE */
