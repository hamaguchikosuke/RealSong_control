/*
 * f14tmp25.h
 *
 * Code generation for model "f14tmp25".
 *
 * Model version              : 1.0
 * Simulink Coder version : 8.3 (R2012b) 20-Jul-2012
 * C source code generated on : Mon Sep 16 12:50:49 2013
 *
 * Target selection: xpctarget.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#ifndef RTW_HEADER_f14tmp25_h_
#define RTW_HEADER_f14tmp25_h_
#include "rtw_modelmap.h"
#ifndef f14tmp25_COMMON_INCLUDES_
# define f14tmp25_COMMON_INCLUDES_
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
#endif                                 /* f14tmp25_COMMON_INCLUDES_ */

#include "f14tmp25_types.h"

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
#define f14tmp25_rtModel               rtModel_f14tmp25

/* user code (top of export header file) */
#include "xpcdatatypes.h"

/* Block signals (auto storage) */
typedef struct {
  real_T TransferFcn2;                 /* '<S26>/Transfer Fcn.2' */
  real_T Gain5;                        /* '<S1>/Gain5' */
  real_T Derivative;                   /* '<S29>/Derivative' */
  real_T TransferFcn1;                 /* '<S26>/Transfer Fcn.1' */
  real_T Derivative1;                  /* '<S29>/Derivative1' */
  real_T Gain1;                        /* '<S29>/Gain1' */
  real_T Product;                      /* '<S29>/Product' */
  real_T Sum1;                         /* '<S29>/Sum1' */
  real_T Gain2;                        /* '<S29>/Gain2' */
  real_T Pilot;                        /* '<S1>/Pilot' */
  real_T Sum1_k;                       /* '<S1>/Sum1' */
  real_T ActuatorModel;                /* '<S1>/Actuator Model' */
  real_T Gain3;                        /* '<S26>/Gain3' */
  real_T Gain4;                        /* '<S26>/Gain4' */
  real_T Gain5_b;                      /* '<S26>/Gain5' */
  real_T Gain6;                        /* '<S26>/Gain6' */
  real_T Wgustmodel;                   /* '<S28>/W-gust model' */
  real_T Gain;                         /* '<S1>/Gain' */
  real_T Sum1_o;                       /* '<S26>/Sum1' */
  real_T Gain2_f;                      /* '<S1>/Gain2' */
  real_T Qgustmodel;                   /* '<S28>/Q-gust model' */
  real_T Gain1_h;                      /* '<S1>/Gain1' */
  real_T Sum;                          /* '<S1>/Sum' */
  real_T Sum2;                         /* '<S26>/Sum2' */
  real_T AlphasensorLowpassFilter;     /* '<S27>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter;               /* '<S27>/Stick Prefilter' */
  real_T PitchRateLeadFilter;          /* '<S27>/Pitch Rate Lead Filter' */
  real_T Gain2_e;                      /* '<S27>/Gain2' */
  real_T Gain3_g;                      /* '<S27>/Gain3' */
  real_T Sum1_d;                       /* '<S27>/Sum1' */
  real_T Sum2_f;                       /* '<S27>/Sum2' */
  real_T Gain_d;                       /* '<S27>/Gain' */
  real_T Proportionalplusintegralcompens;/* '<S27>/Proportional plus integral compensator' */
  real_T Sum_n;                        /* '<S27>/Sum' */
  real_T WhiteNoise;                   /* '<S30>/White Noise' */
  real_T Output;                       /* '<S30>/Output' */
  real_T TransferFcn2_b;               /* '<S31>/Transfer Fcn.2' */
  real_T Gain5_h;                      /* '<S2>/Gain5' */
  real_T Derivative_k;                 /* '<S34>/Derivative' */
  real_T TransferFcn1_a;               /* '<S31>/Transfer Fcn.1' */
  real_T Derivative1_a;                /* '<S34>/Derivative1' */
  real_T Gain1_c;                      /* '<S34>/Gain1' */
  real_T Product_a;                    /* '<S34>/Product' */
  real_T Sum1_di;                      /* '<S34>/Sum1' */
  real_T Gain2_l;                      /* '<S34>/Gain2' */
  real_T Pilot_k;                      /* '<S2>/Pilot' */
  real_T Sum1_n;                       /* '<S2>/Sum1' */
  real_T ActuatorModel_n;              /* '<S2>/Actuator Model' */
  real_T Gain3_a;                      /* '<S31>/Gain3' */
  real_T Gain4_p;                      /* '<S31>/Gain4' */
  real_T Gain5_h4;                     /* '<S31>/Gain5' */
  real_T Gain6_m;                      /* '<S31>/Gain6' */
  real_T Wgustmodel_j;                 /* '<S33>/W-gust model' */
  real_T Gain_n;                       /* '<S2>/Gain' */
  real_T Sum1_e;                       /* '<S31>/Sum1' */
  real_T Gain2_o;                      /* '<S2>/Gain2' */
  real_T Qgustmodel_c;                 /* '<S33>/Q-gust model' */
  real_T Gain1_i;                      /* '<S2>/Gain1' */
  real_T Sum_e;                        /* '<S2>/Sum' */
  real_T Sum2_c;                       /* '<S31>/Sum2' */
  real_T AlphasensorLowpassFilter_e;   /* '<S32>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_h;             /* '<S32>/Stick Prefilter' */
  real_T PitchRateLeadFilter_f;        /* '<S32>/Pitch Rate Lead Filter' */
  real_T Gain2_j;                      /* '<S32>/Gain2' */
  real_T Gain3_l;                      /* '<S32>/Gain3' */
  real_T Sum1_i;                       /* '<S32>/Sum1' */
  real_T Sum2_k;                       /* '<S32>/Sum2' */
  real_T Gain_e;                       /* '<S32>/Gain' */
  real_T Proportionalplusintegralcompe_j;/* '<S32>/Proportional plus integral compensator' */
  real_T Sum_l;                        /* '<S32>/Sum' */
  real_T WhiteNoise_l;                 /* '<S35>/White Noise' */
  real_T Output_e;                     /* '<S35>/Output' */
  real_T TransferFcn2_d;               /* '<S36>/Transfer Fcn.2' */
  real_T Gain5_k;                      /* '<S3>/Gain5' */
  real_T Derivative_kd;                /* '<S39>/Derivative' */
  real_T TransferFcn1_b;               /* '<S36>/Transfer Fcn.1' */
  real_T Derivative1_e;                /* '<S39>/Derivative1' */
  real_T Gain1_a;                      /* '<S39>/Gain1' */
  real_T Product_d;                    /* '<S39>/Product' */
  real_T Sum1_h;                       /* '<S39>/Sum1' */
  real_T Gain2_f0;                     /* '<S39>/Gain2' */
  real_T Pilot_m;                      /* '<S3>/Pilot' */
  real_T Sum1_j;                       /* '<S3>/Sum1' */
  real_T ActuatorModel_i;              /* '<S3>/Actuator Model' */
  real_T Gain3_k;                      /* '<S36>/Gain3' */
  real_T Gain4_h;                      /* '<S36>/Gain4' */
  real_T Gain5_bp;                     /* '<S36>/Gain5' */
  real_T Gain6_l;                      /* '<S36>/Gain6' */
  real_T Wgustmodel_n;                 /* '<S38>/W-gust model' */
  real_T Gain_i;                       /* '<S3>/Gain' */
  real_T Sum1_p;                       /* '<S36>/Sum1' */
  real_T Gain2_d;                      /* '<S3>/Gain2' */
  real_T Qgustmodel_a;                 /* '<S38>/Q-gust model' */
  real_T Gain1_c5;                     /* '<S3>/Gain1' */
  real_T Sum_ec;                       /* '<S3>/Sum' */
  real_T Sum2_i;                       /* '<S36>/Sum2' */
  real_T AlphasensorLowpassFilter_m;   /* '<S37>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_j;             /* '<S37>/Stick Prefilter' */
  real_T PitchRateLeadFilter_b;        /* '<S37>/Pitch Rate Lead Filter' */
  real_T Gain2_i;                      /* '<S37>/Gain2' */
  real_T Gain3_p;                      /* '<S37>/Gain3' */
  real_T Sum1_nd;                      /* '<S37>/Sum1' */
  real_T Sum2_j;                       /* '<S37>/Sum2' */
  real_T Gain_l;                       /* '<S37>/Gain' */
  real_T Proportionalplusintegralcompe_i;/* '<S37>/Proportional plus integral compensator' */
  real_T Sum_k;                        /* '<S37>/Sum' */
  real_T WhiteNoise_g;                 /* '<S40>/White Noise' */
  real_T Output_o;                     /* '<S40>/Output' */
  real_T TransferFcn2_e;               /* '<S41>/Transfer Fcn.2' */
  real_T Gain5_bk;                     /* '<S4>/Gain5' */
  real_T Derivative_b;                 /* '<S44>/Derivative' */
  real_T TransferFcn1_o;               /* '<S41>/Transfer Fcn.1' */
  real_T Derivative1_l;                /* '<S44>/Derivative1' */
  real_T Gain1_g;                      /* '<S44>/Gain1' */
  real_T Product_g;                    /* '<S44>/Product' */
  real_T Sum1_f;                       /* '<S44>/Sum1' */
  real_T Gain2_i5;                     /* '<S44>/Gain2' */
  real_T Pilot_a;                      /* '<S4>/Pilot' */
  real_T Sum1_m;                       /* '<S4>/Sum1' */
  real_T ActuatorModel_d;              /* '<S4>/Actuator Model' */
  real_T Gain3_i;                      /* '<S41>/Gain3' */
  real_T Gain4_pj;                     /* '<S41>/Gain4' */
  real_T Gain5_j;                      /* '<S41>/Gain5' */
  real_T Gain6_j;                      /* '<S41>/Gain6' */
  real_T Wgustmodel_f;                 /* '<S43>/W-gust model' */
  real_T Gain_g;                       /* '<S4>/Gain' */
  real_T Sum1_b;                       /* '<S41>/Sum1' */
  real_T Gain2_h;                      /* '<S4>/Gain2' */
  real_T Qgustmodel_o;                 /* '<S43>/Q-gust model' */
  real_T Gain1_gb;                     /* '<S4>/Gain1' */
  real_T Sum_d;                        /* '<S4>/Sum' */
  real_T Sum2_p;                       /* '<S41>/Sum2' */
  real_T AlphasensorLowpassFilter_k;   /* '<S42>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_d;             /* '<S42>/Stick Prefilter' */
  real_T PitchRateLeadFilter_e;        /* '<S42>/Pitch Rate Lead Filter' */
  real_T Gain2_ih;                     /* '<S42>/Gain2' */
  real_T Gain3_b;                      /* '<S42>/Gain3' */
  real_T Sum1_g;                       /* '<S42>/Sum1' */
  real_T Sum2_b;                       /* '<S42>/Sum2' */
  real_T Gain_h;                       /* '<S42>/Gain' */
  real_T Proportionalplusintegralcompe_c;/* '<S42>/Proportional plus integral compensator' */
  real_T Sum_nw;                       /* '<S42>/Sum' */
  real_T WhiteNoise_d;                 /* '<S45>/White Noise' */
  real_T Output_g;                     /* '<S45>/Output' */
  real_T TransferFcn2_en;              /* '<S46>/Transfer Fcn.2' */
  real_T Gain5_hk;                     /* '<S5>/Gain5' */
  real_T Derivative_j;                 /* '<S49>/Derivative' */
  real_T TransferFcn1_c;               /* '<S46>/Transfer Fcn.1' */
  real_T Derivative1_p;                /* '<S49>/Derivative1' */
  real_T Gain1_ax;                     /* '<S49>/Gain1' */
  real_T Product_h;                    /* '<S49>/Product' */
  real_T Sum1_fy;                      /* '<S49>/Sum1' */
  real_T Gain2_in;                     /* '<S49>/Gain2' */
  real_T Pilot_l;                      /* '<S5>/Pilot' */
  real_T Sum1_k2;                      /* '<S5>/Sum1' */
  real_T ActuatorModel_j;              /* '<S5>/Actuator Model' */
  real_T Gain3_h;                      /* '<S46>/Gain3' */
  real_T Gain4_f;                      /* '<S46>/Gain4' */
  real_T Gain5_br;                     /* '<S46>/Gain5' */
  real_T Gain6_a;                      /* '<S46>/Gain6' */
  real_T Wgustmodel_c;                 /* '<S48>/W-gust model' */
  real_T Gain_o;                       /* '<S5>/Gain' */
  real_T Sum1_ez;                      /* '<S46>/Sum1' */
  real_T Gain2_is;                     /* '<S5>/Gain2' */
  real_T Qgustmodel_m;                 /* '<S48>/Q-gust model' */
  real_T Gain1_b;                      /* '<S5>/Gain1' */
  real_T Sum_m;                        /* '<S5>/Sum' */
  real_T Sum2_e;                       /* '<S46>/Sum2' */
  real_T AlphasensorLowpassFilter_j;   /* '<S47>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_jd;            /* '<S47>/Stick Prefilter' */
  real_T PitchRateLeadFilter_k;        /* '<S47>/Pitch Rate Lead Filter' */
  real_T Gain2_dg;                     /* '<S47>/Gain2' */
  real_T Gain3_h5;                     /* '<S47>/Gain3' */
  real_T Sum1_l;                       /* '<S47>/Sum1' */
  real_T Sum2_m;                       /* '<S47>/Sum2' */
  real_T Gain_do;                      /* '<S47>/Gain' */
  real_T Proportionalplusintegralcompe_n;/* '<S47>/Proportional plus integral compensator' */
  real_T Sum_h;                        /* '<S47>/Sum' */
  real_T WhiteNoise_e;                 /* '<S50>/White Noise' */
  real_T Output_a;                     /* '<S50>/Output' */
  real_T TransferFcn2_eu;              /* '<S51>/Transfer Fcn.2' */
  real_T Gain5_n;                      /* '<S6>/Gain5' */
  real_T Derivative_j5;                /* '<S54>/Derivative' */
  real_T TransferFcn1_os;              /* '<S51>/Transfer Fcn.1' */
  real_T Derivative1_o;                /* '<S54>/Derivative1' */
  real_T Gain1_j;                      /* '<S54>/Gain1' */
  real_T Product_m;                    /* '<S54>/Product' */
  real_T Sum1_gd;                      /* '<S54>/Sum1' */
  real_T Gain2_jz;                     /* '<S54>/Gain2' */
  real_T Pilot_b;                      /* '<S6>/Pilot' */
  real_T Sum1_kq;                      /* '<S6>/Sum1' */
  real_T ActuatorModel_f;              /* '<S6>/Actuator Model' */
  real_T Gain3_ho;                     /* '<S51>/Gain3' */
  real_T Gain4_k;                      /* '<S51>/Gain4' */
  real_T Gain5_p;                      /* '<S51>/Gain5' */
  real_T Gain6_j0;                     /* '<S51>/Gain6' */
  real_T Wgustmodel_nc;                /* '<S53>/W-gust model' */
  real_T Gain_f;                       /* '<S6>/Gain' */
  real_T Sum1_bx;                      /* '<S51>/Sum1' */
  real_T Gain2_fb;                     /* '<S6>/Gain2' */
  real_T Qgustmodel_i;                 /* '<S53>/Q-gust model' */
  real_T Gain1_j5;                     /* '<S6>/Gain1' */
  real_T Sum_b;                        /* '<S6>/Sum' */
  real_T Sum2_o;                       /* '<S51>/Sum2' */
  real_T AlphasensorLowpassFilter_f;   /* '<S52>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_f;             /* '<S52>/Stick Prefilter' */
  real_T PitchRateLeadFilter_i;        /* '<S52>/Pitch Rate Lead Filter' */
  real_T Gain2_el;                     /* '<S52>/Gain2' */
  real_T Gain3_kr;                     /* '<S52>/Gain3' */
  real_T Sum1_hc;                      /* '<S52>/Sum1' */
  real_T Sum2_g;                       /* '<S52>/Sum2' */
  real_T Gain_nh;                      /* '<S52>/Gain' */
  real_T Proportionalplusintegralcompe_m;/* '<S52>/Proportional plus integral compensator' */
  real_T Sum_p;                        /* '<S52>/Sum' */
  real_T WhiteNoise_c;                 /* '<S55>/White Noise' */
  real_T Output_h;                     /* '<S55>/Output' */
  real_T TransferFcn2_be;              /* '<S56>/Transfer Fcn.2' */
  real_T Gain5_nt;                     /* '<S7>/Gain5' */
  real_T Derivative_i;                 /* '<S59>/Derivative' */
  real_T TransferFcn1_n;               /* '<S56>/Transfer Fcn.1' */
  real_T Derivative1_e2;               /* '<S59>/Derivative1' */
  real_T Gain1_k;                      /* '<S59>/Gain1' */
  real_T Product_n;                    /* '<S59>/Product' */
  real_T Sum1_mt;                      /* '<S59>/Sum1' */
  real_T Gain2_h5;                     /* '<S59>/Gain2' */
  real_T Pilot_c;                      /* '<S7>/Pilot' */
  real_T Sum1_gi;                      /* '<S7>/Sum1' */
  real_T ActuatorModel_ib;             /* '<S7>/Actuator Model' */
  real_T Gain3_c;                      /* '<S56>/Gain3' */
  real_T Gain4_d;                      /* '<S56>/Gain4' */
  real_T Gain5_m;                      /* '<S56>/Gain5' */
  real_T Gain6_d;                      /* '<S56>/Gain6' */
  real_T Wgustmodel_d;                 /* '<S58>/W-gust model' */
  real_T Gain_j;                       /* '<S7>/Gain' */
  real_T Sum1_bq;                      /* '<S56>/Sum1' */
  real_T Gain2_m;                      /* '<S7>/Gain2' */
  real_T Qgustmodel_h;                 /* '<S58>/Q-gust model' */
  real_T Gain1_cj;                     /* '<S7>/Gain1' */
  real_T Sum_kc;                       /* '<S7>/Sum' */
  real_T Sum2_o5;                      /* '<S56>/Sum2' */
  real_T AlphasensorLowpassFilter_e0;  /* '<S57>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_ha;            /* '<S57>/Stick Prefilter' */
  real_T PitchRateLeadFilter_a;        /* '<S57>/Pitch Rate Lead Filter' */
  real_T Gain2_j0;                     /* '<S57>/Gain2' */
  real_T Gain3_ab;                     /* '<S57>/Gain3' */
  real_T Sum1_c;                       /* '<S57>/Sum1' */
  real_T Sum2_kr;                      /* '<S57>/Sum2' */
  real_T Gain_o3;                      /* '<S57>/Gain' */
  real_T Proportionalplusintegralcomp_ca;/* '<S57>/Proportional plus integral compensator' */
  real_T Sum_eg;                       /* '<S57>/Sum' */
  real_T WhiteNoise_m;                 /* '<S60>/White Noise' */
  real_T Output_i;                     /* '<S60>/Output' */
  real_T TransferFcn2_o;               /* '<S61>/Transfer Fcn.2' */
  real_T Gain5_hw;                     /* '<S8>/Gain5' */
  real_T Derivative_l;                 /* '<S64>/Derivative' */
  real_T TransferFcn1_m;               /* '<S61>/Transfer Fcn.1' */
  real_T Derivative1_c;                /* '<S64>/Derivative1' */
  real_T Gain1_as;                     /* '<S64>/Gain1' */
  real_T Product_f;                    /* '<S64>/Product' */
  real_T Sum1_mo;                      /* '<S64>/Sum1' */
  real_T Gain2_k;                      /* '<S64>/Gain2' */
  real_T Pilot_g;                      /* '<S8>/Pilot' */
  real_T Sum1_m2;                      /* '<S8>/Sum1' */
  real_T ActuatorModel_c;              /* '<S8>/Actuator Model' */
  real_T Gain3_e;                      /* '<S61>/Gain3' */
  real_T Gain4_l;                      /* '<S61>/Gain4' */
  real_T Gain5_d;                      /* '<S61>/Gain5' */
  real_T Gain6_b;                      /* '<S61>/Gain6' */
  real_T Wgustmodel_a;                 /* '<S63>/W-gust model' */
  real_T Gain_ob;                      /* '<S8>/Gain' */
  real_T Sum1_fz;                      /* '<S61>/Sum1' */
  real_T Gain2_jo;                     /* '<S8>/Gain2' */
  real_T Qgustmodel_i1;                /* '<S63>/Q-gust model' */
  real_T Gain1_p;                      /* '<S8>/Gain1' */
  real_T Sum_pj;                       /* '<S8>/Sum' */
  real_T Sum2_gl;                      /* '<S61>/Sum2' */
  real_T AlphasensorLowpassFilter_o;   /* '<S62>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_c;             /* '<S62>/Stick Prefilter' */
  real_T PitchRateLeadFilter_g;        /* '<S62>/Pitch Rate Lead Filter' */
  real_T Gain2_dk;                     /* '<S62>/Gain2' */
  real_T Gain3_kf;                     /* '<S62>/Gain3' */
  real_T Sum1_em;                      /* '<S62>/Sum1' */
  real_T Sum2_c3;                      /* '<S62>/Sum2' */
  real_T Gain_na;                      /* '<S62>/Gain' */
  real_T Proportionalplusintegralcompe_p;/* '<S62>/Proportional plus integral compensator' */
  real_T Sum_pi;                       /* '<S62>/Sum' */
  real_T WhiteNoise_k;                 /* '<S65>/White Noise' */
  real_T Output_n;                     /* '<S65>/Output' */
  real_T TransferFcn2_d1;              /* '<S66>/Transfer Fcn.2' */
  real_T Gain5_e;                      /* '<S9>/Gain5' */
  real_T Derivative_p;                 /* '<S69>/Derivative' */
  real_T TransferFcn1_b1;              /* '<S66>/Transfer Fcn.1' */
  real_T Derivative1_lu;               /* '<S69>/Derivative1' */
  real_T Gain1_e;                      /* '<S69>/Gain1' */
  real_T Product_p;                    /* '<S69>/Product' */
  real_T Sum1_ia;                      /* '<S69>/Sum1' */
  real_T Gain2_dv;                     /* '<S69>/Gain2' */
  real_T Pilot_kw;                     /* '<S9>/Pilot' */
  real_T Sum1_ij;                      /* '<S9>/Sum1' */
  real_T ActuatorModel_m;              /* '<S9>/Actuator Model' */
  real_T Gain3_o;                      /* '<S66>/Gain3' */
  real_T Gain4_g;                      /* '<S66>/Gain4' */
  real_T Gain5_l;                      /* '<S66>/Gain5' */
  real_T Gain6_n;                      /* '<S66>/Gain6' */
  real_T Wgustmodel_g;                 /* '<S68>/W-gust model' */
  real_T Gain_fj;                      /* '<S9>/Gain' */
  real_T Sum1_fo;                      /* '<S66>/Sum1' */
  real_T Gain2_lh;                     /* '<S9>/Gain2' */
  real_T Qgustmodel_mh;                /* '<S68>/Q-gust model' */
  real_T Gain1_kh;                     /* '<S9>/Gain1' */
  real_T Sum_c;                        /* '<S9>/Sum' */
  real_T Sum2_jr;                      /* '<S66>/Sum2' */
  real_T AlphasensorLowpassFilter_fj;  /* '<S67>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_l;             /* '<S67>/Stick Prefilter' */
  real_T PitchRateLeadFilter_em;       /* '<S67>/Pitch Rate Lead Filter' */
  real_T Gain2_ew;                     /* '<S67>/Gain2' */
  real_T Gain3_c3;                     /* '<S67>/Gain3' */
  real_T Sum1_gq;                      /* '<S67>/Sum1' */
  real_T Sum2_a;                       /* '<S67>/Sum2' */
  real_T Gain_c;                       /* '<S67>/Gain' */
  real_T Proportionalplusintegralcompe_l;/* '<S67>/Proportional plus integral compensator' */
  real_T Sum_a;                        /* '<S67>/Sum' */
  real_T WhiteNoise_f;                 /* '<S70>/White Noise' */
  real_T Output_gu;                    /* '<S70>/Output' */
  real_T TransferFcn2_n;               /* '<S71>/Transfer Fcn.2' */
  real_T Gain5_nv;                     /* '<S10>/Gain5' */
  real_T Derivative_m;                 /* '<S74>/Derivative' */
  real_T TransferFcn1_g;               /* '<S71>/Transfer Fcn.1' */
  real_T Derivative1_n;                /* '<S74>/Derivative1' */
  real_T Gain1_bc;                     /* '<S74>/Gain1' */
  real_T Product_i;                    /* '<S74>/Product' */
  real_T Sum1_is;                      /* '<S74>/Sum1' */
  real_T Gain2_n;                      /* '<S74>/Gain2' */
  real_T Pilot_mj;                     /* '<S10>/Pilot' */
  real_T Sum1_fov;                     /* '<S10>/Sum1' */
  real_T ActuatorModel_e;              /* '<S10>/Actuator Model' */
  real_T Gain3_oe;                     /* '<S71>/Gain3' */
  real_T Gain4_hg;                     /* '<S71>/Gain4' */
  real_T Gain5_k2;                     /* '<S71>/Gain5' */
  real_T Gain6_jf;                     /* '<S71>/Gain6' */
  real_T Wgustmodel_do;                /* '<S73>/W-gust model' */
  real_T Gain_cs;                      /* '<S10>/Gain' */
  real_T Sum1_dq;                      /* '<S71>/Sum1' */
  real_T Gain2_ow;                     /* '<S10>/Gain2' */
  real_T Qgustmodel_b;                 /* '<S73>/Q-gust model' */
  real_T Gain1_o;                      /* '<S10>/Gain1' */
  real_T Sum_o;                        /* '<S10>/Sum' */
  real_T Sum2_kw;                      /* '<S71>/Sum2' */
  real_T AlphasensorLowpassFilter_c;   /* '<S72>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_m;             /* '<S72>/Stick Prefilter' */
  real_T PitchRateLeadFilter_fd;       /* '<S72>/Pitch Rate Lead Filter' */
  real_T Gain2_b;                      /* '<S72>/Gain2' */
  real_T Gain3_j;                      /* '<S72>/Gain3' */
  real_T Sum1_gp;                      /* '<S72>/Sum1' */
  real_T Sum2_ee;                      /* '<S72>/Sum2' */
  real_T Gain_cm;                      /* '<S72>/Gain' */
  real_T Proportionalplusintegralcompe_b;/* '<S72>/Proportional plus integral compensator' */
  real_T Sum_bx;                       /* '<S72>/Sum' */
  real_T WhiteNoise_g1;                /* '<S75>/White Noise' */
  real_T Output_nn;                    /* '<S75>/Output' */
  real_T TransferFcn2_nh;              /* '<S76>/Transfer Fcn.2' */
  real_T Gain5_pn;                     /* '<S11>/Gain5' */
  real_T Derivative_n;                 /* '<S79>/Derivative' */
  real_T TransferFcn1_h;               /* '<S76>/Transfer Fcn.1' */
  real_T Derivative1_m;                /* '<S79>/Derivative1' */
  real_T Gain1_l;                      /* '<S79>/Gain1' */
  real_T Product_dp;                   /* '<S79>/Product' */
  real_T Sum1_h5;                      /* '<S79>/Sum1' */
  real_T Gain2_a;                      /* '<S79>/Gain2' */
  real_T Pilot_e;                      /* '<S11>/Pilot' */
  real_T Sum1_jt;                      /* '<S11>/Sum1' */
  real_T ActuatorModel_k;              /* '<S11>/Actuator Model' */
  real_T Gain3_d;                      /* '<S76>/Gain3' */
  real_T Gain4_g2;                     /* '<S76>/Gain4' */
  real_T Gain5_c;                      /* '<S76>/Gain5' */
  real_T Gain6_p;                      /* '<S76>/Gain6' */
  real_T Wgustmodel_nd;                /* '<S78>/W-gust model' */
  real_T Gain_k;                       /* '<S11>/Gain' */
  real_T Sum1_jj;                      /* '<S76>/Sum1' */
  real_T Gain2_ml;                     /* '<S11>/Gain2' */
  real_T Qgustmodel_l;                 /* '<S78>/Q-gust model' */
  real_T Gain1_ap;                     /* '<S11>/Gain1' */
  real_T Sum_i;                        /* '<S11>/Sum' */
  real_T Sum2_f1;                      /* '<S76>/Sum2' */
  real_T AlphasensorLowpassFilter_i;   /* '<S77>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_hq;            /* '<S77>/Stick Prefilter' */
  real_T PitchRateLeadFilter_d;        /* '<S77>/Pitch Rate Lead Filter' */
  real_T Gain2_p;                      /* '<S77>/Gain2' */
  real_T Gain3_n;                      /* '<S77>/Gain3' */
  real_T Sum1_a;                       /* '<S77>/Sum1' */
  real_T Sum2_mp;                      /* '<S77>/Sum2' */
  real_T Gain_f5;                      /* '<S77>/Gain' */
  real_T Proportionalplusintegralcompe_g;/* '<S77>/Proportional plus integral compensator' */
  real_T Sum_km;                       /* '<S77>/Sum' */
  real_T WhiteNoise_a;                 /* '<S80>/White Noise' */
  real_T Output_b;                     /* '<S80>/Output' */
  real_T TransferFcn2_f;               /* '<S81>/Transfer Fcn.2' */
  real_T Gain5_nb;                     /* '<S12>/Gain5' */
  real_T Derivative_a;                 /* '<S84>/Derivative' */
  real_T TransferFcn1_e;               /* '<S81>/Transfer Fcn.1' */
  real_T Derivative1_b;                /* '<S84>/Derivative1' */
  real_T Gain1_d;                      /* '<S84>/Gain1' */
  real_T Product_ik;                   /* '<S84>/Product' */
  real_T Sum1_dh;                      /* '<S84>/Sum1' */
  real_T Gain2_ny;                     /* '<S84>/Gain2' */
  real_T Pilot_f;                      /* '<S12>/Pilot' */
  real_T Sum1_oo;                      /* '<S12>/Sum1' */
  real_T ActuatorModel_o;              /* '<S12>/Actuator Model' */
  real_T Gain3_nz;                     /* '<S81>/Gain3' */
  real_T Gain4_fm;                     /* '<S81>/Gain4' */
  real_T Gain5_hb;                     /* '<S81>/Gain5' */
  real_T Gain6_i;                      /* '<S81>/Gain6' */
  real_T Wgustmodel_c5;                /* '<S83>/W-gust model' */
  real_T Gain_e4;                      /* '<S12>/Gain' */
  real_T Sum1_bk;                      /* '<S81>/Sum1' */
  real_T Gain2_pz;                     /* '<S12>/Gain2' */
  real_T Qgustmodel_j;                 /* '<S83>/Q-gust model' */
  real_T Gain1_du;                     /* '<S12>/Gain1' */
  real_T Sum_h4;                       /* '<S12>/Sum' */
  real_T Sum2_ol;                      /* '<S81>/Sum2' */
  real_T AlphasensorLowpassFilter_p;   /* '<S82>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_cq;            /* '<S82>/Stick Prefilter' */
  real_T PitchRateLeadFilter_c;        /* '<S82>/Pitch Rate Lead Filter' */
  real_T Gain2_ar;                     /* '<S82>/Gain2' */
  real_T Gain3_n3;                     /* '<S82>/Gain3' */
  real_T Sum1_ot;                      /* '<S82>/Sum1' */
  real_T Sum2_px;                      /* '<S82>/Sum2' */
  real_T Gain_p;                       /* '<S82>/Gain' */
  real_T Proportionalplusintegralcompe_h;/* '<S82>/Proportional plus integral compensator' */
  real_T Sum_my;                       /* '<S82>/Sum' */
  real_T WhiteNoise_dw;                /* '<S85>/White Noise' */
  real_T Output_l;                     /* '<S85>/Output' */
  real_T TransferFcn2_l;               /* '<S86>/Transfer Fcn.2' */
  real_T Gain5_py;                     /* '<S13>/Gain5' */
  real_T Derivative_lz;                /* '<S89>/Derivative' */
  real_T TransferFcn1_gi;              /* '<S86>/Transfer Fcn.1' */
  real_T Derivative1_j;                /* '<S89>/Derivative1' */
  real_T Gain1_g4;                     /* '<S89>/Gain1' */
  real_T Product_b;                    /* '<S89>/Product' */
  real_T Sum1_ev;                      /* '<S89>/Sum1' */
  real_T Gain2_g;                      /* '<S89>/Gain2' */
  real_T Pilot_h;                      /* '<S13>/Pilot' */
  real_T Sum1_n0;                      /* '<S13>/Sum1' */
  real_T ActuatorModel_a;              /* '<S13>/Actuator Model' */
  real_T Gain3_m;                      /* '<S86>/Gain3' */
  real_T Gain4_c;                      /* '<S86>/Gain4' */
  real_T Gain5_o;                      /* '<S86>/Gain5' */
  real_T Gain6_mc;                     /* '<S86>/Gain6' */
  real_T Wgustmodel_e;                 /* '<S88>/W-gust model' */
  real_T Gain_la;                      /* '<S13>/Gain' */
  real_T Sum1_dr;                      /* '<S86>/Sum1' */
  real_T Gain2_l0;                     /* '<S13>/Gain2' */
  real_T Qgustmodel_jp;                /* '<S88>/Q-gust model' */
  real_T Gain1_bt;                     /* '<S13>/Gain1' */
  real_T Sum_iw;                       /* '<S13>/Sum' */
  real_T Sum2_ola;                     /* '<S86>/Sum2' */
  real_T AlphasensorLowpassFilter_h;   /* '<S87>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_i;             /* '<S87>/Stick Prefilter' */
  real_T PitchRateLeadFilter_dg;       /* '<S87>/Pitch Rate Lead Filter' */
  real_T Gain2_ph;                     /* '<S87>/Gain2' */
  real_T Gain3_gl;                     /* '<S87>/Gain3' */
  real_T Sum1_o0;                      /* '<S87>/Sum1' */
  real_T Sum2_gk;                      /* '<S87>/Sum2' */
  real_T Gain_hu;                      /* '<S87>/Gain' */
  real_T Proportionalplusintegralcompe_e;/* '<S87>/Proportional plus integral compensator' */
  real_T Sum_ou;                       /* '<S87>/Sum' */
  real_T WhiteNoise_gw;                /* '<S90>/White Noise' */
  real_T Output_c;                     /* '<S90>/Output' */
  real_T TransferFcn2_ne;              /* '<S91>/Transfer Fcn.2' */
  real_T Gain5_kd;                     /* '<S14>/Gain5' */
  real_T Derivative_bl;                /* '<S94>/Derivative' */
  real_T TransferFcn1_i;               /* '<S91>/Transfer Fcn.1' */
  real_T Derivative1_f;                /* '<S94>/Derivative1' */
  real_T Gain1_m;                      /* '<S94>/Gain1' */
  real_T Product_l;                    /* '<S94>/Product' */
  real_T Sum1_cl;                      /* '<S94>/Sum1' */
  real_T Gain2_e5;                     /* '<S94>/Gain2' */
  real_T Pilot_bf;                     /* '<S14>/Pilot' */
  real_T Sum1_co;                      /* '<S14>/Sum1' */
  real_T ActuatorModel_o5;             /* '<S14>/Actuator Model' */
  real_T Gain3_j2;                     /* '<S91>/Gain3' */
  real_T Gain4_o;                      /* '<S91>/Gain4' */
  real_T Gain5_l2;                     /* '<S91>/Gain5' */
  real_T Gain6_e;                      /* '<S91>/Gain6' */
  real_T Wgustmodel_dn;                /* '<S93>/W-gust model' */
  real_T Gain_obj;                     /* '<S14>/Gain' */
  real_T Sum1_gl;                      /* '<S91>/Sum1' */
  real_T Gain2_l4;                     /* '<S14>/Gain2' */
  real_T Qgustmodel_k;                 /* '<S93>/Q-gust model' */
  real_T Gain1_bx;                     /* '<S14>/Gain1' */
  real_T Sum_b0;                       /* '<S14>/Sum' */
  real_T Sum2_mr;                      /* '<S91>/Sum2' */
  real_T AlphasensorLowpassFilter_o1;  /* '<S92>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_k;             /* '<S92>/Stick Prefilter' */
  real_T PitchRateLeadFilter_j;        /* '<S92>/Pitch Rate Lead Filter' */
  real_T Gain2_aa;                     /* '<S92>/Gain2' */
  real_T Gain3_js;                     /* '<S92>/Gain3' */
  real_T Sum1_os;                      /* '<S92>/Sum1' */
  real_T Sum2_mn;                      /* '<S92>/Sum2' */
  real_T Gain_c0;                      /* '<S92>/Gain' */
  real_T Proportionalplusintegralcomp_ii;/* '<S92>/Proportional plus integral compensator' */
  real_T Sum_af;                       /* '<S92>/Sum' */
  real_T WhiteNoise_h;                 /* '<S95>/White Noise' */
  real_T Output_k;                     /* '<S95>/Output' */
  real_T TransferFcn2_a;               /* '<S96>/Transfer Fcn.2' */
  real_T Gain5_kv;                     /* '<S15>/Gain5' */
  real_T Derivative_im;                /* '<S99>/Derivative' */
  real_T TransferFcn1_e3;              /* '<S96>/Transfer Fcn.1' */
  real_T Derivative1_ph;               /* '<S99>/Derivative1' */
  real_T Gain1_on;                     /* '<S99>/Gain1' */
  real_T Product_dp5;                  /* '<S99>/Product' */
  real_T Sum1_h0;                      /* '<S99>/Sum1' */
  real_T Gain2_gc;                     /* '<S99>/Gain2' */
  real_T Pilot_fw;                     /* '<S15>/Pilot' */
  real_T Sum1_lr;                      /* '<S15>/Sum1' */
  real_T ActuatorModel_j1;             /* '<S15>/Actuator Model' */
  real_T Gain3_jn;                     /* '<S96>/Gain3' */
  real_T Gain4_or;                     /* '<S96>/Gain4' */
  real_T Gain5_i;                      /* '<S96>/Gain5' */
  real_T Gain6_dl;                     /* '<S96>/Gain6' */
  real_T Wgustmodel_gx;                /* '<S98>/W-gust model' */
  real_T Gain_gh;                      /* '<S15>/Gain' */
  real_T Sum1_iav;                     /* '<S96>/Sum1' */
  real_T Gain2_b4;                     /* '<S15>/Gain2' */
  real_T Qgustmodel_kd;                /* '<S98>/Q-gust model' */
  real_T Gain1_mh;                     /* '<S15>/Gain1' */
  real_T Sum_lg;                       /* '<S15>/Sum' */
  real_T Sum2_bu;                      /* '<S96>/Sum2' */
  real_T AlphasensorLowpassFilter_kd;  /* '<S97>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_dp;            /* '<S97>/Stick Prefilter' */
  real_T PitchRateLeadFilter_an;       /* '<S97>/Pitch Rate Lead Filter' */
  real_T Gain2_aw;                     /* '<S97>/Gain2' */
  real_T Gain3_b5;                     /* '<S97>/Gain3' */
  real_T Sum1_hf;                      /* '<S97>/Sum1' */
  real_T Sum2_eu;                      /* '<S97>/Sum2' */
  real_T Gain_cg;                      /* '<S97>/Gain' */
  real_T Proportionalplusintegralcom_iia;/* '<S97>/Proportional plus integral compensator' */
  real_T Sum_kq;                       /* '<S97>/Sum' */
  real_T WhiteNoise_ag;                /* '<S100>/White Noise' */
  real_T Output_gq;                    /* '<S100>/Output' */
  real_T TransferFcn2_j;               /* '<S101>/Transfer Fcn.2' */
  real_T Gain5_nz;                     /* '<S16>/Gain5' */
  real_T Derivative_g;                 /* '<S104>/Derivative' */
  real_T TransferFcn1_n3;              /* '<S101>/Transfer Fcn.1' */
  real_T Derivative1_l2;               /* '<S104>/Derivative1' */
  real_T Gain1_n;                      /* '<S104>/Gain1' */
  real_T Product_e;                    /* '<S104>/Product' */
  real_T Sum1_b2;                      /* '<S104>/Sum1' */
  real_T Gain2_mw;                     /* '<S104>/Gain2' */
  real_T Pilot_p;                      /* '<S16>/Pilot' */
  real_T Sum1_ds;                      /* '<S16>/Sum1' */
  real_T ActuatorModel_g;              /* '<S16>/Actuator Model' */
  real_T Gain3_e3;                     /* '<S101>/Gain3' */
  real_T Gain4_d4;                     /* '<S101>/Gain4' */
  real_T Gain5_nu;                     /* '<S101>/Gain5' */
  real_T Gain6_ba;                     /* '<S101>/Gain6' */
  real_T Wgustmodel_i;                 /* '<S103>/W-gust model' */
  real_T Gain_ii;                      /* '<S16>/Gain' */
  real_T Sum1_bx5;                     /* '<S101>/Sum1' */
  real_T Gain2_mc;                     /* '<S16>/Gain2' */
  real_T Qgustmodel_d;                 /* '<S103>/Q-gust model' */
  real_T Gain1_n3;                     /* '<S16>/Gain1' */
  real_T Sum_ns;                       /* '<S16>/Sum' */
  real_T Sum2_ei;                      /* '<S101>/Sum2' */
  real_T AlphasensorLowpassFilter_b;   /* '<S102>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_ms;            /* '<S102>/Stick Prefilter' */
  real_T PitchRateLeadFilter_af;       /* '<S102>/Pitch Rate Lead Filter' */
  real_T Gain2_hf;                     /* '<S102>/Gain2' */
  real_T Gain3_bi;                     /* '<S102>/Gain3' */
  real_T Sum1_en;                      /* '<S102>/Sum1' */
  real_T Sum2_il;                      /* '<S102>/Sum2' */
  real_T Gain_b;                       /* '<S102>/Gain' */
  real_T Proportionalplusintegralcompe_d;/* '<S102>/Proportional plus integral compensator' */
  real_T Sum_bd;                       /* '<S102>/Sum' */
  real_T WhiteNoise_ml;                /* '<S105>/White Noise' */
  real_T Output_d;                     /* '<S105>/Output' */
  real_T TransferFcn2_br;              /* '<S106>/Transfer Fcn.2' */
  real_T Gain5_a;                      /* '<S17>/Gain5' */
  real_T Derivative_f;                 /* '<S109>/Derivative' */
  real_T TransferFcn1_ep;              /* '<S106>/Transfer Fcn.1' */
  real_T Derivative1_pf;               /* '<S109>/Derivative1' */
  real_T Gain1_ga;                     /* '<S109>/Gain1' */
  real_T Product_j;                    /* '<S109>/Product' */
  real_T Sum1_pu;                      /* '<S109>/Sum1' */
  real_T Gain2_io;                     /* '<S109>/Gain2' */
  real_T Pilot_pz;                     /* '<S17>/Pilot' */
  real_T Sum1_cx;                      /* '<S17>/Sum1' */
  real_T ActuatorModel_l;              /* '<S17>/Actuator Model' */
  real_T Gain3_nv;                     /* '<S106>/Gain3' */
  real_T Gain4_kp;                     /* '<S106>/Gain4' */
  real_T Gain5_eq;                     /* '<S106>/Gain5' */
  real_T Gain6_f;                      /* '<S106>/Gain6' */
  real_T Wgustmodel_o;                 /* '<S108>/W-gust model' */
  real_T Gain_m;                       /* '<S17>/Gain' */
  real_T Sum1_kk;                      /* '<S106>/Sum1' */
  real_T Gain2_kq;                     /* '<S17>/Gain2' */
  real_T Qgustmodel_hf;                /* '<S108>/Q-gust model' */
  real_T Gain1_ki;                     /* '<S17>/Gain1' */
  real_T Sum_f;                        /* '<S17>/Sum' */
  real_T Sum2_ky;                      /* '<S106>/Sum2' */
  real_T AlphasensorLowpassFilter_ob;  /* '<S107>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_kv;            /* '<S107>/Stick Prefilter' */
  real_T PitchRateLeadFilter_fw;       /* '<S107>/Pitch Rate Lead Filter' */
  real_T Gain2_lr;                     /* '<S107>/Gain2' */
  real_T Gain3_j0;                     /* '<S107>/Gain3' */
  real_T Sum1_ft;                      /* '<S107>/Sum1' */
  real_T Sum2_e1;                      /* '<S107>/Sum2' */
  real_T Gain_mg;                      /* '<S107>/Gain' */
  real_T Proportionalplusintegralcompe_k;/* '<S107>/Proportional plus integral compensator' */
  real_T Sum_ab;                       /* '<S107>/Sum' */
  real_T WhiteNoise_cv;                /* '<S110>/White Noise' */
  real_T Output_b0;                    /* '<S110>/Output' */
  real_T TransferFcn2_m;               /* '<S111>/Transfer Fcn.2' */
  real_T Gain5_l5;                     /* '<S18>/Gain5' */
  real_T Derivative_mv;                /* '<S114>/Derivative' */
  real_T TransferFcn1_j;               /* '<S111>/Transfer Fcn.1' */
  real_T Derivative1_pz;               /* '<S114>/Derivative1' */
  real_T Gain1_ih;                     /* '<S114>/Gain1' */
  real_T Product_ev;                   /* '<S114>/Product' */
  real_T Sum1_fi;                      /* '<S114>/Sum1' */
  real_T Gain2_ix;                     /* '<S114>/Gain2' */
  real_T Pilot_pg;                     /* '<S18>/Pilot' */
  real_T Sum1_i1;                      /* '<S18>/Sum1' */
  real_T ActuatorModel_p;              /* '<S18>/Actuator Model' */
  real_T Gain3_lz;                     /* '<S111>/Gain3' */
  real_T Gain4_i;                      /* '<S111>/Gain4' */
  real_T Gain5_bb;                     /* '<S111>/Gain5' */
  real_T Gain6_c;                      /* '<S111>/Gain6' */
  real_T Wgustmodel_a1;                /* '<S113>/W-gust model' */
  real_T Gain_a;                       /* '<S18>/Gain' */
  real_T Sum1_hu;                      /* '<S111>/Sum1' */
  real_T Gain2_ki;                     /* '<S18>/Gain2' */
  real_T Qgustmodel_kt;                /* '<S113>/Q-gust model' */
  real_T Gain1_kl;                     /* '<S18>/Gain1' */
  real_T Sum_pa;                       /* '<S18>/Sum' */
  real_T Sum2_oq;                      /* '<S111>/Sum2' */
  real_T AlphasensorLowpassFilter_og;  /* '<S112>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_ky;            /* '<S112>/Stick Prefilter' */
  real_T PitchRateLeadFilter_g0;       /* '<S112>/Pitch Rate Lead Filter' */
  real_T Gain2_k2;                     /* '<S112>/Gain2' */
  real_T Gain3_no;                     /* '<S112>/Gain3' */
  real_T Sum1_iao;                     /* '<S112>/Sum1' */
  real_T Sum2_n;                       /* '<S112>/Sum2' */
  real_T Gain_lag;                     /* '<S112>/Gain' */
  real_T Proportionalplusintegralcomp_ce;/* '<S112>/Proportional plus integral compensator' */
  real_T Sum_em;                       /* '<S112>/Sum' */
  real_T WhiteNoise_ae;                /* '<S115>/White Noise' */
  real_T Output_dm;                    /* '<S115>/Output' */
  real_T TransferFcn2_ja;              /* '<S116>/Transfer Fcn.2' */
  real_T Gain5_k5;                     /* '<S19>/Gain5' */
  real_T Derivative_pw;                /* '<S119>/Derivative' */
  real_T TransferFcn1_k;               /* '<S116>/Transfer Fcn.1' */
  real_T Derivative1_g;                /* '<S119>/Derivative1' */
  real_T Gain1_gao;                    /* '<S119>/Gain1' */
  real_T Product_hh;                   /* '<S119>/Product' */
  real_T Sum1_o0i;                     /* '<S119>/Sum1' */
  real_T Gain2_h0;                     /* '<S119>/Gain2' */
  real_T Pilot_gs;                     /* '<S19>/Pilot' */
  real_T Sum1_dd;                      /* '<S19>/Sum1' */
  real_T ActuatorModel_ms;             /* '<S19>/Actuator Model' */
  real_T Gain3_lc;                     /* '<S116>/Gain3' */
  real_T Gain4_j;                      /* '<S116>/Gain4' */
  real_T Gain5_pj;                     /* '<S116>/Gain5' */
  real_T Gain6_fi;                     /* '<S116>/Gain6' */
  real_T Wgustmodel_h;                 /* '<S118>/W-gust model' */
  real_T Gain_od;                      /* '<S19>/Gain' */
  real_T Sum1_fl;                      /* '<S116>/Sum1' */
  real_T Gain2_nm;                     /* '<S19>/Gain2' */
  real_T Qgustmodel_g;                 /* '<S118>/Q-gust model' */
  real_T Gain1_om;                     /* '<S19>/Gain1' */
  real_T Sum_en;                       /* '<S19>/Sum' */
  real_T Sum2_cx;                      /* '<S116>/Sum2' */
  real_T AlphasensorLowpassFilter_jg;  /* '<S117>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_e;             /* '<S117>/Stick Prefilter' */
  real_T PitchRateLeadFilter_ke;       /* '<S117>/Pitch Rate Lead Filter' */
  real_T Gain2_nh;                     /* '<S117>/Gain2' */
  real_T Gain3_bj;                     /* '<S117>/Gain3' */
  real_T Sum1_om;                      /* '<S117>/Sum1' */
  real_T Sum2_gm;                      /* '<S117>/Sum2' */
  real_T Gain_df;                      /* '<S117>/Gain' */
  real_T Proportionalplusintegralcomp_hc;/* '<S117>/Proportional plus integral compensator' */
  real_T Sum_kb;                       /* '<S117>/Sum' */
  real_T WhiteNoise_p;                 /* '<S120>/White Noise' */
  real_T Output_k4;                    /* '<S120>/Output' */
  real_T TransferFcn2_oz;              /* '<S121>/Transfer Fcn.2' */
  real_T Gain5_cq;                     /* '<S20>/Gain5' */
  real_T Derivative_fo;                /* '<S124>/Derivative' */
  real_T TransferFcn1_iw;              /* '<S121>/Transfer Fcn.1' */
  real_T Derivative1_i;                /* '<S124>/Derivative1' */
  real_T Gain1_omh;                    /* '<S124>/Gain1' */
  real_T Product_ij;                   /* '<S124>/Product' */
  real_T Sum1_aj;                      /* '<S124>/Sum1' */
  real_T Gain2_oj;                     /* '<S124>/Gain2' */
  real_T Pilot_h3;                     /* '<S20>/Pilot' */
  real_T Sum1_hc1;                     /* '<S20>/Sum1' */
  real_T ActuatorModel_b;              /* '<S20>/Actuator Model' */
  real_T Gain3_as;                     /* '<S121>/Gain3' */
  real_T Gain4_ld;                     /* '<S121>/Gain4' */
  real_T Gain5_iu;                     /* '<S121>/Gain5' */
  real_T Gain6_b5;                     /* '<S121>/Gain6' */
  real_T Wgustmodel_ox;                /* '<S123>/W-gust model' */
  real_T Gain_hr;                      /* '<S20>/Gain' */
  real_T Sum1_gg;                      /* '<S121>/Sum1' */
  real_T Gain2_bh;                     /* '<S20>/Gain2' */
  real_T Qgustmodel_n;                 /* '<S123>/Q-gust model' */
  real_T Gain1_lq;                     /* '<S20>/Gain1' */
  real_T Sum_kh;                       /* '<S20>/Sum' */
  real_T Sum2_oa;                      /* '<S121>/Sum2' */
  real_T AlphasensorLowpassFilter_n;   /* '<S122>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_o;             /* '<S122>/Stick Prefilter' */
  real_T PitchRateLeadFilter_f1;       /* '<S122>/Pitch Rate Lead Filter' */
  real_T Gain2_fs;                     /* '<S122>/Gain2' */
  real_T Gain3_f;                      /* '<S122>/Gain3' */
  real_T Sum1_mx;                      /* '<S122>/Sum1' */
  real_T Sum2_f5;                      /* '<S122>/Sum2' */
  real_T Gain_i2;                      /* '<S122>/Gain' */
  real_T Proportionalplusintegralcomp_eg;/* '<S122>/Proportional plus integral compensator' */
  real_T Sum_mb;                       /* '<S122>/Sum' */
  real_T WhiteNoise_ms;                /* '<S125>/White Noise' */
  real_T Output_al;                    /* '<S125>/Output' */
  real_T TransferFcn2_jp;              /* '<S126>/Transfer Fcn.2' */
  real_T Gain5_o4;                     /* '<S21>/Gain5' */
  real_T Derivative_gv;                /* '<S129>/Derivative' */
  real_T TransferFcn1_f;               /* '<S126>/Transfer Fcn.1' */
  real_T Derivative1_oy;               /* '<S129>/Derivative1' */
  real_T Gain1_ho;                     /* '<S129>/Gain1' */
  real_T Product_o;                    /* '<S129>/Product' */
  real_T Sum1_ap;                      /* '<S129>/Sum1' */
  real_T Gain2_di;                     /* '<S129>/Gain2' */
  real_T Pilot_j;                      /* '<S21>/Pilot' */
  real_T Sum1_fih;                     /* '<S21>/Sum1' */
  real_T ActuatorModel_b4;             /* '<S21>/Actuator Model' */
  real_T Gain3_c0;                     /* '<S126>/Gain3' */
  real_T Gain4_dh;                     /* '<S126>/Gain4' */
  real_T Gain5_f;                      /* '<S126>/Gain5' */
  real_T Gain6_j2;                     /* '<S126>/Gain6' */
  real_T Wgustmodel_o4;                /* '<S128>/W-gust model' */
  real_T Gain_i2f;                     /* '<S21>/Gain' */
  real_T Sum1_o3;                      /* '<S126>/Sum1' */
  real_T Gain2_da;                     /* '<S21>/Gain2' */
  real_T Qgustmodel_h0;                /* '<S128>/Q-gust model' */
  real_T Gain1_br;                     /* '<S21>/Gain1' */
  real_T Sum_i2;                       /* '<S21>/Sum' */
  real_T Sum2_pt;                      /* '<S126>/Sum2' */
  real_T AlphasensorLowpassFilter_bd;  /* '<S127>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_ew;            /* '<S127>/Stick Prefilter' */
  real_T PitchRateLeadFilter_h;        /* '<S127>/Pitch Rate Lead Filter' */
  real_T Gain2_fo;                     /* '<S127>/Gain2' */
  real_T Gain3_n1;                     /* '<S127>/Gain3' */
  real_T Sum1_my;                      /* '<S127>/Sum1' */
  real_T Sum2_oh;                      /* '<S127>/Sum2' */
  real_T Gain_ky;                      /* '<S127>/Gain' */
  real_T Proportionalplusintegralcompe_a;/* '<S127>/Proportional plus integral compensator' */
  real_T Sum_cd;                       /* '<S127>/Sum' */
  real_T WhiteNoise_mt;                /* '<S130>/White Noise' */
  real_T Output_bc;                    /* '<S130>/Output' */
  real_T TransferFcn2_fa;              /* '<S131>/Transfer Fcn.2' */
  real_T Gain5_et;                     /* '<S22>/Gain5' */
  real_T Derivative_ps;                /* '<S134>/Derivative' */
  real_T TransferFcn1_nf;              /* '<S131>/Transfer Fcn.1' */
  real_T Derivative1_pm;               /* '<S134>/Derivative1' */
  real_T Gain1_e4;                     /* '<S134>/Gain1' */
  real_T Product_ap;                   /* '<S134>/Product' */
  real_T Sum1_nb;                      /* '<S134>/Sum1' */
  real_T Gain2_ne;                     /* '<S134>/Gain2' */
  real_T Pilot_c3;                     /* '<S22>/Pilot' */
  real_T Sum1_ec;                      /* '<S22>/Sum1' */
  real_T ActuatorModel_n2;             /* '<S22>/Actuator Model' */
  real_T Gain3_c0d;                    /* '<S131>/Gain3' */
  real_T Gain4_a;                      /* '<S131>/Gain4' */
  real_T Gain5_ej;                     /* '<S131>/Gain5' */
  real_T Gain6_cv;                     /* '<S131>/Gain6' */
  real_T Wgustmodel_fj;                /* '<S133>/W-gust model' */
  real_T Gain_i1;                      /* '<S22>/Gain' */
  real_T Sum1_n02;                     /* '<S131>/Sum1' */
  real_T Gain2_fa;                     /* '<S22>/Gain2' */
  real_T Qgustmodel_ih;                /* '<S133>/Q-gust model' */
  real_T Gain1_b3;                     /* '<S22>/Gain1' */
  real_T Sum_lm;                       /* '<S22>/Sum' */
  real_T Sum2_bul;                     /* '<S131>/Sum2' */
  real_T AlphasensorLowpassFilter_pq;  /* '<S132>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_p;             /* '<S132>/Stick Prefilter' */
  real_T PitchRateLeadFilter_aj;       /* '<S132>/Pitch Rate Lead Filter' */
  real_T Gain2_m0;                     /* '<S132>/Gain2' */
  real_T Gain3_m2;                     /* '<S132>/Gain3' */
  real_T Sum1_ad;                      /* '<S132>/Sum1' */
  real_T Sum2_d;                       /* '<S132>/Sum2' */
  real_T Gain_i21;                     /* '<S132>/Gain' */
  real_T Proportionalplusintegralcomp_le;/* '<S132>/Proportional plus integral compensator' */
  real_T Sum_cy;                       /* '<S132>/Sum' */
  real_T WhiteNoise_lu;                /* '<S135>/White Noise' */
  real_T Output_hu;                    /* '<S135>/Output' */
  real_T TransferFcn2_jt;              /* '<S136>/Transfer Fcn.2' */
  real_T Gain5_mu;                     /* '<S23>/Gain5' */
  real_T Derivative_e;                 /* '<S139>/Derivative' */
  real_T TransferFcn1_d;               /* '<S136>/Transfer Fcn.1' */
  real_T Derivative1_n2;               /* '<S139>/Derivative1' */
  real_T Gain1_m4;                     /* '<S139>/Gain1' */
  real_T Product_b2;                   /* '<S139>/Product' */
  real_T Sum1_myl;                     /* '<S139>/Sum1' */
  real_T Gain2_br;                     /* '<S139>/Gain2' */
  real_T Pilot_n;                      /* '<S23>/Pilot' */
  real_T Sum1_ni;                      /* '<S23>/Sum1' */
  real_T ActuatorModel_n3;             /* '<S23>/Actuator Model' */
  real_T Gain3_bt;                     /* '<S136>/Gain3' */
  real_T Gain4_kk;                     /* '<S136>/Gain4' */
  real_T Gain5_nl;                     /* '<S136>/Gain5' */
  real_T Gain6_ax;                     /* '<S136>/Gain6' */
  real_T Wgustmodel_hc;                /* '<S138>/W-gust model' */
  real_T Gain_kd;                      /* '<S23>/Gain' */
  real_T Sum1_m5;                      /* '<S136>/Sum1' */
  real_T Gain2_fh;                     /* '<S23>/Gain2' */
  real_T Qgustmodel_ao;                /* '<S138>/Q-gust model' */
  real_T Gain1_j2;                     /* '<S23>/Gain1' */
  real_T Sum_le;                       /* '<S23>/Sum' */
  real_T Sum2_m4;                      /* '<S136>/Sum2' */
  real_T AlphasensorLowpassFilter_na;  /* '<S137>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_mu;            /* '<S137>/Stick Prefilter' */
  real_T PitchRateLeadFilter_it;       /* '<S137>/Pitch Rate Lead Filter' */
  real_T Gain2_ju;                     /* '<S137>/Gain2' */
  real_T Gain3_gr;                     /* '<S137>/Gain3' */
  real_T Sum1_aa;                      /* '<S137>/Sum1' */
  real_T Sum2_h;                       /* '<S137>/Sum2' */
  real_T Gain_dr;                      /* '<S137>/Gain' */
  real_T Proportionalplusintegralcomp_aj;/* '<S137>/Proportional plus integral compensator' */
  real_T Sum_nsk;                      /* '<S137>/Sum' */
  real_T WhiteNoise_l4;                /* '<S140>/White Noise' */
  real_T Output_p;                     /* '<S140>/Output' */
  real_T TransferFcn2_mc;              /* '<S141>/Transfer Fcn.2' */
  real_T Gain5_m5;                     /* '<S24>/Gain5' */
  real_T Derivative_by;                /* '<S144>/Derivative' */
  real_T TransferFcn1_l;               /* '<S141>/Transfer Fcn.1' */
  real_T Derivative1_cp;               /* '<S144>/Derivative1' */
  real_T Gain1_ld;                     /* '<S144>/Gain1' */
  real_T Product_a0;                   /* '<S144>/Product' */
  real_T Sum1_jv;                      /* '<S144>/Sum1' */
  real_T Gain2_ig;                     /* '<S144>/Gain2' */
  real_T Pilot_ff;                     /* '<S24>/Pilot' */
  real_T Sum1_jty;                     /* '<S24>/Sum1' */
  real_T ActuatorModel_da;             /* '<S24>/Actuator Model' */
  real_T Gain3_nn;                     /* '<S141>/Gain3' */
  real_T Gain4_jo;                     /* '<S141>/Gain4' */
  real_T Gain5_ky;                     /* '<S141>/Gain5' */
  real_T Gain6_ii;                     /* '<S141>/Gain6' */
  real_T Wgustmodel_il;                /* '<S143>/W-gust model' */
  real_T Gain_l3;                      /* '<S24>/Gain' */
  real_T Sum1_flb;                     /* '<S141>/Sum1' */
  real_T Gain2_jn;                     /* '<S24>/Gain2' */
  real_T Qgustmodel_lq;                /* '<S143>/Q-gust model' */
  real_T Gain1_g4a;                    /* '<S24>/Gain1' */
  real_T Sum_ah;                       /* '<S24>/Sum' */
  real_T Sum2_p1;                      /* '<S141>/Sum2' */
  real_T AlphasensorLowpassFilter_d;   /* '<S142>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_ok;            /* '<S142>/Stick Prefilter' */
  real_T PitchRateLeadFilter_o;        /* '<S142>/Pitch Rate Lead Filter' */
  real_T Gain2_elw;                    /* '<S142>/Gain2' */
  real_T Gain3_ae;                     /* '<S142>/Gain3' */
  real_T Sum1_lg;                      /* '<S142>/Sum1' */
  real_T Sum2_fw;                      /* '<S142>/Sum2' */
  real_T Gain_nq;                      /* '<S142>/Gain' */
  real_T Proportionalplusintegralcomp_ap;/* '<S142>/Proportional plus integral compensator' */
  real_T Sum_lq;                       /* '<S142>/Sum' */
  real_T WhiteNoise_lx;                /* '<S145>/White Noise' */
  real_T Output_o4;                    /* '<S145>/Output' */
  real_T TransferFcn2_k;               /* '<S146>/Transfer Fcn.2' */
  real_T Gain5_cl;                     /* '<S25>/Gain5' */
  real_T Derivative_c;                 /* '<S149>/Derivative' */
  real_T TransferFcn1_jd;              /* '<S146>/Transfer Fcn.1' */
  real_T Derivative1_lq;               /* '<S149>/Derivative1' */
  real_T Gain1_bh;                     /* '<S149>/Gain1' */
  real_T Product_fg;                   /* '<S149>/Product' */
  real_T Sum1_a3;                      /* '<S149>/Sum1' */
  real_T Gain2_c;                      /* '<S149>/Gain2' */
  real_T Pilot_ci;                     /* '<S25>/Pilot' */
  real_T Sum1_oz;                      /* '<S25>/Sum1' */
  real_T ActuatorModel_h;              /* '<S25>/Actuator Model' */
  real_T Gain3_g4;                     /* '<S146>/Gain3' */
  real_T Gain4_lt;                     /* '<S146>/Gain4' */
  real_T Gain5_jr;                     /* '<S146>/Gain5' */
  real_T Gain6_pl;                     /* '<S146>/Gain6' */
  real_T Wgustmodel_k;                 /* '<S148>/W-gust model' */
  real_T Gain_ih;                      /* '<S25>/Gain' */
  real_T Sum1_pn;                      /* '<S146>/Sum1' */
  real_T Gain2_ah;                     /* '<S25>/Gain2' */
  real_T Qgustmodel_gx;                /* '<S148>/Q-gust model' */
  real_T Gain1_hc;                     /* '<S25>/Gain1' */
  real_T Sum_ob;                       /* '<S25>/Sum' */
  real_T Sum2_hz;                      /* '<S146>/Sum2' */
  real_T AlphasensorLowpassFilter_kr;  /* '<S147>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_pi;            /* '<S147>/Stick Prefilter' */
  real_T PitchRateLeadFilter_ik;       /* '<S147>/Pitch Rate Lead Filter' */
  real_T Gain2_id;                     /* '<S147>/Gain2' */
  real_T Gain3_oq;                     /* '<S147>/Gain3' */
  real_T Sum1_dg;                      /* '<S147>/Sum1' */
  real_T Sum2_jy;                      /* '<S147>/Sum2' */
  real_T Gain_er;                      /* '<S147>/Gain' */
  real_T Proportionalplusintegralcomp_gn;/* '<S147>/Proportional plus integral compensator' */
  real_T Sum_j;                        /* '<S147>/Sum' */
  real_T WhiteNoise_fe;                /* '<S150>/White Noise' */
  real_T Output_dn;                    /* '<S150>/Output' */
} BlockIO_f14tmp25;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T NextOutput;                   /* '<S30>/White Noise' */
  real_T NextOutput_f;                 /* '<S35>/White Noise' */
  real_T NextOutput_n;                 /* '<S40>/White Noise' */
  real_T NextOutput_g;                 /* '<S45>/White Noise' */
  real_T NextOutput_h;                 /* '<S50>/White Noise' */
  real_T NextOutput_c;                 /* '<S55>/White Noise' */
  real_T NextOutput_j;                 /* '<S60>/White Noise' */
  real_T NextOutput_d;                 /* '<S65>/White Noise' */
  real_T NextOutput_l;                 /* '<S70>/White Noise' */
  real_T NextOutput_a;                 /* '<S75>/White Noise' */
  real_T NextOutput_ag;                /* '<S80>/White Noise' */
  real_T NextOutput_m;                 /* '<S85>/White Noise' */
  real_T NextOutput_hq;                /* '<S90>/White Noise' */
  real_T NextOutput_nm;                /* '<S95>/White Noise' */
  real_T NextOutput_i;                 /* '<S100>/White Noise' */
  real_T NextOutput_o;                 /* '<S105>/White Noise' */
  real_T NextOutput_h5;                /* '<S110>/White Noise' */
  real_T NextOutput_ai;                /* '<S115>/White Noise' */
  real_T NextOutput_am;                /* '<S120>/White Noise' */
  real_T NextOutput_e;                 /* '<S125>/White Noise' */
  real_T NextOutput_k;                 /* '<S130>/White Noise' */
  real_T NextOutput_ct;                /* '<S135>/White Noise' */
  real_T NextOutput_d2;                /* '<S140>/White Noise' */
  real_T NextOutput_g3;                /* '<S145>/White Noise' */
  real_T NextOutput_ip;                /* '<S150>/White Noise' */
  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK;                  /* '<S29>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative1_RWORK;                 /* '<S29>/Derivative1' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_f;                /* '<S34>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative1_RWORK_o;               /* '<S34>/Derivative1' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_p;                /* '<S39>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative1_RWORK_c;               /* '<S39>/Derivative1' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_c;                /* '<S44>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative1_RWORK_d;               /* '<S44>/Derivative1' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_j;                /* '<S49>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative1_RWORK_e;               /* '<S49>/Derivative1' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_h;                /* '<S54>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative1_RWORK_p;               /* '<S54>/Derivative1' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_hr;               /* '<S59>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative1_RWORK_cz;              /* '<S59>/Derivative1' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_b;                /* '<S64>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative1_RWORK_cb;              /* '<S64>/Derivative1' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_jk;               /* '<S69>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative1_RWORK_ev;              /* '<S69>/Derivative1' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_bz;               /* '<S74>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative1_RWORK_cd;              /* '<S74>/Derivative1' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_a;                /* '<S79>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative1_RWORK_i;               /* '<S79>/Derivative1' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_l;                /* '<S84>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative1_RWORK_eb;              /* '<S84>/Derivative1' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_lu;               /* '<S89>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative1_RWORK_k;               /* '<S89>/Derivative1' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_n;                /* '<S94>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative1_RWORK_m;               /* '<S94>/Derivative1' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_d;                /* '<S99>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative1_RWORK_b;               /* '<S99>/Derivative1' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_fd;               /* '<S104>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative1_RWORK_bx;              /* '<S104>/Derivative1' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_nx;               /* '<S109>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative1_RWORK_kl;              /* '<S109>/Derivative1' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_bp;               /* '<S114>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative1_RWORK_mv;              /* '<S114>/Derivative1' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_k;                /* '<S119>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative1_RWORK_bm;              /* '<S119>/Derivative1' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_lc;               /* '<S124>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative1_RWORK_dt;              /* '<S124>/Derivative1' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_jt;               /* '<S129>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative1_RWORK_pp;              /* '<S129>/Derivative1' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_o;                /* '<S134>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative1_RWORK_eu;              /* '<S134>/Derivative1' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_o0;               /* '<S139>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative1_RWORK_j;               /* '<S139>/Derivative1' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_p5;               /* '<S144>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative1_RWORK_dy;              /* '<S144>/Derivative1' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative_RWORK_ch;               /* '<S149>/Derivative' */

  struct {
    real_T TimeStampA;
    real_T LastUAtTimeA;
    real_T TimeStampB;
    real_T LastUAtTimeB;
  } Derivative1_RWORK_n;               /* '<S149>/Derivative1' */

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
  } AngleofAttack_PWORK_o;             /* '<S3>/Angle of  Attack' */

  struct {
    void *LoggedData;
  } PilotGforceScope_PWORK_i;          /* '<S3>/Pilot G force Scope' */

  struct {
    void *LoggedData;
  } StickInput_PWORK_d;                /* '<S3>/Stick Input' */

  struct {
    void *LoggedData;
  } AngleofAttack_PWORK_d;             /* '<S4>/Angle of  Attack' */

  struct {
    void *LoggedData;
  } PilotGforceScope_PWORK_f;          /* '<S4>/Pilot G force Scope' */

  struct {
    void *LoggedData;
  } StickInput_PWORK_i;                /* '<S4>/Stick Input' */

  struct {
    void *LoggedData;
  } AngleofAttack_PWORK_e;             /* '<S5>/Angle of  Attack' */

  struct {
    void *LoggedData;
  } PilotGforceScope_PWORK_g;          /* '<S5>/Pilot G force Scope' */

  struct {
    void *LoggedData;
  } StickInput_PWORK_kf;               /* '<S5>/Stick Input' */

  struct {
    void *LoggedData;
  } AngleofAttack_PWORK_i;             /* '<S6>/Angle of  Attack' */

  struct {
    void *LoggedData;
  } PilotGforceScope_PWORK_d;          /* '<S6>/Pilot G force Scope' */

  struct {
    void *LoggedData;
  } StickInput_PWORK_g;                /* '<S6>/Stick Input' */

  struct {
    void *LoggedData;
  } AngleofAttack_PWORK_l;             /* '<S7>/Angle of  Attack' */

  struct {
    void *LoggedData;
  } PilotGforceScope_PWORK_a;          /* '<S7>/Pilot G force Scope' */

  struct {
    void *LoggedData;
  } StickInput_PWORK_o;                /* '<S7>/Stick Input' */

  struct {
    void *LoggedData;
  } AngleofAttack_PWORK_df;            /* '<S8>/Angle of  Attack' */

  struct {
    void *LoggedData;
  } PilotGforceScope_PWORK_m;          /* '<S8>/Pilot G force Scope' */

  struct {
    void *LoggedData;
  } StickInput_PWORK_l;                /* '<S8>/Stick Input' */

  struct {
    void *LoggedData;
  } AngleofAttack_PWORK_eb;            /* '<S9>/Angle of  Attack' */

  struct {
    void *LoggedData;
  } PilotGforceScope_PWORK_ic;         /* '<S9>/Pilot G force Scope' */

  struct {
    void *LoggedData;
  } StickInput_PWORK_is;               /* '<S9>/Stick Input' */

  struct {
    void *LoggedData;
  } AngleofAttack_PWORK_of;            /* '<S10>/Angle of  Attack' */

  struct {
    void *LoggedData;
  } PilotGforceScope_PWORK_a5;         /* '<S10>/Pilot G force Scope' */

  struct {
    void *LoggedData;
  } StickInput_PWORK_gt;               /* '<S10>/Stick Input' */

  struct {
    void *LoggedData;
  } AngleofAttack_PWORK_c;             /* '<S11>/Angle of  Attack' */

  struct {
    void *LoggedData;
  } PilotGforceScope_PWORK_gz;         /* '<S11>/Pilot G force Scope' */

  struct {
    void *LoggedData;
  } StickInput_PWORK_b;                /* '<S11>/Stick Input' */

  struct {
    void *LoggedData;
  } AngleofAttack_PWORK_de;            /* '<S12>/Angle of  Attack' */

  struct {
    void *LoggedData;
  } PilotGforceScope_PWORK_o;          /* '<S12>/Pilot G force Scope' */

  struct {
    void *LoggedData;
  } StickInput_PWORK_c;                /* '<S12>/Stick Input' */

  struct {
    void *LoggedData;
  } AngleofAttack_PWORK_k;             /* '<S13>/Angle of  Attack' */

  struct {
    void *LoggedData;
  } PilotGforceScope_PWORK_ii;         /* '<S13>/Pilot G force Scope' */

  struct {
    void *LoggedData;
  } StickInput_PWORK_dc;               /* '<S13>/Stick Input' */

  struct {
    void *LoggedData;
  } AngleofAttack_PWORK_h;             /* '<S14>/Angle of  Attack' */

  struct {
    void *LoggedData;
  } PilotGforceScope_PWORK_a5g;        /* '<S14>/Pilot G force Scope' */

  struct {
    void *LoggedData;
  } StickInput_PWORK_kc;               /* '<S14>/Stick Input' */

  struct {
    void *LoggedData;
  } AngleofAttack_PWORK_is;            /* '<S15>/Angle of  Attack' */

  struct {
    void *LoggedData;
  } PilotGforceScope_PWORK_gv;         /* '<S15>/Pilot G force Scope' */

  struct {
    void *LoggedData;
  } StickInput_PWORK_h;                /* '<S15>/Stick Input' */

  struct {
    void *LoggedData;
  } AngleofAttack_PWORK_ix;            /* '<S16>/Angle of  Attack' */

  struct {
    void *LoggedData;
  } PilotGforceScope_PWORK_h;          /* '<S16>/Pilot G force Scope' */

  struct {
    void *LoggedData;
  } StickInput_PWORK_oq;               /* '<S16>/Stick Input' */

  struct {
    void *LoggedData;
  } AngleofAttack_PWORK_n;             /* '<S17>/Angle of  Attack' */

  struct {
    void *LoggedData;
  } PilotGforceScope_PWORK_h3;         /* '<S17>/Pilot G force Scope' */

  struct {
    void *LoggedData;
  } StickInput_PWORK_hg;               /* '<S17>/Stick Input' */

  struct {
    void *LoggedData;
  } AngleofAttack_PWORK_ky;            /* '<S18>/Angle of  Attack' */

  struct {
    void *LoggedData;
  } PilotGforceScope_PWORK_a5z;        /* '<S18>/Pilot G force Scope' */

  struct {
    void *LoggedData;
  } StickInput_PWORK_p;                /* '<S18>/Stick Input' */

  struct {
    void *LoggedData;
  } AngleofAttack_PWORK_ng;            /* '<S19>/Angle of  Attack' */

  struct {
    void *LoggedData;
  } PilotGforceScope_PWORK_oc;         /* '<S19>/Pilot G force Scope' */

  struct {
    void *LoggedData;
  } StickInput_PWORK_n;                /* '<S19>/Stick Input' */

  struct {
    void *LoggedData;
  } AngleofAttack_PWORK_g;             /* '<S20>/Angle of  Attack' */

  struct {
    void *LoggedData;
  } PilotGforceScope_PWORK_aq;         /* '<S20>/Pilot G force Scope' */

  struct {
    void *LoggedData;
  } StickInput_PWORK_pz;               /* '<S20>/Stick Input' */

  struct {
    void *LoggedData;
  } AngleofAttack_PWORK_dg;            /* '<S21>/Angle of  Attack' */

  struct {
    void *LoggedData;
  } PilotGforceScope_PWORK_ai;         /* '<S21>/Pilot G force Scope' */

  struct {
    void *LoggedData;
  } StickInput_PWORK_f;                /* '<S21>/Stick Input' */

  struct {
    void *LoggedData;
  } AngleofAttack_PWORK_m;             /* '<S22>/Angle of  Attack' */

  struct {
    void *LoggedData;
  } PilotGforceScope_PWORK_jx;         /* '<S22>/Pilot G force Scope' */

  struct {
    void *LoggedData;
  } StickInput_PWORK_ly;               /* '<S22>/Stick Input' */

  struct {
    void *LoggedData;
  } AngleofAttack_PWORK_dfx;           /* '<S23>/Angle of  Attack' */

  struct {
    void *LoggedData;
  } PilotGforceScope_PWORK_k;          /* '<S23>/Pilot G force Scope' */

  struct {
    void *LoggedData;
  } StickInput_PWORK_m;                /* '<S23>/Stick Input' */

  struct {
    void *LoggedData;
  } AngleofAttack_PWORK_il;            /* '<S24>/Angle of  Attack' */

  struct {
    void *LoggedData;
  } PilotGforceScope_PWORK_l;          /* '<S24>/Pilot G force Scope' */

  struct {
    void *LoggedData;
  } StickInput_PWORK_or;               /* '<S24>/Stick Input' */

  struct {
    void *LoggedData;
  } AngleofAttack_PWORK_ac;            /* '<S25>/Angle of  Attack' */

  struct {
    void *LoggedData;
  } PilotGforceScope_PWORK_jxg;        /* '<S25>/Pilot G force Scope' */

  struct {
    void *LoggedData;
  } StickInput_PWORK_o4;               /* '<S25>/Stick Input' */

  uint32_T RandSeed;                   /* '<S30>/White Noise' */
  uint32_T RandSeed_n;                 /* '<S35>/White Noise' */
  uint32_T RandSeed_b;                 /* '<S40>/White Noise' */
  uint32_T RandSeed_c;                 /* '<S45>/White Noise' */
  uint32_T RandSeed_h;                 /* '<S50>/White Noise' */
  uint32_T RandSeed_d;                 /* '<S55>/White Noise' */
  uint32_T RandSeed_f;                 /* '<S60>/White Noise' */
  uint32_T RandSeed_g;                 /* '<S65>/White Noise' */
  uint32_T RandSeed_bq;                /* '<S70>/White Noise' */
  uint32_T RandSeed_e;                 /* '<S75>/White Noise' */
  uint32_T RandSeed_e1;                /* '<S80>/White Noise' */
  uint32_T RandSeed_bo;                /* '<S85>/White Noise' */
  uint32_T RandSeed_eo;                /* '<S90>/White Noise' */
  uint32_T RandSeed_dr;                /* '<S95>/White Noise' */
  uint32_T RandSeed_m;                 /* '<S100>/White Noise' */
  uint32_T RandSeed_md;                /* '<S105>/White Noise' */
  uint32_T RandSeed_fu;                /* '<S110>/White Noise' */
  uint32_T RandSeed_i;                 /* '<S115>/White Noise' */
  uint32_T RandSeed_fk;                /* '<S120>/White Noise' */
  uint32_T RandSeed_dd;                /* '<S125>/White Noise' */
  uint32_T RandSeed_j;                 /* '<S130>/White Noise' */
  uint32_T RandSeed_k;                 /* '<S135>/White Noise' */
  uint32_T RandSeed_ju;                /* '<S140>/White Noise' */
  uint32_T RandSeed_nb;                /* '<S145>/White Noise' */
  uint32_T RandSeed_ju4;               /* '<S150>/White Noise' */
} D_Work_f14tmp25;

