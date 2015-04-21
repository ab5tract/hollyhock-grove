
//-----------------------------------------------------------------------------

// include once, no more
#ifndef __RGBA_COLOR_MODULE_H__
#define __RGBA_COLOR_MODULE_H__
//------------------------------------------------------------------------------
#define Psize_Max 32
//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <iostream>
#include <cmath>
#include <limits>
#include "UsineDefinitions.h"
#include "UserDefinitions.h"
#include "UserModule.h"
#include "UserUtils.h"

//-----------------------------------------------------------------------------
// class definition
//-----------------------------------------------------------------------------
class Color_Selector : public UserModuleBase
{
	//-------------------------------------------------------------------------
	// module constructors/destructors
	//-------------------------------------------------------------------------
public:
	// constructor
	Color_Selector(){};

	// destructor
	virtual ~Color_Selector(){};

	//-------------------------------------------------------------------------
	// public methodes inherited from UserModule
	//------------------------------------------------------------------------
public:
	//-----------------------------------------------------------------------------
	// module info
	void onGetModuleInfo(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo);

	//-----------------------------------------------------------------------------
	 //query system and init
	void onInitModule (MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo);

	//-----------------------------------------------------------------------------
	// parameters and process
	void onGetParamInfo(int ParamIndex, TParamInfo* pParamInfo);
	void onSetEventAddress(int ParamIndex, UsineEventPtr pEvent);
	void onCallBack(UsineMessage *Message);
	//-------------------------------------------------------------------------
	// layout
	//void onCreateSettings();
	//void onSettingsHasChanged();
	//void onCreateCommands();
	void onPaint();
	//void ResizeModule(void* pModule, float W, float H);
	//--------------------------------------------------------------------------------------------------------------
	// chunk system
	//int  onGetChunkLen(LongBool Preset);
	//void onGetChunk(void* chunk, LongBool Preset);
	//void onSetChunk(const void* chunk, int sizeInBytes, LongBool Preset);
	//--------------------------------------------------------------------------------------------------------------
	// mouse and multi touch interaction
	void onMouseMove(TShiftState Shift, float X, float Y);
	void onMouseDown(TMouseButton MouseButton, TShiftState Shift, float X, float Y);
	void onMouseUp(TMouseButton MouseButton, TShiftState Shift, float X, float Y);
	//void onMouseMoveMultiProc(TShiftState Shift, UsineEventPtr X, UsineEventPtr Y);
	//void onMouseDownMultiProc(TMouseButton MouseButton, TShiftState Shift, UsineEventPtr X, UsineEventPtr Y);
	//void onMouseUpMultiProc (TMouseButton MouseButton, TShiftState Shift,UsineEventPtr X, UsineEventPtr Y);
	//void onProcess();
	//-------------------------------------------------------------------------
	// private members
	void INIT_ALL();
	void GET_FINAL_COLOR();
	void COMPUTE_INPUT(float X, float Y);
	//void PAINT();
	void PAINT_HUE_WHEEl();
	void PAINT_HSL_TEXT();
	//-------------------------------------------------------------------------
private:
	//-------------------------------------------------------------------------
	// parameters events
	UsineEventPtr pColorOut;
	UsineEventPtr pColorHex;
	//////////////////////////////////
}; // class Color_Selector

#endif //__Color_Selector__