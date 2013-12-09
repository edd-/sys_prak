#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netdb.h>
#include "sharedVariables.h"
#include "errmmry.h"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define AT __FILE__ ":" TOSTRING(__LINE__)



int initConnection(int argc, char ** argv)
{

    //überpruefe ob die angegebene Game-ID ueberhaupt die richtige Laenge hat oder existiert
    if ( argc == 1 || (strlen (argv[1])) != 11)
    {
        printf("Fehler: Der uebergebene Parameter hat nicht die korrekte Laenge");
        return EXIT_FAILURE;
    }
    else
    {

        if (argc == 3)
        {
            if (openConfig(argv[2])!= 0) //Falls Custom-config angegeben wurde
            {
                return EXIT_FAILURE;
            }
        }
        else
        {
            if (openConfig("client.conf") != 0) //Sonst Standard-config
            {
                return EXIT_FAILURE;
            }
        }


        strcat(shm->gameID,argv[1]);

        shm->pidDad = getppid(); //PID vom Vater und Eigene in SHM schreiben
        shm->pidKid = getppid();
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    writelog(logdatei,AT);
    struct sockaddr_in host;
    struct hostent* ip;
    ip = (gethostbyname(conf->hostname)); //uebersetze HOSTNAME in IP Adresse
    memcpy(&(host.sin_addr),ip ->h_addr,ip ->h_length);
    host.sin_family = AF_INET;
    host.sin_port = htons(conf->portnumber);

    if (connect(sock,(struct sockaddr*)&host, sizeof(host)) == 0)
    {
        printf("\nVerbindung mit %s hergestellt!\n",conf->hostname);
        writelog(logdatei,AT);
    }
    else
    {
        perror("\n Fehler beim Verbindungsaufbau");
        writelog(logdatei,AT);
        return EXIT_FAILURE;
    }
    performConnection(sock);//Fuehre Prolog Protokoll aus


    return EXIT_SUCCESS;
}