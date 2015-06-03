//-----------------------------------------------------------------------------
//@file  
//	AudioDemix.cpp
//
//@author
//	Martin FLEURENT aka 'martignasse'
//
//@brief 
//	Implementation of the AudioDemix class.
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
#include "AudioDemix1.h"

//----------------------------------------------------------------------------
// create, general info and destroy methodes
//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Create
void CreateModule (void* &pModule, AnsiCharPtr optionalString, LongBool Flag, MasterInfo* pMasterInfo, AnsiCharPtr optionalContent)
{
	pModule = new AudioDemix();
}

// destroy
void DestroyModule(void* pModule) 
{
	// cast is important to call the good destructor
	delete ((AudioDemix*)pModule);
}

//-------------------------------------------------------------------------
// module constructors/destructors
//-------------------------------------------------------------------------

// constructor
AudioDemix::AudioDemix()
    : Gain (1)
{
	// audio smooth
	m_tevtSmoothCurrentCoeff1 = NULL;
	m_tevtSmoothCurrentCoeff2 = NULL;
}

// destructor
AudioDemix::~AudioDemix()
{
	if (m_tevtSmoothCurrentCoeff1 != NULL)
       sdkDestroyEvt(m_tevtSmoothCurrentCoeff1);
	if (m_tevtSmoothCurrentCoeff2 != NULL)
		sdkDestroyEvt(m_tevtSmoothCurrentCoeff2);
}

void AudioDemix::onGetModuleInfo (MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo)
{
	pModuleInfo->Name				= "audio demix 1:2";
	pModuleInfo->Description		= "audio demix 1:2";
	pModuleInfo->ModuleType         = mtSimple;
	pModuleInfo->BackColor          = sdkGetUsineColor(clAudioModuleColor);
	pModuleInfo->Version			= "2.1";
    
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
int AudioDemix::onGetNumberOfParams (int queryIndex)
{
	int result = 0;
    this->queryIndex = queryIndex;
    numOfAudiotInsOuts = sdkGetAudioQueryToNbChannels (queryIndex);

    // we want 1 in 2 outs per channels
	result = (numOfAudiotInsOuts * 3) + numOfParamAfterAudiotInOut;

    return result;
}

//-----------------------------------------------------------------------------
// Called after the query popup
void AudioDemix::onAfterQuery (MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo, int queryIndex)
{
	sdkCreateEvt(m_tevtSmoothCurrentCoeff1, pMasterInfo->BlocSize);
	sdkCreateEvt(m_tevtSmoothCurrentCoeff2, pMasterInfo->BlocSize);
}


//-----------------------------------------------------------------------------
// initialisation
void AudioDemix::onInitModule (MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo) {}

//----------------------------------------------------------------------------
// parameters and process
//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Parameters description
void AudioDemix::onGetParamInfo (int ParamIndex, TParamInfo* pParamInfo)
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
		pParamInfo->Caption			= sdkGetAudioQueryChannelNames ( "out1 ", ParamIndex - numOfAudiotInsOuts + 1, queryIndex);
		pParamInfo->IsInput			= FALSE;
		pParamInfo->IsOutput		= TRUE;
		pParamInfo->ReadOnly		= TRUE;

        if (ParamIndex == numOfAudiotInsOuts)
        {
            pParamInfo->IsSeparator     = TRUE;
            pParamInfo->SeparatorCaption = "audio out";
        }
    }

	else if (ParamIndex >= numOfAudiotInsOuts && ParamIndex < (numOfAudiotInsOuts * 3))
	{
		pParamInfo->ParamType = ptAudio;
		pParamInfo->Caption = sdkGetAudioQueryChannelNames("out2 ", ParamIndex - numOfAudiotInsOuts*2 + 1, queryIndex);
		pParamInfo->IsInput = FALSE;
		pParamInfo->IsOutput = TRUE;
		pParamInfo->ReadOnly = TRUE;

		if (ParamIndex == numOfAudiotInsOuts*2)
		{
			pParamInfo->IsSeparator = TRUE;
			pParamInfo->SeparatorCaption = "audio out";
		}
	}

    // fdrGain
    else if (ParamIndex == (numOfAudiotInsOuts*3))
	{
		pParamInfo->ParamType		= ptDataFader;
		pParamInfo->Caption			= "crossMix";
		pParamInfo->MaxValue = 1;
		pParamInfo->MinValue = 0;
		pParamInfo->Format = "%.5f";
		pParamInfo->IsInput			= TRUE;
		pParamInfo->IsOutput		= FALSE;
        pParamInfo->IsSeparator     = TRUE;
        pParamInfo->CallBackType    = ctImmediate;
        //pParamInfo->SeparatorCaption = "Volume";

    }
    // switchMute
    else if (ParamIndex == (numOfAudiotInsOuts*3) + 1)
	{
		pParamInfo->ParamType		= ptLeftLed;
		pParamInfo->Caption			= "mute source";
		pParamInfo->IsInput			= TRUE;
		pParamInfo->IsOutput		= FALSE;
        pParamInfo->CallBackType    = ctImmediate;
    }
	else if (ParamIndex == (numOfAudiotInsOuts * 3) + 2)
	{
		pParamInfo->ParamType = ptGainFader;
		pParamInfo->Caption = "att outs 1";
		pParamInfo->IsInput = TRUE;
		pParamInfo->IsOutput = FALSE;
		pParamInfo->CallBackType = ctImmediate;
	}
	else if (ParamIndex == (numOfAudiotInsOuts * 3) + 3)
	{
		pParamInfo->ParamType = ptGainFader;
		pParamInfo->Caption = "att outs 2";
		pParamInfo->IsInput = TRUE;
		pParamInfo->IsOutput = FALSE;
		pParamInfo->CallBackType = ctImmediate;
	}
	else if (ParamIndex == (numOfAudiotInsOuts * 3) + 4)
	{
		pParamInfo->ParamType = ptDataFader;
		pParamInfo->Caption = "overlapping";
		pParamInfo->MaxValue = 1;
		pParamInfo->MinValue = 0;
		pParamInfo->Format = "%.3f";
		pParamInfo->DefaultValue = 0.5;
		pParamInfo->IsInput = TRUE;
		pParamInfo->IsOutput = FALSE;
		pParamInfo->CallBackType = ctImmediate;
	}
}

