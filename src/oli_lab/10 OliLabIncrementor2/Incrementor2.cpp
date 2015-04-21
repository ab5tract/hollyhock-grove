//-----------------------------------------------------------------------------
//@file  
//	Incrementor2.cpp
//
//@author
//  Oli_Lab with precious help from
//	Martin FLEURENT aka 'martignasse'
//
//@brief 
//	Implementation of the Incrementor class.
//
//
//@historic 
//	2013/06/28
//    first release for Hollyhock CPP SDK 6.00.226 
//
//@IMPORTANT
//	This file is part of the Usine Hollyhock CPP SDK
//
//  Please, report bugs and patch to Usine forum :
//  http://www.sensomusic.com/wiki2/doku.php?id=hollyhock:bugsreport 
//
// All dependencies are under there own licence.
//
//@LICENCE
// Copyright (C) 2013 Sensomusic
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy of 
// this software and associated documentation files (the "Software"), 
// to deal in the Software without restriction, including without limitation 
// the rights to use, copy, modify, merge, publish, distribute, sublicense, 
// and/or sell copies of the Software, and to permit persons to whom the Software 
// is furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all 
//     copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
// SOFTWARE.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include "Incrementor2.h"

//----------------------------------------------------------------------------
// create, general info and destroy methodes
//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Create
void CreateModule (void* &pModule, AnsiCharPtr optionalString, LongBool Flag, MasterInfo* pMasterInfo, AnsiCharPtr optionalContent)
{
	pModule = new Incrementor();
}

// destroy
void DestroyModule(void* pModule) 
{
	// cast is important to call the good destructor
	delete ((Incrementor*)pModule);
}

//-------------------------------------------------------------------------
// module constructors/destructors
//-------------------------------------------------------------------------

// constructor
Incrementor::Incrementor()
{
	//
}

// destructor
Incrementor::~Incrementor()
{
	// 
}



//void Incrementor::onCreate(AinsiCharPtr optionalString);
//void Incrementor::onDestroy(); 
void Incrementor::onGetModuleInfo (MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo)
{
	pModuleInfo->Name				= "Incrementor - modulo";
	pModuleInfo->Description		= "Data - Incrementor";
	pModuleInfo->ModuleType         = mtSimple;
	pModuleInfo->BackColor			= sdkGetUsineColor(clInterfaceDesignModuleColor) + 0x101010;
	pModuleInfo->NumberOfParams     = 7;
	pModuleInfo->DontProcess		= false;
    pModuleInfo->Version			= "2.1";
}

//-----------------------------------------------------------------------------
// query system and init
int  Incrementor::onGetNumberOfParams( int QIdx) {return 0;}
void Incrementor::onAfterQuery (MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo, int QIdx) {}
void Incrementor::onInitModule (MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo) {}

