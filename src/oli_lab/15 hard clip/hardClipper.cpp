//-----------------------------------------------------------------------------
//@file  
//	AudioVolumeExample.cpp
//
//@author
//	Martin FLEURENT aka 'martignasse'
//
//@brief 
//	Implementation of the AudioVolumeExample class.
//
//  Example user module to show how to process audio buffers.
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
#include "hardClipper.h"

//----------------------------------------------------------------------------
// create, general info and destroy methodes
//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Create
void CreateModule (void* &pModule, AnsiCharPtr optionalString, LongBool Flag, MasterInfo* pMasterInfo, AnsiCharPtr optionalContent)
{
	pModule = new AudioVolumeExample();
}

// destroy
void DestroyModule(void* pModule) 
{
	// cast is important to call the good destructor
	delete ((AudioVolumeExample*)pModule);
}

//-------------------------------------------------------------------------
// module constructors/destructors
//-------------------------------------------------------------------------

// constructor
AudioVolumeExample::AudioVolumeExample()
    : coeffGain (1)
{
	//
}

// destructor
AudioVolumeExample::~AudioVolumeExample()
{
	// 
}

void AudioVolumeExample::onGetModuleInfo (MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo)
{
	pModuleInfo->Name				= "Hard Clipper";
	pModuleInfo->Description		= "hard clipper with many gain";
	pModuleInfo->ModuleType         = mtSimple;
	pModuleInfo->BackColor          = sdkGetUsineColor(clAudioModuleColor);
	pModuleInfo->Version			= "1.0";
	pModuleInfo->DontProcess = FALSE;
    
	// query for multi-channels
	if (pMasterInfo != nullptr)
    {
	    pModuleInfo->QueryString		= sdkGetAudioQueryTitle();
	    pModuleInfo->QueryListValues	= sdkGetAudioQueryChannelList();
	    pModuleInfo->QueryDefaultIdx	= 1;
    }
}

//-----------------------------------------------------------------------------
// query system and init methodes
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Get total parameters number of the module
int AudioVolumeExample::onGetNumberOfParams (int queryIndex)
{
	int result = 0;
    this->queryIndex = queryIndex;
    numOfAudiotInsOuts = sdkGetAudioQueryToNbChannels (queryIndex);

    // we want 1 in 1 out per channels
	result = (numOfAudiotInsOuts * 2) + numOfParamAfterAudiotInOut;

    return result;
}

//-----------------------------------------------------------------------------
// Called after the query popup
void AudioVolumeExample::onAfterQuery (MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo, int queryIndex)
{
}


//-----------------------------------------------------------------------------
// initialisation
void AudioVolumeExample::onInitModule (MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo) {}

//----------------------------------------------------------------------------
// parameters and process
//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Parameters description
void AudioVolumeExample::onGetParamInfo (int ParamIndex, TParamInfo* pParamInfo)
{	
    // audioInputs
    if (ParamIndex < numOfAudiotInsOuts)
    {
		pParamInfo->ParamType		= ptAudio;
		pParamInfo->Caption			= sdkGetAudioQueryChannelNames ( "in ", ParamIndex + 1, queryIndex);
		pParamInfo->IsInput			= TRUE;
		pParamInfo->IsOutput		= FALSE;
		pParamInfo->ReadOnly		= FALSE;

        if (ParamIndex == 0)
        {
            pParamInfo->IsSeparator     = TRUE;
            pParamInfo->SeparatorCaption = "audio in";
        }
    }
    // audioOutputs
    else if (ParamIndex >= numOfAudiotInsOuts && ParamIndex < (numOfAudiotInsOuts*2))
    {
		pParamInfo->ParamType		= ptAudio;
		pParamInfo->Caption			= sdkGetAudioQueryChannelNames ( "out ", ParamIndex - numOfAudiotInsOuts + 1, queryIndex);
		pParamInfo->IsInput			= FALSE;
		pParamInfo->IsOutput		= TRUE;
		pParamInfo->ReadOnly		= TRUE;

        if (ParamIndex == numOfAudiotInsOuts)
        {
            pParamInfo->IsSeparator     = TRUE;
            pParamInfo->SeparatorCaption = "audio out";
        }
    }
    // fdrGain
    else if (ParamIndex == (numOfAudiotInsOuts*2))
	{
		pParamInfo->ParamType		= ptDataFader;
		pParamInfo->Caption			= "gain";
		pParamInfo->MaxValue = 80.0f;
		pParamInfo->MinValue = -80.0f;
		pParamInfo->DefaultValue = 0.0f;
		pParamInfo->Format = "%.2f";
		pParamInfo->Symbol = "dB";
		pParamInfo->IsInput			= TRUE;
		pParamInfo->IsOutput		= FALSE;
        pParamInfo->IsSeparator     = TRUE;
        pParamInfo->CallBackType    = ctImmediate;
        pParamInfo->SeparatorCaption = "Volume";

    }
    // switchMute
    else if (ParamIndex == (numOfAudiotInsOuts*2) + 1)
	{
		pParamInfo->ParamType		= ptLeftLed;
		pParamInfo->Caption			= "mute";
		pParamInfo->IsInput			= TRUE;
		pParamInfo->IsOutput		= FALSE;
        pParamInfo->CallBackType    = ctImmediate;
    }
}

//-----------------------------------------------------------------------------
// set the parameters events address
void AudioVolumeExample::onSetEventAddress (int ParamIndex, UsineEventPtr pEvent)
{
    // audioInputs
    if (ParamIndex < numOfAudiotInsOuts)
    {
		audioInputs[ParamIndex] = pEvent;
    }
    // audioOutputs
    else if (ParamIndex >= numOfAudiotInsOuts && ParamIndex < (numOfAudiotInsOuts*2))
    {
		audioOutputs[ParamIndex - numOfAudiotInsOuts] = pEvent;
    }
    // fdrGain
    else if (ParamIndex == (numOfAudiotInsOuts*2))
	{
		fdrGain = pEvent;
    }
    // switchMute
    else if (ParamIndex == (numOfAudiotInsOuts*2) + 1)
	{
		switchMute = pEvent;
    }
}

//-----------------------------------------------------------------------------
// Parameters callback
void AudioVolumeExample::onCallBack (UsineMessage *Message) 
{
    // filter only message specific to this user module
    if (Message->message == NOTIFY_MSG_USINE_CALLBACK)
    {
        // Message->wParam is equal to ParamIndex
		if ((Message->wParam >= (numOfAudiotInsOuts*2)) && (Message->lParam == MSG_CHANGE))
		{
			coeffGain = sdkDbToCoeff (sdkGetEvtData (fdrGain)) * (1.0f - sdkGetEvtData (switchMute));
		}
    }
}

void AudioVolumeExample::onProcess()
{
	for (int i = 0; i < numOfAudiotInsOuts; i++)
	{
		sdkCopyEvt(audioInputs[i], audioOutputs[i]);
		sdkMultEvt1(coeffGain, audioOutputs[i]);

		//y = x / (1 + | x | )  softclipping formula
		for (int j = 0; j < sdkGetEvtSize(audioOutputs[i]); j++)
		{
			if (sdkGetEvtArrayData(audioOutputs[i], j) > 0.99f) {
				sdkSetEvtArrayData(audioOutputs[i], j, 0.99f);
			}
			else if (sdkGetEvtArrayData(audioOutputs[i], j) < -0.99f) {
				sdkSetEvtArrayData(audioOutputs[i], j, (-0.99f));
			}


		}
	}
}