/*
 * f14tmp5.h
 *
 * Code generation for model "f14tmp5".
 *
 * Model version              : 1.0
 * Simulink Coder version : 8.3 (R2012b) 20-Jul-2012
 * C source code generated on : Mon Sep 16 12:49:21 2013
 *
 * Target selection: xpctarget.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#ifndef RTW_HEADER_f14tmp5_h_
#define RTW_HEADER_f14tmp5_h_
#include "rtw_modelmap.h"
#ifndef f14tmp5_COMMON_INCLUDES_
# define f14tmp5_COMMON_INCLUDES_
#include <xpcdatatypes.h>
#include <math.h>
#include <stddef.h>
#include <string.h>
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "rt_logging.h"
#include "rtGetInf.h"
#include "rtGetNaN.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#endif                                 /* f14tmp5_COMMON_INCLUDES_ */

#include "f14tmp5_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetBlkStateChangeFlag
# define rtmGetBlkStateChangeFlag(rtm) ((rtm)->ModelData.blkStateChange)
#endif

#ifndef rtmSetBlkStateChangeFlag
# define rtmSetBlkStateChangeFlag(rtm, val) ((rtm)->ModelData.blkStateChange = (val))
#endif

#ifndef rtmGetBlockIO
# define rtmGetBlockIO(rtm)            ((rtm)->ModelData.blockIO)
#endif

#ifndef rtmSetBlockIO
# define rtmSetBlockIO(rtm, val)       ((rtm)->ModelData.blockIO = (val))
#endif

#ifndef rtmGetChecksums
# define rtmGetChecksums(rtm)          ((rtm)->Sizes.checksums)
#endif

#ifndef rtmSetChecksums
# define rtmSetChecksums(rtm, val)     ((rtm)->Sizes.checksums = (val))
#endif

#ifndef rtmGetConstBlockIO
# define rtmGetConstBlockIO(rtm)       ((rtm)->ModelData.constBlockIO)
#endif

#ifndef rtmSetConstBlockIO
# define rtmSetConstBlockIO(rtm, val)  ((rtm)->ModelData.constBlockIO = (val))
#endif

#ifndef rtmGetContStateDisabled
# define rtmGetContStateDisabled(rtm)  ((rtm)->ModelData.contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
# define rtmSetContStateDisabled(rtm, val) ((rtm)->ModelData.contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
# define rtmGetContStates(rtm)         ((rtm)->ModelData.contStates)
#endif

#ifndef rtmSetContStates
# define rtmSetContStates(rtm, val)    ((rtm)->ModelData.contStates = (val))
#endif

#ifndef rtmGetDataMapInfo
# define rtmGetDataMapInfo(rtm)        ((rtm)->DataMapInfo)
#endif

#ifndef rtmSetDataMapInfo
# define rtmSetDataMapInfo(rtm, val)   ((rtm)->DataMapInfo = (val))
#endif

#ifndef rtmGetDefaultParam
# define rtmGetDefaultParam(rtm)       ((rtm)->ModelData.defaultParam)
#endif

#ifndef rtmSetDefaultParam
# define rtmSetDefaultParam(rtm, val)  ((rtm)->ModelData.defaultParam = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
# define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->ModelData.derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
# define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->ModelData.derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetDirectFeedThrough
# define rtmGetDirectFeedThrough(rtm)  ((rtm)->Sizes.sysDirFeedThru)
#endif

#ifndef rtmSetDirectFeedThrough
# define rtmSetDirectFeedThrough(rtm, val) ((rtm)->Sizes.sysDirFeedThru = (val))
#endif

#ifndef rtmGetErrorStatusFlag
# define rtmGetErrorStatusFlag(rtm)    ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatusFlag
# define rtmSetErrorStatusFlag(rtm, val) ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetFinalTime
# define rtmGetFinalTime(rtm)          ((rtm)->Timing.tFinal)
#endif

#ifndef rtmSetFinalTime
# define rtmSetFinalTime(rtm, val)     ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmGetFirstInitCondFlag
# define rtmGetFirstInitCondFlag(rtm)  ()
#endif

#ifndef rtmSetFirstInitCondFlag
# define rtmSetFirstInitCondFlag(rtm, val) ()
#endif

#ifndef rtmGetIntgData
# define rtmGetIntgData(rtm)           ((rtm)->ModelData.intgData)
#endif

#ifndef rtmSetIntgData
# define rtmSetIntgData(rtm, val)      ((rtm)->ModelData.intgData = (val))
#endif

#ifndef rtmGetMdlRefGlobalTID
# define rtmGetMdlRefGlobalTID(rtm)    ()
#endif

#ifndef rtmSetMdlRefGlobalTID
# define rtmSetMdlRefGlobalTID(rtm, val) ()
#endif

#ifndef rtmGetMdlRefTriggerTID
# define rtmGetMdlRefTriggerTID(rtm)   ()
#endif

#ifndef rtmSetMdlRefTriggerTID
# define rtmSetMdlRefTriggerTID(rtm, val) ()
#endif

#ifndef rtmGetModelMappingInfo
# define rtmGetModelMappingInfo(rtm)   ((rtm)->SpecialInfo.mappingInfo)
#endif

#ifndef rtmSetModelMappingInfo
# define rtmSetModelMappingInfo(rtm, val) ((rtm)->SpecialInfo.mappingInfo = (val))
#endif

#ifndef rtmGetModelName
# define rtmGetModelName(rtm)          ((rtm)->modelName)
#endif

#ifndef rtmSetModelName
# define rtmSetModelName(rtm, val)     ((rtm)->modelName = (val))
#endif

#ifndef rtmGetNonInlinedSFcns
# define rtmGetNonInlinedSFcns(rtm)    ()
#endif

#ifndef rtmSetNonInlinedSFcns
# define rtmSetNonInlinedSFcns(rtm, val) ()
#endif

#ifndef rtmGetNumBlockIO
# define rtmGetNumBlockIO(rtm)         ((rtm)->Sizes.numBlockIO)
#endif

#ifndef rtmSetNumBlockIO
# define rtmSetNumBlockIO(rtm, val)    ((rtm)->Sizes.numBlockIO = (val))
#endif

#ifndef rtmGetNumBlockParams
# define rtmGetNumBlockParams(rtm)     ((rtm)->Sizes.numBlockPrms)
#endif

#ifndef rtmSetNumBlockParams
# define rtmSetNumBlockParams(rtm, val) ((rtm)->Sizes.numBlockPrms = (val))
#endif

#ifndef rtmGetNumBlocks
# define rtmGetNumBlocks(rtm)          ((rtm)->Sizes.numBlocks)
#endif

#ifndef rtmSetNumBlocks
# define rtmSetNumBlocks(rtm, val)     ((rtm)->Sizes.numBlocks = (val))
#endif

#ifndef rtmGetNumContStates
# define rtmGetNumContStates(rtm)      ((rtm)->Sizes.numContStates)
#endif

#ifndef rtmSetNumContStates
# define rtmSetNumContStates(rtm, val) ((rtm)->Sizes.numContStates = (val))
#endif

#ifndef rtmGetNumDWork
# define rtmGetNumDWork(rtm)           ((rtm)->Sizes.numDwork)
#endif

#ifndef rtmSetNumDWork
# define rtmSetNumDWork(rtm, val)      ((rtm)->Sizes.numDwork = (val))
#endif

#ifndef rtmGetNumInputPorts
# define rtmGetNumInputPorts(rtm)      ((rtm)->Sizes.numIports)
#endif

#ifndef rtmSetNumInputPorts
# define rtmSetNumInputPorts(rtm, val) ((rtm)->Sizes.numIports = (val))
#endif

#ifndef rtmGetNumNonSampledZCs
# define rtmGetNumNonSampledZCs(rtm)   ((rtm)->Sizes.numNonSampZCs)
#endif

#ifndef rtmSetNumNonSampledZCs
# define rtmSetNumNonSampledZCs(rtm, val) ((rtm)->Sizes.numNonSampZCs = (val))
#endif

#ifndef rtmGetNumOutputPorts
# define rtmGetNumOutputPorts(rtm)     ((rtm)->Sizes.numOports)
#endif

#ifndef rtmSetNumOutputPorts
# define rtmSetNumOutputPorts(rtm, val) ((rtm)->Sizes.numOports = (val))
#endif

#ifndef rtmGetNumSFcnParams
# define rtmGetNumSFcnParams(rtm)      ((rtm)->Sizes.numSFcnPrms)
#endif

#ifndef rtmSetNumSFcnParams
# define rtmSetNumSFcnParams(rtm, val) ((rtm)->Sizes.numSFcnPrms = (val))
#endif

#ifndef rtmGetNumSFunctions
# define rtmGetNumSFunctions(rtm)      ((rtm)->Sizes.numSFcns)
#endif

#ifndef rtmSetNumSFunctions
# define rtmSetNumSFunctions(rtm, val) ((rtm)->Sizes.numSFcns = (val))
#endif

#ifndef rtmGetNumSampleTimes
# define rtmGetNumSampleTimes(rtm)     ((rtm)->Sizes.numSampTimes)
#endif

#ifndef rtmSetNumSampleTimes
# define rtmSetNumSampleTimes(rtm, val) ((rtm)->Sizes.numSampTimes = (val))
#endif

#ifndef rtmGetNumU
# define rtmGetNumU(rtm)               ((rtm)->Sizes.numU)
#endif

#ifndef rtmSetNumU
# define rtmSetNumU(rtm, val)          ((rtm)->Sizes.numU = (val))
#endif

#ifndef rtmGetNumY
# define rtmGetNumY(rtm)               ((rtm)->Sizes.numY)
#endif

#ifndef rtmSetNumY
# define rtmSetNumY(rtm, val)          ((rtm)->Sizes.numY = (val))
#endif

#ifndef rtmGetOdeF
# define rtmGetOdeF(rtm)               ((rtm)->ModelData.odeF)
#endif

#ifndef rtmSetOdeF
# define rtmSetOdeF(rtm, val)          ((rtm)->ModelData.odeF = (val))
#endif

#ifndef rtmGetOdeY
# define rtmGetOdeY(rtm)               ((rtm)->ModelData.odeY)
#endif

#ifndef rtmSetOdeY
# define rtmSetOdeY(rtm, val)          ((rtm)->ModelData.odeY = (val))
#endif

#ifndef rtmGetOffsetTimeArray
# define rtmGetOffsetTimeArray(rtm)    ((rtm)->Timing.offsetTimesArray)
#endif

#ifndef rtmSetOffsetTimeArray
# define rtmSetOffsetTimeArray(rtm, val) ((rtm)->Timing.offsetTimesArray = (val))
#endif

#ifndef rtmGetOffsetTimePtr
# define rtmGetOffsetTimePtr(rtm)      ((rtm)->Timing.offsetTimes)
#endif

#ifndef rtmSetOffsetTimePtr
# define rtmSetOffsetTimePtr(rtm, val) ((rtm)->Timing.offsetTimes = (val))
#endif

#ifndef rtmGetOptions
# define rtmGetOptions(rtm)            ((rtm)->Sizes.options)
#endif

#ifndef rtmSetOptions
# define rtmSetOptions(rtm, val)       ((rtm)->Sizes.options = (val))
#endif

#ifndef rtmGetParamIsMalloced
# define rtmGetParamIsMalloced(rtm)    ()
#endif

