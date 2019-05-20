#include "informes.h"
#include "auto.h"
#include "marca.h"
#include "color.h"
#include "trabajo.h"
#include "servicio.h"
#include "validaciones.h"

void menuInformes(eTrabajo tra[], int tamTra, eAuto aut[], int tamAut, eMarca mar[], int tamMar, eColor col[], int tamCol, eServicio serv[], int tamServ, eCliente cli[], int tamCli)
{
    char seguir = 's';
    char valOpcion[2];
    int opcion;

    do
    {

        system("cls");
        printf("     ===================================================\n");
        printf("     #           >>>> MENU DE INFORMES <<<<            #\n");
        printf("     ===================================================\n");
        printf("      1- Mostrar Autos sg ID Color                      \n");
        printf("      2- Mostrar Autos sg ID Marca                      \n");
        printf("      3- Trabajos efectuados x Auto                     \n");
        printf("      4- Autos sin ningun trabajo                       \n");
        printf("      5- Importe total sg Auto                          \n");
        printf("      6- Servicio + pedido                              \n");
        printf("      7- Recaudacion x Fecha                            \n");
        printf("      8- Autos y Fecha de los que realizaron encerados  \n");
        printf("      9- Trabajos realizados a autos blancos            \n");
        printf("      10- Importe Total x Pulidos                       \n");
        printf("      11- Marca que efectuo + lavados completos         \n");
        printf("      12- Autos con trabajos en una fecha determinada   \n");
        printf("      13- Salir                                         \n");
        printf("     ===================================================\n");
        printf("                                                        \n");
        printf("     Ingrese opcion: ");
        fflush(stdin);
        gets(valOpcion);

        opcion = validarEntero(valOpcion);

        switch(opcion)
        {

        case 1:
            autosXcolor(aut,tamAut,mar,tamMar,col,tamCol,cli,tamCli);
            break;

        case 2:
            autosXmarca(aut,tamAut,mar,tamMar,col,tamCol,cli,tamCli);
            break;

        case 3:
            trabajosXauto(tra,tamTra,aut,tamAut,mar,tamMar,col,tamCol,serv,tamServ,cli,tamCli);
            break;

        case 4:
            autosSinTrabajo(tra,tamTra,aut,tamAut,mar,tamMar,col,tamCol,serv,tamServ,cli,tamCli);
            break;

        case 5:
            importesXauto(tra,tamTra,aut,tamAut,mar,tamMar,col,tamCol,serv,tamServ,cli,tamCli);
            break;

        case 6:
            servicioMasPedido(tra,tamTra,aut,tamAut,mar,tamMar,col,tamCol,serv,tamServ,cli,tamCli);
            break;

        case 7:
            importesXfecha(tra,tamTra,aut,tamAut,mar,tamMar,col,tamCol,serv,tamServ,cli,tamCli);
            break;

        case 8:
            autosEncerados(tra,tamTra,aut,tamAut,mar,tamMar,col,tamCol,serv,tamServ,cli,tamCli);
            break;

        case 9:
            trabajosAutosBlancos(tra,tamTra,aut,tamAut,mar,tamMar,col,tamCol,serv,tamServ,cli,tamCli);
            break;

        case 10:
            importeXpulido(tra,tamTra,aut,tamAut,mar,tamMar,col,tamCol,serv,tamServ,cli,tamCli);
            break;

        case 11:
            marcasConMasLavadosCompletos(tra,tamTra,aut,tamAut,mar,tamMar,col,tamCol,serv,tamServ,cli,tamCli);
            break;

        case 12:
            trabajosXfecha(tra,tamTra,aut,tamAut,mar,tamMar,col,tamCol,serv,tamServ,cli,tamCli);
            break;

        case 13:
            seguir = 'n';
            break;

        default:
            printf("\n Opcion invalida\n\n");
            system("break");
        }

        system("pause");
        system("cls");
    }
    while(seguir == 's');
}


