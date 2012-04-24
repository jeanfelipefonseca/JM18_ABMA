
/*!
 *************************************************************************************
 * \file sobel.h
 *
 * \brief
 *    header file of the Filter to calculate the Sobel´s gradient
 *    
 *
 * \author
 *    Contributors:
 *		- Jean Felipe        Original code              31/03/2012    
  *************************************************************************************
 */
#include "global.h"

#define MAX_BRIGHTNESS  255 /* Maximum gray level */

extern void CalculateSobelGradient(VideoParameters *p_Vid, imgpel **imgY, imgpel ***imgUV);
extern void SobelFiltering(VideoParameters *p_Vid, imgpel **imgY, imgpel ***imgUV, int MbQAddr);