#ifndef rtmSetParamIsMalloced
# define rtmSetParamIsMalloced(rtm, val) ()
#endif

#ifndef rtmGetPath
# define rtmGetPath(rtm)               ((rtm)->path)
#endif

#ifndef rtmSetPath
# define rtmSetPath(rtm, val)          ((rtm)->path = (val))
#endif

#ifndef rtmGetPerTaskSampleHits
# define rtmGetPerTaskSampleHits(rtm)  ()
#endif

#ifndef rtmSetPerTaskSampleHits
# define rtmSetPerTaskSampleHits(rtm, val) ()
#endif

#ifndef rtmGetPerTaskSampleHitsArray
# define rtmGetPerTaskSampleHitsArray(rtm) ((rtm)->Timing.perTaskSampleHitsArray)
#endif

#ifndef rtmSetPerTaskSampleHitsArray
# define rtmSetPerTaskSampleHitsArray(rtm, val) ((rtm)->Timing.perTaskSampleHitsArray = (val))
#endif

#ifndef rtmGetPerTaskSampleHitsPtr
# define rtmGetPerTaskSampleHitsPtr(rtm) ((rtm)->Timing.perTaskSampleHits)
#endif

#ifndef rtmSetPerTaskSampleHitsPtr
# define rtmSetPerTaskSampleHitsPtr(rtm, val) ((rtm)->Timing.perTaskSampleHits = (val))
#endif

#ifndef rtmGetPrevZCSigState
# define rtmGetPrevZCSigState(rtm)     ((rtm)->ModelData.prevZCSigState)
#endif

#ifndef rtmSetPrevZCSigState
# define rtmSetPrevZCSigState(rtm, val) ((rtm)->ModelData.prevZCSigState = (val))
#endif

#ifndef rtmGetRTWExtModeInfo
# define rtmGetRTWExtModeInfo(rtm)     ((rtm)->extModeInfo)
#endif

#ifndef rtmSetRTWExtModeInfo
# define rtmSetRTWExtModeInfo(rtm, val) ((rtm)->extModeInfo = (val))
#endif

#ifndef rtmGetRTWGeneratedSFcn
# define rtmGetRTWGeneratedSFcn(rtm)   ((rtm)->Sizes.rtwGenSfcn)
#endif

#ifndef rtmSetRTWGeneratedSFcn
# define rtmSetRTWGeneratedSFcn(rtm, val) ((rtm)->Sizes.rtwGenSfcn = (val))
#endif

#ifndef rtmGetRTWLogInfo
# define rtmGetRTWLogInfo(rtm)         ((rtm)->rtwLogInfo)
#endif

#ifndef rtmSetRTWLogInfo
# define rtmSetRTWLogInfo(rtm, val)    ((rtm)->rtwLogInfo = (val))
#endif

#ifndef rtmGetRTWRTModelMethodsInfo
# define rtmGetRTWRTModelMethodsInfo(rtm) ()
#endif

#ifndef rtmSetRTWRTModelMethodsInfo
# define rtmSetRTWRTModelMethodsInfo(rtm, val) ()
#endif

#ifndef rtmGetRTWSfcnInfo
# define rtmGetRTWSfcnInfo(rtm)        ((rtm)->sfcnInfo)
#endif

#ifndef rtmSetRTWSfcnInfo
# define rtmSetRTWSfcnInfo(rtm, val)   ((rtm)->sfcnInfo = (val))
#endif

#ifndef rtmGetRTWSolverInfo
# define rtmGetRTWSolverInfo(rtm)      ((rtm)->solverInfo)
#endif

#ifndef rtmSetRTWSolverInfo
# define rtmSetRTWSolverInfo(rtm, val) ((rtm)->solverInfo = (val))
#endif

#ifndef rtmGetRTWSolverInfoPtr
# define rtmGetRTWSolverInfoPtr(rtm)   ((rtm)->solverInfoPtr)
#endif

#ifndef rtmSetRTWSolverInfoPtr
# define rtmSetRTWSolverInfoPtr(rtm, val) ((rtm)->solverInfoPtr = (val))
#endif

#ifndef rtmGetReservedForXPC
# define rtmGetReservedForXPC(rtm)     ((rtm)->SpecialInfo.xpcData)
#endif

#ifndef rtmSetReservedForXPC
# define rtmSetReservedForXPC(rtm, val) ((rtm)->SpecialInfo.xpcData = (val))
#endif

#ifndef rtmGetRootDWork
# define rtmGetRootDWork(rtm)          ((rtm)->Work.dwork)
#endif

#ifndef rtmSetRootDWork
# define rtmSetRootDWork(rtm, val)     ((rtm)->Work.dwork = (val))
#endif

#ifndef rtmGetSFunctions
# define rtmGetSFunctions(rtm)         ((rtm)->childSfunctions)
#endif

#ifndef rtmSetSFunctions
# define rtmSetSFunctions(rtm, val)    ((rtm)->childSfunctions = (val))
#endif

#ifndef rtmGetSampleHitArray
# define rtmGetSampleHitArray(rtm)     ((rtm)->Timing.sampleHitArray)
#endif

#ifndef rtmSetSampleHitArray
# define rtmSetSampleHitArray(rtm, val) ((rtm)->Timing.sampleHitArray = (val))
#endif

#ifndef rtmGetSampleHitPtr
# define rtmGetSampleHitPtr(rtm)       ((rtm)->Timing.sampleHits)
#endif

#ifndef rtmSetSampleHitPtr
# define rtmSetSampleHitPtr(rtm, val)  ((rtm)->Timing.sampleHits = (val))
#endif

#ifndef rtmGetSampleTimeArray
# define rtmGetSampleTimeArray(rtm)    ((rtm)->Timing.sampleTimesArray)
#endif

#ifndef rtmSetSampleTimeArray
# define rtmSetSampleTimeArray(rtm, val) ((rtm)->Timing.sampleTimesArray = (val))
#endif

#ifndef rtmGetSampleTimePtr
# define rtmGetSampleTimePtr(rtm)      ((rtm)->Timing.sampleTimes)
#endif

#ifndef rtmSetSampleTimePtr
# define rtmSetSampleTimePtr(rtm, val) ((rtm)->Timing.sampleTimes = (val))
#endif

#ifndef rtmGetSampleTimeTaskIDArray
# define rtmGetSampleTimeTaskIDArray(rtm) ((rtm)->Timing.sampleTimeTaskIDArray)
#endif

#ifndef rtmSetSampleTimeTaskIDArray
# define rtmSetSampleTimeTaskIDArray(rtm, val) ((rtm)->Timing.sampleTimeTaskIDArray = (val))
#endif

#ifndef rtmGetSampleTimeTaskIDPtr
# define rtmGetSampleTimeTaskIDPtr(rtm) ((rtm)->Timing.sampleTimeTaskIDPtr)
#endif

#ifndef rtmSetSampleTimeTaskIDPtr
# define rtmSetSampleTimeTaskIDPtr(rtm, val) ((rtm)->Timing.sampleTimeTaskIDPtr = (val))
#endif

#ifndef rtmGetSimMode
# define rtmGetSimMode(rtm)            ((rtm)->simMode)
#endif

#ifndef rtmSetSimMode
# define rtmSetSimMode(rtm, val)       ((rtm)->simMode = (val))
#endif

#ifndef rtmGetSimTimeStep
# define rtmGetSimTimeStep(rtm)        ((rtm)->Timing.simTimeStep)
#endif

#ifndef rtmSetSimTimeStep
# define rtmSetSimTimeStep(rtm, val)   ((rtm)->Timing.simTimeStep = (val))
#endif

#ifndef rtmGetStartTime
# define rtmGetStartTime(rtm)          ((rtm)->Timing.tStart)
#endif

#ifndef rtmSetStartTime
# define rtmSetStartTime(rtm, val)     ((rtm)->Timing.tStart = (val))
#endif

#ifndef rtmGetStepSize
# define rtmGetStepSize(rtm)           ((rtm)->Timing.stepSize)
#endif

#ifndef rtmSetStepSize
# define rtmSetStepSize(rtm, val)      ((rtm)->Timing.stepSize = (val))
#endif

#ifndef rtmGetStopRequestedFlag
# define rtmGetStopRequestedFlag(rtm)  ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequestedFlag
# define rtmSetStopRequestedFlag(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetTaskCounters
# define rtmGetTaskCounters(rtm)       ((rtm)->Timing.TaskCounters)
#endif

#ifndef rtmSetTaskCounters
# define rtmSetTaskCounters(rtm, val)  ((rtm)->Timing.TaskCounters = (val))
#endif

#ifndef rtmGetTaskTimeArray
# define rtmGetTaskTimeArray(rtm)      ((rtm)->Timing.tArray)
#endif

#ifndef rtmSetTaskTimeArray
# define rtmSetTaskTimeArray(rtm, val) ((rtm)->Timing.tArray = (val))
#endif

#ifndef rtmGetTimePtr
# define rtmGetTimePtr(rtm)            ((rtm)->Timing.t)
#endif

#ifndef rtmSetTimePtr
# define rtmSetTimePtr(rtm, val)       ((rtm)->Timing.t = (val))
#endif

#ifndef rtmGetTimingData
# define rtmGetTimingData(rtm)         ((rtm)->Timing.timingData)
#endif

#ifndef rtmSetTimingData
# define rtmSetTimingData(rtm, val)    ((rtm)->Timing.timingData = (val))
#endif

#ifndef rtmGetU
# define rtmGetU(rtm)                  ((rtm)->ModelData.inputs)
#endif

#ifndef rtmSetU
# define rtmSetU(rtm, val)             ((rtm)->ModelData.inputs = (val))
#endif

#ifndef rtmGetVarNextHitTimesListPtr
# define rtmGetVarNextHitTimesListPtr(rtm) ((rtm)->Timing.varNextHitTimesList)
#endif

#ifndef rtmSetVarNextHitTimesListPtr
# define rtmSetVarNextHitTimesListPtr(rtm, val) ((rtm)->Timing.varNextHitTimesList = (val))
#endif

#ifndef rtmGetY
# define rtmGetY(rtm)                  ((rtm)->ModelData.outputs)
#endif

#ifndef rtmSetY
# define rtmSetY(rtm, val)             ((rtm)->ModelData.outputs = (val))
#endif

#ifndef rtmGetZCCacheNeedsReset
# define rtmGetZCCacheNeedsReset(rtm)  ((rtm)->ModelData.zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
# define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->ModelData.zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetZCSignalValues
# define rtmGetZCSignalValues(rtm)     ((rtm)->ModelData.zcSignalValues)
#endif

#ifndef rtmSetZCSignalValues
# define rtmSetZCSignalValues(rtm, val) ((rtm)->ModelData.zcSignalValues = (val))
#endif

#ifndef rtmGet_TimeOfLastOutput
# define rtmGet_TimeOfLastOutput(rtm)  ((rtm)->Timing.timeOfLastOutput)
#endif

#ifndef rtmSet_TimeOfLastOutput
# define rtmSet_TimeOfLastOutput(rtm, val) ((rtm)->Timing.timeOfLastOutput = (val))
#endif

#ifndef rtmGetdX
# define rtmGetdX(rtm)                 ((rtm)->ModelData.derivs)
#endif

#ifndef rtmSetdX
# define rtmSetdX(rtm, val)            ((rtm)->ModelData.derivs = (val))
#endif