void autosXmarca(eAuto aut[], int tamAut, eMarca mar[], int tamMar, eColor col[], int tamCol, eCliente cli[], int tamCli)
{
    int flag = 0;
    int idMarca;
    char valMarca[4];

    listarMarcas(mar,tamMar);
    printf("Ingrese un ID Marca: ");
    fflush(stdin);
    gets(valMarca);

    idMarca = validarEnteroRango(valMarca,1000,1004);

    for(int i=0; i<tamAut; i++)
    {
        if(aut[i].idMarca == idMarca && aut[i].ocupado == OCUPADO)
        {
            mostrarAuto(aut[i],mar,tamMar,col,tamCol,cli,tamCli);
            flag = 1;
        }
    }

    if(flag == 0)
    {
        printf("Nadie dio de Alta esta marca\n");
    }
}


void autosXcolor(eAuto aut[], int tamAut, eMarca mar[], int tamMar, eColor col[], int tamCol, eCliente cli[], int tamCli)
{
    int flag = 0;
    int idColor;
    char valColor[4];

    listarColores(col,tamCol);
    printf("Ingrese un ID Color: ");
    fflush(stdin);
    gets(valColor);

    idColor = validarEnteroRango(valColor,5000,5004);

    for(int i=0; i<tamAut; i++)
    {
        if(aut[i].idColor == idColor && aut[i].ocupado == OCUPADO)
        {
            mostrarAuto(aut[i],mar,tamMar,col,tamCol,cli,tamCli);
            flag = 1;
        }
    }

    if(flag == 0)
    {
        printf("Nadie dio de Alta este color\n");
    }
}


void trabajosXauto(eTrabajo tra[], int tamTra, eAuto aut[], int tamAut, eMarca mar[], int tamMar, eColor col[], int tamCol, eServicio serv[], int tamServ, eCliente cli[], int tamCli)
{
    int flag = 0;
    char patente[7];

    mostrarAutos(aut,tamAut,mar,tamMar,col,tamCol,cli,tamCli);

    printf("Ingrese Patente: ");
    fflush(stdin);
    gets(patente);

    ValidarPatente(patente);

    if(buscarPatente(aut,tamAut,patente)==-1)
    {
        printf("Esta patente no existe\n");
    }
    else
    {
        for(int i=0; i<tamTra; i++)
        {
            if(tra[i].ocupado == OCUPADO)
            {
                for(int j=0; j<tamAut; j++)
                {
                    if(stricmp(tra[i].patente,patente) == 0 && aut[j].ocupado == OCUPADO)
                    {
                        mostrarTrabajo(tra[i],aut,tamAut,mar,tamMar,col,tamCol,serv,tamServ);
                        flag = 1;
                        break;
                    }
                }
            }
        }

        if(flag == 0)
        {
            printf("Este auto no esta trabajando\n");
        }
    }


}

//PREGUNTAR X SERVICIO 2004
void autosSinTrabajo(eTrabajo tra[], int tamTra, eAuto aut[], int tamAut, eMarca mar[], int tamMar, eColor col[], int tamCol, eServicio serv[], int tamServ, eCliente cli[], int tamCli)
{
    int flag;

    printf("Autos que no tuvieron trabajos: \n");

    for(int i=0; i<tamAut; i++)
    {
        flag = 0;

        for(int j=0; j<tamTra; j++)
        {
            if(strcmp(aut[i].patente,tra[j].patente) == 0 && aut[i].ocupado == OCUPADO && tra[j].ocupado == OCUPADO)
            {
                for(int k=0; k<tamServ; k++)
                {
                    if(serv[k].id == tra[j].idServicio)
                    {
                        flag = 1;
                        break;
                    }
                }
            }
        }

        if(flag == 0 && aut[i].ocupado == OCUPADO)
        {

            mostrarAuto(aut[i],mar,tamMar,col,tamCol,cli,tamCli);

        }


    }


    if(flag == 1)
    {
        printf("Todos tienen algun servicio\n");

    }
}


