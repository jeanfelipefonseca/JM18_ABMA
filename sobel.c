
/*!
 *************************************************************************************
 * \file sobel.c
 *
 * \brief
 *    Filter to calculate the Sobel´s gradient
 *    
 *
 * \author
 *    Contributors:
 *		- Jean Felipe        Original code              31/03/2012    
  *************************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <stdint.h>

#include "global.h"
#include "image.h"
#include "mb_access.h"
#include "sobel.h"

void CalculateSobelGradient(VideoParameters *p_Vid, imgpel **imgY, imgpel ***imgUV) {
  unsigned int i;
  //init_SobelFilter(p_Vid);
  //printf("---p_Vid->PicSizeInMbs = %d \n", p_Vid->PicSizeInMbs);
  for (i=0; i < p_Vid->PicSizeInMbs; i++)
  {
	printf("---------------------------- Macroblock = %d\n", i);
	SobelFiltering( p_Vid, imgY, imgUV, i ) ;
  }
}

void SobelFiltering(VideoParameters *p_Vid, imgpel **imgY, imgpel ***imgUV, int MbQAddr)
{
  /* Definition of Sobel filter in horizontal direction */
 // FILE *sobel_fp = fopen("sobel_matrix.txt", "a");	

  /*int weight[3][3] = {{ -1,  0,  1 },
			  { -2,  0,  2 },
			  { -1,  0,  1 }};*/
  //double pixel_value;
  //imgpel pixel_value;
  int64 min, max;
  int x, y, i, j, sumX, sumY, SUM;  /* Loop variable */

  Macroblock *MbQ = &(p_Vid->mb_data[MbQAddr]) ; // current Mb

  int GX[3][3];
  int GY[3][3];

  //Sobel Matrices Horizontal
  GX[0][0] = 1; GX[0][1] = 0; GX[0][2] = -1;
  GX[1][0] = 2; GX[1][1] = 0; GX[1][2] = -2;
  GX[2][0] = 1; GX[2][1] = 0; GX[2][2] = -1;

  //Sobel Matrices Vertical
  GY[0][0] =  1; GY[0][1] =    2; GY[0][2] =   1;
  GY[1][0] =  0; GY[1][1] =    0; GY[1][2] =   0;
  GY[2][0] = -1; GY[2][1] =   -2; GY[2][2] =  -1;

  printf("MbQ->pix_y = %d\n", MbQ->pix_y);
  printf("MbQ->pix_x = %d\n", MbQ->pix_x);
  printf("MbQ->mb_y = \n", MbQ->mb_y);
  printf("MbQ->mb_x = \n", MbQ->mb_x);
  
  /* Maximum values calculation after filtering*/
  printf("Now, filtering of input image is performed\n\n");
  min = INT64_MIN;
  max = INT64_MAX;
  
  //SUM = 0;
  
  for (y = MbQ->mb_y; y < MbQ->mb_y + 16; y++) {
	  for (x = MbQ->mb_x ; x < MbQ->mb_x + 16; x++) {
		sumX = 0;
		sumY = 0;
		//printf("imgY[y][x] =%d\n", imgY[y][x]);
		if (y == 0 || y == MbQ->mb_y + 15)
			SUM = 0;
		else if (x == 0 || x == MbQ->mb_x + 15)
			SUM = 0;
		else {
			for (j = -1; j <= 1; j++) {
				for (i = -1; i <= 1; i++) {
					sumX = sumX + GX[j+1][i+1] * imgY[y + j][x + i];
					//printf("sumX(%d) + GX[%d+1][%d+1](%d) * imgY[%d+%d][%d+%d](%d)\n",sumX, j, i, GX[j+1][i+1], y, j, x, i, imgY[y + j][x + i]);
				}
			}
			for (j = -1; j <= 1; j++) {
				for (i = -1; i <= 1; i++) {
					sumY = sumY + GY[j+1][i+1] * imgY[y + j][x + i];
				}
			}
			SUM = sqrt(pow((double)sumX,2) + pow((double)sumY,2));
		}
		if(SUM > 255) SUM = 255;	
		if(SUM < 0) SUM = 0;

		//printf("SUM = %f\n", SUM);
		p_Vid->imgData.frm_data[0][y][x] = (imgpel)SUM;
		
	}
  }
//  if ((int)(max - min) == 0) {
//    printf("Nothing exists!!!\n\n");
//    //exit(1);
//  }

  /* Initialization of image2[y][x] */
  //x_size2 = x_size1;
  //y_size2 = y_size1;
 // for (y = MbQ->pix_y; y < MbQ->pix_y + 16; y++) {
 //   for (x = MbQ->pix_x; x < MbQ->pix_x + 16; x++) {
 //     imgY[y][x] = 0;
 //   }
 // } 
 // /* Generation of image2 after linear transformtion */
 // for (y = MbQ->pix_y; y < MbQ->pix_y + 16; y++) {
 //   for (x = MbQ->pix_x; x < MbQ->pix_x + 16; x++) {
 //     pixel_value = 0;
 //     for (j = -1; j <= 1; j++) {
	//    for (i = -1; i <= 1; i++) {
	//      pixel_value += weight[j + 1][i + 1] * imgY[y + j][x + i];
	//    }
 //     }
 //     pixel_value = MAX_BRIGHTNESS * (pixel_value - min) / (max - min);
	//  printf("pixel_value = %d\n", pixel_value);
	//  p_Vid->imgData.frm_data[0][y][x] = (imgpel)pixel_value;
	//  fprintf(sobel_fp, "%d ", (int)p_Vid->imgData.frm_data[0][y][x]);
	//  //imgY[y][x] = (unsigned char)pixel_value = + 20;
 //   }
	//fprintf(sobel_fp, "\n");
 // }
 // fprintf(sobel_fp, "\n");
 // fclose(sobel_fp);
}


