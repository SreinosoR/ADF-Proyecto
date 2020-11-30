/*----------------------------------------------------------------------------------------------------------------------
  Descripcion: Proyecto ADF.
  Autores: Jose Manuel Corvalan Parada, Sebastian Reinoso Rodriguez, Maximiliano Leon Palominos.
  Asignatura: Estructura de datos [INF2240].
------------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tamMaxFaltas 500
/*---------------------------------------------------Estructuras-----------------------------------------*/
                         
struct carrera 
{
    char *nombre;
    int id;
    struct nodoAsignatura *asignaturas; 
};
struct nodoAsignatura
{
    struct asignatura *datosAsignatura;
    struct nodoAsignatura *sig;
};
struct asignatura
{
    char *nombre;
    int     id;
    char *profesor;
    struct nodoAlumno *alumnos;
    struct falta *historialFaltas;
};
struct nodoAlumno
{
    struct alumno *datosAlumno;
    struct nodoAlumno  *sig;
};
struct alumno 
{
    char *nombre;
    char *rut;
    int anoIngreso;
    int cantidadFaltas;
};
struct falta
{
    struct alumno *acusado;
    int valor;
    char *medio;
    char pLibre;
    
};
/*---------------------------------------------------Prototipos de funciones-----------------------------------------*/
//Declaracion de funciones de menu

void menuAlumno();
void menuAsignatura();
void menuFaltas();

//Declaracion de funciones de Alumno

struct nodoAlumno *crearAlumno(char*,char *, int);
void *agregarAlumno (struct nodoAlumno **, struct nodoAlumno *);
struct nodoAlumno *buscarAlumno (struct nodoAlumno *, char *);
struct nodoAlumno *eliminarAlumno (struct nodoAlumno **, char *);
void mostrarAlumnosAsignatura(struct nodoAlumno*);
void *mostrarAlumnosCarrera (struct carrera *escuela);
void ingresarAlumno(struct carrera *);
void EliminandoAlumno(struct carrera *);

//Declaracion de funciones de Asignatura

void *mostrarAsignaturas (struct carrera * );
struct nodoAsignatura *crearAsignatura(char*,int , char* );
void *agregarAsignatura (struct carrera *, struct nodoAsignatura *);
void ingresarNuevaAsignatura(struct carrera *);
void EliminandoAsignatura(struct carrera *);

//Declaracion de funciones de Falta

void mostrarFaltas (struct nodoAsignatura *);
struct falta crearFalta(struct falta *,struct alumno *,char *,int );
struct falta buscarFalta(struct falta *,char *,char *, int );
void agregarFalta(struct falta **,char *,char *, int );
char *faltaMasComun (struct asignatura *);
int contadorFaltas (char *,struct falta *);
struct falta *eliminarFalta (struct falta **,char *, char *, int );
void aumentarFaltas(struct carrera *,char *,int);
void aumentandoFaltas(struct carrera* );
void elimandoFalta(struct carrera *);
void ingresarNuevafalta(struct carrera*);
void MostrarFaltaMasComun (struct carrera *);

/*-----------------------------------------------------Programa Principal-------------------------------------------*/
main()
{
        int opcion;
        do
        {
                printf("\n 1. Alumno");
                printf("\n 2. Asignatura");
                printf("\n 3. Faltas");
                printf("\n 4. Salir");
                do
                {
                        printf("\n Ingrese seleccion");
                        scanf("%d",&opcion);
                } while (opcion<1 || opcion>4);
                switch (opcion)
                {
                case 1: menuAlumno();
                        break;
                case 2: menuAsignatura();
                        break;
                case 3: menuFaltas();
                        break;                
                }
        } while (opcion!=4);      
}
/*---------------------------------------------------------Funciones-----------------------------------------------*/

// Funciones del menu

