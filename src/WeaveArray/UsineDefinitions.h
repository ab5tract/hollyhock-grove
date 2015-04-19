///-----------------------------------------------------------------------------
///@file  
///	UsineDefinitions.h
///
///@author
///	Martin FLEURENT aka 'martignasse'
///
///@brief  
///	Datas and functions declarations exposed by Usine.
///
///HISTORIC 
///	2013/05/15
///    first release for Hollyhock CPP SDK 6.00.226 
///
///IMPORTANT
///	This file is part of the Usine Hollyhock CPP SDK
///
///  Please, report bugs and patch to Usine forum :
///  http://www.sensomusic.com/wiki2/doku.php?id=hollyhock:bugsreport 
///  
/// All dependencies are under there own licence.
///
///@copyright
/// Copyright (C) 2013 Sensomusic
/// 
/// Permission is hereby granted, free of charge, to any person obtaining a copy of 
/// this software and associated documentation files (the "Software"), 
/// to deal in the Software without restriction, including without limitation 
/// the rights to use, copy, modify, merge, publish, distribute, sublicense, 
/// and/or sell copies of the Software, and to permit persons to whom the Software 
/// is furnished to do so, subject to the following conditions:
/// 
/// The above copyright notice and this permission notice shall be included in all 
///     copies or substantial portions of the Software.
/// 
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
/// SOFTWARE.
///
///-----------------------------------------------------------------------------

// include once, no more
#ifndef __USINE_DEFINITIONS_H__
#define __USINE_DEFINITIONS_H__

//-----------------------------------------------------------------------------
// target platform preprocessor define
//-----------------------------------------------------------------------------
#if (defined (_WIN32) && ! defined(_WIN64)) 
  #define       USINE_WIN32 1
#elif defined (_WIN64)
  #define       USINE_WIN64 1
#elif defined (__APPLE_CPP__) || defined(__APPLE_CC__)
    #define     USINE_OSX32 1
#else
  #error "Unknown platform!"
#endif

// plateform specific defines
//-----------------------------------------------------------------------------
#if (defined (USINE_WIN32) || defined (USINE_WIN64))
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#elif defined (USINE_OSX32)
//-----------------------------------------------------------------------------
#ifdef USINE_OSX_1068
	#define nullptr (0)
#endif
//-----------------------------------------------------------------------------
#else
  #error "condidionnal compilation error!"
#endif
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <climits>
#include <cfloat>

//-----------------------------------------------------------------------------
// Datatypes definitions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// for memory alignment with DELPHI
//-----------------------------------------------------------------------------
#if (defined (USINE_WIN64))
//-----------------------------------------------------------------------------
#pragma pack(push, 4)
//-----------------------------------------------------------------------------
#elif  (defined (USINE_WIN32))
//-----------------------------------------------------------------------------
#pragma pack(push, 4)
//-----------------------------------------------------------------------------
#elif defined (USINE_OSX32)
//-----------------------------------------------------------------------------
#pragma pack(push, 4)
//-----------------------------------------------------------------------------
#else
  #error "condidionnal compilation error!"
#endif
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// version of the SDK
// to use in GetSDKVersion function to return the SDK version number
static int const SDK_VERSION = 604002;


//-----------------------------------------------------------------------------
#if (defined (USINE_WIN64))
//-----------------------------------------------------------------------------
typedef  __int64 NativeInt;
typedef  unsigned __int64 NativeUInt;
//-----------------------------------------------------------------------------
#elif (defined (USINE_WIN32))
//-----------------------------------------------------------------------------
typedef  __int32 NativeInt;
typedef  unsigned __int32 NativeUInt;
//-----------------------------------------------------------------------------
#elif defined (USINE_OSX32)
//-----------------------------------------------------------------------------
#include <stdint.h>
typedef  int32_t NativeInt;
typedef  uint32_t NativeUInt;
//-----------------------------------------------------------------------------
#else
  #error "condidionnal compilation error!"
#endif
//-----------------------------------------------------------------------------
/// @addtogroup Datatypes
/// @{

//-----------------------------------------------------------------------------
/// Custom bool type to match the 4 bytes DELPHI LongBool type.
typedef int LongBool;

/// Pointer to a LongBool variable.
typedef LongBool* LongBoolPtr;

/// To test LongBool equality against false. @see LongBool
#define FALSE 0 

/// To test LongBool equality against false. @see LongBool 
#define TRUE  1 

//-----------------------------------------------------------------------------
/// Pointer to an ANSI string variable.
/// Strings format conformance between CPP and DELPHI
typedef char* AnsiCharPtr;

/// @see TShifyState, TColorUsine
typedef unsigned long ULong;

//----------------------------------------------------------------------------
/// Usine internal message 
/// @see onCallback
typedef struct UsineMessage 
{
    NativeInt message; ///< the parameter value has changed
    NativeInt wParam;  ///< the parameter value has changed
    NativeInt lParam;  ///< @ref lParam "UsineMessage.lParam possible values"
    NativeInt result;  ///< the parameter value has changed
} UsineMessage;


//----------------------------------------------------------------------------
/// Possible values for UsineMessage::lParam.
/// @name UsineMessage::lParam
/// @{
static const NativeInt MSG_CHANGE     = 0;  ///< the parameter value has changed
static const NativeInt MSG_CLICK      = 1;  ///< the parameter has been clicked
static const NativeInt MSG_DBLCLICK   = 2;  ///< the parameter has been double clicked
static const NativeInt MSG_SETCAPTION = 3;  ///< change the caption of a control
static const NativeInt MSG_MOUSEUP    = 4;  ///< mouse Up
static const NativeInt MSG_MOUSEMOVE  = 5;  ///< mouse Move
static const NativeInt MSG_DROP       = 6;  ///< Something has been dropped on the control
static const NativeInt MSG_COMMATEXT  = 7;  ///< A commatext has changed
/// @}

//----------------------------------------------------------------------------
/// Possible target for a notification to Usine @see sdkNotifyUsine
/// @name Notifications Target types.
/// @{
static const NativeInt NOTIFY_TARGET_USINE        = 1;  ///< notify the main Usine panel
static const NativeInt NOTIFY_TARGET_SETUP        = 2;  ///< notify the setup of Usine
static const NativeInt NOTIFY_TARGET_USER_MODULE  = 3;  ///< notify the current User module
/// @}

//----------------------------------------------------------------------------
/// Possible message for a notification to Usine @see sdkNotifyUsine
/// @name Notifications Message types.
/// @{
static const NativeInt NOTIFY_MSG_AUDIO_DRIVER_CHANGED	= 0xFAB000;  ///< no param
static const NativeInt NOTIFY_MSG_MIDI_DRIVER_CHANGED	= 0xFAB001;  ///< no param
static const NativeInt NOTIFY_MSG_SAMPLE_RATE_CHANGED	= 0xFAB002;  ///< param1 = samplerate
static const NativeInt NOTIFY_MSG_BLOC_SIZE_CHANGED		= 0xFAB003;  ///< param1 = blocsize
static const NativeInt NOTIFY_MSG_RESCAN_PLUGINS_DONE	= 0xFAB004;  ///< no param
static const NativeInt NOTIFY_MSG_RECREATE_CONTROLS		= 0xFAB005;  ///< no param
static const NativeInt NOTIFY_MSG_KEY_DOWN		        = 0xFAB006;  ///< param1 = keycode, param2 = modifier
static const NativeInt NOTIFY_MSG_KEY_UP		        = 0xFAB007;  ///< param
static const NativeInt NOTIFY_MSG_FOCUS_LOST	        = 0xFAB008;  ///< no param

