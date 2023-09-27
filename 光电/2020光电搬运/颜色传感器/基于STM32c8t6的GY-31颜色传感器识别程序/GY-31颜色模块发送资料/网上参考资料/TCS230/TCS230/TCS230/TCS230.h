/*

*/

#define F_POWERDOWN         0
#define F_100_2             1
#define F_100_20            2
#define F_100_100           3

#define PH_RED              0
#define PH_BLUE             1
#define PH_CLEAR            2
#define PH_GREEN            3

extern unsigned char FrequencyMode  ;
extern unsigned char PhotoDiodeMode ;
extern unsigned char Time1sCount    ;
extern unsigned int  TCSPlus_1s     ;
extern unsigned char Time_1sFlag    ;

void TCS230Inital(void);
void TimerInital(void);
unsigned char TCS230Mode(unsigned char FOutMode,unsigned char PhotoType);
//$
