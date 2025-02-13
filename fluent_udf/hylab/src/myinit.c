/*
* =====================================================================================
*
*       Filename:  myinit.c
*
*    Description:  UDF for initialization
*
*        Version:  1.0
*        Created:  2010-2-23 12:01:23
*       Revision:  none
*       Compiler:  gcc/msc
*
*         Author:  huys (hys), huys03@gmail.com
*        Company:  hu
*
* =====================================================================================
*/

#include "udf.h"

/***********************************************************************
UDF for initializing flow field variables
************************************************************************/
DEFINE_INIT(my_init_func, dom)
{
    cell_t c;
    Thread *t;
    real xc[ND_ND];
    real d;
    
    /* loop over all cell threads in the domain  */
    thread_loop_c(t,dom)
    {
        /* loop over all cells  */
        begin_c_loop_all(c,t)
        {
            C_CENTROID(xc,c,t);
            
            d = sqrt(ND_SUM(pow(xc[0] - 0.5, 2.), pow(xc[1] - 0.5,2.), pow(xc[2] - 0.5,2.)));
            
            if ( d < 0.25)
                C_T(c,t) = 400.;
            else
                C_T(c,t) = 300.;
        }
        end_c_loop_all(c,t)
    }
}

/* Initialize solid cells' temperature */
DEFINE_INIT(my_init_temperature, d)
{
    cell_t c;
    Thread *t;
    real xc[ND_ND];

    thread_loop_c(t,d)
    {
        if (!FLUID_THREAD_P(t))
        /* if (9 == THREAD_ID(t)) */
        {
            /* loop over all cells  */
            begin_c_loop_all(c,t)
            {
                C_T(c,t) = 400.;
            }
            end_c_loop_all(c,t)
        }
    }
}
