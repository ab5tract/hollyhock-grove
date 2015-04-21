#include "Color_Selector.h"
#include <math.h>
#include <string> 
#include <iostream>
#include <iomanip>
using namespace std;
///////////////////////////////////////////
static bool MSDWN;
static bool HUE_CHG;
static bool PAINT_WHEEL;
static float  MSX;
static float  MSY;
static float Distance_center;
static TRectF BGrect;
static TRectF TxtRect;
static TPointF PCenter;
static TPointF MSD_HUE;
static TPointF MSD_LUMSAT;
static TPointF PLUM_SAT;
TPointF PRing[127];
static float  SEL_HUE;
static float  SEL_LUM;
static float  SEL_SAT;
static float t_hue;
float Ring_Radius = 0.25;
int RingMax = 127;
static string Txt;
static string TxtColorHex;
TColorUsine RING_COLOR;
TColorUsine HUE_COLOR;
TColorUsine LUM_SAT_COLOR;
TColorUsine FINAL_COLOR;
TColorUsine WHITE_COLOR = sdkColorAhslToAlphaColor(sdkColorAhsl(0, 0, 1));
TColorUsine BLACK_COLOR = sdkColorAhslToAlphaColor(sdkColorAhsl(0, 0, 0));
float Ring_Dot_Size = 40;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CreateModule (void* &pModule, AnsiCharPtr optionalString, LongBool Flag, MasterInfo* pMasterInfo, AnsiCharPtr optionalContent)
{
	pModule = new Color_Selector();
}

void DestroyModule (void* pModule)
{
	delete ((Color_Selector*)pModule);
}

void Color_Selector::onGetModuleInfo(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo)
{

	//identification of the module
	pModuleInfo->Name				= "Color_Selector";
	pModuleInfo->Description		= "Color_Selector";
	pModuleInfo->ModuleType 		= mtControl;
	pModuleInfo->BackColor          = sdkGetUsineColor(clDataModuleColor);
	pModuleInfo->NumberOfParams     = 3;
	pModuleInfo->Version			= "1.0";
	pModuleInfo->DontProcess		= true;
	pModuleInfo->DefaultWidth		= 400;
	pModuleInfo->DefaultHeight		= 400;
}

void Color_Selector::onGetParamInfo(int ParamIndex, TParamInfo* pParamInfo)
{
	// all parameters declared in the module class
	switch (ParamIndex)
	{


	case 0:
		pParamInfo->ParamType = ptChooseColor;
		pParamInfo->Caption = "Color";
		pParamInfo->IsInput = FALSE;
		pParamInfo->IsOutput = TRUE;
		pParamInfo->DontSave = FALSE;
		break;

	case 1:
		pParamInfo->ParamType = ptTextField;
		pParamInfo->Caption = "Hex Value";
		pParamInfo->IsInput = FALSE;
		pParamInfo->IsOutput = TRUE;
		pParamInfo->DontSave = FALSE;
		break;

	// default case
	default:
		break;
	}
}//getpinf

void Color_Selector::onSetEventAddress(int ParamIndex, UsineEventPtr pEvent)
{

	//Initialyse all events adress declared in your module class
	switch (ParamIndex)
	{
		// INPUTS

	case 0:
		pColorOut = pEvent;
		break;
	case 1:
		pColorHex = pEvent;
		break;

		// default case
	default:
		break;

	}
}

