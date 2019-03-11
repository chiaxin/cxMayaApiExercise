#include "cxapiSelectNegativeFaceCmd.h"

#include <maya/MPxCommand.h>
#include <maya/MSelectionList.h>
#include <maya/MDagPath.h>
#include <maya/MItMeshPolygon.h>
#include <maya/MFnSingleIndexedComponent.h>
#include <maya/MGlobal.h>
#include <maya/MPointArray.h>

const char * CxApiSelectNegativeFaceCmd::kCmdName = "cxSelectNegativeFace";

CxApiSelectNegativeFaceCmd::CxApiSelectNegativeFaceCmd()
{
    MGlobal::displayInfo("selectNegativeFace command loaded.");
}

CxApiSelectNegativeFaceCmd::~CxApiSelectNegativeFaceCmd()
{
    MGlobal::displayInfo("selectNegativeFace command unloaded.");
}

void * CxApiSelectNegativeFaceCmd::creator()
{
    return new CxApiSelectNegativeFaceCmd();
}

MStatus CxApiSelectNegativeFaceCmd::doIt(const MArgList & arg_list)
{
    MStatus stat;
    MSelectionList selection_list;
    MDagPath dag_path;
    MObject object;

    stat = MGlobal::getActiveSelectionList(selection_list);
    if (selection_list.length() > 0) {
        selection_list.getDagPath(0, dag_path);
        object = dag_path.node();
        MFnSingleIndexedComponent fn_sic;
        fn_sic.create(MFn::kMeshPolygonComponent);
        if (object.apiType() == MFn::kMesh) {
            MItMeshPolygon it_poly(dag_path);

            while (!it_poly.isDone()) {
                bool is_negative = false;
                MPointArray point_arr;
                it_poly.getPoints(point_arr, MSpace::kWorld, &stat);
                for (unsigned int idx = 0 ; idx < point_arr.length() ; idx++) {
                    if ((point_arr[idx].x + 0.005) < 0.0) {
                        is_negative = true;
                        break;
                    }
                }
                if (is_negative) {
                    fn_sic.addElement(it_poly.index());
                }
                it_poly.next();
            }

            MGlobal::clearSelectionList();
            MGlobal::select(dag_path, fn_sic.object());
        } else {
            MGlobal::displayWarning("Please select a mesh!");
        }
    }
    return stat;
}