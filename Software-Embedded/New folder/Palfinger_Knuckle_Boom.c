/*
 * File:   Palfinger_Knuckle_Boom.c
 * Author: Nitin Shankar
 *
 * Created on 7 January, 2022, 11:59 AM
 */

#include "main.h"


void Process_Len_Angle_Data_Palfinger_Knuckle(void)
{
    uint16_t BmCntrLineOfst=0;
    
    TempDispBoomAngle = (bm_angle/10);
    BoomLength_BmTip = (bm_length/10);
    DispBoomAngle1= (bm_angle/10.0);
    BmCntrLineOfst=sys.para.bm_cntr_line_offset;
    
    //=================================================
    // K.Sin(Q) + Sin(G) ......		
    f1 = sin((DispBoomAngle1)*DEG_TO_RAD);
    DispSinQ = (f1*1000);	// Test_Para
    
    f1 = ((constK_Int/1000.0)*(f1));
    f1 = (f1 + (sin_Gamma_Int/1000.0));
    
     //=================================================
    // K.Cos(Q) - Cos(G) ......
    
    f2 = cos((DispBoomAngle1)*DEG_TO_RAD);
    DispCosQ = (f2*1000);	// Test_Para 
    f2 = ((constK_Int/1000.0)*(f2));
    
    
    //=================================================
    // If this Step is not done then a -ve angle is generated in some cases.
    if((f2 > (cos_Gamma_Int/1000.0)))
    {
        f2 = (f2 - (cos_Gamma_Int/1000.0));

        Alpha_Float = atan(f1/f2);
        Alpha_Float = (Alpha_Float*RAD_TO_DEG*10); 	

        Alpha_Int = (unsigned int)(Alpha_Float);
        if((Alpha_Float - Alpha_Int) > 0.5) 
        {
            Alpha_Int++; 
        }
    }
    else
    {
        f2 = ((cos_Gamma_Int/1000.0) - f2);

        Alpha_Float = atan(f1/f2);
        Alpha_Float = (Alpha_Float*RAD_TO_DEG*10);
        Alpha_Float = (1800 - Alpha_Float); 	

        Alpha_Int = (unsigned int)(Alpha_Float);
        if((Alpha_Float - Alpha_Int) > 0.5) 
        {
            Alpha_Int++;
        }			
    }
    
    //=======================================================	
    // Beta = (Alpha - Theta) .....

    if((Alpha_Int) >= (DispBoomAngle1*10))
    {
        Beta_Int = ((Alpha_Int) - (DispBoomAngle1*10)); 	// IN DEGREES .......

    }
    else
    {
        Beta_Int = ((DispBoomAngle1*10) - (Alpha_Int)); 	// IN DEGREES .......

    }		
    //=======================================================	
    // C * Sin(B) .......

    if(DispBoomAngle1 < 47)
    {
        f2 = (BmCntrLineOfst/1000.0)*(tan((DispBoomAngle1)*(DEG_TO_RAD)));
    }
    else if((47 <= DispBoomAngle1)&&(DispBoomAngle1 < 53))
    {
        f2 = (BmCntrLineOfst/1000.0)*(tan((DispBoomAngle1-5)*(DEG_TO_RAD)));
    }
    else if((53 <= DispBoomAngle1)&&(DispBoomAngle1 < 65))
    {
        f2 = (BmCntrLineOfst/1000.0)*(tan((DispBoomAngle1-15)*(DEG_TO_RAD)));
    }
    else if((65 <= DispBoomAngle1)&&(DispBoomAngle1 < 77))
    {
        f2 = (BmCntrLineOfst/1000.0)*(tan((DispBoomAngle1-40)*(DEG_TO_RAD)));
    }
    else 
    {
        f2 = (BmCntrLineOfst/1000.0)*(tan((DispBoomAngle1-45)*(DEG_TO_RAD)));
    }

    if(sys.para.num_cal == 0)  
    {
        f1 = ((sys.para.rampivot_offset/1000.0)+ (f2));	//*(sin(((Beta_Int/10.0)*DEG_TO_RAD)));	// Deg To Rad		
    }
    else
    {
        f1 = ((sys.para.rampivot_offset/1000.0));
    }
    f1 = ((f1)*(sin((Beta_Int/10.0)*DEG_TO_RAD)));
    //f1 = (RamPivotOfst/1000.0)*(sin((Beta_Int/10.0)*DEG_TO_RAD));	// Deg To Rad
    Num_Float = f1;
    Num_Int = (uint16_t)(f1*1000);  	

    //==========================================================================		
     ActualPickingLength = TotalBmLength;	
    //==========================================================================
    // L * Cos(Q) ......

//    if(DispBoomAngle1 > 7)
//    {
//        TempoAngle = DispBoomAngle1-7;
//    }
//    RAD = cosangle1[TempoAngle*10];
//    Radius = (float) ( ActualPickingLength-JibLength) * RAD;
//    
//    if(JibLength > 0)
//    {
//        Alpha2 =0;
//        Alpha1 = cosangle1[DispBoomAngle1*10];
//        Alpha2 = (float)(JibLength) * Alpha1;
//    }
//
//    Radius1 = (uint16_t) (Radius + Alpha2);
    
    f2 = Radius1;	
    f2 = (f2/10.0);  
    Den_Float = f2;
    Den_Int = (uint16_t)(f2*1000);
}
	