#ifndef rtmGetChecksumVal
# define rtmGetChecksumVal(rtm, idx)   ((rtm)->Sizes.checksums[idx])
#endif

#ifndef rtmSetChecksumVal
# define rtmSetChecksumVal(rtm, idx, val) ((rtm)->Sizes.checksums[idx] = (val))
#endif

#ifndef rtmGetDWork
# define rtmGetDWork(rtm, idx)         ((rtm)->Work.dwork[idx])
#endif

#ifndef rtmSetDWork
# define rtmSetDWork(rtm, idx, val)    ((rtm)->Work.dwork[idx] = (val))
#endif

#ifndef rtmGetOffsetTime
# define rtmGetOffsetTime(rtm, idx)    ((rtm)->Timing.offsetTimes[idx])
#endif

#ifndef rtmSetOffsetTime
# define rtmSetOffsetTime(rtm, idx, val) ((rtm)->Timing.offsetTimes[idx] = (val))
#endif

#ifndef rtmGetSFunction
# define rtmGetSFunction(rtm, idx)     ((rtm)->childSfunctions[idx])
#endif

#ifndef rtmSetSFunction
# define rtmSetSFunction(rtm, idx, val) ((rtm)->childSfunctions[idx] = (val))
#endif

#ifndef rtmGetSampleTime
# define rtmGetSampleTime(rtm, idx)    ((rtm)->Timing.sampleTimes[idx])
#endif

#ifndef rtmSetSampleTime
# define rtmSetSampleTime(rtm, idx, val) ((rtm)->Timing.sampleTimes[idx] = (val))
#endif

#ifndef rtmGetSampleTimeTaskID
# define rtmGetSampleTimeTaskID(rtm, idx) ((rtm)->Timing.sampleTimeTaskIDPtr[idx])
#endif

#ifndef rtmSetSampleTimeTaskID
# define rtmSetSampleTimeTaskID(rtm, idx, val) ((rtm)->Timing.sampleTimeTaskIDPtr[idx] = (val))
#endif

#ifndef rtmGetVarNextHitTimeList
# define rtmGetVarNextHitTimeList(rtm, idx) ((rtm)->Timing.varNextHitTimesList[idx])
#endif

#ifndef rtmSetVarNextHitTimeList
# define rtmSetVarNextHitTimeList(rtm, idx, val) ((rtm)->Timing.varNextHitTimesList[idx] = (val))
#endif

#ifndef rtmIsContinuousTask
# define rtmIsContinuousTask(rtm, tid) ((tid) == 0)
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmIsMajorTimeStep
# define rtmIsMajorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
# define rtmIsMinorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmIsSampleHit
# define rtmIsSampleHit(rtm, sti, tid) ((rtmIsMajorTimeStep((rtm)) && (rtm)->Timing.sampleHits[(rtm)->Timing.sampleTimeTaskIDPtr[sti]]))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmSetT
# define rtmSetT(rtm, val)                                       /* Do Nothing */
#endif

#ifndef rtmGetTFinal
# define rtmGetTFinal(rtm)             ((rtm)->Timing.tFinal)
#endif

#ifndef rtmSetTFinal
# define rtmSetTFinal(rtm, val)        ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

#ifndef rtmSetTPtr
# define rtmSetTPtr(rtm, val)          ((rtm)->Timing.t = (val))
#endif

#ifndef rtmGetTStart
# define rtmGetTStart(rtm)             ((rtm)->Timing.tStart)
#endif

#ifndef rtmSetTStart
# define rtmSetTStart(rtm, val)        ((rtm)->Timing.tStart = (val))
#endif

#ifndef rtmGetTaskTime
# define rtmGetTaskTime(rtm, sti)      (rtmGetTPtr((rtm))[(rtm)->Timing.sampleTimeTaskIDPtr[sti]])
#endif

#ifndef rtmSetTaskTime
# define rtmSetTaskTime(rtm, sti, val) (rtmGetTPtr((rtm))[sti] = (val))
#endif

#ifndef rtmGetTimeOfLastOutput
# define rtmGetTimeOfLastOutput(rtm)   ((rtm)->Timing.timeOfLastOutput)
#endif

#ifdef rtmGetRTWSolverInfo
#undef rtmGetRTWSolverInfo
#endif

#define rtmGetRTWSolverInfo(rtm)       &((rtm)->solverInfo)

/* Definition for use in the target main file */
#define f14tmp5_rtModel                rtModel_f14tmp5

/* user code (top of export header file) */
#include "xpcdatatypes.h"