//-----------------------------------------------------------------------------
// parameters and process
void Incrementor::onGetParamInfo (int ParamIndex, TParamInfo* pParamInfo)
{	
	switch (ParamIndex) 
    {
//  Add all parameters declared in the module class, example :

    // minus input
	case 0:
		pParamInfo->ParamType		= ptDataField;
		pParamInfo->Caption			= "add";
		//pParamInfo->DefaultValue    = 0;
		pParamInfo->IsInput			= true;
		pParamInfo->IsOutput		= false;
		pParamInfo->ReadOnly		= false;
		//pParamInfo->MinValue		= 0;
		//pParamInfo->MaxValue		= 1;
		break;
    // positive input
	case 1:
		pParamInfo->ParamType		= ptDataField;
		pParamInfo->Caption			= "sub";
		//pParamInfo->DefaultValue    = 0;
		pParamInfo->IsInput			= true;
		pParamInfo->IsOutput		= false;
		pParamInfo->ReadOnly		= false;
		//pParamInfo->MinValue		= 0;
		//pParamInfo->MaxValue		= 1;
		break;

    // resolution input
	case 2:
		pParamInfo->ParamType		= ptDataFader;
		pParamInfo->Caption			= "modulo";
		pParamInfo->DefaultValue    = 1000;
		pParamInfo->IsInput			= true;
		pParamInfo->IsOutput		= false;
		pParamInfo->ReadOnly		= false;
		pParamInfo->Format          = DEFAULT_FORMAT_INTEGER;
		pParamInfo->MinValue		= 1;
		pParamInfo->MaxValue		= 1000000;
		break;

    // reset value
	case 3:
		pParamInfo->ParamType		= ptDataFader;
		pParamInfo->Caption			= "reset value";
		pParamInfo->DefaultValue    = 0;
		pParamInfo->IsInput			= true;
		pParamInfo->IsOutput		= false;
		pParamInfo->ReadOnly		= false;
		pParamInfo->Format          = DEFAULT_FORMAT_FLOAT_2;
		pParamInfo->MinValue		= 0;
		pParamInfo->MaxValue		= 1000000;
		break;
    // reset input
	case 4:
		pParamInfo->ParamType		= ptButton;
		pParamInfo->Caption			= "reset";
		pParamInfo->IsInput			= true;
		pParamInfo->IsOutput		= false;
		pParamInfo->ReadOnly		= false;
		pParamInfo->MinValue		= 0;
		pParamInfo->MaxValue		= 1;
		break;
    // output
	case 5:
		pParamInfo->ParamType		= ptDataField;
		pParamInfo->Caption			= "out 1";
		pParamInfo->IsInput			= false;
		pParamInfo->IsOutput		= true;
		pParamInfo->ReadOnly		= true;
		pParamInfo->DefaultValue    = 0;
		pParamInfo->Format          = "%.5f"; //DEFAULT_FORMAT_FLOAT_2;
		pParamInfo->MinValue		= 0;
		pParamInfo->MaxValue		= 1;
		break;
    case 6:
		pParamInfo->ParamType		= ptDataField;
		pParamInfo->Caption			= "out abs";
		pParamInfo->IsInput			= false;
		pParamInfo->IsOutput		= true;
		pParamInfo->ReadOnly		= true;
		pParamInfo->DefaultValue    = 0;
		pParamInfo->Format          = DEFAULT_FORMAT_INTEGER;
		pParamInfo->MinValue		= 0;
		pParamInfo->MaxValue		= 1000000;
		break;
		// default case
	default:
		break;
	}
}
void Incrementor::onSetEventAddress (int ParamIndex, UsineEventPtr pEvent)
{
	switch (ParamIndex) 
    {
//  Initialyse all events adress declared in your module class, Example :
	
    // +1 input
	case 0:
		positiveInput = pEvent;
		break;
    // -1 input
	case 1:
		minusInput = pEvent;
		break;
	case 2:
		resolutionInput = pEvent;
		break;
	case 3:
		resetValueInput = pEvent;
		break;
	case 4:
		resetInput = pEvent;
		break;
	case 5:
		output = pEvent;
		break;
	case 6:
		internalOutput = pEvent;
		break;
	// default case
	default:
		break;
	}
}
void Incrementor::onCallBack (UsineMessage *Message) 
{
	if ((Message->wParam == 0) && (Message->lParam == MSG_CHANGE))
    {
        sdkAddEvt3       (internalOutput, positiveInput, internalOutput);
		
		if (sdkGetEvtData(internalOutput) > sdkGetEvtData(resolutionInput)) 
		{
			sdkSetEvtData(internalOutput, 0);
		}
		else if (sdkGetEvtData(internalOutput) < 0)
		{
			sdkSetEvtData(internalOutput, sdkGetEvtData(resolutionInput));
		}
		sdkDivEvt3       (internalOutput, resolutionInput, output);
    }

    if ((Message->wParam == 1) && (Message->lParam == MSG_CHANGE))
    {
        sdkSubEvt3       (internalOutput, minusInput, internalOutput);

		if (sdkGetEvtData(internalOutput) > sdkGetEvtData(resolutionInput)) 
		{
			sdkSetEvtData(internalOutput, sdkGetEvtData(resolutionInput));
		}
		else if (sdkGetEvtData(internalOutput) < 0) 
		{
			sdkSetEvtData(internalOutput, 0);
		}
		sdkDivEvt3       (internalOutput, resolutionInput, output);
    }

    if (((Message->wParam == 2) || (Message->wParam == 3)) && (Message->lParam == MSG_CHANGE))
    {
		if (sdkGetEvtData(resetValueInput) > sdkGetEvtData(resolutionInput)) 
		{
            sdkSetEvtData(resetValueInput, sdkGetEvtData(resolutionInput));
		}
	}
	if ((Message->wParam == 4) && (Message->lParam == MSG_CHANGE))
    {
		if (sdkGetEvtData(resetValueInput) > sdkGetEvtData(resolutionInput)) 
		{
            sdkSetEvtData(resetValueInput, sdkGetEvtData(resolutionInput));
		}
		sdkSetEvtData(internalOutput, sdkGetEvtData(resetValueInput));
		sdkDivEvt3       (internalOutput, resolutionInput, output);
    }

}
void Incrementor::onProcess () 
{

}

//-----------------------------------------------------------------------------
// midi out callbacks
//void Incrementor::onMidiSendOut (int DeviceID, UsineMidiCode Code) {}
//void Incrementor::onMidiSysexSendOut (int DeviceID, char* Sysex) {}

//-----------------------------------------------------------------------------
// chunk system
int  Incrementor::onGetChunkLen (LongBool Preset) {return 0;}
void Incrementor::onGetChunk (void* chunk, LongBool Preset) {}
void Incrementor::onSetChunk (const void* chunk, int sizeInBytes, LongBool Preset) {}

//-----------------------------------------------------------------------------
// layout
void Incrementor::onCreateSettings() {}
void Incrementor::onSettingsHasChanged() {}
void Incrementor::onPaint () {}

//-----------------------------------------------------------------------------
// mouse and multi touch interaction
//void Incrementor::onMouseMove(TShiftState Shift, float X, float Y) {}
//void Incrementor::onMouseDown(TMouseButton MouseButton, TShiftState Shift, float X,float Y) {}
//void Incrementor::onMouseUp (TMouseButton MouseButton, TShiftState Shift, float X,float Y) {}
//void Incrementor::onMouseMoveMultiProc(TShiftState Shift, UsineEventPtr X, UsineEventPtr Y) {}
//void Incrementor::onMouseDownMultiProc(TMouseButton MouseButton, TShiftState Shift, UsineEventPtr X, UsineEventPtr Y) {}
//void Incrementor::onMouseUpMultiProc (TMouseButton MouseButton, TShiftState Shift,UsineEventPtr X, UsineEventPtr Y) {}
//void Incrementor::onOpenEditor() {}
//void Incrementor::onBringToFront() {}

//-----------------------------------------------------------------------------
// audio setup update
//void Incrementor::onBlocSizeChange (int BlocSize) {}
//void Incrementor::onSampleRateChange (double SampleRate) {}

//-----------------------------------------------------------------------------
// recording 
//void Incrementor::onSetRecordedValue (TPrecision X, TPrecision Y, TPrecision Z) {}
