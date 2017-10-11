#include "rack.hpp"
#include "Biquad.h"
#include "VAStateVariableFilter.h"




using namespace rack;



////////////////////
// module widgets
////////////////////

extern Plugin *plugin;




/////////////////////////////
// CUSTOM KNOBS & GRAPHICS //
/////////////////////////////


struct AutodafeKnobRed : SVGKnob {
    AutodafeKnobRed() {
        box.size = Vec(20, 20);
        minAngle = -0.75*M_PI;
        maxAngle = 0.75*M_PI;
        setSVG(SVG::load(assetPlugin(plugin, "res/AutodafeKnobRed.svg")));
    }
};


struct AutodafeKnobBlue : SVGKnob {
	AutodafeKnobBlue() {
		box.size = Vec(20, 20);
		minAngle = -0.75*M_PI;
		maxAngle = 0.75*M_PI;
		setSVG(SVG::load(assetPlugin(plugin, "res/AutodafeKnobBlue.svg")));
	}
};


struct AutodafeKnobGreen : SVGKnob {
	AutodafeKnobGreen() {
		box.size = Vec(20, 20);
		minAngle = -0.75*M_PI;
		maxAngle = 0.75*M_PI;
		setSVG(SVG::load(assetPlugin(plugin, "res/AutodafeKnobGreen.svg")));
	}
};


struct AutodafeKnobGray : SVGKnob {
	AutodafeKnobGray() {
		box.size = Vec(20, 20);
		minAngle = -0.75*M_PI;
		maxAngle = 0.75*M_PI;
		setSVG(SVG::load(assetPlugin(plugin, "res/AutodafeKnobGray.svg")));
	}
};
struct AutodafeKnobPurple : SVGKnob {
	AutodafeKnobPurple() {
		box.size = Vec(20, 20);
		minAngle = -0.75*M_PI;
		maxAngle = 0.75*M_PI;
		setSVG(SVG::load(assetPlugin(plugin, "res/AutodafeKnobPurple.svg")));
	}
};

struct AutodafeKnobPink : SVGKnob {
	AutodafeKnobPink() {
		box.size = Vec(20, 20);
		minAngle = -0.75*M_PI;
		maxAngle = 0.75*M_PI;
		setSVG(SVG::load(assetPlugin(plugin, "res/AutodafeKnobPink.svg")));
	}
};

struct AutodafeKnobOrange : SVGKnob {
	AutodafeKnobOrange() {
		box.size = Vec(20, 20);
		minAngle = -0.75*M_PI;
		maxAngle = 0.75*M_PI;
		setSVG(SVG::load(assetPlugin(plugin, "res/AutodafeKnobOrange.svg")));
	}
};



struct AutodafeKnobYellow : SVGKnob {
	AutodafeKnobYellow() {
		box.size = Vec(20, 20);
		minAngle = -0.75*M_PI;
		maxAngle = 0.75*M_PI;
		setSVG(SVG::load(assetPlugin(plugin, "res/AutodafeKnobYellow.svg")));
	}
};


struct AutodafeButton : SVGSwitch, MomentarySwitch {
    AutodafeButton() {

    	addFrame(SVG::load(assetPlugin(plugin, "res/AutodafeButton.svg")));
        //SVG::load("res/AutodafeButton.svg");
		
		box.size = Vec(20,20);
      
    } 
};   



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







struct FormantFilterWidget : ModuleWidget{
	FormantFilterWidget();
};

struct MultiModeFilterWidget : ModuleWidget{
	MultiModeFilterWidget();
};
struct FixedFilterWidget : ModuleWidget{
	FixedFilterWidget();
};





struct PhaserFxWidget : ModuleWidget{
	PhaserFxWidget();
};
