/* Block signals (auto storage) */
typedef struct {
  real_T TransferFcn2;                 /* '<S6>/Transfer Fcn.2' */
  real_T Gain5;                        /* '<S1>/Gain5' */
  real_T Derivative;                   /* '<S9>/Derivative' */
  real_T TransferFcn1;                 /* '<S6>/Transfer Fcn.1' */
  real_T Derivative1;                  /* '<S9>/Derivative1' */
  real_T Gain1;                        /* '<S9>/Gain1' */
  real_T Product;                      /* '<S9>/Product' */
  real_T Sum1;                         /* '<S9>/Sum1' */
  real_T Gain2;                        /* '<S9>/Gain2' */
  real_T Pilot;                        /* '<S1>/Pilot' */
  real_T Sum1_k;                       /* '<S1>/Sum1' */
  real_T ActuatorModel;                /* '<S1>/Actuator Model' */
  real_T Gain3;                        /* '<S6>/Gain3' */
  real_T Gain4;                        /* '<S6>/Gain4' */
  real_T Gain5_b;                      /* '<S6>/Gain5' */
  real_T Gain6;                        /* '<S6>/Gain6' */
  real_T Wgustmodel;                   /* '<S8>/W-gust model' */
  real_T Gain;                         /* '<S1>/Gain' */
  real_T Sum1_o;                       /* '<S6>/Sum1' */
  real_T Gain2_f;                      /* '<S1>/Gain2' */
  real_T Qgustmodel;                   /* '<S8>/Q-gust model' */
  real_T Gain1_h;                      /* '<S1>/Gain1' */
  real_T Sum;                          /* '<S1>/Sum' */
  real_T Sum2;                         /* '<S6>/Sum2' */
  real_T AlphasensorLowpassFilter;     /* '<S7>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter;               /* '<S7>/Stick Prefilter' */
  real_T PitchRateLeadFilter;          /* '<S7>/Pitch Rate Lead Filter' */
  real_T Gain2_e;                      /* '<S7>/Gain2' */
  real_T Gain3_g;                      /* '<S7>/Gain3' */
  real_T Sum1_d;                       /* '<S7>/Sum1' */
  real_T Sum2_f;                       /* '<S7>/Sum2' */
  real_T Gain_d;                       /* '<S7>/Gain' */
  real_T Proportionalplusintegralcompens;/* '<S7>/Proportional plus integral compensator' */
  real_T Sum_n;                        /* '<S7>/Sum' */
  real_T WhiteNoise;                   /* '<S10>/White Noise' */
  real_T Output;                       /* '<S10>/Output' */
  real_T TransferFcn2_b;               /* '<S11>/Transfer Fcn.2' */
  real_T Gain5_h;                      /* '<S2>/Gain5' */
  real_T Derivative_k;                 /* '<S14>/Derivative' */
  real_T TransferFcn1_a;               /* '<S11>/Transfer Fcn.1' */
  real_T Derivative1_a;                /* '<S14>/Derivative1' */
  real_T Gain1_c;                      /* '<S14>/Gain1' */
  real_T Product_a;                    /* '<S14>/Product' */
  real_T Sum1_di;                      /* '<S14>/Sum1' */
  real_T Gain2_l;                      /* '<S14>/Gain2' */
  real_T Pilot_k;                      /* '<S2>/Pilot' */
  real_T Sum1_n;                       /* '<S2>/Sum1' */
  real_T ActuatorModel_n;              /* '<S2>/Actuator Model' */
  real_T Gain3_a;                      /* '<S11>/Gain3' */
  real_T Gain4_p;                      /* '<S11>/Gain4' */
  real_T Gain5_h4;                     /* '<S11>/Gain5' */
  real_T Gain6_m;                      /* '<S11>/Gain6' */
  real_T Wgustmodel_j;                 /* '<S13>/W-gust model' */
  real_T Gain_n;                       /* '<S2>/Gain' */
  real_T Sum1_e;                       /* '<S11>/Sum1' */
  real_T Gain2_o;                      /* '<S2>/Gain2' */
  real_T Qgustmodel_c;                 /* '<S13>/Q-gust model' */
  real_T Gain1_i;                      /* '<S2>/Gain1' */
  real_T Sum_e;                        /* '<S2>/Sum' */
  real_T Sum2_c;                       /* '<S11>/Sum2' */
  real_T AlphasensorLowpassFilter_e;   /* '<S12>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_h;             /* '<S12>/Stick Prefilter' */
  real_T PitchRateLeadFilter_f;        /* '<S12>/Pitch Rate Lead Filter' */
  real_T Gain2_j;                      /* '<S12>/Gain2' */
  real_T Gain3_l;                      /* '<S12>/Gain3' */
  real_T Sum1_i;                       /* '<S12>/Sum1' */
  real_T Sum2_k;                       /* '<S12>/Sum2' */
  real_T Gain_e;                       /* '<S12>/Gain' */
  real_T Proportionalplusintegralcompe_j;/* '<S12>/Proportional plus integral compensator' */
  real_T Sum_l;                        /* '<S12>/Sum' */
  real_T WhiteNoise_l;                 /* '<S15>/White Noise' */
  real_T Output_e;                     /* '<S15>/Output' */
  real_T TransferFcn2_l;               /* '<S16>/Transfer Fcn.2' */
  real_T Gain5_p;                      /* '<S3>/Gain5' */
  real_T Derivative_l;                 /* '<S19>/Derivative' */
  real_T TransferFcn1_g;               /* '<S16>/Transfer Fcn.1' */
  real_T Derivative1_j;                /* '<S19>/Derivative1' */
  real_T Gain1_g;                      /* '<S19>/Gain1' */
  real_T Product_b;                    /* '<S19>/Product' */
  real_T Sum1_ev;                      /* '<S19>/Sum1' */
  real_T Gain2_g;                      /* '<S19>/Gain2' */
  real_T Pilot_h;                      /* '<S3>/Pilot' */
  real_T Sum1_n0;                      /* '<S3>/Sum1' */
  real_T ActuatorModel_a;              /* '<S3>/Actuator Model' */
  real_T Gain3_m;                      /* '<S16>/Gain3' */
  real_T Gain4_c;                      /* '<S16>/Gain4' */
  real_T Gain5_o;                      /* '<S16>/Gain5' */
  real_T Gain6_mc;                     /* '<S16>/Gain6' */
  real_T Wgustmodel_e;                 /* '<S18>/W-gust model' */
  real_T Gain_l;                       /* '<S3>/Gain' */
  real_T Sum1_dr;                      /* '<S16>/Sum1' */
  real_T Gain2_l0;                     /* '<S3>/Gain2' */
  real_T Qgustmodel_j;                 /* '<S18>/Q-gust model' */
  real_T Gain1_b;                      /* '<S3>/Gain1' */
  real_T Sum_i;                        /* '<S3>/Sum' */
  real_T Sum2_o;                       /* '<S16>/Sum2' */
  real_T AlphasensorLowpassFilter_h;   /* '<S17>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_i;             /* '<S17>/Stick Prefilter' */
  real_T PitchRateLeadFilter_d;        /* '<S17>/Pitch Rate Lead Filter' */
  real_T Gain2_p;                      /* '<S17>/Gain2' */
  real_T Gain3_gl;                     /* '<S17>/Gain3' */
  real_T Sum1_o0;                      /* '<S17>/Sum1' */
  real_T Sum2_g;                       /* '<S17>/Sum2' */
  real_T Gain_h;                       /* '<S17>/Gain' */
  real_T Proportionalplusintegralcompe_e;/* '<S17>/Proportional plus integral compensator' */
  real_T Sum_o;                        /* '<S17>/Sum' */
  real_T WhiteNoise_g;                 /* '<S20>/White Noise' */
  real_T Output_c;                     /* '<S20>/Output' */
  real_T TransferFcn2_j;               /* '<S21>/Transfer Fcn.2' */
  real_T Gain5_k;                      /* '<S4>/Gain5' */
  real_T Derivative_p;                 /* '<S24>/Derivative' */
  real_T TransferFcn1_k;               /* '<S21>/Transfer Fcn.1' */
  real_T Derivative1_g;                /* '<S24>/Derivative1' */
  real_T Gain1_ga;                     /* '<S24>/Gain1' */
  real_T Product_h;                    /* '<S24>/Product' */
  real_T Sum1_o0i;                     /* '<S24>/Sum1' */
  real_T Gain2_h;                      /* '<S24>/Gain2' */
  real_T Pilot_g;                      /* '<S4>/Pilot' */
  real_T Sum1_dd;                      /* '<S4>/Sum1' */
  real_T ActuatorModel_m;              /* '<S4>/Actuator Model' */
  real_T Gain3_lc;                     /* '<S21>/Gain3' */
  real_T Gain4_j;                      /* '<S21>/Gain4' */
  real_T Gain5_pj;                     /* '<S21>/Gain5' */
  real_T Gain6_f;                      /* '<S21>/Gain6' */
  real_T Wgustmodel_h;                 /* '<S23>/W-gust model' */
  real_T Gain_o;                       /* '<S4>/Gain' */
  real_T Sum1_f;                       /* '<S21>/Sum1' */
  real_T Gain2_n;                      /* '<S4>/Gain2' */
  real_T Qgustmodel_g;                 /* '<S23>/Q-gust model' */
  real_T Gain1_o;                      /* '<S4>/Gain1' */
  real_T Sum_en;                       /* '<S4>/Sum' */
  real_T Sum2_cx;                      /* '<S21>/Sum2' */
  real_T AlphasensorLowpassFilter_j;   /* '<S22>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_e;             /* '<S22>/Stick Prefilter' */
  real_T PitchRateLeadFilter_k;        /* '<S22>/Pitch Rate Lead Filter' */
  real_T Gain2_nh;                     /* '<S22>/Gain2' */
  real_T Gain3_b;                      /* '<S22>/Gain3' */
  real_T Sum1_om;                      /* '<S22>/Sum1' */
  real_T Sum2_gm;                      /* '<S22>/Sum2' */
  real_T Gain_df;                      /* '<S22>/Gain' */
  real_T Proportionalplusintegralcompe_h;/* '<S22>/Proportional plus integral compensator' */
  real_T Sum_k;                        /* '<S22>/Sum' */
  real_T WhiteNoise_p;                 /* '<S25>/White Noise' */
  real_T Output_k;                     /* '<S25>/Output' */
  real_T TransferFcn2_o;               /* '<S26>/Transfer Fcn.2' */
  real_T Gain5_c;                      /* '<S5>/Gain5' */
  real_T Derivative_f;                 /* '<S29>/Derivative' */
  real_T TransferFcn1_i;               /* '<S26>/Transfer Fcn.1' */
  real_T Derivative1_i;                /* '<S29>/Derivative1' */
  real_T Gain1_om;                     /* '<S29>/Gain1' */
  real_T Product_i;                    /* '<S29>/Product' */
  real_T Sum1_a;                       /* '<S29>/Sum1' */
  real_T Gain2_oj;                     /* '<S29>/Gain2' */
  real_T Pilot_h3;                     /* '<S5>/Pilot' */
  real_T Sum1_h;                       /* '<S5>/Sum1' */
  real_T ActuatorModel_b;              /* '<S5>/Actuator Model' */
  real_T Gain3_as;                     /* '<S26>/Gain3' */
  real_T Gain4_l;                      /* '<S26>/Gain4' */
  real_T Gain5_i;                      /* '<S26>/Gain5' */
  real_T Gain6_b;                      /* '<S26>/Gain6' */
  real_T Wgustmodel_o;                 /* '<S28>/W-gust model' */
  real_T Gain_hr;                      /* '<S5>/Gain' */
  real_T Sum1_g;                       /* '<S26>/Sum1' */
  real_T Gain2_b;                      /* '<S5>/Gain2' */
  real_T Qgustmodel_n;                 /* '<S28>/Q-gust model' */
  real_T Gain1_l;                      /* '<S5>/Gain1' */
  real_T Sum_kh;                       /* '<S5>/Sum' */
  real_T Sum2_oa;                      /* '<S26>/Sum2' */
  real_T AlphasensorLowpassFilter_n;   /* '<S27>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_o;             /* '<S27>/Stick Prefilter' */
  real_T PitchRateLeadFilter_f1;       /* '<S27>/Pitch Rate Lead Filter' */
  real_T Gain2_fs;                     /* '<S27>/Gain2' */
  real_T Gain3_f;                      /* '<S27>/Gain3' */
  real_T Sum1_m;                       /* '<S27>/Sum1' */
  real_T Sum2_f5;                      /* '<S27>/Sum2' */
  real_T Gain_i;                       /* '<S27>/Gain' */
  real_T Proportionalplusintegralcomp_eg;/* '<S27>/Proportional plus integral compensator' */
  real_T Sum_m;                        /* '<S27>/Sum' */
  real_T WhiteNoise_m;                 /* '<S30>/White Noise' */
  real_T Output_a;                     /* '<S30>/Output' */
} BlockIO_f14tmp5;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T NextOutput;                   /* '<S10>/White Noise' */
  real_T NextOutput_f;                 /* '<S15>/White Noise' */
  real_T NextOutput_h;                 /* '<S20>/White Noise' */
  real_T NextOutput_a;                 /* '<S25>/White Noise' */
  real_T NextOutput_e;                 /* '<S30>/White Noise' */
  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK;                  /* '<S9>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative1_RWORK;                 /* '<S9>/Derivative1' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_f;                /* '<S14>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative1_RWORK_o;               /* '<S14>/Derivative1' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_l;                /* '<S19>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative1_RWORK_k;               /* '<S19>/Derivative1' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_k;                /* '<S24>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative1_RWORK_b;               /* '<S24>/Derivative1' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_lc;               /* '<S29>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative1_RWORK_d;               /* '<S29>/Derivative1' */

  struct {
    void *LoggedData;
  } AngleofAttack_PWORK;               /* '<S1>/Angle of  Attack' */

  struct {
    void *LoggedData;
  } PilotGforceScope_PWORK;            /* '<S1>/Pilot G force Scope' */

  struct {
    void *LoggedData;
  } StickInput_PWORK;                  /* '<S1>/Stick Input' */

  struct {
    void *LoggedData;
  } AngleofAttack_PWORK_a;             /* '<S2>/Angle of  Attack' */

  struct {
    void *LoggedData;
  } PilotGforceScope_PWORK_j;          /* '<S2>/Pilot G force Scope' */

  struct {
    void *LoggedData;
  } StickInput_PWORK_k;                /* '<S2>/Stick Input' */

  struct {
    void *LoggedData;
  } AngleofAttack_PWORK_k;             /* '<S3>/Angle of  Attack' */

  struct {
    void *LoggedData;
  } PilotGforceScope_PWORK_i;          /* '<S3>/Pilot G force Scope' */

  struct {
    void *LoggedData;
  } StickInput_PWORK_d;                /* '<S3>/Stick Input' */

  struct {
    void *LoggedData;
  } AngleofAttack_PWORK_n;             /* '<S4>/Angle of  Attack' */

  struct {
    void *LoggedData;
  } PilotGforceScope_PWORK_o;          /* '<S4>/Pilot G force Scope' */

  struct {
    void *LoggedData;
  } StickInput_PWORK_n;                /* '<S4>/Stick Input' */

  struct {
    void *LoggedData;
  } AngleofAttack_PWORK_g;             /* '<S5>/Angle of  Attack' */

  struct {
    void *LoggedData;
  } PilotGforceScope_PWORK_a;          /* '<S5>/Pilot G force Scope' */

  struct {
    void *LoggedData;
  } StickInput_PWORK_p;                /* '<S5>/Stick Input' */

  uint32_T RandSeed;                   /* '<S10>/White Noise' */
  uint32_T RandSeed_n;                 /* '<S15>/White Noise' */
  uint32_T RandSeed_e;                 /* '<S20>/White Noise' */
  uint32_T RandSeed_f;                 /* '<S25>/White Noise' */
  uint32_T RandSeed_d;                 /* '<S30>/White Noise' */
} D_Work_f14tmp5;

/* Continuous states (auto storage) */
typedef struct {
  real_T TransferFcn2_CSTATE;          /* '<S6>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE;          /* '<S6>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE;         /* '<S1>/Actuator Model' */
  real_T Wgustmodel_CSTATE[2];         /* '<S8>/W-gust model' */
  real_T Qgustmodel_CSTATE;            /* '<S8>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CSTATE;/* '<S7>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE;        /* '<S7>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE;   /* '<S7>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompens;/* '<S7>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_h;        /* '<S11>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_p;        /* '<S11>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_a;       /* '<S2>/Actuator Model' */
  real_T Wgustmodel_CSTATE_f[2];       /* '<S13>/W-gust model' */
  real_T Qgustmodel_CSTATE_d;          /* '<S13>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CSTA_g;/* '<S12>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_a;      /* '<S12>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_k; /* '<S12>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompe_n;/* '<S12>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_n;        /* '<S16>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_k;        /* '<S16>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_f;       /* '<S3>/Actuator Model' */
  real_T Wgustmodel_CSTATE_i[2];       /* '<S18>/W-gust model' */
  real_T Qgustmodel_CSTATE_k;          /* '<S18>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CSTA_i;/* '<S17>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_j;      /* '<S17>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_n; /* '<S17>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompe_h;/* '<S17>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_e;        /* '<S21>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_j;        /* '<S21>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_p;       /* '<S4>/Actuator Model' */
  real_T Wgustmodel_CSTATE_k[2];       /* '<S23>/W-gust model' */
  real_T Qgustmodel_CSTATE_a;          /* '<S23>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CSTA_k;/* '<S22>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_ju;     /* '<S22>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_e; /* '<S22>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompe_j;/* '<S22>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_k;        /* '<S26>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_pe;       /* '<S26>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_o;       /* '<S5>/Actuator Model' */
  real_T Wgustmodel_CSTATE_if[2];      /* '<S28>/W-gust model' */
  real_T Qgustmodel_CSTATE_m;          /* '<S28>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CST_ku;/* '<S27>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_m;      /* '<S27>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_f; /* '<S27>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompe_k;/* '<S27>/Proportional plus integral compensator' */
} ContinuousStates_f14tmp5;

