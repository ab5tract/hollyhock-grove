//-----------------------------------------------------------------------------
//@file  
//	StringFlip.cpp
//
//@author
//  Oli_Lab with precious help from
//	Martin FLEURENT aka 'martignasse'
//
//@brief 
//
//
//@historic 
//	2013/05/15
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
#include "stringFlip.h"

//----------------------------------------------------------------------------
// create, general info and destroy methodes
//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Create
void CreateModule (void* &pModule, AnsiCharPtr optionalString, LongBool Flag, MasterInfo* pMasterInfo, AnsiCharPtr optionalContent)
{
	pModule = new StringFlip();
}

// destroy
void DestroyModule(void* pModule) 
{
	// cast is important to call the good destructor
	delete ((StringFlip*) pModule);
}

//-------------------------------------------------------------------------
// module constructors/destructors
//-------------------------------------------------------------------------

// constructor
StringFlip::StringFlip()
{
	//
}

// destructor
StringFlip::~StringFlip()
{
	// 
}



//void TemplateModule::onCreate(AinsiCharPtr optionalString);
//void TemplateModule::onDestroy(); 
void StringFlip::onGetModuleInfo(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo)
{
	pModuleInfo->Name				= "string flip";
	pModuleInfo->Description		= "flip string";
	pModuleInfo->ModuleType         = mtSimple;
	pModuleInfo->BackColor  = sdkGetUsineColor(clInterfaceDesignModuleColor) + 0x101010;
	pModuleInfo->NumberOfParams     = 4;
	pModuleInfo->DontProcess = false;
	pModuleInfo->Version = "1.1";
}

//-----------------------------------------------------------------------------
// query system and init
int  StringFlip::onGetNumberOfParams(int QIdx) { return 0; }
void StringFlip::onAfterQuery(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo, int QIdx) {}
void StringFlip::onInitModule(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo) {}

//-----------------------------------------------------------------------------
// parameters and process
void StringFlip::onGetParamInfo(int ParamIndex, TParamInfo* pParamInfo)
{	
	switch (ParamIndex) 
    {
        // Add all parameters declared in the module class, example :

        // m_txtfExample
        case 0:
			pParamInfo->ParamType = ptTextField;
            pParamInfo->Caption   = "Character in";
            pParamInfo->IsInput   = TRUE;
            pParamInfo->IsOutput  = FALSE;
            break;
		case 1:
			pParamInfo->ParamType = ptDataField;
			pParamInfo->Caption = "enable";
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
		case 2:
			pParamInfo->ParamType = ptDataField;
			pParamInfo->Caption = "clear string";
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
		case 3:
			pParamInfo->ParamType = ptTextField;
			pParamInfo->Caption = "text";
			pParamInfo->IsInput = FALSE;
			pParamInfo->IsOutput = TRUE;
			break;
		// default case
	   default:
		break;
	}
}
void StringFlip::onSetEventAddress(int ParamIndex, UsineEventPtr pEvent)
{
	switch (ParamIndex) 
    {
        // Initialise all events adress declared in your module class, Example :
    
        // 
        case 0:
            m_textInput = pEvent;
            break;
		case 1:
			m_enable = pEvent;
			break;
		case 2:
			m_reset = pEvent;
			break;
		case 3:
			m_textOutput = pEvent;
			break;
	// default case
	default:
		break;
	}
}


void StringFlip::onCallBack(UsineMessage *Message) 
{
	
	if ((Message->wParam == 1) && (Message->lParam == MSG_CHANGE)) // && (Message->result == 1)) //received 1 on "enable" input
	{
		if (sdkGetEvtData(m_enable) == 1)
		{
			m_textNew = sdkGetEvtPChar(m_textInput); //
			str.append(m_textNew);
			sdkSetEvtPChar(m_textOutput, (AnsiCharPtr)(str.c_str()));
			//sdkSetEvtPChar(m_textOutput, m_textNew);
		}
	}

	else if ((Message->wParam == 2) && (Message->lParam == MSG_CHANGE) ) //&& (Message->result == 1)) //received 1 on "reset" input
	{
		if (sdkGetEvtData(m_reset) == 1)
		{
			str.clear();
			sdkSetEvtPChar(m_textOutput, (AnsiCharPtr)(str.c_str()));
		}
	}
	else{}
	
}

void StringFlip::onProcess() {





}

//-----------------------------------------------------------------------------
// midi out callbacks
void StringFlip::onMidiSendOut(int DeviceID, UsineMidiCode Code) {}
void StringFlip::onMidiSysexSendOut(int DeviceID, char* Sysex) {}

//-----------------------------------------------------------------------------
// chunk system
int  StringFlip::onGetChunkLen(LongBool Preset) { return 0; }
void StringFlip::onGetChunk(void* chunk, LongBool Preset) {}
void StringFlip::onSetChunk(const void* chunk, int sizeInBytes, LongBool Preset) {}

//-----------------------------------------------------------------------------
// layout
void StringFlip::onCreateSettings() {}
void StringFlip::onSettingsHasChanged() {}
void StringFlip::onPaint() {}

//-----------------------------------------------------------------------------
// mouse and multi touch interaction
void StringFlip::onMouseMove(TShiftState Shift, float X, float Y) {}
void StringFlip::onMouseDown(TMouseButton MouseButton, TShiftState Shift, float X, float Y) {}
void StringFlip::onMouseUp(TMouseButton MouseButton, TShiftState Shift, float X, float Y) {}
void StringFlip::onMouseMoveMultiProc(TShiftState Shift, UsineEventPtr X, UsineEventPtr Y) {}
void StringFlip::onMouseDownMultiProc(TMouseButton MouseButton, TShiftState Shift, UsineEventPtr X, UsineEventPtr Y) {}
void StringFlip::onMouseUpMultiProc(TMouseButton MouseButton, TShiftState Shift, UsineEventPtr X, UsineEventPtr Y) {}
void StringFlip::onOpenEditor() {}
void StringFlip::onBringToFront() {}

//-----------------------------------------------------------------------------
// audio setup update
void StringFlip::onBlocSizeChange(int BlocSize) {}
void StringFlip::onSampleRateChange(double SampleRate) {}

//-----------------------------------------------------------------------------
// recording 
void StringFlip::onSetRecordedValue(TPrecision X, TPrecision Y, TPrecision Z) {}
