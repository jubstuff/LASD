/*=============================================================================
 *
 * Nome File: provaGraph.c
 *
 * Scopo: Testare varie possibilità per le strutture dati per grafi
 *
 * Data Creazione: 15-05-2011
 *
 * Ultima Modifica: lun 16 mag 2011 00:37:25 CEST
 *
 * Autore: Giustino Borzacchiello - giustinob@gmail.com
 *
 *
 =============================================================================*/
    #include <stdlib.h>
    #include <stdio.h>
    #include <time.h>
    #define DIM 4
    
    void DeactivateVertex( int *Vertices, int DeactivatedVertex, int DimSetVertices );
    void PrintMatrix( int *Mat, int *Vertices, int NumVertici, int DimSetVertices);
    
    int main(void)
    {
    	int i, j;
    	int *Mat = malloc( DIM * DIM * sizeof(int) );
    	int *Vertices = malloc(DIM * sizeof(int) );
    	int *TempVertici = NULL;
    	int *TempMat = NULL;
    
    	int NumVertici = DIM;
    	int DimSetVertices = DIM;
    
    	srand(time(NULL));
    
    	//Initialize matrix with values from 1 to NumVertici
    	for( i = 0; i < NumVertici * NumVertici; i++ )
    	{
    		Mat[i] = i+1;
    	}
    	//Initialize vertices set
    	for( i = 0; i < NumVertici; i++ )
    	{
    		Vertices[i] = i;
    	}
        /*
    	 * Vertices 
    	 * _0_1_2_3_ 
    	 * |0_1_2_3|
    	 *
    	 * Mat
    	 *  _0_1_2_3_
    	 * 0|1 2 3 4 
    	 * 1|5 6 7 8 
    	 * 2|9 10 11 12 
    	 * 3|13 14 15 16 
    	 *
    	 *
    	 * */
    	PrintMatrix( Mat, Vertices, NumVertici, DimSetVertices );
    
    	// "Delete" vertices 1 and 2
    	DeactivateVertex( Vertices, 2, DimSetVertices );
    	NumVertici--;
    	DeactivateVertex( Vertices, 1, DimSetVertices );
    	NumVertici--;
        /*
    	 * Vertices 
    	 * _0_1_2_3_ 
    	 * |0_3_ _ |
    	 *
    	 * Mat
    	 *  _0_1_2_3_
    	 * 0|1 2 3 4 
    	 * 1|5 6 7 8 
    	 * 2|9 10 11 12 
    	 * 3|13 14 15 16 
         */
    	PrintMatrix( Mat, Vertices, NumVertici, DimSetVertices );
    
    	//Memory cleanup: this will be done periodically
    	printf("Memory Cleanup\n");
    
    	TempMat = malloc( NumVertici * NumVertici * sizeof(int) );
    	for( i = 0; i < NumVertici; i++ )
    	{
    		for( j = 0; j < NumVertici; j++ )
    		{
    			TempMat[i * NumVertici + j] = Mat[ Vertices[i] * DimSetVertices + Vertices[j] ];
    		}
    	}
    	free( Mat );
    	Mat = TempMat;
    	TempMat = NULL;
    	
    	TempVertici = realloc( Vertices, NumVertici * sizeof(int) );
    	if( TempVertici != NULL )
    	{
    		Vertices = TempVertici;
    	}
    	for( i = 0; i < NumVertici; i++ )
    	{
    		Vertices[i] = i;
    	}
    	TempVertici = NULL;
    	DimSetVertices = NumVertici;
        /*
    	 * Vertices 
    	 * _0_1_ 
    	 * |0_1_|
    	 *
    	 * Mat
    	 *  _0__1_
    	 * 0|1  4 
    	 * 1|13 16 
         */
    
    	PrintMatrix( Mat, Vertices, NumVertici, DimSetVertices );
    
    	free( Mat );
    	free( Vertices );
    	return 0;
    }   /* main */
    /**
     * Mat => Puntatore alla matrice di adiacenza
     * Vertices => Array contenente gli indici dei vertici "attivi"
     * NumVertici => Numero di vertici attivi
     * DimSetVertices => Dimensione iniziale dell'insieme dei vertici
     * */
    void PrintMatrix( int *Mat, int *Vertices, int NumVertici, int DimSetVertices)
    {
    	int i, j;
    
    	for( i = 0; i < NumVertici; i++ )
    	{
    		for( j = 0; j < NumVertici; j++ )
    		{
    			printf( "%d ", Mat[ Vertices[i] * DimSetVertices + Vertices[j] ] );
    		}
    		printf("\n");
    	}	
    }
    
    void DeactivateVertex( int *Vertices, int DeactivatedVertex, int DimSetVertices )
    {
    	int i;
    	printf("Delete vertex %d\n", DeactivatedVertex);
    	for( i = DeactivatedVertex; i < DimSetVertices-1; i++ )
    	{
    		Vertices[i] = Vertices[i+1];
    	}
    }