/* State derivatives (auto storage) */
typedef struct {
  real_T TransferFcn2_CSTATE;          /* '<S6>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE;          /* '<S6>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE;         /* '<S1>/Actuator Model' */
  real_T Wgustmodel_CSTATE[2];         /* '<S8>/W-gust model' */
  real_T Qgustmodel_CSTATE;            /* '<S8>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CSTATE;/* '<S7>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE;        /* '<S7>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE;   /* '<S7>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompens;/* '<S7>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_h;        /* '<S11>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_p;        /* '<S11>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_a;       /* '<S2>/Actuator Model' */
  real_T Wgustmodel_CSTATE_f[2];       /* '<S13>/W-gust model' */
  real_T Qgustmodel_CSTATE_d;          /* '<S13>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CSTA_g;/* '<S12>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_a;      /* '<S12>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_k; /* '<S12>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompe_n;/* '<S12>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_n;        /* '<S16>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_k;        /* '<S16>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_f;       /* '<S3>/Actuator Model' */
  real_T Wgustmodel_CSTATE_i[2];       /* '<S18>/W-gust model' */
  real_T Qgustmodel_CSTATE_k;          /* '<S18>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CSTA_i;/* '<S17>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_j;      /* '<S17>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_n; /* '<S17>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompe_h;/* '<S17>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_e;        /* '<S21>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_j;        /* '<S21>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_p;       /* '<S4>/Actuator Model' */
  real_T Wgustmodel_CSTATE_k[2];       /* '<S23>/W-gust model' */
  real_T Qgustmodel_CSTATE_a;          /* '<S23>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CSTA_k;/* '<S22>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_ju;     /* '<S22>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_e; /* '<S22>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompe_j;/* '<S22>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_k;        /* '<S26>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_pe;       /* '<S26>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_o;       /* '<S5>/Actuator Model' */
  real_T Wgustmodel_CSTATE_if[2];      /* '<S28>/W-gust model' */
  real_T Qgustmodel_CSTATE_m;          /* '<S28>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CST_ku;/* '<S27>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_m;      /* '<S27>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_f; /* '<S27>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompe_k;/* '<S27>/Proportional plus integral compensator' */
} StateDerivatives_f14tmp5;

/* State disabled  */
typedef struct {
  boolean_T TransferFcn2_CSTATE;       /* '<S6>/Transfer Fcn.2' */
  boolean_T TransferFcn1_CSTATE;       /* '<S6>/Transfer Fcn.1' */
  boolean_T ActuatorModel_CSTATE;      /* '<S1>/Actuator Model' */
  boolean_T Wgustmodel_CSTATE[2];      /* '<S8>/W-gust model' */
  boolean_T Qgustmodel_CSTATE;         /* '<S8>/Q-gust model' */
  boolean_T AlphasensorLowpassFilter_CSTATE;/* '<S7>/Alpha-sensor Low-pass Filter' */
  boolean_T StickPrefilter_CSTATE;     /* '<S7>/Stick Prefilter' */
  boolean_T PitchRateLeadFilter_CSTATE;/* '<S7>/Pitch Rate Lead Filter' */
  boolean_T Proportionalplusintegralcompens;/* '<S7>/Proportional plus integral compensator' */
  boolean_T TransferFcn2_CSTATE_h;     /* '<S11>/Transfer Fcn.2' */
  boolean_T TransferFcn1_CSTATE_p;     /* '<S11>/Transfer Fcn.1' */
  boolean_T ActuatorModel_CSTATE_a;    /* '<S2>/Actuator Model' */
  boolean_T Wgustmodel_CSTATE_f[2];    /* '<S13>/W-gust model' */
  boolean_T Qgustmodel_CSTATE_d;       /* '<S13>/Q-gust model' */
  boolean_T AlphasensorLowpassFilter_CSTA_g;/* '<S12>/Alpha-sensor Low-pass Filter' */
  boolean_T StickPrefilter_CSTATE_a;   /* '<S12>/Stick Prefilter' */
  boolean_T PitchRateLeadFilter_CSTATE_k;/* '<S12>/Pitch Rate Lead Filter' */
  boolean_T Proportionalplusintegralcompe_n;/* '<S12>/Proportional plus integral compensator' */
  boolean_T TransferFcn2_CSTATE_n;     /* '<S16>/Transfer Fcn.2' */
  boolean_T TransferFcn1_CSTATE_k;     /* '<S16>/Transfer Fcn.1' */
  boolean_T ActuatorModel_CSTATE_f;    /* '<S3>/Actuator Model' */
  boolean_T Wgustmodel_CSTATE_i[2];    /* '<S18>/W-gust model' */
  boolean_T Qgustmodel_CSTATE_k;       /* '<S18>/Q-gust model' */
  boolean_T AlphasensorLowpassFilter_CSTA_i;/* '<S17>/Alpha-sensor Low-pass Filter' */
  boolean_T StickPrefilter_CSTATE_j;   /* '<S17>/Stick Prefilter' */
  boolean_T PitchRateLeadFilter_CSTATE_n;/* '<S17>/Pitch Rate Lead Filter' */
  boolean_T Proportionalplusintegralcompe_h;/* '<S17>/Proportional plus integral compensator' */
  boolean_T TransferFcn2_CSTATE_e;     /* '<S21>/Transfer Fcn.2' */
  boolean_T TransferFcn1_CSTATE_j;     /* '<S21>/Transfer Fcn.1' */
  boolean_T ActuatorModel_CSTATE_p;    /* '<S4>/Actuator Model' */
  boolean_T Wgustmodel_CSTATE_k[2];    /* '<S23>/W-gust model' */
  boolean_T Qgustmodel_CSTATE_a;       /* '<S23>/Q-gust model' */
  boolean_T AlphasensorLowpassFilter_CSTA_k;/* '<S22>/Alpha-sensor Low-pass Filter' */
  boolean_T StickPrefilter_CSTATE_ju;  /* '<S22>/Stick Prefilter' */
  boolean_T PitchRateLeadFilter_CSTATE_e;/* '<S22>/Pitch Rate Lead Filter' */
  boolean_T Proportionalplusintegralcompe_j;/* '<S22>/Proportional plus integral compensator' */
  boolean_T TransferFcn2_CSTATE_k;     /* '<S26>/Transfer Fcn.2' */
  boolean_T TransferFcn1_CSTATE_pe;    /* '<S26>/Transfer Fcn.1' */
  boolean_T ActuatorModel_CSTATE_o;    /* '<S5>/Actuator Model' */
  boolean_T Wgustmodel_CSTATE_if[2];   /* '<S28>/W-gust model' */
  boolean_T Qgustmodel_CSTATE_m;       /* '<S28>/Q-gust model' */
  boolean_T AlphasensorLowpassFilter_CST_ku;/* '<S27>/Alpha-sensor Low-pass Filter' */
  boolean_T StickPrefilter_CSTATE_m;   /* '<S27>/Stick Prefilter' */
  boolean_T PitchRateLeadFilter_CSTATE_f;/* '<S27>/Pitch Rate Lead Filter' */
  boolean_T Proportionalplusintegralcompe_k;/* '<S27>/Proportional plus integral compensator' */
} StateDisabled_f14tmp5;

#ifndef ODE4_INTG
#define ODE4_INTG

/* ODE4 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[4];                        /* derivatives */
} ODE4_IntgData;

#endif

/* Backward compatible GRT Identifiers */
#define rtB                            f14tmp5_B
#define BlockIO                        BlockIO_f14tmp5
#define rtX                            f14tmp5_X
#define ContinuousStates               ContinuousStates_f14tmp5
#define rtXdot                         f14tmp5_Xdot
#define StateDerivatives               StateDerivatives_f14tmp5
#define tXdis                          f14tmp5_Xdis
#define StateDisabled                  StateDisabled_f14tmp5
#define rtP                            f14tmp5_P
#define Parameters                     Parameters_f14tmp5
#define rtDWork                        f14tmp5_DWork
#define D_Work                         D_Work_f14tmp5

