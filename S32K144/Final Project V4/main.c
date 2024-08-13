/*******************************************************************************
															Inclusion 
 *******************************************************************************/
#include "main.h"

/*******************************************************************************
															Macro Denifition
 *******************************************************************************/
#define ID_LENGTH 5
#define UART                  LPUART1
/*******************************************************************************
															Typedef Denifition
 *******************************************************************************/
typedef struct {
    uint8_t ID[5];
    bool Role;
    char location[10];
    char itemName[20];
    char status;
} ID_system;

typedef enum {
	Slave,
	Master
} Role;

typedef enum {
	In,
	Out
} Status;

/*******************************************************************************
															Function Prototype
 *******************************************************************************/
void Init(void);
void PORT_conf(void);
bool CheckAvailableTag(void);
Role CheckRole(void);
int IsSlaveIDInSys(void);
void RegisterCard(void);
void DeleteCard(void);
void DeleteIDFromFlash(void);
void AddIDToFlash(void);
void sendData(ID_system ID);
bool IsMasterID(void);
void LoadID(void);
void LPUART1_RxTx_IRQHandler(void);
void PORTC_IRQHandler(void);
void SendPacket(char operation, ID_system id);

/*******************************************************************************
															Global Variables
 *******************************************************************************/
static uint8_t CardID[5];
static char szBuff[100];
static char szBuff2[100];


static volatile char location[20];
static volatile uint8_t quantity = 0;
static volatile uint8_t lastQuantity = 0;
static volatile uint16_t menu = 0;
static volatile uint16_t subMenu = 0;
static volatile int8_t prevSubMenu = -1;
//static volatile uint8_t check = 0;
static volatile uint8_t check1 = 0;

/************** Master card**************/
static	ID_system masterID = {
	.ID[0] = 0x54,
	.ID[1] = 0x76,
	.ID[2] = 0x3a,
	.ID[3] = 0x72,
	.ID[4] = 0x6a,
	.Role = Master
};
	
/************** Slave cards**************/
static ID_system slaveID[100];
static uint8_t flag = 0;


/*******************************************************************************
Main
 *******************************************************************************/