// used by usine at startup to notify devices (in onCallback ()) that the loaded phase is complete
static const NativeInt NOTIFY_MSG_USINE_LOADED	        = 0xFAB009;  ///< param1 = 0, param2 = 0
static const NativeInt NOTIFY_MSG_USINE_CALLBACK        = 0xFAB679;  ///< identify a Message->message as a callback for user module

static const NativeInt CALLBACK_WPARAM_LIMIT = 0xF000000;
/// @}

//----------------------------------------------------------------------------
/// keys state modifier.
/// @see MouseEventsCallbacks
typedef ULong TShiftState;

/// Possible value for a TShiftState variable.
/// @see onMouseMove, onMouseDown, onMouseUp, onMouseMoveMultiProc, onMouseDownMultiProc, onMouseUpMultiProc
/// @name TShiftState
/// @{
static const ULong ssShift  = 0x1;	///< Shift keyboard state
static const ULong ssAlt    = 0x2;  ///< Alt keyboard state
static const ULong ssCtrl   = 0x4;  ///< Ctrl keyboard state
static const ULong ssLeft   = 0x8;  ///< Left mouse button state
static const ULong ssRight  = 0x10; ///< Right mouse button state
static const ULong ssMiddle = 0x20; ///< Middle mouse button state
static const ULong ssDouble = 0x40; ///< Mouse Double click state
/// @}

//----------------------------------------------------------------------------
/// Mouse buttons available for a mouse event callback.
/// @see onMouseMove, onMouseDown, onMouseUp, onMouseMoveMultiProc, onMouseDownMultiProc, onMouseUpMultiProc
typedef enum TMouseButton 
{ 
    mbLeft,		///< Left mouse button
    mbRight,    ///< Right mouse button
    mbMiddle    ///< Middle mouse button
} TMouseButton;

//-----------------------------------------------------------------------------
/// Scale type available for a parameter.
/// @see TParamInfo
typedef enum TScale 
{ 
    scLinear,   ///< Linear type of scale
    scLog,      ///< Logarithmic  type of scale
    scExp       ///< Exponantial  type of scale
} TScale;

//-----------------------------------------------------------------------------
/// parameters type available in usine.
/// @see TParamInfo
typedef enum TParamType 
{ 
    ptTextField,            ///< param contain a string
    ptChooseColor,          ///< parameter
    ptMidi,                 ///< parameter
    ptGainFader,            ///< parameter
    ptAudio,                ///< parameter
    ptDataField,            ///< parameter
    ptDataFader,            ///< parameter
    ptButton,               ///< parameter
    ptListBox,              ///< parameter
    ptSwitch,               ///< parameter
    ptArray,                ///< parameter
    ptIpAddress,            ///< parameter
    ptSmpte,                ///< parameter
    ptMidiNoteFader,        ///< parameter
    ptPointerBitMap,        ///< parameter
    ptPointer,              ///< parameter
    ptRightLed,             ///< parameter
    ptChooseFolder,         ///< parameter
    ptLeftLed,              ///< parameter
	ptTriggerLed,           ///< parameter
    ptOther                 ///< parameter
} TParamType;

//-----------------------------------------------------------------------------
/// Data type of the parameter.
/// Used in UsineEvent, not used in user modules
typedef enum TFlowType  
{ 
    ftNone,             ///< Exponantial  type of scale
    ftPCM,				///< Exponantial  type of scale
    ftInternText, 		///< Exponantial  type of scale
    ftData, 			///< Exponantial  type of scale
    ftMIDI, 			///< Exponantial  type of scale
    ftArray, 			///< Exponantial  type of scale
    ftUser, 			///< Exponantial  type of scale
    ftEvtText, 			///< Exponantial  type of scale
    ftIntern=INT_MAX  	///< @internal Force the enum type size to 4bytes
} TFlowType;

//-----------------------------------------------------------------------------
/// Usine Midi code format.
typedef struct UsineMidiCode
{   
    unsigned char Channel;	///< Midi channel of the midi code
    unsigned char Msg;		///< Message part of the midi code
    unsigned char Data1;	///< Data1 part of the midi code
    unsigned char Data2;	///< Data2 of the midi code
} UsineMidiCode; 

/// Possible value for a UsineMidiCode::Msg variable.
/// @name UsineMidiCode::Msg
/// @{
static const unsigned char MIDI_ALLNOTESOFF     = 0x7B; ///< Midi msg
static const unsigned char MIDI_NOTEON          = 0x90; ///< Midi msg
static const unsigned char MIDI_NOTEOFF         = 0x80; ///< Midi msg
static const unsigned char MIDI_KEYAFTERTOUCH   = 0xa0; ///< Midi msg
static const unsigned char MIDI_CONTROLCHANGE   = 0xb0; ///< Midi msg
static const unsigned char MIDI_PROGRAMCHANGE   = 0xc0; ///< Midi msg
static const unsigned char MIDI_CHANAFTERTOUCH  = 0xd0; ///< Midi msg
static const unsigned char MIDI_PITCHBEND       = 0xe0; ///< Midi msg
static const unsigned char MIDI_SYSTEMMESSAGE   = 0xf0; ///< Midi msg
static const unsigned char MIDI_BEGINSYSEX      = 0xf0; ///< Midi msg
static const unsigned char MIDI_MTCQUARTERFRAME = 0xf1; ///< Midi msg
static const unsigned char MIDI_SONGPOSPTR      = 0xf2; ///< Midi msg
static const unsigned char MIDI_SONGSELECT      = 0xf3; ///< Midi msg
static const unsigned char MIDI_ENDSYSEX        = 0xF7; ///< Midi msg
static const unsigned char MIDI_TIMINGCLOCK     = 0xF8; ///< Midi msg
static const unsigned char MIDI_START           = 0xFA; ///< Midi msg
static const unsigned char MIDI_CONTINUE        = 0xFB; ///< Midi msg
static const unsigned char MIDI_STOP            = 0xFC; ///< Midi msg
static const unsigned char MIDI_ACTIVESENSING   = 0xFE; ///< Midi msg
static const unsigned char MIDI_SYSTEMRESET     = 0xFF; ///< Midi msg
/// @}

//-----------------------------------------------------------------------------
/// Usine native color format.
typedef ULong TColorUsine; 

//-----------------------------------------------------------------------------
/// Type used in all parameters data.
typedef float TPrecision; 

//-----------------------------------------------------------------------------
/// handle to an audio file.
typedef void* AudioFilePtr;

//-----------------------------------------------------------------------------
/// Colorset used by Usine.
typedef enum TUsineColorSet
{
    notUsed01,
    clTransparencyFactor,
    clDragOverFactor,
    clURed,
    clDarkPanelBack,
    clLiterPatchBack,
    clFont,
    clValueBack,
    clMidiLearnIcon,
    clPluginsParamIcon,
    clQuantizeIcon,
    clNotStoredIcon,
    clDATA,
    clMIDI,
    clMIDIlearn,
    clAUDIO,
    clARRAY,
    clText,
    clColor,
    clBitmap,
    clSynchroBack,
    clMasterBack,
    clMoreLitePanelBack,
    clVeryLitePanelBack,
    clToolBoxBack,
    clTraceBack,
    clKnobCursorBack,
    notUsed08,
    notUsed09,
    notUsed10,
    clPopupBack,
    notUsed11,
    clSwitchOff,
    clSwitchOn,
    clControlBorder,
    clButtonClick,
    clButton,
    clListBoxScroll,
    clSelected,
    clNotUsed01,
    clMainBack,
    //sequencer,
    clNotUsed02,
    clNotUsed03,
    clSeqGrid,
    clSeqGridLite,
    //pianoroll
    clPianoRollWhite,
    clPianoRollBlack,
    clPianoRollMidiEvents,
    clPianoRollCCEvents,
    
    //
    clCursor,
    clModulePanelBack,
    clNotUsed04,
    clFaderCursorColor,
    
    clInvalidLink,
    clInterfaceDesignModuleColor,
    clAnalyseModuleColor,
    clAudioModuleColor,
    clPluginModuleColor,
    clMidiModuleColor,
    clEventModuleColor,
    clDataModuleColor,
    clArrayModuleColor,
    clMathModuleColor,
    clSubPatchModuleColor,
    clScriptModuleColor,
    clOSCModuleColor,
    clInterfaceCtrlModuleColor,
    clStringModuleColor,
    clAudioDeviceModuleColor,
    // color picker
    cl0, cl1, cl2, cl3, cl4, cl5, cl6, cl7, cl8, cl9, cl10, cl11, cl12,
    cl13, cl14, cl15, cl16, cl17, cl18, cl19, cl20, cl21, cl22, cl23
} TUsineColorSet;

