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
#include "wander.h"
//#include <cmath>

//----------------------------------------------------------------------------
// create, general info and destroy methodes
//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Create
void CreateModule (void* &pModule, AnsiCharPtr optionalString, LongBool Flag, MasterInfo* pMasterInfo, AnsiCharPtr optionalContent)
{
	pModule = new wander();
}

// destroy
void DestroyModule(void* pModule) 
{
	// cast is important to call the good destructor
	delete ((wander*) pModule);
}

//-------------------------------------------------------------------------
// module constructors/destructors
//-------------------------------------------------------------------------

// constructor
wander::wander()
{
	//
}

// destructor
wander::~wander()
{
	// 
}



//void TemplateModule::onCreate(AinsiCharPtr optionalString);
//void TemplateModule::onDestroy(); 
void wander::onGetModuleInfo(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo)
{
	pModuleInfo->Name = "wanderer";
	pModuleInfo->Description = "wanderer";
	pModuleInfo->ModuleType = mtSimple;
	pModuleInfo->BackColor = sdkGetUsineColor(clInterfaceDesignModuleColor) + 0x101010;
	pModuleInfo->NumberOfParams = 13;
	pModuleInfo->DontProcess = false;
	pModuleInfo->Version	= "1.0";
}
//-----------------------------------------------------------------------------
// query system and init
int  wander::onGetNumberOfParams(int QIdx) { return 0; }
void wander::onAfterQuery(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo, int QIdx) {}
void wander::onInitModule(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo) {
	/* initialize random seed: */
	srand(time(NULL));
	
}



