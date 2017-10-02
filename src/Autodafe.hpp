#include "rack.hpp"
#include "Biquad.h"

using namespace rack;


////////////////////
// module widgets
////////////////////



struct LFOWidget : ModuleWidget {
	LFOWidget();
};



struct Multiple28Widget : ModuleWidget  {
	Multiple28Widget();
};


struct Multiple18Widget : ModuleWidget  {
	Multiple18Widget();
};

struct ClockDividerWidget : ModuleWidget {
	ClockDividerWidget();
};



struct SEQ16Widget : ModuleWidget{
	SEQ16Widget();
	
};

struct TriggerSeqWidget : ModuleWidget{
	TriggerSeqWidget();
	
};


struct FoldBackWidget : ModuleWidget{
	FoldBackWidget();
};

struct BitCrusherWidget : ModuleWidget{
	BitCrusherWidget();
};





struct SEQ8Widget : ModuleWidget{
	SEQ8Widget();
	
};






struct FixedFilterWidget : ModuleWidget{
	FixedFilterWidget();
};




struct PhaserFxWidget : ModuleWidget{
	PhaserFxWidget();
};