void Color_Selector::onInitModule(MasterInfo* pMasterInfo, ModuleInfo* pModuleInfo)
{
	
	MSDWN = FALSE;
	HUE_CHG = TRUE;
	PAINT_WHEEL = TRUE;
	INIT_ALL();
	//0.3 0.7
	BGrect.bottom = 0.7;
		BGrect.top = 0.3;
		BGrect.left = 0.3;
		BGrect.right = 0.7;

		TxtRect.bottom = 0.85;
		TxtRect.top = 0.8;
		TxtRect.left = 0;
		TxtRect.right = 1;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
/*void Color_Selector::ResizeModule(void* pModule, float W, float H)
{
	Resize((Color_Selector*)pModule, 400, 400);
} */
////////////////////////////////////////////////////////////////////////////////////////////////////
void Color_Selector::onCallBack(UsineMessage* Message)
{
try
	{
	 if (Message->message == NOTIFY_MSG_USINE_CALLBACK)
		{  int paramIndex = (int)Message->wParam;
				///////////////////////////////////////////////////

			if ((paramIndex == 0) && (Message->lParam == MSG_CHANGE))
			{
			    sdkRepaintPanel();}

//////////////////////////////////////////////////////////////////////////////////////////////////
		} //before is cb

	}
	catch (...)
	{
		//sdkTraceErrorChar("error");
	}

} // end psyk
//////////// Callbacks ////////////////////////////////////
void Color_Selector::INIT_ALL()
{
	//ResizeModule(Color_Selector, 400, 400);
	for (int i = 0; i < RingMax; i++)
	{
		float t = float(float(i) / float(RingMax));
		PRing[i].x = (cos(t * Ring_Radius * 8 * PI) / 2) + 0.5;
		PRing[i].y = (sin(t * Ring_Radius * 8 * PI) / 2) + 0.5;
	}

}
///////////////////////////////////////////////
//void Color_Selector::onResize()
//{	ResizeModule(400, 400);}
/////////////////////////////////////////////////////////////////////////////////////////////////////
template< typename T >
std::string int_to_hex(T i)
{
	std::stringstream stream;
	stream << ""
		<< std::setfill('0') << std::setw(sizeof(T) * 2)
		<< std::hex << i;
	return stream.str();
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void Color_Selector::GET_FINAL_COLOR()
{
	FINAL_COLOR = sdkColorAhslToAlphaColor(sdkColorAhsl(SEL_HUE, SEL_SAT, SEL_LUM));
	long int FINAL_COLOR_VALUE = long int(FINAL_COLOR);
	TxtColorHex = int_to_hex(FINAL_COLOR_VALUE);
	sdkSetEvtColor(pColorOut, FINAL_COLOR);
	sdkSetEvtPChar(pColorHex, AnsiCharPtr(TxtColorHex.c_str()));
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void Color_Selector::COMPUTE_INPUT(float X, float Y)
{
	MSX = X;
	MSY = Y;

	if (MSDWN)
	//HUE_CHG = FALSE;
	{
		Distance_center = float(sqrt(pow((0.5 - X), 2) + pow((0.5 - Y), 2)));
		if ((Distance_center > 0.48) && (Distance_center < 0.52))
		{
			float Angle_center = float((atan2(Y - 0.5, 0.5 - X)) + PI) / (2 * PI);
			MSD_HUE.x = MSX;
			MSD_HUE.y = MSY;
			SEL_HUE = fmodf(-Angle_center * 360, 360);
			HUE_CHG = true;
		}

		if ((abs(X - 0.5) < 0.3) && (abs(Y - 0.5) < 0.3))
		{
			MSD_LUMSAT.x = X;
			MSD_LUMSAT.y = Y;
			SEL_LUM = ((1 - Y) * 2) - 0.5;
			SEL_LUM = fminf(1, fmaxf(0, SEL_LUM));
			SEL_SAT = (X * 2) - 0.5;
			SEL_SAT = fminf(1, fmaxf(0, SEL_SAT));
		}

	}
	//sdkTracePrecision(HUE_CHG);
	GET_FINAL_COLOR();
	sdkRepaintPanel();

}
///////////////////////////////////////////////////////////////////////////////////////////////////
void Color_Selector::PAINT_HUE_WHEEl()
{
//temp disabled. all need to be redrawn or disapear
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void Color_Selector::PAINT_HSL_TEXT()
{
	string TxtHue = sdkIntToString((int)abs((fmodf(((SEL_HUE / 360) * 255) - 255, 256))));
	string TxtSat = sdkIntToString((int)(SEL_SAT * 255));
	string TxtLum = sdkIntToString((int)(SEL_LUM * 255));

	Txt = "H: ";
	Txt.append(TxtHue);
	Txt.append(" ");
	Txt.append("S: ");
	Txt.append(TxtSat);
	Txt.append(" ");
	Txt.append("L: ");
	Txt.append(TxtLum);
	Txt.append(" ");
	Txt.append("Hex: ");
	Txt.append(TxtColorHex);

	sdkFillText(TxtRect, AnsiCharPtr(Txt.c_str()), WHITE_COLOR, 0.03, FALSE, FALSE, taCenter, taCenter, FALSE);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void Color_Selector::onPaint()
{

	sdkFillRect(BGrect, FINAL_COLOR, 0.5, FINAL_COLOR, 0.5);

	if (PAINT_WHEEL)
	{ 
	float t;
	for (int i = 0; i < RingMax; i++)
		{
		t = float(float(i) / float(RingMax));

		RING_COLOR = sdkColorAhslToAlphaColor(sdkColorAhsl(t * 360, 1, 0.5));

		sdkDrawPoint(PRing[i], RING_COLOR, Ring_Dot_Size, TRUE);
		}
	//PAINT_WHEEL = FALSE;
	}
	HUE_COLOR = sdkColorAhslToAlphaColor(sdkColorAhsl(SEL_HUE, 1, 0.5));
	sdkDrawPoint(MSD_HUE, WHITE_COLOR, Ring_Dot_Size / 1.4, TRUE);
	sdkDrawPoint(MSD_HUE, HUE_COLOR, Ring_Dot_Size / 1.65, TRUE);

	if (HUE_CHG)
	{
		float u;
		float v;
		for (int j = 0; j < RingMax; j++)
		{
			u = float(float(j) / float(RingMax));
			for (int k = 0; k < RingMax; k++)
			{
				v = float(float(k) / float(RingMax));

				PLUM_SAT.x = (u / 2) + 0.25;
				PLUM_SAT.y = ((1 - v) / 2) + 0.25;
				LUM_SAT_COLOR = sdkColorAhslToAlphaColor(sdkColorAhsl(SEL_HUE, u, v));

				sdkDrawPoint(PLUM_SAT, LUM_SAT_COLOR, Ring_Dot_Size / 16, FALSE);
			}
		}
	}

	sdkDrawPoint(MSD_LUMSAT, WHITE_COLOR, Ring_Dot_Size / 1.4, FALSE);
	sdkDrawPoint(MSD_LUMSAT, FINAL_COLOR, Ring_Dot_Size / 1.65, FALSE);
	PAINT_HSL_TEXT();
	sdkRepaintPanel();
}
////////////////////////////////////////////////////////////////////-
////////////////////////////////////////////////////////////////////////
void Color_Selector::onMouseMove(TShiftState Shift, float X, float Y)
{
	//HUE_CHG = FALSE;
	COMPUTE_INPUT(X, Y);
}
void Color_Selector::onMouseDown(TMouseButton Button, TShiftState Shift, float X, float Y)
{
		MSDWN = TRUE;
		//HUE_CHG = FALSE;
		COMPUTE_INPUT(X, Y);
}
void Color_Selector::onMouseUp(TMouseButton Button, TShiftState Shift, float X, float Y)
{
		MSDWN = FALSE;
		GET_FINAL_COLOR();
}
/////////////////////////////////////////////////////////////////////////////////////
