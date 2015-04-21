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
#include "DoublePendulum2.h"
//#include <cmath>

//----------------------------------------------------------------------------
// create, general info and destroy methodes
//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Create
void CreateModule (void* &pModule, AnsiCharPtr optionalString, LongBool Flag, MasterInfo* pMasterInfo, AnsiCharPtr optionalContent)
{
	pModule = new DoublePendulum();
}

// destroy
void DestroyModule(void* pModule) 
{
	// cast is important to call the good destructor
	delete ((DoublePendulum*) pModule);
}

//-------------------------------------------------------------------------
// module constructors/destructors
//-------------------------------------------------------------------------

// constructor
DoublePendulum::DoublePendulum()
{
	//
}

// destructor
DoublePendulum::~DoublePendulum()
{
	// 
}



//void TemplateModule::onCreate(AinsiCharPtr optionalString);
//void TemplateModule::onDestroy(); 
void DoublePendulum::onGetModuleInfo(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo)
{
	pModuleInfo->Name = "Double Pendulum";
	pModuleInfo->Description = "Double Pendulum";
	pModuleInfo->ModuleType = mtSimple;
	pModuleInfo->BackColor = sdkGetUsineColor(clInterfaceDesignModuleColor) + 0x101010;
	pModuleInfo->NumberOfParams = 18;
	pModuleInfo->DontProcess = false;
	pModuleInfo->Version	= "1.0";
}
//-----------------------------------------------------------------------------
// query system and init
int  DoublePendulum::onGetNumberOfParams(int QIdx) { return 0; }
void DoublePendulum::onAfterQuery(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo, int QIdx) {}
void DoublePendulum::onInitModule(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo) {}