/* Parameters (auto storage) */
struct Parameters_f14tmp5_ {
  real_T TransferFcn2_A;               /* Computed Parameter: TransferFcn2_A
                                        * Referenced by: '<S6>/Transfer Fcn.2'
                                        */
  real_T TransferFcn2_C;               /* Computed Parameter: TransferFcn2_C
                                        * Referenced by: '<S6>/Transfer Fcn.2'
                                        */
  real_T Gain5_Gain;                   /* Expression: 1/Uo
                                        * Referenced by: '<S1>/Gain5'
                                        */
  real_T TransferFcn1_A;               /* Computed Parameter: TransferFcn1_A
                                        * Referenced by: '<S6>/Transfer Fcn.1'
                                        */
  real_T TransferFcn1_C;               /* Computed Parameter: TransferFcn1_C
                                        * Referenced by: '<S6>/Transfer Fcn.1'
                                        */
  real_T Gain1_Gain;                   /* Expression: 22.8
                                        * Referenced by: '<S9>/Gain1'
                                        */
  real_T Constant_Value;               /* Expression: Uo
                                        * Referenced by: '<S9>/Constant'
                                        */
  real_T Gain2_Gain;                   /* Expression: 1/g
                                        * Referenced by: '<S9>/Gain2'
                                        */
  real_T Pilot_Amplitude;              /* Expression: 1
                                        * Referenced by: '<S1>/Pilot'
                                        */
  real_T Pilot_Frequency;              /* Computed Parameter: Pilot_Frequency
                                        * Referenced by: '<S1>/Pilot'
                                        */
  real_T ActuatorModel_A;              /* Computed Parameter: ActuatorModel_A
                                        * Referenced by: '<S1>/Actuator Model'
                                        */
  real_T ActuatorModel_C;              /* Computed Parameter: ActuatorModel_C
                                        * Referenced by: '<S1>/Actuator Model'
                                        */
  real_T Gain3_Gain;                   /* Expression: Uo
                                        * Referenced by: '<S6>/Gain3'
                                        */
  real_T Gain4_Gain;                   /* Expression: Mw
                                        * Referenced by: '<S6>/Gain4'
                                        */
  real_T Gain5_Gain_j;                 /* Expression: Zd
                                        * Referenced by: '<S6>/Gain5'
                                        */
  real_T Gain6_Gain;                   /* Expression: Md
                                        * Referenced by: '<S6>/Gain6'
                                        */
  real_T Wgustmodel_A[2];              /* Computed Parameter: Wgustmodel_A
                                        * Referenced by: '<S8>/W-gust model'
                                        */
  real_T Wgustmodel_C[2];              /* Computed Parameter: Wgustmodel_C
                                        * Referenced by: '<S8>/W-gust model'
                                        */
  real_T Gain_Gain;                    /* Expression: Zw
                                        * Referenced by: '<S1>/Gain'
                                        */
  real_T Gain2_Gain_p;                 /* Expression: Mw
                                        * Referenced by: '<S1>/Gain2'
                                        */
  real_T Qgustmodel_A;                 /* Computed Parameter: Qgustmodel_A
                                        * Referenced by: '<S8>/Q-gust model'
                                        */
  real_T Qgustmodel_C;                 /* Computed Parameter: Qgustmodel_C
                                        * Referenced by: '<S8>/Q-gust model'
                                        */
  real_T Qgustmodel_D;                 /* Computed Parameter: Qgustmodel_D
                                        * Referenced by: '<S8>/Q-gust model'
                                        */
  real_T Gain1_Gain_h;                 /* Expression: Mq
                                        * Referenced by: '<S1>/Gain1'
                                        */
  real_T AlphasensorLowpassFilter_A;   /* Computed Parameter: AlphasensorLowpassFilter_A
                                        * Referenced by: '<S7>/Alpha-sensor Low-pass Filter'
                                        */
  real_T AlphasensorLowpassFilter_C;   /* Computed Parameter: AlphasensorLowpassFilter_C
                                        * Referenced by: '<S7>/Alpha-sensor Low-pass Filter'
                                        */
  real_T StickPrefilter_A;             /* Computed Parameter: StickPrefilter_A
                                        * Referenced by: '<S7>/Stick Prefilter'
                                        */
  real_T StickPrefilter_C;             /* Computed Parameter: StickPrefilter_C
                                        * Referenced by: '<S7>/Stick Prefilter'
                                        */
  real_T PitchRateLeadFilter_A;        /* Computed Parameter: PitchRateLeadFilter_A
                                        * Referenced by: '<S7>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_C;        /* Computed Parameter: PitchRateLeadFilter_C
                                        * Referenced by: '<S7>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_D;        /* Computed Parameter: PitchRateLeadFilter_D
                                        * Referenced by: '<S7>/Pitch Rate Lead Filter'
                                        */
  real_T Gain2_Gain_k;                 /* Expression: Kq
                                        * Referenced by: '<S7>/Gain2'
                                        */
  real_T Gain3_Gain_i;                 /* Expression: Ka
                                        * Referenced by: '<S7>/Gain3'
                                        */
  real_T Gain_Gain_k;                  /* Expression: Kf
                                        * Referenced by: '<S7>/Gain'
                                        */
  real_T Proportionalplusintegralcompens;/* Computed Parameter: Proportionalplusintegralcompens
                                          * Referenced by: '<S7>/Proportional plus integral compensator'
                                          */
  real_T Proportionalplusintegralcompe_i;/* Computed Parameter: Proportionalplusintegralcompe_i
                                          * Referenced by: '<S7>/Proportional plus integral compensator'
                                          */
  real_T WhiteNoise_Mean;              /* Expression: 0
                                        * Referenced by: '<S10>/White Noise'
                                        */
  real_T WhiteNoise_StdDev;            /* Computed Parameter: WhiteNoise_StdDev
                                        * Referenced by: '<S10>/White Noise'
                                        */
  real_T WhiteNoise_Seed;              /* Expression: seed
                                        * Referenced by: '<S10>/White Noise'
                                        */
  real_T Output_Gain;                  /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S10>/Output'
                                        */
  real_T TransferFcn2_A_j;             /* Computed Parameter: TransferFcn2_A_j
                                        * Referenced by: '<S11>/Transfer Fcn.2'
                                        */
  real_T TransferFcn2_C_k;             /* Computed Parameter: TransferFcn2_C_k
                                        * Referenced by: '<S11>/Transfer Fcn.2'
                                        */
  real_T Gain5_Gain_o;                 /* Expression: 1/Uo
                                        * Referenced by: '<S2>/Gain5'
                                        */
  real_T TransferFcn1_A_n;             /* Computed Parameter: TransferFcn1_A_n
                                        * Referenced by: '<S11>/Transfer Fcn.1'
                                        */
  real_T TransferFcn1_C_g;             /* Computed Parameter: TransferFcn1_C_g
                                        * Referenced by: '<S11>/Transfer Fcn.1'
                                        */
  real_T Gain1_Gain_n;                 /* Expression: 22.8
                                        * Referenced by: '<S14>/Gain1'
                                        */
  real_T Constant_Value_m;             /* Expression: Uo
                                        * Referenced by: '<S14>/Constant'
                                        */
  real_T Gain2_Gain_e;                 /* Expression: 1/g
                                        * Referenced by: '<S14>/Gain2'
                                        */
  real_T Pilot_Amplitude_n;            /* Expression: 1
                                        * Referenced by: '<S2>/Pilot'
                                        */
  real_T Pilot_Frequency_d;            /* Computed Parameter: Pilot_Frequency_d
                                        * Referenced by: '<S2>/Pilot'
                                        */
  real_T ActuatorModel_A_j;            /* Computed Parameter: ActuatorModel_A_j
                                        * Referenced by: '<S2>/Actuator Model'
                                        */
  real_T ActuatorModel_C_f;            /* Computed Parameter: ActuatorModel_C_f
                                        * Referenced by: '<S2>/Actuator Model'
                                        */
  real_T Gain3_Gain_k;                 /* Expression: Uo
                                        * Referenced by: '<S11>/Gain3'
                                        */
  real_T Gain4_Gain_f;                 /* Expression: Mw
                                        * Referenced by: '<S11>/Gain4'
                                        */
  real_T Gain5_Gain_g;                 /* Expression: Zd
                                        * Referenced by: '<S11>/Gain5'
                                        */
  real_T Gain6_Gain_b;                 /* Expression: Md
                                        * Referenced by: '<S11>/Gain6'
                                        */
  real_T Wgustmodel_A_l[2];            /* Computed Parameter: Wgustmodel_A_l
                                        * Referenced by: '<S13>/W-gust model'
                                        */
  real_T Wgustmodel_C_a[2];            /* Computed Parameter: Wgustmodel_C_a
                                        * Referenced by: '<S13>/W-gust model'
                                        */
  real_T Gain_Gain_l;                  /* Expression: Zw
                                        * Referenced by: '<S2>/Gain'
                                        */
  real_T Gain2_Gain_h;                 /* Expression: Mw
                                        * Referenced by: '<S2>/Gain2'
                                        */
  real_T Qgustmodel_A_e;               /* Computed Parameter: Qgustmodel_A_e
                                        * Referenced by: '<S13>/Q-gust model'
                                        */
  real_T Qgustmodel_C_p;               /* Computed Parameter: Qgustmodel_C_p
                                        * Referenced by: '<S13>/Q-gust model'
                                        */
  real_T Qgustmodel_D_c;               /* Computed Parameter: Qgustmodel_D_c
                                        * Referenced by: '<S13>/Q-gust model'
                                        */
  real_T Gain1_Gain_p;                 /* Expression: Mq
                                        * Referenced by: '<S2>/Gain1'
                                        */
  real_T AlphasensorLowpassFilter_A_d; /* Computed Parameter: AlphasensorLowpassFilter_A_d
                                        * Referenced by: '<S12>/Alpha-sensor Low-pass Filter'
                                        */
  real_T AlphasensorLowpassFilter_C_g; /* Computed Parameter: AlphasensorLowpassFilter_C_g
                                        * Referenced by: '<S12>/Alpha-sensor Low-pass Filter'
                                        */
  real_T StickPrefilter_A_c;           /* Computed Parameter: StickPrefilter_A_c
                                        * Referenced by: '<S12>/Stick Prefilter'
                                        */
  real_T StickPrefilter_C_p;           /* Computed Parameter: StickPrefilter_C_p
                                        * Referenced by: '<S12>/Stick Prefilter'
                                        */
  real_T PitchRateLeadFilter_A_c;      /* Computed Parameter: PitchRateLeadFilter_A_c
                                        * Referenced by: '<S12>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_C_l;      /* Computed Parameter: PitchRateLeadFilter_C_l
                                        * Referenced by: '<S12>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_D_f;      /* Computed Parameter: PitchRateLeadFilter_D_f
                                        * Referenced by: '<S12>/Pitch Rate Lead Filter'
                                        */
  real_T Gain2_Gain_et;                /* Expression: Kq
                                        * Referenced by: '<S12>/Gain2'
                                        */
  real_T Gain3_Gain_b;                 /* Expression: Ka
                                        * Referenced by: '<S12>/Gain3'
                                        */
  real_T Gain_Gain_a;                  /* Expression: Kf
                                        * Referenced by: '<S12>/Gain'
                                        */
  real_T Proportionalplusintegralcompe_d;/* Computed Parameter: Proportionalplusintegralcompe_d
                                          * Referenced by: '<S12>/Proportional plus integral compensator'
                                          */
  real_T Proportionalplusintegralcomp_mx;/* Computed Parameter: Proportionalplusintegralcomp_mx
                                          * Referenced by: '<S12>/Proportional plus integral compensator'
                                          */
  real_T WhiteNoise_Mean_j;            /* Expression: 0
                                        * Referenced by: '<S15>/White Noise'
                                        */
  real_T WhiteNoise_StdDev_n;          /* Computed Parameter: WhiteNoise_StdDev_n
                                        * Referenced by: '<S15>/White Noise'
                                        */
  real_T WhiteNoise_Seed_i;            /* Expression: seed
                                        * Referenced by: '<S15>/White Noise'
                                        */
  real_T Output_Gain_l;                /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S15>/Output'
                                        */
  real_T TransferFcn2_A_l;             /* Computed Parameter: TransferFcn2_A_l
                                        * Referenced by: '<S16>/Transfer Fcn.2'
                                        */
  real_T TransferFcn2_C_a;             /* Computed Parameter: TransferFcn2_C_a
                                        * Referenced by: '<S16>/Transfer Fcn.2'
                                        */
  real_T Gain5_Gain_c;                 /* Expression: 1/Uo
                                        * Referenced by: '<S3>/Gain5'
                                        */
  real_T TransferFcn1_A_d;             /* Computed Parameter: TransferFcn1_A_d
                                        * Referenced by: '<S16>/Transfer Fcn.1'
                                        */
  real_T TransferFcn1_C_gb;            /* Computed Parameter: TransferFcn1_C_gb
                                        * Referenced by: '<S16>/Transfer Fcn.1'
                                        */
  real_T Gain1_Gain_e;                 /* Expression: 22.8
                                        * Referenced by: '<S19>/Gain1'
                                        */
  real_T Constant_Value_b;             /* Expression: Uo
                                        * Referenced by: '<S19>/Constant'
                                        */
  real_T Gain2_Gain_h5;                /* Expression: 1/g
                                        * Referenced by: '<S19>/Gain2'
                                        */
  real_T Pilot_Amplitude_e;            /* Expression: 1
                                        * Referenced by: '<S3>/Pilot'
                                        */
  real_T Pilot_Frequency_k;            /* Computed Parameter: Pilot_Frequency_k
                                        * Referenced by: '<S3>/Pilot'
                                        */
  real_T ActuatorModel_A_g;            /* Computed Parameter: ActuatorModel_A_g
                                        * Referenced by: '<S3>/Actuator Model'
                                        */
  real_T ActuatorModel_C_b;            /* Computed Parameter: ActuatorModel_C_b
                                        * Referenced by: '<S3>/Actuator Model'
                                        */
  real_T Gain3_Gain_c;                 /* Expression: Uo
                                        * Referenced by: '<S16>/Gain3'
                                        */
  real_T Gain4_Gain_j;                 /* Expression: Mw
                                        * Referenced by: '<S16>/Gain4'
                                        */
  real_T Gain5_Gain_p;                 /* Expression: Zd
                                        * Referenced by: '<S16>/Gain5'
                                        */
  real_T Gain6_Gain_f;                 /* Expression: Md
                                        * Referenced by: '<S16>/Gain6'
                                        */
  real_T Wgustmodel_A_m[2];            /* Computed Parameter: Wgustmodel_A_m
                                        * Referenced by: '<S18>/W-gust model'
                                        */
  real_T Wgustmodel_C_m[2];            /* Computed Parameter: Wgustmodel_C_m
                                        * Referenced by: '<S18>/W-gust model'
                                        */
  real_T Gain_Gain_d;                  /* Expression: Zw
                                        * Referenced by: '<S3>/Gain'
                                        */
  real_T Gain2_Gain_g;                 /* Expression: Mw
                                        * Referenced by: '<S3>/Gain2'
                                        */
  real_T Qgustmodel_A_b;               /* Computed Parameter: Qgustmodel_A_b
                                        * Referenced by: '<S18>/Q-gust model'
                                        */
  real_T Qgustmodel_C_j;               /* Computed Parameter: Qgustmodel_C_j
                                        * Referenced by: '<S18>/Q-gust model'
                                        */
  real_T Qgustmodel_D_i;               /* Computed Parameter: Qgustmodel_D_i
                                        * Referenced by: '<S18>/Q-gust model'
                                        */
  real_T Gain1_Gain_f;                 /* Expression: Mq
                                        * Referenced by: '<S3>/Gain1'
                                        */
  real_T AlphasensorLowpassFilter_A_c; /* Computed Parameter: AlphasensorLowpassFilter_A_c
                                        * Referenced by: '<S17>/Alpha-sensor Low-pass Filter'
                                        */
  real_T AlphasensorLowpassFilter_C_gf;/* Computed Parameter: AlphasensorLowpassFilter_C_gf
                                        * Referenced by: '<S17>/Alpha-sensor Low-pass Filter'
                                        */
  real_T StickPrefilter_A_e;           /* Computed Parameter: StickPrefilter_A_e
                                        * Referenced by: '<S17>/Stick Prefilter'
                                        */
  real_T StickPrefilter_C_j;           /* Computed Parameter: StickPrefilter_C_j
                                        * Referenced by: '<S17>/Stick Prefilter'
                                        */
  real_T PitchRateLeadFilter_A_i;      /* Computed Parameter: PitchRateLeadFilter_A_i
                                        * Referenced by: '<S17>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_C_k;      /* Computed Parameter: PitchRateLeadFilter_C_k
                                        * Referenced by: '<S17>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_D_ft;     /* Computed Parameter: PitchRateLeadFilter_D_ft
                                        * Referenced by: '<S17>/Pitch Rate Lead Filter'
                                        */
  real_T Gain2_Gain_eh;                /* Expression: Kq
                                        * Referenced by: '<S17>/Gain2'
                                        */
  real_T Gain3_Gain_m;                 /* Expression: Ka
                                        * Referenced by: '<S17>/Gain3'
                                        */
  real_T Gain_Gain_j;                  /* Expression: Kf
                                        * Referenced by: '<S17>/Gain'
                                        */
  real_T Proportionalplusintegralcompe_h;/* Computed Parameter: Proportionalplusintegralcompe_h
                                          * Referenced by: '<S17>/Proportional plus integral compensator'
                                          */
  real_T Proportionalplusintegralcompe_l;/* Computed Parameter: Proportionalplusintegralcompe_l
                                          * Referenced by: '<S17>/Proportional plus integral compensator'
                                          */
  real_T WhiteNoise_Mean_k;            /* Expression: 0
                                        * Referenced by: '<S20>/White Noise'
                                        */
  real_T WhiteNoise_StdDev_g;          /* Computed Parameter: WhiteNoise_StdDev_g
                                        * Referenced by: '<S20>/White Noise'
                                        */
  real_T WhiteNoise_Seed_j;            /* Expression: seed
                                        * Referenced by: '<S20>/White Noise'
                                        */
  real_T Output_Gain_m;                /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S20>/Output'
                                        */
  real_T TransferFcn2_A_jz;            /* Computed Parameter: TransferFcn2_A_jz
                                        * Referenced by: '<S21>/Transfer Fcn.2'
                                        */
  real_T TransferFcn2_C_l;             /* Computed Parameter: TransferFcn2_C_l
                                        * Referenced by: '<S21>/Transfer Fcn.2'
                                        */
  real_T Gain5_Gain_j0;                /* Expression: 1/Uo
                                        * Referenced by: '<S4>/Gain5'
                                        */
  real_T TransferFcn1_A_a;             /* Computed Parameter: TransferFcn1_A_a
                                        * Referenced by: '<S21>/Transfer Fcn.1'
                                        */
  real_T TransferFcn1_C_l;             /* Computed Parameter: TransferFcn1_C_l
                                        * Referenced by: '<S21>/Transfer Fcn.1'
                                        */
  real_T Gain1_Gain_fm;                /* Expression: 22.8
                                        * Referenced by: '<S24>/Gain1'
                                        */
  real_T Constant_Value_f;             /* Expression: Uo
                                        * Referenced by: '<S24>/Constant'
                                        */
  real_T Gain2_Gain_kz;                /* Expression: 1/g
                                        * Referenced by: '<S24>/Gain2'
                                        */
  real_T Pilot_Amplitude_o;            /* Expression: 1
                                        * Referenced by: '<S4>/Pilot'
                                        */
  real_T Pilot_Frequency_i;            /* Computed Parameter: Pilot_Frequency_i
                                        * Referenced by: '<S4>/Pilot'
                                        */
  real_T ActuatorModel_A_p;            /* Computed Parameter: ActuatorModel_A_p
                                        * Referenced by: '<S4>/Actuator Model'
                                        */
  real_T ActuatorModel_C_l;            /* Computed Parameter: ActuatorModel_C_l
                                        * Referenced by: '<S4>/Actuator Model'
                                        */
  real_T Gain3_Gain_p;                 /* Expression: Uo
                                        * Referenced by: '<S21>/Gain3'
                                        */
  real_T Gain4_Gain_c;                 /* Expression: Mw
                                        * Referenced by: '<S21>/Gain4'
                                        */
  real_T Gain5_Gain_j0q;               /* Expression: Zd
                                        * Referenced by: '<S21>/Gain5'
                                        */
  real_T Gain6_Gain_j;                 /* Expression: Md
                                        * Referenced by: '<S21>/Gain6'
                                        */
  real_T Wgustmodel_A_b[2];            /* Computed Parameter: Wgustmodel_A_b
                                        * Referenced by: '<S23>/W-gust model'
                                        */
  real_T Wgustmodel_C_g[2];            /* Computed Parameter: Wgustmodel_C_g
                                        * Referenced by: '<S23>/W-gust model'
                                        */
  real_T Gain_Gain_h;                  /* Expression: Zw
                                        * Referenced by: '<S4>/Gain'
                                        */
  real_T Gain2_Gain_m;                 /* Expression: Mw
                                        * Referenced by: '<S4>/Gain2'
                                        */
  real_T Qgustmodel_A_g;               /* Computed Parameter: Qgustmodel_A_g
                                        * Referenced by: '<S23>/Q-gust model'
                                        */
  real_T Qgustmodel_C_a;               /* Computed Parameter: Qgustmodel_C_a
                                        * Referenced by: '<S23>/Q-gust model'
                                        */
  real_T Qgustmodel_D_a;               /* Computed Parameter: Qgustmodel_D_a
                                        * Referenced by: '<S23>/Q-gust model'
                                        */
  real_T Gain1_Gain_d;                 /* Expression: Mq
                                        * Referenced by: '<S4>/Gain1'
                                        */
  real_T AlphasensorLowpassFilter_A_p; /* Computed Parameter: AlphasensorLowpassFilter_A_p
                                        * Referenced by: '<S22>/Alpha-sensor Low-pass Filter'
                                        */
  real_T AlphasensorLowpassFilter_C_m; /* Computed Parameter: AlphasensorLowpassFilter_C_m
                                        * Referenced by: '<S22>/Alpha-sensor Low-pass Filter'
                                        */
  real_T StickPrefilter_A_d;           /* Computed Parameter: StickPrefilter_A_d
                                        * Referenced by: '<S22>/Stick Prefilter'
                                        */
  real_T StickPrefilter_C_h;           /* Computed Parameter: StickPrefilter_C_h
                                        * Referenced by: '<S22>/Stick Prefilter'
                                        */
  real_T PitchRateLeadFilter_A_p;      /* Computed Parameter: PitchRateLeadFilter_A_p
                                        * Referenced by: '<S22>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_C_b;      /* Computed Parameter: PitchRateLeadFilter_C_b
                                        * Referenced by: '<S22>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_D_b;      /* Computed Parameter: PitchRateLeadFilter_D_b
                                        * Referenced by: '<S22>/Pitch Rate Lead Filter'
                                        */
  real_T Gain2_Gain_b;                 /* Expression: Kq
                                        * Referenced by: '<S22>/Gain2'
                                        */
  real_T Gain3_Gain_a;                 /* Expression: Ka
                                        * Referenced by: '<S22>/Gain3'
                                        */
  real_T Gain_Gain_f;                  /* Expression: Kf
                                        * Referenced by: '<S22>/Gain'
                                        */
  real_T Proportionalplusintegralcomp_kg;/* Computed Parameter: Proportionalplusintegralcomp_kg
                                          * Referenced by: '<S22>/Proportional plus integral compensator'
                                          */
  real_T Proportionalplusintegralcompe_j;/* Computed Parameter: Proportionalplusintegralcompe_j
                                          * Referenced by: '<S22>/Proportional plus integral compensator'
                                          */
  real_T WhiteNoise_Mean_n;            /* Expression: 0
                                        * Referenced by: '<S25>/White Noise'
                                        */
  real_T WhiteNoise_StdDev_f;          /* Computed Parameter: WhiteNoise_StdDev_f
                                        * Referenced by: '<S25>/White Noise'
                                        */
  real_T WhiteNoise_Seed_c;            /* Expression: seed
                                        * Referenced by: '<S25>/White Noise'
                                        */
  real_T Output_Gain_p;                /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S25>/Output'
                                        */
  real_T TransferFcn2_A_c;             /* Computed Parameter: TransferFcn2_A_c
                                        * Referenced by: '<S26>/Transfer Fcn.2'
                                        */
  real_T TransferFcn2_C_e;             /* Computed Parameter: TransferFcn2_C_e
                                        * Referenced by: '<S26>/Transfer Fcn.2'
                                        */
  real_T Gain5_Gain_f;                 /* Expression: 1/Uo
                                        * Referenced by: '<S5>/Gain5'
                                        */
  real_T TransferFcn1_A_o;             /* Computed Parameter: TransferFcn1_A_o
                                        * Referenced by: '<S26>/Transfer Fcn.1'
                                        */
  real_T TransferFcn1_C_j;             /* Computed Parameter: TransferFcn1_C_j
                                        * Referenced by: '<S26>/Transfer Fcn.1'
                                        */
  real_T Gain1_Gain_m;                 /* Expression: 22.8
                                        * Referenced by: '<S29>/Gain1'
                                        */
  real_T Constant_Value_p;             /* Expression: Uo
                                        * Referenced by: '<S29>/Constant'
                                        */
  real_T Gain2_Gain_d;                 /* Expression: 1/g
                                        * Referenced by: '<S29>/Gain2'
                                        */
  real_T Pilot_Amplitude_h;            /* Expression: 1
                                        * Referenced by: '<S5>/Pilot'
                                        */
  real_T Pilot_Frequency_a;            /* Computed Parameter: Pilot_Frequency_a
                                        * Referenced by: '<S5>/Pilot'
                                        */
  real_T ActuatorModel_A_gl;           /* Computed Parameter: ActuatorModel_A_gl
                                        * Referenced by: '<S5>/Actuator Model'
                                        */
  real_T ActuatorModel_C_a;            /* Computed Parameter: ActuatorModel_C_a
                                        * Referenced by: '<S5>/Actuator Model'
                                        */
  real_T Gain3_Gain_ai;                /* Expression: Uo
                                        * Referenced by: '<S26>/Gain3'
                                        */
  real_T Gain4_Gain_d;                 /* Expression: Mw
                                        * Referenced by: '<S26>/Gain4'
                                        */
  real_T Gain5_Gain_n;                 /* Expression: Zd
                                        * Referenced by: '<S26>/Gain5'
                                        */
  real_T Gain6_Gain_n;                 /* Expression: Md
                                        * Referenced by: '<S26>/Gain6'
                                        */
  real_T Wgustmodel_A_lv[2];           /* Computed Parameter: Wgustmodel_A_lv
                                        * Referenced by: '<S28>/W-gust model'
                                        */
  real_T Wgustmodel_C_p[2];            /* Computed Parameter: Wgustmodel_C_p
                                        * Referenced by: '<S28>/W-gust model'
                                        */
  real_T Gain_Gain_c;                  /* Expression: Zw
                                        * Referenced by: '<S5>/Gain'
                                        */
  real_T Gain2_Gain_l;                 /* Expression: Mw
                                        * Referenced by: '<S5>/Gain2'
                                        */
  real_T Qgustmodel_A_gl;              /* Computed Parameter: Qgustmodel_A_gl
                                        * Referenced by: '<S28>/Q-gust model'
                                        */
  real_T Qgustmodel_C_c;               /* Computed Parameter: Qgustmodel_C_c
                                        * Referenced by: '<S28>/Q-gust model'
                                        */
  real_T Qgustmodel_D_l;               /* Computed Parameter: Qgustmodel_D_l
                                        * Referenced by: '<S28>/Q-gust model'
                                        */
  real_T Gain1_Gain_a;                 /* Expression: Mq
                                        * Referenced by: '<S5>/Gain1'
                                        */
  real_T AlphasensorLowpassFilter_A_a; /* Computed Parameter: AlphasensorLowpassFilter_A_a
                                        * Referenced by: '<S27>/Alpha-sensor Low-pass Filter'
                                        */
  real_T AlphasensorLowpassFilter_C_e; /* Computed Parameter: AlphasensorLowpassFilter_C_e
                                        * Referenced by: '<S27>/Alpha-sensor Low-pass Filter'
                                        */
  real_T StickPrefilter_A_ee;          /* Computed Parameter: StickPrefilter_A_ee
                                        * Referenced by: '<S27>/Stick Prefilter'
                                        */
  real_T StickPrefilter_C_b;           /* Computed Parameter: StickPrefilter_C_b
                                        * Referenced by: '<S27>/Stick Prefilter'
                                        */
  real_T PitchRateLeadFilter_A_m;      /* Computed Parameter: PitchRateLeadFilter_A_m
                                        * Referenced by: '<S27>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_C_a;      /* Computed Parameter: PitchRateLeadFilter_C_a
                                        * Referenced by: '<S27>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_D_a;      /* Computed Parameter: PitchRateLeadFilter_D_a
                                        * Referenced by: '<S27>/Pitch Rate Lead Filter'
                                        */
  real_T Gain2_Gain_n;                 /* Expression: Kq
                                        * Referenced by: '<S27>/Gain2'
                                        */
  real_T Gain3_Gain_h;                 /* Expression: Ka
                                        * Referenced by: '<S27>/Gain3'
                                        */
  real_T Gain_Gain_o;                  /* Expression: Kf
                                        * Referenced by: '<S27>/Gain'
                                        */
  real_T Proportionalplusintegralcomp_mw;/* Computed Parameter: Proportionalplusintegralcomp_mw
                                          * Referenced by: '<S27>/Proportional plus integral compensator'
                                          */
  real_T Proportionalplusintegralcomp_jp;/* Computed Parameter: Proportionalplusintegralcomp_jp
                                          * Referenced by: '<S27>/Proportional plus integral compensator'
                                          */
  real_T WhiteNoise_Mean_b;            /* Expression: 0
                                        * Referenced by: '<S30>/White Noise'
                                        */
  real_T WhiteNoise_StdDev_k;          /* Computed Parameter: WhiteNoise_StdDev_k
                                        * Referenced by: '<S30>/White Noise'
                                        */
  real_T WhiteNoise_Seed_g;            /* Expression: seed
                                        * Referenced by: '<S30>/White Noise'
                                        */
  real_T Output_Gain_pk;               /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S30>/Output'
                                        */
};