void menuAlumno(struct carrera *escuela)
{
        int seleccion;
        do
        {
                printf("\n 1. Agregar Alumno");
                printf("\n 2. Mostrar Lista");
                printf("\n 3. Eliminar Alumno");
                printf("\n 4. Salir");
                do
                {
                        printf("\n Ingrese seleccion");
                        scanf("%d",&seleccion);
                } while (seleccion<1 || seleccion>4);
                switch (seleccion)
                {
                case 1: printf("\nAqui se agrega un alumno");
                        ingresarAlumno(escuela);
                        break;
                case 2: printf("\nAqui se muestran los alumnos");
                        mostrarAlumnosCarrera(escuela);
                        break;
                case 3: printf("\nAqui se elimina a un alumno");
                        EliminandoAlumno(escuela);
                        break;                
                }
        } while (seleccion !=4);
}
void menuAsignatura(struct carrera *escuela )
{
        int seleccion;
        do
        {
                printf("\n 1. Agregar Asignatura");
                printf("\n 2. Mostrar Asignatura");
                printf("\n 3. Eliminar Asignatura");
                printf("\n 4. Salir\n\n");
                do
                {
                       printf("\n Ingrese seleccion\n");
                       scanf("%d",&seleccion);
                } while (seleccion<1 || seleccion>4);
                switch (seleccion)
                {
                case 1: printf("\nAqui se agrega una asginatura\n\n\n");
                		ingresarNuevaAsignatura(escuela);
                        break;
                case 2: printf("\nAqui se muestran las asginaturas\n");
                		mostrarAsignaturas (escuela);
                        break;
                case 3: printf("\nAqui se elimina una asignatura\n");
                        EliminandoAsignatura(escuela);
                        break;
                case 4: printf("\nAqui se muestra la falta mas comun\n");
                        MostrarFaltaMasComun(escuela);
                        break;
					                
                }
        } while (seleccion !=4);
}
void menuFaltas(struct carrera *escuela )
{


        int seleccion;
        
        do
        {
            printf("\n 1. Agregar Faltas");
                printf("\n 2. Eliminar Faltas");
                printf("\n 3. Aumentar Falta");
                printf("\n 4. Salir");
                do
                {
                        printf("\n Ingrese seleccion");
                        scanf("%d",&seleccion);
                } while (seleccion<1 || seleccion>4);
                switch (seleccion)
                {
                case 1: printf("\nAqui se agrega una Falta ");
                		ingresarNuevafalta(escuela);
                        break;
                case 2: printf("\nAqui se elimina la Falta");
                		eliminandoFalta(escuela);
                        break;
            	case 3: printf("Se aumentara una falta");
            			aumentandoFaltas(escuela);
            			break;
                }
        } while (seleccion !=4);
}

//Funciones de alumnos 

void ingresarAlumno(struct carrera *escuela)
{
	char nombre[60],rut[50];
	int anoIngreso;
	FILE *AlumC; 
	AlumC= fopen("AlumC.txt","at");
	struct nodoAlumno *nuevoAlumno;
	
	printf("Ingrese Nombre del Alumno sin espacios \n\n");
		scanf("%s[^\n]",&nombre);
		fprintf(AlumC,"%s\n",nombre);
	printf("Ingrese Rut del Alumno\n\n");
		scanf("%s[^\n]",&rut);
		fprintf(AlumC,"%s\n",rut);
	printf("Ingrese Ano del ingreso\n\n");
		scanf("%d",&anoIngreso);
		fprintf(AlumC,"%d\n\n",anoIngreso);
	fclose(AlumC);
	
	nuevoAlumno= crearAlumno(nombre,rut,anoIngreso);
	agregarAlumno(escuela->asignaturas->datosAsignatura->alumnos,nuevoAlumno);	
}

struct nodoAlumno *crearAlumno(char *nombre,char *rut , int ingreso)
{
    struct nodoAlumno *nuevoAlumno;
    