int main()
{
	srand(12345);
	int8_t counter = -1;
	Init();
	
	while(1) {
		if(menu == 0)
		{
			if(subMenu == 0) {
				if(prevSubMenu != 0) {
					lcd_clear();
					lcd_put_cur(0, 0);
					lcd_send_string("Swipe Item");
					prevSubMenu = 0;
					delay_ms(1000);
				}
				if(CheckAvailableTag()){
					if(!IsMasterID())
					{
						subMenu = 1;
					}
				}
				
				if(lastQuantity != quantity) {
					lcd_put_cur(1, 0);
					lcd_send_string("Quantity: ");
					lcd_send_num(quantity / 100 % 10);
					lcd_send_num(quantity / 10 % 10);
					lcd_send_num(quantity % 10);
					lastQuantity = quantity;
				}
			}
			else if(subMenu == 1)
			{
				/*************************************************************************** 
					 TODO: Check the Slave Card 
					 if Slave card is not in system => display "Card not found"
					 else display "Door Unlocked" then implement a 10s counterer to open the door
				****************************************************************************/
				if(flag == 0)
				{
					if(IsSlaveIDInSys() > -1)
					{
						lcd_clear();
						lcd_put_cur(0, 0);
						if((slaveID[IsSlaveIDInSys()].status) == 0)
						{
							lcd_send_string(slaveID[IsSlaveIDInSys()].itemName);
							lcd_send_string(" Import");
							slaveID[IsSlaveIDInSys()].status = 1;
						}
						else if((slaveID[IsSlaveIDInSys()].status) == 1){
							lcd_send_string(slaveID[IsSlaveIDInSys()].itemName);
							lcd_send_string(" Export");
							slaveID[IsSlaveIDInSys()].status = 0;
						}
						sendData(slaveID[IsSlaveIDInSys()]);
						counter = 2;
						flag = 1;
					}
					else if(IsSlaveIDInSys() == -1)
					{
						lcd_clear();
						lcd_put_cur(0, 0);
						lcd_send_string("Item Not Found   ");
						flag = 2;
						counter = 2;
					}
				}
				else if(flag != 0)
				{
					if(flag == 1) {
						lcd_put_cur(1, 0);
						lcd_send_string(slaveID[IsSlaveIDInSys()].location);
						lcd_put_cur(1, 11);
						lcd_send_num((uint8_t)counter);
					}
					else if(flag == 2)
					{
						lcd_put_cur(1, 0);
						lcd_send_string("PLS Register");
					}
					counter--;
					if(counter == 0)
					{
						counter = -1;
						prevSubMenu = -1;
						subMenu = 0;
						flag = 0;
					}
					delay_ms(1000);
				}
			}
		}
		else if(menu == 1)
		{
			/*************************************************************************** 
				TODO:
				 Waiting for Card swiped
				 if Card is master Card, move to next session
				 if Card is not already registered, Add it into system
				 if Card is Slave Card, display "Card registered"
			***************************************************************************/
			if(subMenu == 0) {
				if(prevSubMenu != 0) {
					lcd_clear();
					lcd_put_cur(0, 0);
					lcd_send_string("Add New Item");
					lcd_put_cur(1, 0);
					lcd_send_string("Waiting");
					prevSubMenu = 0;
					delay_ms(1000);
				}
				if(CheckAvailableTag()){
					if(!IsMasterID())
					{
						subMenu = 1;
					}
				}
			}
			else if (subMenu == 1)
			{
				if(flag == 0)
				{
					if(IsSlaveIDInSys() > -1)
					{
						lcd_clear();
						lcd_put_cur(0, 0);
						lcd_send_string("Item Available");
						flag = 1;
					}
					else if (IsSlaveIDInSys() == -1)
					{
						if(prevSubMenu != 1) {
							lcd_clear();
							lcd_put_cur(0, 0);
							lcd_send_string("BTN1: KHO 1");
							lcd_put_cur(1, 0);
							lcd_send_string("BTN2: KHO 2");
							prevSubMenu = 1;
						}
						if(check1 == 1)
						{
							RegisterCard();
							flag = 1;
							lcd_clear();
							check1 = 0;
							prevSubMenu = -1;
						}
					}
				}
				if(flag == 1)
				{
					/* Wait 3s to return first menu*/
					delay_ms(3000);
					subMenu = 0;
					flag = 0;
					lcd_clear();
					lcd_send_num(2);
				}
			}
		}
		else if(menu == 2)
		{
			/****************************************************************************  
				TODO:
				 Waiting for Card swiped
				 if Card is master Card, move to next session
				 if Card is not already registered, display "not registered"
				 if Card is Slave Card, delete it
			****************************************************************************/
			if(subMenu == 0) {
				if(prevSubMenu != 0) {
					lcd_clear();
					lcd_put_cur(0, 0);
					lcd_send_string("Delete Card");
					lcd_put_cur(1, 0);
					lcd_send_string("Waiting");
					prevSubMenu = 0;
					flag = 0;
					delay_ms(1000);
				}
				if(CheckAvailableTag()){
					if(!IsMasterID())
					{
						subMenu = 1;
					}
				}
			}
			else if (subMenu == 1)
			{
				if(flag == 0)
				{
					if(IsSlaveIDInSys() > -1)
					{
						DeleteCard();
						lcd_clear();
						lcd_put_cur(0, 0);
						lcd_send_string("Card Deleted");
						lcd_put_cur(1, 0);
						lcd_send_string("succesfully");
						flag = 1;
					}
					else if (IsSlaveIDInSys() == -1)
					{
						lcd_clear();
						lcd_put_cur(0, 0);
						lcd_send_string("Card not");
						lcd_put_cur(1, 0);
						lcd_send_string("registered");
						flag = 1;
					}
				}
				if(flag == 1)
				{
					/* Wait 3s to return first menu */
					delay_ms(3000);
					subMenu = 0;
					prevSubMenu = -1;
					flag = 0;
				}
			}
		}
	}
}