/* Real-time Model Data Structure */
struct tag_rtM_f14tmp5 {
  const char_T *path;
  const char_T *modelName;
  struct SimStruct_tag * *childSfunctions;
  const char_T *errorStatus;
  SS_SimMode simMode;
  RTWLogInfo *rtwLogInfo;
  RTWExtModeInfo *extModeInfo;
  RTWSolverInfo solverInfo;
  RTWSolverInfo *solverInfoPtr;
  void *sfcnInfo;

  /*
   * DataMapInfo:
   * The following substructure contains information regarding
   * structures generated in the model's C API.
   */
  struct {
    rtwCAPI_ModelMappingInfo mmi;
  } DataMapInfo;

  /*
   * ModelData:
   * The following substructure contains information regarding
   * the data used in the model.
   */
  struct {
    void *blockIO;
    const void *constBlockIO;
    void *defaultParam;
    ZCSigState *prevZCSigState;
    real_T *contStates;
    real_T *derivs;
    void *zcSignalValues;
    void *inputs;
    void *outputs;
    boolean_T *contStateDisabled;
    boolean_T zCCacheNeedsReset;
    boolean_T derivCacheNeedsReset;
    boolean_T blkStateChange;
    real_T odeY[50];
    real_T odeF[4][50];
    ODE4_IntgData intgData;
  } ModelData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T checksums[4];
    uint32_T options;
    int_T numContStates;
    int_T numU;
    int_T numY;
    int_T numSampTimes;
    int_T numBlocks;
    int_T numBlockIO;
    int_T numBlockPrms;
    int_T numDwork;
    int_T numSFcnPrms;
    int_T numSFcns;
    int_T numIports;
    int_T numOports;
    int_T numNonSampZCs;
    int_T sysDirFeedThru;
    int_T rtwGenSfcn;
  } Sizes;

  /*
   * SpecialInfo:
   * The following substructure contains special information
   * related to other components that are dependent on RTW.
   */
  struct {
    const void *mappingInfo;
    void *xpcData;
  } SpecialInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T stepSize;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    time_T stepSize1;
    uint32_T clockTick2;
    uint32_T clockTickH2;
    time_T stepSize2;
    struct {
      uint8_T TID[3];
    } TaskCounters;

    time_T tStart;
    time_T tFinal;
    time_T timeOfLastOutput;
    void *timingData;
    real_T *varNextHitTimesList;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *sampleTimes;
    time_T *offsetTimes;
    int_T *sampleTimeTaskIDPtr;
    int_T *sampleHits;
    int_T *perTaskSampleHits;
    time_T *t;
    time_T sampleTimesArray[3];
    time_T offsetTimesArray[3];
    int_T sampleTimeTaskIDArray[3];
    int_T sampleHitArray[3];
    int_T perTaskSampleHitsArray[9];
    time_T tArray[3];
  } Timing;

  /*
   * Work:
   * The following substructure contains information regarding
   * the work vectors in the model.
   */
  struct {
    void *dwork;
  } Work;
};