//-----------------------------------------------------------------------------
// parameters and process
void DoublePendulum::onGetParamInfo(int ParamIndex, TParamInfo* pParamInfo)
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
			pParamInfo->Caption = "L2";
			pParamInfo->MinValue = 0.01f;
			pParamInfo->MaxValue = 0.5f;
			pParamInfo->DefaultValue = 0.25f;
			pParamInfo->Format = "%.5f";
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
		case 2:
			pParamInfo->ParamType = ptDataFader;
			pParamInfo->Caption = "M1";
			pParamInfo->MinValue = 0.2f;
			pParamInfo->MaxValue = 1.0f;
			pParamInfo->DefaultValue = 0.5f;
			pParamInfo->Format = "%.5f";
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
		case 3:
			pParamInfo->ParamType = ptDataFader;
			pParamInfo->Caption = "M2";
			pParamInfo->MinValue = 0.2f;
			pParamInfo->MaxValue = 1.0f;
			pParamInfo->DefaultValue = 0.5f;
			pParamInfo->Format = "%.5f";
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
		case 4:
			pParamInfo->ParamType = ptDataFader;
			pParamInfo->Caption = "Friction";
			pParamInfo->MinValue = 0.0f;
			pParamInfo->MaxValue = 10.0f;
			pParamInfo->DefaultValue = 0.008f;
			pParamInfo->Format = "%.6f";
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
		case 5:
			pParamInfo->ParamType = ptDataFader;
			pParamInfo->Caption = "Gravity";
			pParamInfo->MinValue = 0.0f;
			pParamInfo->MaxValue = 20.0f;
			pParamInfo->DefaultValue = 0.981f;
			pParamInfo->Format = "%.3f";
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
		case 6:
			pParamInfo->ParamType = ptDataFader;
			pParamInfo->Caption = "g_angle";
			pParamInfo->MaxValue = 1;
			pParamInfo->MinValue = 0.0f;
			pParamInfo->DefaultValue = 0.0f;
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
		case 7:
			pParamInfo->ParamType = ptDataFader;
			pParamInfo->Caption = "phy_speed";
			pParamInfo->MaxValue = 0.01f;
			pParamInfo->MinValue = 0.0001f;
			pParamInfo->DefaultValue = 0.005f;
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
		case 8:
			pParamInfo->ParamType = ptDataField;
			pParamInfo->Caption = "reset";
			pParamInfo->MaxValue = 1;
			pParamInfo->MinValue = 0;
			pParamInfo->DefaultValue = 0;
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
		case 9:
			pParamInfo->ParamType = ptDataField;
			pParamInfo->Caption = "ck_in";
			pParamInfo->DefaultValue = 0;
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
        //outputs
		case 10:
			pParamInfo->ParamType = ptDataField;
			pParamInfo->Caption = "posM1x";
			pParamInfo->IsInput = FALSE;
			pParamInfo->IsOutput = TRUE;
			break;
		case 11:
			pParamInfo->ParamType = ptDataField;
			pParamInfo->Caption = "posM1y";
			pParamInfo->IsInput = FALSE;
			pParamInfo->IsOutput = TRUE;
			break;
		case 12:
			pParamInfo->ParamType = ptDataField;
			pParamInfo->Caption = "posM2x";
			pParamInfo->IsInput = FALSE;
			pParamInfo->IsOutput = TRUE;
			break;
		case 13:
			pParamInfo->ParamType = ptDataField;
			pParamInfo->Caption = "posM2y";
			pParamInfo->IsInput = FALSE;
			pParamInfo->IsOutput = TRUE;
			break;
		case 14:
			pParamInfo->ParamType = ptDataField;
			pParamInfo->Caption = "OffSet posM1x";
			pParamInfo->IsInput = FALSE;
			pParamInfo->IsOutput = TRUE;
			break;
		case 15:
			pParamInfo->ParamType = ptDataField;
			pParamInfo->Caption = "OffSet posM1y";
			pParamInfo->IsInput = FALSE;
			pParamInfo->IsOutput = TRUE;
			break;
		case 16:
			pParamInfo->ParamType = ptDataField;
			pParamInfo->Caption = "OffSet posM2x";
			pParamInfo->IsInput = FALSE;
			pParamInfo->IsOutput = TRUE;
			break;
		case 17:
			pParamInfo->ParamType = ptDataField;
			pParamInfo->Caption = "OffSet posM2y";
			pParamInfo->IsInput = FALSE;
			pParamInfo->IsOutput = TRUE;
			break;
		// default case
	default:
		break;
	}
}
void DoublePendulum::onSetEventAddress(int ParamIndex, UsineEventPtr pEvent)
{
	switch (ParamIndex) 
    {
        // Initialyse all events adress declared in your module class, Example :

        case 0:
			m_L1 = pEvent;       // pendulum 1 length
			break;
		case 1:
			m_L2 = pEvent;       // pendulum 2 length
			break;
		case 2:
			m_M1 = pEvent;       // pendulum 1 Mass
			break;
		case 3:
			m_M2 = pEvent;       // pendulum 2 Mass
			break;
		case 4:
			m_friction = pEvent;
			break;
		case 5:
			m_gravity = pEvent;
			break;
		case 6:
			m_gravityAngle = pEvent;
			break;
		case 7:
			m_physicSpeed = pEvent;
			break;
			
		case 8:
			m_reset = pEvent;
			break;
		case 9:
			m_clockIn = pEvent;
			break;
		case 10:
			m_M1posx = pEvent;
			break;
		case 11:
			m_M1posy = pEvent;
			break;
		case 12:
			m_M2posx = pEvent;
			break;
		case 13:
			m_M2posy = pEvent;
			break;
		case 14:
			m_OffSetM1posx = pEvent;
			break;
		case 15:
			m_OffSetM1posy = pEvent;
			break;
		case 16:
			m_OffSetM2posx = pEvent;
			break;
		case 17:
			m_OffSetM2posy = pEvent;
			break;

	// default case
	default:
		break;
	}
}
void DoublePendulum::onCallBack(UsineMessage *Message) {
	//algo ici
	if (Message->message == NOTIFY_MSG_USINE_CALLBACK && Message->lParam == MSG_CHANGE)
	{
		switch (Message->wParam)
		{
		case 6:
			//set new position
			gravityAngle = sdkGetEvtData(m_gravityAngle) * 2 * PI;
			prev_gravityCorrection = gravityCorrection;
			gravityCorrection = gravityAngle;
			token1 = 2;
			break;
			
		case 8: //reset
			x[0] = 0;
			x[1] = 0;
			x[2] = 0;
			x[3] = 0;
			sdkSetEvtData(m_OffSetM1posx, centerx + 0.5f*sin(x[0]));
			sdkSetEvtData(m_OffSetM1posy, centery + 0.5f*cos(x[0]));
			sdkSetEvtData(m_OffSetM2posx, centerx + 0.5f*sin(x[2]));
			sdkSetEvtData(m_OffSetM2posy, centery + 0.5f*cos(x[2]));
			sdkSetEvtData(m_M2posx, centerx + sdkGetEvtData(m_L1)*sin(x[0]) + sdkGetEvtData(m_L2)*sin(x[2]));
			sdkSetEvtData(m_M2posy, centery + sdkGetEvtData(m_L1)*cos(x[0]) + sdkGetEvtData(m_L2)*cos(x[2]));
			sdkSetEvtData(m_M1posx, centerx + sdkGetEvtData(m_L1)*sin(x[0]));
			sdkSetEvtData(m_M1posy, centery + sdkGetEvtData(m_L1)*cos(x[0]));
			break;
			
		case 9: //received clock trigger
				//evaluate the state functions
			float friction = sdkGetEvtData(m_friction);
			float gravity = sdkGetEvtData(m_gravity);

				dx[0] = x[1];

				dx[1] = gravity * -1 * (2 * sdkGetEvtData(m_M1) + sdkGetEvtData(m_M2))*(sin(x[0])) -
					sdkGetEvtData(m_M2) * gravity * sin((x[0]) - 2 * x[2]) -
					2 * sin((x[0]) - x[2])*sdkGetEvtData(m_M2)*(x[3] * x[3] * sdkGetEvtData(m_L2) +
					x[1] * x[1] * sdkGetEvtData(m_L1) * cos(x[0] - x[2]));
				dx[1] = dx[1] / (sdkGetEvtData(m_L1)*(2 * sdkGetEvtData(m_M1) + sdkGetEvtData(m_M2) - 
					sdkGetEvtData(m_M2)*cos(2 * x[0] - 2 * x[2])));
				dx[1] = dx[1] - friction*x[1] / (abs(x[1]) + 0.01f); //friction, 

				
				dx[2] = x[3];

				dx[3] = 2 * sin(x[0] - x[2])*(x[1] * x[1] * sdkGetEvtData(m_L1)*(sdkGetEvtData(m_M1) + sdkGetEvtData(m_M2)) +
					gravity *(sdkGetEvtData(m_M1) + sdkGetEvtData(m_M2))*cos(x[0]) +
					x[3] * x[3] * sdkGetEvtData(m_L2)*sdkGetEvtData(m_M2)*cos(x[0] - x[2]));
				dx[3] = dx[3] / (sdkGetEvtData(m_L2)*(2 * sdkGetEvtData(m_M1) + sdkGetEvtData(m_M2) - sdkGetEvtData(m_M2)*cos(2 * x[0] - 2 * x[2])));
				dx[3] = dx[3] - friction*x[3] / (abs(x[3]) + 0.01f); //friction

				if (token1 == 2) {
					token1 = 0;
					x[0] = x[0] - gravityCorrection + prev_gravityCorrection;	   //
					x[2] = x[2] - gravityCorrection + prev_gravityCorrection;	   //
				}
				else {}
				//euler step
				float h = sdkGetEvtData(m_physicSpeed);
				x[0] += h*dx[0];
				x[1] += h*dx[1];
				x[2] += h*dx[2];
				x[3] += h*dx[3];

				float newAngle1 = x[0] + gravityCorrection;
				float newAngle2 = x[2] + gravityCorrection;

				sdkSetEvtData(m_M2posx, centerx + sdkGetEvtData(m_L1)*sin(newAngle1) + sdkGetEvtData(m_L2)*sin(newAngle2));
				sdkSetEvtData(m_M2posy, centery + sdkGetEvtData(m_L1)*cos(newAngle1) + sdkGetEvtData(m_L2)*cos(newAngle2));
				sdkSetEvtData(m_M1posx, centerx + sdkGetEvtData(m_L1)*sin(newAngle1));
				sdkSetEvtData(m_M1posy, centery + sdkGetEvtData(m_L1)*cos(newAngle1));
				sdkSetEvtData(m_OffSetM1posx, centerx + 0.5f*sin(newAngle1));
				sdkSetEvtData(m_OffSetM1posy, centery + 0.5f*cos(newAngle1));
				sdkSetEvtData(m_OffSetM2posx, centerx + 0.5f*sin(newAngle2));
				sdkSetEvtData(m_OffSetM2posy, centery + 0.5f*cos(newAngle2));
			break;
		}
	}
}
void DoublePendulum::onProcess() {}

