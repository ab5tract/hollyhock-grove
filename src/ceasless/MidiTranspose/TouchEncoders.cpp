//-----------x------------------------------------------------------------------
//@file  
//	TouchEncoders.cpp
//
//@author
//	John Haltiwanger aka 'ceasless'
//
//@brief 
//	Definitions of the TouchEncoders class.
//
//  Example user module to show how to process midi messages.
//
//@historic 
//	2015/02/23
//    first release for Hollyhock CPP SDK 6.04.001
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
// Copyright (C) 2013, 2014, 2015 Sensomusic
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
#include "TouchEncoders.h"
#include <string>

//----------------------------------------------------------------------------
// create, general info and destroy methodes
//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Create
void CreateModule (void* &pModule, AnsiCharPtr optionalString, LongBool Flag, MasterInfo* pMasterInfo, AnsiCharPtr optionalContent)
{
	pModule = new TouchEncoders ();
}

//-----------------------------------------------------------------------------
// destroy
void DestroyModule (void* pModule) 
{
    // cast is important to call the good destructor
	delete ((TouchEncoders*)pModule);
}

//-----------------------------------------------------------------------------
// module description
void TouchEncoders::onGetModuleInfo (MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo) 
{

	//identification of the module
	pModuleInfo->Name				= "touch encoders";
	pModuleInfo->Description		= "touch encoders";
	pModuleInfo->ModuleType         = mtSimple;
	pModuleInfo->BackColor          = sdkGetUsineColor(clMidiModuleColor);
	pModuleInfo->NumberOfParams     = 10;
	pModuleInfo->Version			= "1.0";
}

//----------------------------------------------------------------------------
// parameters and process
//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Parameters description
void TouchEncoders::onGetParamInfo (int ParamIndex, TParamInfo* pParamInfo) 
{
    if( ParamIndex == 0 ) {
		pParamInfo->ParamType			= ptMidi;
		pParamInfo->Caption				= "in";
		pParamInfo->IsInput				= TRUE;
		pParamInfo->IsOutput			= FALSE;
		pParamInfo->CallBackType		= ctImmediate;
    } else if( ParamIndex == 1 ) {
		pParamInfo->ParamType			= ptMidi;
		pParamInfo->Caption				= "filtered midi out";
		pParamInfo->IsInput				= FALSE;
		pParamInfo->IsOutput			= TRUE;
    } else if( ParamIndex >= 2 && ParamIndex < 9 ) {
        std::sprintf(pParamInfo->Caption, "encoder %i", ParamIndex - 1);
        
		pParamInfo->ParamType			= ptSwitch;
		pParamInfo->IsInput				= FALSE;
		pParamInfo->IsOutput			= TRUE;
		pParamInfo->MinValue			= 0;
		pParamInfo->MaxValue			= 1;
		pParamInfo->DefaultValue		= 0;
		pParamInfo->CallBackType		= ctImmediate;
	}
}

//-----------------------------------------------------------------------------
// set the parameters events address
void TouchEncoders::onSetEventAddress (int ParamIndex, UsineEventPtr pEvent) 
{
    if( ParamIndex == 0 ) {
		midiIn = pEvent;
    } else if( ParamIndex == 1 ) {
		midiOut = pEvent;
    } else if( ParamIndex >= 2 && ParamIndex < 9 ) {
        encoderParams[ ParamIndex - 1 ] = pEvent;
    }
}

void TouchEncoders::onProcess () 
{
//    int sizeMidiIn = sdkGetEvtSize (midiIn);
//    sdkSetEvtSize (midiOut, 0);
//
//    if (sizeMidiIn > 0)
//    {
//        sdkCopyEvt (midiIn, midiOut);
//        int pitch = (int)sdkGetEvtData (fdrPitch);
//
//	    for (int i = 0; i < sizeMidiIn; i++)
//        {
//            UsineMidiCode code = sdkGetEvtArrayMidi (midiOut, i);
//           if (code.Msg ==  MIDI_NOTEON || code.Msg ==  MIDI_NOTEOFF)
//           {
//                code.Data1 = std::min (127, std::max (0, (int)code.Data1 + pitch));
//                sdkSetEvtArrayMidi (midiOut, i, code);
//           }
//        }
//    }
}

