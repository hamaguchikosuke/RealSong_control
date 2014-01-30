#ifndef __f14tmp1_XPCOPTIONS_H___
#define __f14tmp1_XPCOPTIONS_H___
#include "simstruc_types.h"
#ifndef MT
#define MT                             0                         /* MT may be undefined by simstruc_types.h */
#endif

#include "f14tmp1.h"
#define XPCMDSSUPPORT                  0
#define MDSTASKSNUM                    0
#define FULLMULTITHREAD                0
#define SIZEOF_PARAMS                  (-1 * (int)sizeof(Parameters_f14tmp1))
#define SIMMODE                        0
#define LOGTET                         0
#define LOGBUFSIZE                     100000
#define PROFILINGFLAG                  0
#define EVENTNUMBER                    5000
#define IRQ_NO                         0
#define IO_IRQ                         0
#define WWW_ACCESS_LEVEL               0
#define CPUCLOCK                       0
#define MAXOVERLOAD                    0
#define MAXOVERLOADLEN                 0
#define XPCMODELSTACKSIZEKB            64
#define XPCSTARTUPFLAG                 1
#define PTLOADPARAMFLAG                0

/* Change all stepsize using the newBaseRateStepSize */
void f14tmp1_ChangeStepSize(real_T newBaseRateStepSize, rtModel_f14tmp1 *const
  f14tmp1_rtM)
{
  real_T ratio = newBaseRateStepSize / 0.01;

  /* update non-zore stepsize of periodic
   * sample time. Stepsize of asynchronous
   * sample time is not changed in this function */
  f14tmp1_rtM->Timing.stepSize0 = f14tmp1_rtM->Timing.stepSize0 * ratio;
  f14tmp1_rtM->Timing.stepSize1 = f14tmp1_rtM->Timing.stepSize1 * ratio;
  f14tmp1_rtM->Timing.stepSize2 = f14tmp1_rtM->Timing.stepSize2 * ratio;
  f14tmp1_rtM->Timing.stepSize = f14tmp1_rtM->Timing.stepSize * ratio;
}

void XPCCALLCONV changeStepSize(real_T stepSize)
{
  /* Change all stepsize using the newBaseRateStepSize */
  f14tmp1_ChangeStepSize(stepSize, f14tmp1_rtM);
}

#endif                                 /* __f14tmp1_XPCOPTIONS_H___ */
