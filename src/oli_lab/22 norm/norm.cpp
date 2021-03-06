//-----------------------------------------------------------------------------
//@file  
//	DoublePendulum.cpp
//
//@author
//	Martin FLEURENT aka 'martignasse'
//
//@brief 
//	Implementation of the DoublePendulum class.
//
//  A template include to start from whereit should start.
//
//@historic 
//	2013/07/02
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
#include "norm.h"
//#include <cmath>

//----------------------------------------------------------------------------
// create, general info and destroy methodes
//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Create
void CreateModule (void* &pModule, AnsiCharPtr optionalString, LongBool Flag, MasterInfo* pMasterInfo, AnsiCharPtr optionalContent)
{
	pModule = new vectorManip();
}

// destroy
void DestroyModule(void* pModule) 
{
	// cast is important to call the good destructor
	delete ((vectorManip*) pModule);
}

//-------------------------------------------------------------------------
// module constructors/destructors
//-------------------------------------------------------------------------

// constructor
vectorManip::vectorManip()
{
	//
}

// destructor
vectorManip::~vectorManip()
{
	// 
}



//void TemplateModule::onCreate(AinsiCharPtr optionalString);
//void TemplateModule::onDestroy(); 
void vectorManip::onGetModuleInfo(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo)
{
	pModuleInfo->Name = "vector_Norm";
	pModuleInfo->Description = "distance between pad center and ball";
	pModuleInfo->ModuleType = mtSimple;
	pModuleInfo->BackColor = sdkGetUsineColor(clInterfaceDesignModuleColor) + 0x201020;
	pModuleInfo->NumberOfParams = 3;
	pModuleInfo->DontProcess = TRUE;
	pModuleInfo->Version	= "1.0";
}
//-----------------------------------------------------------------------------
// query system and init
int  vectorManip::onGetNumberOfParams(int QIdx) { return 0; }
void vectorManip::onAfterQuery(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo, int QIdx) {}
void vectorManip::onInitModule(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo) {}



//-----------------------------------------------------------------------------
// parameters and process
void vectorManip::onGetParamInfo(int ParamIndex, TParamInfo* pParamInfo)
{	
	switch (ParamIndex)
    {
        // Add all parameters declared in the module class, example :

		case 0:
			pParamInfo->ParamType = ptDataFader;
			pParamInfo->Caption = "X";
			pParamInfo->MinValue = 0.0f;
			pParamInfo->MaxValue = 1.0f;
			pParamInfo->DefaultValue = 0.5f;
			pParamInfo->Format = "%.6f";
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
		case 1:
			pParamInfo->ParamType = ptDataFader;
			pParamInfo->Caption = "Y";
			pParamInfo->MinValue = 0.0f;
			pParamInfo->MaxValue = 1.0f;
			pParamInfo->DefaultValue = 0.5f;
			pParamInfo->Format = "%.6f";
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
		//outputs
		case 2:
			pParamInfo->ParamType = ptDataField;
			pParamInfo->Caption = "norm";
			pParamInfo->Format = "%.6f";
			pParamInfo->IsInput = FALSE;
			pParamInfo->IsOutput = TRUE;
			break;
		// default case
	default:
		break;
	}
}
void vectorManip::onSetEventAddress(int ParamIndex, UsineEventPtr pEvent)
{
	switch (ParamIndex) 
    {
        // Initialise all events adress declared in your module class, Example :

		case 0:
			m_X = pEvent;       // 
			break;
		case 1:
			m_Y = pEvent;       // 
			break;
		case 2:
			m_norm = pEvent;       // 
			break;
	// default case
	    default:
		    break;
	}
}
void vectorManip::onCallBack(UsineMessage *Message) {
	//algo ici
	if ((Message->message == NOTIFY_MSG_USINE_CALLBACK) && (Message->lParam == MSG_CHANGE))
	{
		
		switch (Message->wParam)
		{
		case 0:
			X = sdkGetEvtData(m_X);
			computeNewNorm();
			break;
		case 1:
			Y = sdkGetEvtData(m_Y);
			computeNewNorm();
			break;
		}
		
    }

}


void vectorManip::onProcess() {}

void vectorManip::computeNewNorm()//(TPrecision rotationAngle, TPrecision x, TPrecision y)
{
	norme = pow((pow((X-0.5f)*2.0f, 2) + pow((Y-0.5f)*2.0f, 2)),0.5f);
	sdkSetEvtData(m_norm, norme);
}

//-----------------------------------------------------------------------------
// midi out callbacks
void vectorManip::onMidiSendOut(int DeviceID, UsineMidiCode Code) {}
void vectorManip::onMidiSysexSendOut(int DeviceID, char* Sysex) {}

//-----------------------------------------------------------------------------
// chunk system
int  vectorManip::onGetChunkLen(LongBool Preset) { return 0; }
void vectorManip::onGetChunk(void* chunk, LongBool Preset) {}
void vectorManip::onSetChunk(const void* chunk, int sizeInBytes, LongBool Preset) {}

//-----------------------------------------------------------------------------
// layout
void vectorManip::onCreateSettings() {}
void vectorManip::onSettingsHasChanged() {}
void vectorManip::onPaint() {}

//-----------------------------------------------------------------------------
// mouse and multi touch interaction
void vectorManip::onMouseMove(TShiftState Shift, float X, float Y) {}
void vectorManip::onMouseDown(TMouseButton MouseButton, TShiftState Shift, float X, float Y) {}
void vectorManip::onMouseUp(TMouseButton MouseButton, TShiftState Shift, float X, float Y) {}
void vectorManip::onMouseMoveMultiProc(TShiftState Shift, UsineEventPtr X, UsineEventPtr Y) {}
void vectorManip::onMouseDownMultiProc(TMouseButton MouseButton, TShiftState Shift, UsineEventPtr X, UsineEventPtr Y) {}
void vectorManip::onMouseUpMultiProc(TMouseButton MouseButton, TShiftState Shift, UsineEventPtr X, UsineEventPtr Y) {}
void vectorManip::onOpenEditor() {}
void vectorManip::onBringToFront() {}

//-----------------------------------------------------------------------------
// audio setup update
void vectorManip::onBlocSizeChange(int BlocSize) {}
void vectorManip::onSampleRateChange(double SampleRate) {}

//-----------------------------------------------------------------------------
// recording 
void vectorManip::onSetRecordedValue(TPrecision X, TPrecision Y, TPrecision Z) {}
