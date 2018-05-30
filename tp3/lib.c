
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "peliculas.h"
#include "lib.h"


/** \brief LIMPIAR PANATALLA
 *
 */
void cleanScreen (void)
{
            printf("\n");
            system ("pause");
            system ("cls");
}


 /** \brief Pregunta S o N
 * *
 * \param texto de la pregunta
 * \return respuesta
 *
 */
 char preguntarSiNo ( char texto [])
 {
     char respuesta;

     printf("%s S o N:", texto);
     fflush(stdin);
     respuesta= tolower(getche());

    while (respuesta != 's' && respuesta !='n')
        {
        printf(" \nRespuesta Incorrecta-%s\t",texto);
        fflush(stdin);
        respuesta= tolower(getche());
        }

  return respuesta;
}

/** \brief devolver numero random float //////////arreglar!!!!!!!
 * \param
 * \param
 * \return
 *
 */

float devolverPuntaje()
{
    float random;
    srand(time(NULL));
    random = (rand()%11)+1;
    return random;

}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
int guardarEnArchivo(EMovie peliculas [], int cantidad)
 {
	FILE *pelis;
	int i=0;
	int j;

		pelis=fopen("BaseDePeliculas.data","wb");
		if(pelis== NULL)
		{
       return 1;
		}
        else
        {
        while(i<=cantidad)
        {
            fwrite(&peliculas[i] ,sizeof(EMovie),1,pelis);
            i++;
        }

        }

    fclose(pelis);
       return 0;
        }


/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
int guardarArchivoABM (EMovie peliculas [], int cantidad)
{
    char guardar;

            guardar=preguntarSiNo("\nDesea guardar los cambios realizados?");
            if (guardar == 's')
            {
                if(guardarEnArchivo(peliculas,cantidad))
                {
                printf("\nNo se pudo abrir el fichero\n");
                }
                else
                {
                cantidad=0;
                }
            }
            else
            {
            printf("-------------------------------\n");
            printf("Operacion Cancelada\n");
            printf("-------------------------------\n");
            }

            cleanScreen();


        return cantidad;
}


/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
int cargarDesdeArchivo(EMovie peliculas[], int cantidad)
{
	FILE *pelis;
	int i=0;
	int flag = 0;

	pelis=fopen("BaseDePeliculas.data", "rb");
    if(pelis==NULL)
    {
        pelis= fopen("BaseDePeliculas.data", "wb");
        if(pelis==NULL)
        {
        return 1;
        }
        flag=1;
        }

	if(flag==0)
	{
        while(feof(pelis)==0 && i<cantidad)
        {
        fread(&peliculas[i],sizeof(EMovie),1,pelis);
        i++;
        }
    }

	fclose(pelis);
	return 0;

}

////////////////////////////////////////

int buscarLibre(EMovie peliculas[], int cantidad)
{
	int index=-1;
	int i;
	for( i=0; i < cantidad; i++)
	   if(peliculas[i].estado==0)
        {
		index=i;
		break;
	   }
	return index;
}


////////////////
int contadorArray (EMovie peliculas [], int tamanio)
{
    int i;
    int contador=0;
    for (i=0; i<tamanio; i++)
    {
        if ( peliculas[i].estado==1)
        {
            contador ++;
        }
    }

    return contador;
}
///////////////////////
void pedirTitulo (EMovie peliculas[], int posicion, int cantTexto)
{
    char titulo [100];
    char auxtitulo [20];
    int i;
    int flag =0;

    printf("\n \nIngrese El Titulo\t");
    fflush(stdin);
    gets (titulo);
        for (i=0; i<cantTexto; i++)
        {
            auxtitulo[i]=titulo[i];
        }
    strcpy(peliculas[posicion].titulo, auxtitulo);
}

void pedirGenero (EMovie pelicula[], int i)
{
    int auxGenero;
    printf("\n----------------------\n");
    printf("Ingrese El Genero\n");
    printf("----------------------");
    printf("\n 1- Terror\t");
    printf("\n 2- Comedia\t");
    printf("\n 3- Drama\t");
    printf("\n 4- Dibujos Animados\t");
    printf("\n 5- Accion\t");
    printf("\n 6- Ciencia Ficcion\t");
    printf("\n 7- Otro\t");
      do {
    fflush(stdin);
    printf("\n \nSeleccione la opcion deseada\t");
    scanf("%d", &auxGenero);

                switch (auxGenero)
                {
                case 1:
                    strcpy(pelicula[i].genero, "Terror");
                    break;
                case 2:
                    strcpy(pelicula[i].genero, "Comedia");
                    break;
                case 3:
                    strcpy(pelicula[i].genero, "Drama");
                    break;
                case 4:
                    strcpy(pelicula[i].genero, "DA");
                    break;
                case 5:
                    strcpy(pelicula[i].genero, "Accion");
                    break;
                case 6:
                    strcpy(pelicula[i].genero, "CF");
                    break;
                case 7:
                    strcpy(pelicula[i].genero, "Otro");
                    break;
                case 8:
                    strcpy(pelicula[i].genero, "Otro");
                    break;
                default:
                    fflush(stdin);
                    printf("\n-----------------------------\n");
                    printf(" NO INGRESO UNA OPCION VALIDA\t");
                     printf("\n-----------------------------\n");
                    auxGenero=0;
                    break;
                }
    }while (auxGenero==0);

                    printf("\n-----------------------------\n");
                    printf("El genero es %s \t",pelicula[i].genero );
                    printf("\n-----------------------------\n");

}

  void asignarNombrehtml (EMovie pelicula [], int j, int lenLink)
  {
      char buffer [50];
      char aux [lenLink];
      int i;

      strcpy(buffer, pelicula[j].titulo);
      strcat(buffer,"-");
      strcat(buffer,pelicula[j].genero);

      for (i=0; i<lenLink-5; i++)
        {
            aux[i]=buffer[i];
        }

        strcat(aux,".html");


      strcpy(pelicula[j].nombreArchivo, aux);
      RemoveSpaces(pelicula[j].nombreArchivo);

     // printf("\nel nombre del archivo %s\t",pelicula[j].nombreArchivo);

 }


void pedirDescripcion(EMovie pelicula [], int j, int lenDescrip)
  {
      char buffer [1500];
      char aux [lenDescrip];
      int i;

       printf("Ingrese Descripcion\t");
       fflush(stdin);
       gets(buffer);

      for (i=0; i<lenDescrip; i++)
        {
            aux[i]=buffer[i];
        }

      strcpy(pelicula[j].descripcion, aux);

    //  printf("\nla descripcioon es  %s\t\n",pelicula[j].descripcion);

 }


void pedirLink(EMovie pelicula [], int j, int lenLink)
  {
      char buffer [1500];
      char aux [lenLink];
      int i;

     printf("Ingrese URL\t");
     fflush(stdin);
     gets(buffer);

      for (i=0; i<lenLink; i++)
        {
            aux[i]=buffer[i];
        }

      strcpy(pelicula[j].linkImagen, aux);

 //     printf("\nel link  es  %s\t\n",pelicula[j].linkImagen);

 }


