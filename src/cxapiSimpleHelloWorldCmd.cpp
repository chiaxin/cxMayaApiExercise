//
//  cxapiSimpleHelloWorldCmd.cpp
//  cxMayaApiExercise
//
//  Created by ChiaXin on 2019/3/8.
//

#include "cxapiSimpleHelloWorldCmd.h"
#include <maya/MGlobal.h>

const char * CxApiSimpleHelloWorldCmd::kCmdName = "cxSimpleHelloWorld";

CxApiSimpleHelloWorldCmd::CxApiSimpleHelloWorldCmd()
{
}

CxApiSimpleHelloWorldCmd::~CxApiSimpleHelloWorldCmd()
{
}

void * CxApiSimpleHelloWorldCmd::creator()
{
    return new CxApiSimpleHelloWorldCmd();
}

MStatus CxApiSimpleHelloWorldCmd::doIt(const MArgList & arg_list)
{
    MStatus stat;
    MGlobal::displayInfo("Hello, World!");
    return stat;
}
