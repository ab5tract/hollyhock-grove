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
#include "simplePendulum.h"
//#include <cmath>

//----------------------------------------------------------------------------
// create, general info and destroy methodes
//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Create
void CreateModule (void* &pModule, AnsiCharPtr optionalString, LongBool Flag, MasterInfo* pMasterInfo, AnsiCharPtr optionalContent)
{
	pModule = new SimplePendulum();
}

// destroy
void DestroyModule(void* pModule) 
{
	// cast is important to call the good destructor
	delete ((SimplePendulum*) pModule);
}

//-------------------------------------------------------------------------
// module constructors/destructors
//-------------------------------------------------------------------------

// constructor
SimplePendulum::SimplePendulum()
{
	//
}

// destructor
SimplePendulum::~SimplePendulum()
{
	// 
}



//void TemplateModule::onCreate(AinsiCharPtr optionalString);
//void TemplateModule::onDestroy(); 
void SimplePendulum::onGetModuleInfo(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo)
{
	pModuleInfo->Name = "Simple Pendulum";
	pModuleInfo->Description = "Simple Pendulum";
	pModuleInfo->ModuleType = mtSimple;
	pModuleInfo->BackColor = sdkGetUsineColor(clInterfaceDesignModuleColor) + 0x101010;
	pModuleInfo->NumberOfParams = 9;
	pModuleInfo->DontProcess = false;
	pModuleInfo->Version	= "0.1";
}
//-----------------------------------------------------------------------------
// query system and init
int  SimplePendulum::onGetNumberOfParams(int QIdx) { return 0; }
void SimplePendulum::onAfterQuery(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo, int QIdx) {}
void SimplePendulum::onInitModule(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo) {}

//-----------------------------------------------------------------------------
// parameters and process
void SimplePendulum::onGetParamInfo(int ParamIndex, TParamInfo* pParamInfo)
{	
	switch (ParamIndex) 
    {
        // Add all parameters declared in the module class, example :

        // m_txtfExample
        case 0:
			pParamInfo->ParamType			= ptDataFader;
            pParamInfo->Caption			    = "L1";
			pParamInfo->MinValue = 0.01f;
			pParamInfo->MaxValue = 0.5f;
			pParamInfo->DefaultValue = 0.25f;
			pParamInfo->Format = "%.5f";
            pParamInfo->IsInput				= TRUE;
            pParamInfo->IsOutput			= FALSE;
            break;
		case 1:
			pParamInfo->ParamType = ptDataFader;
			pParamInfo->Caption = "Friction";
			pParamInfo->MinValue = 0.0f;
			pParamInfo->MaxValue = 0.01f;
			pParamInfo->DefaultValue = 0.0001f;
			pParamInfo->Format = "%.6f";
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
		case 2:
			pParamInfo->ParamType = ptDataFader;
			pParamInfo->Caption = "Gravity";
			pParamInfo->MinValue = 0.0f;
			pParamInfo->MaxValue = 100.0f;
			pParamInfo->DefaultValue = 0.981f;
			pParamInfo->Format = "%.3f";
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
		case 3:
			pParamInfo->ParamType = ptDataFader;
			pParamInfo->Caption = "set final position";
			pParamInfo->MaxValue = 1.0f;
			pParamInfo->MinValue = 0.0f;
			pParamInfo->DefaultValue = 0.52f;
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
		case 4:
			pParamInfo->ParamType = ptButton;
			pParamInfo->Caption = "ck_in";
			pParamInfo->DefaultValue = 0;
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
        //outputs
		case 5:
			pParamInfo->ParamType = ptDataField;
			pParamInfo->Caption = "posM1x";
			pParamInfo->IsInput = FALSE;
			pParamInfo->IsOutput = TRUE;
			break;
		case 6:
			pParamInfo->ParamType = ptDataField;
			pParamInfo->Caption = "posM1y";
			pParamInfo->IsInput = FALSE;
			pParamInfo->IsOutput = TRUE;
			break;
		case 7:
			pParamInfo->ParamType = ptDataField;
			pParamInfo->Caption = "OffSet posM1x";
			pParamInfo->IsInput = FALSE;
			pParamInfo->IsOutput = TRUE;
			break;
		case 8:
			pParamInfo->ParamType = ptDataField;
			pParamInfo->Caption = "OffSet posM1y";
			pParamInfo->IsInput = FALSE;
			pParamInfo->IsOutput = TRUE;
			break;
		// default case
	default:
		break;
	}
}
void SimplePendulum::onSetEventAddress(int ParamIndex, UsineEventPtr pEvent)
{
	switch (ParamIndex) 
    {
        // Initialyse all events adress declared in your module class, Example :

        case 0:
			m_L1 = pEvent;       // pendulum 1 length
			break;
		case 1:
			m_friction = pEvent;
			break;
		case 2:
			m_gravity = pEvent;
			break;
		case 3:
			m_resetValue = pEvent;
			break;		
		case 4:
			m_clockIn = pEvent;
			break;
		case 5:
			m_M1posx = pEvent;
			break;
		case 6:
			m_M1posy = pEvent;
			break;
		case 7:
			m_OffSetM1posx = pEvent;
			break;
		case 8:
			m_OffSetM1posy = pEvent;
			break;

	// default case
	default:
		break;
	}
}
void SimplePendulum::onCallBack(UsineMessage *Message) {
	//algo ici
	if (Message->message == NOTIFY_MSG_USINE_CALLBACK && Message->lParam == MSG_CHANGE)
	{
		switch (Message->wParam)
		{
		case 3: //reset position
			gravityAngle = sdkGetEvtData(m_resetValue) * 2 * PI;
			prev_gravityCorrection = gravityCorrection;
			gravityCorrection = gravityAngle;
			token1 = 2;
			break;

		case 4: //received clock trigger
				//evaluate the state functions
			
			float gravity = sdkGetEvtData(m_gravity);
			float friction = sdkGetEvtData(m_friction) * (1+gravity);
			
			dx[0] = (-gravity / (sdkGetEvtData(m_L1) * 1000)) * sin(dx[2]);	//acceleration
			dx[1] += dx[0];											//vitesse
			dx[1] *= (1 - friction);
			if (token1 == 2) {
				token1 = 0;
				dx[2] = dx[2] - gravityCorrection + prev_gravityCorrection;	   //angle
			}
			else {
				dx[2] += dx[1];	   //angle
			}


			float newAngle1 = dx[2] + gravityCorrection;
				sdkSetEvtData(m_M1posx, centerx + sdkGetEvtData(m_L1)*sin(newAngle1));
				sdkSetEvtData(m_M1posy, centery + sdkGetEvtData(m_L1)*cos(newAngle1));
				sdkSetEvtData(m_OffSetM1posx, centerx + 0.5f*sin(newAngle1));
				sdkSetEvtData(m_OffSetM1posy, centery + 0.5f*cos(newAngle1));

			//}
			break;
		}
	}
}
void SimplePendulum::onProcess() {}