/* Continuous states (auto storage) */
typedef struct {
  real_T TransferFcn2_CSTATE;          /* '<S26>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE;          /* '<S26>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE;         /* '<S1>/Actuator Model' */
  real_T Wgustmodel_CSTATE[2];         /* '<S28>/W-gust model' */
  real_T Qgustmodel_CSTATE;            /* '<S28>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CSTATE;/* '<S27>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE;        /* '<S27>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE;   /* '<S27>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompens;/* '<S27>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_h;        /* '<S31>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_p;        /* '<S31>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_a;       /* '<S2>/Actuator Model' */
  real_T Wgustmodel_CSTATE_f[2];       /* '<S33>/W-gust model' */
  real_T Qgustmodel_CSTATE_d;          /* '<S33>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CSTA_g;/* '<S32>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_a;      /* '<S32>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_k; /* '<S32>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompe_n;/* '<S32>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_g;        /* '<S36>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_o;        /* '<S36>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_j;       /* '<S3>/Actuator Model' */
  real_T Wgustmodel_CSTATE_m[2];       /* '<S38>/W-gust model' */
  real_T Qgustmodel_CSTATE_i;          /* '<S38>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CSTA_e;/* '<S37>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_ak;     /* '<S37>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_m; /* '<S37>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompe_f;/* '<S37>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_h0;       /* '<S41>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_h;        /* '<S41>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_h;       /* '<S4>/Actuator Model' */
  real_T Wgustmodel_CSTATE_g[2];       /* '<S43>/W-gust model' */
  real_T Qgustmodel_CSTATE_p;          /* '<S43>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CSTA_j;/* '<S42>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_i;      /* '<S42>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_c; /* '<S42>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompe_g;/* '<S42>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_m;        /* '<S46>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_i;        /* '<S46>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_f;       /* '<S5>/Actuator Model' */
  real_T Wgustmodel_CSTATE_a[2];       /* '<S48>/W-gust model' */
  real_T Qgustmodel_CSTATE_h;          /* '<S48>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CSTA_c;/* '<S47>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_h;      /* '<S47>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_l; /* '<S47>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcomp_gl;/* '<S47>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_p;        /* '<S51>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_n;        /* '<S51>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_aw;      /* '<S6>/Actuator Model' */
  real_T Wgustmodel_CSTATE_j[2];       /* '<S53>/W-gust model' */
  real_T Qgustmodel_CSTATE_pw;         /* '<S53>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CST_j4;/* '<S52>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_p;      /* '<S52>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_c5;/* '<S52>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompe_l;/* '<S52>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_n;        /* '<S56>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_b;        /* '<S56>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_k;       /* '<S7>/Actuator Model' */
  real_T Wgustmodel_CSTATE_mw[2];      /* '<S58>/W-gust model' */
  real_T Qgustmodel_CSTATE_l;          /* '<S58>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CST_ji;/* '<S57>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_d;      /* '<S57>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_j; /* '<S57>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompe_p;/* '<S57>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_o;        /* '<S61>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_nw;       /* '<S61>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_o;       /* '<S8>/Actuator Model' */
  real_T Wgustmodel_CSTATE_e[2];       /* '<S63>/W-gust model' */
  real_T Qgustmodel_CSTATE_b;          /* '<S63>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CST_ep;/* '<S62>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_hs;     /* '<S62>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_h; /* '<S62>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompe_h;/* '<S62>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_c;        /* '<S66>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_bm;       /* '<S66>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_ku;      /* '<S9>/Actuator Model' */
  real_T Wgustmodel_CSTATE_fj[2];      /* '<S68>/W-gust model' */
  real_T Qgustmodel_CSTATE_a;          /* '<S68>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CST_cd;/* '<S67>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_f;      /* '<S67>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_e; /* '<S67>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompe_i;/* '<S67>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_a;        /* '<S71>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_m;        /* '<S71>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_c;       /* '<S10>/Actuator Model' */
  real_T Wgustmodel_CSTATE_d[2];       /* '<S73>/W-gust model' */
  real_T Qgustmodel_CSTATE_o;          /* '<S73>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CST_ej;/* '<S72>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_n;      /* '<S72>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_e4;/* '<S72>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcomp_p5;/* '<S72>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_l;        /* '<S76>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_iz;       /* '<S76>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_hl;      /* '<S11>/Actuator Model' */
  real_T Wgustmodel_CSTATE_mo[2];      /* '<S78>/W-gust model' */
  real_T Qgustmodel_CSTATE_p3;         /* '<S78>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CSTA_i;/* '<S77>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_b;      /* '<S77>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_d; /* '<S77>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcomp_he;/* '<S77>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_b;        /* '<S81>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_l;        /* '<S81>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_d;       /* '<S12>/Actuator Model' */
  real_T Wgustmodel_CSTATE_n[2];       /* '<S83>/W-gust model' */
  real_T Qgustmodel_CSTATE_g;          /* '<S83>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CSTA_b;/* '<S82>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_j;      /* '<S82>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_f; /* '<S82>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompe_o;/* '<S82>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_n5;       /* '<S86>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_k;        /* '<S86>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_fg;      /* '<S13>/Actuator Model' */
  real_T Wgustmodel_CSTATE_i[2];       /* '<S88>/W-gust model' */
  real_T Qgustmodel_CSTATE_k;          /* '<S88>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CST_i1;/* '<S87>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_jz;     /* '<S87>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_n; /* '<S87>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcomp_hi;/* '<S87>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_k;        /* '<S91>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_g;        /* '<S91>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_ov;      /* '<S14>/Actuator Model' */
  real_T Wgustmodel_CSTATE_p[2];       /* '<S93>/W-gust model' */
  real_T Qgustmodel_CSTATE_m;          /* '<S93>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CSTA_h;/* '<S92>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_c;      /* '<S92>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_m2;/* '<S92>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcomp_gw;/* '<S92>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_ki;       /* '<S96>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_im;       /* '<S96>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_i;       /* '<S15>/Actuator Model' */
  real_T Wgustmodel_CSTATE_o[2];       /* '<S98>/W-gust model' */
  real_T Qgustmodel_CSTATE_n;          /* '<S98>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CST_ef;/* '<S97>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_n1;     /* '<S97>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_mp;/* '<S97>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompe_j;/* '<S97>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_oa;       /* '<S101>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_a;        /* '<S101>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_e;       /* '<S16>/Actuator Model' */
  real_T Wgustmodel_CSTATE_it[2];      /* '<S103>/W-gust model' */
  real_T Qgustmodel_CSTATE_ie;         /* '<S103>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CST_gn;/* '<S102>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_bs;     /* '<S102>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_mo;/* '<S102>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompe_k;/* '<S102>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_bv;       /* '<S106>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_kr;       /* '<S106>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_l;       /* '<S17>/Actuator Model' */
  real_T Wgustmodel_CSTATE_h[2];       /* '<S108>/W-gust model' */
  real_T Qgustmodel_CSTATE_kp;         /* '<S108>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CSTA_p;/* '<S107>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_pr;     /* '<S107>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_fn;/* '<S107>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcomp_lg;/* '<S107>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_ku;       /* '<S111>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_ku;       /* '<S111>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_hh;      /* '<S18>/Actuator Model' */
  real_T Wgustmodel_CSTATE_e5[2];      /* '<S113>/W-gust model' */
  real_T Qgustmodel_CSTATE_f;          /* '<S113>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CST_ba;/* '<S112>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_p3;     /* '<S112>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_ke;/* '<S112>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompe_c;/* '<S112>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_e;        /* '<S116>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_j;        /* '<S116>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_p;       /* '<S19>/Actuator Model' */
  real_T Wgustmodel_CSTATE_k[2];       /* '<S118>/W-gust model' */
  real_T Qgustmodel_CSTATE_ad;         /* '<S118>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CSTA_k;/* '<S117>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_ju;     /* '<S117>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_ez;/* '<S117>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcomp_jd;/* '<S117>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_kz;       /* '<S121>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_pe;       /* '<S121>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_ol;      /* '<S20>/Actuator Model' */
  real_T Wgustmodel_CSTATE_if[2];      /* '<S123>/W-gust model' */
  real_T Qgustmodel_CSTATE_mh;         /* '<S123>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CST_ku;/* '<S122>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_m;      /* '<S122>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_f0;/* '<S122>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcomp_kq;/* '<S122>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_ar;       /* '<S126>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_id;       /* '<S126>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_g;       /* '<S21>/Actuator Model' */
  real_T Wgustmodel_CSTATE_iv[2];      /* '<S128>/W-gust model' */
  real_T Qgustmodel_CSTATE_ob;         /* '<S128>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CST_pj;/* '<S127>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_ah;     /* '<S127>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_p; /* '<S127>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcomp_jw;/* '<S127>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_lp;       /* '<S131>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_je;       /* '<S131>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_fk;      /* '<S22>/Actuator Model' */
  real_T Wgustmodel_CSTATE_gw[2];      /* '<S133>/W-gust model' */
  real_T Qgustmodel_CSTATE_e;          /* '<S133>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CSTA_d;/* '<S132>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_o;      /* '<S132>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_a; /* '<S132>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcomp_iz;/* '<S132>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_aw;       /* '<S136>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_be;       /* '<S136>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_pq;      /* '<S23>/Actuator Model' */
  real_T Wgustmodel_CSTATE_c[2];       /* '<S138>/W-gust model' */
  real_T Qgustmodel_CSTATE_fh;         /* '<S138>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CST_b1;/* '<S137>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_p2;     /* '<S137>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_au;/* '<S137>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcomp_nm;/* '<S137>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_ms;       /* '<S141>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_nz;       /* '<S141>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_fb;      /* '<S24>/Actuator Model' */
  real_T Wgustmodel_CSTATE_h3[2];      /* '<S143>/W-gust model' */
  real_T Qgustmodel_CSTATE_c;          /* '<S143>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CST_jw;/* '<S142>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_ns;     /* '<S142>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_ds;/* '<S142>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompe_a;/* '<S142>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_bk;       /* '<S146>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_gr;       /* '<S146>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_iv;      /* '<S25>/Actuator Model' */
  real_T Wgustmodel_CSTATE_b[2];       /* '<S148>/W-gust model' */
  real_T Qgustmodel_CSTATE_lb;         /* '<S148>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CST_iy;/* '<S147>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_pb;     /* '<S147>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_ak;/* '<S147>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcomp_ab;/* '<S147>/Proportional plus integral compensator' */
} ContinuousStates_f14tmp25;