//-----------------------------------------------------------------------------
/// VST Time info structure as defined by the Steinberg VST SDK.
/// Used by Usine to deal with time at a musical point of view.
/// @see MasterInfo, sdkGetVstTimeInfo
typedef struct VstTimeInfo
{
    double samplePos;           ///< current location
    double sampleRate;          ///< current sample rate
    double nanoSeconds;         ///< system time
    double PpqPos;              ///< 1 ppq
    double tempo;               ///< in bpm
    double barStartPos;         ///< last bar start, in 1 ppq
    double cycleStartPos;       ///< 1 ppq
    double cycleEndPos;         ///< 1 ppq
    long   timeSigNumerator;    ///< time signature
    long   timeSigDenominator;  ///< 
    long   smpteOffset;         ///< 
    long   smpteFrameRate;      ///< 0:24, 1:25, 2:29.97, 3:30, 4:29.97 df, 5:30 df
    long   samplesToNextClock;  ///< midi clock resolution (24 ppq), can be negative
    long   flags;               ///< 
    double cyclePpqPos;         ///< usine cycle ppq
} VstTimeInfo;

//-----------------------------------------------------------------------------
/// Dialogs popup results
/// The value returned by a popup 
/// @see UserModuleBase::sdkDialogConfirmationYesNoCancel, UserModuleBase::sdkDialogConfirmationYesNo, UserModuleBase::sdkDialogInformationOk, UserModuleBase::sdkDialogConfirmationOKCancel
typedef enum TDialogsResults
{
	  idOk       = 1
	, idCancel   = 2
	, idAbort    = 3
	, idRetry    = 4
	, idIgnore   = 5
	, idYes      = 6
	, idNo       = 7
	, idClose    = 8
	, idHelp     = 9
	, idTryAgain = 10
	, idContinue = 11
	, mrNone     = 0
	, mrOk       = idOk
	, mrCancel   = idCancel
	, mrAbort    = idAbort
	, mrRetry    = idRetry
	, mrIgnore   = idIgnore
	, mrYes      = idYes
	, mrNo       = idNo
	, mrClose    = idClose
	, mrHelp     = idHelp
	, mrTryAgain = idTryAgain
	, mrContinue = idContinue
	, mrAll      = mrContinue + 1
	, mrNoToAll  = mrAll + 1
	, mrYesToAll = mrNoToAll + 1
} TDialogsResults;

/// Function pointer for a dialog box
typedef int (*FuncDialogBox)	(AnsiCharPtr msg);

//-----------------------------------------------------------------------------
/// To store 2D coordinates in coefficiant (from 0 to 1).
typedef struct TPointF 
{
    float x;
    float y;
} TPointF;

/// To store an array of 2D coordinates.
typedef TPointF* TPointFArray;

/// To store 3D coordinates in coefficiant (from 0 to 1).
typedef struct T3DPointF 
{
    float x;
    float y;
    float z;
} T3DPointF;

/// To store an array of 3D coordinates.
typedef T3DPointF* T3DPointFArray;

/// To store Rectangle coordinates in coefficiant (from 0 to 1).
struct TRectF 
{
    float left;
    float top;
    float right;
    float bottom;
};

/// Text vertical alignement.
/// @see sdkFillText
typedef enum TTextAlign 
{
    taCenter = 0,
    taLeading,
    taTrailling
} TTextAlign;

//-----------------------------------------------------------------------------
// Event associated to the parameter
// used in MultiTouch function declaration (see end of file)
struct UsineEvent;

/// Handle to a paramerer event.
/// @see onGetParamEvent
typedef UsineEvent* UsineEventPtr;

// forward declarations
struct MasterInfo;
struct ModuleInfo;

//-----------------------------------------------------------------------------
/// @name Settings Panel Tab's name
/// @see sdkAddSettingLineCaption ...
/// @{
static const AnsiCharPtr PROPERTIES_TAB_NAME	= "properties";	///< Used to populate the properties tab of the Settings panel
static const AnsiCharPtr DESIGN_TAB_NAME		= "design";		///< Used to populate the design tab of the Settings panel
static const AnsiCharPtr OTHER_TAB_NAME		= "other";		///< Used to populate the other tab of the Settings panel
static const AnsiCharPtr REMOTE_TAB_NAME		= "remote";		///< Used to populate the remote tab of the Settings panel
static const AnsiCharPtr CURVES_TAB_NAME		= "curves";		///< Used to populate the curves tab of the Settings panel
static const AnsiCharPtr LAN_TAB_NAME		    = "lan";		///< Used to populate the lan tab of the Settings panel
/// @}

/// @name Numeric format
/// @see sdkAddSettingLineSingle ...
/// @{
static const AnsiCharPtr DEFAULT_FORMAT_FLOAT_2  = "%.2f"; ///< Default format for a decimal number.
static const AnsiCharPtr DEFAULT_FORMAT_INTEGER  = "%.0f"; ///<  Default format for an integer number.
static const AnsiCharPtr DEFAULT_FORMAT_GENERAL  = "%g";   ///<  Default format for a string.
/// @}

/// @}

//-----------------------------------------------------------------------------
// functions pointers used in MasterInfo structure (see below)
//-----------------------------------------------------------------------------

// layouts
typedef void (*FuncRepaintPanel)           (ModuleInfo* pModuleInfo);
typedef void (*FuncAddSettingLineCaption)  (ModuleInfo* pModuleInfo, AnsiCharPtr tab, AnsiCharPtr caption, TColorUsine color, LongBool Translate);
typedef void (*FuncAddSettingLineColor)    (ModuleInfo* pModuleInfo, AnsiCharPtr tab, TColorUsine* pVal, AnsiCharPtr Caption, LongBool Translate);
typedef void (*FuncAddSettingLineBoolean)  (ModuleInfo* pModuleInfo, AnsiCharPtr tab, LongBool* pVal, AnsiCharPtr Caption, LongBool Translate);
typedef void (*FuncAddSettingLineInteger)  (ModuleInfo* pModuleInfo, AnsiCharPtr tab, int* pVal, AnsiCharPtr caption, int min, int max, TScale scale, AnsiCharPtr symbol, int defaultValue, LongBool Translate);
typedef void (*FuncAddSettingLineSingle)   (ModuleInfo* pModuleInfo, AnsiCharPtr tab, float* pVal, AnsiCharPtr caption, float min, float max, TScale scale, AnsiCharPtr symbol, AnsiCharPtr format, float defaultValue, LongBool Translate);
typedef void (*FuncAddSettingLineCombobox) (ModuleInfo* pModuleInfo, AnsiCharPtr tab, int* pVal, AnsiCharPtr caption, AnsiCharPtr commaText, LongBool Translate);