//-----------------------------------------------------------------------------
// parameters and process
void wander::onGetParamInfo(int ParamIndex, TParamInfo* pParamInfo)
{	
	switch (ParamIndex)
    {
        // Add all parameters declared in the module class, example :

        case 0:
			pParamInfo->ParamType = ptDataFader;
            pParamInfo->Caption	= "Circle Distance";
			pParamInfo->MinValue = 0.0f;
			pParamInfo->MaxValue = 1.0f;
			pParamInfo->DefaultValue = 0.5f;
			pParamInfo->Format = "%.5f";
            pParamInfo->IsInput	= TRUE;
            pParamInfo->IsOutput = FALSE;
            break;
		case 1:
			pParamInfo->ParamType = ptDataFader;
			pParamInfo->Caption = "Circle Radius";
			pParamInfo->MinValue = 0.0f;
			pParamInfo->MaxValue = 1.0f;
			pParamInfo->DefaultValue = 0.5f;
			pParamInfo->Format = "%.5f";
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
		case 2:
			pParamInfo->ParamType = ptDataFader;
			pParamInfo->Caption = "Wander Angle";
			//pParamInfo->MinValue = 0.0f;
			//pParamInfo->MaxValue = 1.0f;
			//pParamInfo->DefaultValue = 0.5f;
			pParamInfo->Format = "%.6f";
			pParamInfo->IsInput = FALSE;
			pParamInfo->IsOutput = TRUE;
			break;
		case 3:
			pParamInfo->ParamType = ptDataFader;
			pParamInfo->Caption = "Angle Change";
			pParamInfo->MinValue = 0.0f;
			pParamInfo->MaxValue = 1.0f;
			pParamInfo->DefaultValue = 0.5f;
			pParamInfo->Format = "%.6f";
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
		case 4:
			pParamInfo->ParamType = ptDataFader;
			pParamInfo->Caption = "max Speed";
			pParamInfo->MinValue = 0.0f; //linear
			pParamInfo->MaxValue = 1.0f; //slowdown near target
			pParamInfo->DefaultValue = 0.5f;
			pParamInfo->Format = "%.6f";
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
		case 5:
			pParamInfo->ParamType = ptDataFader;
			pParamInfo->Caption = "max steer";
			pParamInfo->MinValue = 0.0f; //
			pParamInfo->MaxValue = 1.0f; //
			pParamInfo->DefaultValue = 0.5f;
			pParamInfo->Format = "%.6f";
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
		case 6:
			pParamInfo->ParamType = ptDataFader;
			pParamInfo->Caption = "mass";
			pParamInfo->MinValue = 0.0f; 
			pParamInfo->MaxValue = 1.0f; 
			pParamInfo->DefaultValue = 0.5f;
			pParamInfo->Format = "%.6f";
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
		case 7:
			pParamInfo->ParamType = ptButton;
			pParamInfo->Caption = "reset";
			pParamInfo->DefaultValue = 0;
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
		case 8:
			pParamInfo->ParamType = ptDataFader;
			pParamInfo->Caption = "reset pos x";
			pParamInfo->MinValue = 0.0f;
			pParamInfo->MaxValue = 1.0f;
			pParamInfo->DefaultValue = 0.5f;
			pParamInfo->Format = "%.6f";
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
		case 9:
			pParamInfo->ParamType = ptDataFader;
			pParamInfo->Caption = "reset pos y";
			pParamInfo->MinValue = 0.0f;
			pParamInfo->MaxValue = 1.0f;
			pParamInfo->DefaultValue = 0.5f;
			pParamInfo->Format = "%.6f";
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
		case 10:
			pParamInfo->ParamType = ptButton;
			pParamInfo->Caption = "clock in";
			pParamInfo->DefaultValue = 0;
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
        //outputs
		case 11:
			pParamInfo->ParamType = ptDataField;
			pParamInfo->Caption = "pos x";
			pParamInfo->IsInput = FALSE;
			pParamInfo->IsOutput = TRUE;
			break;
		case 12:
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
void wander::onSetEventAddress(int ParamIndex, UsineEventPtr pEvent)
{
	switch (ParamIndex) 
    {
        // Initialise all events adress declared in your module class, Example :

        case 0:
			m_circleDistance = pEvent;       // 
			break;
		case 1:
			m_circleRadius = pEvent;       // 
			break;
		case 2:
			m_wanderAngle = pEvent;       // 
			break;
		case 3:
			m_angleChange = pEvent;       // 
			break;
		case 4:
			m_SpeedMax = pEvent;
			break;
		case 5:
			m_SteerMax = pEvent;
			break;
		case 6:
			m_mass = pEvent;
			break;
		case 7:
			m_reset = pEvent;
			break;
		case 8:
			m_resetX = pEvent;
			break;
		case 9:
			m_resetY = pEvent;
			break;
		case 10:
			m_clockIn = pEvent;
			break;
		case 11:
			m_posX = pEvent;
			break;
		case 12:
			m_posY = pEvent;
			break;
			

	// default case
	default:
		break;
	}
}
void wander::onCallBack(UsineMessage *Message) {
	//algo ici
	if (Message->message == NOTIFY_MSG_USINE_CALLBACK && Message->lParam == MSG_CHANGE)
	{
		switch (Message->wParam)
		{
		case 7: //received reset
			position(1, 0) = sdkGetEvtData(m_resetX);
			position(1, 1) = sdkGetEvtData(m_resetY);
			//sdkSetEvtData(m_posX, sdkGetEvtData(m_resetX));
			//sdkSetEvtData(m_posY, sdkGetEvtData(m_resetY));
			break;

		case 10: //received clock trigger
			//evaluate the state functions

			// The code to calculate the circle center:
			circleCenter = position;
			//sdkTracePrecision(circleCenter(1, 0));
			//sdkTracePrecision(circleCenter(1, 1));
			circleCenter.normalize();
			circleCenter*sdkGetEvtData(m_circleDistance)*50;
			// Change wanderAngle just a bit, so it
			// won't have the same value in the
			// next game frame.
			val = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			val -= 0.5f;
			val *= 2;
			//sdkTracePrecision(val);
			wanderAngle += (val * sdkGetEvtData(m_angleChange) * 2 * M_PI);

			wanderAngle = fmod(wanderAngle,(2 * M_PI));
			/*
			if (wanderAngle > 2 * M_PI) {
				wanderAngle = 0;
			}
			else if (wanderAngle < 0) {
				wanderAngle = 2 * M_PI;
			}
			*/
			sdkSetEvtData(m_wanderAngle, wanderAngle);
			// Randomly change the vector direction
			// by making it change its current angle			
			displacement << 0, 0, sin(wanderAngle), cos(wanderAngle); //-1*
			displacement *= sdkGetEvtData(m_circleRadius);

			//sdkTracePrecision(displacement(1, 0));
			//sdkTracePrecision(displacement(1, 1));

			// Finally calculate the wander force
			wanderForce = circleCenter + displacement; //probleme ici
			//sdkTracePrecision(wanderForce(1, 0));
			//sdkTracePrecision(wanderForce(1, 1));
			//TPrecision norm = sqrt(pow((wanderForce(1, 0) - wanderForce(0, 0)), 2) + pow((wanderForce(1, 1) - wanderForce(0, 1)), 2));
			TPrecision norm = wanderForce.norm();
			//sdkTracePrecision(norm);
			if (norm > (sdkGetEvtData(m_SteerMax)) + 0.0001) {
				//sdkTracePrecision(norm);
				wanderForce *= sdkGetEvtData(m_SteerMax) / norm;
				//sdkTracePrecision(wanderForce(1, 0));
				//sdkTracePrecision(wanderForce(1, 1));
			}
			wanderForce = wanderForce / (sdkGetEvtData(m_mass) + 0.001f);
			velocity = velocity + wanderForce;
			norm = velocity.norm();
			float speedMax = sdkGetEvtData(m_SpeedMax) * 0.1;
			if (norm > speedMax) {
				velocity = velocity *(0.00001 + speedMax / norm);
				//sdkTracePrecision(velocity(1, 0));
				//sdkTracePrecision(velocity(1, 1));
			}
			position = position + velocity/2;
			if (position(1, 0) >= 1){
			 position(1, 0) = 0.99;
			 wanderAngle = M_PI - wanderAngle;
		     //velocity(1, 0) *= -1;
		    }
			if (position(1, 0) <= 0){
				position(1, 0) = 0.01;
				wanderAngle = M_PI - wanderAngle;
				//velocity(1, 0) *= -1;
			}
			if (position(1, 1) > 1){
				position(1, 1) = 0.99;
				wanderAngle = - wanderAngle;
				//velocity(1, 1) *= -1;
			}
			if (position(1, 1) < 0){
				position(1, 1) = 0.01;
				wanderAngle = - wanderAngle;
				//velocity(1, 1) *= -1;
			}
			
			sdkTracePrecision(position(1, 0));
			sdkTracePrecision(position(1, 1));
			sdkSetEvtData(m_posX, position(1,0));
			sdkSetEvtData(m_posY, position(1, 1));
			break;
		}
	}
}


void wander::onProcess() {}

//-----------------------------------------------------------------------------
// midi out callbacks
void wander::onMidiSendOut(int DeviceID, UsineMidiCode Code) {}
void wander::onMidiSysexSendOut(int DeviceID, char* Sysex) {}

//-----------------------------------------------------------------------------
// chunk system
int  wander::onGetChunkLen(LongBool Preset) { return 0; }
void wander::onGetChunk(void* chunk, LongBool Preset) {}
void wander::onSetChunk(const void* chunk, int sizeInBytes, LongBool Preset) {}

//-----------------------------------------------------------------------------
// layout
void wander::onCreateSettings() {}
void wander::onSettingsHasChanged() {}
void wander::onPaint() {}

//-----------------------------------------------------------------------------
// mouse and multi touch interaction
void wander::onMouseMove(TShiftState Shift, float X, float Y) {}
void wander::onMouseDown(TMouseButton MouseButton, TShiftState Shift, float X, float Y) {}
void wander::onMouseUp(TMouseButton MouseButton, TShiftState Shift, float X, float Y) {}
void wander::onMouseMoveMultiProc(TShiftState Shift, UsineEventPtr X, UsineEventPtr Y) {}
void wander::onMouseDownMultiProc(TMouseButton MouseButton, TShiftState Shift, UsineEventPtr X, UsineEventPtr Y) {}
void wander::onMouseUpMultiProc(TMouseButton MouseButton, TShiftState Shift, UsineEventPtr X, UsineEventPtr Y) {}
void wander::onOpenEditor() {}
void wander::onBringToFront() {}

//-----------------------------------------------------------------------------
// audio setup update
void wander::onBlocSizeChange(int BlocSize) {}
void wander::onSampleRateChange(double SampleRate) {}

//-----------------------------------------------------------------------------
// recording 
void wander::onSetRecordedValue(TPrecision X, TPrecision Y, TPrecision Z) {}
