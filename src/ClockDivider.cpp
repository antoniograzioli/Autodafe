//**************************************************************************************
//Clock Divider Module for VCV Rack by Autodafe http://www.autodafe.net
//
//Based in part on code created by user rafzael on KVR Forum: https://www.kvraudio.com/forum/viewtopic.php?f=23&t=489230&start=90
//**************************************************************************************


#include "Autodafe.hpp"
struct ClockDivider : Module {
	enum ParamIds {
		RESET_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		CLOCK_INPUT,
		RESET_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		OUT1,
		OUT2,
		OUT4,
		OUT8,
		OUT16,
		OUT32,
		NUM_OUTPUTS
	};
	int clock2Count = 0;
	int clock4Count = 0;
	int clock8Count = 0;
	int clock16Count = 0;
	int clock32Count = 0;

	SchmittTrigger trigger2;
	SchmittTrigger trigger4;
	SchmittTrigger trigger8;
	SchmittTrigger trigger16;
	SchmittTrigger trigger32;

	SchmittTrigger reset_trig;

    float lights[5] = {0};

	void initialize() {

		lights[0] = 0.0;
		lights[1] = 0.0;
		lights[2] = 0.0;
		lights[3] = 0.0;
        lights[4] = 0.0;


	}

	ClockDivider();
	void step();
};







ClockDivider::ClockDivider() {
	params.resize(NUM_PARAMS);
	inputs.resize(NUM_INPUTS);
	outputs.resize(NUM_OUTPUTS);
	trigger2.setThresholds(0.0, 1.0);
	trigger4.setThresholds(0.0, 1.0);
	trigger8.setThresholds(0.0, 1.0);
	trigger16.setThresholds(0.0, 1.0);
	trigger32.setThresholds(0.0, 1.0);

	reset_trig.setThresholds(0.0, 1.0);

}



const float lightLambda = 0.075;
int divider2 = 2;
int divider4 = 4;

int divider8 = 8;
int divider16 = 16;
int divider32 = 32;
void ClockDivider::step() {

	bool reset = false;

	if (reset_trig.process(params[RESET_PARAM]))
	{
		clock2Count = 0;
		clock4Count = 0;
		clock8Count = 0;
		clock16Count = 0;
		clock32Count = 0;

		reset = true;
	}

	if ((clock2Count >= divider2) || (reset_trig.process(getf(inputs[RESET_INPUT]))))
	{
		clock2Count = 0;
		
		reset = true;
	}

	if ((clock4Count >= divider4) || (reset_trig.process(getf(inputs[RESET_INPUT]))))
	{
		clock4Count = 0;
		
		reset = true;
	}

	if ((clock8Count >= divider8) || (reset_trig.process(getf(inputs[RESET_INPUT]))))
	{
		clock8Count = 0;
		
		reset = true;
	}

	if ((clock16Count >= divider16) || (reset_trig.process(getf(inputs[RESET_INPUT]))))
	{
		clock16Count = 0;
		
		reset = true;
	}

	if ((clock32Count >= divider32) || (reset_trig.process(getf(inputs[RESET_INPUT]))))
	{
		clock32Count = 0;
	
		reset = true;
	}


	if (clock2Count < divider2 / 2)
	{
		setf(outputs[OUT2], 10.0);
		if (clock2Count == 0)
		{
			lights[0] = 1.0;
		}
		else
		{
			lights[0] -= lights[0] / lightLambda / gSampleRate;
		}
		
	}
	else
	{
		setf(outputs[OUT2], 0.0);
		lights[0] = 0.0;
		
	}


	if (clock4Count < divider4 / 2)
	{
		setf(outputs[OUT4], 10.0);
		if (clock4Count == 0)
		{
			lights[1] = 1.0;
		}
		else
		{
			lights[1] -= lights[1] / lightLambda / gSampleRate;
		}
		
	}
	else
	{
		setf(outputs[OUT4], 0.0);
		lights[1] = 0.0;
		
	}


	if (clock8Count < divider8 / 2)
	{
		setf(outputs[OUT8], 10.0);
		if (clock8Count == 0)
		{
			lights[2] = 1.0;
		}
		else
		{
			lights[2] -= lights[2] / lightLambda / gSampleRate;
		}
	
	}
	else
	{
		setf(outputs[OUT8], 0.0);
		lights[2] = 0.0;
		
	}


	if (clock16Count < divider16 / 2)
	{
		setf(outputs[OUT16], 10.0);
		if (clock16Count == 0)
		{
			lights[3] = 1.0;
		}
		else
		{
			lights[3] -= lights[3] / lightLambda / gSampleRate;
		}
		
	}
	else
	{
		setf(outputs[OUT16], 0.0);
		lights[3] = 0.0;
	
	}


	if (clock32Count < divider32 / 2)
	{
		setf(outputs[OUT32], 10.0);
		if (clock16Count == 0)
		{
			lights[4] = 1.0;
		}
		else
		{
			lights[4] -= lights[4] / lightLambda / gSampleRate;
		}
		
	}
	else
	{
		setf(outputs[OUT32], 0.0);
		lights[4] = 0.0;
	
	}
	 




	if (reset == false)
	{
		if (trigger2.process(getf(inputs[CLOCK_INPUT])) && clock2Count <= divider2)
		{
			clock2Count++;
		
		}

	}

	if (reset == false)
	{
		if (trigger4.process(getf(inputs[CLOCK_INPUT])) && clock4Count <= divider4)
		{
			clock4Count++;
			
		}

	}

	if (reset == false)
	{
		if (trigger8.process(getf(inputs[CLOCK_INPUT])) && clock8Count <= divider8)
		{
			clock8Count++;
		
		}

	}

	if (reset == false)
	{
		if (trigger16.process(getf(inputs[CLOCK_INPUT])) && clock16Count <= divider16)
		{
			clock16Count++;
		
		}

	}

	if (reset == false)
	{
		if (trigger32.process(getf(inputs[CLOCK_INPUT])) && clock32Count <= divider32)
		{
			clock32Count++;
			
		}

	}
}