// internal messages
typedef void (*FuncSendMessage)    (ModuleInfo* pModuleInfo, AnsiCharPtr Msg);

// events manipuation
typedef bool (*FuncCompareEvt)     (UsineEventPtr e1, UsineEventPtr e2);
typedef void (*FuncCopyEvt)        (UsineEventPtr scr, UsineEventPtr dest );
typedef void (*FuncConcatEvt)      (UsineEventPtr i1, UsineEventPtr i2, UsineEventPtr o);
typedef void (*FuncShiftEvt)       (int n, UsineEventPtr input, UsineEventPtr output);
typedef void (*FuncSetEvtSize)     (UsineEventPtr ev, int size);
typedef int  (*FuncGetEvtSize)     (UsineEventPtr ev);
typedef void (*FuncSetEvtMaxSize)  (UsineEventPtr ev, int size);
typedef void (*FuncDestroyEvt)     (UsineEventPtr &ev);
typedef void (*FuncCreateEvt)      (UsineEventPtr &ev, int originalsize);
typedef void (*FuncMoveBLOC32)     (TPrecision* src, TPrecision* dest, int size);

typedef void (*FuncNotImplemented) ();
// access to evt values
typedef void            (*FuncSetEvtData)          (UsineEventPtr ev, TPrecision value);
typedef TPrecision      (*FuncGetEvtData)          (UsineEventPtr ev);
typedef void            (*FuncSetEvtArrayData)     (UsineEventPtr ev, int idx, TPrecision value);
typedef TPrecision      (*FuncGetEvtArrayData)     (UsineEventPtr ev, int idx);
typedef void            (*FuncSetEvtPointer)       (UsineEventPtr ev, void* value);            
typedef void*           (*FuncGetEvtPointer)       (UsineEventPtr ev);   
typedef void            (*FuncSetEvtColor)         (UsineEventPtr ev, TColorUsine value);            
typedef TColorUsine     (*FuncGetEvtColor)         (UsineEventPtr ev);                        
//typedef void          (*FuncSetEvtArrayPointer)  (UsineEventPtr ev, int idx, void* value);   
//typedef void*         (*FuncGetEvtArrayPointer)  (UsineEventPtr ev, int idx);                
typedef void            (*FuncSetEvtArrayMidi)     (UsineEventPtr ev, int idx, UsineMidiCode midi);
typedef UsineMidiCode   (*FuncGetEvtArrayMidi)     (UsineEventPtr ev, int idx);
typedef  void           (*FuncSetEvtPChar)         (UsineEventPtr ev, AnsiCharPtr delphistring);
typedef AnsiCharPtr    (*FuncGetEvtPChar)         (UsineEventPtr ev);
typedef TPrecision*     (*FuncGetEvtDataAddr)      (UsineEventPtr ev);

// evt data manipulation
typedef void  (*FuncAddEvt3)   (UsineEventPtr in1, UsineEventPtr in2, UsineEventPtr out);
typedef void  (*FuncAddEvt2)   (UsineEventPtr in1, UsineEventPtr in2);
typedef void  (*FuncSubEvt3)   (UsineEventPtr in1, UsineEventPtr in2, UsineEventPtr out);
typedef void  (*FuncSubEvt2)   (UsineEventPtr in1, UsineEventPtr in2);
typedef void  (*FuncDivEvt3)   (UsineEventPtr in1, UsineEventPtr in2, UsineEventPtr out);
typedef void  (*FuncMultEvt3)  (UsineEventPtr in1, UsineEventPtr in2, UsineEventPtr out);
typedef void  (*FuncMultEvt2)  (UsineEventPtr in1, UsineEventPtr in2);
typedef void  (*FuncMultEvt1)  (TPrecision m, UsineEventPtr out);
typedef void  (*FuncModEvt3)   (UsineEventPtr in1, UsineEventPtr in2, UsineEventPtr out);
typedef void  (*FuncPowerEvt3) (UsineEventPtr in1, UsineEventPtr in2, UsineEventPtr out);
typedef void  (*FuncExpEvt1)   (UsineEventPtr in1);
typedef void  (*FuncSqrtEvt1)  (UsineEventPtr in1);

// matrix event
typedef void  (*FuncSetEvtNbLines)            (UsineEventPtr in1, int nbLines);
typedef int   (*FuncGetEvtNbLines)            (UsineEventPtr in1);


typedef TPrecision  (*FuncMaxEvt1) (UsineEventPtr in1);
typedef TPrecision  (*FuncMinEvt1) (UsineEventPtr in1);
typedef void        (*FuncMaxEvt3) (UsineEventPtr in1, UsineEventPtr in2, UsineEventPtr out);
typedef void        (*FuncMinEvt3) (UsineEventPtr in1, UsineEventPtr in2, UsineEventPtr out);

typedef void  (*FuncThreshEvt2)      (const UsineEventPtr in1, UsineEventPtr out, TPrecision min, TPrecision max);
typedef void  (*FuncThreshEvt1)      (UsineEventPtr in1, TPrecision min, TPrecision max);
typedef void  (*FuncMixMidiEvt3)     (UsineEventPtr in1, UsineEventPtr in2, UsineEventPtr out);
typedef void  (*FuncMixMidiEvt2)     (UsineEventPtr in1, UsineEventPtr in2);
typedef void  (*FuncFadeInAudioEvt)  (UsineEventPtr TPCMin);
typedef void  (*FuncFadeOutAudioEvt) (UsineEventPtr TPCMin);
typedef void  (*FuncClearAudioEvt)   (UsineEventPtr in1);

// Audio File manipulation
typedef AudioFilePtr    (*FuncCreateAudioFile)          ();
typedef void            (*FuncDestroyAudioFile)         (AudioFilePtr audiofile);
typedef TPrecision      (*FuncGetSampleAudioFile)       (AudioFilePtr audiofile, int channel, int pos);
typedef void            (*FuncGetBlocSampleAudioFile)   (AudioFilePtr audiofile, int channel, int pos, UsineEventPtr evt);
typedef int             (*FuncGetSizeAudioFile)         (AudioFilePtr audiofile);
typedef int             (*FuncGetChannelAudioFile)      (AudioFilePtr audiofile);
typedef int             (*FuncGetSampleRateAudioFile)   (AudioFilePtr audiofile);
typedef int             (*FuncGetBitPerSampleAudioFile) (AudioFilePtr audiofile);
typedef void            (*FuncLoadInMemoryAudioFile)    (AudioFilePtr audiofile, AnsiCharPtr name);
typedef void            (*FuncLoadStayOnDiskAudioFile)  (AudioFilePtr audiofile, AnsiCharPtr name);
typedef void            (*FuncGetPeaksAudioFile)        (AudioFilePtr audiofile, UsineEventPtr evt);
typedef void            (*FuncSaveToDiskAudioFile)      (AudioFilePtr audiofile, AnsiCharPtr name, int nbChannels);
typedef void            (*FuncSetChannelsAudioFile)     (AudioFilePtr audiofile, int nbChannels);
typedef void            (*FuncSetSizeAudioFile)         (AudioFilePtr audiofile, int size);
typedef void            (*FuncSetSampleAudioFile)       (AudioFilePtr audiofile, int channel, int pos, TPrecision sample);
typedef void            (*FuncClearAudioFile)           (AudioFilePtr audiofile);