/* State derivatives (auto storage) */
typedef struct {
  real_T TransferFcn2_CSTATE;          /* '<S26>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE;          /* '<S26>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE;         /* '<S1>/Actuator Model' */
  real_T Wgustmodel_CSTATE[2];         /* '<S28>/W-gust model' */
  real_T Qgustmodel_CSTATE;            /* '<S28>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CSTATE;/* '<S27>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE;        /* '<S27>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE;   /* '<S27>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompens;/* '<S27>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_h;        /* '<S31>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_p;        /* '<S31>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_a;       /* '<S2>/Actuator Model' */
  real_T Wgustmodel_CSTATE_f[2];       /* '<S33>/W-gust model' */
  real_T Qgustmodel_CSTATE_d;          /* '<S33>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CSTA_g;/* '<S32>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_a;      /* '<S32>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_k; /* '<S32>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompe_n;/* '<S32>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_g;        /* '<S36>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_o;        /* '<S36>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_j;       /* '<S3>/Actuator Model' */
  real_T Wgustmodel_CSTATE_m[2];       /* '<S38>/W-gust model' */
  real_T Qgustmodel_CSTATE_i;          /* '<S38>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CSTA_e;/* '<S37>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_ak;     /* '<S37>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_m; /* '<S37>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompe_f;/* '<S37>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_h0;       /* '<S41>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_h;        /* '<S41>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_h;       /* '<S4>/Actuator Model' */
  real_T Wgustmodel_CSTATE_g[2];       /* '<S43>/W-gust model' */
  real_T Qgustmodel_CSTATE_p;          /* '<S43>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CSTA_j;/* '<S42>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_i;      /* '<S42>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_c; /* '<S42>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompe_g;/* '<S42>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_m;        /* '<S46>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_i;        /* '<S46>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_f;       /* '<S5>/Actuator Model' */
  real_T Wgustmodel_CSTATE_a[2];       /* '<S48>/W-gust model' */
  real_T Qgustmodel_CSTATE_h;          /* '<S48>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CSTA_c;/* '<S47>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_h;      /* '<S47>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_l; /* '<S47>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcomp_gl;/* '<S47>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_p;        /* '<S51>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_n;        /* '<S51>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_aw;      /* '<S6>/Actuator Model' */
  real_T Wgustmodel_CSTATE_j[2];       /* '<S53>/W-gust model' */
  real_T Qgustmodel_CSTATE_pw;         /* '<S53>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CST_j4;/* '<S52>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_p;      /* '<S52>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_c5;/* '<S52>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompe_l;/* '<S52>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_n;        /* '<S56>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_b;        /* '<S56>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_k;       /* '<S7>/Actuator Model' */
  real_T Wgustmodel_CSTATE_mw[2];      /* '<S58>/W-gust model' */
  real_T Qgustmodel_CSTATE_l;          /* '<S58>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CST_ji;/* '<S57>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_d;      /* '<S57>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_j; /* '<S57>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompe_p;/* '<S57>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_o;        /* '<S61>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_nw;       /* '<S61>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_o;       /* '<S8>/Actuator Model' */
  real_T Wgustmodel_CSTATE_e[2];       /* '<S63>/W-gust model' */
  real_T Qgustmodel_CSTATE_b;          /* '<S63>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CST_ep;/* '<S62>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_hs;     /* '<S62>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_h; /* '<S62>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompe_h;/* '<S62>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_c;        /* '<S66>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_bm;       /* '<S66>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_ku;      /* '<S9>/Actuator Model' */
  real_T Wgustmodel_CSTATE_fj[2];      /* '<S68>/W-gust model' */
  real_T Qgustmodel_CSTATE_a;          /* '<S68>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CST_cd;/* '<S67>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_f;      /* '<S67>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_e; /* '<S67>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompe_i;/* '<S67>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_a;        /* '<S71>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_m;        /* '<S71>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_c;       /* '<S10>/Actuator Model' */
  real_T Wgustmodel_CSTATE_d[2];       /* '<S73>/W-gust model' */
  real_T Qgustmodel_CSTATE_o;          /* '<S73>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CST_ej;/* '<S72>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_n;      /* '<S72>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_e4;/* '<S72>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcomp_p5;/* '<S72>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_l;        /* '<S76>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_iz;       /* '<S76>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_hl;      /* '<S11>/Actuator Model' */
  real_T Wgustmodel_CSTATE_mo[2];      /* '<S78>/W-gust model' */
  real_T Qgustmodel_CSTATE_p3;         /* '<S78>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CSTA_i;/* '<S77>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_b;      /* '<S77>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_d; /* '<S77>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcomp_he;/* '<S77>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_b;        /* '<S81>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_l;        /* '<S81>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_d;       /* '<S12>/Actuator Model' */
  real_T Wgustmodel_CSTATE_n[2];       /* '<S83>/W-gust model' */
  real_T Qgustmodel_CSTATE_g;          /* '<S83>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CSTA_b;/* '<S82>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_j;      /* '<S82>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_f; /* '<S82>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompe_o;/* '<S82>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_n5;       /* '<S86>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_k;        /* '<S86>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_fg;      /* '<S13>/Actuator Model' */
  real_T Wgustmodel_CSTATE_i[2];       /* '<S88>/W-gust model' */
  real_T Qgustmodel_CSTATE_k;          /* '<S88>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CST_i1;/* '<S87>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_jz;     /* '<S87>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_n; /* '<S87>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcomp_hi;/* '<S87>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_k;        /* '<S91>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_g;        /* '<S91>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_ov;      /* '<S14>/Actuator Model' */
  real_T Wgustmodel_CSTATE_p[2];       /* '<S93>/W-gust model' */
  real_T Qgustmodel_CSTATE_m;          /* '<S93>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CSTA_h;/* '<S92>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_c;      /* '<S92>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_m2;/* '<S92>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcomp_gw;/* '<S92>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_ki;       /* '<S96>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_im;       /* '<S96>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_i;       /* '<S15>/Actuator Model' */
  real_T Wgustmodel_CSTATE_o[2];       /* '<S98>/W-gust model' */
  real_T Qgustmodel_CSTATE_n;          /* '<S98>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CST_ef;/* '<S97>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_n1;     /* '<S97>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_mp;/* '<S97>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompe_j;/* '<S97>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_oa;       /* '<S101>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_a;        /* '<S101>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_e;       /* '<S16>/Actuator Model' */
  real_T Wgustmodel_CSTATE_it[2];      /* '<S103>/W-gust model' */
  real_T Qgustmodel_CSTATE_ie;         /* '<S103>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CST_gn;/* '<S102>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_bs;     /* '<S102>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_mo;/* '<S102>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompe_k;/* '<S102>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_bv;       /* '<S106>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_kr;       /* '<S106>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_l;       /* '<S17>/Actuator Model' */
  real_T Wgustmodel_CSTATE_h[2];       /* '<S108>/W-gust model' */
  real_T Qgustmodel_CSTATE_kp;         /* '<S108>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CSTA_p;/* '<S107>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_pr;     /* '<S107>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_fn;/* '<S107>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcomp_lg;/* '<S107>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_ku;       /* '<S111>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_ku;       /* '<S111>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_hh;      /* '<S18>/Actuator Model' */
  real_T Wgustmodel_CSTATE_e5[2];      /* '<S113>/W-gust model' */
  real_T Qgustmodel_CSTATE_f;          /* '<S113>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CST_ba;/* '<S112>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_p3;     /* '<S112>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_ke;/* '<S112>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompe_c;/* '<S112>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_e;        /* '<S116>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_j;        /* '<S116>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_p;       /* '<S19>/Actuator Model' */
  real_T Wgustmodel_CSTATE_k[2];       /* '<S118>/W-gust model' */
  real_T Qgustmodel_CSTATE_ad;         /* '<S118>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CSTA_k;/* '<S117>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_ju;     /* '<S117>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_ez;/* '<S117>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcomp_jd;/* '<S117>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_kz;       /* '<S121>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_pe;       /* '<S121>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_ol;      /* '<S20>/Actuator Model' */
  real_T Wgustmodel_CSTATE_if[2];      /* '<S123>/W-gust model' */
  real_T Qgustmodel_CSTATE_mh;         /* '<S123>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CST_ku;/* '<S122>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_m;      /* '<S122>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_f0;/* '<S122>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcomp_kq;/* '<S122>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_ar;       /* '<S126>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_id;       /* '<S126>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_g;       /* '<S21>/Actuator Model' */
  real_T Wgustmodel_CSTATE_iv[2];      /* '<S128>/W-gust model' */
  real_T Qgustmodel_CSTATE_ob;         /* '<S128>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CST_pj;/* '<S127>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_ah;     /* '<S127>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_p; /* '<S127>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcomp_jw;/* '<S127>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_lp;       /* '<S131>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_je;       /* '<S131>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_fk;      /* '<S22>/Actuator Model' */
  real_T Wgustmodel_CSTATE_gw[2];      /* '<S133>/W-gust model' */
  real_T Qgustmodel_CSTATE_e;          /* '<S133>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CSTA_d;/* '<S132>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_o;      /* '<S132>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_a; /* '<S132>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcomp_iz;/* '<S132>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_aw;       /* '<S136>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_be;       /* '<S136>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_pq;      /* '<S23>/Actuator Model' */
  real_T Wgustmodel_CSTATE_c[2];       /* '<S138>/W-gust model' */
  real_T Qgustmodel_CSTATE_fh;         /* '<S138>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CST_b1;/* '<S137>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_p2;     /* '<S137>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_au;/* '<S137>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcomp_nm;/* '<S137>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_ms;       /* '<S141>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_nz;       /* '<S141>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_fb;      /* '<S24>/Actuator Model' */
  real_T Wgustmodel_CSTATE_h3[2];      /* '<S143>/W-gust model' */
  real_T Qgustmodel_CSTATE_c;          /* '<S143>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CST_jw;/* '<S142>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_ns;     /* '<S142>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_ds;/* '<S142>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcompe_a;/* '<S142>/Proportional plus integral compensator' */
  real_T TransferFcn2_CSTATE_bk;       /* '<S146>/Transfer Fcn.2' */
  real_T TransferFcn1_CSTATE_gr;       /* '<S146>/Transfer Fcn.1' */
  real_T ActuatorModel_CSTATE_iv;      /* '<S25>/Actuator Model' */
  real_T Wgustmodel_CSTATE_b[2];       /* '<S148>/W-gust model' */
  real_T Qgustmodel_CSTATE_lb;         /* '<S148>/Q-gust model' */
  real_T AlphasensorLowpassFilter_CST_iy;/* '<S147>/Alpha-sensor Low-pass Filter' */
  real_T StickPrefilter_CSTATE_pb;     /* '<S147>/Stick Prefilter' */
  real_T PitchRateLeadFilter_CSTATE_ak;/* '<S147>/Pitch Rate Lead Filter' */
  real_T Proportionalplusintegralcomp_ab;/* '<S147>/Proportional plus integral compensator' */
} StateDerivatives_f14tmp25;