//-----------------------------------------------------------------------------
// midi out callbacks
void SimplePendulum::onMidiSendOut(int DeviceID, UsineMidiCode Code) {}
void SimplePendulum::onMidiSysexSendOut(int DeviceID, char* Sysex) {}

//-----------------------------------------------------------------------------
// chunk system
int  SimplePendulum::onGetChunkLen(LongBool Preset) { return 0; }
void SimplePendulum::onGetChunk(void* chunk, LongBool Preset) {}
void SimplePendulum::onSetChunk(const void* chunk, int sizeInBytes, LongBool Preset) {}

//-----------------------------------------------------------------------------
// layout
void SimplePendulum::onCreateSettings() {}
void SimplePendulum::onSettingsHasChanged() {}
void SimplePendulum::onPaint() {}

//-----------------------------------------------------------------------------
// mouse and multi touch interaction
void SimplePendulum::onMouseMove(TShiftState Shift, float X, float Y) {}
void SimplePendulum::onMouseDown(TMouseButton MouseButton, TShiftState Shift, float X, float Y) {}
void SimplePendulum::onMouseUp(TMouseButton MouseButton, TShiftState Shift, float X, float Y) {}
void SimplePendulum::onMouseMoveMultiProc(TShiftState Shift, UsineEventPtr X, UsineEventPtr Y) {}
void SimplePendulum::onMouseDownMultiProc(TMouseButton MouseButton, TShiftState Shift, UsineEventPtr X, UsineEventPtr Y) {}
void SimplePendulum::onMouseUpMultiProc(TMouseButton MouseButton, TShiftState Shift, UsineEventPtr X, UsineEventPtr Y) {}
void SimplePendulum::onOpenEditor() {}
void SimplePendulum::onBringToFront() {}

//-----------------------------------------------------------------------------
// audio setup update
void SimplePendulum::onBlocSizeChange(int BlocSize) {}
void SimplePendulum::onSampleRateChange(double SampleRate) {}

//-----------------------------------------------------------------------------
// recording 
void SimplePendulum::onSetRecordedValue(TPrecision X, TPrecision Y, TPrecision Z) {}
