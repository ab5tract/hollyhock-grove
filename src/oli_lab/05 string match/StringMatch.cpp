//-----------------------------------------------------------------------------
//@file  
//	StringMatch.cpp
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
#include "StringMatch.h"

//----------------------------------------------------------------------------
// create, general info and destroy methodes
//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Create
void CreateModule (void* &pModule, AnsiCharPtr optionalString, LongBool Flag, MasterInfo* pMasterInfo, AnsiCharPtr optionalContent)
{
	pModule = new StringMatch();
}

// destroy
void DestroyModule(void* pModule) 
{
	// cast is important to call the good destructor
	delete ((StringMatch*) pModule);
}

//-------------------------------------------------------------------------
// module constructors/destructors
//-------------------------------------------------------------------------

// constructor
StringMatch::StringMatch()
{
	//
}

// destructor
StringMatch::~StringMatch()
{
	// 
}



//void TemplateModule::onCreate(AinsiCharPtr optionalString);
//void TemplateModule::onDestroy(); 
void StringMatch::onGetModuleInfo(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo)
{
	pModuleInfo->Name = "String Match";
	pModuleInfo->Description = "Sring Match";
	pModuleInfo->ModuleType         = mtSimple;
	pModuleInfo->BackColor = sdkGetUsineColor(clInterfaceDesignModuleColor) + 0x101010;
	pModuleInfo->NumberOfParams     = 4;
	// pModuleInfo->NumberOfParams is supplied by the query system
	pModuleInfo->DontProcess = false;
	// for optional params
	//pModuleInfo->QueryString = "max inputs/outputs \?";
	//pModuleInfo->QueryListValues = "\"2 in out\",\"4 in out\",\"8 in out\",\"16 in out\",\"32 in out\"";
	//pModuleInfo->QueryDefaultIdx = 1;
	pModuleInfo->Version = "1.1";
}

//-----------------------------------------------------------------------------
// query system and init

int StringMatch::onGetNumberOfParams(int queryIndex) { return(0); }
void StringMatch::onAfterQuery(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo, int QIdx) {}
void StringMatch::onInitModule(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo) {}

//-----------------------------------------------------------------------------
// parameters and process
void StringMatch::onGetParamInfo(int ParamIndex, TParamInfo* pParamInfo)
{
	
	switch (ParamIndex) 
    {
        // Add all parameters declared in the module class, example :

        // m_txtfExample
        case 0:
			pParamInfo->ParamType = ptTextField;
            pParamInfo->Caption   = "string";
            pParamInfo->IsInput   = TRUE;
			pParamInfo->IsOutput = TRUE;
            break;
		case 1:
			pParamInfo->ParamType = ptTextField;
			pParamInfo->Caption = "test string";
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
		case 2:
			pParamInfo->ParamType = ptDataField;
			pParamInfo->Caption = "out comp";
			pParamInfo->IsInput = FALSE;
			pParamInfo->IsOutput = TRUE;
			break;
		case 3:
			pParamInfo->ParamType = ptDataField;
			pParamInfo->Caption = "bang!";
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = TRUE;
			break;
		// default case
	   default:
		break;
	}
}
void StringMatch::onSetEventAddress(int ParamIndex, UsineEventPtr pEvent)
{
	switch (ParamIndex) 
    {
        // Initialise all events adress declared in your module class, Example :
    
        // 
        case 0:
            m_textInput = pEvent;
            break;
		case 1:
			m_text2MatchInput = pEvent;
			break;
		case 2:
			m_comparatorResult = pEvent;
			break;
		case 3:
			m_bang = pEvent;
			break;
	// default case
	default:
		break;
	}
}


void StringMatch::onCallBack(UsineMessage *Message)
{
	
	if ((Message->wParam == 3) && (Message->lParam == MSG_CHANGE)) // && (Message->result == 1)) //received 1 on "enable" input
	{
		if (sdkGetEvtData(m_bang) == 1)
		{
			m_textIn = sdkGetEvtPChar(m_textInput); //
			m_text2Match = sdkGetEvtPChar(m_text2MatchInput); //
			std::string str1(m_textIn);
			std::string str2(m_text2Match);
			if (str1.compare(str2) == 0){
				sdkSetEvtData(m_comparatorResult, 1);
			}
			else {
			sdkSetEvtData(m_comparatorResult, 0);
		    }
		}
		else {

			sdkSetEvtData(m_comparatorResult, 0);
		}
	}
	else{}
	
}

void StringMatch::onProcess() {





}

//-----------------------------------------------------------------------------
// midi out callbacks
void StringMatch::onMidiSendOut(int DeviceID, UsineMidiCode Code) {}
void StringMatch::onMidiSysexSendOut(int DeviceID, char* Sysex) {}

//-----------------------------------------------------------------------------
// chunk system
int  StringMatch::onGetChunkLen(LongBool Preset) { return 0; }
void StringMatch::onGetChunk(void* chunk, LongBool Preset) {}
void StringMatch::onSetChunk(const void* chunk, int sizeInBytes, LongBool Preset) {}

//-----------------------------------------------------------------------------
// layout
void StringMatch::onCreateSettings() {}
void StringMatch::onSettingsHasChanged() {}
void StringMatch::onPaint() {}

//-----------------------------------------------------------------------------
// mouse and multi touch interaction
void StringMatch::onMouseMove(TShiftState Shift, float X, float Y) {}
void StringMatch::onMouseDown(TMouseButton MouseButton, TShiftState Shift, float X, float Y) {}
void StringMatch::onMouseUp(TMouseButton MouseButton, TShiftState Shift, float X, float Y) {}
void StringMatch::onMouseMoveMultiProc(TShiftState Shift, UsineEventPtr X, UsineEventPtr Y) {}
void StringMatch::onMouseDownMultiProc(TMouseButton MouseButton, TShiftState Shift, UsineEventPtr X, UsineEventPtr Y) {}
void StringMatch::onMouseUpMultiProc(TMouseButton MouseButton, TShiftState Shift, UsineEventPtr X, UsineEventPtr Y) {}
void StringMatch::onOpenEditor() {}
void StringMatch::onBringToFront() {}

//-----------------------------------------------------------------------------
// audio setup update
void StringMatch::onBlocSizeChange(int BlocSize) {}
void StringMatch::onSampleRateChange(double SampleRate) {}

//-----------------------------------------------------------------------------
// recording 
void StringMatch::onSetRecordedValue(TPrecision X, TPrecision Y, TPrecision Z) {}