//-----------------------------------------------------------------------------
// set the parameters events address
void AudioDemix::onSetEventAddress (int ParamIndex, UsineEventPtr pEvent)
{
    // audioInputs
    if (ParamIndex < numOfAudiotInsOuts)
    {
		audioInputs[ParamIndex] = pEvent;
    }
    // audioOutputs
    else if (ParamIndex >= numOfAudiotInsOuts && ParamIndex < (numOfAudiotInsOuts*2))
    {
		audioOutputs1[ParamIndex - numOfAudiotInsOuts] = pEvent;
    }
	else if (ParamIndex >= (numOfAudiotInsOuts*2) && ParamIndex < (numOfAudiotInsOuts * 3))
	{
		audioOutputs2[ParamIndex - numOfAudiotInsOuts*2] = pEvent;
	}
    // fdrGain
    else if (ParamIndex == (numOfAudiotInsOuts*3))
	{
		fdrGain = pEvent;
    }
    // switchMute
    else if (ParamIndex == (numOfAudiotInsOuts*3) + 1)
	{
		switchMute = pEvent;
    }
	// attenuation outputs 1
	else if (ParamIndex == (numOfAudiotInsOuts * 3) + 2)
	{
		attenuation1 = pEvent;
	}
	// attenuation outputs 3
	else if (ParamIndex == (numOfAudiotInsOuts * 3) + 3)
	{
		attenuation2 = pEvent;
	}
	// overlapping
	else if (ParamIndex == (numOfAudiotInsOuts * 3) + 4)
	{
		overlapping = pEvent;
	}

}

//-----------------------------------------------------------------------------
// Parameters callback
void AudioDemix::onCallBack (UsineMessage *Message) 
{
    // filter only message specific to this user module
    if (Message->message == NOTIFY_MSG_USINE_CALLBACK)
    {
        // Message->wParam is equal to ParamIndex
		if ((Message->wParam >= (numOfAudiotInsOuts*3)) && (Message->lParam == MSG_CHANGE))
		{
			Gain = sdkGetEvtData(fdrGain);
			mute = (1 - sdkGetEvtData(switchMute));
			Gain1 = (1 - Gain) * 1.0001f / (1.0001f - sdkGetEvtData(overlapping));
			if (Gain1 > 1) {
				Gain1 = 1;
			}
			Gain2 = Gain*1.0001f / (1.0001f - sdkGetEvtData(overlapping));
			if (Gain2 > 1) {
				Gain2 = 1;
			}
		    Gain1 *= mute*sdkDbToCoeff(sdkGetEvtData(attenuation1));
			Gain2 *= mute*sdkDbToCoeff(sdkGetEvtData(attenuation2));
		}
    }
}

void AudioDemix::onProcess () 
{
	sdkSmoothEvent(m_smoothOldCoeff1, m_tevtSmoothCurrentCoeff1, Gain1, SMOOTH);
	sdkSmoothEvent(m_smoothOldCoeff2, m_tevtSmoothCurrentCoeff2, Gain2, SMOOTH);
	for (int i = 0; i < numOfAudiotInsOuts; i++)
    {
        sdkCopyEvt (audioInputs[i], audioOutputs1[i]);
        //sdkMultEvt1 (Gain1, audioOutputs1[i]);
		sdkMultEvt2Audio(m_tevtSmoothCurrentCoeff1, audioOutputs1[i]);
		sdkCopyEvt(audioInputs[i], audioOutputs2[i]);
		//sdkMultEvt1(Gain2, audioOutputs2[i]);
		sdkMultEvt2Audio(m_tevtSmoothCurrentCoeff2, audioOutputs2[i]);
    }
}