    nuevoAlumno = (struct nodoAlumno*) malloc(sizeof(struct nodoAlumno));
    nuevoAlumno->datosAlumno = (struct alumno*) malloc(sizeof(struct alumno)); 
    nuevoAlumno->datosAlumno->nombre = (char *) malloc(sizeof(strlen(nombre)+1));
    nuevoAlumno->datosAlumno->rut = (char *) malloc(sizeof(strlen(rut)+1));

    strcpy (nuevoAlumno->datosAlumno->nombre,nombre);
    strcpy (nuevoAlumno->datosAlumno->rut,rut);
    nuevoAlumno->datosAlumno->anoIngreso = ingreso;
    nuevoAlumno->datosAlumno->cantidadFaltas = 0; 
    nuevoAlumno->sig = NULL;
    return nuevoAlumno;
}

void *agregarAlumno (struct nodoAlumno **alumno, struct nodoAlumno *nuevo)
{  
    struct nodoAlumno *posicion;
     
    posicion = *alumno;

    if((*alumno) !=NULL)//si la lista no esta vacia
    {
        while(posicion!=NULL)
        {
            if (posicion->sig ==NULL)
            {
                posicion->sig = nuevo;//se asigna el nuevo nodo a la lista 
                posicion= posicion->sig;
            }
            posicion = posicion->sig;
        }
         
    }
    else 
    (*alumno) = nuevo;//si la lista esta vacia 
}

struct nodoAlumno *buscarAlumno (struct nodoAlumno *alumno , char *rut )
{
    struct nodoAlumno *posicion;

    posicion= alumno;

    if (alumno !=NULL)
    {
        while (posicion !=NULL)
        {
            if (posicion->datosAlumno !=NULL)
            {
                if(strcmp(rut,posicion->datosAlumno->rut)== 0);
                {
                    return posicion;   
                }

            }
            posicion= posicion->sig; 
        }
        return NULL;
    }
    return NULL;
}

struct nodoAlumno *eliminarAlumno (struct nodoAlumno **alumno, char *rut)
{
    struct nodoAlumno *eliminado;
    

    eliminado = buscarAlumno((*alumno),rut);

    if (eliminado!=NULL)
    {
        while(*alumno!=NULL)
        {
            if (strcmp((*alumno)->datosAlumno->rut,eliminado->datosAlumno->rut)==0)
            {
                (*alumno)=eliminado->sig;
                return eliminado;  
            }
            (*alumno)=(*alumno)->sig;  
        }   
    }
    return eliminado;
}

void mostrarAlumnosAsignatura(struct nodoAlumno* alumnos)
{        
    struct nodoAlumno *pos;
	FILE *AlumC;
	AlumC=fopen("AlumnosCarrera.txt","rb");
    
    while(alumnos != NULL)
    {
        if(alumnos->datosAlumno!= NULL)
        {
            fscanf(AlumC,"%s%s%d",&alumnos->datosAlumno->nombre,&alumnos->datosAlumno->rut,&alumnos->datosAlumno->anoIngreso);
			printf("%s\n%s\n ","Nombre del Alumno: ",alumnos->datosAlumno->nombre);
			printf("%s\n%s\n ","Rut: ",alumnos->datosAlumno->rut );
			printf("%s\n  %d\n ","Ano de Ingreso: ",alumnos->datosAlumno->anoIngreso);   
        }
        alumnos = alumnos->sig;
    }
    fclose(AlumC);
    printf("\n\n");
}

void *mostrarAlumnosCarrera (struct carrera *escuela)
{
    while(escuela->asignaturas->datosAsignatura!= NULL)
    {
        if(escuela->asignaturas->datosAsignatura!= NULL)
        {
            printf("%s%s\n  %s%s\n ","Ramo: ","Id:  ",escuela->asignaturas->datosAsignatura->nombre,escuela->asignaturas->datosAsignatura->id);
            mostrarAlumnosAsignatura(escuela->asignaturas->datosAsignatura->alumnos);
        }
        escuela->asignaturas= escuela->asignaturas->sig;
    } 
    
} 