// math util
typedef TPrecision (*FuncLinearInterpolation) (TPrecision f, TPrecision a, TPrecision b);
typedef TPrecision (*FuncCubicInterpolation)  (TPrecision fr, TPrecision inm1, TPrecision inp, TPrecision inp1, TPrecision inp2);
typedef TPrecision (*FuncSplineInterpolation) (TPrecision fr, TPrecision inm1, TPrecision inp, TPrecision inp1, TPrecision inp2);

// files manipulation
typedef LongBool        (*FuncProcessOpenDialog) (AnsiCharPtr* filename, AnsiCharPtr initialDir, AnsiCharPtr filter);
typedef LongBool        (*FuncProcessSaveDialog) (AnsiCharPtr* filename, AnsiCharPtr initialDir, AnsiCharPtr filter);
typedef AnsiCharPtr    (*FuncFindFile)          (AnsiCharPtr* filename, AnsiCharPtr initialDir);
    
// trace functions
typedef void (*FuncTraceChar)       (AnsiCharPtr s);
typedef void (*FuncTraceInteger)    (int i);
typedef void (*FuncTracePrecision)  (TPrecision f);
typedef void (*FuncTraceLogChar)    (AnsiCharPtr s, LongBool showInSplashForm);
typedef void (*FuncTraceSplashChar) (AnsiCharPtr s, int autoClose);
typedef void (*FuncTraceErrorChar)  (AnsiCharPtr s);

// smooth functions
typedef void (*FuncSmoothPrecision)    (TPrecision& oldValue, UsineEventPtr currentEvent, TPrecision factor);
typedef void (*FuncSmoothEvent)        (TPrecision& oldValue, UsineEventPtr currentEvent, TPrecision target, TPrecision factor);
typedef void (*FuncMultEvt2Audio)      (UsineEventPtr in1, UsineEventPtr in2);

// update param callback
typedef void (*FuncSetListBoxCommatext)	(ModuleInfo* pModuleInfo, int numParam, AnsiCharPtr commaText);
typedef void (*FuncSetParamCaption)	    (ModuleInfo* pModuleInfo, int numParam, AnsiCharPtr caption);
typedef void (*FuncSetParamVisible)	    (ModuleInfo* pModuleInfo, int numParam, LongBool visible );
typedef void (*FuncRepaintParam)		(ModuleInfo* pModuleInfo, int numParam);
typedef void (*FuncSetParamValueText)	(ModuleInfo* pModuleInfo, int numParam, AnsiCharPtr valueText);


// audio callbacks
typedef void (*FuncAudioDeviceIOCallback)	(float** inputChannelData, int numInputChannels, float** outputChannelData, int numOutputChannels, int numSamples);

// midi callbacks
typedef void (*FuncMidiDeviceCallback)		(int deviceID, double TimeStamp, UsineMidiCode midiData);
typedef void (*FuncMidiSysexDeviceCallback)	(int deviceID, double TimeStamp, char** sysEx, int size);

// language translation
typedef AnsiCharPtr    (*FuncGetTranslationSDK)			( AnsiCharPtr StringID );

typedef double			(*FuncGetSampleRate)		();
typedef VstTimeInfo*	(*FuncGetVstTimeInfo)		(ModuleInfo* pModuleInfo);
typedef int				(*FuncCreatePlugInsTree)    ();

typedef void (*FuncNotifyUsine)	(ModuleInfo* pModuleInfo, NativeInt Target, NativeInt Msg, NativeInt Param1, NativeInt Param2);

// draw functions
typedef void (*FuncDrawPoint)		(ModuleInfo* pModuleInfo, TPointF point, TColorUsine color, float size, LongBool rounded);
typedef void (*FuncDrawLine)		(ModuleInfo* pModuleInfo, TPointF p1, TPointF p2, TColorUsine color, float strokeThickness);
typedef void (*FuncDrawPolyLine)	(ModuleInfo* pModuleInfo, TPointFArray points, int sizeList, TColorUsine color, float strokeThickness);
// draw path functions
typedef void (*FuncDrawPathMoveTo)		(ModuleInfo* pModuleInfo, TPointF point);
typedef void (*FuncDrawPathLineTo)		(ModuleInfo* pModuleInfo, TPointF point);
typedef void (*FuncDrawPathQuadCurveTo)	(ModuleInfo* pModuleInfo, TPointF control, TPointF point);
typedef void (*FuncDrawPathDraw)		(ModuleInfo* pModuleInfo, TColorUsine color, float strokeThickness);
typedef void (*FuncDrawPathFill)		(ModuleInfo* pModuleInfo, TColorUsine color);
typedef void (*FuncDrawPathClear)		(ModuleInfo* pModuleInfo);
typedef void (*FuncDrawPathClose)		(ModuleInfo* pModuleInfo);

// fill functions
typedef void (*FuncFillRect)	    (ModuleInfo* pModuleInfo, TRectF rect, TColorUsine color, float radius, TColorUsine borderColor, float borderWith);
typedef void (*FuncFillText)	    (ModuleInfo* pModuleInfo, TRectF rect, AnsiCharPtr text, TColorUsine textColor, float fontSize, LongBool isBold, LongBool isWordWrap, TTextAlign alignHorizontal, TTextAlign alignVertical, LongBool isVertical);
typedef void (*FuncFillPolyLine)	(ModuleInfo* pModuleInfo, TPointFArray points, int sizeList, TColorUsine color);

// record functions
typedef void (*FuncStopRecord)		(ModuleInfo* pModuleInfo);
typedef void (*FuncProcessRecord)	(ModuleInfo* pModuleInfo, TPrecision X, TPrecision Y, TPrecision Z);


typedef TColorUsine (*FuncGetUsineColor) ( int colorName);

typedef void  (*FuncAddCommand)           (ModuleInfo* pModuleInfo, AnsiCharPtr name, NativeInt CallbackId, LongBool Translate);
typedef void  (*FuncAddCommandSeparator)  (ModuleInfo* pModuleInfo, AnsiCharPtr name, LongBool Translate);
typedef void* (*FuncGetUsineMainWindow) ();
typedef void* (*FuncGetMacNSView) ();

typedef void*  (*FuncNeedRemoteUpdate)          (ModuleInfo* pModuleInfo, int numParam);
typedef double (*FuncGetTimeMs)                 (ModuleInfo* pModuleInfo); // precision up to nanoseconde
typedef void   (*FuncSetDeskWindowClientSize)   (ModuleInfo* pModuleInfo, int clientWidth, int clientHeight);
typedef void*  (*FuncCreateDeskWindow)          (ModuleInfo* pModuleInfo);
typedef void   (*FuncDestroyDeskWindow)         (ModuleInfo* pModuleInfo);
typedef void*  (*FuncShowDeskWindow)            (ModuleInfo* pModuleInfo);
typedef void   (*FuncHideDeskWindow)            (ModuleInfo* pModuleInfo);
typedef void   (*FuncSetDeskWindowCaption)      (ModuleInfo* pModuleInfo, AnsiCharPtr name);

typedef LongBool   (*FuncPatchIsRunning)      (ModuleInfo* pModuleInfo);


// return the nb off audio channels from QueryIndex
typedef int   (*FuncGetAudioQueryToNbChannels) (int qQueryIndex);

// return the n° index label from QueryIndex
// optional prefix (ex: "in " or "out "
// attention index commence à 1 (and not 0)
typedef AnsiCharPtr    (*FuncGetAudioQueryChannelNames) (AnsiCharPtr prefix, int index, int queryIndex);

//-----------------------------------------------------------------------------
/// @addtogroup Datatypes
/// @{

//-----------------------------------------------------------------------------
/// Versions type of Usine.
/// @see sdkGetUsineVersionType
typedef enum TUsineVersionType 
{
    uvStandAlonePro, 
    uvStandAloneFree, 
    uvStandAloneReader, 
    uvVST, 
    uvAudioUnit, 
    uvOther = INT_MAX
} TUsineVersionType;