/* State disabled  */
typedef struct {
  boolean_T TransferFcn2_CSTATE;       /* '<S26>/Transfer Fcn.2' */
  boolean_T TransferFcn1_CSTATE;       /* '<S26>/Transfer Fcn.1' */
  boolean_T ActuatorModel_CSTATE;      /* '<S1>/Actuator Model' */
  boolean_T Wgustmodel_CSTATE[2];      /* '<S28>/W-gust model' */
  boolean_T Qgustmodel_CSTATE;         /* '<S28>/Q-gust model' */
  boolean_T AlphasensorLowpassFilter_CSTATE;/* '<S27>/Alpha-sensor Low-pass Filter' */
  boolean_T StickPrefilter_CSTATE;     /* '<S27>/Stick Prefilter' */
  boolean_T PitchRateLeadFilter_CSTATE;/* '<S27>/Pitch Rate Lead Filter' */
  boolean_T Proportionalplusintegralcompens;/* '<S27>/Proportional plus integral compensator' */
  boolean_T TransferFcn2_CSTATE_h;     /* '<S31>/Transfer Fcn.2' */
  boolean_T TransferFcn1_CSTATE_p;     /* '<S31>/Transfer Fcn.1' */
  boolean_T ActuatorModel_CSTATE_a;    /* '<S2>/Actuator Model' */
  boolean_T Wgustmodel_CSTATE_f[2];    /* '<S33>/W-gust model' */
  boolean_T Qgustmodel_CSTATE_d;       /* '<S33>/Q-gust model' */
  boolean_T AlphasensorLowpassFilter_CSTA_g;/* '<S32>/Alpha-sensor Low-pass Filter' */
  boolean_T StickPrefilter_CSTATE_a;   /* '<S32>/Stick Prefilter' */
  boolean_T PitchRateLeadFilter_CSTATE_k;/* '<S32>/Pitch Rate Lead Filter' */
  boolean_T Proportionalplusintegralcompe_n;/* '<S32>/Proportional plus integral compensator' */
  boolean_T TransferFcn2_CSTATE_g;     /* '<S36>/Transfer Fcn.2' */
  boolean_T TransferFcn1_CSTATE_o;     /* '<S36>/Transfer Fcn.1' */
  boolean_T ActuatorModel_CSTATE_j;    /* '<S3>/Actuator Model' */
  boolean_T Wgustmodel_CSTATE_m[2];    /* '<S38>/W-gust model' */
  boolean_T Qgustmodel_CSTATE_i;       /* '<S38>/Q-gust model' */
  boolean_T AlphasensorLowpassFilter_CSTA_e;/* '<S37>/Alpha-sensor Low-pass Filter' */
  boolean_T StickPrefilter_CSTATE_ak;  /* '<S37>/Stick Prefilter' */
  boolean_T PitchRateLeadFilter_CSTATE_m;/* '<S37>/Pitch Rate Lead Filter' */
  boolean_T Proportionalplusintegralcompe_f;/* '<S37>/Proportional plus integral compensator' */
  boolean_T TransferFcn2_CSTATE_h0;    /* '<S41>/Transfer Fcn.2' */
  boolean_T TransferFcn1_CSTATE_h;     /* '<S41>/Transfer Fcn.1' */
  boolean_T ActuatorModel_CSTATE_h;    /* '<S4>/Actuator Model' */
  boolean_T Wgustmodel_CSTATE_g[2];    /* '<S43>/W-gust model' */
  boolean_T Qgustmodel_CSTATE_p;       /* '<S43>/Q-gust model' */
  boolean_T AlphasensorLowpassFilter_CSTA_j;/* '<S42>/Alpha-sensor Low-pass Filter' */
  boolean_T StickPrefilter_CSTATE_i;   /* '<S42>/Stick Prefilter' */
  boolean_T PitchRateLeadFilter_CSTATE_c;/* '<S42>/Pitch Rate Lead Filter' */
  boolean_T Proportionalplusintegralcompe_g;/* '<S42>/Proportional plus integral compensator' */
  boolean_T TransferFcn2_CSTATE_m;     /* '<S46>/Transfer Fcn.2' */
  boolean_T TransferFcn1_CSTATE_i;     /* '<S46>/Transfer Fcn.1' */
  boolean_T ActuatorModel_CSTATE_f;    /* '<S5>/Actuator Model' */
  boolean_T Wgustmodel_CSTATE_a[2];    /* '<S48>/W-gust model' */
  boolean_T Qgustmodel_CSTATE_h;       /* '<S48>/Q-gust model' */
  boolean_T AlphasensorLowpassFilter_CSTA_c;/* '<S47>/Alpha-sensor Low-pass Filter' */
  boolean_T StickPrefilter_CSTATE_h;   /* '<S47>/Stick Prefilter' */
  boolean_T PitchRateLeadFilter_CSTATE_l;/* '<S47>/Pitch Rate Lead Filter' */
  boolean_T Proportionalplusintegralcomp_gl;/* '<S47>/Proportional plus integral compensator' */
  boolean_T TransferFcn2_CSTATE_p;     /* '<S51>/Transfer Fcn.2' */
  boolean_T TransferFcn1_CSTATE_n;     /* '<S51>/Transfer Fcn.1' */
  boolean_T ActuatorModel_CSTATE_aw;   /* '<S6>/Actuator Model' */
  boolean_T Wgustmodel_CSTATE_j[2];    /* '<S53>/W-gust model' */
  boolean_T Qgustmodel_CSTATE_pw;      /* '<S53>/Q-gust model' */
  boolean_T AlphasensorLowpassFilter_CST_j4;/* '<S52>/Alpha-sensor Low-pass Filter' */
  boolean_T StickPrefilter_CSTATE_p;   /* '<S52>/Stick Prefilter' */
  boolean_T PitchRateLeadFilter_CSTATE_c5;/* '<S52>/Pitch Rate Lead Filter' */
  boolean_T Proportionalplusintegralcompe_l;/* '<S52>/Proportional plus integral compensator' */
  boolean_T TransferFcn2_CSTATE_n;     /* '<S56>/Transfer Fcn.2' */
  boolean_T TransferFcn1_CSTATE_b;     /* '<S56>/Transfer Fcn.1' */
  boolean_T ActuatorModel_CSTATE_k;    /* '<S7>/Actuator Model' */
  boolean_T Wgustmodel_CSTATE_mw[2];   /* '<S58>/W-gust model' */
  boolean_T Qgustmodel_CSTATE_l;       /* '<S58>/Q-gust model' */
  boolean_T AlphasensorLowpassFilter_CST_ji;/* '<S57>/Alpha-sensor Low-pass Filter' */
  boolean_T StickPrefilter_CSTATE_d;   /* '<S57>/Stick Prefilter' */
  boolean_T PitchRateLeadFilter_CSTATE_j;/* '<S57>/Pitch Rate Lead Filter' */
  boolean_T Proportionalplusintegralcompe_p;/* '<S57>/Proportional plus integral compensator' */
  boolean_T TransferFcn2_CSTATE_o;     /* '<S61>/Transfer Fcn.2' */
  boolean_T TransferFcn1_CSTATE_nw;    /* '<S61>/Transfer Fcn.1' */
  boolean_T ActuatorModel_CSTATE_o;    /* '<S8>/Actuator Model' */
  boolean_T Wgustmodel_CSTATE_e[2];    /* '<S63>/W-gust model' */
  boolean_T Qgustmodel_CSTATE_b;       /* '<S63>/Q-gust model' */
  boolean_T AlphasensorLowpassFilter_CST_ep;/* '<S62>/Alpha-sensor Low-pass Filter' */
  boolean_T StickPrefilter_CSTATE_hs;  /* '<S62>/Stick Prefilter' */
  boolean_T PitchRateLeadFilter_CSTATE_h;/* '<S62>/Pitch Rate Lead Filter' */
  boolean_T Proportionalplusintegralcompe_h;/* '<S62>/Proportional plus integral compensator' */
  boolean_T TransferFcn2_CSTATE_c;     /* '<S66>/Transfer Fcn.2' */
  boolean_T TransferFcn1_CSTATE_bm;    /* '<S66>/Transfer Fcn.1' */
  boolean_T ActuatorModel_CSTATE_ku;   /* '<S9>/Actuator Model' */
  boolean_T Wgustmodel_CSTATE_fj[2];   /* '<S68>/W-gust model' */
  boolean_T Qgustmodel_CSTATE_a;       /* '<S68>/Q-gust model' */
  boolean_T AlphasensorLowpassFilter_CST_cd;/* '<S67>/Alpha-sensor Low-pass Filter' */
  boolean_T StickPrefilter_CSTATE_f;   /* '<S67>/Stick Prefilter' */
  boolean_T PitchRateLeadFilter_CSTATE_e;/* '<S67>/Pitch Rate Lead Filter' */
  boolean_T Proportionalplusintegralcompe_i;/* '<S67>/Proportional plus integral compensator' */
  boolean_T TransferFcn2_CSTATE_a;     /* '<S71>/Transfer Fcn.2' */
  boolean_T TransferFcn1_CSTATE_m;     /* '<S71>/Transfer Fcn.1' */
  boolean_T ActuatorModel_CSTATE_c;    /* '<S10>/Actuator Model' */
  boolean_T Wgustmodel_CSTATE_d[2];    /* '<S73>/W-gust model' */
  boolean_T Qgustmodel_CSTATE_o;       /* '<S73>/Q-gust model' */
  boolean_T AlphasensorLowpassFilter_CST_ej;/* '<S72>/Alpha-sensor Low-pass Filter' */
  boolean_T StickPrefilter_CSTATE_n;   /* '<S72>/Stick Prefilter' */
  boolean_T PitchRateLeadFilter_CSTATE_e4;/* '<S72>/Pitch Rate Lead Filter' */
  boolean_T Proportionalplusintegralcomp_p5;/* '<S72>/Proportional plus integral compensator' */
  boolean_T TransferFcn2_CSTATE_l;     /* '<S76>/Transfer Fcn.2' */
  boolean_T TransferFcn1_CSTATE_iz;    /* '<S76>/Transfer Fcn.1' */
  boolean_T ActuatorModel_CSTATE_hl;   /* '<S11>/Actuator Model' */
  boolean_T Wgustmodel_CSTATE_mo[2];   /* '<S78>/W-gust model' */
  boolean_T Qgustmodel_CSTATE_p3;      /* '<S78>/Q-gust model' */
  boolean_T AlphasensorLowpassFilter_CSTA_i;/* '<S77>/Alpha-sensor Low-pass Filter' */
  boolean_T StickPrefilter_CSTATE_b;   /* '<S77>/Stick Prefilter' */
  boolean_T PitchRateLeadFilter_CSTATE_d;/* '<S77>/Pitch Rate Lead Filter' */
  boolean_T Proportionalplusintegralcomp_he;/* '<S77>/Proportional plus integral compensator' */
  boolean_T TransferFcn2_CSTATE_b;     /* '<S81>/Transfer Fcn.2' */
  boolean_T TransferFcn1_CSTATE_l;     /* '<S81>/Transfer Fcn.1' */
  boolean_T ActuatorModel_CSTATE_d;    /* '<S12>/Actuator Model' */
  boolean_T Wgustmodel_CSTATE_n[2];    /* '<S83>/W-gust model' */
  boolean_T Qgustmodel_CSTATE_g;       /* '<S83>/Q-gust model' */
  boolean_T AlphasensorLowpassFilter_CSTA_b;/* '<S82>/Alpha-sensor Low-pass Filter' */
  boolean_T StickPrefilter_CSTATE_j;   /* '<S82>/Stick Prefilter' */
  boolean_T PitchRateLeadFilter_CSTATE_f;/* '<S82>/Pitch Rate Lead Filter' */
  boolean_T Proportionalplusintegralcompe_o;/* '<S82>/Proportional plus integral compensator' */
  boolean_T TransferFcn2_CSTATE_n5;    /* '<S86>/Transfer Fcn.2' */
  boolean_T TransferFcn1_CSTATE_k;     /* '<S86>/Transfer Fcn.1' */
  boolean_T ActuatorModel_CSTATE_fg;   /* '<S13>/Actuator Model' */
  boolean_T Wgustmodel_CSTATE_i[2];    /* '<S88>/W-gust model' */
  boolean_T Qgustmodel_CSTATE_k;       /* '<S88>/Q-gust model' */
  boolean_T AlphasensorLowpassFilter_CST_i1;/* '<S87>/Alpha-sensor Low-pass Filter' */
  boolean_T StickPrefilter_CSTATE_jz;  /* '<S87>/Stick Prefilter' */
  boolean_T PitchRateLeadFilter_CSTATE_n;/* '<S87>/Pitch Rate Lead Filter' */
  boolean_T Proportionalplusintegralcomp_hi;/* '<S87>/Proportional plus integral compensator' */
  boolean_T TransferFcn2_CSTATE_k;     /* '<S91>/Transfer Fcn.2' */
  boolean_T TransferFcn1_CSTATE_g;     /* '<S91>/Transfer Fcn.1' */
  boolean_T ActuatorModel_CSTATE_ov;   /* '<S14>/Actuator Model' */
  boolean_T Wgustmodel_CSTATE_p[2];    /* '<S93>/W-gust model' */
  boolean_T Qgustmodel_CSTATE_m;       /* '<S93>/Q-gust model' */
  boolean_T AlphasensorLowpassFilter_CSTA_h;/* '<S92>/Alpha-sensor Low-pass Filter' */
  boolean_T StickPrefilter_CSTATE_c;   /* '<S92>/Stick Prefilter' */
  boolean_T PitchRateLeadFilter_CSTATE_m2;/* '<S92>/Pitch Rate Lead Filter' */
  boolean_T Proportionalplusintegralcomp_gw;/* '<S92>/Proportional plus integral compensator' */
  boolean_T TransferFcn2_CSTATE_ki;    /* '<S96>/Transfer Fcn.2' */
  boolean_T TransferFcn1_CSTATE_im;    /* '<S96>/Transfer Fcn.1' */
  boolean_T ActuatorModel_CSTATE_i;    /* '<S15>/Actuator Model' */
  boolean_T Wgustmodel_CSTATE_o[2];    /* '<S98>/W-gust model' */
  boolean_T Qgustmodel_CSTATE_n;       /* '<S98>/Q-gust model' */
  boolean_T AlphasensorLowpassFilter_CST_ef;/* '<S97>/Alpha-sensor Low-pass Filter' */
  boolean_T StickPrefilter_CSTATE_n1;  /* '<S97>/Stick Prefilter' */
  boolean_T PitchRateLeadFilter_CSTATE_mp;/* '<S97>/Pitch Rate Lead Filter' */
  boolean_T Proportionalplusintegralcompe_j;/* '<S97>/Proportional plus integral compensator' */
  boolean_T TransferFcn2_CSTATE_oa;    /* '<S101>/Transfer Fcn.2' */
  boolean_T TransferFcn1_CSTATE_a;     /* '<S101>/Transfer Fcn.1' */
  boolean_T ActuatorModel_CSTATE_e;    /* '<S16>/Actuator Model' */
  boolean_T Wgustmodel_CSTATE_it[2];   /* '<S103>/W-gust model' */
  boolean_T Qgustmodel_CSTATE_ie;      /* '<S103>/Q-gust model' */
  boolean_T AlphasensorLowpassFilter_CST_gn;/* '<S102>/Alpha-sensor Low-pass Filter' */
  boolean_T StickPrefilter_CSTATE_bs;  /* '<S102>/Stick Prefilter' */
  boolean_T PitchRateLeadFilter_CSTATE_mo;/* '<S102>/Pitch Rate Lead Filter' */
  boolean_T Proportionalplusintegralcompe_k;/* '<S102>/Proportional plus integral compensator' */
  boolean_T TransferFcn2_CSTATE_bv;    /* '<S106>/Transfer Fcn.2' */
  boolean_T TransferFcn1_CSTATE_kr;    /* '<S106>/Transfer Fcn.1' */
  boolean_T ActuatorModel_CSTATE_l;    /* '<S17>/Actuator Model' */
  boolean_T Wgustmodel_CSTATE_h[2];    /* '<S108>/W-gust model' */
  boolean_T Qgustmodel_CSTATE_kp;      /* '<S108>/Q-gust model' */
  boolean_T AlphasensorLowpassFilter_CSTA_p;/* '<S107>/Alpha-sensor Low-pass Filter' */
  boolean_T StickPrefilter_CSTATE_pr;  /* '<S107>/Stick Prefilter' */
  boolean_T PitchRateLeadFilter_CSTATE_fn;/* '<S107>/Pitch Rate Lead Filter' */
  boolean_T Proportionalplusintegralcomp_lg;/* '<S107>/Proportional plus integral compensator' */
  boolean_T TransferFcn2_CSTATE_ku;    /* '<S111>/Transfer Fcn.2' */
  boolean_T TransferFcn1_CSTATE_ku;    /* '<S111>/Transfer Fcn.1' */
  boolean_T ActuatorModel_CSTATE_hh;   /* '<S18>/Actuator Model' */
  boolean_T Wgustmodel_CSTATE_e5[2];   /* '<S113>/W-gust model' */
  boolean_T Qgustmodel_CSTATE_f;       /* '<S113>/Q-gust model' */
  boolean_T AlphasensorLowpassFilter_CST_ba;/* '<S112>/Alpha-sensor Low-pass Filter' */
  boolean_T StickPrefilter_CSTATE_p3;  /* '<S112>/Stick Prefilter' */
  boolean_T PitchRateLeadFilter_CSTATE_ke;/* '<S112>/Pitch Rate Lead Filter' */
  boolean_T Proportionalplusintegralcompe_c;/* '<S112>/Proportional plus integral compensator' */
  boolean_T TransferFcn2_CSTATE_e;     /* '<S116>/Transfer Fcn.2' */
  boolean_T TransferFcn1_CSTATE_j;     /* '<S116>/Transfer Fcn.1' */
  boolean_T ActuatorModel_CSTATE_p;    /* '<S19>/Actuator Model' */
  boolean_T Wgustmodel_CSTATE_k[2];    /* '<S118>/W-gust model' */
  boolean_T Qgustmodel_CSTATE_ad;      /* '<S118>/Q-gust model' */
  boolean_T AlphasensorLowpassFilter_CSTA_k;/* '<S117>/Alpha-sensor Low-pass Filter' */
  boolean_T StickPrefilter_CSTATE_ju;  /* '<S117>/Stick Prefilter' */
  boolean_T PitchRateLeadFilter_CSTATE_ez;/* '<S117>/Pitch Rate Lead Filter' */
  boolean_T Proportionalplusintegralcomp_jd;/* '<S117>/Proportional plus integral compensator' */
  boolean_T TransferFcn2_CSTATE_kz;    /* '<S121>/Transfer Fcn.2' */
  boolean_T TransferFcn1_CSTATE_pe;    /* '<S121>/Transfer Fcn.1' */
  boolean_T ActuatorModel_CSTATE_ol;   /* '<S20>/Actuator Model' */
  boolean_T Wgustmodel_CSTATE_if[2];   /* '<S123>/W-gust model' */
  boolean_T Qgustmodel_CSTATE_mh;      /* '<S123>/Q-gust model' */
  boolean_T AlphasensorLowpassFilter_CST_ku;/* '<S122>/Alpha-sensor Low-pass Filter' */
  boolean_T StickPrefilter_CSTATE_m;   /* '<S122>/Stick Prefilter' */
  boolean_T PitchRateLeadFilter_CSTATE_f0;/* '<S122>/Pitch Rate Lead Filter' */
  boolean_T Proportionalplusintegralcomp_kq;/* '<S122>/Proportional plus integral compensator' */
  boolean_T TransferFcn2_CSTATE_ar;    /* '<S126>/Transfer Fcn.2' */
  boolean_T TransferFcn1_CSTATE_id;    /* '<S126>/Transfer Fcn.1' */
  boolean_T ActuatorModel_CSTATE_g;    /* '<S21>/Actuator Model' */
  boolean_T Wgustmodel_CSTATE_iv[2];   /* '<S128>/W-gust model' */
  boolean_T Qgustmodel_CSTATE_ob;      /* '<S128>/Q-gust model' */
  boolean_T AlphasensorLowpassFilter_CST_pj;/* '<S127>/Alpha-sensor Low-pass Filter' */
  boolean_T StickPrefilter_CSTATE_ah;  /* '<S127>/Stick Prefilter' */
  boolean_T PitchRateLeadFilter_CSTATE_p;/* '<S127>/Pitch Rate Lead Filter' */
  boolean_T Proportionalplusintegralcomp_jw;/* '<S127>/Proportional plus integral compensator' */
  boolean_T TransferFcn2_CSTATE_lp;    /* '<S131>/Transfer Fcn.2' */
  boolean_T TransferFcn1_CSTATE_je;    /* '<S131>/Transfer Fcn.1' */
  boolean_T ActuatorModel_CSTATE_fk;   /* '<S22>/Actuator Model' */
  boolean_T Wgustmodel_CSTATE_gw[2];   /* '<S133>/W-gust model' */
  boolean_T Qgustmodel_CSTATE_e;       /* '<S133>/Q-gust model' */
  boolean_T AlphasensorLowpassFilter_CSTA_d;/* '<S132>/Alpha-sensor Low-pass Filter' */
  boolean_T StickPrefilter_CSTATE_o;   /* '<S132>/Stick Prefilter' */
  boolean_T PitchRateLeadFilter_CSTATE_a;/* '<S132>/Pitch Rate Lead Filter' */
  boolean_T Proportionalplusintegralcomp_iz;/* '<S132>/Proportional plus integral compensator' */
  boolean_T TransferFcn2_CSTATE_aw;    /* '<S136>/Transfer Fcn.2' */
  boolean_T TransferFcn1_CSTATE_be;    /* '<S136>/Transfer Fcn.1' */
  boolean_T ActuatorModel_CSTATE_pq;   /* '<S23>/Actuator Model' */
  boolean_T Wgustmodel_CSTATE_c[2];    /* '<S138>/W-gust model' */
  boolean_T Qgustmodel_CSTATE_fh;      /* '<S138>/Q-gust model' */
  boolean_T AlphasensorLowpassFilter_CST_b1;/* '<S137>/Alpha-sensor Low-pass Filter' */
  boolean_T StickPrefilter_CSTATE_p2;  /* '<S137>/Stick Prefilter' */
  boolean_T PitchRateLeadFilter_CSTATE_au;/* '<S137>/Pitch Rate Lead Filter' */
  boolean_T Proportionalplusintegralcomp_nm;/* '<S137>/Proportional plus integral compensator' */
  boolean_T TransferFcn2_CSTATE_ms;    /* '<S141>/Transfer Fcn.2' */
  boolean_T TransferFcn1_CSTATE_nz;    /* '<S141>/Transfer Fcn.1' */
  boolean_T ActuatorModel_CSTATE_fb;   /* '<S24>/Actuator Model' */
  boolean_T Wgustmodel_CSTATE_h3[2];   /* '<S143>/W-gust model' */
  boolean_T Qgustmodel_CSTATE_c;       /* '<S143>/Q-gust model' */
  boolean_T AlphasensorLowpassFilter_CST_jw;/* '<S142>/Alpha-sensor Low-pass Filter' */
  boolean_T StickPrefilter_CSTATE_ns;  /* '<S142>/Stick Prefilter' */
  boolean_T PitchRateLeadFilter_CSTATE_ds;/* '<S142>/Pitch Rate Lead Filter' */
  boolean_T Proportionalplusintegralcompe_a;/* '<S142>/Proportional plus integral compensator' */
  boolean_T TransferFcn2_CSTATE_bk;    /* '<S146>/Transfer Fcn.2' */
  boolean_T TransferFcn1_CSTATE_gr;    /* '<S146>/Transfer Fcn.1' */
  boolean_T ActuatorModel_CSTATE_iv;   /* '<S25>/Actuator Model' */
  boolean_T Wgustmodel_CSTATE_b[2];    /* '<S148>/W-gust model' */
  boolean_T Qgustmodel_CSTATE_lb;      /* '<S148>/Q-gust model' */
  boolean_T AlphasensorLowpassFilter_CST_iy;/* '<S147>/Alpha-sensor Low-pass Filter' */
  boolean_T StickPrefilter_CSTATE_pb;  /* '<S147>/Stick Prefilter' */
  boolean_T PitchRateLeadFilter_CSTATE_ak;/* '<S147>/Pitch Rate Lead Filter' */
  boolean_T Proportionalplusintegralcomp_ab;/* '<S147>/Proportional plus integral compensator' */
} StateDisabled_f14tmp25;

#ifndef ODE4_INTG
#define ODE4_INTG

/* ODE4 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[4];                        /* derivatives */
} ODE4_IntgData;

#endif

/* Backward compatible GRT Identifiers */
#define rtB                            f14tmp25_B
#define BlockIO                        BlockIO_f14tmp25
#define rtX                            f14tmp25_X
#define ContinuousStates               ContinuousStates_f14tmp25
#define rtXdot                         f14tmp25_Xdot
#define StateDerivatives               StateDerivatives_f14tmp25
#define tXdis                          f14tmp25_Xdis
#define StateDisabled                  StateDisabled_f14tmp25
#define rtP                            f14tmp25_P
#define Parameters                     Parameters_f14tmp25
#define rtDWork                        f14tmp25_DWork
#define D_Work                         D_Work_f14tmp25