/* Block parameters (auto storage) */
extern Parameters_f14tmp5 f14tmp5_P;

/* Block signals (auto storage) */
extern BlockIO_f14tmp5 f14tmp5_B;

/* Continuous states (auto storage) */
extern ContinuousStates_f14tmp5 f14tmp5_X;

/* Block states (auto storage) */
extern D_Work_f14tmp5 f14tmp5_DWork;

/* Model entry point functions */
extern void f14tmp5_initialize(void);
extern void f14tmp5_output(void);
extern void f14tmp5_update(void);
extern void f14tmp5_terminate(void);

/* Real-time Model object */
extern rtModel_f14tmp5 *const f14tmp5_rtM;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'f14tmp5'
 * '<S1>'   : 'f14tmp5/Subsystem'
 * '<S2>'   : 'f14tmp5/Subsystem1'
 * '<S3>'   : 'f14tmp5/Subsystem2'
 * '<S4>'   : 'f14tmp5/Subsystem3'
 * '<S5>'   : 'f14tmp5/Subsystem4'
 * '<S6>'   : 'f14tmp5/Subsystem/Aircraft Dynamics Model'
 * '<S7>'   : 'f14tmp5/Subsystem/Controller'
 * '<S8>'   : 'f14tmp5/Subsystem/Dryden Wind Gust Models'
 * '<S9>'   : 'f14tmp5/Subsystem/Nz pilot calculation'
 * '<S10>'  : 'f14tmp5/Subsystem/Dryden Wind Gust Models/Band-Limited White Noise'
 * '<S11>'  : 'f14tmp5/Subsystem1/Aircraft Dynamics Model'
 * '<S12>'  : 'f14tmp5/Subsystem1/Controller'
 * '<S13>'  : 'f14tmp5/Subsystem1/Dryden Wind Gust Models'
 * '<S14>'  : 'f14tmp5/Subsystem1/Nz pilot calculation'
 * '<S15>'  : 'f14tmp5/Subsystem1/Dryden Wind Gust Models/Band-Limited White Noise'
 * '<S16>'  : 'f14tmp5/Subsystem2/Aircraft Dynamics Model'
 * '<S17>'  : 'f14tmp5/Subsystem2/Controller'
 * '<S18>'  : 'f14tmp5/Subsystem2/Dryden Wind Gust Models'
 * '<S19>'  : 'f14tmp5/Subsystem2/Nz pilot calculation'
 * '<S20>'  : 'f14tmp5/Subsystem2/Dryden Wind Gust Models/Band-Limited White Noise'
 * '<S21>'  : 'f14tmp5/Subsystem3/Aircraft Dynamics Model'
 * '<S22>'  : 'f14tmp5/Subsystem3/Controller'
 * '<S23>'  : 'f14tmp5/Subsystem3/Dryden Wind Gust Models'
 * '<S24>'  : 'f14tmp5/Subsystem3/Nz pilot calculation'
 * '<S25>'  : 'f14tmp5/Subsystem3/Dryden Wind Gust Models/Band-Limited White Noise'
 * '<S26>'  : 'f14tmp5/Subsystem4/Aircraft Dynamics Model'
 * '<S27>'  : 'f14tmp5/Subsystem4/Controller'
 * '<S28>'  : 'f14tmp5/Subsystem4/Dryden Wind Gust Models'
 * '<S29>'  : 'f14tmp5/Subsystem4/Nz pilot calculation'
 * '<S30>'  : 'f14tmp5/Subsystem4/Dryden Wind Gust Models/Band-Limited White Noise'
 */
#endif                                 /* RTW_HEADER_f14tmp5_h_ */
