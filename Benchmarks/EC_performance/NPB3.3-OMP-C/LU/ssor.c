//-------------------------------------------------------------------------//
//                                                                         //
//  This benchmark is an OpenMP C version of the NPB LU code. This OpenMP  //
//  C version is developed by the Center for Manycore Programming at Seoul //
//  National University and derived from the OpenMP Fortran versions in    //
//  "NPB3.3-OMP" developed by NAS.                                         //
//                                                                         //
//  Permission to use, copy, distribute and modify this software for any   //
//  purpose with or without fee is hereby granted. This software is        //
//  provided "as is" without express or implied warranty.                  //
//                                                                         //
//  Information on NPB 3.3, including the technical report, the original   //
//  specifications, source code, results and information on how to submit  //
//  new results, is available at:                                          //
//                                                                         //
//           http://www.nas.nasa.gov/Software/NPB/                         //
//                                                                         //
//  Send comments or suggestions for this OpenMP C version to              //
//  cmp@aces.snu.ac.kr                                                     //
//                                                                         //
//          Center for Manycore Programming                                //
//          School of Computer Science and Engineering                     //
//          Seoul National University                                      //
//          Seoul 151-744, Korea                                           //
//                                                                         //
//          E-mail:  cmp@aces.snu.ac.kr                                    //
//                                                                         //
//-------------------------------------------------------------------------//

//-------------------------------------------------------------------------//
// Authors: Sangmin Seo, Jungwon Kim, Jun Lee, Jeongho Nah, Gangwon Jo,    //
//          and Jaejin Lee                                                 //
//-------------------------------------------------------------------------//

#include <stdio.h>
#ifdef _OPENMP
#include <omp.h>
#endif
#include "applu.incl"
#include "timers.h"

//---------------------------------------------------------------------
// Thread synchronization for pipeline operation
//---------------------------------------------------------------------
/* common /threadinfo1/ */
int isync[ISIZ2+1];
/* common /threadinfo2/ */
int mthreadnum, iam;
#pragma omp threadprivate(mthreadnum,iam)


