#include "cxapiSelectNegativeFaceCmd.h"

#include <maya/MPxCommand.h>
#include <maya/MSelectionList.h>
#include <maya/MDagPath.h>
#include <maya/MItMeshPolygon.h>
#include <maya/MFnSingleIndexedComponent.h>
#include <maya/MGlobal.h>
#include <maya/MPointArray.h>
#include <maya/MSyntax.h>
#include <maya/MArgDatabase.h>

const char * CxApiSelectNegativeFaceCmd::kCmdName = "cxSelectNegativeFace";
const char * kToleranceFlagSN = "-t";
const char * kToleranceFlagLN = "-tolerance";

CxApiSelectNegativeFaceCmd::CxApiSelectNegativeFaceCmd()
{
    MGlobal::displayInfo("selectNegativeFace command loaded.");
    tolerance = 0.005;
}

CxApiSelectNegativeFaceCmd::~CxApiSelectNegativeFaceCmd()
{
    MGlobal::displayInfo("selectNegativeFace command unloaded.");
}

void * CxApiSelectNegativeFaceCmd::creator()
{
    return new CxApiSelectNegativeFaceCmd();
}

MSyntax CxApiSelectNegativeFaceCmd::new_syntax()
{
    MSyntax syntax;
    MStatus stat;
    stat = syntax.addFlag(kToleranceFlagSN, kToleranceFlagLN, MSyntax::kDouble);
    return syntax;
}

MStatus CxApiSelectNegativeFaceCmd::parse_syntax(const MArgList & arg_list)
{
    MArgDatabase parser(syntax(), arg_list);
    MStatus stat;

    if (parser.isFlagSet(kToleranceFlagSN, &stat) && stat == MS::kSuccess)
    {
        stat = parser.getFlagArgument(kToleranceFlagSN, 0, tolerance);
        if (tolerance < 0.001 || tolerance > 1.0) {
            MGlobal::displayError("The tolerance must between 0.001 to 1.0!");
            return MS::kInvalidParameter;
        }
    }
    return stat;
}

MStatus CxApiSelectNegativeFaceCmd::doIt(const MArgList & arg_list)
{
    MStatus stat = parse_syntax(arg_list);

    if (stat != MS::kSuccess) {
        return stat;
    }

    MSelectionList selection_list;
    MSelectionList result_selection_list;
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
                    if ((point_arr[idx].x + tolerance) < 0.0) {
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
            MGlobal::getActiveSelectionList(result_selection_list);
        } else {
            MGlobal::displayWarning("Please select a mesh!");
        }
        MStringArray result_items;
        result_selection_list.getSelectionStrings(result_items);
        setResult(result_items);
    }
    return stat;
}