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
#include "seek.h"
//#include <cmath>

//----------------------------------------------------------------------------
// create, general info and destroy methodes
//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Create
void CreateModule (void* &pModule, AnsiCharPtr optionalString, LongBool Flag, MasterInfo* pMasterInfo, AnsiCharPtr optionalContent)
{
	pModule = new Seek();
}

// destroy
void DestroyModule(void* pModule) 
{
	// cast is important to call the good destructor
	delete ((Seek*) pModule);
}

//-------------------------------------------------------------------------
// module constructors/destructors
//-------------------------------------------------------------------------

// constructor
Seek::Seek()
{
	//
}

// destructor
Seek::~Seek()
{
	// 
}



//void TemplateModule::onCreate(AinsiCharPtr optionalString);
//void TemplateModule::onDestroy(); 
void Seek::onGetModuleInfo(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo)
{
	pModuleInfo->Name = "Seek Target";
	pModuleInfo->Description = "Seek Target";
	pModuleInfo->ModuleType = mtSimple;
	pModuleInfo->BackColor = sdkGetUsineColor(clInterfaceDesignModuleColor) + 0x101010;
	pModuleInfo->NumberOfParams = 8;
	pModuleInfo->DontProcess = false;
	pModuleInfo->Version	= "1.0";
}
//-----------------------------------------------------------------------------
// query system and init
int  Seek::onGetNumberOfParams(int QIdx) { return 0; }
void Seek::onAfterQuery(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo, int QIdx) {}
void Seek::onInitModule(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo) {}

//-----------------------------------------------------------------------------
// parameters and process
void Seek::onGetParamInfo(int ParamIndex, TParamInfo* pParamInfo)
{	
	switch (ParamIndex) 
    {
        // Add all parameters declared in the module class, example :

        // m_txtfExample
        case 0:
			pParamInfo->ParamType = ptDataFader;
            pParamInfo->Caption = "target X";
			pParamInfo->MinValue = 0.0f;
			pParamInfo->MaxValue = 1.0f;
			pParamInfo->DefaultValue = 0.5f;
			pParamInfo->Format = "%.5f";
            pParamInfo->IsInput				= TRUE;
            pParamInfo->IsOutput			= FALSE;
            break;
		case 1:
			pParamInfo->ParamType = ptDataFader;
			pParamInfo->Caption = "target Y";
			pParamInfo->MinValue = 0.0f;
			pParamInfo->MaxValue = 1.0f;
			pParamInfo->DefaultValue = 0.5f;
			pParamInfo->Format = "%.5f";
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
		case 2:
			pParamInfo->ParamType = ptDataFader;
			pParamInfo->Caption = "max force";
			pParamInfo->MinValue = 0.0f;
			pParamInfo->MaxValue = 1.0f;
			pParamInfo->DefaultValue = 0.5f;
			pParamInfo->Format = "%.6f";
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
		case 3:
			pParamInfo->ParamType = ptDataFader;
			pParamInfo->Caption = "max speed";
			pParamInfo->MinValue = 0.0f;
			pParamInfo->MaxValue = 1.0f;
			pParamInfo->DefaultValue = 0.5f;
			pParamInfo->Format = "%.6f";
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
		case 4:
			pParamInfo->ParamType = ptDataFader;
			pParamInfo->Caption = "max Steer";
			pParamInfo->MinValue = 0.0f; //linear
			pParamInfo->MaxValue = 1.0f; //slowdown near target
			pParamInfo->DefaultValue = 0.5f;
			pParamInfo->Format = "%.6f";
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
		case 5:
			pParamInfo->ParamType = ptButton;
			pParamInfo->Caption = "clock in";
			pParamInfo->DefaultValue = 0;
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
        //outputs
		case 6:
			pParamInfo->ParamType = ptDataField;
			pParamInfo->Caption = "pos x";
			pParamInfo->IsInput = FALSE;
			pParamInfo->IsOutput = TRUE;
			break;
		case 7:
			pParamInfo->ParamType = ptDataField;
			pParamInfo->Caption = "pos y";
			pParamInfo->IsInput = FALSE;
			pParamInfo->IsOutput = TRUE;
			break;
		// default case
	default:
		break;
	}
}
void Seek::onSetEventAddress(int ParamIndex, UsineEventPtr pEvent)
{
	switch (ParamIndex) 
    {
        // Initialyse all events adress declared in your module class, Example :

        case 0:
			m_TgX = pEvent;       // 
			break;
		case 1:
			m_TgY = pEvent;       // 
			break;
		case 2:
			m_ForceMax = pEvent;       // 
			break;
		case 3:
			m_SpeedMax = pEvent;       // 
			break;
		case 4:
			m_SteerMax = pEvent;
			break;
		case 5:
			m_clockIn = pEvent;
			break;
		case 6:
			m_posX = pEvent;
			break;
		case 7:
			m_posY = pEvent;
			break;

	// default case
	default:
		break;
	}
}
void Seek::onCallBack(UsineMessage *Message) {
	//algo ici
	if (Message->message == NOTIFY_MSG_USINE_CALLBACK && Message->lParam == MSG_CHANGE)
	{
		switch (Message->wParam)
		{
		
			
		case 5: //received clock trigger
				//evaluate the state functions

			
			//actualPos[0] = sdkGetEvtData(m_posX);
			//actualPos[1] = sdkGetEvtData(m_posY);
			targetPos[0] = sdkGetEvtData(m_TgX);
			targetPos[1] = sdkGetEvtData(m_TgY);
			desiredVel[0] = targetPos[0] - actualPos[0];
			desiredVel[1] = targetPos[1] - actualPos[1];
			//sdkTracePrecision(desiredVel[0]);
			//sdkTracePrecision(desiredVel[1]);
			//normalize and set max speed;
			float SpeedMax = sdkGetEvtData(m_SpeedMax)*0.1f;
			float norm = sqrt(pow(desiredVel[0], 2) + pow(desiredVel[1], 2));
			if (norm > 0) {
				desiredVel[0] = SpeedMax * desiredVel[0];// -.1 / norm + 1;
				desiredVel[1] = SpeedMax * desiredVel[1];// -.1 / norm + 1;
			}
			//sdkTracePrecision(desiredVel[0]);
			//sdkTracePrecision(desiredVel[1]);
			steer[0] = desiredVel[0] - actualVel[0];
			steer[1] = desiredVel[1] - actualVel[1];
			//sdkTracePrecision(steer[0]);
			//sdkTracePrecision(steer[1]);
			float normS = sqrt(pow(steer[0], 2) + pow(steer[1], 2));
			float SteerMax = sdkGetEvtData(m_SteerMax);// *0.1f;
			if (norm > SteerMax){
				steer[0] *= SteerMax / normS;
				steer[1] *= SteerMax / normS;
			}
			//sdkTracePrecision(steer[0]);
			//sdkTracePrecision(steer[1]);
			accel[0] += steer[0];
			accel[1] += steer[1];
			if (accel[0] > 1) {
				accel[0] = 1;
			}
			else if (accel[0] < -1) {
				accel[0] = -1;
			}
			if (accel[1] > 1) {
				accel[1] = 1;
			}
			else if (accel[1] < -1) {
				accel[1] = -1;
			}

			actualVel[0] += accel[0]*0.1f;
			actualVel[1] += accel[1]*0.1f;
			//ajout oli_lab pour limiter la vitesse à proximité de la cible
			actualVel[0] = actualVel[0] * norm*1.3f;
			actualVel[1] = actualVel[1] * norm*1.3f;
			//actualVel[0] *= desiredVel[0];
			//actualVel[1] *= desiredVel[1];
			//sdkTracePrecision(actualVel[0]);
			//sdkTracePrecision(actualVel[1]);
			
			norm = sqrt(pow(actualVel[0], 2) + pow(actualVel[1], 2));
			if (norm > SpeedMax){
				actualVel[0] *= SpeedMax / norm;
				actualVel[1] *= SpeedMax / norm;
			}
			actualPos[0] = actualVel[0] + actualPos[0];
			actualPos[1] = actualVel[1] + actualPos[1];
			if (actualPos[0] > 1){
				actualPos[0] = 1;
			}
			else if (actualPos[0] < 0){
				actualPos[0] = 0;
			}
			if (actualPos[1] > 1){
				actualPos[1] = 1;
			}
			else if (actualPos[1] < 0){
				actualPos[1] = 0;
			}
			sdkSetEvtData(m_posX, actualPos[0]);
			sdkSetEvtData(m_posY, actualPos[1]);
			
			break;
		}
	}
}