//-----------------------------------------------------------------------------
/// Contains globals infos provided by Usine and all functions handle of the module wrapper.
struct MasterInfo 
{
    int                     BlocSize;				// size of Usine audio blocs (number of samples)
    NativeUInt              NSApplication;
    FuncRepaintPanel        RepaintPanel;			// ask Usine to repaint the module Panel
    FuncGetUsineMainWindow  GetUsineMainWindow;		// Usine mainform handle (THandle)
    FuncGetMacNSView        GetMacNSView;				// pointer to Usine internal User Module

    // add layout lines in the layout panel
    FuncAddSettingLineCaption	AddSettingLineCaption;
    FuncAddSettingLineColor	    AddSettingLineColor;
    FuncAddSettingLineBoolean	AddSettingLineBoolean;
    FuncAddSettingLineInteger	AddSettingLineInteger;

    // the colorset used by usine 
    FuncGetUsineColor         GetUsineColor;
                                                                
    // Internal usine message
    FuncSendMessage    SendUsineMsg;

    // Events manipuation
    FuncCopyEvt        CopyEvt;
    FuncCompareEvt     CompareEvt;
    FuncConcatEvt      ConcatEvt;
    FuncShiftEvt       ShiftEvt;
    FuncSetEvtSize     SetEvtSize;
    FuncSetEvtMaxSize  SetEvtMaxSize;
    FuncDestroyEvt     DestroyEvt;
    FuncCreateEvt      CreateEvt;
    FuncGetEvtSize     GetEvtSize;

    // Events values access
    FuncSetEvtData         SetEvtData;
    FuncGetEvtData         GetEvtData;
    FuncSetEvtArrayData    SetEvtArrayData;
    FuncGetEvtArrayData    GetEvtArrayData;
    FuncSetEvtPointer      SetEvtPointer;
    FuncGetEvtPointer      GetEvtPointer;
    FuncNotImplemented	   SetEvtArrayPointer;
    FuncNotImplemented	   GetEvtArrayPointer;
    FuncSetEvtArrayMidi    SetEvtArrayMidi;
    FuncGetEvtArrayMidi    GetEvtArrayMidi;
    FuncSetEvtPChar        SetEvtPChar;
    FuncGetEvtPChar        GetEvtPChar;

    FuncGetEvtDataAddr     GetEvtDataAddr;
    FuncMoveBLOC32 		   MoveBLOC32;

    // Events data manipulation
    FuncAddEvt3    AddEvt3;
    FuncAddEvt2    AddEvt2;
    FuncSubEvt3    SubEvt3;
    FuncSubEvt2    SubEvt2;
    FuncMultEvt3   MultEvt3;
    FuncMultEvt2   MultEvt2;
    FuncMultEvt1   MultEvt1;
    FuncDivEvt3    DivEvt3;
    FuncModEvt3    ModEvt3;
    FuncPowerEvt3  PowerEvt3;
    FuncExpEvt1    ExpEvt1;
    FuncSqrtEvt1   SqrtEvt1;

    FuncMaxEvt1    MaxEvt1;
    FuncMinEvt1    MinEvt1;
    FuncMaxEvt3    MaxEvt3;
    FuncMinEvt3    MinEvt3;

    FuncThreshEvt2      ThreshEvt2;
    FuncThreshEvt1      ThreshEvt1;
    FuncMixMidiEvt3     MixMidiEvt3;
    FuncMixMidiEvt2     MixMidiEvt2;
    FuncFadeInAudioEvt  FadeInAudioEvt;
    FuncFadeOutAudioEvt FadeOutAudioEvt;
    FuncClearAudioEvt   ClearAudioEvt;

    // Audio File manipulation
    FuncCreateAudioFile            CreateAudioFile;	
    FuncDestroyAudioFile           DestroyAudioFile;			
    FuncGetSampleAudioFile         GetSampleAudioFile;			
    FuncGetBlocSampleAudioFile     GetBlocSampleAudioFile;		
    FuncGetSizeAudioFile           GetSizeAudioFile;			
    FuncGetChannelAudioFile        GetChannelAudioFile;		
    FuncGetSampleRateAudioFile	   GetSampleRateAudioFile;		
    FuncGetBitPerSampleAudioFile   GetBitPerSampleAudioFile;	
    FuncLoadInMemoryAudioFile      LoadInMemoryAudioFile;		
    FuncLoadStayOnDiskAudioFile    LoadStayOnDiskAudioFile;	
    FuncGetPeaksAudioFile          GetPeaksAudioFile;			
    FuncSaveToDiskAudioFile        SaveToDiskAudioFile;		
    FuncSetChannelsAudioFile       SetChannelsAudioFile;		
    FuncSetSizeAudioFile           SetSizeAudioFile;			
    FuncSetSampleAudioFile         SetSampleAudioFile;			
    FuncClearAudioFile             ClearAudioFile;				

    // Math util
    FuncLinearInterpolation    LinearInterpolation;	
    FuncCubicInterpolation	   CubicInterpolation;		
    FuncSplineInterpolation    SplineInterpolation;

    // Files manipulation
    FuncProcessOpenDialog  ProcessOpenDialog;
    FuncProcessSaveDialog  ProcessSaveDialog;
    FuncFindFile           FindFile;
    
    // Usine path
    AnsiCharPtr   SoundPath;
    AnsiCharPtr   UserLibPath; 
    AnsiCharPtr   CurrentWorkspacePath; 
    AnsiCharPtr   CurrentPatchPath; 
    AnsiCharPtr   RecordPath;

    // Trace functions
    FuncTraceChar         TraceChar;
    FuncTraceInteger      TraceInteger;
    FuncTracePrecision    TracePrecision;
    FuncTraceLogChar      TraceLogChar;
    FuncTraceErrorChar    TraceErrorChar;
 
    // smooth functions
    FuncSmoothPrecision    SmoothPrecision;
    FuncSmoothEvent        SmoothEvent;
    FuncMultEvt2Audio      MultEvt2Audio;
	     
	int	MAX_AUDIO_INPUTS;
    int MAX_AUDIO_OUTUTS;
    int MAX_MIDI_DEVICES;
    int MULTIPHONY_MAX;

	FuncSetListBoxCommatext	        SetListBoxCommatext;
    AnsiCharPtr					UsineTempPath;
	FuncAudioDeviceIOCallback	    AudioDeviceIOCallback;

	FuncMidiDeviceCallback			MidiDeviceCallback;
	FuncMidiSysexDeviceCallback	    MidiSysexDeviceCallback;
	
	FuncSetParamCaption	            SetParamCaption;

	FuncGetTranslationSDK	        GetTranslation;
   
	FuncTraceErrorChar  TraceWarningChar;
	FuncSetParamVisible	SetParamVisible;
	FuncRepaintParam	RepaintParam;

	FuncGetSampleRate	GetSampleRate;
	FuncGetVstTimeInfo	GetVstTimeInfo;
    
    AnsiCharPtr            GlobalApplicationPath;
    FuncCreatePlugInsTree   CreatePlugInsTree;
    FuncNotifyUsine         NotifyUsine;

    FuncTraceSplashChar     TraceSplashChar;	

    FuncDialogBox		DialogConfirmationYesNoCancel;
    FuncDialogBox		DialogConfirmationYesNo;	
	FuncDialogBox		DialogInformationOk;		
	FuncDialogBox		DialogConfirmationOKCancel;