void sendData(ID_system ID) {
    sprintf(szBuff2, "%02X%02X%02X%02X%02X|%s|%s|%d\n", 
            ID.ID[0], ID.ID[1], ID.ID[2], ID.ID[3], ID.ID[4],
            ID.itemName, ID.location, ID.status);
    LPUARTx_SendString(UART, szBuff2);
}

void LPUART1_RxTx_IRQHandler(void) {
    static char buffer[100];
    static uint8_t bufferIndex = 0;

    if ((LPUART1->STAT & LPUART_STAT_RDRF_MASK) >> 21u) {
        char d = (uint8_t)LPUART1->DATA;

        if (d == '\n') {
            buffer[bufferIndex] = '\0';
            if (strncmp(buffer, "s|", 2) == 0 && strstr(buffer, "|e") != NULL) {
                char id[11];
                char itemName[21];
                char place[11];
                char status[4];

                if (sscanf(buffer, "s|%10[^|]|%20[^|]|%10[^|]|%3[^|]|e", id, itemName, place, status) == 4) {
                    if (quantity < sizeof(slaveID) / sizeof(slaveID[0])) {
                        // Convert hex string to bytes
                        for (int i = 0; i < 5; i++) {
                            sscanf(&id[i*2], "%2hhx", &slaveID[quantity].ID[i]);
                        }
                        sprintf(szBuff, "%02X%02X%02X%02X%02X", slaveID[quantity].ID[0], slaveID[quantity].ID[1], slaveID[quantity].ID[2], slaveID[quantity].ID[3], slaveID[quantity].ID[4]);
                        
                        strncpy(slaveID[quantity].itemName, itemName, sizeof(slaveID[quantity].itemName) - 1);
                        slaveID[quantity].itemName[sizeof(slaveID[quantity].itemName) - 1] = '\0';
                        
                        strncpy(slaveID[quantity].location, place, sizeof(slaveID[quantity].location) - 1);
                        slaveID[quantity].location[sizeof(slaveID[quantity].location) - 1] = '\0';
                        
                        slaveID[quantity].status = (strcmp(status, "in") == 0) ? In : Out;
                        slaveID[quantity].Role = Slave;
                        lastQuantity = quantity;
                        quantity++;
                    }
                }
            } else if (strcmp(buffer, "eom") == 0) {
                // Handle end of message
            }
            bufferIndex = 0;
        } else if (bufferIndex < sizeof(buffer) - 1) {
            buffer[bufferIndex++] = d;
        }
    }    
}

void PORTC_IRQHandler(void)
{
	if(PORTC->PORT_PCRn[12] & (1 << 24))
	{
		strcpy(location, "kho1");
		check1 = 1;
		PORTC->PORT_PCRn[12] |= (1 << 24);
	}
	
	if(PORTC->PORT_PCRn[13] & (1 << 24))
	{
		strcpy(location, "kho2");
		check1 = 1;
		PORTC->PORT_PCRn[13] |= (1 << 24);
	}
}

void Init(void) {
	/* Clock configuration */
	SOSC_Init();
	SPLL_160Mhz_init();
	NormalRUNmode_80MHz();
	initSysTick();
	
	/* Port Init */
	PORT_conf();
	
	/* Uart Init */
	LPUART_init(LPUART1, 9600, CLOCK_SOSC);

	/* SPI Init */
	TM_SPI_Init();
	
	/* LPI2C Init */
	LPI2C0_clock();
	LPI2C0_init();
	LPUART_init(LPUART1, 9600, CLOCK_SOSC);
	
	/*Module RC522 init*/
	TM_MFRC522_Init();
	
	/*LCD1602 init*/
	lcd_init();
	lcd_put_cur(0,0);

	lcd_send_string("Loading...");
	for(int i = 0; i < 5;  i++){
		lcd_send_data('.');
		delay_ms(500);
	}
	lcd_clear();
		LoadID();
}

