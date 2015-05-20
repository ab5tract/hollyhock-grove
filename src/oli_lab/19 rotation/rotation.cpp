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
#include "rotation.h"
//#include <cmath>

//----------------------------------------------------------------------------
// create, general info and destroy methodes
//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Create
void CreateModule (void* &pModule, AnsiCharPtr optionalString, LongBool Flag, MasterInfo* pMasterInfo, AnsiCharPtr optionalContent)
{
	pModule = new rotationMatrix();
}

// destroy
void DestroyModule(void* pModule) 
{
	// cast is important to call the good destructor
	delete ((rotationMatrix*) pModule);
}

//-------------------------------------------------------------------------
// module constructors/destructors
//-------------------------------------------------------------------------

// constructor
rotationMatrix::rotationMatrix()
{
	//
}

// destructor
rotationMatrix::~rotationMatrix()
{
	// 
}



//void TemplateModule::onCreate(AinsiCharPtr optionalString);
//void TemplateModule::onDestroy(); 
void rotationMatrix::onGetModuleInfo(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo)
{
	pModuleInfo->Name = "rotationer";
	pModuleInfo->Description = "rotate XY coordinates";
	pModuleInfo->ModuleType = mtSimple;
	pModuleInfo->BackColor = sdkGetUsineColor(clInterfaceDesignModuleColor) + 0x101010;
	pModuleInfo->NumberOfParams = 5;
	pModuleInfo->DontProcess = FALSE;
	pModuleInfo->Version	= "1.0";
}
//-----------------------------------------------------------------------------
// query system and init
int  rotationMatrix::onGetNumberOfParams(int QIdx) { return 0; }
void rotationMatrix::onAfterQuery(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo, int QIdx) {}
void rotationMatrix::onInitModule(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo) {}



//-----------------------------------------------------------------------------
// parameters and process
void rotationMatrix::onGetParamInfo(int ParamIndex, TParamInfo* pParamInfo)
{	
	switch (ParamIndex)
    {
        // Add all parameters declared in the module class, example :

        case 0:
			pParamInfo->ParamType = ptDataFader;
            pParamInfo->Caption	= "x";
			pParamInfo->MinValue = 0.0f;
			pParamInfo->MaxValue = 1.0f;
			pParamInfo->DefaultValue = 0.5f;
			pParamInfo->Format = "%.5f";
            pParamInfo->IsInput	= TRUE;
            pParamInfo->IsOutput = FALSE;
            break;
		case 1:
			pParamInfo->ParamType = ptDataFader;
			pParamInfo->Caption = "y";
			pParamInfo->MinValue = 0.0f;
			pParamInfo->MaxValue = 1.0f;
			pParamInfo->DefaultValue = 0.5f;
			pParamInfo->Format = "%.5f";
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
		case 2:
			pParamInfo->ParamType = ptDataFader;
			pParamInfo->Caption = "rotation Angle";
			pParamInfo->MinValue = -1.0f;
			pParamInfo->MaxValue = 1.0f;
			pParamInfo->DefaultValue = 0.0f;
			pParamInfo->Format = "%.6f";
			pParamInfo->IsInput = TRUE;
			pParamInfo->IsOutput = FALSE;
			break;
	
        //outputs
		case 3:
			pParamInfo->ParamType = ptDataField;
			pParamInfo->Caption = "out x";
			pParamInfo->Format = "%.6f";
			pParamInfo->IsInput = FALSE;
			pParamInfo->IsOutput = TRUE;
			break;
		case 4:
			pParamInfo->ParamType = ptDataField;
			pParamInfo->Caption = "out y";
			pParamInfo->Format = "%.6f";
			pParamInfo->IsInput = FALSE;
			pParamInfo->IsOutput = TRUE;
			break;
		// default case
	default:
		break;
	}
}
void rotationMatrix::onSetEventAddress(int ParamIndex, UsineEventPtr pEvent)
{
	switch (ParamIndex) 
    {
        // Initialise all events adress declared in your module class, Example :

        case 0:
			m_inX = pEvent;       // 
			break;
		case 1:
			m_inY = pEvent;       // 
			break;
		case 2:
			m_rotationAngle = pEvent;       // 
			break;
		case 3:
			m_outX = pEvent;       // 
			break;
		case 4:
			m_outY = pEvent;
			break;
	// default case
	    default:
		    break;
	}
}
void rotationMatrix::onCallBack(UsineMessage *Message) {
	//algo ici
	if ((Message->message == NOTIFY_MSG_USINE_CALLBACK) && (Message->lParam == MSG_CHANGE))
	{
		
		switch (Message->wParam)
		{
		case 0:
			x = sdkGetEvtData(m_inX);
			computeNewCoordinates();
			break;
		case 1:
			y = sdkGetEvtData(m_inY);
			computeNewCoordinates();
			break;
		case 2:
			rotationAngle = 2 * PI*sdkGetEvtData(m_rotationAngle);
			computeNewCoordinates();
			break;
		
		}
		
    }

}