	LongBoolPtr		    NeedAllNoteOff;
	UsineEventPtr		AllNotOffEvent;

	FuncDrawPoint		DrawPoint;
	FuncDrawLine		DrawLine;
	FuncDrawPolyLine	DrawPolyLine;
	
	FuncFillRect		FillRect;
	FuncFillText		FillText;
		
	FuncAddSettingLineSingle	AddSettingLineSingle;
    AnsiCharPtr				PlugInsPath;
	FuncSetEvtColor		        SetEvtColor;
	FuncGetEvtColor		        GetEvtColor;
    
	FuncFillPolyLine		FillPolyLine;

	FuncStopRecord			StopRecord;
	FuncProcessRecord		ProcessRecord;
    
    FuncAddCommand              AddCommand;
    FuncAddCommandSeparator     AddCommandSeparator;
	FuncAddSettingLineCombobox  AddSettingLineCombobox;
    FuncNeedRemoteUpdate        NeedRemoteUpdate;
    
    AnsiCharPtr                UsineVersion; // 6.00.193alpha  -> major minor build
    FuncSetParamValueText       SetParamValueText;
    FuncGetTimeMs               GetTimeMs;
    FuncSetDeskWindowClientSize SetDeskWindowClientSize;
    FuncCreateDeskWindow        CreateDeskWindow;
    FuncDestroyDeskWindow       DestroyDeskWindow;
    FuncShowDeskWindow          ShowDeskWindow;
    FuncHideDeskWindow          HideDeskWindow;
    FuncSetDeskWindowCaption    SetDeskWindowCaption;

    // audio multi channels 
    FuncGetAudioQueryToNbChannels   AudioQueryToNbChannels;
    FuncGetAudioQueryChannelNames   AudioQueryChannelNames;
    AnsiCharPtr                    AudioQueryChannelList; // commatext to put in the query choice;

    int                             UsineSaveVersion;
    // draw path functions
    FuncDrawPathClear               DrawPathClear;
    FuncDrawPathMoveTo              DrawPathMoveTo;
    FuncDrawPathLineTo              DrawPathLineTo;
    FuncDrawPathDraw                DrawPathDraw;
    FuncDrawPathFill                DrawPathFill;
    FuncDrawPathClose               DrawPathClose;

    FuncSetEvtNbLines               SetEvtNbLines;
    FuncPatchIsRunning              PatchIsRunning;
    FuncDrawPathQuadCurveTo         DrawPathQuadCurveTo;
    FuncGetEvtNbLines               GetEvtNbLines;
    TUsineVersionType               UsineVersionType;
    AnsiCharPtr                    UsineLanguage;
    AnsiCharPtr                    AudioQueryTitle;
};

//-----------------------------------------------------------------------------
/// Possible type of callback for a parameter.
/// @see TParamInfo
typedef enum TFastCallBackType 
{
    ctNormal,       ///< Processed in the normal Usine messages handler. The latencie is defined by the User in the Usine Setup.  
    ctImmediate,    ///< Each time the parameter change, callback is processed immediatelly. Be careful, the the callBack procedure is called in the audio thread.
    ctAsynchronous  ///< Processed in the window message handler (slower than ctNormal). Use this if the process is very long or if you open a modal window.
} TFastCallBackType;

//-----------------------------------------------------------------------------
/// Usine parameter description.
/// Contain all the properties to define a parameter.
/// @see onGetParamInfo 
struct TParamInfo 
{
    TParamType        ParamType;            ///< parameter type
    AnsiCharPtr       Caption;              ///< displayed caption
    LongBool          IsInput;              ///< TRUE if the parameter has input port
    LongBool          IsOutput;             ///< TRUE if the parameter has output port
    TScale            Scale;                ///< scale, if the param is a fader
    TColorUsine       Color;                ///< front color of the fader or on Color of the switch
    TColorUsine       OffColor;             ///< off color only if the parameter is a switch
    TPrecision        MinValue;             ///< min param value
    TPrecision        MaxValue;             ///< max param value
    TPrecision        DefaultValue;         ///< default param value, when created
    AnsiCharPtr       Symbol;               ///< displayed symbol
    AnsiCharPtr       Format;               ///< format string of the displayed value
    AnsiCharPtr       ListBoxStrings;       ///< if listbox looks like '"item1","item2"'
    AnsiCharPtr       TextValue;            ///< default text value if param type = ptTextField
    LongBool          ReadOnly;             ///< TRUE if the user cant modify value
    TFastCallBackType CallBackType;         ///< see TFastCallBackType definition
    LongBool          DontSave;             ///< specifies if the parameter need to be save or not
    int               DisplayOrder;         ///< <b>Deprecated</b> Parameters are now ordered according to their param index choosen in onGetParamInfo
    LongBool          IsSeparator;          ///< optional, determines if the parameter add a blank line above him in the list
    LongBool          IsInvisible;          ///< set the parameter totally invisible
    LongBool          IsStoredInPreset;     ///< set the param stored in the preset (default false)
    AnsiCharPtr       SavedName;            ///< optional: ident used to save the value in inifiles. if NULL Caption is used
    AnsiCharPtr	      SeparatorCaption;     ///< optional, if isSeparator,  show a section name
    NativeInt         CallBackId;           ///< the id of the param for the callback, setEvent and param (choose a value up to 0x00000FFE)
	LongBool		  IsVisibleByDefault;   ///< TRUE by default
    LongBool		  IsShared;             ///< FALSE by default. Activate the LAN Remote mode for the parameter. @see sdkNeedRemoteUpdate
    LongBool		  Translate;            ///< usine autu translate
};

//-----------------------------------------------------------------------------
/// Possible type of user modules.
/// @see onGetModuleInfo, ModuleInfo
typedef enum TModuleType 
{ 
    mtSimple,           ///< module without graphic canvas
    mtNotUsed, 
    mtControl,          ///< module with a graphic canvas
	mtDeviceAudio,      ///< not for public use
	mtDeviceMidi,       ///< not for public use
	mtDeviceOther,      ///< not for public use
	mtPluginWrapper,    ///< not for public use
    mtPluginLister,     ///< not for public use
    mtDeviceDMX,        ///< not for public use
	mtOther             ///< not for public use
} TModuleType;


//-----------------------------------------------------------------------------
/// Contain characteristics and infos about the module.
/// You fill the Moduleinfo structure in the onGetModuleInfo callback to inform Usine of the module specs.
struct ModuleInfo 
{
    AnsiCharPtr     Name;           ///< short name displayed in the patch view
    AnsiCharPtr     Description;    ///< long name displayed in the  Browser
    TModuleType     ModuleType;     ///< module type: simple, form, control
    TColorUsine     BackColor;      ///< module color in the patch view
    int             NumberOfParams; ///< number of parameters of the module

    // form and panelwidth
    //   if moduletype = mtForm : form width
    //   if moduletype = mtControl :
    //      width is set to MasterInfo.PanelWidth
    //   if moduletype = mtSimple : ignored
    float       DefaultWidth;   // in pixel 
    
    // form and panel height
    //   if moduletype = mtSimple : ignored
    float       DefaultHeight; // in pixel 

    LongBool    DontProcess;        ///< FALSE by default. if TRUE, the module doesn't need any processing 
    LongBool	CanRecord;    		///< FALSE by default. if TRUE, the module will have the Automation record functionality. 

    //option for not show additionnal parameters, false by default  
    LongBool DoNotCreateAddCtrl ;   // if true usine don't create parameters like mousedown, hint, etc.

    // pointer to Usine internal User Module
    void*   UsineUserModule;    
    
    // to verify that the module has been created properly
    int     CheckCode; ///< @internal not for public use