ClockDividerWidget::ClockDividerWidget() {
	ClockDivider *module = new ClockDivider();
	setModule(module);
	box.size = Vec(15 * 4, 380);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load("plugins/Autodafe/res/ClockDivider.svg"));
		addChild(panel);
	}

	addChild(createScrew<ScrewSilver>(Vec(1, 0)));
	addChild(createScrew<ScrewSilver>(Vec(1, 365)));

	addInput(createInput<PJ3410Port>(Vec(2, 20), module, ClockDivider::CLOCK_INPUT));
	addInput(createInput<PJ3410Port>(Vec(2, 60), module, ClockDivider::RESET_INPUT));
	addParam(createParam<LEDButton>(Vec(38, 67), module, ClockDivider::RESET_PARAM, 0.0, 1.0, 0.0));
	 
	addOutput(createOutput<PJ3410Port>(Vec(2, 120), module, ClockDivider::OUT2));
	addOutput(createOutput<PJ3410Port>(Vec(2, 160), module, ClockDivider::OUT4));
	addOutput(createOutput<PJ3410Port>(Vec(2, 200), module, ClockDivider::OUT8));
	addOutput(createOutput<PJ3410Port>(Vec(2, 240), module, ClockDivider::OUT16));
	addOutput(createOutput<PJ3410Port>(Vec(2, 280), module, ClockDivider::OUT32));

	addChild(createValueLight<SmallLight<GreenRedPolarityLight>>(Vec(38, 125), &module->lights[0]));
	addChild(createValueLight<SmallLight<GreenRedPolarityLight>>(Vec(38, 165), &module->lights[1]));
	addChild(createValueLight<SmallLight<GreenRedPolarityLight>>(Vec(38, 205), &module->lights[2]));
	addChild(createValueLight<SmallLight<GreenRedPolarityLight>>(Vec(38, 245), &module->lights[3]));
	addChild(createValueLight<SmallLight<GreenRedPolarityLight>>(Vec(38, 285), &module->lights[4]));

}