/*******************************************************************************
@Function Name : PORT_conf
 *******************************************************************************/
void PORT_conf(void)
{
	// Peripheral Clock Controller
	PCC->PCCn[PCC_PORTA_INDEX] |= ENABLE_PCC;
	PCC->PCCn[PCC_PORTB_INDEX] |= ENABLE_PCC;
	PCC->PCCn[PCC_PORTC_INDEX] |= ENABLE_PCC;
	PCC->PCCn[PCC_PORTD_INDEX] |= ENABLE_PCC;

	Gpio_ConfigType gpioConf;
	gpioConf.portBase = PORTC;
	gpioConf.gpioBase = GPIOC;
	gpioConf.GPIO_PinMode = INPUT;
	gpioConf.GPIO_PinNumber = PIN12;
	gpioConf.muxMode = GPIO;
	Gpio_Init(&gpioConf);
	
	PORTC->PORT_PCRn[PIN12] |= (9 << 16);
	
	gpioConf.GPIO_PinNumber = PIN13;
	gpioConf.muxMode = GPIO;
	Gpio_Init(&gpioConf);
	
	PORTC->PORT_PCRn[PIN13] |= (9 << 16);
	
	/*I2C Pin configurate**********************/

	gpioConf.portBase = PORTA;
	gpioConf.gpioBase = GPIOA;
	gpioConf.GPIO_PinMode = NONE;
	gpioConf.GPIO_PinNumber = PIN2;
	gpioConf.muxMode = MUXALT3;
	Gpio_Init(&gpioConf);
	
	gpioConf.GPIO_PinNumber = PIN3;
	Gpio_Init(&gpioConf);

	
	/*SPI Pin configurate**********************/
	gpioConf.portBase = PORTB;
	gpioConf.gpioBase = GPIOB;
	gpioConf.GPIO_PinMode = OUTPUT;
	gpioConf.GPIO_PinNumber = PIN0; // PCS
	gpioConf.muxMode = GPIO;
	Gpio_Init(&gpioConf);
	GPIO_SetOutputPin(GPIOB, PIN0);
	
	gpioConf.GPIO_PinMode = NONE;
	gpioConf.muxMode = 3;
	gpioConf.GPIO_PinNumber = PIN1; // MOSI
	Gpio_Init(&gpioConf);
	
	gpioConf.GPIO_PinNumber = PIN2; // SCK
	Gpio_Init(&gpioConf);
	
	gpioConf.GPIO_PinNumber = PIN3; // MISO
	Gpio_Init(&gpioConf);
	NVIC_EnableInterrupt(PORTC_IRQn);
	
	// UART PIN Configuration
	gpioConf.portBase = PORTD;
	gpioConf.gpioBase = GPIOD;
	gpioConf.GPIO_PinNumber = 13; // RX
	gpioConf.muxMode = 3;
	gpioConf.GPIO_PinMode = NONE;
	Gpio_Init(&gpioConf);
	
	gpioConf.GPIO_PinNumber = 14; // TX
	gpioConf.muxMode = 3;
	gpioConf.GPIO_PinMode = NONE;
	Gpio_Init(&gpioConf);
}

/*******************************************************************************
@Function Name : CheckAvailableTag
 *******************************************************************************/
bool CheckAvailableTag(void) {
	bool check = 0;
	if (TM_MFRC522_Check(CardID) == MI_OK) {
		sprintf(szBuff, "%02X%02X%02X%02X%02X", CardID[0], CardID[1], CardID[2], CardID[3], CardID[4]);
		check = 1;
		
		if(CheckRole() == Master) {
			if(menu < 2) 
			{
				menu += 1;
			}
			else if (menu >=2)
			{
				menu = 0;
			}
			subMenu = 0;
			prevSubMenu = -1;
		}
	}
	return check;
}

