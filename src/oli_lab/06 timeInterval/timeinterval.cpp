//-----------------------------------------------------------------------------
//@file  
//	timeIntervalModule.cpp
//
//@author
//	Oli_Lab
//
//@brief 
//	Implementation of the DelayArrayModule class.
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
#include "timeinterval.h"

//----------------------------------------------------------------------------
// create, general info and destroy methodes
//----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Create module
void CreateModule (void* &pModule, AnsiCharPtr optionalString, LongBool Flag, MasterInfo* pMasterInfo, AnsiCharPtr optionalContent)
{
	pModule = new timeIntervalModule();
}

//-----------------------------------------------------------------------------
// destroy module
void DestroyModule (void* pModule) 
{
	// cast is important to call the good destructor
	delete ((timeIntervalModule*) pModule);
}

//-----------------------------------------------------------------------------
timeIntervalModule::timeIntervalModule()
{
}

//-----------------------------------------------------------------------------------------
timeIntervalModule::~timeIntervalModule()
{	
}


//void DelayArrayModule::onCreate(AinsiCharPtr optionalString);
//void DelayArrayModule::onDestroy(); 
void timeIntervalModule::onGetModuleInfo(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo)
{
	pModuleInfo->Name				= "timeInterval";
	pModuleInfo->Description		= "time interval";
	pModuleInfo->ModuleType         = mtSimple;
	pModuleInfo->BackColor			= sdkGetUsineColor(clInterfaceDesignModuleColor) + 0x101010;
	pModuleInfo->NumberOfParams     = 2;
	pModuleInfo->Version			= "1.0";
}

//-----------------------------------------------------------------------------
// query system and init
//int  DelayArrayModule::onGetNumberOfParams( int queryIndex) {return 0;}
//void DelayArrayModule::onAfterQuery (MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo, int queryIndex) {}
//void DelayArrayModule::onInitModule (MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo) {}

//-----------------------------------------------------------------------------
// parameters and process
void timeIntervalModule::onGetParamInfo(int ParamIndex, TParamInfo* pParamInfo)
{	
	switch (ParamIndex) 
    {
		// entrée switch
	case 0:
		pParamInfo->ParamType       = ptDataField;
		pParamInfo->Caption			= "switch event";
		pParamInfo->IsInput			= true;
		pParamInfo->IsOutput		= false;
		pParamInfo->ReadOnly		= true;
		pParamInfo->MinValue		= 0;
		pParamInfo->MaxValue		= 1;
		break;

		// sortie  : le temps de fermeture du switch
	case 1: 
		pParamInfo->ParamType       = ptDataField;
		pParamInfo->Caption			= "time interval";
		pParamInfo->IsInput			= false;
		pParamInfo->IsOutput		= true;
		pParamInfo->ReadOnly		= true;
        //pParamInfo->MinValue		= 0;
		//pParamInfo->MaxValue		= FLT_MAX;
		break;

		// default case
	default:
		break;
	}
}
void timeIntervalModule::onSetEventAddress(int ParamIndex, UsineEventPtr pEvent)
{
	switch (ParamIndex) 
    {
	// switchState
	case 0: 
		switchState = pEvent;
		break;

	// time interval
	case 1:
		time = pEvent;
		break;

	// default case
	default:
		break;
	}
}
void timeIntervalModule::onCallBack(UsineMessage *Message)
{	
    // switchState
	if ((Message->wParam == 0) && (Message->lParam == MSG_CHANGE) && (sdkGetEvtData(switchState) == 1))
    {
		setTime = UserModuleBase::sdkGetTimeMs();
		//sdkSetEvtData(setTime, UserModuleBase::sdkGetTimeMs);
	}
	// switchState
	if ((Message->wParam == 0) && (Message->lParam == MSG_CHANGE) && (sdkGetEvtData(switchState) == 0))
	{
		resetTime = UserModuleBase::sdkGetTimeMs();
		intervalTime = resetTime - setTime;
		sdkSetEvtData(time, intervalTime);


	}
}

void timeIntervalModule::onProcess()
{	

}

//-----------------------------------------------------------------------------
// midi out callbacks
//void DelayArrayModule::onMidiSendOut (int DeviceID, UsineMidiCode Code) {}
//void DelayArrayModule::onMidiSysexSendOut (int DeviceID, char* Sysex) {}
//
//-----------------------------------------------------------------------------
// chunk system
//int  timeIntervalModule::onGetChunkLen (LongBool Preset) {return 0;}
//void timeIntervalModule::onGetChunk (void* chunk, LongBool Preset) {}
//void timeIntervalModule::onSetChunk (const void* chunk, int sizeInBytes, LongBool Preset) {}
//
//-----------------------------------------------------------------------------
// layout
//void timeIntervalModule::onCreateSettings() {}
//void timeIntervalModule::onSettingsHasChanged() {}
//void timeIntervalModule::onPaint () {}
//
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
// recording 
//void timeIntervalModule::onSetRecordedValue(TPrecision X, TPrecision Y, TPrecision Z) {}