void importesXauto(eTrabajo tra[], int tamTra, eAuto aut[], int tamAut, eMarca mar[], int tamMar, eColor col[], int tamCol, eServicio serv[], int tamServ, eCliente cli[], int tamCli)
{
    int total = 0;
    char patente[7];
    int flag = 0;

    mostrarAutos(aut,tamAut,mar,tamMar,col,tamCol,cli,tamCli);

    printf("Ingrese Patente: ");
    fflush(stdin);
    gets(patente);

    ValidarPatente(patente);

    if(buscarPatente(aut,tamAut,patente)==-1)
    {
        printf("Esta patente no existe\n");
    }
    else
    {
        for(int i=0; i<tamTra; i++)
        {

            if(stricmp(tra[i].patente,patente) == 0 && tra[i].ocupado == OCUPADO)
            {

                for(int j=0; j<tamServ; j++)
                {
                    if(serv[j].id == tra[i].idServicio)
                    {
                        total+=serv[j].precio;
                        flag = 1;
                        break;
                    }
                }
            }
        }


        printf("Total recaudado: %d\n",total);


        if(flag == 0)
        {
            printf("Este auto no presenta ningun gasto\n");
        }

    }


}


void servicioMasPedido(eTrabajo tra[], int tamTra, eAuto aut[], int tamAut, eMarca mar[], int tamMar, eColor col[], int tamCol, eServicio serv[], int tamServ, eCliente cli[], int tamCli)
{
    int cont[tamServ];
    int flag = 0;
    int mayor;

    for(int i=0; i<tamServ; i++)
    {
        cont[i] = 0;

        for(int j=0; j<tamTra; j++)
        {
            if(serv[i].id == tra[j].idServicio && tra[i].ocupado == OCUPADO)
            {
                for(int k=0; k<tamAut; k++)
                {
                    if(aut[k].ocupado == OCUPADO && strcmp(tra[j].patente,aut[k].patente)==0)
                    {
                        cont[i]++;

                    }
                }
            }
        }
    }


    for(int i=0; i<tamServ; i++)
    {
        if(flag == 0 || cont[i]>mayor)
        {
            mayor =  cont[i];

            flag = 1;
        }
    }


    printf("Servicio mas pedido:\n");


    for(int i=0; i<tamServ; i++)
    {
        if(cont[i] == mayor)
        {
            printf("%s\n",serv[i].descripcion);
        }
    }
}


void importesXfecha(eTrabajo tra[], int tamTra, eAuto aut[], int tamAut, eMarca mar[], int tamMar, eColor col[], int tamCol, eServicio serv[], int tamServ, eCliente cli[], int tamCli)
{
    int total = 0;
    int flag = 0;

    eFecha fecha;

    char valDia[2];
    char valMes[2];
    char valAnio[4];

    printf("Ingrese anio: ");
    fflush(stdin);
    gets(valAnio);

    fecha.anio = validarEnteroRango(valAnio,2019,2080);

    printf("Ingrese mes: ");
    fflush(stdin);
    gets(valMes);

    fecha.mes = validarEnteroRango(valMes,1,12);

    printf("Ingrese dia: ");
    fflush(stdin);
    gets(valDia);

    if (fecha.mes == 4 || fecha.mes == 6 || fecha.mes == 9 || fecha.mes == 11)
    {
        fecha.dia = validarEnteroRango(valDia,1,30);
    }
    else if(fecha.mes == 2)
    {
        fecha.dia = validarEnteroRango(valDia,1,28);
    }
    else
    {
        fecha.dia = validarEnteroRango(valDia,1,31);
    }


    for(int i=0; i<tamTra; i++)
    {
        if(compararFechas(tra[i].fechaTrabajo,fecha))
        {
            for(int j=0; j<tamAut; j++)
            {
                if(aut[j].ocupado == OCUPADO && strcmp(tra[i].patente,aut[j].patente) == 0 && tra[i].ocupado == OCUPADO)
                {
                    for(int k=0; k<tamServ; k++)
                    {
                        if(serv[k].id == tra[i].idServicio)
                        {
                            total+=serv[k].precio;
                            flag = 1;
                            break;
                        }
                    }
                }
            }
        }
    }


    if(flag == 0)
    {
        printf("No hay importes acumulados en esta fecha\n");
    }
    else
    {
        printf("Total recaudado en la fecha %0d/%0d/%d: %d\n",fecha.dia,fecha.mes,fecha.anio,total);
    }
}