void EliminandoAlumno(struct carrera *escuela)
{
	char rut[10];
	struct nodoAlumno *eliminado;
	
	printf("\n\n Ingrese rut del alumno que desea eliminar ");
	scanf("%d",&rut);
    
	eliminado=eliminarAlumno(escuela->asignaturas->datosAsignatura->alumnos,rut);
	printf("El alumno %s, rut %s fue eliminado con exito.\n\n",eliminado->datosAlumno->nombre,eliminado->datosAlumno->rut);	
}

//Funciones de asignatura

void ingresarNuevaAsignatura(struct carrera *escuela)
{
	char nombre[50],profesor[50];
	int id;
	struct nodoAsignatura *nuevaAsignatura;
	
	printf("Ingrese Nombre de la Nueva Asignatura\n\n");
	scanf("%s",&(*nombre));
	printf("Ingrese Nombre del Profesor acargo de la Nueva Asignatura\n\n");
	scanf("%s",&(*profesor));
	printf("Ingrese id de la Nueva Asignatura\n\n");
	scanf("%d",&id);
	nuevaAsignatura = crearAsignatura(nombre,id,profesor);
	agregarAsignatura(escuela,nuevaAsignatura);
		
}

struct nodoAsignatura *crearAsignatura(char *nombre,int id , char *profesor)
{
    struct nodoAsignatura *nuevoAsignatura;
    nuevoAsignatura = (struct nodoAsignatura*) malloc(sizeof(struct nodoAsignatura));
    nuevoAsignatura->datosAsignatura =(struct asignatura*) malloc(sizeof(struct asignatura));
    nuevoAsignatura->datosAsignatura->historialFaltas = (struct falta*) malloc(sizeof(struct falta));
    nuevoAsignatura->datosAsignatura->nombre = (char *) malloc(sizeof(strlen(nombre)+1));
    nuevoAsignatura->datosAsignatura->profesor = (char *) malloc(sizeof(strlen(profesor)+1));
    
    strcpy (nuevoAsignatura->datosAsignatura->nombre,nombre);
    nuevoAsignatura->datosAsignatura->id=id;
    strcpy (nuevoAsignatura->datosAsignatura->profesor,profesor);
    nuevoAsignatura->datosAsignatura->historialFaltas=NULL;

    nuevoAsignatura->sig =NULL;

    return nuevoAsignatura;
}

void *agregarAsignatura (struct carrera *escuela, struct nodoAsignatura *nuevo)

{  
    struct nodoAsignatura *posicion;
     
    posicion = escuela->asignaturas;

    if(escuela->asignaturas !=NULL)//si la lista no esta vacia
    {
        while(posicion!=NULL)
        {
            if (posicion->sig ==NULL)
            {
                posicion->sig = nuevo;//se asigna el nuevo nodo a la lista 
                posicion= posicion->sig;
            }
            posicion = posicion->sig;
        }
         
    }
    else 
    escuela->asignaturas = nuevo;//si la lista esta vacia 
}

void *mostrarAsignaturas (struct carrera *escuela)
{
    if (escuela!=NULL)
    {   
        if (escuela ->asignaturas!=NULL)
        {   
            printf("  %s%s\n", "Nombre Carrera: ", escuela->nombre);
            printf("  %s%s\n", "Id: ", escuela->id);
            while (escuela->asignaturas!=NULL)
            {
                if(escuela->asignaturas->datosAsignatura!= NULL)
                {
                    printf("  %s%s\n", "Nombre Asignatura: ", escuela->asignaturas->datosAsignatura->nombre);
                    printf("  %s%d\n", "Id: ", escuela->asignaturas->datosAsignatura->id);
                    printf("  %s%s\n", "Nombre Profesor", escuela->asignaturas->datosAsignatura->profesor);
        
                }
                escuela->asignaturas = escuela->asignaturas->sig;
                printf("\n\n");
            }
        }
        else 
        printf ("No existe ninguna asignatura\n\n");
   
    }
    else 
    printf ("No existe ninguna carrera\n\n");    
}

