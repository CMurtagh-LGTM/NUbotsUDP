#define S_FUNCTION_NAME  SfunProtobufEncode
#define S_FUNCTION_LEVEL 2
#include "simstruc.h"

#include "Vector.pb.h"
#include <string>
//#include <iostream>

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
    
    //ssSetInputPortWidth(S,0,256);
    ssSetInputPortWidth(S,0,16);
    ssSetInputPortDirectFeedThrough(S, 0, 1);

    if (!ssSetNumOutputPorts(S,1)) return;
    ssSetOutputPortWidth(S, 0, 256);
    ssSetOutputPortDataType(S, 1, SS_UINT8);
    //ssSetOutputPortWidth(S, 0, DYNAMICALLY_SIZED);
    //ssSetOutputPortDimensionsMode(S, 0, VARIABLE_DIMS_MODE);
    
    //DimsInfo_T outputDimsInfo;
    //int_T dims[1];
    //dims[0] = DYNAMICALLY_SIZED;

    //outputDimsInfo.numDims = 1;
    //outputDimsInfo.dims = dims;
    //outputDimsInfo.width = DYNAMICALLY_SIZED;
    
    //ssSetOutputPortDimensionInfo(S, 0, &outputDimsInfo);
    
    ssSetNumSampleTimes(S, 1);

    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
}

static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);
}

static void mdlOutputs(SimStruct *S, int_T tid)
{
    InputRealPtrsType inputs = ssGetInputPortRealSignalPtrs(S,0);
    
    vec16 protobufobj;
    
    //std::cout << inputs[0][15] << std::endl;

    protobufobj.set_s0(inputs[0][0]);
    protobufobj.set_s1(inputs[0][1]);
    protobufobj.set_s2(inputs[0][2]);
    protobufobj.set_s3(inputs[0][3]);
    protobufobj.set_s4(inputs[0][4]);
    protobufobj.set_s5(inputs[0][5]);
    protobufobj.set_s6(inputs[0][6]);
    protobufobj.set_s7(inputs[0][7]);
    protobufobj.set_s8(inputs[0][8]);
    protobufobj.set_s9(inputs[0][9]);
    protobufobj.set_sa(inputs[0][10]);
    protobufobj.set_sb(inputs[0][11]);
    protobufobj.set_sc(inputs[0][12]);
    protobufobj.set_sd(inputs[0][13]);
    protobufobj.set_se(inputs[0][14]);
    protobufobj.set_sf(inputs[0][15]);

    std::string buffer = std::string();
    protobufobj.SerializeToString(&buffer);
    
    //std::cout << "Output: " << buffer << std::endl;
    
    //ssSetOutputPortWidth(S,0,buffer.length());
    //ssSetCurrentOutputPortDimensions(S,0,0,buffer.length());
    
    uint8_T *output = (uint8_T*)ssGetOutputPortSignal(S,0);
    
    //std::string *output = (std::string*)ssGetOutputPortSignal(S,0);
    
    //protobufobj.SerializeToString(output);
    
    for (int i = 0; i < buffer.length(); i++) {
        output[i] = buffer[i];
    }
    
    UNUSED_ARG(tid);
}

static void mdlTerminate(SimStruct *S)
{
    UNUSED_ARG(S);
}

#ifdef MATLAB_MEX_FILE    /* Is this file being compiled as a 
                             MEX-file? */
#include "simulink.c"     /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"      /* Code generation registration 
                             function */
#endif