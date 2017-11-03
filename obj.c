#include "obj.h"

/* Faz uso de todas as informações listadas em VertInfo para alocar e   /
** preencher um vetor de vértices tridimensionais. VertInfo é esvaziada /
** no processo                                                         */

void getRawVerts(obj_t Obj)
{
    cell_t *Cell = Obj.VertInfo.First;
    char *ptr, X[MAXFLOATSIZE], Y[MAXFLOATSIZE], Z[MAXFLOATSIZE];
    unsigned short i = 2, j, k = 0;

    Obj.RawVerts = Malloc(sizeof(threeD_t) * Obj.VertInfo.Length);

    while (Cell)
    {
        ptr = (char *) Cell->Item;

        j = 0;
        while (ptr[i] != ' ')
        {
            X[j] = ptr[i];
            i++;
            j++;
        }
        X[j] = '\0';
        i++;

        j = 0;
        while (ptr[i] != ' ')
        {
            Y[j] = ptr[i];
            i++;
            j++;
        }
        Y[j] = '\0';
        i++;

        j = 0;
        while (ptr[i] != ' ' && ptr[i] !=  '\n')
        {
            Z[j] = ptr[i];
            i++;
            j++;
        }
        Z[j] = '\0';

        free(ptr);

        Obj.RawVerts[k].x = atof(X);
        Obj.RawVerts[k].y = atof(Y);
        Obj.RawVerts[k].z = atof(Z);

        k++;

        removeCell(&Obj.VertInfo);
        Cell = Obj.VertInfo.First;
    }

    Obj.VertInfo.Last = NULL;

    // Isso deveria ir em outro lugar...
    Obj.ProjVerts = Malloc(sizeof(twoD_t) * Obj.VertInfo.Length);
}

/***********************************************************************/

/* Aplica o cálculo de perspectiva, gerando um vetor de vértices bidimensionais /
** a partir do vetor de vértices tridimensionais                               */

void getProjVerts(obj_t Obj, threeD_t Cam)
{
    for (unsigned int i = 0; i < Obj.VertInfo.Length; i++)
    {
        Obj.ProjVerts[i].x = Cam.x + Cam.z * ((Obj.RawVerts[i].x - Cam.x) / (Obj.RawVerts[i].z + Cam.z));
        Obj.ProjVerts[i].y = Cam.y + Cam.z * ((Obj.RawVerts[i].y - Cam.y) / (Obj.RawVerts[i].z + Cam.z));
    }
}

/*******************************************************************************/