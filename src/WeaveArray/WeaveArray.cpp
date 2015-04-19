//-----------------------------------------------------------------------------
//@file  
//	WeaveArray.cpp
//
//@author
//	ab5tract
//
//@brief 
//	Implementation of the WeaveArray class.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include "WeaveArray.h"

//----------------------------------------------------------------------------
// create, general info and destroy methodes
//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Create
void CreateModule (void* &pModule, AnsiCharPtr optionalString, LongBool Flag, MasterInfo* pMasterInfo, AnsiCharPtr optionalContent)
{
	pModule = new WeaveArray ();
}

//-----------------------------------------------------------------------------
// destroy
void DestroyModule (void* pModule) 
{
    // cast is important to call the good destructor
	delete ((WeaveArray*)pModule);
}

//-----------------------------------------------------------------------------
// module description
void WeaveArray::onGetModuleInfo (MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo) 
{

	//identification of the module
	pModuleInfo->Name				= "weave array";
	pModuleInfo->Description		= "Weave Arrays";
	pModuleInfo->ModuleType         = mtSimple;
	pModuleInfo->BackColor          = sdkGetUsineColor(clDataModuleColor);
	pModuleInfo->NumberOfParams     = 3;
	pModuleInfo->Version			= "1.0";
	pModuleInfo->DontProcess		= TRUE;
}

//-----------------------------------------------------------------------------
// query system and init methodes
//-----------------------------------------------------------------------------
// query system not used

//void WeaveArray::onInitModule (MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo) 
//{
//}

//----------------------------------------------------------------------------
// parameters and process
//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Parameters description
void WeaveArray::onGetParamInfo (int ParamIndex, TParamInfo* pParamInfo) 
{
	// all parameters declared in the module class		
	switch (ParamIndex) 
	{
	// waInput1
	case 0:
		pParamInfo->ParamType		= ptArray;
		pParamInfo->Caption			= "array 1";
		pParamInfo->IsInput			= TRUE;
		pParamInfo->IsOutput		= FALSE;
        pParamInfo->MinValue		= - FLT_MAX;
        pParamInfo->MaxValue		= FLT_MAX;
		pParamInfo->CallBackType	= ctImmediate;
		break;

	// waInput2
	case 1:
		pParamInfo->ParamType		= ptArray;
		pParamInfo->Caption			= "array 2";
		pParamInfo->IsInput			= TRUE;
		pParamInfo->IsOutput		= FALSE;
        pParamInfo->MinValue		= - FLT_MAX;
        pParamInfo->MaxValue		= FLT_MAX;
		pParamInfo->CallBackType	= ctImmediate;
		break;

	// waOutput
	case 2:
		pParamInfo->ParamType		= ptArray;
		pParamInfo->Caption			= "output";
		pParamInfo->IsInput			= FALSE;
		pParamInfo->IsOutput		= TRUE;
        pParamInfo->MinValue		= - FLT_MAX;
        pParamInfo->MaxValue		= FLT_MAX;
        pParamInfo->CallBackType	= ctImmediate;
		break;

	// default case
	default:
		break;
	}
}

//-----------------------------------------------------------------------------
// set the parameters events address
void WeaveArray::onSetEventAddress (int ParamIndex, UsineEventPtr pEvent) 
{
	
	//Initialyse all events adress declared in your module class
	switch (ParamIndex) 
    {
	// waInput1
	case 0:
		waInput1 = pEvent;
		break;

	// waInput2
	case 1:
		waInput2 = pEvent;
		break;

	// waOutput
	case 2:
		waOutput = pEvent;
		break;

	// default case
	default:
		break;

	}
}

//-----------------------------------------------------------------------------
// Parameters callback
void WeaveArray::onCallBack (UsineMessage* Message) 
{
	try
	{
        if (Message->message == NOTIFY_MSG_USINE_CALLBACK)
        {
            int paramIndex = (int)Message->wParam;

            if((paramIndex == 0 || paramIndex == 1) && Message->lParam == MSG_CHANGE)
            {
                input1Length = sdkGetEvtSize(waInput1);
                input2Length = sdkGetEvtSize(waInput2);
                outputLength = input1Length + input2Length;
                writeOutput();
            }
        }
	}
	catch (...)
	{
		//sdkTraceErrorChar("error");
	}
}

void WeaveArray::writeOutput()
{
    sdkSetEvtSize(waOutput, outputLength);
    int i;
    int r = 0;

    if ( input1Length <= input2Length )
    {
        for ( i=0; i < input1Length; i++ )
        {
            sdkSetEvtArrayData(waOutput, r++, sdkGetEvtArrayData(waInput1, i));
            sdkSetEvtArrayData(waOutput, r++, sdkGetEvtArrayData(waInput2, i));
        }
        
        for ( i=input1Length; i < input2Length; i++ )
        {
            sdkSetEvtArrayData(waOutput, r++, sdkGetEvtArrayData(waInput2,i));
        }
    }
    else
    {
        for ( i=0; i < input2Length; i++ )
        {
            sdkSetEvtArrayData(waOutput, r++, sdkGetEvtArrayData(waInput1, i));
            sdkSetEvtArrayData(waOutput, r++, sdkGetEvtArrayData(waInput2, i));
        }
        
        for ( i=input2Length; i < input1Length; i++ )
        {
            sdkSetEvtArrayData(waOutput, r++, sdkGetEvtArrayData(waInput1,i));
        }
    }
}