void trabajosXfecha(eTrabajo tra[], int tamTra, eAuto aut[], int tamAut, eMarca mar[], int tamMar, eColor col[], int tamCol, eServicio serv[], int tamServ, eCliente cli[], int tamCli)
{
    int flag = 0;

    eFecha fecha;

    char valDia[2];
    char valMes[2];
    char valAnio[4];

    printf("Ingrese anio: ");
    fflush(stdin);
    gets(valAnio);

    fecha.anio = validarEnteroRango(valAnio,2019,2080);

    printf("Ingrese mes: ");
    fflush(stdin);
    gets(valMes);

    fecha.mes = validarEnteroRango(valMes,1,12);

    printf("Ingrese dia: ");
    fflush(stdin);
    gets(valDia);

    if (fecha.mes == 4 || fecha.mes == 6 || fecha.mes == 9 || fecha.mes == 11)
    {
        fecha.dia = validarEnteroRango(valDia,1,30);
    }
    else if(fecha.mes == 2)
    {
        fecha.dia = validarEnteroRango(valDia,1,28);
    }
    else
    {
        fecha.dia = validarEnteroRango(valDia,1,31);
    }

    for(int i=0; i<tamTra; i++)
    {
        if(compararFechas(tra[i].fechaTrabajo,fecha))
        {
            for(int j=0; j<tamAut; j++)
            {
                if(aut[j].ocupado == OCUPADO && strcmp(tra[i].patente,aut[j].patente) == 0 && tra[i].ocupado == OCUPADO)
                {
                    for(int k=0; k<tamServ; k++)
                    {
                        if(serv[k].id == tra[i].idServicio)
                        {
                            mostrarAuto(aut[j],mar,tamMar,col,tamCol,cli,tamCli);
                            flag = 1;
                            break;
                        }
                    }
                }
            }
        }
    }


    if(flag == 0)
    {
        printf("No hay trabajos en esta fecha\n");
    }
}


void autosEncerados(eTrabajo tra[], int tamTra, eAuto aut[], int tamAut, eMarca mar[], int tamMar, eColor col[], int tamCol, eServicio serv[], int tamServ, eCliente cli[], int tamCli)
{
    char descripcion[20];
    int flag = 0;

    listarServicios(serv,tamServ);

    printf("Ingrese la descripcion del servicio a buscar: ");
    fflush(stdin);
    gets(descripcion);

    validarStringTam(descripcion,20);

    printf("\n\n");

    for(int i=0; i<tamTra; i++)
    {
        for(int j=0; j<tamAut; j++)
        {
            if(tra[i].ocupado == OCUPADO && aut[j].ocupado == OCUPADO && strcmp(tra[i].patente,aut[j].patente) == 0)
            {
                for(int k=0; k<tamServ; k++)
                {
                    if(stricmp(serv[k].descripcion,descripcion) == 0 && tra[i].idServicio == serv[k].id)
                    {
                        printf("%s %d/%d/%d\n",aut[j].patente, tra[i].fechaTrabajo.dia, tra[i].fechaTrabajo.mes, tra[i].fechaTrabajo.anio);
                        flag = 1;

                        break;
                    }
                }
            }
        }
    }

    if(flag == 0)
    {
        printf("No hay ningun auto para el servicio %s\n",descripcion);
    }
}


