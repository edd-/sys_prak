#ifndef SharedVariables
#define SharedVariables
/* Alle Variablen und Funktionen die zwischen den einzelnen Modulen geteilt werden */
#define MAXGAMEID 42
#define MAXGAMENAME 50
#define MAXPLAYERNAME 50
#define KEY 5678

typedef struct config_struct {
	char hostname[100];
	char gamekindname[20];
	char version[5];
	char playernumber[5];
	int portnumber;
} config_struct;

typedef struct sharedmem {
	pid_t pidDad;
	pid_t pidKid;
	char gameID[MAXGAMEID], gameName[MAXGAMENAME], nextField[3];
	int sock, playerCount, thinkTime, thinking, pleaseThink, fieldX, fieldY,
			StoneToPlace, nextStone, pfID;
	int *pf;
	struct player {
		int playerNumber;
		char playerName[MAXPLAYERNAME];
		int playerReady;
		int playerRegisterd;
	} player[8];
} sharedmem;

#endif
