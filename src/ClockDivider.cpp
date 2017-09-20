#include "Autodafe.hpp"


struct ClockDivider : Module {
	enum ParamIds {
		
		NUM_PARAMS
	};
	enum InputIds {
		CLOCK_INPUT,
		 
		NUM_INPUTS
	};
	enum OutputIds {
		OUT1,
		OUT2,
		OUT4,
		OUT8,
		OUT16,
		NUM_OUTPUTS
	};

	float lights[5] = {};

	ClockDivider();
	void step();
};


ClockDivider::ClockDivider() {
	params.resize(NUM_PARAMS);
	inputs.resize(NUM_INPUTS);
	outputs.resize(NUM_OUTPUTS);
}

static float clip(float x) {
	x = clampf(x, -2.0, 2.0);
	return x / powf(1.0 + powf(x, 24.0), 1 / 24.0);
}

void ClockDivider::step() {
	
	
	float clock = 12* getf(inputs[CLOCK_INPUT]);

	
	float out1 = clock;
	float out2 = out1 / 2;
	float out4 = out1 / 4;
	float out8 = out1 / 8;
	float out16 = out1 / 16;

	// Set outputs
	if (outputs[OUT1]) {
		*outputs[OUT1] = clip(out1 / 10.0) * 10.0;
	}
	
	if (outputs[OUT2]) {
		*outputs[OUT2] = clip(out2 / 10.0) * 10.0;
	}

	if (outputs[OUT4]) {
		*outputs[OUT4] = clip(out4 / 10.0) * 10.0;
	}

	if (outputs[OUT8]) {
		*outputs[OUT8] = clip(out8 / 10.0) * 10.0;
	}

	if (outputs[OUT16]) {
		*outputs[OUT16] = clip(out16 / 10.0) * 10.0;
	}
	lights[0] = out1 / 5.0;
	lights[1] = out2 / 5.0;
	lights[2] = out4 / 5.0;
	lights[3] = out8 / 5.0;
	lights[4] = out16 / 5.0;




	
}


ClockDividerWidget::ClockDividerWidget() {
	ClockDivider *module = new ClockDivider();
	setModule(module);
	box.size = Vec(15*6, 380);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load("plugins/Autodafe/res/ClockDivider.svg"));
		addChild(panel);
	}

	addChild(createScrew<ScrewBlack>(Vec(15, 0)));
	addChild(createScrew<ScrewBlack>(Vec(15, 365)));

	

	addInput(createInput<PJ3410Port>(Vec(2, 40), module, ClockDivider::CLOCK_INPUT));
	
	addOutput(createOutput<PJ3410Port>(Vec(2, 80), module, ClockDivider::OUT1));
	addOutput(createOutput<PJ3410Port>(Vec(2, 120), module, ClockDivider::OUT2));
	addOutput(createOutput<PJ3410Port>(Vec(2, 160), module, ClockDivider::OUT4));
	addOutput(createOutput<PJ3410Port>(Vec(2, 200), module, ClockDivider::OUT8));
	addOutput(createOutput<PJ3410Port>(Vec(2, 240), module, ClockDivider::OUT16));

	addChild(createValueLight<SmallLight<GreenRedPolarityLight>>(Vec(38, 80), &module->lights[0]));
	addChild(createValueLight<SmallLight<GreenRedPolarityLight>>(Vec(38, 120), &module->lights[1]));
	addChild(createValueLight<SmallLight<GreenRedPolarityLight>>(Vec(38, 160), &module->lights[2]));
	addChild(createValueLight<SmallLight<GreenRedPolarityLight>>(Vec(38, 200), &module->lights[3]));
	addChild(createValueLight<SmallLight<GreenRedPolarityLight>>(Vec(38, 240), &module->lights[4]));
}