//---------------------------------------------------------------------
// to perform pseudo-time stepping SSOR iterations
// for five nonlinear pde's.
//---------------------------------------------------------------------
void ssor(int niter)
{

          //kai
 // int k1,k2,k3,k4;
 // consistent_data(&k1, "int", 1);
//  consistent_data(&k2, "int", 1);
 // consistent_data(&k3, "int", 1);
//  consistent_data(&k4, "int", 1);


  //---------------------------------------------------------------------
  // local variables
  //---------------------------------------------------------------------
  int i, j, k, m, n;
  int istep;
  double tmp, tmp2, tv[ISIZ2][ISIZ1][5];
  double delunm[5];
//kai
	  consistent_data(&istep, "int", 1);

  //---------------------------------------------------------------------
  // begin pseudo-time stepping iterations
  //---------------------------------------------------------------------
  tmp = 1.0 / ( omega * ( 2.0 - omega ) );

  //---------------------------------------------------------------------
  // initialize a,b,c,d to zero (guarantees that page tables have been
  // formed, if applicable on given architecture, before timestepping).
  //---------------------------------------------------------------------
  #pragma omp parallel default(shared) private(m,n,i,j)
  {
  #pragma omp for nowait
  for (j = jst; j < jend; j++) {
    for (i = ist; i < iend; i++) {
      for (n = 0; n < 5; n++) {
        for (m = 0; m < 5; m++) {
          a[j][i][n][m] = 0.0;
          b[j][i][n][m] = 0.0;
          c[j][i][n][m] = 0.0;
          d[j][i][n][m] = 0.0;
        }
      }
    }
  }
  #pragma omp for nowait
  for (j = jend - 1; j >= jst; j--) {
    for (i = iend - 1; i >= ist; i--) {
      for (n = 0; n < 5; n++) {
        for (m = 0; m < 5; m++) {
          au[j][i][n][m] = 0.0;
          bu[j][i][n][m] = 0.0;
          cu[j][i][n][m] = 0.0;
          du[j][i][n][m] = 0.0;
        }
      }
    }
  }
  } //end parallel
  for (i = 1; i <= t_last; i++) {
    timer_clear(i);
  }

  //---------------------------------------------------------------------
  // compute the steady-state residuals
  //---------------------------------------------------------------------
  rhs();

  //---------------------------------------------------------------------
  // compute the L2 norms of newton iteration residuals
  //---------------------------------------------------------------------
  l2norm( ISIZ1, ISIZ2, ISIZ3, nx0, ny0, nz0,
          ist, iend, jst, jend, rsd, rsdnm );

  for (i = 1; i <= t_last; i++) {
    timer_clear(i);
  }
  timer_start(1);

	//kai
	if (niter > 1) {
                flush_whole_cache();
		//start_crash();
	}
  //---------------------------------------------------------------------
  // the timestep loop
  //---------------------------------------------------------------------
  for (istep = 1; istep <= niter; istep++) {
    if ((istep % 20) == 0 || istep == itmax || istep == 1) {
      if (niter > 1) printf(" Time step %4d\n", istep);
    }
    //if(istep == 5)
    //   start_crash();
    //if(istep == 11)
    //   end_crash();

    //---------------------------------------------------------------------
    // perform SSOR iteration
    //---------------------------------------------------------------------
    #pragma omp parallel default(shared) private(i,j,k,m,tmp2) \
                shared(ist,iend,jst,jend,nx,ny,nz,nx0,ny0,omega)
    {
    #pragma omp master
    if (timeron) timer_start(t_rhs);
    tmp2 = dt;
    #pragma omp for nowait
    for (k = 1; k < nz - 1; k++) {
      for (j = jst; j < jend; j++) {
        for (i = ist; i < iend; i++) {
          for (m = 0; m < 5; m++) {
            rsd[k][j][i][m] = tmp2 * rsd[k][j][i][m];
          }
        }
      }
	//kai
	k1 = k;
    }
    #pragma omp master
    if (timeron) timer_stop(t_rhs);

    mthreadnum = 0;
    mthreadnum = omp_get_num_threads() - 1;
    if (mthreadnum > jend - jst) mthreadnum = jend - jst;
    iam = 0;
    iam = omp_get_thread_num();
    if (iam <= mthreadnum) isync[iam] = 0;
    #pragma omp barrier

    for (k = 1; k < nz -1; k++) {
      //---------------------------------------------------------------------
      // form the lower triangular part of the jacobian matrix
      //---------------------------------------------------------------------
      #pragma omp master
      if (timeron) timer_start(t_jacld);
      jacld(k);
      #pragma omp master
      {
      if (timeron) timer_stop(t_jacld);

      //---------------------------------------------------------------------
      // perform the lower triangular solution
      //---------------------------------------------------------------------
      if (timeron) timer_start(t_blts);
      }
      blts( ISIZ1, ISIZ2, ISIZ3,
            nx, ny, nz, k,
            omega,
            rsd,
            a, b, c, d,
            ist, iend, jst, jend,
            nx0, ny0 );
      #pragma omp master
      if (timeron) timer_stop(t_blts);
      //kai
	k2 = k;
	if(k2 == 30 && istep == 55)
        {
           FILE *file;
           file = fopen("checkpoint.txt","w");
           int iteration1=0,iteration2=0,iteration3=0,iteration4=0;
           for(iteration1=0; iteration1<ISIZ2;iteration1++)
           {
                for(iteration2 = 0; iteration2<ISIZ1/2*2+1; iteration2++)
                    for(iteration3 = 0; iteration3<5; iteration3++)
                        for(iteration4 = 0; iteration4<5; iteration4++)
                                fprintf(file,"%20.12E\n",a[iteration1][iteration2][iteration3][iteration4]);
                }
           for(iteration1=0; iteration1<ISIZ2;iteration1++)
           {
                for(iteration2 = 0; iteration2<ISIZ1/2*2+1; iteration2++)
                    for(iteration3 = 0; iteration3<5; iteration3++)
                        for(iteration4 = 0; iteration4<5; iteration4++)
                                fprintf(file,"%20.12E\n",b[iteration1][iteration2][iteration3][iteration4]);
                }
	for(iteration1=0; iteration1<ISIZ2;iteration1++)
           {
                for(iteration2 = 0; iteration2<ISIZ1/2*2+1; iteration2++)
                    for(iteration3 = 0; iteration3<5; iteration3++)
                        for(iteration4 = 0; iteration4<5; iteration4++)
                                fprintf(file,"%20.12E\n",c[iteration1][iteration2][iteration3][iteration4]);
                }
	for(iteration1=0; iteration1<ISIZ2;iteration1++)
           {
                for(iteration2 = 0; iteration2<ISIZ1/2*2+1; iteration2++)
                    for(iteration3 = 0; iteration3<5; iteration3++)
                        for(iteration4 = 0; iteration4<5; iteration4++)
                                fprintf(file,"%20.12E\n",d[iteration1][iteration2][iteration3][iteration4]);
                }
           fclose(file);
        }
    }
    #pragma omp barrier

    for (k = nz - 2; k > 0; k--) {
      //---------------------------------------------------------------------
      // form the strictly upper triangular part of the jacobian matrix
      //---------------------------------------------------------------------
      #pragma omp master
      if (timeron) timer_start(t_jacu);
      jacu(k);
      #pragma omp master
      {
      if (timeron) timer_stop(t_jacu);

      //---------------------------------------------------------------------
      // perform the upper triangular solution
      //---------------------------------------------------------------------
      if (timeron) timer_start(t_buts);
      }
      buts( ISIZ1, ISIZ2, ISIZ3,
            nx, ny, nz, k,
            omega,
            rsd, tv,
            du, au, bu, cu,
            ist, iend, jst, jend,
            nx0, ny0 );
      #pragma omp master
      if (timeron) timer_stop(t_buts);
      //kai
	    k3 = k;
/*       if(k3 == 30 && istep == 55)
	{
	   FILE *file;
           file = fopen("checkpoint.txt","w");
           int iteration1=0,iteration2=0,iteration3=0,iteration4=0;
           for(iteration1=0; iteration1<ISIZ3;iteration1++)
	   {
		for(iteration2 = 0; iteration2<ISIZ2/2*2+1; iteration2++)
                    for(iteration3 = 0; iteration3<ISIZ1/2*2+1; iteration3++)
			for(iteration4 = 0; iteration4<5; iteration4++)
				fprintf(file,"%20.12E\n",rsd[iteration1][iteration2][iteration3][iteration4]);
		}
           fclose(file);
	}*/
    }
    #pragma omp barrier

    //---------------------------------------------------------------------
    // update the variables
    //---------------------------------------------------------------------
    #pragma omp master
    if (timeron) timer_start(t_add);
    tmp2 = tmp;
    #pragma omp for nowait
    for (k = 1; k < nz-1; k++) {
      for (j = jst; j < jend; j++) {
        for (i = ist; i < iend; i++) {
          for (m = 0; m < 5; m++) {
            u[k][j][i][m] = u[k][j][i][m] + tmp2 * rsd[k][j][i][m];
          }
        }
      }
	//kai
	k4 = k;
    }
    } //end parallel
    if (timeron) timer_stop(t_add);

    //---------------------------------------------------------------------
    // compute the max-norms of newton iteration corrections
    //---------------------------------------------------------------------
    if ( (istep % inorm) == 0 ) {
      if (timeron) timer_start(t_l2norm);
      l2norm( ISIZ1, ISIZ2, ISIZ3, nx0, ny0, nz0,
              ist, iend, jst, jend,
              rsd, delunm );
      if (timeron) timer_stop(t_l2norm);
      /*
      if ( ipr == 1 ) {
        printf(" \n RMS-norm of SSOR-iteration correction "
               "for first pde  = %12.5E\n"
               " RMS-norm of SSOR-iteration correction "
               "for second pde = %12.5E\n"
               " RMS-norm of SSOR-iteration correction "
               "for third pde  = %12.5E\n"
               " RMS-norm of SSOR-iteration correction "
               "for fourth pde = %12.5E\n",
               " RMS-norm of SSOR-iteration correction "
               "for fifth pde  = %12.5E\n",
               delunm[0], delunm[1], delunm[2], delunm[3], delunm[4]);
      } else if ( ipr == 2 ) {
        printf("(%5d,%15.6f)\n", istep, delunm[4]);
      }
      */
    }

    //---------------------------------------------------------------------
    // compute the steady-state residuals
    //---------------------------------------------------------------------
    rhs();

    //---------------------------------------------------------------------
    // compute the max-norms of newton iteration residuals
    //---------------------------------------------------------------------
    if ( ((istep % inorm ) == 0 ) || ( istep == itmax ) ) {
      if (timeron) timer_start(t_l2norm);
      l2norm( ISIZ1, ISIZ2, ISIZ3, nx0, ny0, nz0,
              ist, iend, jst, jend, rsd, rsdnm );
      if (timeron) timer_stop(t_l2norm);
      /*
      if ( ipr == 1 ) {
        printf(" \n RMS-norm of steady-state residual for "
               "first pde  = %12.5E\n"
               " RMS-norm of steady-state residual for "
               "second pde = %12.5E\n"
               " RMS-norm of steady-state residual for "
               "third pde  = %12.5E\n"
               " RMS-norm of steady-state residual for "
               "fourth pde = %12.5E\n"
               " RMS-norm of steady-state residual for "
               "fifth pde  = %12.5E\n",
               rsdnm[0], rsdnm[1], rsdnm[2], rsdnm[3], rsdnm[4]);
      }
      */
    }

    //---------------------------------------------------------------------
    // check the newton-iteration residuals against the tolerance levels
    //---------------------------------------------------------------------
    if ( ( rsdnm[0] < tolrsd[0] ) && ( rsdnm[1] < tolrsd[1] ) &&
         ( rsdnm[2] < tolrsd[2] ) && ( rsdnm[3] < tolrsd[3] ) &&
         ( rsdnm[4] < tolrsd[4] ) ) {
      //if (ipr == 1 ) {
      printf(" \n convergence was achieved after %4d pseudo-time steps\n",
          istep);
      //}
      break;
    }
    maxtime = timer_read(1);
 /*   //EasyCrash: candidates of critical data obj: u, rsd, frct, gs, rho\_i, rsdnm, a, b, c, d, au, bu, cu, du
    //EasyCrash: critical data objs: u
    //checkpointing:
    checkpoint(u, ISIZ3*(ISIZ2/2*2+1)*(ISIZ1/2*2+1)*5*sizeof(double));
    checkpoint(rsd, sizeof(double)*ISIZ3*(ISIZ2/2*2+1)*(ISIZ1/2*2+1)*5);
    checkpoint(frct, sizeof(double)*ISIZ3*(ISIZ2/2*2+1)*(ISIZ1/2*2+1)*5);
    checkpoint(qs, ISIZ3*(ISIZ2/2*2+1)*(ISIZ1/2*2+1)*5*sizeof(double));
    checkpoint(rho_i, ISIZ3*(ISIZ2/2*2+1)*(ISIZ1/2*2+1)*5*sizeof(double));
    checkpoint(rsdnm, 5*sizeof(double));
    checkpoint(a, ISIZ2*(ISIZ1/2*2+1)*5*5*sizeof(double));
    checkpoint(b, ISIZ2*(ISIZ1/2*2+1)*5*5*sizeof(double));
    checkpoint(c, ISIZ2*(ISIZ1/2*2+1)*5*5*sizeof(double));
    checkpoint(d, ISIZ2*(ISIZ1/2*2+1)*5*5*sizeof(double));
    checkpoint(au,ISIZ2*(ISIZ1/2*2+1)*5*5*sizeof(double));
    checkpoint(bu,ISIZ2*(ISIZ1/2*2+1)*5*5*sizeof(double));
    checkpoint(cu,ISIZ2*(ISIZ1/2*2+1)*5*5*sizeof(double));
    checkpoint(du,ISIZ2*(ISIZ1/2*2+1)*5*5*sizeof(double));

  */
// /*    //EC:
    EC(u, ISIZ3*(ISIZ2/2*2+1)*(ISIZ1/2*2+1)*5*sizeof(double));
//  */

  }
	//kai
	//if (niter > 1) {
	//	end_crash();
	//}
  timer_stop(1);
  maxtime = timer_read(1);
}
