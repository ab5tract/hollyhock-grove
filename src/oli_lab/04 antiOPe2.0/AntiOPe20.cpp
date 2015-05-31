//-----------------------------------------------------------------------------
//@file  
//	AntiOPe20.cpp
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
#include "AntiOPe20.h"

//----------------------------------------------------------------------------
// create, general info and destroy methodes
//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Create
void CreateModule (void* &pModule, AnsiCharPtr optionalString, LongBool Flag, MasterInfo* pMasterInfo, AnsiCharPtr optionalContent)
{
	pModule = new AntiOPe20();
}

// destroy
void DestroyModule(void* pModule) 
{
	// cast is important to call the good destructor
	delete ((AntiOPe20*) pModule);
}

//-------------------------------------------------------------------------
// module constructors/destructors
//-------------------------------------------------------------------------

// constructor
AntiOPe20::AntiOPe20()
{
	//
}

// destructor
AntiOPe20::~AntiOPe20()
{
	// 
}



//void TemplateModule::onCreate(AinsiCharPtr optionalString);
//void TemplateModule::onDestroy(); 
void AntiOPe20::onGetModuleInfo(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo)
{
	pModuleInfo->Name = "AntiOPe 2.0";
	pModuleInfo->Description = "AntiOPe 2.0";
	pModuleInfo->ModuleType         = mtSimple;
	pModuleInfo->BackColor			= sdkGetUsineColor(clInterfaceDesignModuleColor) + 0x101010;
	pModuleInfo->NumberOfParams     = 4;
	pModuleInfo->DontProcess = false;
	pModuleInfo->Version = "1.1";
}

//-----------------------------------------------------------------------------
// query system and init
int  AntiOPe20::onGetNumberOfParams(int QIdx) { return 0; }
void AntiOPe20::onAfterQuery(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo, int QIdx) {}
void AntiOPe20::onInitModule(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo) {}

//-----------------------------------------------------------------------------
// parameters and process
void AntiOPe20::onGetParamInfo(int ParamIndex, TParamInfo* pParamInfo)
{	
	switch (ParamIndex) 
    {
        // Add all parameters declared in the module class, example :

        // m_txtfExample
        case 0:
			pParamInfo->ParamType = ptTextField;
            pParamInfo->Caption   = "string input";
            pParamInfo->IsInput   = TRUE;
            pParamInfo->IsOutput  = FALSE;
            break;
		case 1:
			pParamInfo->ParamType = ptDataField;
			pParamInfo->Caption = "doSend";
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
		case 2:
			pParamInfo->ParamType = ptDataField;
			pParamInfo->Caption = "send";
			pParamInfo->IsInput = FALSE;
			pParamInfo->IsOutput = TRUE
				;
			break;
		case 3:
			pParamInfo->ParamType = ptTextField;
			pParamInfo->Caption = "Data to OSC";
			pParamInfo->IsInput = FALSE;
			pParamInfo->IsOutput = TRUE;
			break;
		// default case
	   default:
		break;
	}
}
void AntiOPe20::onSetEventAddress(int ParamIndex, UsineEventPtr pEvent)
{
	switch (ParamIndex) 
    {
        // Initialise all events adress declared in your module class, Example :
    
        // 
        case 0:
            m_textInput = pEvent;
            break;
		case 1:
			m_receivedSendOrder = pEvent;
			break;
		case 2:
			m_SendOrderToOSCModule = pEvent;
			break;
		case 3:
			m_textOutput = pEvent;
			break;
	// default case
	default:
		break;
	}
}


void AntiOPe20::onCallBack(UsineMessage *Message)
{
	
	if ((Message->wParam == 1) && (Message->lParam == MSG_CHANGE) && (sdkGetEvtData(m_receivedSendOrder) == 1)) // && (Message->result == 1)) //received 1 on "enable" input
	{
			m_textNew = sdkGetEvtPChar(m_textInput); //
			std::string str(m_textNew);
			int firstChar(0);
			for (unsigned i = 0; i < str.length(); ++i)
			{
				char m_simplechar = str.at(i);
				if (m_simplechar == ',') {
					std::string strToSend = str.substr(firstChar, i - (1 + firstChar)); // a string between 2 commas
					firstChar = i+1; // the index of the string to start the next subtring
					sdkSetEvtPChar(m_textOutput, (AnsiCharPtr) (strToSend.c_str()));
					sdkSetEvtData(m_SendOrderToOSCModule, 1);
					//wait one cycle here
					sdkTraceChar("sending to MINITEL");
                    // replaced Windows-specific _sleep for the std-library version.
                    // as such, this module requires OS X 10.7 on Mac.
					std::this_thread::sleep_for( std::chrono::milliseconds(160) );
					sdkSetEvtData(m_SendOrderToOSCModule, 0);
					}
				else{}
			}

	}

	else{}
	
}

void AntiOPe20::onProcess() {





}

//-----------------------------------------------------------------------------
// midi out callbacks
void AntiOPe20::onMidiSendOut(int DeviceID, UsineMidiCode Code) {}
void AntiOPe20::onMidiSysexSendOut(int DeviceID, char* Sysex) {}

//-----------------------------------------------------------------------------
// chunk system
int  AntiOPe20::onGetChunkLen(LongBool Preset) { return 0; }
void AntiOPe20::onGetChunk(void* chunk, LongBool Preset) {}
void AntiOPe20::onSetChunk(const void* chunk, int sizeInBytes, LongBool Preset) {}

//-----------------------------------------------------------------------------
// layout
void AntiOPe20::onCreateSettings() {}
void AntiOPe20::onSettingsHasChanged() {}
void AntiOPe20::onPaint() {}

//-----------------------------------------------------------------------------
// mouse and multi touch interaction
void AntiOPe20::onMouseMove(TShiftState Shift, float X, float Y) {}
void AntiOPe20::onMouseDown(TMouseButton MouseButton, TShiftState Shift, float X, float Y) {}
void AntiOPe20::onMouseUp(TMouseButton MouseButton, TShiftState Shift, float X, float Y) {}
void AntiOPe20::onMouseMoveMultiProc(TShiftState Shift, UsineEventPtr X, UsineEventPtr Y) {}
void AntiOPe20::onMouseDownMultiProc(TMouseButton MouseButton, TShiftState Shift, UsineEventPtr X, UsineEventPtr Y) {}
void AntiOPe20::onMouseUpMultiProc(TMouseButton MouseButton, TShiftState Shift, UsineEventPtr X, UsineEventPtr Y) {}
void AntiOPe20::onOpenEditor() {}
void AntiOPe20::onBringToFront() {}

//-----------------------------------------------------------------------------
// audio setup update
void AntiOPe20::onBlocSizeChange(int BlocSize) {}
void AntiOPe20::onSampleRateChange(double SampleRate) {}

//-----------------------------------------------------------------------------
// recording 
void AntiOPe20::onSetRecordedValue(TPrecision X, TPrecision Y, TPrecision Z) {}