/* Parameters (auto storage) */
struct Parameters_f14tmp25_ {
  real_T TransferFcn2_A;               /* Computed Parameter: TransferFcn2_A
                                        * Referenced by: '<S26>/Transfer Fcn.2'
                                        */
  real_T TransferFcn2_C;               /* Computed Parameter: TransferFcn2_C
                                        * Referenced by: '<S26>/Transfer Fcn.2'
                                        */
  real_T Gain5_Gain;                   /* Expression: 1/Uo
                                        * Referenced by: '<S1>/Gain5'
                                        */
  real_T TransferFcn1_A;               /* Computed Parameter: TransferFcn1_A
                                        * Referenced by: '<S26>/Transfer Fcn.1'
                                        */
  real_T TransferFcn1_C;               /* Computed Parameter: TransferFcn1_C
                                        * Referenced by: '<S26>/Transfer Fcn.1'
                                        */
  real_T Gain1_Gain;                   /* Expression: 22.8
                                        * Referenced by: '<S29>/Gain1'
                                        */
  real_T Constant_Value;               /* Expression: Uo
                                        * Referenced by: '<S29>/Constant'
                                        */
  real_T Gain2_Gain;                   /* Expression: 1/g
                                        * Referenced by: '<S29>/Gain2'
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
                                        * Referenced by: '<S26>/Gain3'
                                        */
  real_T Gain4_Gain;                   /* Expression: Mw
                                        * Referenced by: '<S26>/Gain4'
                                        */
  real_T Gain5_Gain_j;                 /* Expression: Zd
                                        * Referenced by: '<S26>/Gain5'
                                        */
  real_T Gain6_Gain;                   /* Expression: Md
                                        * Referenced by: '<S26>/Gain6'
                                        */
  real_T Wgustmodel_A[2];              /* Computed Parameter: Wgustmodel_A
                                        * Referenced by: '<S28>/W-gust model'
                                        */
  real_T Wgustmodel_C[2];              /* Computed Parameter: Wgustmodel_C
                                        * Referenced by: '<S28>/W-gust model'
                                        */
  real_T Gain_Gain;                    /* Expression: Zw
                                        * Referenced by: '<S1>/Gain'
                                        */
  real_T Gain2_Gain_p;                 /* Expression: Mw
                                        * Referenced by: '<S1>/Gain2'
                                        */
  real_T Qgustmodel_A;                 /* Computed Parameter: Qgustmodel_A
                                        * Referenced by: '<S28>/Q-gust model'
                                        */
  real_T Qgustmodel_C;                 /* Computed Parameter: Qgustmodel_C
                                        * Referenced by: '<S28>/Q-gust model'
                                        */
  real_T Qgustmodel_D;                 /* Computed Parameter: Qgustmodel_D
                                        * Referenced by: '<S28>/Q-gust model'
                                        */
  real_T Gain1_Gain_h;                 /* Expression: Mq
                                        * Referenced by: '<S1>/Gain1'
                                        */
  real_T AlphasensorLowpassFilter_A;   /* Computed Parameter: AlphasensorLowpassFilter_A
                                        * Referenced by: '<S27>/Alpha-sensor Low-pass Filter'
                                        */
  real_T AlphasensorLowpassFilter_C;   /* Computed Parameter: AlphasensorLowpassFilter_C
                                        * Referenced by: '<S27>/Alpha-sensor Low-pass Filter'
                                        */
  real_T StickPrefilter_A;             /* Computed Parameter: StickPrefilter_A
                                        * Referenced by: '<S27>/Stick Prefilter'
                                        */
  real_T StickPrefilter_C;             /* Computed Parameter: StickPrefilter_C
                                        * Referenced by: '<S27>/Stick Prefilter'
                                        */
  real_T PitchRateLeadFilter_A;        /* Computed Parameter: PitchRateLeadFilter_A
                                        * Referenced by: '<S27>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_C;        /* Computed Parameter: PitchRateLeadFilter_C
                                        * Referenced by: '<S27>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_D;        /* Computed Parameter: PitchRateLeadFilter_D
                                        * Referenced by: '<S27>/Pitch Rate Lead Filter'
                                        */
  real_T Gain2_Gain_k;                 /* Expression: Kq
                                        * Referenced by: '<S27>/Gain2'
                                        */
  real_T Gain3_Gain_i;                 /* Expression: Ka
                                        * Referenced by: '<S27>/Gain3'
                                        */
  real_T Gain_Gain_k;                  /* Expression: Kf
                                        * Referenced by: '<S27>/Gain'
                                        */
  real_T Proportionalplusintegralcompens;/* Computed Parameter: Proportionalplusintegralcompens
                                          * Referenced by: '<S27>/Proportional plus integral compensator'
                                          */
  real_T Proportionalplusintegralcompe_i;/* Computed Parameter: Proportionalplusintegralcompe_i
                                          * Referenced by: '<S27>/Proportional plus integral compensator'
                                          */
  real_T WhiteNoise_Mean;              /* Expression: 0
                                        * Referenced by: '<S30>/White Noise'
                                        */
  real_T WhiteNoise_StdDev;            /* Computed Parameter: WhiteNoise_StdDev
                                        * Referenced by: '<S30>/White Noise'
                                        */
  real_T WhiteNoise_Seed;              /* Expression: seed
                                        * Referenced by: '<S30>/White Noise'
                                        */
  real_T Output_Gain;                  /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S30>/Output'
                                        */
  real_T TransferFcn2_A_j;             /* Computed Parameter: TransferFcn2_A_j
                                        * Referenced by: '<S31>/Transfer Fcn.2'
                                        */
  real_T TransferFcn2_C_k;             /* Computed Parameter: TransferFcn2_C_k
                                        * Referenced by: '<S31>/Transfer Fcn.2'
                                        */
  real_T Gain5_Gain_o;                 /* Expression: 1/Uo
                                        * Referenced by: '<S2>/Gain5'
                                        */
  real_T TransferFcn1_A_n;             /* Computed Parameter: TransferFcn1_A_n
                                        * Referenced by: '<S31>/Transfer Fcn.1'
                                        */
  real_T TransferFcn1_C_g;             /* Computed Parameter: TransferFcn1_C_g
                                        * Referenced by: '<S31>/Transfer Fcn.1'
                                        */
  real_T Gain1_Gain_n;                 /* Expression: 22.8
                                        * Referenced by: '<S34>/Gain1'
                                        */
  real_T Constant_Value_m;             /* Expression: Uo
                                        * Referenced by: '<S34>/Constant'
                                        */
  real_T Gain2_Gain_e;                 /* Expression: 1/g
                                        * Referenced by: '<S34>/Gain2'
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
                                        * Referenced by: '<S31>/Gain3'
                                        */
  real_T Gain4_Gain_f;                 /* Expression: Mw
                                        * Referenced by: '<S31>/Gain4'
                                        */
  real_T Gain5_Gain_g;                 /* Expression: Zd
                                        * Referenced by: '<S31>/Gain5'
                                        */
  real_T Gain6_Gain_b;                 /* Expression: Md
                                        * Referenced by: '<S31>/Gain6'
                                        */
  real_T Wgustmodel_A_l[2];            /* Computed Parameter: Wgustmodel_A_l
                                        * Referenced by: '<S33>/W-gust model'
                                        */
  real_T Wgustmodel_C_a[2];            /* Computed Parameter: Wgustmodel_C_a
                                        * Referenced by: '<S33>/W-gust model'
                                        */
  real_T Gain_Gain_l;                  /* Expression: Zw
                                        * Referenced by: '<S2>/Gain'
                                        */
  real_T Gain2_Gain_h;                 /* Expression: Mw
                                        * Referenced by: '<S2>/Gain2'
                                        */
  real_T Qgustmodel_A_e;               /* Computed Parameter: Qgustmodel_A_e
                                        * Referenced by: '<S33>/Q-gust model'
                                        */
  real_T Qgustmodel_C_p;               /* Computed Parameter: Qgustmodel_C_p
                                        * Referenced by: '<S33>/Q-gust model'
                                        */
  real_T Qgustmodel_D_c;               /* Computed Parameter: Qgustmodel_D_c
                                        * Referenced by: '<S33>/Q-gust model'
                                        */
  real_T Gain1_Gain_p;                 /* Expression: Mq
                                        * Referenced by: '<S2>/Gain1'
                                        */
  real_T AlphasensorLowpassFilter_A_d; /* Computed Parameter: AlphasensorLowpassFilter_A_d
                                        * Referenced by: '<S32>/Alpha-sensor Low-pass Filter'
                                        */
  real_T AlphasensorLowpassFilter_C_g; /* Computed Parameter: AlphasensorLowpassFilter_C_g
                                        * Referenced by: '<S32>/Alpha-sensor Low-pass Filter'
                                        */
  real_T StickPrefilter_A_c;           /* Computed Parameter: StickPrefilter_A_c
                                        * Referenced by: '<S32>/Stick Prefilter'
                                        */
  real_T StickPrefilter_C_p;           /* Computed Parameter: StickPrefilter_C_p
                                        * Referenced by: '<S32>/Stick Prefilter'
                                        */
  real_T PitchRateLeadFilter_A_c;      /* Computed Parameter: PitchRateLeadFilter_A_c
                                        * Referenced by: '<S32>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_C_l;      /* Computed Parameter: PitchRateLeadFilter_C_l
                                        * Referenced by: '<S32>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_D_f;      /* Computed Parameter: PitchRateLeadFilter_D_f
                                        * Referenced by: '<S32>/Pitch Rate Lead Filter'
                                        */
  real_T Gain2_Gain_et;                /* Expression: Kq
                                        * Referenced by: '<S32>/Gain2'
                                        */
  real_T Gain3_Gain_b;                 /* Expression: Ka
                                        * Referenced by: '<S32>/Gain3'
                                        */
  real_T Gain_Gain_a;                  /* Expression: Kf
                                        * Referenced by: '<S32>/Gain'
                                        */
  real_T Proportionalplusintegralcompe_d;/* Computed Parameter: Proportionalplusintegralcompe_d
                                          * Referenced by: '<S32>/Proportional plus integral compensator'
                                          */
  real_T Proportionalplusintegralcomp_mx;/* Computed Parameter: Proportionalplusintegralcomp_mx
                                          * Referenced by: '<S32>/Proportional plus integral compensator'
                                          */
  real_T WhiteNoise_Mean_j;            /* Expression: 0
                                        * Referenced by: '<S35>/White Noise'
                                        */
  real_T WhiteNoise_StdDev_n;          /* Computed Parameter: WhiteNoise_StdDev_n
                                        * Referenced by: '<S35>/White Noise'
                                        */
  real_T WhiteNoise_Seed_i;            /* Expression: seed
                                        * Referenced by: '<S35>/White Noise'
                                        */
  real_T Output_Gain_l;                /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S35>/Output'
                                        */
  real_T TransferFcn2_A_ju;            /* Computed Parameter: TransferFcn2_A_ju
                                        * Referenced by: '<S36>/Transfer Fcn.2'
                                        */
  real_T TransferFcn2_C_kv;            /* Computed Parameter: TransferFcn2_C_kv
                                        * Referenced by: '<S36>/Transfer Fcn.2'
                                        */
  real_T Gain5_Gain_oi;                /* Expression: 1/Uo
                                        * Referenced by: '<S3>/Gain5'
                                        */
  real_T TransferFcn1_A_j;             /* Computed Parameter: TransferFcn1_A_j
                                        * Referenced by: '<S36>/Transfer Fcn.1'
                                        */
  real_T TransferFcn1_C_m;             /* Computed Parameter: TransferFcn1_C_m
                                        * Referenced by: '<S36>/Transfer Fcn.1'
                                        */
  real_T Gain1_Gain_m;                 /* Expression: 22.8
                                        * Referenced by: '<S39>/Gain1'
                                        */
  real_T Constant_Value_f;             /* Expression: Uo
                                        * Referenced by: '<S39>/Constant'
                                        */
  real_T Gain2_Gain_k5;                /* Expression: 1/g
                                        * Referenced by: '<S39>/Gain2'
                                        */
  real_T Pilot_Amplitude_c;            /* Expression: 1
                                        * Referenced by: '<S3>/Pilot'
                                        */
  real_T Pilot_Frequency_g;            /* Computed Parameter: Pilot_Frequency_g
                                        * Referenced by: '<S3>/Pilot'
                                        */
  real_T ActuatorModel_A_g;            /* Computed Parameter: ActuatorModel_A_g
                                        * Referenced by: '<S3>/Actuator Model'
                                        */
  real_T ActuatorModel_C_d;            /* Computed Parameter: ActuatorModel_C_d
                                        * Referenced by: '<S3>/Actuator Model'
                                        */
  real_T Gain3_Gain_iq;                /* Expression: Uo
                                        * Referenced by: '<S36>/Gain3'
                                        */
  real_T Gain4_Gain_fx;                /* Expression: Mw
                                        * Referenced by: '<S36>/Gain4'
                                        */
  real_T Gain5_Gain_ot;                /* Expression: Zd
                                        * Referenced by: '<S36>/Gain5'
                                        */
  real_T Gain6_Gain_d;                 /* Expression: Md
                                        * Referenced by: '<S36>/Gain6'
                                        */
  real_T Wgustmodel_A_a[2];            /* Computed Parameter: Wgustmodel_A_a
                                        * Referenced by: '<S38>/W-gust model'
                                        */
  real_T Wgustmodel_C_e[2];            /* Computed Parameter: Wgustmodel_C_e
                                        * Referenced by: '<S38>/W-gust model'
                                        */
  real_T Gain_Gain_c;                  /* Expression: Zw
                                        * Referenced by: '<S3>/Gain'
                                        */
  real_T Gain2_Gain_c;                 /* Expression: Mw
                                        * Referenced by: '<S3>/Gain2'
                                        */
  real_T Qgustmodel_A_m;               /* Computed Parameter: Qgustmodel_A_m
                                        * Referenced by: '<S38>/Q-gust model'
                                        */
  real_T Qgustmodel_C_e;               /* Computed Parameter: Qgustmodel_C_e
                                        * Referenced by: '<S38>/Q-gust model'
                                        */
  real_T Qgustmodel_D_n;               /* Computed Parameter: Qgustmodel_D_n
                                        * Referenced by: '<S38>/Q-gust model'
                                        */
  real_T Gain1_Gain_d;                 /* Expression: Mq
                                        * Referenced by: '<S3>/Gain1'
                                        */
  real_T AlphasensorLowpassFilter_A_b; /* Computed Parameter: AlphasensorLowpassFilter_A_b
                                        * Referenced by: '<S37>/Alpha-sensor Low-pass Filter'
                                        */
  real_T AlphasensorLowpassFilter_C_c; /* Computed Parameter: AlphasensorLowpassFilter_C_c
                                        * Referenced by: '<S37>/Alpha-sensor Low-pass Filter'
                                        */
  real_T StickPrefilter_A_g;           /* Computed Parameter: StickPrefilter_A_g
                                        * Referenced by: '<S37>/Stick Prefilter'
                                        */
  real_T StickPrefilter_C_f;           /* Computed Parameter: StickPrefilter_C_f
                                        * Referenced by: '<S37>/Stick Prefilter'
                                        */
  real_T PitchRateLeadFilter_A_g;      /* Computed Parameter: PitchRateLeadFilter_A_g
                                        * Referenced by: '<S37>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_C_b;      /* Computed Parameter: PitchRateLeadFilter_C_b
                                        * Referenced by: '<S37>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_D_i;      /* Computed Parameter: PitchRateLeadFilter_D_i
                                        * Referenced by: '<S37>/Pitch Rate Lead Filter'
                                        */
  real_T Gain2_Gain_d;                 /* Expression: Kq
                                        * Referenced by: '<S37>/Gain2'
                                        */
  real_T Gain3_Gain_a;                 /* Expression: Ka
                                        * Referenced by: '<S37>/Gain3'
                                        */
  real_T Gain_Gain_j;                  /* Expression: Kf
                                        * Referenced by: '<S37>/Gain'
                                        */
  real_T Proportionalplusintegralcompe_f;/* Computed Parameter: Proportionalplusintegralcompe_f
                                          * Referenced by: '<S37>/Proportional plus integral compensator'
                                          */
  real_T Proportionalplusintegralcomp_kq;/* Computed Parameter: Proportionalplusintegralcomp_kq
                                          * Referenced by: '<S37>/Proportional plus integral compensator'
                                          */
  real_T WhiteNoise_Mean_n;            /* Expression: 0
                                        * Referenced by: '<S40>/White Noise'
                                        */
  real_T WhiteNoise_StdDev_e;          /* Computed Parameter: WhiteNoise_StdDev_e
                                        * Referenced by: '<S40>/White Noise'
                                        */
  real_T WhiteNoise_Seed_g;            /* Expression: seed
                                        * Referenced by: '<S40>/White Noise'
                                        */
  real_T Output_Gain_m;                /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S40>/Output'
                                        */
  real_T TransferFcn2_A_i;             /* Computed Parameter: TransferFcn2_A_i
                                        * Referenced by: '<S41>/Transfer Fcn.2'
                                        */
  real_T TransferFcn2_C_g;             /* Computed Parameter: TransferFcn2_C_g
                                        * Referenced by: '<S41>/Transfer Fcn.2'
                                        */
  real_T Gain5_Gain_p;                 /* Expression: 1/Uo
                                        * Referenced by: '<S4>/Gain5'
                                        */
  real_T TransferFcn1_A_d;             /* Computed Parameter: TransferFcn1_A_d
                                        * Referenced by: '<S41>/Transfer Fcn.1'
                                        */
  real_T TransferFcn1_C_mz;            /* Computed Parameter: TransferFcn1_C_mz
                                        * Referenced by: '<S41>/Transfer Fcn.1'
                                        */
  real_T Gain1_Gain_pr;                /* Expression: 22.8
                                        * Referenced by: '<S44>/Gain1'
                                        */
  real_T Constant_Value_fk;            /* Expression: Uo
                                        * Referenced by: '<S44>/Constant'
                                        */
  real_T Gain2_Gain_n;                 /* Expression: 1/g
                                        * Referenced by: '<S44>/Gain2'
                                        */
  real_T Pilot_Amplitude_j;            /* Expression: 1
                                        * Referenced by: '<S4>/Pilot'
                                        */
  real_T Pilot_Frequency_i;            /* Computed Parameter: Pilot_Frequency_i
                                        * Referenced by: '<S4>/Pilot'
                                        */
  real_T ActuatorModel_A_f;            /* Computed Parameter: ActuatorModel_A_f
                                        * Referenced by: '<S4>/Actuator Model'
                                        */
  real_T ActuatorModel_C_ft;           /* Computed Parameter: ActuatorModel_C_ft
                                        * Referenced by: '<S4>/Actuator Model'
                                        */
  real_T Gain3_Gain_p;                 /* Expression: Uo
                                        * Referenced by: '<S41>/Gain3'
                                        */
  real_T Gain4_Gain_p;                 /* Expression: Mw
                                        * Referenced by: '<S41>/Gain4'
                                        */
  real_T Gain5_Gain_f;                 /* Expression: Zd
                                        * Referenced by: '<S41>/Gain5'
                                        */
  real_T Gain6_Gain_a;                 /* Expression: Md
                                        * Referenced by: '<S41>/Gain6'
                                        */
  real_T Wgustmodel_A_l4[2];           /* Computed Parameter: Wgustmodel_A_l4
                                        * Referenced by: '<S43>/W-gust model'
                                        */
  real_T Wgustmodel_C_d[2];            /* Computed Parameter: Wgustmodel_C_d
                                        * Referenced by: '<S43>/W-gust model'
                                        */
  real_T Gain_Gain_i;                  /* Expression: Zw
                                        * Referenced by: '<S4>/Gain'
                                        */
  real_T Gain2_Gain_cm;                /* Expression: Mw
                                        * Referenced by: '<S4>/Gain2'
                                        */
  real_T Qgustmodel_A_g;               /* Computed Parameter: Qgustmodel_A_g
                                        * Referenced by: '<S43>/Q-gust model'
                                        */
  real_T Qgustmodel_C_j;               /* Computed Parameter: Qgustmodel_C_j
                                        * Referenced by: '<S43>/Q-gust model'
                                        */
  real_T Qgustmodel_D_d;               /* Computed Parameter: Qgustmodel_D_d
                                        * Referenced by: '<S43>/Q-gust model'
                                        */
  real_T Gain1_Gain_j;                 /* Expression: Mq
                                        * Referenced by: '<S4>/Gain1'
                                        */
  real_T AlphasensorLowpassFilter_A_bn;/* Computed Parameter: AlphasensorLowpassFilter_A_bn
                                        * Referenced by: '<S42>/Alpha-sensor Low-pass Filter'
                                        */
  real_T AlphasensorLowpassFilter_C_d; /* Computed Parameter: AlphasensorLowpassFilter_C_d
                                        * Referenced by: '<S42>/Alpha-sensor Low-pass Filter'
                                        */
  real_T StickPrefilter_A_i;           /* Computed Parameter: StickPrefilter_A_i
                                        * Referenced by: '<S42>/Stick Prefilter'
                                        */
  real_T StickPrefilter_C_m;           /* Computed Parameter: StickPrefilter_C_m
                                        * Referenced by: '<S42>/Stick Prefilter'
                                        */
  real_T PitchRateLeadFilter_A_o;      /* Computed Parameter: PitchRateLeadFilter_A_o
                                        * Referenced by: '<S42>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_C_n;      /* Computed Parameter: PitchRateLeadFilter_C_n
                                        * Referenced by: '<S42>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_D_j;      /* Computed Parameter: PitchRateLeadFilter_D_j
                                        * Referenced by: '<S42>/Pitch Rate Lead Filter'
                                        */
  real_T Gain2_Gain_hu;                /* Expression: Kq
                                        * Referenced by: '<S42>/Gain2'
                                        */
  real_T Gain3_Gain_g;                 /* Expression: Ka
                                        * Referenced by: '<S42>/Gain3'
                                        */
  real_T Gain_Gain_m;                  /* Expression: Kf
                                        * Referenced by: '<S42>/Gain'
                                        */
  real_T Proportionalplusintegralcompe_h;/* Computed Parameter: Proportionalplusintegralcompe_h
                                          * Referenced by: '<S42>/Proportional plus integral compensator'
                                          */
  real_T Proportionalplusintegralcompe_n;/* Computed Parameter: Proportionalplusintegralcompe_n
                                          * Referenced by: '<S42>/Proportional plus integral compensator'
                                          */
  real_T WhiteNoise_Mean_c;            /* Expression: 0
                                        * Referenced by: '<S45>/White Noise'
                                        */
  real_T WhiteNoise_StdDev_l;          /* Computed Parameter: WhiteNoise_StdDev_l
                                        * Referenced by: '<S45>/White Noise'
                                        */
  real_T WhiteNoise_Seed_e;            /* Expression: seed
                                        * Referenced by: '<S45>/White Noise'
                                        */
  real_T Output_Gain_c;                /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S45>/Output'
                                        */
  real_T TransferFcn2_A_k;             /* Computed Parameter: TransferFcn2_A_k
                                        * Referenced by: '<S46>/Transfer Fcn.2'
                                        */
  real_T TransferFcn2_C_l;             /* Computed Parameter: TransferFcn2_C_l
                                        * Referenced by: '<S46>/Transfer Fcn.2'
                                        */
  real_T Gain5_Gain_n;                 /* Expression: 1/Uo
                                        * Referenced by: '<S5>/Gain5'
                                        */
  real_T TransferFcn1_A_o;             /* Computed Parameter: TransferFcn1_A_o
                                        * Referenced by: '<S46>/Transfer Fcn.1'
                                        */
  real_T TransferFcn1_C_gz;            /* Computed Parameter: TransferFcn1_C_gz
                                        * Referenced by: '<S46>/Transfer Fcn.1'
                                        */
  real_T Gain1_Gain_m3;                /* Expression: 22.8
                                        * Referenced by: '<S49>/Gain1'
                                        */
  real_T Constant_Value_i;             /* Expression: Uo
                                        * Referenced by: '<S49>/Constant'
                                        */
  real_T Gain2_Gain_m;                 /* Expression: 1/g
                                        * Referenced by: '<S49>/Gain2'
                                        */
  real_T Pilot_Amplitude_nq;           /* Expression: 1
                                        * Referenced by: '<S5>/Pilot'
                                        */
  real_T Pilot_Frequency_b;            /* Computed Parameter: Pilot_Frequency_b
                                        * Referenced by: '<S5>/Pilot'
                                        */
  real_T ActuatorModel_A_gl;           /* Computed Parameter: ActuatorModel_A_gl
                                        * Referenced by: '<S5>/Actuator Model'
                                        */
  real_T ActuatorModel_C_da;           /* Computed Parameter: ActuatorModel_C_da
                                        * Referenced by: '<S5>/Actuator Model'
                                        */
  real_T Gain3_Gain_e;                 /* Expression: Uo
                                        * Referenced by: '<S46>/Gain3'
                                        */
  real_T Gain4_Gain_i;                 /* Expression: Mw
                                        * Referenced by: '<S46>/Gain4'
                                        */
  real_T Gain5_Gain_m;                 /* Expression: Zd
                                        * Referenced by: '<S46>/Gain5'
                                        */
  real_T Gain6_Gain_n;                 /* Expression: Md
                                        * Referenced by: '<S46>/Gain6'
                                        */
  real_T Wgustmodel_A_d[2];            /* Computed Parameter: Wgustmodel_A_d
                                        * Referenced by: '<S48>/W-gust model'
                                        */
  real_T Wgustmodel_C_eb[2];           /* Computed Parameter: Wgustmodel_C_eb
                                        * Referenced by: '<S48>/W-gust model'
                                        */
  real_T Gain_Gain_o;                  /* Expression: Zw
                                        * Referenced by: '<S5>/Gain'
                                        */
  real_T Gain2_Gain_ck;                /* Expression: Mw
                                        * Referenced by: '<S5>/Gain2'
                                        */
  real_T Qgustmodel_A_i;               /* Computed Parameter: Qgustmodel_A_i
                                        * Referenced by: '<S48>/Q-gust model'
                                        */
  real_T Qgustmodel_C_f;               /* Computed Parameter: Qgustmodel_C_f
                                        * Referenced by: '<S48>/Q-gust model'
                                        */
  real_T Qgustmodel_D_p;               /* Computed Parameter: Qgustmodel_D_p
                                        * Referenced by: '<S48>/Q-gust model'
                                        */
  real_T Gain1_Gain_o;                 /* Expression: Mq
                                        * Referenced by: '<S5>/Gain1'
                                        */
  real_T AlphasensorLowpassFilter_A_g; /* Computed Parameter: AlphasensorLowpassFilter_A_g
                                        * Referenced by: '<S47>/Alpha-sensor Low-pass Filter'
                                        */
  real_T AlphasensorLowpassFilter_C_n; /* Computed Parameter: AlphasensorLowpassFilter_C_n
                                        * Referenced by: '<S47>/Alpha-sensor Low-pass Filter'
                                        */
  real_T StickPrefilter_A_co;          /* Computed Parameter: StickPrefilter_A_co
                                        * Referenced by: '<S47>/Stick Prefilter'
                                        */
  real_T StickPrefilter_C_fv;          /* Computed Parameter: StickPrefilter_C_fv
                                        * Referenced by: '<S47>/Stick Prefilter'
                                        */
  real_T PitchRateLeadFilter_A_p;      /* Computed Parameter: PitchRateLeadFilter_A_p
                                        * Referenced by: '<S47>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_C_k;      /* Computed Parameter: PitchRateLeadFilter_C_k
                                        * Referenced by: '<S47>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_D_c;      /* Computed Parameter: PitchRateLeadFilter_D_c
                                        * Referenced by: '<S47>/Pitch Rate Lead Filter'
                                        */
  real_T Gain2_Gain_hw;                /* Expression: Kq
                                        * Referenced by: '<S47>/Gain2'
                                        */
  real_T Gain3_Gain_c;                 /* Expression: Ka
                                        * Referenced by: '<S47>/Gain3'
                                        */
  real_T Gain_Gain_m0;                 /* Expression: Kf
                                        * Referenced by: '<S47>/Gain'
                                        */
  real_T Proportionalplusintegralcomp_kf;/* Computed Parameter: Proportionalplusintegralcomp_kf
                                          * Referenced by: '<S47>/Proportional plus integral compensator'
                                          */
  real_T Proportionalplusintegralcomp_nt;/* Computed Parameter: Proportionalplusintegralcomp_nt
                                          * Referenced by: '<S47>/Proportional plus integral compensator'
                                          */
  real_T WhiteNoise_Mean_h;            /* Expression: 0
                                        * Referenced by: '<S50>/White Noise'
                                        */
  real_T WhiteNoise_StdDev_k;          /* Computed Parameter: WhiteNoise_StdDev_k
                                        * Referenced by: '<S50>/White Noise'
                                        */
  real_T WhiteNoise_Seed_p;            /* Expression: seed
                                        * Referenced by: '<S50>/White Noise'
                                        */
  real_T Output_Gain_k;                /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S50>/Output'
                                        */
  real_T TransferFcn2_A_f;             /* Computed Parameter: TransferFcn2_A_f
                                        * Referenced by: '<S51>/Transfer Fcn.2'
                                        */
  real_T TransferFcn2_C_i;             /* Computed Parameter: TransferFcn2_C_i
                                        * Referenced by: '<S51>/Transfer Fcn.2'
                                        */
  real_T Gain5_Gain_b;                 /* Expression: 1/Uo
                                        * Referenced by: '<S6>/Gain5'
                                        */
  real_T TransferFcn1_A_m;             /* Computed Parameter: TransferFcn1_A_m
                                        * Referenced by: '<S51>/Transfer Fcn.1'
                                        */
  real_T TransferFcn1_C_g3;            /* Computed Parameter: TransferFcn1_C_g3
                                        * Referenced by: '<S51>/Transfer Fcn.1'
                                        */
  real_T Gain1_Gain_e;                 /* Expression: 22.8
                                        * Referenced by: '<S54>/Gain1'
                                        */
  real_T Constant_Value_h;             /* Expression: Uo
                                        * Referenced by: '<S54>/Constant'
                                        */
  real_T Gain2_Gain_f;                 /* Expression: 1/g
                                        * Referenced by: '<S54>/Gain2'
                                        */
  real_T Pilot_Amplitude_d;            /* Expression: 1
                                        * Referenced by: '<S6>/Pilot'
                                        */
  real_T Pilot_Frequency_i2;           /* Computed Parameter: Pilot_Frequency_i2
                                        * Referenced by: '<S6>/Pilot'
                                        */
  real_T ActuatorModel_A_p;            /* Computed Parameter: ActuatorModel_A_p
                                        * Referenced by: '<S6>/Actuator Model'
                                        */
  real_T ActuatorModel_C_b;            /* Computed Parameter: ActuatorModel_C_b
                                        * Referenced by: '<S6>/Actuator Model'
                                        */
  real_T Gain3_Gain_j;                 /* Expression: Uo
                                        * Referenced by: '<S51>/Gain3'
                                        */
  real_T Gain4_Gain_c;                 /* Expression: Mw
                                        * Referenced by: '<S51>/Gain4'
                                        */
  real_T Gain5_Gain_h;                 /* Expression: Zd
                                        * Referenced by: '<S51>/Gain5'
                                        */
  real_T Gain6_Gain_a2;                /* Expression: Md
                                        * Referenced by: '<S51>/Gain6'
                                        */
  real_T Wgustmodel_A_g[2];            /* Computed Parameter: Wgustmodel_A_g
                                        * Referenced by: '<S53>/W-gust model'
                                        */
  real_T Wgustmodel_C_c[2];            /* Computed Parameter: Wgustmodel_C_c
                                        * Referenced by: '<S53>/W-gust model'
                                        */
  real_T Gain_Gain_m1;                 /* Expression: Zw
                                        * Referenced by: '<S6>/Gain'
                                        */
  real_T Gain2_Gain_a;                 /* Expression: Mw
                                        * Referenced by: '<S6>/Gain2'
                                        */
  real_T Qgustmodel_A_o;               /* Computed Parameter: Qgustmodel_A_o
                                        * Referenced by: '<S53>/Q-gust model'
                                        */
  real_T Qgustmodel_C_k;               /* Computed Parameter: Qgustmodel_C_k
                                        * Referenced by: '<S53>/Q-gust model'
                                        */
  real_T Qgustmodel_D_nw;              /* Computed Parameter: Qgustmodel_D_nw
                                        * Referenced by: '<S53>/Q-gust model'
                                        */
  real_T Gain1_Gain_nf;                /* Expression: Mq
                                        * Referenced by: '<S6>/Gain1'
                                        */
  real_T AlphasensorLowpassFilter_A_i; /* Computed Parameter: AlphasensorLowpassFilter_A_i
                                        * Referenced by: '<S52>/Alpha-sensor Low-pass Filter'
                                        */
  real_T AlphasensorLowpassFilter_C_e; /* Computed Parameter: AlphasensorLowpassFilter_C_e
                                        * Referenced by: '<S52>/Alpha-sensor Low-pass Filter'
                                        */
  real_T StickPrefilter_A_cj;          /* Computed Parameter: StickPrefilter_A_cj
                                        * Referenced by: '<S52>/Stick Prefilter'
                                        */
  real_T StickPrefilter_C_fd;          /* Computed Parameter: StickPrefilter_C_fd
                                        * Referenced by: '<S52>/Stick Prefilter'
                                        */
  real_T PitchRateLeadFilter_A_d;      /* Computed Parameter: PitchRateLeadFilter_A_d
                                        * Referenced by: '<S52>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_C_e;      /* Computed Parameter: PitchRateLeadFilter_C_e
                                        * Referenced by: '<S52>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_D_o;      /* Computed Parameter: PitchRateLeadFilter_D_o
                                        * Referenced by: '<S52>/Pitch Rate Lead Filter'
                                        */
  real_T Gain2_Gain_g;                 /* Expression: Kq
                                        * Referenced by: '<S52>/Gain2'
                                        */
  real_T Gain3_Gain_j4;                /* Expression: Ka
                                        * Referenced by: '<S52>/Gain3'
                                        */
  real_T Gain_Gain_h;                  /* Expression: Kf
                                        * Referenced by: '<S52>/Gain'
                                        */
  real_T Proportionalplusintegralcomp_hd;/* Computed Parameter: Proportionalplusintegralcomp_hd
                                          * Referenced by: '<S52>/Proportional plus integral compensator'
                                          */
  real_T Proportionalplusintegralcomp_il;/* Computed Parameter: Proportionalplusintegralcomp_il
                                          * Referenced by: '<S52>/Proportional plus integral compensator'
                                          */
  real_T WhiteNoise_Mean_hl;           /* Expression: 0
                                        * Referenced by: '<S55>/White Noise'
                                        */
  real_T WhiteNoise_StdDev_p;          /* Computed Parameter: WhiteNoise_StdDev_p
                                        * Referenced by: '<S55>/White Noise'
                                        */
  real_T WhiteNoise_Seed_b;            /* Expression: seed
                                        * Referenced by: '<S55>/White Noise'
                                        */
  real_T Output_Gain_lv;               /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S55>/Output'
                                        */
  real_T TransferFcn2_A_iu;            /* Computed Parameter: TransferFcn2_A_iu
                                        * Referenced by: '<S56>/Transfer Fcn.2'
                                        */
  real_T TransferFcn2_C_j;             /* Computed Parameter: TransferFcn2_C_j
                                        * Referenced by: '<S56>/Transfer Fcn.2'
                                        */
  real_T Gain5_Gain_c;                 /* Expression: 1/Uo
                                        * Referenced by: '<S7>/Gain5'
                                        */
  real_T TransferFcn1_A_h;             /* Computed Parameter: TransferFcn1_A_h
                                        * Referenced by: '<S56>/Transfer Fcn.1'
                                        */
  real_T TransferFcn1_C_n;             /* Computed Parameter: TransferFcn1_C_n
                                        * Referenced by: '<S56>/Transfer Fcn.1'
                                        */
  real_T Gain1_Gain_g;                 /* Expression: 22.8
                                        * Referenced by: '<S59>/Gain1'
                                        */
  real_T Constant_Value_hc;            /* Expression: Uo
                                        * Referenced by: '<S59>/Constant'
                                        */
  real_T Gain2_Gain_b;                 /* Expression: 1/g
                                        * Referenced by: '<S59>/Gain2'
                                        */
  real_T Pilot_Amplitude_j5;           /* Expression: 1
                                        * Referenced by: '<S7>/Pilot'
                                        */
  real_T Pilot_Frequency_bf;           /* Computed Parameter: Pilot_Frequency_bf
                                        * Referenced by: '<S7>/Pilot'
                                        */
  real_T ActuatorModel_A_o;            /* Computed Parameter: ActuatorModel_A_o
                                        * Referenced by: '<S7>/Actuator Model'
                                        */
  real_T ActuatorModel_C_k;            /* Computed Parameter: ActuatorModel_C_k
                                        * Referenced by: '<S7>/Actuator Model'
                                        */
  real_T Gain3_Gain_pa;                /* Expression: Uo
                                        * Referenced by: '<S56>/Gain3'
                                        */
  real_T Gain4_Gain_b;                 /* Expression: Mw
                                        * Referenced by: '<S56>/Gain4'
                                        */
  real_T Gain5_Gain_pl;                /* Expression: Zd
                                        * Referenced by: '<S56>/Gain5'
                                        */
  real_T Gain6_Gain_i;                 /* Expression: Md
                                        * Referenced by: '<S56>/Gain6'
                                        */
  real_T Wgustmodel_A_k[2];            /* Computed Parameter: Wgustmodel_A_k
                                        * Referenced by: '<S58>/W-gust model'
                                        */
  real_T Wgustmodel_C_m[2];            /* Computed Parameter: Wgustmodel_C_m
                                        * Referenced by: '<S58>/W-gust model'
                                        */
  real_T Gain_Gain_b;                  /* Expression: Zw
                                        * Referenced by: '<S7>/Gain'
                                        */
  real_T Gain2_Gain_ej;                /* Expression: Mw
                                        * Referenced by: '<S7>/Gain2'
                                        */
  real_T Qgustmodel_A_c;               /* Computed Parameter: Qgustmodel_A_c
                                        * Referenced by: '<S58>/Q-gust model'
                                        */
  real_T Qgustmodel_C_n;               /* Computed Parameter: Qgustmodel_C_n
                                        * Referenced by: '<S58>/Q-gust model'
                                        */
  real_T Qgustmodel_D_b;               /* Computed Parameter: Qgustmodel_D_b
                                        * Referenced by: '<S58>/Q-gust model'
                                        */
  real_T Gain1_Gain_mf;                /* Expression: Mq
                                        * Referenced by: '<S7>/Gain1'
                                        */
  real_T AlphasensorLowpassFilter_A_h; /* Computed Parameter: AlphasensorLowpassFilter_A_h
                                        * Referenced by: '<S57>/Alpha-sensor Low-pass Filter'
                                        */
  real_T AlphasensorLowpassFilter_C_f; /* Computed Parameter: AlphasensorLowpassFilter_C_f
                                        * Referenced by: '<S57>/Alpha-sensor Low-pass Filter'
                                        */
  real_T StickPrefilter_A_d;           /* Computed Parameter: StickPrefilter_A_d
                                        * Referenced by: '<S57>/Stick Prefilter'
                                        */
  real_T StickPrefilter_C_j;           /* Computed Parameter: StickPrefilter_C_j
                                        * Referenced by: '<S57>/Stick Prefilter'
                                        */
  real_T PitchRateLeadFilter_A_a;      /* Computed Parameter: PitchRateLeadFilter_A_a
                                        * Referenced by: '<S57>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_C_ls;     /* Computed Parameter: PitchRateLeadFilter_C_ls
                                        * Referenced by: '<S57>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_D_b;      /* Computed Parameter: PitchRateLeadFilter_D_b
                                        * Referenced by: '<S57>/Pitch Rate Lead Filter'
                                        */
  real_T Gain2_Gain_i;                 /* Expression: Kq
                                        * Referenced by: '<S57>/Gain2'
                                        */
  real_T Gain3_Gain_f;                 /* Expression: Ka
                                        * Referenced by: '<S57>/Gain3'
                                        */
  real_T Gain_Gain_be;                 /* Expression: Kf
                                        * Referenced by: '<S57>/Gain'
                                        */
  real_T Proportionalplusintegralcomp_n4;/* Computed Parameter: Proportionalplusintegralcomp_n4
                                          * Referenced by: '<S57>/Proportional plus integral compensator'
                                          */
  real_T Proportionalplusintegralcomp_aj;/* Computed Parameter: Proportionalplusintegralcomp_aj
                                          * Referenced by: '<S57>/Proportional plus integral compensator'
                                          */
  real_T WhiteNoise_Mean_l;            /* Expression: 0
                                        * Referenced by: '<S60>/White Noise'
                                        */
  real_T WhiteNoise_StdDev_i;          /* Computed Parameter: WhiteNoise_StdDev_i
                                        * Referenced by: '<S60>/White Noise'
                                        */
  real_T WhiteNoise_Seed_gf;           /* Expression: seed
                                        * Referenced by: '<S60>/White Noise'
                                        */
  real_T Output_Gain_d;                /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S60>/Output'
                                        */
  real_T TransferFcn2_A_g;             /* Computed Parameter: TransferFcn2_A_g
                                        * Referenced by: '<S61>/Transfer Fcn.2'
                                        */
  real_T TransferFcn2_C_l3;            /* Computed Parameter: TransferFcn2_C_l3
                                        * Referenced by: '<S61>/Transfer Fcn.2'
                                        */
  real_T Gain5_Gain_mp;                /* Expression: 1/Uo
                                        * Referenced by: '<S8>/Gain5'
                                        */
  real_T TransferFcn1_A_nv;            /* Computed Parameter: TransferFcn1_A_nv
                                        * Referenced by: '<S61>/Transfer Fcn.1'
                                        */
  real_T TransferFcn1_C_j;             /* Computed Parameter: TransferFcn1_C_j
                                        * Referenced by: '<S61>/Transfer Fcn.1'
                                        */
  real_T Gain1_Gain_a;                 /* Expression: 22.8
                                        * Referenced by: '<S64>/Gain1'
                                        */
  real_T Constant_Value_g;             /* Expression: Uo
                                        * Referenced by: '<S64>/Constant'
                                        */
  real_T Gain2_Gain_b3;                /* Expression: 1/g
                                        * Referenced by: '<S64>/Gain2'
                                        */
  real_T Pilot_Amplitude_i;            /* Expression: 1
                                        * Referenced by: '<S8>/Pilot'
                                        */
  real_T Pilot_Frequency_e;            /* Computed Parameter: Pilot_Frequency_e
                                        * Referenced by: '<S8>/Pilot'
                                        */
  real_T ActuatorModel_A_k;            /* Computed Parameter: ActuatorModel_A_k
                                        * Referenced by: '<S8>/Actuator Model'
                                        */
  real_T ActuatorModel_C_by;           /* Computed Parameter: ActuatorModel_C_by
                                        * Referenced by: '<S8>/Actuator Model'
                                        */
  real_T Gain3_Gain_o;                 /* Expression: Uo
                                        * Referenced by: '<S61>/Gain3'
                                        */
  real_T Gain4_Gain_h;                 /* Expression: Mw
                                        * Referenced by: '<S61>/Gain4'
                                        */
  real_T Gain5_Gain_jk;                /* Expression: Zd
                                        * Referenced by: '<S61>/Gain5'
                                        */
  real_T Gain6_Gain_c;                 /* Expression: Md
                                        * Referenced by: '<S61>/Gain6'
                                        */
  real_T Wgustmodel_A_h[2];            /* Computed Parameter: Wgustmodel_A_h
                                        * Referenced by: '<S63>/W-gust model'
                                        */
  real_T Wgustmodel_C_i[2];            /* Computed Parameter: Wgustmodel_C_i
                                        * Referenced by: '<S63>/W-gust model'
                                        */
  real_T Gain_Gain_ka;                 /* Expression: Zw
                                        * Referenced by: '<S8>/Gain'
                                        */
  real_T Gain2_Gain_k5j;               /* Expression: Mw
                                        * Referenced by: '<S8>/Gain2'
                                        */
  real_T Qgustmodel_A_k;               /* Computed Parameter: Qgustmodel_A_k
                                        * Referenced by: '<S63>/Q-gust model'
                                        */
  real_T Qgustmodel_C_o;               /* Computed Parameter: Qgustmodel_C_o
                                        * Referenced by: '<S63>/Q-gust model'
                                        */
  real_T Qgustmodel_D_h;               /* Computed Parameter: Qgustmodel_D_h
                                        * Referenced by: '<S63>/Q-gust model'
                                        */
  real_T Gain1_Gain_gg;                /* Expression: Mq
                                        * Referenced by: '<S8>/Gain1'
                                        */
  real_T AlphasensorLowpassFilter_A_p; /* Computed Parameter: AlphasensorLowpassFilter_A_p
                                        * Referenced by: '<S62>/Alpha-sensor Low-pass Filter'
                                        */
  real_T AlphasensorLowpassFilter_C_dk;/* Computed Parameter: AlphasensorLowpassFilter_C_dk
                                        * Referenced by: '<S62>/Alpha-sensor Low-pass Filter'
                                        */
  real_T StickPrefilter_A_cf;          /* Computed Parameter: StickPrefilter_A_cf
                                        * Referenced by: '<S62>/Stick Prefilter'
                                        */
  real_T StickPrefilter_C_jx;          /* Computed Parameter: StickPrefilter_C_jx
                                        * Referenced by: '<S62>/Stick Prefilter'
                                        */
  real_T PitchRateLeadFilter_A_n;      /* Computed Parameter: PitchRateLeadFilter_A_n
                                        * Referenced by: '<S62>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_C_h;      /* Computed Parameter: PitchRateLeadFilter_C_h
                                        * Referenced by: '<S62>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_D_fn;     /* Computed Parameter: PitchRateLeadFilter_D_fn
                                        * Referenced by: '<S62>/Pitch Rate Lead Filter'
                                        */
  real_T Gain2_Gain_i1;                /* Expression: Kq
                                        * Referenced by: '<S62>/Gain2'
                                        */
  real_T Gain3_Gain_jo;                /* Expression: Ka
                                        * Referenced by: '<S62>/Gain3'
                                        */
  real_T Gain_Gain_jp;                 /* Expression: Kf
                                        * Referenced by: '<S62>/Gain'
                                        */
  real_T Proportionalplusintegralcomp_pa;/* Computed Parameter: Proportionalplusintegralcomp_pa
                                          * Referenced by: '<S62>/Proportional plus integral compensator'
                                          */
  real_T Proportionalplusintegralcomp_db;/* Computed Parameter: Proportionalplusintegralcomp_db
                                          * Referenced by: '<S62>/Proportional plus integral compensator'
                                          */
  real_T WhiteNoise_Mean_no;           /* Expression: 0
                                        * Referenced by: '<S65>/White Noise'
                                        */
  real_T WhiteNoise_StdDev_h;          /* Computed Parameter: WhiteNoise_StdDev_h
                                        * Referenced by: '<S65>/White Noise'
                                        */
  real_T WhiteNoise_Seed_c;            /* Expression: seed
                                        * Referenced by: '<S65>/White Noise'
                                        */
  real_T Output_Gain_kp;               /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S65>/Output'
                                        */
  real_T TransferFcn2_A_h;             /* Computed Parameter: TransferFcn2_A_h
                                        * Referenced by: '<S66>/Transfer Fcn.2'
                                        */
  real_T TransferFcn2_C_n;             /* Computed Parameter: TransferFcn2_C_n
                                        * Referenced by: '<S66>/Transfer Fcn.2'
                                        */
  real_T Gain5_Gain_oy;                /* Expression: 1/Uo
                                        * Referenced by: '<S9>/Gain5'
                                        */
  real_T TransferFcn1_A_b;             /* Computed Parameter: TransferFcn1_A_b
                                        * Referenced by: '<S66>/Transfer Fcn.1'
                                        */
  real_T TransferFcn1_C_gzf;           /* Computed Parameter: TransferFcn1_C_gzf
                                        * Referenced by: '<S66>/Transfer Fcn.1'
                                        */
  real_T Gain1_Gain_m2;                /* Expression: 22.8
                                        * Referenced by: '<S69>/Gain1'
                                        */
  real_T Constant_Value_b;             /* Expression: Uo
                                        * Referenced by: '<S69>/Constant'
                                        */
  real_T Gain2_Gain_d5;                /* Expression: 1/g
                                        * Referenced by: '<S69>/Gain2'
                                        */
  real_T Pilot_Amplitude_o;            /* Expression: 1
                                        * Referenced by: '<S9>/Pilot'
                                        */
  real_T Pilot_Frequency_bw;           /* Computed Parameter: Pilot_Frequency_bw
                                        * Referenced by: '<S9>/Pilot'
                                        */
  real_T ActuatorModel_A_l;            /* Computed Parameter: ActuatorModel_A_l
                                        * Referenced by: '<S9>/Actuator Model'
                                        */
  real_T ActuatorModel_C_j;            /* Computed Parameter: ActuatorModel_C_j
                                        * Referenced by: '<S9>/Actuator Model'
                                        */
  real_T Gain3_Gain_d;                 /* Expression: Uo
                                        * Referenced by: '<S66>/Gain3'
                                        */
  real_T Gain4_Gain_l;                 /* Expression: Mw
                                        * Referenced by: '<S66>/Gain4'
                                        */
  real_T Gain5_Gain_l;                 /* Expression: Zd
                                        * Referenced by: '<S66>/Gain5'
                                        */
  real_T Gain6_Gain_cd;                /* Expression: Md
                                        * Referenced by: '<S66>/Gain6'
                                        */
  real_T Wgustmodel_A_i[2];            /* Computed Parameter: Wgustmodel_A_i
                                        * Referenced by: '<S68>/W-gust model'
                                        */
  real_T Wgustmodel_C_o[2];            /* Computed Parameter: Wgustmodel_C_o
                                        * Referenced by: '<S68>/W-gust model'
                                        */
  real_T Gain_Gain_o1;                 /* Expression: Zw
                                        * Referenced by: '<S9>/Gain'
                                        */
  real_T Gain2_Gain_l;                 /* Expression: Mw
                                        * Referenced by: '<S9>/Gain2'
                                        */
  real_T Qgustmodel_A_a;               /* Computed Parameter: Qgustmodel_A_a
                                        * Referenced by: '<S68>/Q-gust model'
                                        */
  real_T Qgustmodel_C_b;               /* Computed Parameter: Qgustmodel_C_b
                                        * Referenced by: '<S68>/Q-gust model'
                                        */
  real_T Qgustmodel_D_pt;              /* Computed Parameter: Qgustmodel_D_pt
                                        * Referenced by: '<S68>/Q-gust model'
                                        */
  real_T Gain1_Gain_i;                 /* Expression: Mq
                                        * Referenced by: '<S9>/Gain1'
                                        */
  real_T AlphasensorLowpassFilter_A_it;/* Computed Parameter: AlphasensorLowpassFilter_A_it
                                        * Referenced by: '<S67>/Alpha-sensor Low-pass Filter'
                                        */
  real_T AlphasensorLowpassFilter_C_a; /* Computed Parameter: AlphasensorLowpassFilter_C_a
                                        * Referenced by: '<S67>/Alpha-sensor Low-pass Filter'
                                        */
  real_T StickPrefilter_A_j;           /* Computed Parameter: StickPrefilter_A_j
                                        * Referenced by: '<S67>/Stick Prefilter'
                                        */
  real_T StickPrefilter_C_h;           /* Computed Parameter: StickPrefilter_C_h
                                        * Referenced by: '<S67>/Stick Prefilter'
                                        */
  real_T PitchRateLeadFilter_A_e;      /* Computed Parameter: PitchRateLeadFilter_A_e
                                        * Referenced by: '<S67>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_C_a;      /* Computed Parameter: PitchRateLeadFilter_C_a
                                        * Referenced by: '<S67>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_D_p;      /* Computed Parameter: PitchRateLeadFilter_D_p
                                        * Referenced by: '<S67>/Pitch Rate Lead Filter'
                                        */
  real_T Gain2_Gain_cc;                /* Expression: Kq
                                        * Referenced by: '<S67>/Gain2'
                                        */
  real_T Gain3_Gain_ek;                /* Expression: Ka
                                        * Referenced by: '<S67>/Gain3'
                                        */
  real_T Gain_Gain_me;                 /* Expression: Kf
                                        * Referenced by: '<S67>/Gain'
                                        */
  real_T Proportionalplusintegralcomp_nc;/* Computed Parameter: Proportionalplusintegralcomp_nc
                                          * Referenced by: '<S67>/Proportional plus integral compensator'
                                          */
  real_T Proportionalplusintegralcomp_o2;/* Computed Parameter: Proportionalplusintegralcomp_o2
                                          * Referenced by: '<S67>/Proportional plus integral compensator'
                                          */
  real_T WhiteNoise_Mean_d;            /* Expression: 0
                                        * Referenced by: '<S70>/White Noise'
                                        */
  real_T WhiteNoise_StdDev_p1;         /* Computed Parameter: WhiteNoise_StdDev_p1
                                        * Referenced by: '<S70>/White Noise'
                                        */
  real_T WhiteNoise_Seed_m;            /* Expression: seed
                                        * Referenced by: '<S70>/White Noise'
                                        */
  real_T Output_Gain_kt;               /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S70>/Output'
                                        */
  real_T TransferFcn2_A_o;             /* Computed Parameter: TransferFcn2_A_o
                                        * Referenced by: '<S71>/Transfer Fcn.2'
                                        */
  real_T TransferFcn2_C_iu;            /* Computed Parameter: TransferFcn2_C_iu
                                        * Referenced by: '<S71>/Transfer Fcn.2'
                                        */
  real_T Gain5_Gain_m5;                /* Expression: 1/Uo
                                        * Referenced by: '<S10>/Gain5'
                                        */
  real_T TransferFcn1_A_me;            /* Computed Parameter: TransferFcn1_A_me
                                        * Referenced by: '<S71>/Transfer Fcn.1'
                                        */
  real_T TransferFcn1_C_i;             /* Computed Parameter: TransferFcn1_C_i
                                        * Referenced by: '<S71>/Transfer Fcn.1'
                                        */
  real_T Gain1_Gain_l;                 /* Expression: 22.8
                                        * Referenced by: '<S74>/Gain1'
                                        */
  real_T Constant_Value_k;             /* Expression: Uo
                                        * Referenced by: '<S74>/Constant'
                                        */
  real_T Gain2_Gain_fh;                /* Expression: 1/g
                                        * Referenced by: '<S74>/Gain2'
                                        */
  real_T Pilot_Amplitude_if;           /* Expression: 1
                                        * Referenced by: '<S10>/Pilot'
                                        */
  real_T Pilot_Frequency_ga;           /* Computed Parameter: Pilot_Frequency_ga
                                        * Referenced by: '<S10>/Pilot'
                                        */
  real_T ActuatorModel_A_ga;           /* Computed Parameter: ActuatorModel_A_ga
                                        * Referenced by: '<S10>/Actuator Model'
                                        */
  real_T ActuatorModel_C_jn;           /* Computed Parameter: ActuatorModel_C_jn
                                        * Referenced by: '<S10>/Actuator Model'
                                        */
  real_T Gain3_Gain_ao;                /* Expression: Uo
                                        * Referenced by: '<S71>/Gain3'
                                        */
  real_T Gain4_Gain_o;                 /* Expression: Mw
                                        * Referenced by: '<S71>/Gain4'
                                        */
  real_T Gain5_Gain_hj;                /* Expression: Zd
                                        * Referenced by: '<S71>/Gain5'
                                        */
  real_T Gain6_Gain_p;                 /* Expression: Md
                                        * Referenced by: '<S71>/Gain6'
                                        */
  real_T Wgustmodel_A_he[2];           /* Computed Parameter: Wgustmodel_A_he
                                        * Referenced by: '<S73>/W-gust model'
                                        */
  real_T Wgustmodel_C_g[2];            /* Computed Parameter: Wgustmodel_C_g
                                        * Referenced by: '<S73>/W-gust model'
                                        */
  real_T Gain_Gain_e;                  /* Expression: Zw
                                        * Referenced by: '<S10>/Gain'
                                        */
  real_T Gain2_Gain_nv;                /* Expression: Mw
                                        * Referenced by: '<S10>/Gain2'
                                        */
  real_T Qgustmodel_A_l;               /* Computed Parameter: Qgustmodel_A_l
                                        * Referenced by: '<S73>/Q-gust model'
                                        */
  real_T Qgustmodel_C_bg;              /* Computed Parameter: Qgustmodel_C_bg
                                        * Referenced by: '<S73>/Q-gust model'
                                        */
  real_T Qgustmodel_D_ci;              /* Computed Parameter: Qgustmodel_D_ci
                                        * Referenced by: '<S73>/Q-gust model'
                                        */
  real_T Gain1_Gain_no;                /* Expression: Mq
                                        * Referenced by: '<S10>/Gain1'
                                        */
  real_T AlphasensorLowpassFilter_A_f; /* Computed Parameter: AlphasensorLowpassFilter_A_f
                                        * Referenced by: '<S72>/Alpha-sensor Low-pass Filter'
                                        */
  real_T AlphasensorLowpassFilter_C_ee;/* Computed Parameter: AlphasensorLowpassFilter_C_ee
                                        * Referenced by: '<S72>/Alpha-sensor Low-pass Filter'
                                        */
  real_T StickPrefilter_A_jy;          /* Computed Parameter: StickPrefilter_A_jy
                                        * Referenced by: '<S72>/Stick Prefilter'
                                        */
  real_T StickPrefilter_C_o;           /* Computed Parameter: StickPrefilter_C_o
                                        * Referenced by: '<S72>/Stick Prefilter'
                                        */
  real_T PitchRateLeadFilter_A_h;      /* Computed Parameter: PitchRateLeadFilter_A_h
                                        * Referenced by: '<S72>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_C_bz;     /* Computed Parameter: PitchRateLeadFilter_C_bz
                                        * Referenced by: '<S72>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_D_cd;     /* Computed Parameter: PitchRateLeadFilter_D_cd
                                        * Referenced by: '<S72>/Pitch Rate Lead Filter'
                                        */
  real_T Gain2_Gain_dg;                /* Expression: Kq
                                        * Referenced by: '<S72>/Gain2'
                                        */
  real_T Gain3_Gain_m;                 /* Expression: Ka
                                        * Referenced by: '<S72>/Gain3'
                                        */
  real_T Gain_Gain_ld;                 /* Expression: Kf
                                        * Referenced by: '<S72>/Gain'
                                        */
  real_T Proportionalplusintegralcomp_o3;/* Computed Parameter: Proportionalplusintegralcomp_o3
                                          * Referenced by: '<S72>/Proportional plus integral compensator'
                                          */
  real_T Proportionalplusintegralcompe_e;/* Computed Parameter: Proportionalplusintegralcompe_e
                                          * Referenced by: '<S72>/Proportional plus integral compensator'
                                          */
  real_T WhiteNoise_Mean_m;            /* Expression: 0
                                        * Referenced by: '<S75>/White Noise'
                                        */
  real_T WhiteNoise_StdDev_g;          /* Computed Parameter: WhiteNoise_StdDev_g
                                        * Referenced by: '<S75>/White Noise'
                                        */
  real_T WhiteNoise_Seed_p0;           /* Expression: seed
                                        * Referenced by: '<S75>/White Noise'
                                        */
  real_T Output_Gain_e;                /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S75>/Output'
                                        */
  real_T TransferFcn2_A_l;             /* Computed Parameter: TransferFcn2_A_l
                                        * Referenced by: '<S76>/Transfer Fcn.2'
                                        */
  real_T TransferFcn2_C_e;             /* Computed Parameter: TransferFcn2_C_e
                                        * Referenced by: '<S76>/Transfer Fcn.2'
                                        */
  real_T Gain5_Gain_k;                 /* Expression: 1/Uo
                                        * Referenced by: '<S11>/Gain5'
                                        */
  real_T TransferFcn1_A_g;             /* Computed Parameter: TransferFcn1_A_g
                                        * Referenced by: '<S76>/Transfer Fcn.1'
                                        */
  real_T TransferFcn1_C_ir;            /* Computed Parameter: TransferFcn1_C_ir
                                        * Referenced by: '<S76>/Transfer Fcn.1'
                                        */
  real_T Gain1_Gain_at;                /* Expression: 22.8
                                        * Referenced by: '<S79>/Gain1'
                                        */
  real_T Constant_Value_o;             /* Expression: Uo
                                        * Referenced by: '<S79>/Constant'
                                        */
  real_T Gain2_Gain_pu;                /* Expression: 1/g
                                        * Referenced by: '<S79>/Gain2'
                                        */
  real_T Pilot_Amplitude_h;            /* Expression: 1
                                        * Referenced by: '<S11>/Pilot'
                                        */
  real_T Pilot_Frequency_c;            /* Computed Parameter: Pilot_Frequency_c
                                        * Referenced by: '<S11>/Pilot'
                                        */
  real_T ActuatorModel_A_lr;           /* Computed Parameter: ActuatorModel_A_lr
                                        * Referenced by: '<S11>/Actuator Model'
                                        */
  real_T ActuatorModel_C_m;            /* Computed Parameter: ActuatorModel_C_m
                                        * Referenced by: '<S11>/Actuator Model'
                                        */
  real_T Gain3_Gain_fb;                /* Expression: Uo
                                        * Referenced by: '<S76>/Gain3'
                                        */
  real_T Gain4_Gain_p3;                /* Expression: Mw
                                        * Referenced by: '<S76>/Gain4'
                                        */
  real_T Gain5_Gain_e;                 /* Expression: Zd
                                        * Referenced by: '<S76>/Gain5'
                                        */
  real_T Gain6_Gain_e;                 /* Expression: Md
                                        * Referenced by: '<S76>/Gain6'
                                        */
  real_T Wgustmodel_A_gn[2];           /* Computed Parameter: Wgustmodel_A_gn
                                        * Referenced by: '<S78>/W-gust model'
                                        */
  real_T Wgustmodel_C_p[2];            /* Computed Parameter: Wgustmodel_C_p
                                        * Referenced by: '<S78>/W-gust model'
                                        */
  real_T Gain_Gain_lw;                 /* Expression: Zw
                                        * Referenced by: '<S11>/Gain'
                                        */
  real_T Gain2_Gain_pn;                /* Expression: Mw
                                        * Referenced by: '<S11>/Gain2'
                                        */
  real_T Qgustmodel_A_d;               /* Computed Parameter: Qgustmodel_A_d
                                        * Referenced by: '<S78>/Q-gust model'
                                        */
  real_T Qgustmodel_C_m;               /* Computed Parameter: Qgustmodel_C_m
                                        * Referenced by: '<S78>/Q-gust model'
                                        */
  real_T Qgustmodel_D_o;               /* Computed Parameter: Qgustmodel_D_o
                                        * Referenced by: '<S78>/Q-gust model'
                                        */
  real_T Gain1_Gain_gy;                /* Expression: Mq
                                        * Referenced by: '<S11>/Gain1'
                                        */
  real_T AlphasensorLowpassFilter_A_id;/* Computed Parameter: AlphasensorLowpassFilter_A_id
                                        * Referenced by: '<S77>/Alpha-sensor Low-pass Filter'
                                        */
  real_T AlphasensorLowpassFilter_C_fk;/* Computed Parameter: AlphasensorLowpassFilter_C_fk
                                        * Referenced by: '<S77>/Alpha-sensor Low-pass Filter'
                                        */
  real_T StickPrefilter_A_g0;          /* Computed Parameter: StickPrefilter_A_g0
                                        * Referenced by: '<S77>/Stick Prefilter'
                                        */
  real_T StickPrefilter_C_pu;          /* Computed Parameter: StickPrefilter_C_pu
                                        * Referenced by: '<S77>/Stick Prefilter'
                                        */
  real_T PitchRateLeadFilter_A_l;      /* Computed Parameter: PitchRateLeadFilter_A_l
                                        * Referenced by: '<S77>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_C_i;      /* Computed Parameter: PitchRateLeadFilter_C_i
                                        * Referenced by: '<S77>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_D_h;      /* Computed Parameter: PitchRateLeadFilter_D_h
                                        * Referenced by: '<S77>/Pitch Rate Lead Filter'
                                        */
  real_T Gain2_Gain_gj;                /* Expression: Kq
                                        * Referenced by: '<S77>/Gain2'
                                        */
  real_T Gain3_Gain_b2;                /* Expression: Ka
                                        * Referenced by: '<S77>/Gain3'
                                        */
  real_T Gain_Gain_cm;                 /* Expression: Kf
                                        * Referenced by: '<S77>/Gain'
                                        */
  real_T Proportionalplusintegralcomp_d3;/* Computed Parameter: Proportionalplusintegralcomp_d3
                                          * Referenced by: '<S77>/Proportional plus integral compensator'
                                          */
  real_T Proportionalplusintegralcomp_ea;/* Computed Parameter: Proportionalplusintegralcomp_ea
                                          * Referenced by: '<S77>/Proportional plus integral compensator'
                                          */
  real_T WhiteNoise_Mean_dw;           /* Expression: 0
                                        * Referenced by: '<S80>/White Noise'
                                        */
  real_T WhiteNoise_StdDev_m;          /* Computed Parameter: WhiteNoise_StdDev_m
                                        * Referenced by: '<S80>/White Noise'
                                        */
  real_T WhiteNoise_Seed_o;            /* Expression: seed
                                        * Referenced by: '<S80>/White Noise'
                                        */
  real_T Output_Gain_k2;               /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S80>/Output'
                                        */
  real_T TransferFcn2_A_b;             /* Computed Parameter: TransferFcn2_A_b
                                        * Referenced by: '<S81>/Transfer Fcn.2'
                                        */
  real_T TransferFcn2_C_gn;            /* Computed Parameter: TransferFcn2_C_gn
                                        * Referenced by: '<S81>/Transfer Fcn.2'
                                        */
  real_T Gain5_Gain_nx;                /* Expression: 1/Uo
                                        * Referenced by: '<S12>/Gain5'
                                        */
  real_T TransferFcn1_A_c;             /* Computed Parameter: TransferFcn1_A_c
                                        * Referenced by: '<S81>/Transfer Fcn.1'
                                        */
  real_T TransferFcn1_C_e;             /* Computed Parameter: TransferFcn1_C_e
                                        * Referenced by: '<S81>/Transfer Fcn.1'
                                        */
  real_T Gain1_Gain_n2;                /* Expression: 22.8
                                        * Referenced by: '<S84>/Gain1'
                                        */
  real_T Constant_Value_ha;            /* Expression: Uo
                                        * Referenced by: '<S84>/Constant'
                                        */
  real_T Gain2_Gain_nx;                /* Expression: 1/g
                                        * Referenced by: '<S84>/Gain2'
                                        */
  real_T Pilot_Amplitude_dw;           /* Expression: 1
                                        * Referenced by: '<S12>/Pilot'
                                        */
  real_T Pilot_Frequency_h;            /* Computed Parameter: Pilot_Frequency_h
                                        * Referenced by: '<S12>/Pilot'
                                        */
  real_T ActuatorModel_A_b;            /* Computed Parameter: ActuatorModel_A_b
                                        * Referenced by: '<S12>/Actuator Model'
                                        */
  real_T ActuatorModel_C_dv;           /* Computed Parameter: ActuatorModel_C_dv
                                        * Referenced by: '<S12>/Actuator Model'
                                        */
  real_T Gain3_Gain_n;                 /* Expression: Uo
                                        * Referenced by: '<S81>/Gain3'
                                        */
  real_T Gain4_Gain_f0;                /* Expression: Mw
                                        * Referenced by: '<S81>/Gain4'
                                        */
  real_T Gain5_Gain_lt;                /* Expression: Zd
                                        * Referenced by: '<S81>/Gain5'
                                        */
  real_T Gain6_Gain_bp;                /* Expression: Md
                                        * Referenced by: '<S81>/Gain6'
                                        */
  real_T Wgustmodel_A_le[2];           /* Computed Parameter: Wgustmodel_A_le
                                        * Referenced by: '<S83>/W-gust model'
                                        */
  real_T Wgustmodel_C_cv[2];           /* Computed Parameter: Wgustmodel_C_cv
                                        * Referenced by: '<S83>/W-gust model'
                                        */
  real_T Gain_Gain_m1g;                /* Expression: Zw
                                        * Referenced by: '<S12>/Gain'
                                        */
  real_T Gain2_Gain_pr;                /* Expression: Mw
                                        * Referenced by: '<S12>/Gain2'
                                        */
  real_T Qgustmodel_A_h;               /* Computed Parameter: Qgustmodel_A_h
                                        * Referenced by: '<S83>/Q-gust model'
                                        */
  real_T Qgustmodel_C_i;               /* Computed Parameter: Qgustmodel_C_i
                                        * Referenced by: '<S83>/Q-gust model'
                                        */
  real_T Qgustmodel_D_pk;              /* Computed Parameter: Qgustmodel_D_pk
                                        * Referenced by: '<S83>/Q-gust model'
                                        */
  real_T Gain1_Gain_gb;                /* Expression: Mq
                                        * Referenced by: '<S12>/Gain1'
                                        */
  real_T AlphasensorLowpassFilter_A_o; /* Computed Parameter: AlphasensorLowpassFilter_A_o
                                        * Referenced by: '<S82>/Alpha-sensor Low-pass Filter'
                                        */
  real_T AlphasensorLowpassFilter_C_m; /* Computed Parameter: AlphasensorLowpassFilter_C_m
                                        * Referenced by: '<S82>/Alpha-sensor Low-pass Filter'
                                        */
  real_T StickPrefilter_A_a;           /* Computed Parameter: StickPrefilter_A_a
                                        * Referenced by: '<S82>/Stick Prefilter'
                                        */
  real_T StickPrefilter_C_mg;          /* Computed Parameter: StickPrefilter_C_mg
                                        * Referenced by: '<S82>/Stick Prefilter'
                                        */
  real_T PitchRateLeadFilter_A_b;      /* Computed Parameter: PitchRateLeadFilter_A_b
                                        * Referenced by: '<S82>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_C_nz;     /* Computed Parameter: PitchRateLeadFilter_C_nz
                                        * Referenced by: '<S82>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_D_fx;     /* Computed Parameter: PitchRateLeadFilter_D_fx
                                        * Referenced by: '<S82>/Pitch Rate Lead Filter'
                                        */
  real_T Gain2_Gain_kt;                /* Expression: Kq
                                        * Referenced by: '<S82>/Gain2'
                                        */
  real_T Gain3_Gain_ca;                /* Expression: Ka
                                        * Referenced by: '<S82>/Gain3'
                                        */
  real_T Gain_Gain_lq;                 /* Expression: Kf
                                        * Referenced by: '<S82>/Gain'
                                        */
  real_T Proportionalplusintegralcomp_ov;/* Computed Parameter: Proportionalplusintegralcomp_ov
                                          * Referenced by: '<S82>/Proportional plus integral compensator'
                                          */
  real_T Proportionalplusintegralcompe_j;/* Computed Parameter: Proportionalplusintegralcompe_j
                                          * Referenced by: '<S82>/Proportional plus integral compensator'
                                          */
  real_T WhiteNoise_Mean_k;            /* Expression: 0
                                        * Referenced by: '<S85>/White Noise'
                                        */
  real_T WhiteNoise_StdDev_ng;         /* Computed Parameter: WhiteNoise_StdDev_ng
                                        * Referenced by: '<S85>/White Noise'
                                        */
  real_T WhiteNoise_Seed_d;            /* Expression: seed
                                        * Referenced by: '<S85>/White Noise'
                                        */
  real_T Output_Gain_cn;               /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S85>/Output'
                                        */
  real_T TransferFcn2_A_lg;            /* Computed Parameter: TransferFcn2_A_lg
                                        * Referenced by: '<S86>/Transfer Fcn.2'
                                        */
  real_T TransferFcn2_C_a;             /* Computed Parameter: TransferFcn2_C_a
                                        * Referenced by: '<S86>/Transfer Fcn.2'
                                        */
  real_T Gain5_Gain_cw;                /* Expression: 1/Uo
                                        * Referenced by: '<S13>/Gain5'
                                        */
  real_T TransferFcn1_A_dl;            /* Computed Parameter: TransferFcn1_A_dl
                                        * Referenced by: '<S86>/Transfer Fcn.1'
                                        */
  real_T TransferFcn1_C_gb;            /* Computed Parameter: TransferFcn1_C_gb
                                        * Referenced by: '<S86>/Transfer Fcn.1'
                                        */
  real_T Gain1_Gain_em;                /* Expression: 22.8
                                        * Referenced by: '<S89>/Gain1'
                                        */
  real_T Constant_Value_bm;            /* Expression: Uo
                                        * Referenced by: '<S89>/Constant'
                                        */
  real_T Gain2_Gain_h5;                /* Expression: 1/g
                                        * Referenced by: '<S89>/Gain2'
                                        */
  real_T Pilot_Amplitude_e;            /* Expression: 1
                                        * Referenced by: '<S13>/Pilot'
                                        */
  real_T Pilot_Frequency_k;            /* Computed Parameter: Pilot_Frequency_k
                                        * Referenced by: '<S13>/Pilot'
                                        */
  real_T ActuatorModel_A_gy;           /* Computed Parameter: ActuatorModel_A_gy
                                        * Referenced by: '<S13>/Actuator Model'
                                        */
  real_T ActuatorModel_C_bj;           /* Computed Parameter: ActuatorModel_C_bj
                                        * Referenced by: '<S13>/Actuator Model'
                                        */
  real_T Gain3_Gain_cd;                /* Expression: Uo
                                        * Referenced by: '<S86>/Gain3'
                                        */
  real_T Gain4_Gain_j;                 /* Expression: Mw
                                        * Referenced by: '<S86>/Gain4'
                                        */
  real_T Gain5_Gain_pd;                /* Expression: Zd
                                        * Referenced by: '<S86>/Gain5'
                                        */
  real_T Gain6_Gain_f;                 /* Expression: Md
                                        * Referenced by: '<S86>/Gain6'
                                        */
  real_T Wgustmodel_A_m[2];            /* Computed Parameter: Wgustmodel_A_m
                                        * Referenced by: '<S88>/W-gust model'
                                        */
  real_T Wgustmodel_C_mc[2];           /* Computed Parameter: Wgustmodel_C_mc
                                        * Referenced by: '<S88>/W-gust model'
                                        */
  real_T Gain_Gain_d;                  /* Expression: Zw
                                        * Referenced by: '<S13>/Gain'
                                        */
  real_T Gain2_Gain_g3;                /* Expression: Mw
                                        * Referenced by: '<S13>/Gain2'
                                        */
  real_T Qgustmodel_A_b;               /* Computed Parameter: Qgustmodel_A_b
                                        * Referenced by: '<S88>/Q-gust model'
                                        */
  real_T Qgustmodel_C_j0;              /* Computed Parameter: Qgustmodel_C_j0
                                        * Referenced by: '<S88>/Q-gust model'
                                        */
  real_T Qgustmodel_D_i;               /* Computed Parameter: Qgustmodel_D_i
                                        * Referenced by: '<S88>/Q-gust model'
                                        */
  real_T Gain1_Gain_f;                 /* Expression: Mq
                                        * Referenced by: '<S13>/Gain1'
                                        */
  real_T AlphasensorLowpassFilter_A_c; /* Computed Parameter: AlphasensorLowpassFilter_A_c
                                        * Referenced by: '<S87>/Alpha-sensor Low-pass Filter'
                                        */
  real_T AlphasensorLowpassFilter_C_gf;/* Computed Parameter: AlphasensorLowpassFilter_C_gf
                                        * Referenced by: '<S87>/Alpha-sensor Low-pass Filter'
                                        */
  real_T StickPrefilter_A_e;           /* Computed Parameter: StickPrefilter_A_e
                                        * Referenced by: '<S87>/Stick Prefilter'
                                        */
  real_T StickPrefilter_C_j0;          /* Computed Parameter: StickPrefilter_C_j0
                                        * Referenced by: '<S87>/Stick Prefilter'
                                        */
  real_T PitchRateLeadFilter_A_i;      /* Computed Parameter: PitchRateLeadFilter_A_i
                                        * Referenced by: '<S87>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_C_k4;     /* Computed Parameter: PitchRateLeadFilter_C_k4
                                        * Referenced by: '<S87>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_D_ft;     /* Computed Parameter: PitchRateLeadFilter_D_ft
                                        * Referenced by: '<S87>/Pitch Rate Lead Filter'
                                        */
  real_T Gain2_Gain_eh;                /* Expression: Kq
                                        * Referenced by: '<S87>/Gain2'
                                        */
  real_T Gain3_Gain_my;                /* Expression: Ka
                                        * Referenced by: '<S87>/Gain3'
                                        */
  real_T Gain_Gain_jg;                 /* Expression: Kf
                                        * Referenced by: '<S87>/Gain'
                                        */
  real_T Proportionalplusintegralcomp_hc;/* Computed Parameter: Proportionalplusintegralcomp_hc
                                          * Referenced by: '<S87>/Proportional plus integral compensator'
                                          */
  real_T Proportionalplusintegralcomp_lj;/* Computed Parameter: Proportionalplusintegralcomp_lj
                                          * Referenced by: '<S87>/Proportional plus integral compensator'
                                          */
  real_T WhiteNoise_Mean_kt;           /* Expression: 0
                                        * Referenced by: '<S90>/White Noise'
                                        */
  real_T WhiteNoise_StdDev_gu;         /* Computed Parameter: WhiteNoise_StdDev_gu
                                        * Referenced by: '<S90>/White Noise'
                                        */
  real_T WhiteNoise_Seed_j;            /* Expression: seed
                                        * Referenced by: '<S90>/White Noise'
                                        */
  real_T Output_Gain_me;               /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S90>/Output'
                                        */
  real_T TransferFcn2_A_f1;            /* Computed Parameter: TransferFcn2_A_f1
                                        * Referenced by: '<S91>/Transfer Fcn.2'
                                        */
  real_T TransferFcn2_C_ik;            /* Computed Parameter: TransferFcn2_C_ik
                                        * Referenced by: '<S91>/Transfer Fcn.2'
                                        */
  real_T Gain5_Gain_ey;                /* Expression: 1/Uo
                                        * Referenced by: '<S14>/Gain5'
                                        */
  real_T TransferFcn1_A_nq;            /* Computed Parameter: TransferFcn1_A_nq
                                        * Referenced by: '<S91>/Transfer Fcn.1'
                                        */
  real_T TransferFcn1_C_o;             /* Computed Parameter: TransferFcn1_C_o
                                        * Referenced by: '<S91>/Transfer Fcn.1'
                                        */
  real_T Gain1_Gain_b;                 /* Expression: 22.8
                                        * Referenced by: '<S94>/Gain1'
                                        */
  real_T Constant_Value_d;             /* Expression: Uo
                                        * Referenced by: '<S94>/Constant'
                                        */
  real_T Gain2_Gain_pl;                /* Expression: 1/g
                                        * Referenced by: '<S94>/Gain2'
                                        */
  real_T Pilot_Amplitude_b;            /* Expression: 1
                                        * Referenced by: '<S14>/Pilot'
                                        */
  real_T Pilot_Frequency_cr;           /* Computed Parameter: Pilot_Frequency_cr
                                        * Referenced by: '<S14>/Pilot'
                                        */
  real_T ActuatorModel_A_n;            /* Computed Parameter: ActuatorModel_A_n
                                        * Referenced by: '<S14>/Actuator Model'
                                        */
  real_T ActuatorModel_C_n;            /* Computed Parameter: ActuatorModel_C_n
                                        * Referenced by: '<S14>/Actuator Model'
                                        */
  real_T Gain3_Gain_e0;                /* Expression: Uo
                                        * Referenced by: '<S91>/Gain3'
                                        */
  real_T Gain4_Gain_n;                 /* Expression: Mw
                                        * Referenced by: '<S91>/Gain4'
                                        */
  real_T Gain5_Gain_hv;                /* Expression: Zd
                                        * Referenced by: '<S91>/Gain5'
                                        */
  real_T Gain6_Gain_k;                 /* Expression: Md
                                        * Referenced by: '<S91>/Gain6'
                                        */
  real_T Wgustmodel_A_dc[2];           /* Computed Parameter: Wgustmodel_A_dc
                                        * Referenced by: '<S93>/W-gust model'
                                        */
  real_T Wgustmodel_C_n[2];            /* Computed Parameter: Wgustmodel_C_n
                                        * Referenced by: '<S93>/W-gust model'
                                        */
  real_T Gain_Gain_lj;                 /* Expression: Zw
                                        * Referenced by: '<S14>/Gain'
                                        */
  real_T Gain2_Gain_ir;                /* Expression: Mw
                                        * Referenced by: '<S14>/Gain2'
                                        */
  real_T Qgustmodel_A_oe;              /* Computed Parameter: Qgustmodel_A_oe
                                        * Referenced by: '<S93>/Q-gust model'
                                        */
  real_T Qgustmodel_C_pp;              /* Computed Parameter: Qgustmodel_C_pp
                                        * Referenced by: '<S93>/Q-gust model'
                                        */
  real_T Qgustmodel_D_g;               /* Computed Parameter: Qgustmodel_D_g
                                        * Referenced by: '<S93>/Q-gust model'
                                        */
  real_T Gain1_Gain_gs;                /* Expression: Mq
                                        * Referenced by: '<S14>/Gain1'
                                        */
  real_T AlphasensorLowpassFilter_A_bs;/* Computed Parameter: AlphasensorLowpassFilter_A_bs
                                        * Referenced by: '<S92>/Alpha-sensor Low-pass Filter'
                                        */
  real_T AlphasensorLowpassFilter_C_o; /* Computed Parameter: AlphasensorLowpassFilter_C_o
                                        * Referenced by: '<S92>/Alpha-sensor Low-pass Filter'
                                        */
  real_T StickPrefilter_A_ca;          /* Computed Parameter: StickPrefilter_A_ca
                                        * Referenced by: '<S92>/Stick Prefilter'
                                        */
  real_T StickPrefilter_C_g;           /* Computed Parameter: StickPrefilter_C_g
                                        * Referenced by: '<S92>/Stick Prefilter'
                                        */
  real_T PitchRateLeadFilter_A_go;     /* Computed Parameter: PitchRateLeadFilter_A_go
                                        * Referenced by: '<S92>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_C_it;     /* Computed Parameter: PitchRateLeadFilter_C_it
                                        * Referenced by: '<S92>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_D_m;      /* Computed Parameter: PitchRateLeadFilter_D_m
                                        * Referenced by: '<S92>/Pitch Rate Lead Filter'
                                        */
  real_T Gain2_Gain_nm;                /* Expression: Kq
                                        * Referenced by: '<S92>/Gain2'
                                        */
  real_T Gain3_Gain_fp;                /* Expression: Ka
                                        * Referenced by: '<S92>/Gain3'
                                        */
  real_T Gain_Gain_og;                 /* Expression: Kf
                                        * Referenced by: '<S92>/Gain'
                                        */
  real_T Proportionalplusintegralcomp_fg;/* Computed Parameter: Proportionalplusintegralcomp_fg
                                          * Referenced by: '<S92>/Proportional plus integral compensator'
                                          */
  real_T Proportionalplusintegralcomp_dy;/* Computed Parameter: Proportionalplusintegralcomp_dy
                                          * Referenced by: '<S92>/Proportional plus integral compensator'
                                          */
  real_T WhiteNoise_Mean_ko;           /* Expression: 0
                                        * Referenced by: '<S95>/White Noise'
                                        */
  real_T WhiteNoise_StdDev_pf;         /* Computed Parameter: WhiteNoise_StdDev_pf
                                        * Referenced by: '<S95>/White Noise'
                                        */
  real_T WhiteNoise_Seed_pj;           /* Expression: seed
                                        * Referenced by: '<S95>/White Noise'
                                        */
  real_T Output_Gain_n;                /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S95>/Output'
                                        */
  real_T TransferFcn2_A_iv;            /* Computed Parameter: TransferFcn2_A_iv
                                        * Referenced by: '<S96>/Transfer Fcn.2'
                                        */
  real_T TransferFcn2_C_iy;            /* Computed Parameter: TransferFcn2_C_iy
                                        * Referenced by: '<S96>/Transfer Fcn.2'
                                        */
  real_T Gain5_Gain_eyn;               /* Expression: 1/Uo
                                        * Referenced by: '<S15>/Gain5'
                                        */
  real_T TransferFcn1_A_gv;            /* Computed Parameter: TransferFcn1_A_gv
                                        * Referenced by: '<S96>/Transfer Fcn.1'
                                        */
  real_T TransferFcn1_C_a;             /* Computed Parameter: TransferFcn1_C_a
                                        * Referenced by: '<S96>/Transfer Fcn.1'
                                        */
  real_T Gain1_Gain_mj;                /* Expression: 22.8
                                        * Referenced by: '<S99>/Gain1'
                                        */
  real_T Constant_Value_a;             /* Expression: Uo
                                        * Referenced by: '<S99>/Constant'
                                        */
  real_T Gain2_Gain_b0;                /* Expression: 1/g
                                        * Referenced by: '<S99>/Gain2'
                                        */
  real_T Pilot_Amplitude_a;            /* Expression: 1
                                        * Referenced by: '<S15>/Pilot'
                                        */
  real_T Pilot_Frequency_m;            /* Computed Parameter: Pilot_Frequency_m
                                        * Referenced by: '<S15>/Pilot'
                                        */
  real_T ActuatorModel_A_e;            /* Computed Parameter: ActuatorModel_A_e
                                        * Referenced by: '<S15>/Actuator Model'
                                        */
  real_T ActuatorModel_C_o;            /* Computed Parameter: ActuatorModel_C_o
                                        * Referenced by: '<S15>/Actuator Model'
                                        */
  real_T Gain3_Gain_c3;                /* Expression: Uo
                                        * Referenced by: '<S96>/Gain3'
                                        */
  real_T Gain4_Gain_jg;                /* Expression: Mw
                                        * Referenced by: '<S96>/Gain4'
                                        */
  real_T Gain5_Gain_d;                 /* Expression: Zd
                                        * Referenced by: '<S96>/Gain5'
                                        */
  real_T Gain6_Gain_an;                /* Expression: Md
                                        * Referenced by: '<S96>/Gain6'
                                        */
  real_T Wgustmodel_A_e[2];            /* Computed Parameter: Wgustmodel_A_e
                                        * Referenced by: '<S98>/W-gust model'
                                        */
  real_T Wgustmodel_C_f[2];            /* Computed Parameter: Wgustmodel_C_f
                                        * Referenced by: '<S98>/W-gust model'
                                        */
  real_T Gain_Gain_ir;                 /* Expression: Zw
                                        * Referenced by: '<S15>/Gain'
                                        */
  real_T Gain2_Gain_cq;                /* Expression: Mw
                                        * Referenced by: '<S15>/Gain2'
                                        */
  real_T Qgustmodel_A_f;               /* Computed Parameter: Qgustmodel_A_f
                                        * Referenced by: '<S98>/Q-gust model'
                                        */
  real_T Qgustmodel_C_bf;              /* Computed Parameter: Qgustmodel_C_bf
                                        * Referenced by: '<S98>/Q-gust model'
                                        */
  real_T Qgustmodel_D_k;               /* Computed Parameter: Qgustmodel_D_k
                                        * Referenced by: '<S98>/Q-gust model'
                                        */
  real_T Gain1_Gain_k;                 /* Expression: Mq
                                        * Referenced by: '<S15>/Gain1'
                                        */
  real_T AlphasensorLowpassFilter_A_hx;/* Computed Parameter: AlphasensorLowpassFilter_A_hx
                                        * Referenced by: '<S97>/Alpha-sensor Low-pass Filter'
                                        */
  real_T AlphasensorLowpassFilter_C_nu;/* Computed Parameter: AlphasensorLowpassFilter_C_nu
                                        * Referenced by: '<S97>/Alpha-sensor Low-pass Filter'
                                        */
  real_T StickPrefilter_A_f;           /* Computed Parameter: StickPrefilter_A_f
                                        * Referenced by: '<S97>/Stick Prefilter'
                                        */
  real_T StickPrefilter_C_jy;          /* Computed Parameter: StickPrefilter_C_jy
                                        * Referenced by: '<S97>/Stick Prefilter'
                                        */
  real_T PitchRateLeadFilter_A_p0;     /* Computed Parameter: PitchRateLeadFilter_A_p0
                                        * Referenced by: '<S97>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_C_f;      /* Computed Parameter: PitchRateLeadFilter_C_f
                                        * Referenced by: '<S97>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_D_n;      /* Computed Parameter: PitchRateLeadFilter_D_n
                                        * Referenced by: '<S97>/Pitch Rate Lead Filter'
                                        */
  real_T Gain2_Gain_hg;                /* Expression: Kq
                                        * Referenced by: '<S97>/Gain2'
                                        */
  real_T Gain3_Gain_m0;                /* Expression: Ka
                                        * Referenced by: '<S97>/Gain3'
                                        */
  real_T Gain_Gain_a3;                 /* Expression: Kf
                                        * Referenced by: '<S97>/Gain'
                                        */
  real_T Proportionalplusintegralcomp_fo;/* Computed Parameter: Proportionalplusintegralcomp_fo
                                          * Referenced by: '<S97>/Proportional plus integral compensator'
                                          */
  real_T Proportionalplusintegralcomp_gs;/* Computed Parameter: Proportionalplusintegralcomp_gs
                                          * Referenced by: '<S97>/Proportional plus integral compensator'
                                          */
  real_T WhiteNoise_Mean_p;            /* Expression: 0
                                        * Referenced by: '<S100>/White Noise'
                                        */
  real_T WhiteNoise_StdDev_kj;         /* Computed Parameter: WhiteNoise_StdDev_kj
                                        * Referenced by: '<S100>/White Noise'
                                        */
  real_T WhiteNoise_Seed_a;            /* Expression: seed
                                        * Referenced by: '<S100>/White Noise'
                                        */
  real_T Output_Gain_dh;               /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S100>/Output'
                                        */
  real_T TransferFcn2_A_fp;            /* Computed Parameter: TransferFcn2_A_fp
                                        * Referenced by: '<S101>/Transfer Fcn.2'
                                        */
  real_T TransferFcn2_C_h;             /* Computed Parameter: TransferFcn2_C_h
                                        * Referenced by: '<S101>/Transfer Fcn.2'
                                        */
  real_T Gain5_Gain_kt;                /* Expression: 1/Uo
                                        * Referenced by: '<S16>/Gain5'
                                        */
  real_T TransferFcn1_A_di;            /* Computed Parameter: TransferFcn1_A_di
                                        * Referenced by: '<S101>/Transfer Fcn.1'
                                        */
  real_T TransferFcn1_C_h;             /* Computed Parameter: TransferFcn1_C_h
                                        * Referenced by: '<S101>/Transfer Fcn.1'
                                        */
  real_T Gain1_Gain_nw;                /* Expression: 22.8
                                        * Referenced by: '<S104>/Gain1'
                                        */
  real_T Constant_Value_fo;            /* Expression: Uo
                                        * Referenced by: '<S104>/Constant'
                                        */
  real_T Gain2_Gain_iv;                /* Expression: 1/g
                                        * Referenced by: '<S104>/Gain2'
                                        */
  real_T Pilot_Amplitude_hb;           /* Expression: 1
                                        * Referenced by: '<S16>/Pilot'
                                        */
  real_T Pilot_Frequency_o;            /* Computed Parameter: Pilot_Frequency_o
                                        * Referenced by: '<S16>/Pilot'
                                        */
  real_T ActuatorModel_A_a;            /* Computed Parameter: ActuatorModel_A_a
                                        * Referenced by: '<S16>/Actuator Model'
                                        */
  real_T ActuatorModel_C_jw;           /* Computed Parameter: ActuatorModel_C_jw
                                        * Referenced by: '<S16>/Actuator Model'
                                        */
  real_T Gain3_Gain_dc;                /* Expression: Uo
                                        * Referenced by: '<S101>/Gain3'
                                        */
  real_T Gain4_Gain_np;                /* Expression: Mw
                                        * Referenced by: '<S101>/Gain4'
                                        */
  real_T Gain5_Gain_ct;                /* Expression: Zd
                                        * Referenced by: '<S101>/Gain5'
                                        */
  real_T Gain6_Gain_cq;                /* Expression: Md
                                        * Referenced by: '<S101>/Gain6'
                                        */
  real_T Wgustmodel_A_f[2];            /* Computed Parameter: Wgustmodel_A_f
                                        * Referenced by: '<S103>/W-gust model'
                                        */
  real_T Wgustmodel_C_me[2];           /* Computed Parameter: Wgustmodel_C_me
                                        * Referenced by: '<S103>/W-gust model'
                                        */
  real_T Gain_Gain_e3;                 /* Expression: Zw
                                        * Referenced by: '<S16>/Gain'
                                        */
  real_T Gain2_Gain_ii;                /* Expression: Mw
                                        * Referenced by: '<S16>/Gain2'
                                        */
  real_T Qgustmodel_A_oy;              /* Computed Parameter: Qgustmodel_A_oy
                                        * Referenced by: '<S103>/Q-gust model'
                                        */
  real_T Qgustmodel_C_h;               /* Computed Parameter: Qgustmodel_C_h
                                        * Referenced by: '<S103>/Q-gust model'
                                        */
  real_T Qgustmodel_D_kl;              /* Computed Parameter: Qgustmodel_D_kl
                                        * Referenced by: '<S103>/Q-gust model'
                                        */
  real_T Gain1_Gain_bc;                /* Expression: Mq
                                        * Referenced by: '<S16>/Gain1'
                                        */
  real_T AlphasensorLowpassFilter_A_hc;/* Computed Parameter: AlphasensorLowpassFilter_A_hc
                                        * Referenced by: '<S102>/Alpha-sensor Low-pass Filter'
                                        */
  real_T AlphasensorLowpassFilter_C_i; /* Computed Parameter: AlphasensorLowpassFilter_C_i
                                        * Referenced by: '<S102>/Alpha-sensor Low-pass Filter'
                                        */
  real_T StickPrefilter_A_i1;          /* Computed Parameter: StickPrefilter_A_i1
                                        * Referenced by: '<S102>/Stick Prefilter'
                                        */
  real_T StickPrefilter_C_k;           /* Computed Parameter: StickPrefilter_C_k
                                        * Referenced by: '<S102>/Stick Prefilter'
                                        */
  real_T PitchRateLeadFilter_A_it;     /* Computed Parameter: PitchRateLeadFilter_A_it
                                        * Referenced by: '<S102>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_C_fn;     /* Computed Parameter: PitchRateLeadFilter_C_fn
                                        * Referenced by: '<S102>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_D_hr;     /* Computed Parameter: PitchRateLeadFilter_D_hr
                                        * Referenced by: '<S102>/Pitch Rate Lead Filter'
                                        */
  real_T Gain2_Gain_hm;                /* Expression: Kq
                                        * Referenced by: '<S102>/Gain2'
                                        */
  real_T Gain3_Gain_gc;                /* Expression: Ka
                                        * Referenced by: '<S102>/Gain3'
                                        */
  real_T Gain_Gain_mx;                 /* Expression: Kf
                                        * Referenced by: '<S102>/Gain'
                                        */
  real_T Proportionalplusintegralcomp_dl;/* Computed Parameter: Proportionalplusintegralcomp_dl
                                          * Referenced by: '<S102>/Proportional plus integral compensator'
                                          */
  real_T Proportionalplusintegralcomp_ej;/* Computed Parameter: Proportionalplusintegralcomp_ej
                                          * Referenced by: '<S102>/Proportional plus integral compensator'
                                          */
  real_T WhiteNoise_Mean_b;            /* Expression: 0
                                        * Referenced by: '<S105>/White Noise'
                                        */
  real_T WhiteNoise_StdDev_pd;         /* Computed Parameter: WhiteNoise_StdDev_pd
                                        * Referenced by: '<S105>/White Noise'
                                        */
  real_T WhiteNoise_Seed_l;            /* Expression: seed
                                        * Referenced by: '<S105>/White Noise'
                                        */
  real_T Output_Gain_f;                /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S105>/Output'
                                        */
  real_T TransferFcn2_A_ir;            /* Computed Parameter: TransferFcn2_A_ir
                                        * Referenced by: '<S106>/Transfer Fcn.2'
                                        */
  real_T TransferFcn2_C_jy;            /* Computed Parameter: TransferFcn2_C_jy
                                        * Referenced by: '<S106>/Transfer Fcn.2'
                                        */
  real_T Gain5_Gain_gx;                /* Expression: 1/Uo
                                        * Referenced by: '<S17>/Gain5'
                                        */
  real_T TransferFcn1_A_m5;            /* Computed Parameter: TransferFcn1_A_m5
                                        * Referenced by: '<S106>/Transfer Fcn.1'
                                        */
  real_T TransferFcn1_C_ip;            /* Computed Parameter: TransferFcn1_C_ip
                                        * Referenced by: '<S106>/Transfer Fcn.1'
                                        */
  real_T Gain1_Gain_eo;                /* Expression: 22.8
                                        * Referenced by: '<S109>/Gain1'
                                        */
  real_T Constant_Value_n;             /* Expression: Uo
                                        * Referenced by: '<S109>/Constant'
                                        */
  real_T Gain2_Gain_f2;                /* Expression: 1/g
                                        * Referenced by: '<S109>/Gain2'
                                        */
  real_T Pilot_Amplitude_jy;           /* Expression: 1
                                        * Referenced by: '<S17>/Pilot'
                                        */
  real_T Pilot_Frequency_bs;           /* Computed Parameter: Pilot_Frequency_bs
                                        * Referenced by: '<S17>/Pilot'
                                        */
  real_T ActuatorModel_A_c;            /* Computed Parameter: ActuatorModel_A_c
                                        * Referenced by: '<S17>/Actuator Model'
                                        */
  real_T ActuatorModel_C_ju;           /* Computed Parameter: ActuatorModel_C_ju
                                        * Referenced by: '<S17>/Actuator Model'
                                        */
  real_T Gain3_Gain_mv;                /* Expression: Uo
                                        * Referenced by: '<S106>/Gain3'
                                        */
  real_T Gain4_Gain_on;                /* Expression: Mw
                                        * Referenced by: '<S106>/Gain4'
                                        */
  real_T Gain5_Gain_a;                 /* Expression: Zd
                                        * Referenced by: '<S106>/Gain5'
                                        */
  real_T Gain6_Gain_h;                 /* Expression: Md
                                        * Referenced by: '<S106>/Gain6'
                                        */
  real_T Wgustmodel_A_id[2];           /* Computed Parameter: Wgustmodel_A_id
                                        * Referenced by: '<S108>/W-gust model'
                                        */
  real_T Wgustmodel_C_o2[2];           /* Computed Parameter: Wgustmodel_C_o2
                                        * Referenced by: '<S108>/W-gust model'
                                        */
  real_T Gain_Gain_cr;                 /* Expression: Zw
                                        * Referenced by: '<S17>/Gain'
                                        */
  real_T Gain2_Gain_dq;                /* Expression: Mw
                                        * Referenced by: '<S17>/Gain2'
                                        */
  real_T Qgustmodel_A_n;               /* Computed Parameter: Qgustmodel_A_n
                                        * Referenced by: '<S108>/Q-gust model'
                                        */
  real_T Qgustmodel_C_hg;              /* Computed Parameter: Qgustmodel_C_hg
                                        * Referenced by: '<S108>/Q-gust model'
                                        */
  real_T Qgustmodel_D_m;               /* Computed Parameter: Qgustmodel_D_m
                                        * Referenced by: '<S108>/Q-gust model'
                                        */
  real_T Gain1_Gain_ee;                /* Expression: Mq
                                        * Referenced by: '<S17>/Gain1'
                                        */
  real_T AlphasensorLowpassFilter_A_k; /* Computed Parameter: AlphasensorLowpassFilter_A_k
                                        * Referenced by: '<S107>/Alpha-sensor Low-pass Filter'
                                        */
  real_T AlphasensorLowpassFilter_C_fg;/* Computed Parameter: AlphasensorLowpassFilter_C_fg
                                        * Referenced by: '<S107>/Alpha-sensor Low-pass Filter'
                                        */
  real_T StickPrefilter_A_em;          /* Computed Parameter: StickPrefilter_A_em
                                        * Referenced by: '<S107>/Stick Prefilter'
                                        */
  real_T StickPrefilter_C_a;           /* Computed Parameter: StickPrefilter_C_a
                                        * Referenced by: '<S107>/Stick Prefilter'
                                        */
  real_T PitchRateLeadFilter_A_pn;     /* Computed Parameter: PitchRateLeadFilter_A_pn
                                        * Referenced by: '<S107>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_C_k3;     /* Computed Parameter: PitchRateLeadFilter_C_k3
                                        * Referenced by: '<S107>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_D_cw;     /* Computed Parameter: PitchRateLeadFilter_D_cw
                                        * Referenced by: '<S107>/Pitch Rate Lead Filter'
                                        */
  real_T Gain2_Gain_j;                 /* Expression: Kq
                                        * Referenced by: '<S107>/Gain2'
                                        */
  real_T Gain3_Gain_gu;                /* Expression: Ka
                                        * Referenced by: '<S107>/Gain3'
                                        */
  real_T Gain_Gain_f;                  /* Expression: Kf
                                        * Referenced by: '<S107>/Gain'
                                        */
  real_T Proportionalplusintegralcomp_jv;/* Computed Parameter: Proportionalplusintegralcomp_jv
                                          * Referenced by: '<S107>/Proportional plus integral compensator'
                                          */
  real_T Proportionalplusintegralcom_gsn;/* Computed Parameter: Proportionalplusintegralcom_gsn
                                          * Referenced by: '<S107>/Proportional plus integral compensator'
                                          */
  real_T WhiteNoise_Mean_db;           /* Expression: 0
                                        * Referenced by: '<S110>/White Noise'
                                        */
  real_T WhiteNoise_StdDev_a;          /* Computed Parameter: WhiteNoise_StdDev_a
                                        * Referenced by: '<S110>/White Noise'
                                        */
  real_T WhiteNoise_Seed_pi;           /* Expression: seed
                                        * Referenced by: '<S110>/White Noise'
                                        */
  real_T Output_Gain_k21;              /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S110>/Output'
                                        */
  real_T TransferFcn2_A_p;             /* Computed Parameter: TransferFcn2_A_p
                                        * Referenced by: '<S111>/Transfer Fcn.2'
                                        */
  real_T TransferFcn2_C_kd;            /* Computed Parameter: TransferFcn2_C_kd
                                        * Referenced by: '<S111>/Transfer Fcn.2'
                                        */
  real_T Gain5_Gain_ke;                /* Expression: 1/Uo
                                        * Referenced by: '<S18>/Gain5'
                                        */
  real_T TransferFcn1_A_dw;            /* Computed Parameter: TransferFcn1_A_dw
                                        * Referenced by: '<S111>/Transfer Fcn.1'
                                        */
  real_T TransferFcn1_C_d;             /* Computed Parameter: TransferFcn1_C_d
                                        * Referenced by: '<S111>/Transfer Fcn.1'
                                        */
  real_T Gain1_Gain_gs4;               /* Expression: 22.8
                                        * Referenced by: '<S114>/Gain1'
                                        */
  real_T Constant_Value_kk;            /* Expression: Uo
                                        * Referenced by: '<S114>/Constant'
                                        */
  real_T Gain2_Gain_ie;                /* Expression: 1/g
                                        * Referenced by: '<S114>/Gain2'
                                        */
  real_T Pilot_Amplitude_oj;           /* Expression: 1
                                        * Referenced by: '<S18>/Pilot'
                                        */
  real_T Pilot_Frequency_l;            /* Computed Parameter: Pilot_Frequency_l
                                        * Referenced by: '<S18>/Pilot'
                                        */
  real_T ActuatorModel_A_af;           /* Computed Parameter: ActuatorModel_A_af
                                        * Referenced by: '<S18>/Actuator Model'
                                        */
  real_T ActuatorModel_C_p;            /* Computed Parameter: ActuatorModel_C_p
                                        * Referenced by: '<S18>/Actuator Model'
                                        */
  real_T Gain3_Gain_ou;                /* Expression: Uo
                                        * Referenced by: '<S111>/Gain3'
                                        */
  real_T Gain4_Gain_fe;                /* Expression: Mw
                                        * Referenced by: '<S111>/Gain4'
                                        */
  real_T Gain5_Gain_nv;                /* Expression: Zd
                                        * Referenced by: '<S111>/Gain5'
                                        */
  real_T Gain6_Gain_dl;                /* Expression: Md
                                        * Referenced by: '<S111>/Gain6'
                                        */
  real_T Wgustmodel_A_do[2];           /* Computed Parameter: Wgustmodel_A_do
                                        * Referenced by: '<S113>/W-gust model'
                                        */
  real_T Wgustmodel_C_k[2];            /* Computed Parameter: Wgustmodel_C_k
                                        * Referenced by: '<S113>/W-gust model'
                                        */
  real_T Gain_Gain_ob;                 /* Expression: Zw
                                        * Referenced by: '<S18>/Gain'
                                        */
  real_T Gain2_Gain_eq;                /* Expression: Mw
                                        * Referenced by: '<S18>/Gain2'
                                        */
  real_T Qgustmodel_A_bl;              /* Computed Parameter: Qgustmodel_A_bl
                                        * Referenced by: '<S113>/Q-gust model'
                                        */
  real_T Qgustmodel_C_l;               /* Computed Parameter: Qgustmodel_C_l
                                        * Referenced by: '<S113>/Q-gust model'
                                        */
  real_T Qgustmodel_D_my;              /* Computed Parameter: Qgustmodel_D_my
                                        * Referenced by: '<S113>/Q-gust model'
                                        */
  real_T Gain1_Gain_al;                /* Expression: Mq
                                        * Referenced by: '<S18>/Gain1'
                                        */
  real_T AlphasensorLowpassFilter_A_cp;/* Computed Parameter: AlphasensorLowpassFilter_A_cp
                                        * Referenced by: '<S112>/Alpha-sensor Low-pass Filter'
                                        */
  real_T AlphasensorLowpassFilter_C_ib;/* Computed Parameter: AlphasensorLowpassFilter_C_ib
                                        * Referenced by: '<S112>/Alpha-sensor Low-pass Filter'
                                        */
  real_T StickPrefilter_A_ik;          /* Computed Parameter: StickPrefilter_A_ik
                                        * Referenced by: '<S112>/Stick Prefilter'
                                        */
  real_T StickPrefilter_C_b;           /* Computed Parameter: StickPrefilter_C_b
                                        * Referenced by: '<S112>/Stick Prefilter'
                                        */
  real_T PitchRateLeadFilter_A_g0;     /* Computed Parameter: PitchRateLeadFilter_A_g0
                                        * Referenced by: '<S112>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_C_m;      /* Computed Parameter: PitchRateLeadFilter_C_m
                                        * Referenced by: '<S112>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_D_l;      /* Computed Parameter: PitchRateLeadFilter_D_l
                                        * Referenced by: '<S112>/Pitch Rate Lead Filter'
                                        */
  real_T Gain2_Gain_hk;                /* Expression: Kq
                                        * Referenced by: '<S112>/Gain2'
                                        */
  real_T Gain3_Gain_i5;                /* Expression: Ka
                                        * Referenced by: '<S112>/Gain3'
                                        */
  real_T Gain_Gain_ma;                 /* Expression: Kf
                                        * Referenced by: '<S112>/Gain'
                                        */
  real_T Proportionalplusintegralcomp_by;/* Computed Parameter: Proportionalplusintegralcomp_by
                                          * Referenced by: '<S112>/Proportional plus integral compensator'
                                          */
  real_T Proportionalplusintegralcomp_cm;/* Computed Parameter: Proportionalplusintegralcomp_cm
                                          * Referenced by: '<S112>/Proportional plus integral compensator'
                                          */
  real_T WhiteNoise_Mean_i;            /* Expression: 0
                                        * Referenced by: '<S115>/White Noise'
                                        */
  real_T WhiteNoise_StdDev_mj;         /* Computed Parameter: WhiteNoise_StdDev_mj
                                        * Referenced by: '<S115>/White Noise'
                                        */
  real_T WhiteNoise_Seed_p4;           /* Expression: seed
                                        * Referenced by: '<S115>/White Noise'
                                        */
  real_T Output_Gain_i;                /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S115>/Output'
                                        */
  real_T TransferFcn2_A_jz;            /* Computed Parameter: TransferFcn2_A_jz
                                        * Referenced by: '<S116>/Transfer Fcn.2'
                                        */
  real_T TransferFcn2_C_lj;            /* Computed Parameter: TransferFcn2_C_lj
                                        * Referenced by: '<S116>/Transfer Fcn.2'
                                        */
  real_T Gain5_Gain_j0;                /* Expression: 1/Uo
                                        * Referenced by: '<S19>/Gain5'
                                        */
  real_T TransferFcn1_A_a;             /* Computed Parameter: TransferFcn1_A_a
                                        * Referenced by: '<S116>/Transfer Fcn.1'
                                        */
  real_T TransferFcn1_C_l;             /* Computed Parameter: TransferFcn1_C_l
                                        * Referenced by: '<S116>/Transfer Fcn.1'
                                        */
  real_T Gain1_Gain_fm;                /* Expression: 22.8
                                        * Referenced by: '<S119>/Gain1'
                                        */
  real_T Constant_Value_fy;            /* Expression: Uo
                                        * Referenced by: '<S119>/Constant'
                                        */
  real_T Gain2_Gain_kz;                /* Expression: 1/g
                                        * Referenced by: '<S119>/Gain2'
                                        */
  real_T Pilot_Amplitude_ow;           /* Expression: 1
                                        * Referenced by: '<S19>/Pilot'
                                        */
  real_T Pilot_Frequency_io;           /* Computed Parameter: Pilot_Frequency_io
                                        * Referenced by: '<S19>/Pilot'
                                        */
  real_T ActuatorModel_A_pv;           /* Computed Parameter: ActuatorModel_A_pv
                                        * Referenced by: '<S19>/Actuator Model'
                                        */
  real_T ActuatorModel_C_l;            /* Computed Parameter: ActuatorModel_C_l
                                        * Referenced by: '<S19>/Actuator Model'
                                        */
  real_T Gain3_Gain_pal;               /* Expression: Uo
                                        * Referenced by: '<S116>/Gain3'
                                        */
  real_T Gain4_Gain_cw;                /* Expression: Mw
                                        * Referenced by: '<S116>/Gain4'
                                        */
  real_T Gain5_Gain_j0q;               /* Expression: Zd
                                        * Referenced by: '<S116>/Gain5'
                                        */
  real_T Gain6_Gain_j;                 /* Expression: Md
                                        * Referenced by: '<S116>/Gain6'
                                        */
  real_T Wgustmodel_A_b[2];            /* Computed Parameter: Wgustmodel_A_b
                                        * Referenced by: '<S118>/W-gust model'
                                        */
  real_T Wgustmodel_C_gf[2];           /* Computed Parameter: Wgustmodel_C_gf
                                        * Referenced by: '<S118>/W-gust model'
                                        */
  real_T Gain_Gain_hf;                 /* Expression: Zw
                                        * Referenced by: '<S19>/Gain'
                                        */
  real_T Gain2_Gain_mq;                /* Expression: Mw
                                        * Referenced by: '<S19>/Gain2'
                                        */
  real_T Qgustmodel_A_gs;              /* Computed Parameter: Qgustmodel_A_gs
                                        * Referenced by: '<S118>/Q-gust model'
                                        */
  real_T Qgustmodel_C_a;               /* Computed Parameter: Qgustmodel_C_a
                                        * Referenced by: '<S118>/Q-gust model'
                                        */
  real_T Qgustmodel_D_a;               /* Computed Parameter: Qgustmodel_D_a
                                        * Referenced by: '<S118>/Q-gust model'
                                        */
  real_T Gain1_Gain_d2;                /* Expression: Mq
                                        * Referenced by: '<S19>/Gain1'
                                        */
  real_T AlphasensorLowpassFilter_A_pm;/* Computed Parameter: AlphasensorLowpassFilter_A_pm
                                        * Referenced by: '<S117>/Alpha-sensor Low-pass Filter'
                                        */
  real_T AlphasensorLowpassFilter_C_m5;/* Computed Parameter: AlphasensorLowpassFilter_C_m5
                                        * Referenced by: '<S117>/Alpha-sensor Low-pass Filter'
                                        */
  real_T StickPrefilter_A_dg;          /* Computed Parameter: StickPrefilter_A_dg
                                        * Referenced by: '<S117>/Stick Prefilter'
                                        */
  real_T StickPrefilter_C_hk;          /* Computed Parameter: StickPrefilter_C_hk
                                        * Referenced by: '<S117>/Stick Prefilter'
                                        */
  real_T PitchRateLeadFilter_A_pq;     /* Computed Parameter: PitchRateLeadFilter_A_pq
                                        * Referenced by: '<S117>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_C_bm;     /* Computed Parameter: PitchRateLeadFilter_C_bm
                                        * Referenced by: '<S117>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_D_bv;     /* Computed Parameter: PitchRateLeadFilter_D_bv
                                        * Referenced by: '<S117>/Pitch Rate Lead Filter'
                                        */
  real_T Gain2_Gain_bf;                /* Expression: Kq
                                        * Referenced by: '<S117>/Gain2'
                                        */
  real_T Gain3_Gain_ae;                /* Expression: Ka
                                        * Referenced by: '<S117>/Gain3'
                                        */
  real_T Gain_Gain_f3;                 /* Expression: Kf
                                        * Referenced by: '<S117>/Gain'
                                        */
  real_T Proportionalplusintegralcomp_kg;/* Computed Parameter: Proportionalplusintegralcomp_kg
                                          * Referenced by: '<S117>/Proportional plus integral compensator'
                                          */
  real_T Proportionalplusintegralcomp_jf;/* Computed Parameter: Proportionalplusintegralcomp_jf
                                          * Referenced by: '<S117>/Proportional plus integral compensator'
                                          */
  real_T WhiteNoise_Mean_nk;           /* Expression: 0
                                        * Referenced by: '<S120>/White Noise'
                                        */
  real_T WhiteNoise_StdDev_f;          /* Computed Parameter: WhiteNoise_StdDev_f
                                        * Referenced by: '<S120>/White Noise'
                                        */
  real_T WhiteNoise_Seed_cp;           /* Expression: seed
                                        * Referenced by: '<S120>/White Noise'
                                        */
  real_T Output_Gain_p;                /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S120>/Output'
                                        */
  real_T TransferFcn2_A_c;             /* Computed Parameter: TransferFcn2_A_c
                                        * Referenced by: '<S121>/Transfer Fcn.2'
                                        */
  real_T TransferFcn2_C_eq;            /* Computed Parameter: TransferFcn2_C_eq
                                        * Referenced by: '<S121>/Transfer Fcn.2'
                                        */
  real_T Gain5_Gain_f5;                /* Expression: 1/Uo
                                        * Referenced by: '<S20>/Gain5'
                                        */
  real_T TransferFcn1_A_oo;            /* Computed Parameter: TransferFcn1_A_oo
                                        * Referenced by: '<S121>/Transfer Fcn.1'
                                        */
  real_T TransferFcn1_C_jv;            /* Computed Parameter: TransferFcn1_C_jv
                                        * Referenced by: '<S121>/Transfer Fcn.1'
                                        */
  real_T Gain1_Gain_mk;                /* Expression: 22.8
                                        * Referenced by: '<S124>/Gain1'
                                        */
  real_T Constant_Value_p;             /* Expression: Uo
                                        * Referenced by: '<S124>/Constant'
                                        */
  real_T Gain2_Gain_de;                /* Expression: 1/g
                                        * Referenced by: '<S124>/Gain2'
                                        */
  real_T Pilot_Amplitude_hj;           /* Expression: 1
                                        * Referenced by: '<S20>/Pilot'
                                        */
  real_T Pilot_Frequency_a;            /* Computed Parameter: Pilot_Frequency_a
                                        * Referenced by: '<S20>/Pilot'
                                        */
  real_T ActuatorModel_A_gly;          /* Computed Parameter: ActuatorModel_A_gly
                                        * Referenced by: '<S20>/Actuator Model'
                                        */
  real_T ActuatorModel_C_a;            /* Computed Parameter: ActuatorModel_C_a
                                        * Referenced by: '<S20>/Actuator Model'
                                        */
  real_T Gain3_Gain_ai;                /* Expression: Uo
                                        * Referenced by: '<S121>/Gain3'
                                        */
  real_T Gain4_Gain_d;                 /* Expression: Mw
                                        * Referenced by: '<S121>/Gain4'
                                        */
  real_T Gain5_Gain_no;                /* Expression: Zd
                                        * Referenced by: '<S121>/Gain5'
                                        */
  real_T Gain6_Gain_nn;                /* Expression: Md
                                        * Referenced by: '<S121>/Gain6'
                                        */
  real_T Wgustmodel_A_lv[2];           /* Computed Parameter: Wgustmodel_A_lv
                                        * Referenced by: '<S123>/W-gust model'
                                        */
  real_T Wgustmodel_C_pf[2];           /* Computed Parameter: Wgustmodel_C_pf
                                        * Referenced by: '<S123>/W-gust model'
                                        */
  real_T Gain_Gain_c0;                 /* Expression: Zw
                                        * Referenced by: '<S20>/Gain'
                                        */
  real_T Gain2_Gain_l0;                /* Expression: Mw
                                        * Referenced by: '<S20>/Gain2'
                                        */
  real_T Qgustmodel_A_gl;              /* Computed Parameter: Qgustmodel_A_gl
                                        * Referenced by: '<S123>/Q-gust model'
                                        */
  real_T Qgustmodel_C_c;               /* Computed Parameter: Qgustmodel_C_c
                                        * Referenced by: '<S123>/Q-gust model'
                                        */
  real_T Qgustmodel_D_l;               /* Computed Parameter: Qgustmodel_D_l
                                        * Referenced by: '<S123>/Q-gust model'
                                        */
  real_T Gain1_Gain_a4;                /* Expression: Mq
                                        * Referenced by: '<S20>/Gain1'
                                        */
  real_T AlphasensorLowpassFilter_A_a; /* Computed Parameter: AlphasensorLowpassFilter_A_a
                                        * Referenced by: '<S122>/Alpha-sensor Low-pass Filter'
                                        */
  real_T AlphasensorLowpassFilter_C_es;/* Computed Parameter: AlphasensorLowpassFilter_C_es
                                        * Referenced by: '<S122>/Alpha-sensor Low-pass Filter'
                                        */
  real_T StickPrefilter_A_ee;          /* Computed Parameter: StickPrefilter_A_ee
                                        * Referenced by: '<S122>/Stick Prefilter'
                                        */
  real_T StickPrefilter_C_b3;          /* Computed Parameter: StickPrefilter_C_b3
                                        * Referenced by: '<S122>/Stick Prefilter'
                                        */
  real_T PitchRateLeadFilter_A_m;      /* Computed Parameter: PitchRateLeadFilter_A_m
                                        * Referenced by: '<S122>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_C_at;     /* Computed Parameter: PitchRateLeadFilter_C_at
                                        * Referenced by: '<S122>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_D_a;      /* Computed Parameter: PitchRateLeadFilter_D_a
                                        * Referenced by: '<S122>/Pitch Rate Lead Filter'
                                        */
  real_T Gain2_Gain_ne;                /* Expression: Kq
                                        * Referenced by: '<S122>/Gain2'
                                        */
  real_T Gain3_Gain_h;                 /* Expression: Ka
                                        * Referenced by: '<S122>/Gain3'
                                        */
  real_T Gain_Gain_oa;                 /* Expression: Kf
                                        * Referenced by: '<S122>/Gain'
                                        */
  real_T Proportionalplusintegralcomp_mw;/* Computed Parameter: Proportionalplusintegralcomp_mw
                                          * Referenced by: '<S122>/Proportional plus integral compensator'
                                          */
  real_T Proportionalplusintegralcomp_jp;/* Computed Parameter: Proportionalplusintegralcomp_jp
                                          * Referenced by: '<S122>/Proportional plus integral compensator'
                                          */
  real_T WhiteNoise_Mean_bf;           /* Expression: 0
                                        * Referenced by: '<S125>/White Noise'
                                        */
  real_T WhiteNoise_StdDev_kq;         /* Computed Parameter: WhiteNoise_StdDev_kq
                                        * Referenced by: '<S125>/White Noise'
                                        */
  real_T WhiteNoise_Seed_gu;           /* Expression: seed
                                        * Referenced by: '<S125>/White Noise'
                                        */
  real_T Output_Gain_pk;               /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S125>/Output'
                                        */
  real_T TransferFcn2_A_lz;            /* Computed Parameter: TransferFcn2_A_lz
                                        * Referenced by: '<S126>/Transfer Fcn.2'
                                        */
  real_T TransferFcn2_C_f;             /* Computed Parameter: TransferFcn2_C_f
                                        * Referenced by: '<S126>/Transfer Fcn.2'
                                        */
  real_T Gain5_Gain_hf;                /* Expression: 1/Uo
                                        * Referenced by: '<S21>/Gain5'
                                        */
  real_T TransferFcn1_A_by;            /* Computed Parameter: TransferFcn1_A_by
                                        * Referenced by: '<S126>/Transfer Fcn.1'
                                        */
  real_T TransferFcn1_C_k;             /* Computed Parameter: TransferFcn1_C_k
                                        * Referenced by: '<S126>/Transfer Fcn.1'
                                        */
  real_T Gain1_Gain_ow;                /* Expression: 22.8
                                        * Referenced by: '<S129>/Gain1'
                                        */
  real_T Constant_Value_oq;            /* Expression: Uo
                                        * Referenced by: '<S129>/Constant'
                                        */
  real_T Gain2_Gain_ba;                /* Expression: 1/g
                                        * Referenced by: '<S129>/Gain2'
                                        */
  real_T Pilot_Amplitude_cf;           /* Expression: 1
                                        * Referenced by: '<S21>/Pilot'
                                        */
  real_T Pilot_Frequency_ik;           /* Computed Parameter: Pilot_Frequency_ik
                                        * Referenced by: '<S21>/Pilot'
                                        */
  real_T ActuatorModel_A_o2;           /* Computed Parameter: ActuatorModel_A_o2
                                        * Referenced by: '<S21>/Actuator Model'
                                        */
  real_T ActuatorModel_C_j3;           /* Computed Parameter: ActuatorModel_C_j3
                                        * Referenced by: '<S21>/Actuator Model'
                                        */
  real_T Gain3_Gain_nz;                /* Expression: Uo
                                        * Referenced by: '<S126>/Gain3'
                                        */
  real_T Gain4_Gain_fw;                /* Expression: Mw
                                        * Referenced by: '<S126>/Gain4'
                                        */
  real_T Gain5_Gain_i;                 /* Expression: Zd
                                        * Referenced by: '<S126>/Gain5'
                                        */
  real_T Gain6_Gain_f2;                /* Expression: Md
                                        * Referenced by: '<S126>/Gain6'
                                        */
  real_T Wgustmodel_A_ei[2];           /* Computed Parameter: Wgustmodel_A_ei
                                        * Referenced by: '<S128>/W-gust model'
                                        */
  real_T Wgustmodel_C_no[2];           /* Computed Parameter: Wgustmodel_C_no
                                        * Referenced by: '<S128>/W-gust model'
                                        */
  real_T Gain_Gain_de;                 /* Expression: Zw
                                        * Referenced by: '<S21>/Gain'
                                        */
  real_T Gain2_Gain_by;                /* Expression: Mw
                                        * Referenced by: '<S21>/Gain2'
                                        */
  real_T Qgustmodel_A_ad;              /* Computed Parameter: Qgustmodel_A_ad
                                        * Referenced by: '<S128>/Q-gust model'
                                        */
  real_T Qgustmodel_C_ci;              /* Computed Parameter: Qgustmodel_C_ci
                                        * Referenced by: '<S128>/Q-gust model'
                                        */
  real_T Qgustmodel_D_g4;              /* Computed Parameter: Qgustmodel_D_g4
                                        * Referenced by: '<S128>/Q-gust model'
                                        */
  real_T Gain1_Gain_nw2;               /* Expression: Mq
                                        * Referenced by: '<S21>/Gain1'
                                        */
  real_T AlphasensorLowpassFilter_A_od;/* Computed Parameter: AlphasensorLowpassFilter_A_od
                                        * Referenced by: '<S127>/Alpha-sensor Low-pass Filter'
                                        */
  real_T AlphasensorLowpassFilter_C_gi;/* Computed Parameter: AlphasensorLowpassFilter_C_gi
                                        * Referenced by: '<S127>/Alpha-sensor Low-pass Filter'
                                        */
  real_T StickPrefilter_A_n;           /* Computed Parameter: StickPrefilter_A_n
                                        * Referenced by: '<S127>/Stick Prefilter'
                                        */
  real_T StickPrefilter_C_pn;          /* Computed Parameter: StickPrefilter_C_pn
                                        * Referenced by: '<S127>/Stick Prefilter'
                                        */
  real_T PitchRateLeadFilter_A_itf;    /* Computed Parameter: PitchRateLeadFilter_A_itf
                                        * Referenced by: '<S127>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_C_o;      /* Computed Parameter: PitchRateLeadFilter_C_o
                                        * Referenced by: '<S127>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_D_fb;     /* Computed Parameter: PitchRateLeadFilter_D_fb
                                        * Referenced by: '<S127>/Pitch Rate Lead Filter'
                                        */
  real_T Gain2_Gain_ca;                /* Expression: Kq
                                        * Referenced by: '<S127>/Gain2'
                                        */
  real_T Gain3_Gain_g4;                /* Expression: Ka
                                        * Referenced by: '<S127>/Gain3'
                                        */
  real_T Gain_Gain_n;                  /* Expression: Kf
                                        * Referenced by: '<S127>/Gain'
                                        */
  real_T Proportionalplusintegralcomp_lo;/* Computed Parameter: Proportionalplusintegralcomp_lo
                                          * Referenced by: '<S127>/Proportional plus integral compensator'
                                          */
  real_T Proportionalplusintegralcomp_pv;/* Computed Parameter: Proportionalplusintegralcomp_pv
                                          * Referenced by: '<S127>/Proportional plus integral compensator'
                                          */
  real_T WhiteNoise_Mean_g;            /* Expression: 0
                                        * Referenced by: '<S130>/White Noise'
                                        */
  real_T WhiteNoise_StdDev_fh;         /* Computed Parameter: WhiteNoise_StdDev_fh
                                        * Referenced by: '<S130>/White Noise'
                                        */
  real_T WhiteNoise_Seed_dk;           /* Expression: seed
                                        * Referenced by: '<S130>/White Noise'
                                        */
  real_T Output_Gain_cg;               /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S130>/Output'
                                        */
  real_T TransferFcn2_A_m;             /* Computed Parameter: TransferFcn2_A_m
                                        * Referenced by: '<S131>/Transfer Fcn.2'
                                        */
  real_T TransferFcn2_C_m;             /* Computed Parameter: TransferFcn2_C_m
                                        * Referenced by: '<S131>/Transfer Fcn.2'
                                        */
  real_T Gain5_Gain_l3;                /* Expression: 1/Uo
                                        * Referenced by: '<S22>/Gain5'
                                        */
  real_T TransferFcn1_A_cw;            /* Computed Parameter: TransferFcn1_A_cw
                                        * Referenced by: '<S131>/Transfer Fcn.1'
                                        */
  real_T TransferFcn1_C_c;             /* Computed Parameter: TransferFcn1_C_c
                                        * Referenced by: '<S131>/Transfer Fcn.1'
                                        */
  real_T Gain1_Gain_bu;                /* Expression: 22.8
                                        * Referenced by: '<S134>/Gain1'
                                        */
  real_T Constant_Value_gf;            /* Expression: Uo
                                        * Referenced by: '<S134>/Constant'
                                        */
  real_T Gain2_Gain_o;                 /* Expression: 1/g
                                        * Referenced by: '<S134>/Gain2'
                                        */
  real_T Pilot_Amplitude_l;            /* Expression: 1
                                        * Referenced by: '<S22>/Pilot'
                                        */
  real_T Pilot_Frequency_iu;           /* Computed Parameter: Pilot_Frequency_iu
                                        * Referenced by: '<S22>/Pilot'
                                        */
  real_T ActuatorModel_A_gz;           /* Computed Parameter: ActuatorModel_A_gz
                                        * Referenced by: '<S22>/Actuator Model'
                                        */
  real_T ActuatorModel_C_g;            /* Computed Parameter: ActuatorModel_C_g
                                        * Referenced by: '<S22>/Actuator Model'
                                        */
  real_T Gain3_Gain_ia;                /* Expression: Uo
                                        * Referenced by: '<S131>/Gain3'
                                        */
  real_T Gain4_Gain_nt;                /* Expression: Mw
                                        * Referenced by: '<S131>/Gain4'
                                        */
  real_T Gain5_Gain_jj;                /* Expression: Zd
                                        * Referenced by: '<S131>/Gain5'
                                        */
  real_T Gain6_Gain_jg;                /* Expression: Md
                                        * Referenced by: '<S131>/Gain6'
                                        */
  real_T Wgustmodel_A_c[2];            /* Computed Parameter: Wgustmodel_A_c
                                        * Referenced by: '<S133>/W-gust model'
                                        */
  real_T Wgustmodel_C_l[2];            /* Computed Parameter: Wgustmodel_C_l
                                        * Referenced by: '<S133>/W-gust model'
                                        */
  real_T Gain_Gain_fq;                 /* Expression: Zw
                                        * Referenced by: '<S22>/Gain'
                                        */
  real_T Gain2_Gain_ih;                /* Expression: Mw
                                        * Referenced by: '<S22>/Gain2'
                                        */
  real_T Qgustmodel_A_el;              /* Computed Parameter: Qgustmodel_A_el
                                        * Referenced by: '<S133>/Q-gust model'
                                        */
  real_T Qgustmodel_C_g;               /* Computed Parameter: Qgustmodel_C_g
                                        * Referenced by: '<S133>/Q-gust model'
                                        */
  real_T Qgustmodel_D_j;               /* Computed Parameter: Qgustmodel_D_j
                                        * Referenced by: '<S133>/Q-gust model'
                                        */
  real_T Gain1_Gain_dk;                /* Expression: Mq
                                        * Referenced by: '<S22>/Gain1'
                                        */
  real_T AlphasensorLowpassFilter_A_j; /* Computed Parameter: AlphasensorLowpassFilter_A_j
                                        * Referenced by: '<S132>/Alpha-sensor Low-pass Filter'
                                        */
  real_T AlphasensorLowpassFilter_C_cs;/* Computed Parameter: AlphasensorLowpassFilter_C_cs
                                        * Referenced by: '<S132>/Alpha-sensor Low-pass Filter'
                                        */
  real_T StickPrefilter_A_cc;          /* Computed Parameter: StickPrefilter_A_cc
                                        * Referenced by: '<S132>/Stick Prefilter'
                                        */
  real_T StickPrefilter_C_i;           /* Computed Parameter: StickPrefilter_C_i
                                        * Referenced by: '<S132>/Stick Prefilter'
                                        */
  real_T PitchRateLeadFilter_A_gq;     /* Computed Parameter: PitchRateLeadFilter_A_gq
                                        * Referenced by: '<S132>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_C_ml;     /* Computed Parameter: PitchRateLeadFilter_C_ml
                                        * Referenced by: '<S132>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_D_m5;     /* Computed Parameter: PitchRateLeadFilter_D_m5
                                        * Referenced by: '<S132>/Pitch Rate Lead Filter'
                                        */
  real_T Gain2_Gain_cat;               /* Expression: Kq
                                        * Referenced by: '<S132>/Gain2'
                                        */
  real_T Gain3_Gain_gk;                /* Expression: Ka
                                        * Referenced by: '<S132>/Gain3'
                                        */
  real_T Gain_Gain_im;                 /* Expression: Kf
                                        * Referenced by: '<S132>/Gain'
                                        */
  real_T Proportionalplusintegralcomp_cd;/* Computed Parameter: Proportionalplusintegralcomp_cd
                                          * Referenced by: '<S132>/Proportional plus integral compensator'
                                          */
  real_T Proportionalplusintegralcomp_mq;/* Computed Parameter: Proportionalplusintegralcomp_mq
                                          * Referenced by: '<S132>/Proportional plus integral compensator'
                                          */
  real_T WhiteNoise_Mean_jo;           /* Expression: 0
                                        * Referenced by: '<S135>/White Noise'
                                        */
  real_T WhiteNoise_StdDev_m5;         /* Computed Parameter: WhiteNoise_StdDev_m5
                                        * Referenced by: '<S135>/White Noise'
                                        */
  real_T WhiteNoise_Seed_cc;           /* Expression: seed
                                        * Referenced by: '<S135>/White Noise'
                                        */
  real_T Output_Gain_c3;               /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S135>/Output'
                                        */
  real_T TransferFcn2_A_e;             /* Computed Parameter: TransferFcn2_A_e
                                        * Referenced by: '<S136>/Transfer Fcn.2'
                                        */
  real_T TransferFcn2_C_o;             /* Computed Parameter: TransferFcn2_C_o
                                        * Referenced by: '<S136>/Transfer Fcn.2'
                                        */
  real_T Gain5_Gain_ld;                /* Expression: 1/Uo
                                        * Referenced by: '<S23>/Gain5'
                                        */
  real_T TransferFcn1_A_f;             /* Computed Parameter: TransferFcn1_A_f
                                        * Referenced by: '<S136>/Transfer Fcn.1'
                                        */
  real_T TransferFcn1_C_g1;            /* Computed Parameter: TransferFcn1_C_g1
                                        * Referenced by: '<S136>/Transfer Fcn.1'
                                        */
  real_T Gain1_Gain_dw;                /* Expression: 22.8
                                        * Referenced by: '<S139>/Gain1'
                                        */
  real_T Constant_Value_f0;            /* Expression: Uo
                                        * Referenced by: '<S139>/Constant'
                                        */
  real_T Gain2_Gain_ap;                /* Expression: 1/g
                                        * Referenced by: '<S139>/Gain2'
                                        */
  real_T Pilot_Amplitude_d2;           /* Expression: 1
                                        * Referenced by: '<S23>/Pilot'
                                        */
  real_T Pilot_Frequency_ol;           /* Computed Parameter: Pilot_Frequency_ol
                                        * Referenced by: '<S23>/Pilot'
                                        */
  real_T ActuatorModel_A_pn;           /* Computed Parameter: ActuatorModel_A_pn
                                        * Referenced by: '<S23>/Actuator Model'
                                        */
  real_T ActuatorModel_C_d3;           /* Computed Parameter: ActuatorModel_C_d3
                                        * Referenced by: '<S23>/Actuator Model'
                                        */
  real_T Gain3_Gain_hy;                /* Expression: Uo
                                        * Referenced by: '<S136>/Gain3'
                                        */
  real_T Gain4_Gain_m;                 /* Expression: Mw
                                        * Referenced by: '<S136>/Gain4'
                                        */
  real_T Gain5_Gain_dk;                /* Expression: Zd
                                        * Referenced by: '<S136>/Gain5'
                                        */
  real_T Gain6_Gain_eb;                /* Expression: Md
                                        * Referenced by: '<S136>/Gain6'
                                        */
  real_T Wgustmodel_A_g2[2];           /* Computed Parameter: Wgustmodel_A_g2
                                        * Referenced by: '<S138>/W-gust model'
                                        */
  real_T Wgustmodel_C_b[2];            /* Computed Parameter: Wgustmodel_C_b
                                        * Referenced by: '<S138>/W-gust model'
                                        */
  real_T Gain_Gain_ae;                 /* Expression: Zw
                                        * Referenced by: '<S23>/Gain'
                                        */
  real_T Gain2_Gain_eg;                /* Expression: Mw
                                        * Referenced by: '<S23>/Gain2'
                                        */
  real_T Qgustmodel_A_d3;              /* Computed Parameter: Qgustmodel_A_d3
                                        * Referenced by: '<S138>/Q-gust model'
                                        */
  real_T Qgustmodel_C_ic;              /* Computed Parameter: Qgustmodel_C_ic
                                        * Referenced by: '<S138>/Q-gust model'
                                        */
  real_T Qgustmodel_D_e;               /* Computed Parameter: Qgustmodel_D_e
                                        * Referenced by: '<S138>/Q-gust model'
                                        */
  real_T Gain1_Gain_ji;                /* Expression: Mq
                                        * Referenced by: '<S23>/Gain1'
                                        */
  real_T AlphasensorLowpassFilter_A_n; /* Computed Parameter: AlphasensorLowpassFilter_A_n
                                        * Referenced by: '<S137>/Alpha-sensor Low-pass Filter'
                                        */
  real_T AlphasensorLowpassFilter_C_p; /* Computed Parameter: AlphasensorLowpassFilter_C_p
                                        * Referenced by: '<S137>/Alpha-sensor Low-pass Filter'
                                        */
  real_T StickPrefilter_A_ng;          /* Computed Parameter: StickPrefilter_A_ng
                                        * Referenced by: '<S137>/Stick Prefilter'
                                        */
  real_T StickPrefilter_C_l;           /* Computed Parameter: StickPrefilter_C_l
                                        * Referenced by: '<S137>/Stick Prefilter'
                                        */
  real_T PitchRateLeadFilter_A_lo;     /* Computed Parameter: PitchRateLeadFilter_A_lo
                                        * Referenced by: '<S137>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_C_j;      /* Computed Parameter: PitchRateLeadFilter_C_j
                                        * Referenced by: '<S137>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_D_bq;     /* Computed Parameter: PitchRateLeadFilter_D_bq
                                        * Referenced by: '<S137>/Pitch Rate Lead Filter'
                                        */
  real_T Gain2_Gain_a5;                /* Expression: Kq
                                        * Referenced by: '<S137>/Gain2'
                                        */
  real_T Gain3_Gain_dg;                /* Expression: Ka
                                        * Referenced by: '<S137>/Gain3'
                                        */
  real_T Gain_Gain_d3;                 /* Expression: Kf
                                        * Referenced by: '<S137>/Gain'
                                        */
  real_T Proportionalplusintegralcomp_p1;/* Computed Parameter: Proportionalplusintegralcomp_p1
                                          * Referenced by: '<S137>/Proportional plus integral compensator'
                                          */
  real_T Proportionalplusintegralcomp_a4;/* Computed Parameter: Proportionalplusintegralcomp_a4
                                          * Referenced by: '<S137>/Proportional plus integral compensator'
                                          */
  real_T WhiteNoise_Mean_iu;           /* Expression: 0
                                        * Referenced by: '<S140>/White Noise'
                                        */
  real_T WhiteNoise_StdDev_id;         /* Computed Parameter: WhiteNoise_StdDev_id
                                        * Referenced by: '<S140>/White Noise'
                                        */
  real_T WhiteNoise_Seed_ev;           /* Expression: seed
                                        * Referenced by: '<S140>/White Noise'
                                        */
  real_T Output_Gain_c3r;              /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S140>/Output'
                                        */
  real_T TransferFcn2_A_ja;            /* Computed Parameter: TransferFcn2_A_ja
                                        * Referenced by: '<S141>/Transfer Fcn.2'
                                        */
  real_T TransferFcn2_C_am;            /* Computed Parameter: TransferFcn2_C_am
                                        * Referenced by: '<S141>/Transfer Fcn.2'
                                        */
  real_T Gain5_Gain_ev;                /* Expression: 1/Uo
                                        * Referenced by: '<S24>/Gain5'
                                        */
  real_T TransferFcn1_A_fq;            /* Computed Parameter: TransferFcn1_A_fq
                                        * Referenced by: '<S141>/Transfer Fcn.1'
                                        */
  real_T TransferFcn1_C_gr;            /* Computed Parameter: TransferFcn1_C_gr
                                        * Referenced by: '<S141>/Transfer Fcn.1'
                                        */
  real_T Gain1_Gain_ge;                /* Expression: 22.8
                                        * Referenced by: '<S144>/Gain1'
                                        */
  real_T Constant_Value_e;             /* Expression: Uo
                                        * Referenced by: '<S144>/Constant'
                                        */
  real_T Gain2_Gain_jn;                /* Expression: 1/g
                                        * Referenced by: '<S144>/Gain2'
                                        */
  real_T Pilot_Amplitude_g;            /* Expression: 1
                                        * Referenced by: '<S24>/Pilot'
                                        */
  real_T Pilot_Frequency_ay;           /* Computed Parameter: Pilot_Frequency_ay
                                        * Referenced by: '<S24>/Pilot'
                                        */
  real_T ActuatorModel_A_b1;           /* Computed Parameter: ActuatorModel_A_b1
                                        * Referenced by: '<S24>/Actuator Model'
                                        */
  real_T ActuatorModel_C_ka;           /* Computed Parameter: ActuatorModel_C_ka
                                        * Referenced by: '<S24>/Actuator Model'
                                        */
  real_T Gain3_Gain_on;                /* Expression: Uo
                                        * Referenced by: '<S141>/Gain3'
                                        */
  real_T Gain4_Gain_k;                 /* Expression: Mw
                                        * Referenced by: '<S141>/Gain4'
                                        */
  real_T Gain5_Gain_oik;               /* Expression: Zd
                                        * Referenced by: '<S141>/Gain5'
                                        */
  real_T Gain6_Gain_ep;                /* Expression: Md
                                        * Referenced by: '<S141>/Gain6'
                                        */
  real_T Wgustmodel_A_dm[2];           /* Computed Parameter: Wgustmodel_A_dm
                                        * Referenced by: '<S143>/W-gust model'
                                        */
  real_T Wgustmodel_C_aa[2];           /* Computed Parameter: Wgustmodel_C_aa
                                        * Referenced by: '<S143>/W-gust model'
                                        */
  real_T Gain_Gain_nx;                 /* Expression: Zw
                                        * Referenced by: '<S24>/Gain'
                                        */
  real_T Gain2_Gain_j4;                /* Expression: Mw
                                        * Referenced by: '<S24>/Gain2'
                                        */
  real_T Qgustmodel_A_mp;              /* Computed Parameter: Qgustmodel_A_mp
                                        * Referenced by: '<S143>/Q-gust model'
                                        */
  real_T Qgustmodel_C_az;              /* Computed Parameter: Qgustmodel_C_az
                                        * Referenced by: '<S143>/Q-gust model'
                                        */
  real_T Qgustmodel_D_ay;              /* Computed Parameter: Qgustmodel_D_ay
                                        * Referenced by: '<S143>/Q-gust model'
                                        */
  real_T Gain1_Gain_oq;                /* Expression: Mq
                                        * Referenced by: '<S24>/Gain1'
                                        */
  real_T AlphasensorLowpassFilter_A_l; /* Computed Parameter: AlphasensorLowpassFilter_A_l
                                        * Referenced by: '<S142>/Alpha-sensor Low-pass Filter'
                                        */
  real_T AlphasensorLowpassFilter_C_pz;/* Computed Parameter: AlphasensorLowpassFilter_C_pz
                                        * Referenced by: '<S142>/Alpha-sensor Low-pass Filter'
                                        */
  real_T StickPrefilter_A_m;           /* Computed Parameter: StickPrefilter_A_m
                                        * Referenced by: '<S142>/Stick Prefilter'
                                        */
  real_T StickPrefilter_C_n;           /* Computed Parameter: StickPrefilter_C_n
                                        * Referenced by: '<S142>/Stick Prefilter'
                                        */
  real_T PitchRateLeadFilter_A_f;      /* Computed Parameter: PitchRateLeadFilter_A_f
                                        * Referenced by: '<S142>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_C_em;     /* Computed Parameter: PitchRateLeadFilter_C_em
                                        * Referenced by: '<S142>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_D_i0;     /* Computed Parameter: PitchRateLeadFilter_D_i0
                                        * Referenced by: '<S142>/Pitch Rate Lead Filter'
                                        */
  real_T Gain2_Gain_az;                /* Expression: Kq
                                        * Referenced by: '<S142>/Gain2'
                                        */
  real_T Gain3_Gain_dp;                /* Expression: Ka
                                        * Referenced by: '<S142>/Gain3'
                                        */
  real_T Gain_Gain_ok;                 /* Expression: Kf
                                        * Referenced by: '<S142>/Gain'
                                        */
  real_T Proportionalplusintegralcom_oyd;/* Computed Parameter: Proportionalplusintegralcom_oyd
                                          * Referenced by: '<S142>/Proportional plus integral compensator'
                                          */
  real_T Proportionalplusintegralcomp_fa;/* Computed Parameter: Proportionalplusintegralcomp_fa
                                          * Referenced by: '<S142>/Proportional plus integral compensator'
                                          */
  real_T WhiteNoise_Mean_f;            /* Expression: 0
                                        * Referenced by: '<S145>/White Noise'
                                        */
  real_T WhiteNoise_StdDev_pe;         /* Computed Parameter: WhiteNoise_StdDev_pe
                                        * Referenced by: '<S145>/White Noise'
                                        */
  real_T WhiteNoise_Seed_cm;           /* Expression: seed
                                        * Referenced by: '<S145>/White Noise'
                                        */
  real_T Output_Gain_cw;               /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S145>/Output'
                                        */
  real_T TransferFcn2_A_bx;            /* Computed Parameter: TransferFcn2_A_bx
                                        * Referenced by: '<S146>/Transfer Fcn.2'
                                        */
  real_T TransferFcn2_C_hd;            /* Computed Parameter: TransferFcn2_C_hd
                                        * Referenced by: '<S146>/Transfer Fcn.2'
                                        */
  real_T Gain5_Gain_cwc;               /* Expression: 1/Uo
                                        * Referenced by: '<S25>/Gain5'
                                        */
  real_T TransferFcn1_A_cm;            /* Computed Parameter: TransferFcn1_A_cm
                                        * Referenced by: '<S146>/Transfer Fcn.1'
                                        */
  real_T TransferFcn1_C_lp;            /* Computed Parameter: TransferFcn1_C_lp
                                        * Referenced by: '<S146>/Transfer Fcn.1'
                                        */
  real_T Gain1_Gain_j1;                /* Expression: 22.8
                                        * Referenced by: '<S149>/Gain1'
                                        */
  real_T Constant_Value_dx;            /* Expression: Uo
                                        * Referenced by: '<S149>/Constant'
                                        */
  real_T Gain2_Gain_fd;                /* Expression: 1/g
                                        * Referenced by: '<S149>/Gain2'
                                        */
  real_T Pilot_Amplitude_ob;           /* Expression: 1
                                        * Referenced by: '<S25>/Pilot'
                                        */
  real_T Pilot_Frequency_ax;           /* Computed Parameter: Pilot_Frequency_ax
                                        * Referenced by: '<S25>/Pilot'
                                        */
  real_T ActuatorModel_A_l5;           /* Computed Parameter: ActuatorModel_A_l5
                                        * Referenced by: '<S25>/Actuator Model'
                                        */
  real_T ActuatorModel_C_e;            /* Computed Parameter: ActuatorModel_C_e
                                        * Referenced by: '<S25>/Actuator Model'
                                        */
  real_T Gain3_Gain_gx;                /* Expression: Uo
                                        * Referenced by: '<S146>/Gain3'
                                        */
  real_T Gain4_Gain_a;                 /* Expression: Mw
                                        * Referenced by: '<S146>/Gain4'
                                        */
  real_T Gain5_Gain_fc;                /* Expression: Zd
                                        * Referenced by: '<S146>/Gain5'
                                        */
  real_T Gain6_Gain_l;                 /* Expression: Md
                                        * Referenced by: '<S146>/Gain6'
                                        */
  real_T Wgustmodel_A_p[2];            /* Computed Parameter: Wgustmodel_A_p
                                        * Referenced by: '<S148>/W-gust model'
                                        */
  real_T Wgustmodel_C_n5[2];           /* Computed Parameter: Wgustmodel_C_n5
                                        * Referenced by: '<S148>/W-gust model'
                                        */
  real_T Gain_Gain_bj;                 /* Expression: Zw
                                        * Referenced by: '<S25>/Gain'
                                        */
  real_T Gain2_Gain_dz;                /* Expression: Mw
                                        * Referenced by: '<S25>/Gain2'
                                        */
  real_T Qgustmodel_A_bh;              /* Computed Parameter: Qgustmodel_A_bh
                                        * Referenced by: '<S148>/Q-gust model'
                                        */
  real_T Qgustmodel_C_jg;              /* Computed Parameter: Qgustmodel_C_jg
                                        * Referenced by: '<S148>/Q-gust model'
                                        */
  real_T Qgustmodel_D_gi;              /* Computed Parameter: Qgustmodel_D_gi
                                        * Referenced by: '<S148>/Q-gust model'
                                        */
  real_T Gain1_Gain_pq;                /* Expression: Mq
                                        * Referenced by: '<S25>/Gain1'
                                        */
  real_T AlphasensorLowpassFilter_A_fm;/* Computed Parameter: AlphasensorLowpassFilter_A_fm
                                        * Referenced by: '<S147>/Alpha-sensor Low-pass Filter'
                                        */
  real_T AlphasensorLowpassFilter_C_es0;/* Computed Parameter: AlphasensorLowpassFilter_C_es0
                                         * Referenced by: '<S147>/Alpha-sensor Low-pass Filter'
                                         */
  real_T StickPrefilter_A_aj;          /* Computed Parameter: StickPrefilter_A_aj
                                        * Referenced by: '<S147>/Stick Prefilter'
                                        */
  real_T StickPrefilter_C_pz;          /* Computed Parameter: StickPrefilter_C_pz
                                        * Referenced by: '<S147>/Stick Prefilter'
                                        */
  real_T PitchRateLeadFilter_A_n2;     /* Computed Parameter: PitchRateLeadFilter_A_n2
                                        * Referenced by: '<S147>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_C_hc;     /* Computed Parameter: PitchRateLeadFilter_C_hc
                                        * Referenced by: '<S147>/Pitch Rate Lead Filter'
                                        */
  real_T PitchRateLeadFilter_D_bk;     /* Computed Parameter: PitchRateLeadFilter_D_bk
                                        * Referenced by: '<S147>/Pitch Rate Lead Filter'
                                        */
  real_T Gain2_Gain_iiy;               /* Expression: Kq
                                        * Referenced by: '<S147>/Gain2'
                                        */
  real_T Gain3_Gain_dg2;               /* Expression: Ka
                                        * Referenced by: '<S147>/Gain3'
                                        */
  real_T Gain_Gain_ni;                 /* Expression: Kf
                                        * Referenced by: '<S147>/Gain'
                                        */
  real_T Proportionalplusintegralcomp_io;/* Computed Parameter: Proportionalplusintegralcomp_io
                                          * Referenced by: '<S147>/Proportional plus integral compensator'
                                          */
  real_T Proportionalplusintegralcomp_gb;/* Computed Parameter: Proportionalplusintegralcomp_gb
                                          * Referenced by: '<S147>/Proportional plus integral compensator'
                                          */
  real_T WhiteNoise_Mean_o;            /* Expression: 0
                                        * Referenced by: '<S150>/White Noise'
                                        */
  real_T WhiteNoise_StdDev_g0;         /* Computed Parameter: WhiteNoise_StdDev_g0
                                        * Referenced by: '<S150>/White Noise'
                                        */
  real_T WhiteNoise_Seed_ej;           /* Expression: seed
                                        * Referenced by: '<S150>/White Noise'
                                        */
  real_T Output_Gain_o;                /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S150>/Output'
                                        */
};