struct nodoAsignatura *buscarAsignatura (struct nodoAsignatura *asignaturas, int id)
{
    struct nodoAsignatura *posicion;
    posicion= asignaturas;
    if (asignaturas!=NULL)
    {
        while (posicion !=NULL)
        {
            if (posicion->datosAsignatura !=NULL)
            {   
                if((asignaturas->datosAsignatura->id)==(posicion->datosAsignatura->id))
                {
                    return posicion;   
                }
            }
            posicion= posicion->sig; 
        }
        return NULL;
    }
    return NULL;
}

struct asignatura *eliminarAsignatura (struct nodoAsignatura **ramos, int id )
{
    struct nodoAsignatura *eliminado;
    
eliminado = buscarAsignatura(*ramos,id);
if (eliminado!=NULL)
{
    while(*ramos!=NULL)
    {
        if (((*ramos)->datosAsignatura->id)==(eliminado->datosAsignatura->id)) 
        {
            *ramos=eliminado->sig;
            return eliminado->datosAsignatura;  
        }
        *ramos=(*ramos)->sig;  
    }   
}
return eliminado->datosAsignatura;
}

void EliminandoAsignatura (struct carrera *escuela)
{
	int id;
	struct asignatura *eliminado;
	
	printf("\n\nIngrese id de la carrera de que desea eliminar");
	scanf("%d",&id);
	eliminado=eliminarAsignatura(escuela->asignaturas,id);
	
	printf("La carrera %s, codigo %id fue eliminado con exito\n\n.",eliminado->nombre,eliminado->id); 
		
}

//Funciones de Faltas

void mostrarFaltas (struct nodoAsignatura *asignatura)
{
    struct nodoAsignatura* pos;
    pos = asignatura;
    int i; 

    if (pos->datosAsignatura->historialFaltas!=NULL)
    {
        for (i=0;i<pos->datosAsignatura->historialFaltas->pLibre;i++)
        {
            printf("  %s%s\n", "Rut: ", pos->datosAsignatura->historialFaltas[i].acusado->rut);
            printf("  %s%d\n", "Valor: ", pos->datosAsignatura->historialFaltas[i]->valor);
            printf("  %s%s\n", "Medio: ", pos->datosAsignatura->historialFaltas[i]->medio);
        }    
    }
    else 
        printf("La Asignatura no tiene Faltas");

    printf("\n\n");
}

struct falta crearFalta(struct falta *faltas,struct alumno *acusado,char *medio,int valor)
{
    struct falta *nuevafalta;
    nuevafalta = (struct falta*) malloc(sizeof(struct falta));
    nuevafalta->acusado= (struct alumno*) malloc(sizeof(struct alumno));
    nuevafalta->medio= (char*)malloc(sizeof(strlen(medio)+1));

    strcpy (nuevafalta->medio,medio);
    nuevafalta->acusado=acusado;
    nuevafalta->valor=valor;
    nuevafalta->pLibre++;

    return *nuevafalta;

}

struct falta buscarFalta(struct falta *faltas,char *rut,char *medio, int valor)
{
    int i;

    for(i=0;i<faltas->pLibre;i++)
    {
        if((strcmp((faltas[i])->acusado->rut,rut)==0) && (strcmp((faltas[i])->medio,medio)==0) && ((faltas[i])->valor==valor))
        {
            return (faltas[i]);
        }
    }
}

void agregarFalta(struct falta **faltas,char *rut,char *medio, int valor)
{
    int i;
    
	for (i=0;i<tamMaxFaltas;i++)
    {
        if(i==(*faltas)->pLibre)
        {
            (*faltas[i])=crearFalta((*faltas),(*faltas)->acusado,medio,valor);
        }
    }
}

