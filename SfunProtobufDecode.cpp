#define S_FUNCTION_NAME  SfunProtobufDecode
#define S_FUNCTION_LEVEL 2
#include "simstruc.h"

#include "Vector.pb.h"
#include <string>

static void mdlInitializeSizes(SimStruct *S)
{
    ssSetNumSFcnParams(S, 0);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        return; //Parameter mismatch reported by the Simulink engine
    }

    //Number of Input Ports
    if (!ssSetNumInputPorts(S, 1)) 
    {
        return;
    }
    
    //ssSetInputPortWidth(S,0,DYNAMICALLY_SIZED);
    ssSetInputPortWidth(S,0,1);
    ssSetInputPortDirectFeedThrough(S, 0, 1);

    if (!ssSetNumOutputPorts(S,1)) return;
    ssSetOutputPortWidth(S, 0, 16);
    
    ssSetNumSampleTimes(S, 1);

    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
}

static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);
}

/*#if defined(MATLAB_MEX_FILE)
#define MDL_SET_INPUT_PORT_DIMENSION_INFO
void mdlSetInputPortDimensionInfo(SimStruct *S, int_T port, const DimsInfo_T *dimsInfo)
{
    if(!ssSetInputPortDimensionInfo(S, port, dimsInfo)) return;
}

#define MDL_SET_OUTPUT_PORT_DIMENSION_INFO
void mdlSetOutputPortDimensionInfo(SimStruct *S, int_T port, const DimsInfo_T *dimsInfo)
{
    DimsInfo_T outputDimsInfo;
    int_T dims[1];
    dims[0] = 16;

    outputDimsInfo.numDims = 1;
    outputDimsInfo.dims = dims;
    outputDimsInfo.width = 16;
    
    ssSetOutputPortDimensionInfo(S, port, &outputDimsInfo);
}

#define MDL_SET_DEFAULT_PORT_DIMENSION_INFO
void mdlSetDefaultPortDimensionInfo(SimStruct *S)
{
    DimsInfo_T inputDimsInfo;
    int_T dimsi[1];
    dimsi[0] = 256;

    inputDimsInfo.numDims = 1;
    inputDimsInfo.dims = dimsi;
    inputDimsInfo.width = 256;
    
    mdlSetInputPortDimensionInfo(S, 0, &inputDimsInfo);
    
    DimsInfo_T outputDimsInfo;
    int_T dimso[1];
    dimso[0] = 16;

    outputDimsInfo.numDims = 1;
    outputDimsInfo.dims = dimso;
    outputDimsInfo.width = 16;
    
    ssSetOutputPortDimensionInfo(S, 0, &outputDimsInfo);
}
#endif*/

static void mdlOutputs(SimStruct *S, int_T tid)
{
    /*uint8_T *input = (uint8_T *)ssGetInputPortSignalPtrs(S,0);
    
    std::string buffer = std::string(*input,*input + ssGetCurrentInputPortWidth(S,0));*/
    
    std::string *buffer = (std::string *)ssGetInputPortSignalPtrs(S,0);
    
    vec16 protobufobj;
    protobufobj.ParseFromString(*buffer);
    
    real_T *output = ssGetOutputPortRealSignal(S,0);
    
    output[0] = protobufobj.s0();
    output[1] = protobufobj.s1();
    output[2] = protobufobj.s2();
    output[3] = protobufobj.s3();
    output[4] = protobufobj.s4();
    output[5] = protobufobj.s5();
    output[6] = protobufobj.s6();
    output[7] = protobufobj.s7();
    output[8] = protobufobj.s8();
    output[9] = protobufobj.s9();
    output[10] = protobufobj.sa();
    output[11] = protobufobj.sb();
    output[12] = protobufobj.sc();
    output[13] = protobufobj.sd();
    output[14] = protobufobj.se();
    output[15] = protobufobj.sf();
    
    UNUSED_ARG(tid);
}

static void mdlTerminate(SimStruct *S)
{
}

#ifdef MATLAB_MEX_FILE    /* Is this file being compiled as a 
                             MEX-file? */
#include "simulink.c"     /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"      /* Code generation registration 
                             function */
#endif