/* Real-time Model Data Structure */
struct tag_rtM_f14tmp25 {
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
    real_T odeY[250];
    real_T odeF[4][250];
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
extern Parameters_f14tmp25 f14tmp25_P;

/* Block signals (auto storage) */
extern BlockIO_f14tmp25 f14tmp25_B;

/* Continuous states (auto storage) */
extern ContinuousStates_f14tmp25 f14tmp25_X;

/* Block states (auto storage) */
extern D_Work_f14tmp25 f14tmp25_DWork;

/* Model entry point functions */
extern void f14tmp25_initialize(void);
extern void f14tmp25_output(void);
extern void f14tmp25_update(void);
extern void f14tmp25_terminate(void);

/* Real-time Model object */
extern rtModel_f14tmp25 *const f14tmp25_rtM;

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
 * '<Root>' : 'f14tmp25'
 * '<S1>'   : 'f14tmp25/Subsystem'
 * '<S2>'   : 'f14tmp25/Subsystem1'
 * '<S3>'   : 'f14tmp25/Subsystem10'
 * '<S4>'   : 'f14tmp25/Subsystem11'
 * '<S5>'   : 'f14tmp25/Subsystem12'
 * '<S6>'   : 'f14tmp25/Subsystem13'
 * '<S7>'   : 'f14tmp25/Subsystem14'
 * '<S8>'   : 'f14tmp25/Subsystem15'
 * '<S9>'   : 'f14tmp25/Subsystem16'
 * '<S10>'  : 'f14tmp25/Subsystem17'
 * '<S11>'  : 'f14tmp25/Subsystem18'
 * '<S12>'  : 'f14tmp25/Subsystem19'
 * '<S13>'  : 'f14tmp25/Subsystem2'
 * '<S14>'  : 'f14tmp25/Subsystem20'
 * '<S15>'  : 'f14tmp25/Subsystem21'
 * '<S16>'  : 'f14tmp25/Subsystem22'
 * '<S17>'  : 'f14tmp25/Subsystem23'
 * '<S18>'  : 'f14tmp25/Subsystem24'
 * '<S19>'  : 'f14tmp25/Subsystem3'
 * '<S20>'  : 'f14tmp25/Subsystem4'
 * '<S21>'  : 'f14tmp25/Subsystem5'
 * '<S22>'  : 'f14tmp25/Subsystem6'
 * '<S23>'  : 'f14tmp25/Subsystem7'
 * '<S24>'  : 'f14tmp25/Subsystem8'
 * '<S25>'  : 'f14tmp25/Subsystem9'
 * '<S26>'  : 'f14tmp25/Subsystem/Aircraft Dynamics Model'
 * '<S27>'  : 'f14tmp25/Subsystem/Controller'
 * '<S28>'  : 'f14tmp25/Subsystem/Dryden Wind Gust Models'
 * '<S29>'  : 'f14tmp25/Subsystem/Nz pilot calculation'
 * '<S30>'  : 'f14tmp25/Subsystem/Dryden Wind Gust Models/Band-Limited White Noise'
 * '<S31>'  : 'f14tmp25/Subsystem1/Aircraft Dynamics Model'
 * '<S32>'  : 'f14tmp25/Subsystem1/Controller'
 * '<S33>'  : 'f14tmp25/Subsystem1/Dryden Wind Gust Models'
 * '<S34>'  : 'f14tmp25/Subsystem1/Nz pilot calculation'
 * '<S35>'  : 'f14tmp25/Subsystem1/Dryden Wind Gust Models/Band-Limited White Noise'
 * '<S36>'  : 'f14tmp25/Subsystem10/Aircraft Dynamics Model'
 * '<S37>'  : 'f14tmp25/Subsystem10/Controller'
 * '<S38>'  : 'f14tmp25/Subsystem10/Dryden Wind Gust Models'
 * '<S39>'  : 'f14tmp25/Subsystem10/Nz pilot calculation'
 * '<S40>'  : 'f14tmp25/Subsystem10/Dryden Wind Gust Models/Band-Limited White Noise'
 * '<S41>'  : 'f14tmp25/Subsystem11/Aircraft Dynamics Model'
 * '<S42>'  : 'f14tmp25/Subsystem11/Controller'
 * '<S43>'  : 'f14tmp25/Subsystem11/Dryden Wind Gust Models'
 * '<S44>'  : 'f14tmp25/Subsystem11/Nz pilot calculation'
 * '<S45>'  : 'f14tmp25/Subsystem11/Dryden Wind Gust Models/Band-Limited White Noise'
 * '<S46>'  : 'f14tmp25/Subsystem12/Aircraft Dynamics Model'
 * '<S47>'  : 'f14tmp25/Subsystem12/Controller'
 * '<S48>'  : 'f14tmp25/Subsystem12/Dryden Wind Gust Models'
 * '<S49>'  : 'f14tmp25/Subsystem12/Nz pilot calculation'
 * '<S50>'  : 'f14tmp25/Subsystem12/Dryden Wind Gust Models/Band-Limited White Noise'
 * '<S51>'  : 'f14tmp25/Subsystem13/Aircraft Dynamics Model'
 * '<S52>'  : 'f14tmp25/Subsystem13/Controller'
 * '<S53>'  : 'f14tmp25/Subsystem13/Dryden Wind Gust Models'
 * '<S54>'  : 'f14tmp25/Subsystem13/Nz pilot calculation'
 * '<S55>'  : 'f14tmp25/Subsystem13/Dryden Wind Gust Models/Band-Limited White Noise'
 * '<S56>'  : 'f14tmp25/Subsystem14/Aircraft Dynamics Model'
 * '<S57>'  : 'f14tmp25/Subsystem14/Controller'
 * '<S58>'  : 'f14tmp25/Subsystem14/Dryden Wind Gust Models'
 * '<S59>'  : 'f14tmp25/Subsystem14/Nz pilot calculation'
 * '<S60>'  : 'f14tmp25/Subsystem14/Dryden Wind Gust Models/Band-Limited White Noise'
 * '<S61>'  : 'f14tmp25/Subsystem15/Aircraft Dynamics Model'
 * '<S62>'  : 'f14tmp25/Subsystem15/Controller'
 * '<S63>'  : 'f14tmp25/Subsystem15/Dryden Wind Gust Models'
 * '<S64>'  : 'f14tmp25/Subsystem15/Nz pilot calculation'
 * '<S65>'  : 'f14tmp25/Subsystem15/Dryden Wind Gust Models/Band-Limited White Noise'
 * '<S66>'  : 'f14tmp25/Subsystem16/Aircraft Dynamics Model'
 * '<S67>'  : 'f14tmp25/Subsystem16/Controller'
 * '<S68>'  : 'f14tmp25/Subsystem16/Dryden Wind Gust Models'
 * '<S69>'  : 'f14tmp25/Subsystem16/Nz pilot calculation'
 * '<S70>'  : 'f14tmp25/Subsystem16/Dryden Wind Gust Models/Band-Limited White Noise'
 * '<S71>'  : 'f14tmp25/Subsystem17/Aircraft Dynamics Model'
 * '<S72>'  : 'f14tmp25/Subsystem17/Controller'
 * '<S73>'  : 'f14tmp25/Subsystem17/Dryden Wind Gust Models'
 * '<S74>'  : 'f14tmp25/Subsystem17/Nz pilot calculation'
 * '<S75>'  : 'f14tmp25/Subsystem17/Dryden Wind Gust Models/Band-Limited White Noise'
 * '<S76>'  : 'f14tmp25/Subsystem18/Aircraft Dynamics Model'
 * '<S77>'  : 'f14tmp25/Subsystem18/Controller'
 * '<S78>'  : 'f14tmp25/Subsystem18/Dryden Wind Gust Models'
 * '<S79>'  : 'f14tmp25/Subsystem18/Nz pilot calculation'
 * '<S80>'  : 'f14tmp25/Subsystem18/Dryden Wind Gust Models/Band-Limited White Noise'
 * '<S81>'  : 'f14tmp25/Subsystem19/Aircraft Dynamics Model'
 * '<S82>'  : 'f14tmp25/Subsystem19/Controller'
 * '<S83>'  : 'f14tmp25/Subsystem19/Dryden Wind Gust Models'
 * '<S84>'  : 'f14tmp25/Subsystem19/Nz pilot calculation'
 * '<S85>'  : 'f14tmp25/Subsystem19/Dryden Wind Gust Models/Band-Limited White Noise'
 * '<S86>'  : 'f14tmp25/Subsystem2/Aircraft Dynamics Model'
 * '<S87>'  : 'f14tmp25/Subsystem2/Controller'
 * '<S88>'  : 'f14tmp25/Subsystem2/Dryden Wind Gust Models'
 * '<S89>'  : 'f14tmp25/Subsystem2/Nz pilot calculation'
 * '<S90>'  : 'f14tmp25/Subsystem2/Dryden Wind Gust Models/Band-Limited White Noise'
 * '<S91>'  : 'f14tmp25/Subsystem20/Aircraft Dynamics Model'
 * '<S92>'  : 'f14tmp25/Subsystem20/Controller'
 * '<S93>'  : 'f14tmp25/Subsystem20/Dryden Wind Gust Models'
 * '<S94>'  : 'f14tmp25/Subsystem20/Nz pilot calculation'
 * '<S95>'  : 'f14tmp25/Subsystem20/Dryden Wind Gust Models/Band-Limited White Noise'
 * '<S96>'  : 'f14tmp25/Subsystem21/Aircraft Dynamics Model'
 * '<S97>'  : 'f14tmp25/Subsystem21/Controller'
 * '<S98>'  : 'f14tmp25/Subsystem21/Dryden Wind Gust Models'
 * '<S99>'  : 'f14tmp25/Subsystem21/Nz pilot calculation'
 * '<S100>' : 'f14tmp25/Subsystem21/Dryden Wind Gust Models/Band-Limited White Noise'
 * '<S101>' : 'f14tmp25/Subsystem22/Aircraft Dynamics Model'
 * '<S102>' : 'f14tmp25/Subsystem22/Controller'
 * '<S103>' : 'f14tmp25/Subsystem22/Dryden Wind Gust Models'
 * '<S104>' : 'f14tmp25/Subsystem22/Nz pilot calculation'
 * '<S105>' : 'f14tmp25/Subsystem22/Dryden Wind Gust Models/Band-Limited White Noise'
 * '<S106>' : 'f14tmp25/Subsystem23/Aircraft Dynamics Model'
 * '<S107>' : 'f14tmp25/Subsystem23/Controller'
 * '<S108>' : 'f14tmp25/Subsystem23/Dryden Wind Gust Models'
 * '<S109>' : 'f14tmp25/Subsystem23/Nz pilot calculation'
 * '<S110>' : 'f14tmp25/Subsystem23/Dryden Wind Gust Models/Band-Limited White Noise'
 * '<S111>' : 'f14tmp25/Subsystem24/Aircraft Dynamics Model'
 * '<S112>' : 'f14tmp25/Subsystem24/Controller'
 * '<S113>' : 'f14tmp25/Subsystem24/Dryden Wind Gust Models'
 * '<S114>' : 'f14tmp25/Subsystem24/Nz pilot calculation'
 * '<S115>' : 'f14tmp25/Subsystem24/Dryden Wind Gust Models/Band-Limited White Noise'
 * '<S116>' : 'f14tmp25/Subsystem3/Aircraft Dynamics Model'
 * '<S117>' : 'f14tmp25/Subsystem3/Controller'
 * '<S118>' : 'f14tmp25/Subsystem3/Dryden Wind Gust Models'
 * '<S119>' : 'f14tmp25/Subsystem3/Nz pilot calculation'
 * '<S120>' : 'f14tmp25/Subsystem3/Dryden Wind Gust Models/Band-Limited White Noise'
 * '<S121>' : 'f14tmp25/Subsystem4/Aircraft Dynamics Model'
 * '<S122>' : 'f14tmp25/Subsystem4/Controller'
 * '<S123>' : 'f14tmp25/Subsystem4/Dryden Wind Gust Models'
 * '<S124>' : 'f14tmp25/Subsystem4/Nz pilot calculation'
 * '<S125>' : 'f14tmp25/Subsystem4/Dryden Wind Gust Models/Band-Limited White Noise'
 * '<S126>' : 'f14tmp25/Subsystem5/Aircraft Dynamics Model'
 * '<S127>' : 'f14tmp25/Subsystem5/Controller'
 * '<S128>' : 'f14tmp25/Subsystem5/Dryden Wind Gust Models'
 * '<S129>' : 'f14tmp25/Subsystem5/Nz pilot calculation'
 * '<S130>' : 'f14tmp25/Subsystem5/Dryden Wind Gust Models/Band-Limited White Noise'
 * '<S131>' : 'f14tmp25/Subsystem6/Aircraft Dynamics Model'
 * '<S132>' : 'f14tmp25/Subsystem6/Controller'
 * '<S133>' : 'f14tmp25/Subsystem6/Dryden Wind Gust Models'
 * '<S134>' : 'f14tmp25/Subsystem6/Nz pilot calculation'
 * '<S135>' : 'f14tmp25/Subsystem6/Dryden Wind Gust Models/Band-Limited White Noise'
 * '<S136>' : 'f14tmp25/Subsystem7/Aircraft Dynamics Model'
 * '<S137>' : 'f14tmp25/Subsystem7/Controller'
 * '<S138>' : 'f14tmp25/Subsystem7/Dryden Wind Gust Models'
 * '<S139>' : 'f14tmp25/Subsystem7/Nz pilot calculation'
 * '<S140>' : 'f14tmp25/Subsystem7/Dryden Wind Gust Models/Band-Limited White Noise'
 * '<S141>' : 'f14tmp25/Subsystem8/Aircraft Dynamics Model'
 * '<S142>' : 'f14tmp25/Subsystem8/Controller'
 * '<S143>' : 'f14tmp25/Subsystem8/Dryden Wind Gust Models'
 * '<S144>' : 'f14tmp25/Subsystem8/Nz pilot calculation'
 * '<S145>' : 'f14tmp25/Subsystem8/Dryden Wind Gust Models/Band-Limited White Noise'
 * '<S146>' : 'f14tmp25/Subsystem9/Aircraft Dynamics Model'
 * '<S147>' : 'f14tmp25/Subsystem9/Controller'
 * '<S148>' : 'f14tmp25/Subsystem9/Dryden Wind Gust Models'
 * '<S149>' : 'f14tmp25/Subsystem9/Nz pilot calculation'
 * '<S150>' : 'f14tmp25/Subsystem9/Dryden Wind Gust Models/Band-Limited White Noise'
 */
#endif                                 /* RTW_HEADER_f14tmp25_h_ */