void ingresarNuevafalta(struct carrera* escuela)
{
	struct nodoAlumno *culpable;
	char rut[12],medio[20];
	int valor;
	
	printf("Ingrese rut del alumno");
	scanf("%s",&rut);
	printf("Ingrese medio del ilicito");
	scanf("%s",&medio);
	printf("ingrese valor de la falta, 1-2-3");
	scanf("%d",&valor);
	
	culpable=buscarAlumno(escuela->asignaturas->datosAsignatura->alumnos,rut);
	
	if (culpable!=NULL)
	{
		agregarFalta(escuela->asignaturas->datosAsignatura->historialFaltas,rut,medio,valor);
	}
	printf("La falta se ingreso correctamente");
}

char *faltaMasComun (struct asignatura *ramo)
{
  char *medioMasComun;
  int i;

  for (i=0;i<ramo->historialFaltas->pLibre;i++)
  {
    if (contadorFaltas(ramo->historialFaltas[i]->medio,ramo->historialFaltas)>contadorFaltas(ramo->historialFaltas[i+1]->medio,ramo->historialFaltas))
    {
        medioMasComun=ramo->historialFaltas[i]->medio;
    }
  }
  return medioMasComun;
}

int contadorFaltas (char *medio,struct falta *arregloFaltas)

{
    int i,cont;

    for (i=0;i<tamMaxFaltas;i++)
    {
        if(strcmp(medio,(arregloFaltas[i])->medio))
        {
            cont++;
        }
    }
    return cont;
}

struct falta *eliminarFalta (struct falta **faltas,char *rut, char *medio, int valor)
{
    struct falta *eliminado;
    int i,j;

    *eliminado=buscarFalta(*faltas,rut,medio,valor);
    
    if (eliminado!=NULL)
    {
        for (i=0;i<(*faltas)->pLibre;i++)
        {
           if((strcmp((*faltas)[i]->acusado->rut,rut)==0) && (strcmp((*faltas[i])->medio,medio)==0) && ((*faltas[i])->valor==valor))
           {
               for(j=i; j<(*faltas)->pLibre; j++)
               {
                   (*faltas[j])= (*faltas)[j+1];
               }
               (*faltas)->pLibre--;

               return (*faltas);
           }
        }   
    }
}

void aumentarFaltas(struct carrera *escuela,char *rut)
{
	struct nodoAlumno *ilisito;
	
	ilisito=buscarAlumno(escuela->asignaturas,rut);
	
	if(escuela->asignaturas!=NULL)
	{
		if (strcmp(ilisito->datosAlumno->rut,rut)==0)
		{
			ilisito->datosAlumno->cantidadFaltas++;		
		}
		
	}
	
	
	
}

void MostrarFaltaMasComun (struct carrera *escuela)
{
		char *falta;
		
	falta=faltaMasComun(escuela->asignaturas->datosAsignatura);
	printf("La falta mas comun de la asignatura %s es %s",escuela->asignaturas->datosAsignatura->nombre,falta);
			
}

void eliminandoFalta(struct carrera *escuela)
{
	char rut[12],medio[20];
	int valor;
	struct falta *eliminado;
	
	printf("Ingrese rut del alumno");
	scanf("%s",&rut);
	printf("Ingrese medio del ilicito");
	scanf("%s",&medio);
	printf("ingrese valor de la falta, 1-2-3");
	scanf("%d",&valor);
	 
	eliminado=eliminarFalta(escuela->asignaturas->datosAsignatura->historialFaltas,rut,medio,valor);
	
	printf("La falta del %s, %s fue eliminada con exito",eliminado->acusado->nombre,eliminado->acusado->rut);
	
}

void aumentandoFaltas(struct carrera* escuela)
{
	char rut[12];
	int valor;
	
	
	printf("\n Ingrese Rut del alumno");
	scanf("%s",&rut);
	printf("Ingrese valor de la falta , 1-2-3 ");
	scanf("%d",&valor);
	
	aumentarFaltas(escuela,rut,valor);
			
}
