#include "cxapiSelectNegativeFaceCmd.h"
#include "cxapiSimpleHelloWorldCmd.h"
#include <maya/MFnPlugin.h>
#include <maya/MGlobal.h>

MStatus initializePlugin(MObject mobj)
{
	MStatus stat;
    MFnPlugin fn_plugin(mobj);
    stat = fn_plugin.registerCommand(
         CxApiSimpleHelloWorldCmd::kCmdName,
         CxApiSimpleHelloWorldCmd::creator
    );
    if (stat != MS::kSuccess)
    {
        MGlobal::displayError(MString("Failed to register command : ") + CxApiSimpleHelloWorldCmd::kCmdName);
    }

    stat = fn_plugin.registerCommand(
        CxApiSelectNegativeFaceCmd::kCmdName,
        CxApiSelectNegativeFaceCmd::creator,
        CxApiSelectNegativeFaceCmd::new_syntax
    );
    if (stat != MS::kSuccess)
    {
        MGlobal::displayError(MString("Failed to register command : ") + CxApiSelectNegativeFaceCmd::kCmdName);
    }
    return stat;
}

MStatus uninitializePlugin(MObject mobj)
{
    MStatus stat;
    MFnPlugin fn_plugin(mobj);
    stat = fn_plugin.deregisterCommand(CxApiSimpleHelloWorldCmd::kCmdName);
    if (stat != MS::kSuccess)
    {
        MGlobal::displayError(MString("Failed to deregister command : ") + CxApiSimpleHelloWorldCmd::kCmdName);
    }

    stat = fn_plugin.deregisterCommand(CxApiSelectNegativeFaceCmd::kCmdName);
    if (stat != MS::kSuccess)
    {
        MGlobal::displayError(MString("Failed to deregister command : ") + CxApiSelectNegativeFaceCmd::kCmdName);
    }
	return stat;
}