void Seek::onProcess() {}

//-----------------------------------------------------------------------------
// midi out callbacks
void Seek::onMidiSendOut(int DeviceID, UsineMidiCode Code) {}
void Seek::onMidiSysexSendOut(int DeviceID, char* Sysex) {}

//-----------------------------------------------------------------------------
// chunk system
int  Seek::onGetChunkLen(LongBool Preset) { return 0; }
void Seek::onGetChunk(void* chunk, LongBool Preset) {}
void Seek::onSetChunk(const void* chunk, int sizeInBytes, LongBool Preset) {}

//-----------------------------------------------------------------------------
// layout
void Seek::onCreateSettings() {}
void Seek::onSettingsHasChanged() {}
void Seek::onPaint() {}

//-----------------------------------------------------------------------------
// mouse and multi touch interaction
void Seek::onMouseMove(TShiftState Shift, float X, float Y) {}
void Seek::onMouseDown(TMouseButton MouseButton, TShiftState Shift, float X, float Y) {}
void Seek::onMouseUp(TMouseButton MouseButton, TShiftState Shift, float X, float Y) {}
void Seek::onMouseMoveMultiProc(TShiftState Shift, UsineEventPtr X, UsineEventPtr Y) {}
void Seek::onMouseDownMultiProc(TMouseButton MouseButton, TShiftState Shift, UsineEventPtr X, UsineEventPtr Y) {}
void Seek::onMouseUpMultiProc(TMouseButton MouseButton, TShiftState Shift, UsineEventPtr X, UsineEventPtr Y) {}
void Seek::onOpenEditor() {}
void Seek::onBringToFront() {}

//-----------------------------------------------------------------------------
// audio setup update
void Seek::onBlocSizeChange(int BlocSize) {}
void Seek::onSampleRateChange(double SampleRate) {}

//-----------------------------------------------------------------------------
// recording 
void Seek::onSetRecordedValue(TPrecision X, TPrecision Y, TPrecision Z) {}
