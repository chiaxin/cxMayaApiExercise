//
//  cxapiSimpleHelloWorldCmd.h
//  cxMayaApiExercise
//
//  Created by ChiaXin on 2019/3/8.
//

#ifndef cxapiSimpleHelloWorldCmd_h
#define cxapiSimpleHelloWorldCmd_h

#include <maya/MPxCommand.h>

class CxApiSimpleHelloWorldCmd : public MPxCommand
{
public:
    CxApiSimpleHelloWorldCmd();
    virtual ~CxApiSimpleHelloWorldCmd();
    static const char * kCmdName;
    static void * creator();
    MStatus doIt(const MArgList &);
};


#endif /* cxapiSimpleHelloWorldCmd_h */