/*******************************************************************************
@Function Name : CheckRole
@Return        : Slave, Master
 *******************************************************************************/
Role CheckRole(void) {
	Role role = Slave;
	for(int i = 0; i < 5; i++)
	{
		if(i == 4 && (CardID[4] == masterID.ID[4]))
		{
			role = Master;
		}
	}
	return role;
}

/*******************************************************************************
@FunctionName : IsSlaveIDInSys
@Return       : 0: not in System
				        1: is in System 
 *******************************************************************************/
int IsSlaveIDInSys(void) 
{
	int index = -1;
	for (int i = 0; i < quantity; i++) 
	{
		if (memcmp(CardID, slaveID[i].ID, ID_LENGTH) == 0) 
		{
			index = i;
			break;
		}
	}
	
	return index;
}

/*******************************************************************************
@FunctionName : IsMasterID
@Return       : 0: not master Card
				        1: is master Card
 *******************************************************************************/
bool IsMasterID(void) 
{
	bool isMaster = false;

	for (int i = 0; i < 5; i++) 
	{
		if((CardID[i] == masterID.ID[i]) && i == 4)
		{
			isMaster = true;
		}
	}
	
	return isMaster;
}

/*******************************************************************************
@FunctionName : RegisterCard
 *******************************************************************************/
void RegisterCard(void)
{

    for(int i = 0; i < 5; i++)
    {
        slaveID[quantity].ID[i] = CardID[i];
    }
    slaveID[quantity].Role = Slave;
    strcpy(slaveID[quantity].location, location);

    unsigned short randomNumber = rand() % 255;
    sprintf(slaveID[quantity].itemName, "Item%d", randomNumber);  // Generate a random item name
    slaveID[quantity].status = In;

    quantity++;
    SendPacket('s', slaveID[quantity - 1]);
}

/*******************************************************************************
@FunctionName : DeleteCard
 *******************************************************************************/
void DeleteCard(void)
{
     for (int i = 0; i < quantity; i++)
    {
        if (memcmp(CardID, slaveID[i].ID, ID_LENGTH) == 0)
        {
            // Found the card to delete
            // Move all subsequent elements one position back
            for (int j = i; j < quantity - 1; j++)
            {
                    memcpy(&slaveID[j], &slaveID[j+1], sizeof(ID_system));
            }
            
            // Decrease the quantity
            quantity--;
            // Send delete packet
            SendPacket('d', slaveID[i]);
            // Clear the last element (optional, but can help prevent potential issues)
            memset(&slaveID[quantity], 0, sizeof(ID_system));
            

            break; // Exit the loop once we've deleted the card
        }
    }
}

/*******************************************************************************
@FunctionName : SendPacket
@
 *******************************************************************************/
void SendPacket(char operation, ID_system id) {
    char packet[100];  // Buffer size adjusted for maximum expected length

    if (operation == 's') {
        // Construct the packet for sending card data
        sprintf(packet, "%c|%02X%02X%02X%02X%02X|%s|%s|%d|e\n", 
                operation, 
                id.ID[0], id.ID[1], id.ID[2], id.ID[3], id.ID[4], 
                id.itemName,
                id.location, 
                id.status);
    } else if (operation == 'd') {
        // Construct the packet for deleting a card
        sprintf(packet, "%c|%02X%02X%02X%02X%02X|e\n", 
                operation, 
                id.ID[0], id.ID[1], id.ID[2], id.ID[3], id.ID[4]);
    }

    // Send the constructed packet via UART
    LPUARTx_SendString(UART, packet);
}


/*******************************************************************************
@FunctionName : LoadID
 *******************************************************************************/
// Modify the LoadID function
void LoadID(void) {
    // Clear existing slaveIDs
    memset(slaveID, 0, sizeof(slaveID));
    quantity = 0;

    // Send the "Reload" command to ESP32
    LPUARTx_SendString(LPUART1, "Reload\n");
}