void trabajosAutosBlancos(eTrabajo tra[], int tamTra, eAuto aut[], int tamAut, eMarca mar[], int tamMar, eColor col[], int tamCol, eServicio serv[], int tamServ, eCliente cli[], int tamCli)
{
    char descripcion[20];
    int flag = 0;

    listarColores(col,tamCol);

    printf("Ingrese la descripcion del color a buscar: ");
    fflush(stdin);
    gets(descripcion);

    validarStringTam(descripcion,20);

    for(int i=0; i<tamAut; i++)
    {
        for(int j=0; j<tamCol; j++)
        {
            if(aut[i].ocupado == OCUPADO && stricmp(col[j].nombreColor,descripcion) == 0 && aut[i].idColor == col[j].id)
            {
                for(int k=0; k<tamTra; k++)
                {
                    if(tra[k].ocupado == OCUPADO && strcmp(aut[i].patente,tra[k].patente)==0)
                    {
                        mostrarTrabajo(tra[k],aut,tamAut,mar,tamMar,col,tamCol,serv,tamServ);
                        flag = 1;
                        break;
                    }
                }
            }
        }
    }

    if(flag == 0)
    {
        printf("No hay trabajos con autos color %s\n",descripcion);
    }
}


void importeXpulido(eTrabajo tra[], int tamTra, eAuto aut[], int tamAut, eMarca mar[], int tamMar, eColor col[], int tamCol, eServicio serv[], int tamServ, eCliente cli[], int tamCli)
{
    int flag = 0;
    int total = 0;
    char descripcion[20];

    listarServicios(serv,tamServ);

    printf("Ingrese la descripcion del servicio a buscar: ");
    fflush(stdin);
    gets(descripcion);

    validarStringTam(descripcion,20);

    for(int i=0; i<tamTra; i++)
    {
        for(int j=0; j<tamServ; j++)
        {
            if(stricmp(serv[j].descripcion,descripcion) == 0 && tra[i].idServicio == serv[j].id && tra[i].ocupado == OCUPADO)
            {
                for(int k=0; k<tamAut; k++)
                {
                    if(aut[k].ocupado == OCUPADO && strcmp(tra[i].patente,aut[k].patente) == 0)
                    {
                        total+=serv[j].precio;
                        flag = 1;
                        break;
                    }
                }
            }
        }
    }


    if(flag == 0)
    {
        printf("No hay trabajos con este servicio\n");
    }
    else
    {
        printf("Total acumulado x servicio %s: %d\n",descripcion,total);
    }
}


void marcasConMasLavadosCompletos(eTrabajo tra[], int tamTra, eAuto aut[], int tamAut, eMarca mar[], int tamMar, eColor col[], int tamCol, eServicio serv[], int tamServ, eCliente cli[], int tamCli)
{
    int cont[tamMar];
    int flag = 0;
    int mayor;
    char descripcion[20];

    listarServicios(serv,tamServ);

    printf("Ingrese la descripcion del servicio a buscar: ");
    fflush(stdin);
    gets(descripcion);

    validarStringTam(descripcion,20);

    for(int i=0; i<tamMar; i++)
    {
        cont[i] = 0;

        for(int j=0; j<tamAut; j++)
        {
            if(aut[j].idMarca == mar[i].id && aut[j].ocupado == OCUPADO)
            {
                for(int k=0; k<tamTra; k++)
                {
                    if(strcmp(aut[j].patente,tra[k].patente) == 0 && tra[k].ocupado == OCUPADO)
                    {
                        for(int h=0; h<tamServ; h++)
                        {
                            if(stricmp(serv[h].descripcion,descripcion)==0 && tra[k].idServicio == serv[h].id)
                            {
                                cont[i]++;
                            }
                        }
                    }
                }
            }
        }
    }


    for(int i=0; i<tamMar; i++)
    {
        if(flag == 0 || cont[i]>mayor)
        {
            mayor =  cont[i];

            flag = 1;
        }
    }


    printf("Marca con + servicio %s:\n",descripcion);


    for(int i=0; i<tamMar; i++)
    {
        if(cont[i] == mayor)
        {
            printf("%s\n",mar[i].descripcion);
        }
    }
}