    // stuff for the Audio Query system
    AnsiCharPtr     QueryString;        ///< string to ask about entries numbers
    AnsiCharPtr     QueryListValues;    ///< coma separated list with possible response
    int             QueryDefaultIdx;    ///< pre selected choice index for the coma list (0 to N-1)
                                        
	AnsiCharPtr     Version;            ///< version of the module. Displayed in the Browser
    
    /** FALSE by default, set to TRUE to activate the global Randomize feature.
        If activated you need to implement onRandomize Callback, Usine can call it at any time to initiate a Randomize. 
        When activated, a new entry is added in the properties tab named can be randomized and a randomize icon appear in the Contextual Menu of the module if any.
    */
    LongBool        CanBeRandomized;    
};


//-----------------------------------------------------------------------------
/// To store 2D coordinates in pixels.
struct TPointI 
{
    int x;
    int y;
};

//-----------------------------------------------------------------------------
/// To store color information in ARGB format (from 0 to 1).
struct TColorArgb
{
    float a;   
    float r;
    float g;
    float b;
}; 
//-----------------------------------------------------------------------------
/// To store color information in AHSL format (from 0 to 1).
struct TColorAhsl
{  
    float a;
    float h;
    float s;
    float l;
}; 

/// @}

//-----------------------------------------------------------------------------
// end of memory alignment with DELPHI
#pragma pack(pop)


//-----------------------------------------------------------------------------
// globals functions exposed by the module to communicate with usine
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#if (defined (USINE_WIN32) || defined (USINE_WIN64))
//-----------------------------------------------------------------------------
#define USINE_MODULE_EXPORT extern "C" __declspec( dllexport )
//-----------------------------------------------------------------------------
#elif defined (USINE_OSX32)
//-----------------------------------------------------------------------------
#define USINE_MODULE_EXPORT extern "C" __attribute__ (( visibility ("default") ))
//-----------------------------------------------------------------------------
#else
  #error "condidionnal compilation error!"
#endif
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// create, general info and destroy
// called by usine to get the version of the SDK used
USINE_MODULE_EXPORT int GetSDKVersion(void);
// called by usine to get implementation type (language + compilator) of the module
//USINE_MODULE_EXPORT SdkImplementation GetImplementation(void);
// Create Module
USINE_MODULE_EXPORT void Create(void* &pModule, AnsiCharPtr optionalString, LongBool Flag, MasterInfo* pMasterInfo, AnsiCharPtr optionalContent);
// Destroy Module
USINE_MODULE_EXPORT void Destroy(void* pModule); 
// called by usine to get modules informations
USINE_MODULE_EXPORT void GetModuleInfo (void* pModule, MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo);

//-----------------------------------------------------------------------------
// query system and init
// Get total parameters number of the module
USINE_MODULE_EXPORT int GetNumberOfParams(void* pModule,  int queryIndex);
// called after the query popup
USINE_MODULE_EXPORT void AfterQuery (void* pModule, MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo, int queryIndex);
// initialization procedure
USINE_MODULE_EXPORT void InitModule (void* pModule, MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo);

//-----------------------------------------------------------------------------
// parameters and process
// called by usine to get params informations
USINE_MODULE_EXPORT void GetParamInfo (void* pModule, int ParamIndex, TParamInfo* pParamInfo);
// tels to the module what are the effectives events address
USINE_MODULE_EXPORT void SetEventAddress (void* pModule, int ParamIndex, UsineEventPtr pEvent);
// called by Usine when a parameter value has changed
USINE_MODULE_EXPORT void CallBack (void* pModule, UsineMessage *Message);
// main process procedure
USINE_MODULE_EXPORT void Process (void* pModule);

//-----------------------------------------------------------------------------
// midi out callbacks
// called by Usine to send out midi
USINE_MODULE_EXPORT void MidiSendOut (void* pModule, int DeviceID, UsineMidiCode Code);

USINE_MODULE_EXPORT void MidiSendOutArray (void* pModule, int DeviceID, UsineMidiCode** arrayCode, int arraySize);

// called by Usine to send out midi sysex
USINE_MODULE_EXPORT void MidiSysexSendOut (void* pModule, int DeviceID, char** Sysex, int sysexSize);

// called by Usine to send out OSC messages
USINE_MODULE_EXPORT void DMXSendOut (void* pModule, int deviceId, char* ByteArray, int len);

//-----------------------------------------------------------------------------
// chunk system
// returns the chunk string len, needed for master memory allocation
USINE_MODULE_EXPORT int GetChunkLen (void* pModule, LongBool Preset);
// get the chunk string used to store modules intern data
// ! : all parameters values are strored automatically by Usine
USINE_MODULE_EXPORT void GetChunk (void* pModule, void* chunk, LongBool Preset);
// chunk string send by Usine when loading
USINE_MODULE_EXPORT void SetChunk (void* pModule, const void* chunk, LongBool Preset, int sizeInBytes);

//-----------------------------------------------------------------------------
// layout option and commands
// create user defined layout options in the 'edit layout' panel
USINE_MODULE_EXPORT void CreateSettings(void* pModule);
// Called when someting has changed in the layout
USINE_MODULE_EXPORT void SettingsHasChanged(void* pModule);
// resize the panel
USINE_MODULE_EXPORT void Resize (void* pModule, float W, float H);
// called by Usine to paint the panel
USINE_MODULE_EXPORT void Paint (void* pModule);

USINE_MODULE_EXPORT void CreateCommands(void* pModule);
//-----------------------------------------------------------------------------
// mouse and multi touch
// mouse move event
USINE_MODULE_EXPORT void MouseMove(void* pModule, TShiftState Shift, float X, float Y);
// mouse down event
USINE_MODULE_EXPORT void MouseDown(void* pModule, TMouseButton MouseButton, TShiftState Shift, float X,float Y);
// mouse up event
USINE_MODULE_EXPORT void MouseUp (void* pModule,  TMouseButton MouseButton, TShiftState Shift, float X,float Y);
// multi touch move event
USINE_MODULE_EXPORT void MouseMoveMultiProc(void* pModule, TShiftState Shift, UsineEventPtr X, UsineEventPtr Y);
// multi touch down event
USINE_MODULE_EXPORT void MouseDownMultiProc(void* pModule, TMouseButton MouseButton, TShiftState Shift, UsineEventPtr X, UsineEventPtr Y);
// multi touch up event
USINE_MODULE_EXPORT void MouseUpMultiProc (void* pModule, TMouseButton MouseButton, TShiftState Shift, UsineEventPtr X, UsineEventPtr Y);
// when double clicking on the module in the patch, should open the editor is any (VST or AU plugin)
USINE_MODULE_EXPORT void OpenEditor(void* pModule);
// 
USINE_MODULE_EXPORT void BringToFront(void* pModule);
USINE_MODULE_EXPORT void CloseEditor(void* pModule);
USINE_MODULE_EXPORT void ResizeEditor(void* pModule, int width, int height);

//-----------------------------------------------------------------------------
// usine infos callbacks
// audio setup update
// usine bloc size
USINE_MODULE_EXPORT void OnBlocSizeChange (void* pModule, int BlocSize);
// audio sample rate
USINE_MODULE_EXPORT void OnSampleRateChange (void* pModule, double SampleRate);

//-----------------------------------------------------------------------------
// usine recording callbacks
USINE_MODULE_EXPORT void SetRecordedValue (void* pModule, TPrecision X, TPrecision Y, TPrecision Z);

//-----------------------------------------------------------------------------
// usine preset randomize callback
USINE_MODULE_EXPORT void Randomize (void* pModule);

#endif // __USINE_DEFINITIONS_H__