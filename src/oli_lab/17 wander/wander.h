//-----------------------------------------------------------------------------
//@file  
//	wander.h
//
//@author
//	Olivar Premier
//
//@brief 
//	Definitions of the helloWorldModule class.
//
//  A template include to start from for new user module.
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

// include once, no more
#ifndef __WANDER_MODULE_H__
#define __WANDER_MODULE_H__
//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include "../../sdk/UserDefinitions.h"  
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
//#include <limits>
//#include <vector>
#include "../../libs/eigen/Eigen/Dense"  //C:\00Hollyhock\persolivar\developpement USINE\SDK HH2 6\libs\eigen\Eigen
using namespace Eigen;
using namespace std;

//-----------------------------------------------------------------------------
// defines and constantes
//-----------------------------------------------------------------------------

// defines and constantes goes here 


//-----------------------------------------------------------------------------
// structures and typedef
//-----------------------------------------------------------------------------

// structures and typedef goes here

//-----------------------------------------------------------------------------
// class definition
//-----------------------------------------------------------------------------
class wander : public UserModuleBase
{
    //-------------------------------------------------------------------------
	// module constructors/destructors
	//-------------------------------------------------------------------------
public:
    // constructor
	wander();

    // destructor
	virtual ~wander();

	//-------------------------------------------------------------------------
	// public methodes inherited from UserModule
	//-------------------------------------------------------------------------
public:
	//-----------------------------------------------------------------------------
	// module info
	void onGetModuleInfo (MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo);

	//-----------------------------------------------------------------------------
	// query system and init
	int  onGetNumberOfParams( int QIdx);
	void onAfterQuery (MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo, int QIdx);
	void onInitModule (MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo);

	//-----------------------------------------------------------------------------
	// parameters and process
	void onGetParamInfo (int ParamIndex, TParamInfo* pParamInfo);
	void onSetEventAddress (int ParamIndex, UsineEventPtr pEvent);
	void onCallBack (UsineMessage *Message);
	void onProcess ();

	//-----------------------------------------------------------------------------
	// midi out callbacks
	void onMidiSendOut (int DeviceID, UsineMidiCode Code);
	void onMidiSysexSendOut (int DeviceID, char* Sysex);

	//-----------------------------------------------------------------------------
	// chunk system
	int  onGetChunkLen (LongBool Preset);
	void onGetChunk (void* chunk, LongBool Preset);
	void onSetChunk (const void* chunk, int sizeInBytes, LongBool Preset);

	//-----------------------------------------------------------------------------
	// layout
	void onCreateSettings();
	void onSettingsHasChanged();
    //void onResize (float contentWidth, float contentHeight);
    //void onCreateCommands();
	void onPaint ();

	//-----------------------------------------------------------------------------
	// mouse and multi touch interaction
	void onMouseMove(TShiftState Shift, float X, float Y);
	void onMouseDown(TMouseButton MouseButton, TShiftState Shift, float X,float Y);
	void onMouseUp (TMouseButton MouseButton, TShiftState Shift, float X,float Y);
	void onMouseMoveMultiProc(TShiftState Shift, UsineEventPtr X, UsineEventPtr Y);
	void onMouseDownMultiProc(TMouseButton MouseButton, TShiftState Shift, UsineEventPtr X, UsineEventPtr Y);
	void onMouseUpMultiProc (TMouseButton MouseButton, TShiftState Shift,UsineEventPtr X, UsineEventPtr Y);
	void onOpenEditor();
	void onBringToFront();

	//-----------------------------------------------------------------------------
	// audio setup update
	void onBlocSizeChange (int BlocSize);
	void onSampleRateChange (double SampleRate);
	
	//-----------------------------------------------------------------------------
	// recording 
	void onSetRecordedValue (TPrecision X, TPrecision Y, TPrecision Z);

	//-------------------------------------------------------------------------
	// public methodes
	//-------------------------------------------------------------------------
public:

    // public methodes goes here

	//-------------------------------------------------------------------------
	// protected members
	//-------------------------------------------------------------------------
protected:
	//-------------------------------------------------------------------------
	// parameters events : 

	UsineEventPtr m_circleDistance;
	UsineEventPtr m_circleRadius;
	UsineEventPtr m_wanderAngle;
	UsineEventPtr m_angleChange;
	UsineEventPtr m_SpeedMax;
	UsineEventPtr m_SteerMax;
	UsineEventPtr m_mass;
	UsineEventPtr m_reset;
	UsineEventPtr m_resetX;
	UsineEventPtr m_resetY;
	UsineEventPtr m_clockIn;
	UsineEventPtr m_posX;  
	UsineEventPtr m_posY;

	// protected members goes here	
	//Matrix2f  steering = Matrix2f::Zero();
	Matrix2f  velocity;
	Matrix2f  position;
	Matrix2f displacement;
	Matrix2f  wanderForce;
	Matrix2f  circleCenter;// = Matrix2f::Zero();
	float wanderAngle = 0;
	float val = 0; // srand(static_cast <unsigned> (time(0)));
	//-------------------------------------------------------------------------
	// private methodes
	//-------------------------------------------------------------------------
private:  

    // private methodes goes here
	

}; // class TemplateModule

#endif //__DOUBLE_PENDULUM_MODULE_H__