void rotationMatrix::onProcess() {}

void rotationMatrix::computeNewCoordinates()//(TPrecision rotationAngle, TPrecision x, TPrecision y)
{
	TPrecision valx = ((x - 0.5f)* cos(rotationAngle)) - ((y - 0.5f)*sin(rotationAngle)) + 0.5f;
	sdkSetEvtData(m_outX, valx);
	//sdkTracePrecision(valx);
	TPrecision valy = ((x - 0.5f)* sin(rotationAngle)) + ((y - 0.5f)*cos(rotationAngle)) + 0.5f;
	//sdkTracePrecision(valy);
	sdkSetEvtData(m_outY, valy);
}

//-----------------------------------------------------------------------------
// midi out callbacks
void rotationMatrix::onMidiSendOut(int DeviceID, UsineMidiCode Code) {}
void rotationMatrix::onMidiSysexSendOut(int DeviceID, char* Sysex) {}

//-----------------------------------------------------------------------------
// chunk system
int  rotationMatrix::onGetChunkLen(LongBool Preset) { return 0; }
void rotationMatrix::onGetChunk(void* chunk, LongBool Preset) {}
void rotationMatrix::onSetChunk(const void* chunk, int sizeInBytes, LongBool Preset) {}

//-----------------------------------------------------------------------------
// layout
void rotationMatrix::onCreateSettings() {}
void rotationMatrix::onSettingsHasChanged() {}
void rotationMatrix::onPaint() {}

//-----------------------------------------------------------------------------
// mouse and multi touch interaction
void rotationMatrix::onMouseMove(TShiftState Shift, float X, float Y) {}
void rotationMatrix::onMouseDown(TMouseButton MouseButton, TShiftState Shift, float X, float Y) {}
void rotationMatrix::onMouseUp(TMouseButton MouseButton, TShiftState Shift, float X, float Y) {}
void rotationMatrix::onMouseMoveMultiProc(TShiftState Shift, UsineEventPtr X, UsineEventPtr Y) {}
void rotationMatrix::onMouseDownMultiProc(TMouseButton MouseButton, TShiftState Shift, UsineEventPtr X, UsineEventPtr Y) {}
void rotationMatrix::onMouseUpMultiProc(TMouseButton MouseButton, TShiftState Shift, UsineEventPtr X, UsineEventPtr Y) {}
void rotationMatrix::onOpenEditor() {}
void rotationMatrix::onBringToFront() {}

//-----------------------------------------------------------------------------
// audio setup update
void rotationMatrix::onBlocSizeChange(int BlocSize) {}
void rotationMatrix::onSampleRateChange(double SampleRate) {}

//-----------------------------------------------------------------------------
// recording 
void rotationMatrix::onSetRecordedValue(TPrecision X, TPrecision Y, TPrecision Z) {}