//-----------------------------------------------------------------------------
// midi out callbacks
void DoublePendulum::onMidiSendOut(int DeviceID, UsineMidiCode Code) {}
void DoublePendulum::onMidiSysexSendOut(int DeviceID, char* Sysex) {}

//-----------------------------------------------------------------------------
// chunk system
int  DoublePendulum::onGetChunkLen(LongBool Preset) { return 0; }
void DoublePendulum::onGetChunk(void* chunk, LongBool Preset) {}
void DoublePendulum::onSetChunk(const void* chunk, int sizeInBytes, LongBool Preset) {}

//-----------------------------------------------------------------------------
// layout
void DoublePendulum::onCreateSettings() {}
void DoublePendulum::onSettingsHasChanged() {}
void DoublePendulum::onPaint() {}

//-----------------------------------------------------------------------------
// mouse and multi touch interaction
void DoublePendulum::onMouseMove(TShiftState Shift, float X, float Y) {}
void DoublePendulum::onMouseDown(TMouseButton MouseButton, TShiftState Shift, float X, float Y) {}
void DoublePendulum::onMouseUp(TMouseButton MouseButton, TShiftState Shift, float X, float Y) {}
void DoublePendulum::onMouseMoveMultiProc(TShiftState Shift, UsineEventPtr X, UsineEventPtr Y) {}
void DoublePendulum::onMouseDownMultiProc(TMouseButton MouseButton, TShiftState Shift, UsineEventPtr X, UsineEventPtr Y) {}
void DoublePendulum::onMouseUpMultiProc(TMouseButton MouseButton, TShiftState Shift, UsineEventPtr X, UsineEventPtr Y) {}
void DoublePendulum::onOpenEditor() {}
void DoublePendulum::onBringToFront() {}

//-----------------------------------------------------------------------------
// audio setup update
void DoublePendulum::onBlocSizeChange(int BlocSize) {}
void DoublePendulum::onSampleRateChange(double SampleRate) {}

//-----------------------------------------------------------------------------
// recording 
void DoublePendulum::onSetRecordedValue(TPrecision X, TPrecision Y, TPrecision Z) {}
